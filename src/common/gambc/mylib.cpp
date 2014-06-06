#ifdef ___LINKER_INFO
; File: "mylib.c", produced by Gambit-C v4.7.2
(
407002
" mylib"
((" mylib"))
(
"mylib"
)
(
)
(
" mylib"
"catch-all-errors"
"read-from-string"
"write-exception-to-string"
"write-to-string"
)
(
"eval-string"
)
(
"display-exception"
"eval"
"read"
"with-exception-catcher"
"with-input-from-string"
"with-output-to-string"
"write"
)
 ()
)
#else
#define ___LIBRARY
#define ___VERSION 407002
#define ___MODULE_NAME " mylib"
#define ___LINKER_ID ____20_mylib
#define ___MH_PROC ___H__20_mylib
#define ___SCRIPT_LINE 0
#define ___SYMCOUNT 1
#define ___GLOCOUNT 13
#define ___SUPCOUNT 6
#define ___SUBCOUNT 1
#define ___LBLCOUNT 31
#define ___MODDESCR ___REF_SUB(0)
#include "gambit.h"

___NEED_SYM(___S_mylib)

___NEED_GLO(___G__20_mylib)
___NEED_GLO(___G_catch_2d_all_2d_errors)
___NEED_GLO(___G_display_2d_exception)
___NEED_GLO(___G_eval)
___NEED_GLO(___G_eval_2d_string)
___NEED_GLO(___G_read)
___NEED_GLO(___G_read_2d_from_2d_string)
___NEED_GLO(___G_with_2d_exception_2d_catcher)
___NEED_GLO(___G_with_2d_input_2d_from_2d_string)
___NEED_GLO(___G_with_2d_output_2d_to_2d_string)
___NEED_GLO(___G_write)
___NEED_GLO(___G_write_2d_exception_2d_to_2d_string)
___NEED_GLO(___G_write_2d_to_2d_string)

___BEGIN_SYM
___DEF_SYM(0,___S_mylib,"mylib")
___END_SYM

#define ___SYM_mylib ___SYM(0,___S_mylib)

___BEGIN_GLO
___DEF_GLO(0," mylib")
___DEF_GLO(1,"catch-all-errors")
___DEF_GLO(2,"eval-string")
___DEF_GLO(3,"read-from-string")
___DEF_GLO(4,"write-exception-to-string")
___DEF_GLO(5,"write-to-string")
___DEF_GLO(6,"display-exception")
___DEF_GLO(7,"eval")
___DEF_GLO(8,"read")
___DEF_GLO(9,"with-exception-catcher")
___DEF_GLO(10,"with-input-from-string")
___DEF_GLO(11,"with-output-to-string")
___DEF_GLO(12,"write")
___END_GLO

#define ___GLO__20_mylib ___GLO(0,___G__20_mylib)
#define ___PRM__20_mylib ___PRM(0,___G__20_mylib)
#define ___GLO_catch_2d_all_2d_errors ___GLO(1,___G_catch_2d_all_2d_errors)
#define ___PRM_catch_2d_all_2d_errors ___PRM(1,___G_catch_2d_all_2d_errors)
#define ___GLO_eval_2d_string ___GLO(2,___G_eval_2d_string)
#define ___PRM_eval_2d_string ___PRM(2,___G_eval_2d_string)
#define ___GLO_read_2d_from_2d_string ___GLO(3,___G_read_2d_from_2d_string)
#define ___PRM_read_2d_from_2d_string ___PRM(3,___G_read_2d_from_2d_string)
#define ___GLO_write_2d_exception_2d_to_2d_string ___GLO(4,___G_write_2d_exception_2d_to_2d_string)
#define ___PRM_write_2d_exception_2d_to_2d_string ___PRM(4,___G_write_2d_exception_2d_to_2d_string)
#define ___GLO_write_2d_to_2d_string ___GLO(5,___G_write_2d_to_2d_string)
#define ___PRM_write_2d_to_2d_string ___PRM(5,___G_write_2d_to_2d_string)
#define ___GLO_display_2d_exception ___GLO(6,___G_display_2d_exception)
#define ___PRM_display_2d_exception ___PRM(6,___G_display_2d_exception)
#define ___GLO_eval ___GLO(7,___G_eval)
#define ___PRM_eval ___PRM(7,___G_eval)
#define ___GLO_read ___GLO(8,___G_read)
#define ___PRM_read ___PRM(8,___G_read)
#define ___GLO_with_2d_exception_2d_catcher ___GLO(9,___G_with_2d_exception_2d_catcher)
#define ___PRM_with_2d_exception_2d_catcher ___PRM(9,___G_with_2d_exception_2d_catcher)
#define ___GLO_with_2d_input_2d_from_2d_string ___GLO(10,___G_with_2d_input_2d_from_2d_string)
#define ___PRM_with_2d_input_2d_from_2d_string ___PRM(10,___G_with_2d_input_2d_from_2d_string)
#define ___GLO_with_2d_output_2d_to_2d_string ___GLO(11,___G_with_2d_output_2d_to_2d_string)
#define ___PRM_with_2d_output_2d_to_2d_string ___PRM(11,___G_with_2d_output_2d_to_2d_string)
#define ___GLO_write ___GLO(12,___G_write)
#define ___PRM_write ___PRM(12,___G_write)

