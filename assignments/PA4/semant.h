#ifndef SEMANT_FAIL_H_
#define SEMANT_FAIL_H_

#include <assert.h>
#include <iostream>  
#include "cool-tree.h"
#include "stringtab.h"
#include "symtab.h"
#include "list.h"
#include<map>
#include<list>
#include<set>
#include "compiler_type_traits.h"

#define TRUE 1
#define FALSE 0

class ClassTable;
typedef ClassTable *ClassTableP;

// This is a structure that may be used to contain the semantic
// information such as the inheritance graph.  You may use it or not as
// you like: it is only here to provide a container for the supplied
// methods.

class ClassTable {

private:
  int semant_errors;
  void install_basic_classes();
  ostream& error_stream;


public:
  ClassTable(Classes);
  int errors() { return semant_errors; }
  static ostream& semant_error();
  static ostream& semant_error(Class_ c);
  static ostream& semant_error(Symbol filename, tree_node *t);


  std::map<Symbol,Class_> m_classes;

  std::list<Symbol>* get_inheretance_list(Class_ inhr_class){
    std::list<Class_>* inhr_list_ptr = new std::list<Class_>(inhr_class->GetName());
    while(inhr_class->GetName() != Object){
      inhr_class = find(inhr_class->GetParent());
      inhr_list_ptr->push_back(inhr_class->GetName());
    }
    return inhr_list_ptr;
  }


  bool check_inheritance(Symbol ancestor, Symbol child){
    Symbol parent = m_classes[child].GetParent();
    while(parent != ancestor){
      if(parent == Object){
        return false;
      }
    parent = m_classes[parent].GetParent();
    }
    return true;
  }

  Symbol find_common_ancestor(Symbol type1, Symbol type2){
    Symbol parent1 = m_classes[type1].GetParent();
    Symbol parent2 = m_classes[type2].GetParent();
    while(parent1 != parent2 || parent1 != Object || parent2 != Object){
      parent1 = m_classes[parent1].GetParent();
      parent2 = m_classes[parent1].GetParent();
    }
    if(parent1 == Object || parent2 == Object){
      return Object;
    }else{
      return parent1;
    }
  }

};


template<class _FeatureType>
inline void add_feature_to_method_map(_FeatureType& feature, std::map<Symbol,method_class>& map){
  typedef typename __type_traits<_FeatureType>::Is_Method Is_Method;
  __add_feature_to_method_map(feature, map, Is_Method());
}

template<class _FeatureType>
void __add_feature_to_method_map(_FeatureType& feature, std::map<Symbol,method_class>& map, __true_type){
  map.insert(std::make_pair<feature.GetName(),feature>);
}

template<class _FeatureType>
void __add_feature_to_method_map(_FeatureType& feature, std::map<Symbol,method_class>& map, __false_type){
  // do nothing if feature is not method;
}


template<class _FeatureType>
inline void add_feature_to_attr_map(_FeatureType& feature, std::map<Symbol,attr_class>& map){
  typedef typename __type_traits<_FeatureType>::Is_Attribute Is_Attribute;
  __add_feature_to_attr_map(feature, map, Is_Attribute());
}

template<class _FeatureType>
void __add_feature_to_attr_map(_FeatureType& feature, std::map<Symbol,attr_class>& map, __true_type){
  map.insert(std::make_pair<feature.GetName(),feature>);
}

template<class _FeatureType>
void __add_feature_to_attr_map(_FeatureType& feature, std::map<Symbol,attr_class>& map, __false_type){
  // do nothing if feature is not attr;
}

template<class _Feature>
void add_feature_to_symboltable(_FeatureType& feature, SymbolTable<Symbol.Symbol>* symboltable, ClassTable* classtable,Claass_ curr_class){
  typedef typename __type_traits<_FeatureType>::Is_Attribute Is_Attribute;
  __add_feature_to_symboltable(feature,symboltable,classtable,Is_Attribute());
}

