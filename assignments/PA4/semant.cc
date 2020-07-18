

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "semant.h"
#include "utilities.h"
#include <symtab.h>

#include<utility>


extern int semant_debug;
extern char *curr_filename;

static ClassTable* classtable;
static SymbolTable<Symbol,Symbol>* symboltable;
static std::map<Symbol,std::map<Symbol,method_class>>* m_methods;
static std::map<Symbol,std::map<Symbol,attr_class>>* m_attributes;

//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
//////////////////////////////////////////////////////////////////////
static Symbol 
    arg,
    arg2,
    Bool,
    concat,
    cool_abort,
    copy,
    Int,
    in_int,
    in_string,
    IO,
    length,
    Main,
    main_meth,
    No_class,
    No_type,
    Object,
    out_int,
    out_string,
    prim_slot,
    self,
    SELF_TYPE,
    Str,
    str_field,
    substr,
    type_name,
    val;
//
// Initializing the predefined symbols.
//
static void initialize_constants(void)
{
    arg         = idtable.add_string("arg");
    arg2        = idtable.add_string("arg2");
    Bool        = idtable.add_string("Bool");
    concat      = idtable.add_string("concat");
    cool_abort  = idtable.add_string("abort");
    copy        = idtable.add_string("copy");
    Int         = idtable.add_string("Int");
    in_int      = idtable.add_string("in_int");
    in_string   = idtable.add_string("in_string");
    IO          = idtable.add_string("IO");
    length      = idtable.add_string("length");
    Main        = idtable.add_string("Main");
    main_meth   = idtable.add_string("main");
    //   _no_class is a symbol that can't be the name of any 
    //   user-defined class.
    No_class    = idtable.add_string("_no_class");
    No_type     = idtable.add_string("_no_type");
    Object      = idtable.add_string("Object");
    out_int     = idtable.add_string("out_int");
    out_string  = idtable.add_string("out_string");
    prim_slot   = idtable.add_string("_prim_slot");
    self        = idtable.add_string("self");
    SELF_TYPE   = idtable.add_string("SELF_TYPE");
    Str         = idtable.add_string("String");
    str_field   = idtable.add_string("_str_field");
    substr      = idtable.add_string("substr");
    type_name   = idtable.add_string("type_name");
    val         = idtable.add_string("_val");
}



ClassTable::ClassTable(Classes classes) : semant_errors(0) , error_stream(cerr),m_classes(std::map<Symbol,Class_>()) {

    /* Fill this in */
    install_basic_classes();
    for(int i = classes->first();classes->more();classes->next()){
        Class_ curr_class = classes->nth(i);
        if(curr_class->GetName() == SELF_TYPE){
            semant_error(curr_class) << "Error, SELF_TYPE redeclared" <<std::endl;
        }
        if(m_classes.find(curr_class->GetName()) == m_classes.end()){
            m_classes.insert(std::make_pair(curr_class->GetName(),curr_class));
        }else{
            semant_error(curr_class) << "Error, Class " << curr_class->GetName() << " redefined" <<std::endl;
        }
    }

    // find Main class
    if (m_classes.find(Main) == m_classes.end()) {
        semant_error() << "Class Main is not defined." << std::endl;
    }

    //check inheritance
    for(int i = classes->first();classes->more();classes->next()){
        Class_ curr_class = classes->nth(i);
        Symbol parent_name = curr_class->GetParent();
        while(parent_name!=Object && parent_name != curr_class->GetName()){
            if(parent_name == Int || parent_name == Str || parent_name == SELF_TYPE || parent_name == Bool){
                semant_error(curr_class) << "Error! Class " << curr_class->GetName() << " cannot inherit from " << parent_name << std::endl;
                return;
            }
            auto iter = m_classes.find(parent_name);
            if (iter == m_classes.end()){
                semant_error(curr_class) << "Error! Inherent class not find!" <<std::endl;
                return;
            }
            curr_class = (*iter).second;
            parent_name = curr_class->GetParent();
        }
        if(parent_name != Object){
            semant_error(curr_class) << "Error! Cycle Inheretance" << parent_name << std::endl;
        }
    }


}