___DEF_SUB_VEC(___X0,5)
               ___VEC1(___REF_SYM(0,___S_mylib))
               ___VEC1(___REF_PRC(1))
               ___VEC1(___REF_FIX(1))
               ___VEC1(___REF_NUL)
               ___VEC1(___REF_FAL)
               ___VEC0

___BEGIN_SUB
 ___DEF_SUB(___X0)
___END_SUB


#define ___C_LBL_eval_string 23

#include "mylib.h"
// char* eval_result = NULL;
extern char* eval_string ___P((char* ___arg1),(___arg1)
char* ___arg1;)
{
#define ___NARGS 1
___BEGIN_SFUN(___MLBL(___C_LBL_eval_string),char* ___result)
___BEGIN_SFUN_ARG(1,___ARG1)
___BEGIN_SFUN_CHARSTRING_TO_SCMOBJ(___arg1,___ARG1,1)
___BEGIN_SFUN_BODY
___SFUN_ARG(1,___ARG1)
___SFUN_CALL
___BEGIN_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___SFUN_SET_RESULT
___END_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___END_SFUN_BODY
___END_SFUN_CHARSTRING_TO_SCMOBJ(___arg1,___ARG1,1)
___END_SFUN_ARG(1)
___SFUN_ERROR
___BEGIN_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___SFUN_SET_RESULT
___END_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___END_SFUN
return ___result;
#undef ___NARGS
}


#undef ___MD_ALL
#define ___MD_ALL ___D_HEAP ___D_FP ___D_R0 ___D_R1 ___D_R2 ___D_R4
#undef ___MR_ALL
#define ___MR_ALL ___R_HEAP ___R_FP ___R_R0 ___R_R1 ___R_R2 ___R_R4
#undef ___MW_ALL
#define ___MW_ALL ___W_HEAP ___W_FP ___W_R0 ___W_R1 ___W_R2 ___W_R4
___BEGIN_M_COD
___BEGIN_M_HLBL
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0__20_mylib)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_catch_2d_all_2d_errors)
___DEF_M_HLBL(___L1_catch_2d_all_2d_errors)
___DEF_M_HLBL(___L2_catch_2d_all_2d_errors)
___DEF_M_HLBL(___L3_catch_2d_all_2d_errors)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_write_2d_exception_2d_to_2d_string)
___DEF_M_HLBL(___L1_write_2d_exception_2d_to_2d_string)
___DEF_M_HLBL(___L2_write_2d_exception_2d_to_2d_string)
___DEF_M_HLBL(___L3_write_2d_exception_2d_to_2d_string)
___DEF_M_HLBL(___L4_write_2d_exception_2d_to_2d_string)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_write_2d_to_2d_string)
___DEF_M_HLBL(___L1_write_2d_to_2d_string)
___DEF_M_HLBL(___L2_write_2d_to_2d_string)
___DEF_M_HLBL(___L3_write_2d_to_2d_string)
___DEF_M_HLBL(___L4_write_2d_to_2d_string)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_read_2d_from_2d_string)
___DEF_M_HLBL(___L1_read_2d_from_2d_string)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_eval_2d_string)
___DEF_M_HLBL(___L1_eval_2d_string)
___DEF_M_HLBL(___L2_eval_2d_string)
___DEF_M_HLBL(___L3_eval_2d_string)
___DEF_M_HLBL(___L4_eval_2d_string)
___DEF_M_HLBL(___L5_eval_2d_string)
___DEF_M_HLBL(___L6_eval_2d_string)
___DEF_M_HLBL(___L7_eval_2d_string)
___END_M_HLBL

___BEGIN_M_SW