template<class _Feature>
void __add_feature_to_symboltable(_FeatureType& feature, SymbolTable<Symbol.Symbol>* symboltable,ClassTable* classtable,Claass_ curr_class, __true_type){
  Symbol name = feature->GetName();
  if(name == self){
    classtable->semant_error(curr_class) << "Error! 'self' cannot be the name of an attribute in class " << curr_class->GetName() << std::endl;
  }
  if(symboltable->lookup(name) != NULL){
    classtable->semant_error(curr_class) << "Error! attribute '" << name << "' already exists!" << std::endl;
  }
  symboltable->addid(name, feature->GetType_decl());
}

template<class _Feature>
void __add_feature_to_symboltable(_FeatureType& feature, SymbolTable<Symbol.Symbol>* symboltable,ClassTable* classtable,Claass_ curr_class, __false_type){
  //do nothing if feature is not attr
}

template<class _FeatureType>
inline void check_method_overrride(_FeatureType& feature, Symbol class_name,std::map<Symbol,std::map<Symbol,method_class>>* m_methods, ClassTable* classtable){
  typedef typename __type_traits<_FeatureType>::Is_Method Is_Method;
  __check_method_overrride(feature,class_name,m_methods,Is_Method());
}


template<class _FeatureType>
void __check_method_overrride(_FeatureType& feature, Symbol class_name,std::map<Symbol,std::map<Symbol,method_class>>* m_methods, ClassTable* classtable, __true_type){
  Formals curr_formals = feature.GetFormals();
  std::list<Symbol> inhr_lst = classtable->get_inheretance_list(class_name);
  // inhr_list size larger than 1 is assumed, which means at least a class inherits from Object
  for(auto iter = ++(inhr_lst.begin());iter != inhr_lst.end();++iter){
    Symbol ancestor_name = *iter;
    std::map<Symbol,method_class>* ancestor_m_methods = &*m_methods[ancestor_name];
    std::map<Symbol,method_class>::iterator method_iter = ancestor_m_methods->find(feature.GetName());
    if(method_iter != ancestor_m_methods->end()){ // if find override
      Formals formals = method_iter->GetFormals();
        int k1 = formals->first(), k2 = curr_formals->first();
        for (; formals->more(k1) && curr_formals->more(k2); k1 = formals->next(k1), k2 = formals->next(k2)) {
            if (formals->nth(k1)->GetType() != curr_formals->nth(k2)->GetType()) {
              classtable->semant_error(classtable->m_classes[class_name]) << "Method override error: formal type not match." << std::endl;
            }
        }

        if (formals->more(k1) || curr_formals->more(k2)) {
          classtable->semant_error(classtable->m_classes[class_name]) << "Method override error: length of formals not match." << std::endl;
        }
    }
  }
}

template<class _FeatureType>
void __check_method_overrride(_FeatureType& feature, Symbol class_name,std::map<Symbol,std::map<Symbol,method_class>>* m_methods, ClassTable* classtable, __false_type){
  // do nothing if feature is not method;
}

template<class _FeatureType>
inline void check_feature_type(_FeatureType& feature,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable,Claass_ curr_class){
  typedef typename type_traits<_FeatureType>::Is_Method Is_Method;
  __check_feature_type(feature,classtable,symboltable,Is_Method());
}

template<class _FeatureType>
void __check_feature_type(_FeatureType& method,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable,Claass_ curr_class,__true_type){
  // method check
  if(classtable->m_classes.find(method.GetReturnType()) == classtable->m_classes.end()){
    classtable->semant_error(curr_class) << "Error! return type " << return_type << " doesn't exist." << std::endl;
  }

  symboltable->enterscope();
  std::set<Symbol> uses_names = std::set<Symbol>();
  Formals formals = method.GetFormals();
  for(int i = formals->first(); formals->more(i); i = formals->next(i)){
    Formal curr_formal = formals->nth(i);
    Symbol name = curr_formal->GetName();
    if (used_names.find(name) != used_names.end()) {
      classtable->semant_error(curr_class) << "Error! formal name duplicated. " << std::endl;
    }else{
      used_names.insert(name);  
    }
    Symbol type = curr_formal->GetType_decl();
    if (classtable->m_classes.find(type) == classtable->m_classes.end()) {
        classtable->semant_error(curr_class) << "Error! Cannot find class " << type << std::endl;
    }

    if (curr_formal->GetName() == self) {
        classtable->semant_error(curr_class) << "Error! self in formal " << std::endl;
    }
    symboltable->addid(name,type);
  }
  Expression expr = curr_formal->GetExpression();
  Symbol expr_type = check_expr_type(*expr);
  if (classtable->check_inheritance(curr_formal->GetReturnType(), expr_type) == false) {
    classtable->semant_error(curr_class) << "Error! return type is not ancestor of expr type. " << std::endl;
  }
  symboltable.exitscope();


}

