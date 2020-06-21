/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;

extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;

/*
 *  Add Your own definitions here
 */
int block_layer = 0;
bool exist_null = 0;

#define BUFFER_CHECK do { \
          if (string_buf_ptr - string_buf >= MAX_STR_CONST){\
            cool_yylval.error_msg = "String constant too long";\
            BEGIN(INITIAL); \
            return ERROR;\
          } \
        } while(0);

%}



/*
 * Define names for regular expressions here.
 */

TYPE_ID         [A-Z]([A-Za-z0-9_])*
OBJ_ID          [a-z]([A-Za-z0-9_])*

INTEGER         [0-9]+


WHITESPACE      [ \t\f\v\r]+
NEWLINE         "\n"
NULL_CHAR       "\0"
SINGLE_TOKEN    [\+\*\-\~\/\;\(\)\{\}\:\.\@\<\=\,]
INVALID         [^a-zA-Z0-9]
QUOTE           \"
ESCAPE          "\\"
COMMENTBGN        "(*"
COMMENTEND        "*)"
LINECOMMENT       "--"



DARROW          =>
ASSIGN          <-
LE              <=


%x lineComment blockComment str


%%

 /*
  *  Nested comments
  */

{COMMENTBGN}    {
                  BEGIN(blockComment);
                  ++block_layer;
                }
{COMMENTEND}    {
                  cool_yylval.error_msg = "Unmached *)";
                  return ERROR;
                }
{LINECOMMENT}   {
                  BEGIN(lineComment);
                }
<blockComment>{NEWLINE}       { 
                                ++curr_lineno;
                              }
<blockComment>{COMMENTBGN}    {
                                ++block_layer;
                              }
<blockComment>{COMMENTEND}    {
                                if(--block_layer == 0){
                                  BEGIN(INITIAL);
                                }
                              }

<blockComment>{ESCAPE}.       {}
<blockComment>\([^*]          {}
<blockComment><<EOF>>         {
                                cool_yylval.error_msg = "EOF in comment";
                                BEGIN(INITIAL);
                                yyrestart(yyin);
                                return ERROR;
                              }
<blockComment>[^*\\(\n]*      {}
<blockComment>\*+[^ \\)\n]*   {}

<blockComment>\*+\)           {
                                if(--block_layer == 0){
                                  BEGIN(INITIAL);
                                }
                              }
<lineComment>{NEWLINE}        {
                                ++curr_lineno;
                                BEGIN(INITIAL);
                              }
<lineComment>[^\n]*           {}
<lineComment><<EOF>>          {
                                BEGIN(INITIAL);
                              }


 /*
  *  The multiple-character operators. 
  */

{DARROW}          {return (DARROW);}
{ASSIGN}          {return (ASSIGN);}
{LE}              {return (LE);}
{SINGLE_TOKEN}  {
                  return yytext[0];
                }


 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */

(?i:class)      {return CLASS;}
(?i:else)       {return ELSE;}
(?i:fi)         {return FI;}
(?i:if)         {return IF;}
(?i:in)         {return IN;}
(?i:inherits)   {return INHERITS;}
(?i:isvoid)     {return ISVOID;}
(?i:let)        {return LET;}
(?i:loop)       {return LOOP;}
(?i:pool)       {return POOL;}
(?i:then)       {return THEN;}
(?i:while)      {return WHILE;}
(?i:case)       {return CASE;}
(?i:esac)       {return ESAC;}
(?i:new)        {return NEW;}
(?i:of)         {return OF;}
(?i:not)        {return NOT;}

t(?i:rue)       {
                  cool_yylval.boolean = 1; 
                  return BOOL_CONST;
                }
f(?i:alse)      {
                  cool_yylval.boolean = 0; 
                  return BOOL_CONST;
                }
{WHITESPACE}    {}
{INTEGER}       {
                  cool_yylval.symbol = inttable.add_string(yytext); 
                  return INT_CONST; 
                }
{TYPE_ID}       {
                  cool_yylval.symbol = stringtable.add_string(yytext); 
                  return TYPEID;
                }
{OBJ_ID}        {
                  cool_yylval.symbol = stringtable.add_string(yytext); 
                  return OBJECTID;
                }
{NEWLINE}       {
                  ++curr_lineno;
                }




 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
  */

{QUOTE}               {
                        exist_null = 0;
                        string_buf_ptr = string_buf;
                        BEGIN(str);
                      }
<str>{NULL_CHAR}      {
                        exist_null = 1;
                      }
<str>{NEWLINE}        {
                        BEGIN(INITIAL);
                        ++curr_lineno;
                        cool_yylval.error_msg = "Unterminated string constant";
                        return ERROR;
                      }
<str>{ESCAPE}.        {
                        BUFFER_CHECK
                        switch(yytext[yyleng-1]){
                          case 'b': *string_buf_ptr++ = '\b'; break;
                          case 't': *string_buf_ptr++ = '\t'; break;
                          case 'f': *string_buf_ptr++ = '\f'; break;
                          case 'n': *string_buf_ptr++ = '\n'; break;
                          case  0:  exist_null = 1;      break;
                          default:  *string_buf_ptr++ = yytext[yyleng-1]; break;
                        }
                      }
<str>{ESCAPE}{NEWLINE}  {
                          curr_lineno++;
                          BUFFER_CHECK
                          *string_buf_ptr++ = '\n';
                        } 
<str>{QUOTE}          {
                        BEGIN(INITIAL);
                        BUFFER_CHECK
                        if(exist_null){
                          cool_yylval.error_msg = "String contains null character";
                          return ERROR;
                        }
                        *string_buf_ptr = 0;
                        cool_yylval.symbol = stringtable.add_string(string_buf);
                        return STR_CONST;
                      }

                     
<str><<EOF>>          {
                        BEGIN(INITIAL);
                        cool_yylval.error_msg = "EOF in string constant";
                        yyrestart(yyin);
                        return ERROR;
                      }


<str>.                {
                        BUFFER_CHECK
                        *string_buf_ptr++ = *yytext;
                      }

{INVALID}             {
                        cool_yylval.error_msg = yytext;
                        return ERROR;
                      }


%%