#undef ___PH_PROC
#define ___PH_PROC ___H__20_mylib
#undef ___PH_LBL0
#define ___PH_LBL0 1
#undef ___PD_ALL
#define ___PD_ALL ___D_R0 ___D_R1
#undef ___PR_ALL
#define ___PR_ALL ___R_R0 ___R_R1
#undef ___PW_ALL
#define ___PW_ALL ___W_R1
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0__20_mylib)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0__20_mylib)
   ___IF_NARGS_EQ(0,___NOTHING)
   ___WRONG_NARGS(0,0,0,0)
___DEF_GLBL(___L__20_mylib)
   ___SET_GLO(1,___G_catch_2d_all_2d_errors,___PRC(3))
   ___SET_GLO(4,___G_write_2d_exception_2d_to_2d_string,___PRC(8))
   ___SET_GLO(5,___G_write_2d_to_2d_string,___PRC(14))
   ___SET_GLO(3,___G_read_2d_from_2d_string,___PRC(20))
   ___SET_GLO(2,___G_eval_2d_string,___PRC(23))
   ___SET_R1(___VOID)
   ___JUMPPRM(___NOTHING,___R0)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_catch_2d_all_2d_errors
#undef ___PH_LBL0
#define ___PH_LBL0 3
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R1 ___D_R2 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R1 ___R_R2 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_FP ___W_R1 ___W_R2 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_catch_2d_all_2d_errors)
___DEF_P_HLBL(___L1_catch_2d_all_2d_errors)
___DEF_P_HLBL(___L2_catch_2d_all_2d_errors)
___DEF_P_HLBL(___L3_catch_2d_all_2d_errors)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_catch_2d_all_2d_errors)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_catch_2d_all_2d_errors)
   ___SET_STK(1,___R1)
   ___SET_R1(___LBL(2))
   ___SET_R2(___STK(1))
   ___ADJFP(1)
   ___POLL(1)
___DEF_SLBL(1,___L1_catch_2d_all_2d_errors)
   ___ADJFP(-1)
   ___JUMPGLOSAFE(___SET_NARGS(2),9,___G_with_2d_exception_2d_catcher)
___DEF_SLBL(2,___L2_catch_2d_all_2d_errors)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(2,1,0,0)
   ___POLL(3)
___DEF_SLBL(3,___L3_catch_2d_all_2d_errors)
   ___JUMPGLOSAFE(___SET_NARGS(1),4,___G_write_2d_exception_2d_to_2d_string)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_write_2d_exception_2d_to_2d_string
#undef ___PH_LBL0
#define ___PH_LBL0 8
#undef ___PD_ALL
#define ___PD_ALL ___D_HEAP ___D_FP ___D_R1 ___D_R2 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_HEAP ___R_FP ___R_R1 ___R_R2 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_HEAP ___W_FP ___W_R1 ___W_R2 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_write_2d_exception_2d_to_2d_string)
___DEF_P_HLBL(___L1_write_2d_exception_2d_to_2d_string)
___DEF_P_HLBL(___L2_write_2d_exception_2d_to_2d_string)
___DEF_P_HLBL(___L3_write_2d_exception_2d_to_2d_string)
___DEF_P_HLBL(___L4_write_2d_exception_2d_to_2d_string)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_write_2d_exception_2d_to_2d_string)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_write_2d_exception_2d_to_2d_string)
   ___SET_STK(1,___ALLOC_CLO(1))
   ___BEGIN_SETUP_CLO(1,___STK(1),3)
   ___ADD_CLO_ELEM(0,___R1)
   ___END_SETUP_CLO(1)
   ___SET_R2(___STK(1))
   ___SET_R1(___NUL)
   ___ADJFP(1)
   ___CHECK_HEAP(1,4096)
___DEF_SLBL(1,___L1_write_2d_exception_2d_to_2d_string)
   ___POLL(2)
___DEF_SLBL(2,___L2_write_2d_exception_2d_to_2d_string)
   ___ADJFP(-1)
   ___JUMPGLOSAFE(___SET_NARGS(2),11,___G_with_2d_output_2d_to_2d_string)
___DEF_SLBL(3,___L3_write_2d_exception_2d_to_2d_string)
   ___IF_NARGS_EQ(0,___NOTHING)
   ___WRONG_NARGS(3,0,0,0)
   ___SET_R1(___CLO(___R4,1))
   ___POLL(4)
___DEF_SLBL(4,___L4_write_2d_exception_2d_to_2d_string)
   ___JUMPGLOSAFE(___SET_NARGS(1),6,___G_display_2d_exception)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_write_2d_to_2d_string