template<class _FeatureType>
void __check_feature_type(_FeatureType& attr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable,Claass_ curr_class,__false_type){
  // attr check
  Expression expr = attr.GetExpression();
  check_expr_type(*expr);
}

template<class _ExpressionType>
inline Symbol check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable,
                              std::map<Symbol,std::map<Symbol,method_class>>* m_methods,Claass_ curr_class){
  typedef typename __type_traits<_ExpressionType>::Is_Bool_Const_Expr Is_Bool_Const_Expr;
  typedef typename __type_traits<_ExpressionType>::Is_Int_Const_Expr Is_Int_Const_Expr;
  typedef typename __type_traits<_ExpressionType>::Is_Str_Const_Expr Is_Str_Const_Expr;
  typedef typename __type_traits<_ExpressionType>::Is_Const_Expr Is_Const_Expr;
  typedef typename __type_traits<_ExpressionType>::Is_Assign_Expr Is_Assign_Expr;
  typedef typename __type_traits<_ExpressionType>::Is_New_Expr Is_New_Expr;
  typedef typename __type_traits<_ExpressionType>::Is_Dispatch_Expr Is_Dispatch_Expr;
  typedef typename __type_traits<_ExpressionType>::Is_Static_Dispatch_Expr Is_Static_Dispatch_Expr;
  typedef typename __type_traits<_ExpressionType>::Is_Cond_expr Is_Cond_expr;
  typedef typename __type_traits<_ExpressionType>::Is_Sequence_expr Is_Sequence_expr;
  typedef typename __type_traits<_ExpressionType>::Is_Let_expr Is_Let_expr;
  typedef typename __type_traits<_ExpressionType>::Is_Case_expr Is_Case_expr;
  typedef typename __type_traits<_ExpressionType>::Is_Loop_expr Is_Loop_expr;
  typedef typename __type_traits<_ExpressionType>::Is_Isvoid_expr Is_Isvoid_expr;
  typedef typename __type_traits<_ExpressionType>::Is_Not_expr Is_Not_expr;
  typedef typename __type_traits<_ExpressionType>::Is_Compare_Expr Is_Compare_Expr;
  typedef typename __type_traits<_ExpressionType>::Is_Neg_Expr Is_Neg_Expr;
  typedef typename __type_traits<_ExpressionType>::Is_Arith_Expr Is_Arith_Expr;
  typedef typename __type_traits<_ExpressionType>::Is_Equal_Expr Is_Equal_Expr;
  typedef typename __type_traits<_ExpressionType>::Is_No_Expr Is_No_Expr;
  return __check_expr_type(expr, classtable, symboltable, m_methods,curr_class, Is_Bool_Const_Expr(),Is_Int_Const_Expr(),
                                Is_Str_Const_Expr(),Is_Assign_Expr(),Is_New_Expr(),
                                Is_Dispatch_Expr(),Is_Static_Dispatch_Expr(),
                                Is_Cond_expr(),Is_Sequence_expr(),Is_Let_expr(),
                                Is_Case_expr(),Is_Loop_expr(),Is_Isvoid_expr()
                                Is_Not_expr()Is_Compare_Expr(),Is_Neg_Expr(),
                                Is_Arith_Expr(),Is_Equal_Expr(),Is_No_Expr());
}

template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              ,__true_type,__false_type,__false_type
                                              ,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type){
// bool const expr
  return Bool;
}

