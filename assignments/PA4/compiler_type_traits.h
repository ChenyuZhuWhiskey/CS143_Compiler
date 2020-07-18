#ifndef COMPILER_TYPE_TRAITS_H
#define COMPILER_TYPE_TRAITS_H
#include "cool-tree.h"

struct __true_type{};
struct __false_type{};


template<class _Tp>
struct __type_traits<_Tp>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __false_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};


template<class _Tp>
struct __type_traits<attr_class>{
    typedef __false_type Is_Method ;
    typedef __true_type Is_Attribute ;
    typedef __false_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<method_class>{
    typedef __true_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __false_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};


template<class _Tp>
struct __type_traits<Expression_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<bool_const_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __true_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<int_const_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __true_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<string_const_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __true_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<assign_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __true_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<new__class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __true_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<dispatch_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __true_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<static_dispatch_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __true_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<cond_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __true_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<block_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __true_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<let_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __true_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<typcase_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __true_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<loop_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __true_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<isvoid_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __true_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<comp_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __true_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<leq_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __true_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<lt_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __true_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<neg_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __true_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<plus_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __true_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<sub_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __true_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<mul_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __true_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<divide_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __true_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<eq_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __true_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<let_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __false_type Is_No_Expr;
};

template<class _Tp>
struct __type_traits<no_expr_class>{
    typedef __false_type Is_Method ;
    typedef __false_type Is_Attribute ;
    typedef __true_type Is_Expr;
    typedef __false_type Is_Bool_Const_Expr;
    typedef __false_type Is_Int_Const_Expr;
    typedef __false_type Is_Str_Const_Expr;
    typedef __false_type Is_Assign_Expr;
    typedef __false_type Is_New_Expr;
    typedef __false_type Is_Dispatch_Expr;
    typedef __false_type Is_Static_Dispatch_Expr;
    typedef __false_type Is_Cond_expr;
    typedef __false_type Is_Sequence_expr;
    typedef __false_type Is_Let_expr;
    typedef __false_type Is_Case_expr;
    typedef __false_type Is_Loop_expr;
    typedef __false_type Is_Isvoid_expr;
    typedef __false_type Is_Not_expr;
    typedef __false_type Is_Compare_Expr;
    typedef __false_type Is_Neg_Expr;
    typedef __false_type Is_Arith_Expr;
    typedef __false_type Is_Equal_Expr;
    typedef __true_type Is_No_Expr;
};





#endif