#undef ___PH_LBL0
#define ___PH_LBL0 14
#undef ___PD_ALL
#define ___PD_ALL ___D_HEAP ___D_FP ___D_R1 ___D_R2 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_HEAP ___R_FP ___R_R1 ___R_R2 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_HEAP ___W_FP ___W_R1 ___W_R2 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_write_2d_to_2d_string)
___DEF_P_HLBL(___L1_write_2d_to_2d_string)
___DEF_P_HLBL(___L2_write_2d_to_2d_string)
___DEF_P_HLBL(___L3_write_2d_to_2d_string)
___DEF_P_HLBL(___L4_write_2d_to_2d_string)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_write_2d_to_2d_string)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_write_2d_to_2d_string)
   ___SET_STK(1,___ALLOC_CLO(1))
   ___BEGIN_SETUP_CLO(1,___STK(1),3)
   ___ADD_CLO_ELEM(0,___R1)
   ___END_SETUP_CLO(1)
   ___SET_R2(___STK(1))
   ___SET_R1(___NUL)
   ___ADJFP(1)
   ___CHECK_HEAP(1,4096)
___DEF_SLBL(1,___L1_write_2d_to_2d_string)
   ___POLL(2)
___DEF_SLBL(2,___L2_write_2d_to_2d_string)
   ___ADJFP(-1)
   ___JUMPGLOSAFE(___SET_NARGS(2),11,___G_with_2d_output_2d_to_2d_string)
___DEF_SLBL(3,___L3_write_2d_to_2d_string)
   ___IF_NARGS_EQ(0,___NOTHING)
   ___WRONG_NARGS(3,0,0,0)
   ___SET_R1(___CLO(___R4,1))
   ___POLL(4)
___DEF_SLBL(4,___L4_write_2d_to_2d_string)
   ___JUMPGLOSAFE(___SET_NARGS(1),12,___G_write)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_read_2d_from_2d_string
#undef ___PH_LBL0
#define ___PH_LBL0 20
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R2 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R2 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_R2 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_read_2d_from_2d_string)
___DEF_P_HLBL(___L1_read_2d_from_2d_string)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_read_2d_from_2d_string)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_read_2d_from_2d_string)
   ___SET_R2(___GLO_read)
   ___POLL(1)
___DEF_SLBL(1,___L1_read_2d_from_2d_string)
   ___JUMPGLOSAFE(___SET_NARGS(2),10,___G_with_2d_input_2d_from_2d_string)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_eval_2d_string
#undef ___PH_LBL0
#define ___PH_LBL0 23
#undef ___PD_ALL
#define ___PD_ALL ___D_HEAP ___D_FP ___D_R0 ___D_R1 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_HEAP ___R_FP ___R_R0 ___R_R1 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_HEAP ___W_FP ___W_R0 ___W_R1 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_eval_2d_string)
___DEF_P_HLBL(___L1_eval_2d_string)
___DEF_P_HLBL(___L2_eval_2d_string)
___DEF_P_HLBL(___L3_eval_2d_string)
___DEF_P_HLBL(___L4_eval_2d_string)
___DEF_P_HLBL(___L5_eval_2d_string)
___DEF_P_HLBL(___L6_eval_2d_string)
___DEF_P_HLBL(___L7_eval_2d_string)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_eval_2d_string)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_eval_2d_string)
   ___SET_STK(1,___ALLOC_CLO(1))
   ___BEGIN_SETUP_CLO(1,___STK(1),3)
   ___ADD_CLO_ELEM(0,___R1)
   ___END_SETUP_CLO(1)
   ___SET_R1(___STK(1))
   ___ADJFP(1)
   ___CHECK_HEAP(1,4096)
___DEF_SLBL(1,___L1_eval_2d_string)
   ___POLL(2)
___DEF_SLBL(2,___L2_eval_2d_string)
   ___ADJFP(-1)
   ___JUMPGLOSAFE(___SET_NARGS(1),1,___G_catch_2d_all_2d_errors)
___DEF_SLBL(3,___L3_eval_2d_string)
   ___IF_NARGS_EQ(0,___NOTHING)
   ___WRONG_NARGS(3,0,0,0)
   ___SET_STK(1,___R0)
   ___SET_R1(___CLO(___R4,1))
   ___SET_R0(___LBL(5))
   ___ADJFP(4)
   ___POLL(4)
___DEF_SLBL(4,___L4_eval_2d_string)
   ___JUMPGLOSAFE(___SET_NARGS(1),3,___G_read_2d_from_2d_string)