template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              ,__false_type,__true_type,__false_type
                                              ,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type){
// int const expr
  return Int;
}

template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              ,__false_type,__false_type,__true_type
                                              ,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type){
// str const expr
  return Str;
}

template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              , __false_type,__false_type,__false_type
                                              ,__true_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type){
// assign expr
  Symbol lvalue_type = symboltable.lookup(expr->GetName());
  if(lvalue_type == NULL){
    classtable->semant_error(curr_class) << "Error! Cannot find lvalue " << name << std::endl;
    return Object;
  }
  Symbol rvalue_type = check_expr_type(*(expr->GetExpression()),classtable,symboltable);
  if(classtable->check_inheritance(lvalue_type,rvalue_type)){
  //do nothing
  }else{
    classtable->semant_error(curr_class) << "Error! lvalue is not an ancestor of rvalue. " << std::endl;
    return Object;
  }
  return rvalue_type;
}
template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              , __false_type,__false_type,__false_type
                                              ,__false_type,__true_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type){
// new expr
  Symbol type_name = expr->GetTypename();
  if(type_name != SELF_TYPE && classtable->m_classes.find(type_name) == classtable->m_classes.end()){
    classtable->semant_error(curr_class) << "Error! type " << type_name << " doesn't exist." << std::endl;
  }
  return type_name;
}
template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type
                                              ,__true_type, __false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type){
// dispatch expr
  Expression disp_expr = expr.GetExpression();
  Symbol expr_type = check_expr_type(*disp_expr,classtable,symboltable,m_methods);
  Symbol method_name = expr.GetName();
  std::list<Symbol>* inhr_path = classtable->get_inheretance_list(expr_type);
  method_class* method_ptr = NULL;
  for(auto iter =inhr_path->begin();iter!=inhr_path->end();++iter){
    std::map<Symbol,method_class>* curr_method_map = &m_methods[*iter];
    std::map<Symbol,method_class>::iterator map_iter = curr_method_map->find(method_name);
    if(map_iter != curr_method_map->end()){
      method_ptr = &(map_iter->second);
      break;
    }
  }
  if(!method_ptr){
    classtable->semant_error(curr_class) << "Error! Cannot find method '" << name << "'" << std::endl;
    return Object;
  }
  Expressions actual = expr.GetActual();
  for(int i = actual->first(); actual->more(i); i = actual->next(i)){
    Symbol actual_type = check_expr_type(*(actual->nth(i)),classtable,symboltable,m_methods);
    Symbol formal_type = method->GetFormals()->nth(i)->GetType();
    if(classtable->check_inheritance(formal_type, actual_type)){
      // do nothing
    }
    else{
      classtable->semant_error(curr_class) << "Error! Actual type " << actual_type << " doesn't suit formal type " << formal_type << std::endl;
      return Object;
    }
  }
  if(method->GetType() == SELF_TYPE){
    return expr_type;
  }
  return method->GetType();
}

template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type
                                              ,__false_type, __true_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type){
// static dispatch expr
  Expression disp_expr = expr.GetExpression();
  Symbol expr_type = check_expr_type(*disp_expr,classtable,symboltable,m_methods);
  Symbol type_name = expr.GetTypename();
  if (classtable->check_inheritance(type_name, expr_class)){
  }else{
    classtable->semant_error(curr_class) << "Error! Static dispatch class is not an ancestor." << std::endl;
    return Object;
  }
  std::list<Symbol>* inhr_path = classtable->get_inheretance_list(expr_type);
  method_class* method_ptr = nullptr;
  for(auto iter =inhr_path->begin();iter!=inhr_path->end();++iter){
    std::map<Symbol,method_class>* curr_method_map = &m_methods[*iter];
    std::map<Symbol,method_class>::iterator map_iter = curr_method_map->find(method_name);
    if(map_iter != curr_method_map->end()){
      method_ptr = &(map_iter->second);
      break;
    }
  }
  if(!method_ptr){
    classtable->semant_error(curr_class) << "Error! Cannot find method '" << name << "'" << std::endl;
    return Object;
  }
  Expressions actual = expr.GetActual();
  for(int i = actual->first(); actual->more(i); i = actual->next(i)){
    Symbol actual_type = check_expr_type(*(actual->nth(i)),classtable,symboltable,m_methods);
    Symbol formal_type = method->GetFormals()->nth(i)->GetType();
    if(classtable->check_inheritance(formal_type, actual_type)){
      // do nothing
    }
    else{
      classtable->semant_error(curr_class) << "Error! Actual type " << actual_type << " doesn't suit formal type " << formal_type << std::endl;
      return Object;
    }
  }
  if(method->GetType() == SELF_TYPE){
    return expr_type;
  }
  return method->GetType();  
}