void ClassTable::install_basic_classes() {

    // The tree package uses these globals to annotate the classes built below.
   // curr_lineno  = 0;
    Symbol filename = stringtable.add_string("<basic class>");
    
    // The following demonstrates how to create dummy parse trees to
    // refer to basic Cool classes.  There's no need for method
    // bodies -- these are already built into the runtime system.
    
    // IMPORTANT: The results of the following expressions are
    // stored in local variables.  You will want to do something
    // with those variables at the end of this method to make this
    // code meaningful.

    // 
    // The Object class has no parent class. Its methods are
    //        abort() : Object    aborts the program
    //        type_name() : Str   returns a string representation of class name
    //        copy() : SELF_TYPE  returns a copy of the object
    //
    // There is no need for method bodies in the basic classes---these
    // are already built in to the runtime system.

    Class_ Object_class =
	class_(Object, 
	       No_class,
	       append_Features(
			       append_Features(
					       single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
					       single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
			       single_Features(method(copy, nil_Formals(), SELF_TYPE, no_expr()))),
	       filename);

    // 
    // The IO class inherits from Object. Its methods are
    //        out_string(Str) : SELF_TYPE       writes a string to the output
    //        out_int(Int) : SELF_TYPE            "    an int    "  "     "
    //        in_string() : Str                 reads a string from the input
    //        in_int() : Int                      "   an int     "  "     "
    //
    Class_ IO_class = 
	class_(IO, 
	       Object,
	       append_Features(
			       append_Features(
					       append_Features(
							       single_Features(method(out_string, single_Formals(formal(arg, Str)),
										      SELF_TYPE, no_expr())),
							       single_Features(method(out_int, single_Formals(formal(arg, Int)),
										      SELF_TYPE, no_expr()))),
					       single_Features(method(in_string, nil_Formals(), Str, no_expr()))),
			       single_Features(method(in_int, nil_Formals(), Int, no_expr()))),
	       filename);  

    //
    // The Int class has no methods and only a single attribute, the
    // "val" for the integer. 
    //
    Class_ Int_class =
	class_(Int, 
	       Object,
	       single_Features(attr(val, prim_slot, no_expr())),
	       filename);

    //
    // Bool also has only the "val" slot.
    //
    Class_ Bool_class =
	class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())),filename);

    //
    // The class Str has a number of slots and operations:
    //       val                                  the length of the string
    //       str_field                            the string itself
    //       length() : Int                       returns length of the string
    //       concat(arg: Str) : Str               performs string concatenation
    //       substr(arg: Int, arg2: Int): Str     substring selection
    //       
    Class_ Str_class =
	class_(Str, 
	       Object,
	       append_Features(
			       append_Features(
					       append_Features(
							       append_Features(
									       single_Features(attr(val, Int, no_expr())),
									       single_Features(attr(str_field, prim_slot, no_expr()))),
							       single_Features(method(length, nil_Formals(), Int, no_expr()))),
					       single_Features(method(concat, 
								      single_Formals(formal(arg, Str)),
								      Str, 
								      no_expr()))),
			       single_Features(method(substr, 
						      append_Formals(single_Formals(formal(arg, Int)), 
								     single_Formals(formal(arg2, Int))),
						      Str, 
						      no_expr()))),
	       filename);

    m_classes.insert(std::make_pair(Object, Object_class));
    m_classes.insert(std::make_pair(IO, IO_class)));
    m_classes.insert(std::make_pair(Int, Int_class));
    m_classes.insert(std::make_pair(Bool, Bool_class));
    m_classes.insert(std::make_pair(Str,Str_class));

}

////////////////////////////////////////////////////////////////////
//
// semant_error is an overloaded function for reporting errors
// during semantic analysis.  There are three versions:
//
//    ostream& ClassTable::semant_error()                
//
//    ostream& ClassTable::semant_error(Class_ c)
//       print line number and filename for `c'
//
//    ostream& ClassTable::semant_error(Symbol filename, tree_node *t)  
//       print a line number and filename
//
///////////////////////////////////////////////////////////////////

ostream& ClassTable::semant_error(Class_ c)
{                                                             
    return semant_error(c->get_filename(),c);
}    

ostream& ClassTable::semant_error(Symbol filename, tree_node *t)
{
    error_stream << filename << ":" << t->get_line_number() << ": ";
    return semant_error();
}

ostream& ClassTable::semant_error()                  
{                                                 
    semant_errors++;                            
    return error_stream;
} 



/*   This is the entry point to the semantic checker.

     Your checker should do the following two things:

     1) Check that the program is semantically correct
     2) Decorate the abstract syntax tree with type information
        by setting the `type' field in each Expression node.
        (see `tree.h')

     You are free to first do 1), make sure you catch all semantic
     errors. Part 2) can be done in a second stage, when you want
     to build mycoolc.
 */
void program_class::semant()
{
    initialize_constants();

    /* ClassTable constructor may do some semantic analysis */
    ClassTable *classtable = new ClassTable(classes);

    /* some semantic analysis code may go here */

    // initialize symbol table and methods
    symboltable = new SymbolTable<Symbol.Symbol>();
    m_methods = new std::map<Symbol,std::map<Symbol,method_class>>();
    m_attributes = new std::map<Symbol,std::map<Symbol,attr_class>>();

    //construct method table and arribute table
    Class_ curr_class;
    for(int i = classes->first();classes->more();classes->next(i)){
        curr_class = classes->nth(i);
        Features features = curr_class->GetFeatures();
        std::map<Symbol,method_class> tmp_method_map = std::map<Symbol,method_class>();
        std::map<Symbol,attr_class> tmp_attr_map = std::map<Symbol,attr_class>();
        for(int j = features->first();features->more();features->next(j)){
            Feature curr_feature = features->nth(j);
            add_feature_to_method_map(*curr_feature, tmp_method_map);
            add_feature_to_attr_map(*curr_feature, tmp_attr_map);
        }
        m_methods->insert(std::make_pair(curr_class->GetName(),tmp_method_map));

    }

    //check if method overloading is correct

    Claass_ curr_class = classtable->m_classes[class_name];
    Features curr_features = classtable->m_classes[class_name]->GetFeatures();
    for (int j = curr_features->first(); curr_features->more(j); j = curr_features->next(j)) {
        Feature curr_method = curr_features->nth(j);
        check_method_overrride(*curr_method,curr_class->GetName(),m_methods,classtable);
    }

    //type check
    for(int i = classes->first();classes->more(i);classes->next(i)){
        curr_class = classes->nth(i);
        Features features = curr_class->GetFeatures();
        Feature curr_feature;
        symboltable->enterscope();
        for(int j = features->first();features->more();features->next(j)){
            curr_feature = features->nth(j);
            add_feature_to_symboltable(*curr_feature,symboltable,classtable);
        }
        for(int j = features->first();features->more();features->next(j)){
            curr_feature = features->nth(j);
            check_feature_type(*curr_feature,symboltable,classtable);
        }
        symboltable->exitcope();
    }

    if (classtable->errors()) {
	cerr << "Compilation halted due to static semantic errors." << endl;
	exit(1);
    }
}