___DEF_SLBL(5,___L5_eval_2d_string)
   ___SET_R0(___LBL(6))
   ___JUMPGLOSAFE(___SET_NARGS(1),7,___G_eval)
___DEF_SLBL(6,___L6_eval_2d_string)
   ___SET_R0(___STK(-3))
   ___POLL(7)
___DEF_SLBL(7,___L7_eval_2d_string)
   ___ADJFP(-4)
   ___JUMPGLOSAFE(___SET_NARGS(1),5,___G_write_2d_to_2d_string)
___END_P_SW
___END_P_COD

___END_M_SW
___END_M_COD

___BEGIN_LBL
 ___DEF_LBL_INTRO(___H__20_mylib," mylib",___REF_FAL,1,0)
,___DEF_LBL_PROC(___H__20_mylib,0,-1)
,___DEF_LBL_INTRO(___H_catch_2d_all_2d_errors,0,___REF_FAL,4,0)
,___DEF_LBL_PROC(___H_catch_2d_all_2d_errors,1,-1)
,___DEF_LBL_RET(___H_catch_2d_all_2d_errors,___IFD(___RETI,1,4,0x3f0L))
,___DEF_LBL_PROC(___H_catch_2d_all_2d_errors,1,-1)
,___DEF_LBL_RET(___H_catch_2d_all_2d_errors,___IFD(___RETI,0,0,0x3fL))
,___DEF_LBL_INTRO(___H_write_2d_exception_2d_to_2d_string,0,___REF_FAL,5,0)
,___DEF_LBL_PROC(___H_write_2d_exception_2d_to_2d_string,1,-1)
,___DEF_LBL_RET(___H_write_2d_exception_2d_to_2d_string,___IFD(___RETI,1,4,0x3f0L))
,___DEF_LBL_RET(___H_write_2d_exception_2d_to_2d_string,___IFD(___RETI,1,4,0x3f0L))
,___DEF_LBL_PROC(___H_write_2d_exception_2d_to_2d_string,0,1)
,___DEF_LBL_RET(___H_write_2d_exception_2d_to_2d_string,___IFD(___RETI,0,0,0x3fL))
,___DEF_LBL_INTRO(___H_write_2d_to_2d_string,0,___REF_FAL,5,0)
,___DEF_LBL_PROC(___H_write_2d_to_2d_string,1,-1)
,___DEF_LBL_RET(___H_write_2d_to_2d_string,___IFD(___RETI,1,4,0x3f0L))
,___DEF_LBL_RET(___H_write_2d_to_2d_string,___IFD(___RETI,1,4,0x3f0L))
,___DEF_LBL_PROC(___H_write_2d_to_2d_string,0,1)
,___DEF_LBL_RET(___H_write_2d_to_2d_string,___IFD(___RETI,0,0,0x3fL))
,___DEF_LBL_INTRO(___H_read_2d_from_2d_string,0,___REF_FAL,2,0)
,___DEF_LBL_PROC(___H_read_2d_from_2d_string,1,-1)
,___DEF_LBL_RET(___H_read_2d_from_2d_string,___IFD(___RETI,0,0,0x3fL))
,___DEF_LBL_INTRO(___H_eval_2d_string,0,___REF_FAL,8,eval_string)
,___DEF_LBL_PROC(___H_eval_2d_string,1,-1)
,___DEF_LBL_RET(___H_eval_2d_string,___IFD(___RETI,1,4,0x3f0L))
,___DEF_LBL_RET(___H_eval_2d_string,___IFD(___RETI,1,4,0x3f0L))
,___DEF_LBL_PROC(___H_eval_2d_string,0,1)
,___DEF_LBL_RET(___H_eval_2d_string,___IFD(___RETI,4,0,0x3f1L))
,___DEF_LBL_RET(___H_eval_2d_string,___IFD(___RETN,1,0,0x1L))
,___DEF_LBL_RET(___H_eval_2d_string,___IFD(___RETN,1,0,0x1L))
,___DEF_LBL_RET(___H_eval_2d_string,___IFD(___RETI,4,4,0x3f0L))
___END_LBL

___BEGIN_MOD_PRM
___DEF_MOD_PRM(0,___G__20_mylib,1)
___END_MOD_PRM

___BEGIN_MOD_C_INIT
___END_MOD_C_INIT

___BEGIN_MOD_GLO
___DEF_MOD_GLO(0,___G__20_mylib,1)
___END_MOD_GLO

___BEGIN_MOD_SYM_KEY
___DEF_MOD_SYM(0,___S_mylib,"mylib")
___END_MOD_SYM_KEY

#endif