template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type
                                              ,__false_type,__false_type, __true_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type){
// cond expr
  Expression pred = expr->GetPred();
  Expression then_expr = expr->GetThen();
  Expression else_expr = expr->GetElse();
  if(check_expr_type(*pred,classtable,symboltable,m_methods) != Bool){
    classtable->semant_error(curr_class) << "Error! Type of pred is not Bool." << std::endl;
  }
  Symbol then_type = check_expr_type(*then_exp,classtable,symboltable,m_methods);
  Symbol else_type = check_expr_type(*else_exp,classtable,symboltable,m_methods);
  if (else_type == No_type) {
    return then_type;
  }else{
    return classtable->find_common_ancestor(then_type,else_type);
  }

}

template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              , __true_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type){
// sequence expr
  Expressions body = expr.GetBody();
  Symbol last_type;
  for(int i = body->first();body->more();body->next(i)){
    Expression curr_expr = body->nth(i);
    last_type = check_expr_type(*curr_expr,classtable,symboltable,m_methods);
  }
  return last_type;
}

template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type, __true_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type){
// let expr
  Symbol identifier = expr.GetIdentifier();
  if(identifier == self){
    classtable->semant_error(curr_class) << "Error! self in let binding." << std::endl;
    return Object;
  }
  symboltable->enterscope();
  Symbol type_decl = expr.GetType_decl();
  symboltable->addid(identifier,type_decl);
  Expression init = expr.GetInit();
  Symbol init_type = check_expr_type(*init,classtable,symboltable,m_methods);
  if (init_type != No_type) {
    if (classtable->check_inheritance(type_decl, init_type)){
      // do nothing
    }else{
        classtable->semant_error(curr_class) << "Error! init value is not child." << std::endl;
    }
  }
  Expression body = expr.GetBody();
  Symbol body_type = check_expr_type(*body,classtable,symboltable,m_methods);
  symboltable->exitscope();
  return body_type;
}

template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type, __true_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type){
// case expr
  Expression case_expr = expr.GetExpression();
  Symbol expr_type = check_expr_type(*case_expr, classtable,symboltable,m_methods);
  Case branch;
  std::vector<Symbol> branch_types;
  std::vector<Symbol> branch_type_decls;
  Cases cases = expr.GetCases();
  for (int i = cases->first(); cases->more(i); i = cases->next(i)) {
    branch = cases->nth(i);
    Symbol branch_type = check_branch_type((branch_class *)branch,classtable,symboltable,m_methods);
    branch_types.push_back(branch_type);
    branch_type_decls.push_back(((branch_class *)branch)->GetTypeDecl());
  }
  for (int i = 0; i < branch_types.size() - 1; ++i) {
    for (int j = i + 1; j < branch_types.size(); ++j) {
        if (branch_type_decls[i] == branch_type_decls[j]) {
            classtable->semant_error(curr_class) << "Error! Two branches have same type." << std::endl;
        }
    }
  }
  Symbol type = branch_types[0];
  for (int i = 1; i < branch_types.size(); ++i) {
      type = classtable->find_common_ancestor(type, branch_types[i]);
  }
  return type;

}

Symbol check_branch_type(branch_class* branch, ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable,
                        std::map<Symbol,std::map<Symbol,method_class>>* m_methods){
  symboltable->enterscope();
  Expression expr =  branch->GetExpression();
  Symbol name = branch->GetName();
  Symbol type_decl = branch->GetType_decl();
  symboltable->addid(name,type_decl);
  Symbol expr_type =  check_expr_type(expr,classtable,symboltable,m_methods);
  symboltable->exitscope();
  return expr_type;
  

}

template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              , __true_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type){
  // loop expr
  Expression pred = expr.GetPred();
  if (check_expr_type(pred,classtable,symboltable,m_methods) != Bool) {
      classtable->semant_error(curr_class) << "Error! Type of pred is not Bool." << std::endl;
  }
  Expression body = expr.GetBody();
  check_expr_type(body,classtable,symboltable,m_methods);
  return Object;
}

template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type, __true_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type){
// isvoid expr
  Expression void_expr = expr.GetExpression();
  check_expr_type(*void_expr,classtable,symboltable,m_methods);
  return Bool;
}

template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              , __false_type,__false_type,__false_type
                                              ,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type, __true_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type){
// not expr
  Expression not_expr = expr.GetExpression();
  Symbol not_type = check_expr_type(*not_expr,classtable,symboltable,m_methods);
  if(not_type!= Bool){
    classtable->semant_error(curr_class) << "Error! 'not' meets non-Bool value." << std::endl;
    return Object;
  }
  return Bool;
}

template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              , __true_type,__false_type,__false_type
                                              ,__false_type,__false_type){
// compare expr
  Expression lhs = expr.GetLExpression();
  Expression rhs = expr.GetRExpression();
  Symbol lhs_type = check_expr_type(*lhs,classtable,symboltable,m_methods);
  Symbol rhs_type = check_expr_type(*rhs,classtable,symboltable,m_methods);
  if (lhs_type != Int || rhs_type != Int) {
    classtable->semant_error(curr_class) << "Error! '<=' meets non-Int value." << std::endl;
    return Object;
  }else {
    return Bool;
  }

}

template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              , __false_type,__false_type,__false_type
                                              ,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type, __true_type,__false_type
                                              ,__false_type,__false_type){
// neg expr
  Expression neg_expr = expr.GetExpression();
  if (check_expr_type(*neg_expr,classtable,symboltable,m_methods) != Int) {
    classtable->semant_error(curr_class) << "Error! '~' meets non-Int value." << std::endl;
    return Object;
  }else{
    return Int;
  }
}

template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type, __true_type
                                              ,__false_type,__false_type){
// arithmetic expr

  Expression lhs = expr.GetLExpression();
  Expression rhs = expr.GetRExpression();
  Symbol lhs_type = check_expr_type(*lhs,classtable,symboltable,m_methods);
  Symbol rhs_type = check_expr_type(*rhs,classtable,symboltable,m_methods);
  if (lhs_type != Int || rhs_type != Int) {
    classtable->semant_error(curr_class) << "Error! '-' meets non-Int value." << std::endl;
    return Object;
  }else{
    return Int;
  }
}

template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__true_type,__false_type){
// equal expr
  Expression lhs = expr.GetLExpression();
  Expression rhs = expr.GetRExpression();
  Symbol lhs_type = check_expr_type(*lhs,classtable,symboltable,m_methods);
  Symbol rhs_type = check_expr_type(*rhs,classtable,symboltable,m_methods);
  if (lhs_type == Int || rhs_type == Int || lhs_type == Bool || rhs_type == Bool || lhs_type == Str || rhs_type == Str) {
    if (lhs_type != rhs_type) {
      classtable->semant_error(curr_class) << "Error! '=' meets different types." << std::endl;
      return Object;
    }else{
      return Bool;
    }
  }else{
    return Bool;
  }
}

template<class _ExpressionType>
Symbol __check_expr_type(_ExpressionType& expr,ClassTable* classtable,SymbolTable<Symbol,Symbol>* symboltable
                                              ,std::map<Symbol,std::map<Symbol,method_class>>* m_methods
                                              ,Claass_ curr_class
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type,__false_type,__false_type
                                              ,__false_type, __true_type){
// no expr
  return No_type;
}

#endif

