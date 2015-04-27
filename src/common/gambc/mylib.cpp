#ifdef ___LINKER_INFO
; File: "mylib.c", produced by Gambit-C v4.7.5
(
407005
" mylib"
((" mylib"))
(
"jazz.language.runtime.functional:thread-process"
"mylib"
)
(
"timeout"
)
(
" mylib"
" mylib#0"
" mylib#1"
"catch-all-errors"
"read-from-string"
"write-exception-to-string"
"write-to-string"
)
(
"call-js"
"eval-string"
"eval-string-catch"
"eval-string-int"
"eval-string-string"
"eval-string-void"
"heartbeat"
"register-export"
)
(
"##global-var-ref"
"##global-var?"
"##thread-heartbeat!"
"##unbound?"
"display-exception"
"eval"
"not"
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
#define ___VERSION 407005
#define ___MODULE_NAME " mylib"
#define ___LINKER_ID ____20_mylib
#define ___MH_PROC ___H__20_mylib
#define ___SCRIPT_LINE 0
#define ___SYMCOUNT 2
#define ___KEYCOUNT 1
#define ___GLOCOUNT 27
#define ___SUPCOUNT 15
#define ___SUBCOUNT 1
#define ___LBLCOUNT 68
#define ___MODDESCR ___REF_SUB(0)
#include "gambit.h"

___NEED_SYM(___S_jazz_2e_language_2e_runtime_2e_functional_3a_thread_2d_process)
___NEED_SYM(___S_mylib)

___NEED_KEY(___K_timeout)

___NEED_GLO(___G__20_mylib)
___NEED_GLO(___G__20_mylib_23_0)
___NEED_GLO(___G__20_mylib_23_1)
___NEED_GLO(___G__23__23_global_2d_var_2d_ref)
___NEED_GLO(___G__23__23_global_2d_var_3f_)
___NEED_GLO(___G__23__23_thread_2d_heartbeat_21_)
___NEED_GLO(___G__23__23_unbound_3f_)
___NEED_GLO(___G_call_2d_js)
___NEED_GLO(___G_catch_2d_all_2d_errors)
___NEED_GLO(___G_display_2d_exception)
___NEED_GLO(___G_eval)
___NEED_GLO(___G_eval_2d_string)
___NEED_GLO(___G_eval_2d_string_2d_catch)
___NEED_GLO(___G_eval_2d_string_2d_int)
___NEED_GLO(___G_eval_2d_string_2d_string)
___NEED_GLO(___G_eval_2d_string_2d_void)
___NEED_GLO(___G_heartbeat)
___NEED_GLO(___G_not)
___NEED_GLO(___G_read)
___NEED_GLO(___G_read_2d_from_2d_string)
___NEED_GLO(___G_register_2d_export)
___NEED_GLO(___G_with_2d_exception_2d_catcher)
___NEED_GLO(___G_with_2d_input_2d_from_2d_string)
___NEED_GLO(___G_with_2d_output_2d_to_2d_string)
___NEED_GLO(___G_write)
___NEED_GLO(___G_write_2d_exception_2d_to_2d_string)
___NEED_GLO(___G_write_2d_to_2d_string)

___BEGIN_SYM
___DEF_SYM(0,___S_jazz_2e_language_2e_runtime_2e_functional_3a_thread_2d_process,"jazz.language.runtime.functional:thread-process")

___DEF_SYM(1,___S_mylib,"mylib")
___END_SYM

#define ___SYM_jazz_2e_language_2e_runtime_2e_functional_3a_thread_2d_process ___SYM(0,___S_jazz_2e_language_2e_runtime_2e_functional_3a_thread_2d_process)
#define ___SYM_mylib ___SYM(1,___S_mylib)

___BEGIN_KEY
___DEF_KEY(0,___K_timeout,"timeout")
___END_KEY

#define ___KEY_timeout ___KEY(0,___K_timeout)

___BEGIN_GLO
___DEF_GLO(0," mylib")
___DEF_GLO(1," mylib#0")
___DEF_GLO(2," mylib#1")
___DEF_GLO(3,"call-js")
___DEF_GLO(4,"catch-all-errors")
___DEF_GLO(5,"eval-string")
___DEF_GLO(6,"eval-string-catch")
___DEF_GLO(7,"eval-string-int")
___DEF_GLO(8,"eval-string-string")
___DEF_GLO(9,"eval-string-void")
___DEF_GLO(10,"heartbeat")
___DEF_GLO(11,"read-from-string")
___DEF_GLO(12,"register-export")
___DEF_GLO(13,"write-exception-to-string")
___DEF_GLO(14,"write-to-string")
___DEF_GLO(15,"##global-var-ref")
___DEF_GLO(16,"##global-var?")
___DEF_GLO(17,"##thread-heartbeat!")
___DEF_GLO(18,"##unbound?")
___DEF_GLO(19,"display-exception")
___DEF_GLO(20,"eval")
___DEF_GLO(21,"not")
___DEF_GLO(22,"read")
___DEF_GLO(23,"with-exception-catcher")
___DEF_GLO(24,"with-input-from-string")
___DEF_GLO(25,"with-output-to-string")
___DEF_GLO(26,"write")
___END_GLO

#define ___GLO__20_mylib ___GLO(0,___G__20_mylib)
#define ___PRM__20_mylib ___PRM(0,___G__20_mylib)
#define ___GLO__20_mylib_23_0 ___GLO(1,___G__20_mylib_23_0)
#define ___PRM__20_mylib_23_0 ___PRM(1,___G__20_mylib_23_0)
#define ___GLO__20_mylib_23_1 ___GLO(2,___G__20_mylib_23_1)
#define ___PRM__20_mylib_23_1 ___PRM(2,___G__20_mylib_23_1)
#define ___GLO_call_2d_js ___GLO(3,___G_call_2d_js)
#define ___PRM_call_2d_js ___PRM(3,___G_call_2d_js)
#define ___GLO_catch_2d_all_2d_errors ___GLO(4,___G_catch_2d_all_2d_errors)
#define ___PRM_catch_2d_all_2d_errors ___PRM(4,___G_catch_2d_all_2d_errors)
#define ___GLO_eval_2d_string ___GLO(5,___G_eval_2d_string)
#define ___PRM_eval_2d_string ___PRM(5,___G_eval_2d_string)
#define ___GLO_eval_2d_string_2d_catch ___GLO(6,___G_eval_2d_string_2d_catch)
#define ___PRM_eval_2d_string_2d_catch ___PRM(6,___G_eval_2d_string_2d_catch)
#define ___GLO_eval_2d_string_2d_int ___GLO(7,___G_eval_2d_string_2d_int)
#define ___PRM_eval_2d_string_2d_int ___PRM(7,___G_eval_2d_string_2d_int)
#define ___GLO_eval_2d_string_2d_string ___GLO(8,___G_eval_2d_string_2d_string)
#define ___PRM_eval_2d_string_2d_string ___PRM(8,___G_eval_2d_string_2d_string)
#define ___GLO_eval_2d_string_2d_void ___GLO(9,___G_eval_2d_string_2d_void)
#define ___PRM_eval_2d_string_2d_void ___PRM(9,___G_eval_2d_string_2d_void)
#define ___GLO_heartbeat ___GLO(10,___G_heartbeat)
#define ___PRM_heartbeat ___PRM(10,___G_heartbeat)
#define ___GLO_read_2d_from_2d_string ___GLO(11,___G_read_2d_from_2d_string)
#define ___PRM_read_2d_from_2d_string ___PRM(11,___G_read_2d_from_2d_string)
#define ___GLO_register_2d_export ___GLO(12,___G_register_2d_export)
#define ___PRM_register_2d_export ___PRM(12,___G_register_2d_export)
#define ___GLO_write_2d_exception_2d_to_2d_string ___GLO(13,___G_write_2d_exception_2d_to_2d_string)
#define ___PRM_write_2d_exception_2d_to_2d_string ___PRM(13,___G_write_2d_exception_2d_to_2d_string)
#define ___GLO_write_2d_to_2d_string ___GLO(14,___G_write_2d_to_2d_string)
#define ___PRM_write_2d_to_2d_string ___PRM(14,___G_write_2d_to_2d_string)
#define ___GLO__23__23_global_2d_var_2d_ref ___GLO(15,___G__23__23_global_2d_var_2d_ref)
#define ___PRM__23__23_global_2d_var_2d_ref ___PRM(15,___G__23__23_global_2d_var_2d_ref)
#define ___GLO__23__23_global_2d_var_3f_ ___GLO(16,___G__23__23_global_2d_var_3f_)
#define ___PRM__23__23_global_2d_var_3f_ ___PRM(16,___G__23__23_global_2d_var_3f_)
#define ___GLO__23__23_thread_2d_heartbeat_21_ ___GLO(17,___G__23__23_thread_2d_heartbeat_21_)
#define ___PRM__23__23_thread_2d_heartbeat_21_ ___PRM(17,___G__23__23_thread_2d_heartbeat_21_)
#define ___GLO__23__23_unbound_3f_ ___GLO(18,___G__23__23_unbound_3f_)
#define ___PRM__23__23_unbound_3f_ ___PRM(18,___G__23__23_unbound_3f_)
#define ___GLO_display_2d_exception ___GLO(19,___G_display_2d_exception)
#define ___PRM_display_2d_exception ___PRM(19,___G_display_2d_exception)
#define ___GLO_eval ___GLO(20,___G_eval)
#define ___PRM_eval ___PRM(20,___G_eval)
#define ___GLO_not ___GLO(21,___G_not)
#define ___PRM_not ___PRM(21,___G_not)
#define ___GLO_read ___GLO(22,___G_read)
#define ___PRM_read ___PRM(22,___G_read)
#define ___GLO_with_2d_exception_2d_catcher ___GLO(23,___G_with_2d_exception_2d_catcher)
#define ___PRM_with_2d_exception_2d_catcher ___PRM(23,___G_with_2d_exception_2d_catcher)
#define ___GLO_with_2d_input_2d_from_2d_string ___GLO(24,___G_with_2d_input_2d_from_2d_string)
#define ___PRM_with_2d_input_2d_from_2d_string ___PRM(24,___G_with_2d_input_2d_from_2d_string)
#define ___GLO_with_2d_output_2d_to_2d_string ___GLO(25,___G_with_2d_output_2d_to_2d_string)
#define ___PRM_with_2d_output_2d_to_2d_string ___PRM(25,___G_with_2d_output_2d_to_2d_string)
#define ___GLO_write ___GLO(26,___G_write)
#define ___PRM_write ___PRM(26,___G_write)

___DEF_SUB_VEC(___X0,5)
               ___VEC1(___REF_SYM(1,___S_mylib))
               ___VEC1(___REF_PRC(1))
               ___VEC1(___REF_FIX(1))
               ___VEC1(___REF_NUL)
               ___VEC1(___REF_FAL)
               ___VEC0

___BEGIN_SUB
 ___DEF_SUB(___X0)
___END_SUB


#define ___C_LBL_gambit_eval_string_void 29
#define ___C_LBL_gambit_eval_string_int 34
#define ___C_LBL_gambit_eval_string_string 39
#define ___C_LBL_gambit_eval_string 44
#define ___C_LBL_gambit_eval_string_catch 50
#define ___C_LBL_gambit_heartbeat 59

#include "application.h"
#include "mylib.h"
extern void gambit_eval_string_void ___P((char* ___arg1),(___arg1)
char* ___arg1;)
{
#define ___NARGS 1
___BEGIN_SFUN_VOID(___MLBL(___C_LBL_gambit_eval_string_void))
___BEGIN_SFUN_ARG(1,___ARG1)
___BEGIN_SFUN_CHARSTRING_TO_SCMOBJ(___arg1,___ARG1,1)
___BEGIN_SFUN_BODY
___SFUN_ARG(1,___ARG1)
___SFUN_CALL_VOID
___SFUN_SET_RESULT_VOID
___END_SFUN_BODY
___END_SFUN_CHARSTRING_TO_SCMOBJ(___arg1,___ARG1,1)
___END_SFUN_ARG(1)
___SFUN_ERROR_VOID
___SFUN_SET_RESULT_VOID
___END_SFUN_VOID
#undef ___NARGS
}

extern int gambit_eval_string_int ___P((char* ___arg1),(___arg1)
char* ___arg1;)
{
#define ___NARGS 1
___BEGIN_SFUN(___MLBL(___C_LBL_gambit_eval_string_int),int ___result)
___BEGIN_SFUN_ARG(1,___ARG1)
___BEGIN_SFUN_CHARSTRING_TO_SCMOBJ(___arg1,___ARG1,1)
___BEGIN_SFUN_BODY
___SFUN_ARG(1,___ARG1)
___SFUN_CALL
___BEGIN_SFUN_SCMOBJ_TO_INT(___SFUN_RESULT,___result)
___SFUN_SET_RESULT
___END_SFUN_SCMOBJ_TO_INT(___SFUN_RESULT,___result)
___END_SFUN_BODY
___END_SFUN_CHARSTRING_TO_SCMOBJ(___arg1,___ARG1,1)
___END_SFUN_ARG(1)
___SFUN_ERROR
___BEGIN_SFUN_SCMOBJ_TO_INT(___SFUN_RESULT,___result)
___SFUN_SET_RESULT
___END_SFUN_SCMOBJ_TO_INT(___SFUN_RESULT,___result)
___END_SFUN
return ___result;
#undef ___NARGS
}

extern char* gambit_eval_string_string ___P((char* ___arg1),(___arg1)
char* ___arg1;)
{
#define ___NARGS 1
___BEGIN_SFUN(___MLBL(___C_LBL_gambit_eval_string_string),char* ___result)
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

extern char* gambit_eval_string ___P((char* ___arg1),(___arg1)
char* ___arg1;)
{
#define ___NARGS 1
___BEGIN_SFUN(___MLBL(___C_LBL_gambit_eval_string),char* ___result)
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

extern char* gambit_eval_string_catch ___P((char* ___arg1),(___arg1)
char* ___arg1;)
{
#define ___NARGS 1
___BEGIN_SFUN(___MLBL(___C_LBL_gambit_eval_string_catch),char* ___result)
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

extern void gambit_heartbeat ___PVOID
{
#define ___NARGS 0
___BEGIN_SFUN_VOID(___MLBL(___C_LBL_gambit_heartbeat))
___BEGIN_SFUN_BODY
___SFUN_CALL_VOID
___SFUN_SET_RESULT_VOID
___END_SFUN_BODY
___SFUN_ERROR_VOID
___SFUN_SET_RESULT_VOID
___END_SFUN_VOID
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
___DEF_M_HLBL(___L0__20_mylib_23_0)
___DEF_M_HLBL(___L1__20_mylib_23_0)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0__20_mylib_23_1)
___DEF_M_HLBL(___L1__20_mylib_23_1)
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
___DEF_M_HLBL(___L0_eval_2d_string_2d_void)
___DEF_M_HLBL(___L1_eval_2d_string_2d_void)
___DEF_M_HLBL(___L2_eval_2d_string_2d_void)
___DEF_M_HLBL(___L3_eval_2d_string_2d_void)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_eval_2d_string_2d_int)
___DEF_M_HLBL(___L1_eval_2d_string_2d_int)
___DEF_M_HLBL(___L2_eval_2d_string_2d_int)
___DEF_M_HLBL(___L3_eval_2d_string_2d_int)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_eval_2d_string_2d_string)
___DEF_M_HLBL(___L1_eval_2d_string_2d_string)
___DEF_M_HLBL(___L2_eval_2d_string_2d_string)
___DEF_M_HLBL(___L3_eval_2d_string_2d_string)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_eval_2d_string)
___DEF_M_HLBL(___L1_eval_2d_string)
___DEF_M_HLBL(___L2_eval_2d_string)
___DEF_M_HLBL(___L3_eval_2d_string)
___DEF_M_HLBL(___L4_eval_2d_string)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_eval_2d_string_2d_catch)
___DEF_M_HLBL(___L1_eval_2d_string_2d_catch)
___DEF_M_HLBL(___L2_eval_2d_string_2d_catch)
___DEF_M_HLBL(___L3_eval_2d_string_2d_catch)
___DEF_M_HLBL(___L4_eval_2d_string_2d_catch)
___DEF_M_HLBL(___L5_eval_2d_string_2d_catch)
___DEF_M_HLBL(___L6_eval_2d_string_2d_catch)
___DEF_M_HLBL(___L7_eval_2d_string_2d_catch)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_heartbeat)
___DEF_M_HLBL(___L1_heartbeat)
___DEF_M_HLBL(___L2_heartbeat)
___DEF_M_HLBL(___L3_heartbeat)
___DEF_M_HLBL(___L4_heartbeat)
___DEF_M_HLBL(___L5_heartbeat)
___DEF_M_HLBL(___L6_heartbeat)
___DEF_M_HLBL(___L7_heartbeat)
___DEF_M_HLBL(___L8_heartbeat)
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
   ___SET_GLO(4,___G_catch_2d_all_2d_errors,___PRC(9))
   ___SET_GLO(13,___G_write_2d_exception_2d_to_2d_string,___PRC(14))
   ___SET_GLO(14,___G_write_2d_to_2d_string,___PRC(20))
   ___SET_GLO(11,___G_read_2d_from_2d_string,___PRC(26))
   ___SET_GLO(9,___G_eval_2d_string_2d_void,___PRC(29))
   ___SET_GLO(7,___G_eval_2d_string_2d_int,___PRC(34))
   ___SET_GLO(8,___G_eval_2d_string_2d_string,___PRC(39))
   ___SET_GLO(5,___G_eval_2d_string,___PRC(44))
   ___SET_GLO(6,___G_eval_2d_string_2d_catch,___PRC(50))
   ___SET_GLO(3,___G_call_2d_js,___PRC(3))
   ___SET_GLO(12,___G_register_2d_export,___PRC(6))
   ___SET_GLO(10,___G_heartbeat,___PRC(59))
   ___SET_R1(___VOID)
   ___JUMPPRM(___NOTHING,___R0)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H__20_mylib_23_0
#undef ___PH_LBL0
#define ___PH_LBL0 3
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R0 ___D_R1
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R0 ___R_R1
#undef ___PW_ALL
#define ___PW_ALL ___W_FP ___W_R0
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0__20_mylib_23_0)
___DEF_P_HLBL(___L1__20_mylib_23_0)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0__20_mylib_23_0)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L__20_mylib_23_0)
   ___SET_STK(1,___R1)
   ___SET_STK(2,___R0)
   ___SET_R0(___LBL(1))
   ___ADJFP(8)
#define ___NARGS 1
___BEGIN_CFUN_VOID
#define ___ARG1 ___CFUN_ARG(1)
___BEGIN_CFUN_ARG(1,char* ___arg1)
___BEGIN_CFUN_SCMOBJ_TO_CHARSTRING(___ARG1,___arg1,1)
___BEGIN_CFUN_BODY_CLEANUP
#undef ___AT_END
call_js(___arg1);
#ifndef ___AT_END
#define ___AT_END
#endif
___CFUN_SET_RESULT_VOID
___END_CFUN_BODY_CLEANUP
___END_CFUN_SCMOBJ_TO_CHARSTRING(___ARG1,___arg1,1)
___END_CFUN_ARG(1)
#undef ___ARG1
___CFUN_ERROR_CLEANUP_VOID
___END_CFUN_VOID
#undef ___NARGS
   ___JUMPPRM(___NOTHING,___R0)
___DEF_SLBL(1,___L1__20_mylib_23_0)
   ___ADJFP(-8)
   ___JUMPPRM(___NOTHING,___STK(2))
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H__20_mylib_23_1
#undef ___PH_LBL0
#define ___PH_LBL0 6
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R0 ___D_R1 ___D_R2
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R0 ___R_R1 ___R_R2
#undef ___PW_ALL
#define ___PW_ALL ___W_FP ___W_R0
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0__20_mylib_23_1)
___DEF_P_HLBL(___L1__20_mylib_23_1)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0__20_mylib_23_1)
   ___IF_NARGS_EQ(2,___NOTHING)
   ___WRONG_NARGS(0,2,0,0)
___DEF_GLBL(___L__20_mylib_23_1)
   ___SET_STK(1,___R1)
   ___SET_STK(2,___R2)
   ___SET_STK(3,___R0)
   ___SET_R0(___LBL(1))
   ___ADJFP(8)
#define ___NARGS 2
___BEGIN_CFUN_VOID
#define ___ARG1 ___CFUN_ARG(1)
___BEGIN_CFUN_ARG(1,char* ___arg1)
___BEGIN_CFUN_SCMOBJ_TO_CHARSTRING(___ARG1,___arg1,1)
#define ___ARG2 ___CFUN_ARG(2)
___BEGIN_CFUN_ARG(2,int ___arg2)
___BEGIN_CFUN_SCMOBJ_TO_INT(___ARG2,___arg2,2)
___BEGIN_CFUN_BODY_CLEANUP
#undef ___AT_END
register_export(___arg1, ___arg2);
#ifndef ___AT_END
#define ___AT_END
#endif
___CFUN_SET_RESULT_VOID
___END_CFUN_BODY_CLEANUP
___END_CFUN_SCMOBJ_TO_INT(___ARG2,___arg2,2)
___END_CFUN_ARG(2)
#undef ___ARG2
___END_CFUN_SCMOBJ_TO_CHARSTRING(___ARG1,___arg1,1)
___END_CFUN_ARG(1)
#undef ___ARG1
___CFUN_ERROR_CLEANUP_VOID
___END_CFUN_VOID
#undef ___NARGS
   ___JUMPPRM(___NOTHING,___R0)
___DEF_SLBL(1,___L1__20_mylib_23_1)
   ___ADJFP(-8)
   ___JUMPPRM(___NOTHING,___STK(3))
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_catch_2d_all_2d_errors
#undef ___PH_LBL0
#define ___PH_LBL0 9
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
   ___JUMPGLOSAFE(___SET_NARGS(2),23,___G_with_2d_exception_2d_catcher)
___DEF_SLBL(2,___L2_catch_2d_all_2d_errors)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(2,1,0,0)
   ___POLL(3)
___DEF_SLBL(3,___L3_catch_2d_all_2d_errors)
   ___JUMPGLOSAFE(___SET_NARGS(1),13,___G_write_2d_exception_2d_to_2d_string)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_write_2d_exception_2d_to_2d_string
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
   ___JUMPGLOSAFE(___SET_NARGS(2),25,___G_with_2d_output_2d_to_2d_string)
___DEF_SLBL(3,___L3_write_2d_exception_2d_to_2d_string)
   ___IF_NARGS_EQ(0,___NOTHING)
   ___WRONG_NARGS(3,0,0,0)
   ___SET_R1(___CLO(___R4,1))
   ___POLL(4)
___DEF_SLBL(4,___L4_write_2d_exception_2d_to_2d_string)
   ___JUMPGLOSAFE(___SET_NARGS(1),19,___G_display_2d_exception)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_write_2d_to_2d_string
#undef ___PH_LBL0
#define ___PH_LBL0 20
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
   ___JUMPGLOSAFE(___SET_NARGS(2),25,___G_with_2d_output_2d_to_2d_string)
___DEF_SLBL(3,___L3_write_2d_to_2d_string)
   ___IF_NARGS_EQ(0,___NOTHING)
   ___WRONG_NARGS(3,0,0,0)
   ___SET_R1(___CLO(___R4,1))
   ___POLL(4)
___DEF_SLBL(4,___L4_write_2d_to_2d_string)
   ___JUMPGLOSAFE(___SET_NARGS(1),26,___G_write)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_read_2d_from_2d_string
#undef ___PH_LBL0
#define ___PH_LBL0 26
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
   ___JUMPGLOSAFE(___SET_NARGS(2),24,___G_with_2d_input_2d_from_2d_string)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_eval_2d_string_2d_void
#undef ___PH_LBL0
#define ___PH_LBL0 29
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R0 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R0 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_FP ___W_R0 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_eval_2d_string_2d_void)
___DEF_P_HLBL(___L1_eval_2d_string_2d_void)
___DEF_P_HLBL(___L2_eval_2d_string_2d_void)
___DEF_P_HLBL(___L3_eval_2d_string_2d_void)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_eval_2d_string_2d_void)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_eval_2d_string_2d_void)
   ___SET_STK(1,___R0)
   ___SET_R0(___LBL(2))
   ___ADJFP(4)
   ___POLL(1)
___DEF_SLBL(1,___L1_eval_2d_string_2d_void)
   ___JUMPGLOSAFE(___SET_NARGS(1),11,___G_read_2d_from_2d_string)
___DEF_SLBL(2,___L2_eval_2d_string_2d_void)
   ___SET_R0(___STK(-3))
   ___POLL(3)
___DEF_SLBL(3,___L3_eval_2d_string_2d_void)
   ___ADJFP(-4)
   ___JUMPGLOSAFE(___SET_NARGS(1),20,___G_eval)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_eval_2d_string_2d_int
#undef ___PH_LBL0
#define ___PH_LBL0 34
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R0 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R0 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_FP ___W_R0 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_eval_2d_string_2d_int)
___DEF_P_HLBL(___L1_eval_2d_string_2d_int)
___DEF_P_HLBL(___L2_eval_2d_string_2d_int)
___DEF_P_HLBL(___L3_eval_2d_string_2d_int)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_eval_2d_string_2d_int)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_eval_2d_string_2d_int)
   ___SET_STK(1,___R0)
   ___SET_R0(___LBL(2))
   ___ADJFP(4)
   ___POLL(1)
___DEF_SLBL(1,___L1_eval_2d_string_2d_int)
   ___JUMPGLOSAFE(___SET_NARGS(1),11,___G_read_2d_from_2d_string)
___DEF_SLBL(2,___L2_eval_2d_string_2d_int)
   ___SET_R0(___STK(-3))
   ___POLL(3)
___DEF_SLBL(3,___L3_eval_2d_string_2d_int)
   ___ADJFP(-4)
   ___JUMPGLOSAFE(___SET_NARGS(1),20,___G_eval)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_eval_2d_string_2d_string
#undef ___PH_LBL0
#define ___PH_LBL0 39
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R0 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R0 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_FP ___W_R0 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_eval_2d_string_2d_string)
___DEF_P_HLBL(___L1_eval_2d_string_2d_string)
___DEF_P_HLBL(___L2_eval_2d_string_2d_string)
___DEF_P_HLBL(___L3_eval_2d_string_2d_string)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_eval_2d_string_2d_string)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_eval_2d_string_2d_string)
   ___SET_STK(1,___R0)
   ___SET_R0(___LBL(2))
   ___ADJFP(4)
   ___POLL(1)
___DEF_SLBL(1,___L1_eval_2d_string_2d_string)
   ___JUMPGLOSAFE(___SET_NARGS(1),11,___G_read_2d_from_2d_string)
___DEF_SLBL(2,___L2_eval_2d_string_2d_string)
   ___SET_R0(___STK(-3))
   ___POLL(3)
___DEF_SLBL(3,___L3_eval_2d_string_2d_string)
   ___ADJFP(-4)
   ___JUMPGLOSAFE(___SET_NARGS(1),20,___G_eval)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_eval_2d_string
#undef ___PH_LBL0
#define ___PH_LBL0 44
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R0 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R0 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_FP ___W_R0 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_eval_2d_string)
___DEF_P_HLBL(___L1_eval_2d_string)
___DEF_P_HLBL(___L2_eval_2d_string)
___DEF_P_HLBL(___L3_eval_2d_string)
___DEF_P_HLBL(___L4_eval_2d_string)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_eval_2d_string)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_eval_2d_string)
   ___SET_STK(1,___R0)
   ___SET_R0(___LBL(2))
   ___ADJFP(4)
   ___POLL(1)
___DEF_SLBL(1,___L1_eval_2d_string)
   ___JUMPGLOSAFE(___SET_NARGS(1),11,___G_read_2d_from_2d_string)
___DEF_SLBL(2,___L2_eval_2d_string)
   ___SET_R0(___LBL(3))
   ___JUMPGLOSAFE(___SET_NARGS(1),20,___G_eval)
___DEF_SLBL(3,___L3_eval_2d_string)
   ___SET_R0(___STK(-3))
   ___POLL(4)
___DEF_SLBL(4,___L4_eval_2d_string)
   ___ADJFP(-4)
   ___JUMPGLOSAFE(___SET_NARGS(1),14,___G_write_2d_to_2d_string)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_eval_2d_string_2d_catch
#undef ___PH_LBL0
#define ___PH_LBL0 50
#undef ___PD_ALL
#define ___PD_ALL ___D_HEAP ___D_FP ___D_R0 ___D_R1 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_HEAP ___R_FP ___R_R0 ___R_R1 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_HEAP ___W_FP ___W_R0 ___W_R1 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_eval_2d_string_2d_catch)
___DEF_P_HLBL(___L1_eval_2d_string_2d_catch)
___DEF_P_HLBL(___L2_eval_2d_string_2d_catch)
___DEF_P_HLBL(___L3_eval_2d_string_2d_catch)
___DEF_P_HLBL(___L4_eval_2d_string_2d_catch)
___DEF_P_HLBL(___L5_eval_2d_string_2d_catch)
___DEF_P_HLBL(___L6_eval_2d_string_2d_catch)
___DEF_P_HLBL(___L7_eval_2d_string_2d_catch)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_eval_2d_string_2d_catch)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_eval_2d_string_2d_catch)
   ___SET_STK(1,___ALLOC_CLO(1))
   ___BEGIN_SETUP_CLO(1,___STK(1),3)
   ___ADD_CLO_ELEM(0,___R1)
   ___END_SETUP_CLO(1)
   ___SET_R1(___STK(1))
   ___ADJFP(1)
   ___CHECK_HEAP(1,4096)
___DEF_SLBL(1,___L1_eval_2d_string_2d_catch)
   ___POLL(2)
___DEF_SLBL(2,___L2_eval_2d_string_2d_catch)
   ___ADJFP(-1)
   ___JUMPGLOSAFE(___SET_NARGS(1),4,___G_catch_2d_all_2d_errors)
___DEF_SLBL(3,___L3_eval_2d_string_2d_catch)
   ___IF_NARGS_EQ(0,___NOTHING)
   ___WRONG_NARGS(3,0,0,0)
   ___SET_STK(1,___R0)
   ___SET_R1(___CLO(___R4,1))
   ___SET_R0(___LBL(5))
   ___ADJFP(4)
   ___POLL(4)
___DEF_SLBL(4,___L4_eval_2d_string_2d_catch)
   ___JUMPGLOSAFE(___SET_NARGS(1),11,___G_read_2d_from_2d_string)
___DEF_SLBL(5,___L5_eval_2d_string_2d_catch)
   ___SET_R0(___LBL(6))
   ___JUMPGLOSAFE(___SET_NARGS(1),20,___G_eval)
___DEF_SLBL(6,___L6_eval_2d_string_2d_catch)
   ___SET_R0(___STK(-3))
   ___POLL(7)
___DEF_SLBL(7,___L7_eval_2d_string_2d_catch)
   ___ADJFP(-4)
   ___JUMPGLOSAFE(___SET_NARGS(1),14,___G_write_2d_to_2d_string)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_heartbeat
#undef ___PH_LBL0
#define ___PH_LBL0 59
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R0 ___D_R1 ___D_R2 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R0 ___R_R1 ___R_R2 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_FP ___W_R0 ___W_R1 ___W_R2 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_heartbeat)
___DEF_P_HLBL(___L1_heartbeat)
___DEF_P_HLBL(___L2_heartbeat)
___DEF_P_HLBL(___L3_heartbeat)
___DEF_P_HLBL(___L4_heartbeat)
___DEF_P_HLBL(___L5_heartbeat)
___DEF_P_HLBL(___L6_heartbeat)
___DEF_P_HLBL(___L7_heartbeat)
___DEF_P_HLBL(___L8_heartbeat)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_heartbeat)
   ___IF_NARGS_EQ(0,___NOTHING)
   ___WRONG_NARGS(0,0,0,0)
___DEF_GLBL(___L_heartbeat)
   ___SET_STK(1,___R0)
   ___SET_R0(___LBL(2))
   ___ADJFP(4)
   ___POLL(1)
___DEF_SLBL(1,___L1_heartbeat)
   ___JUMPGLOSAFE(___SET_NARGS(0),17,___G__23__23_thread_2d_heartbeat_21_)
___DEF_SLBL(2,___L2_heartbeat)
   ___SET_R1(___SYM_jazz_2e_language_2e_runtime_2e_functional_3a_thread_2d_process)
   ___SET_R0(___LBL(3))
   ___JUMPGLOSAFE(___SET_NARGS(1),16,___G__23__23_global_2d_var_3f_)
___DEF_SLBL(3,___L3_heartbeat)
   ___IF(___FALSEP(___R1))
   ___GOTO(___L9_heartbeat)
   ___END_IF
   ___GOTO(___L15_heartbeat)
___DEF_SLBL(4,___L4_heartbeat)
   ___IF(___NOT(___FALSEP(___R1)))
   ___GOTO(___L10_heartbeat)
   ___END_IF
   ___ADJFP(-4)
___DEF_GLBL(___L9_heartbeat)
   ___SET_R1(___VOID)
   ___POLL(5)
___DEF_SLBL(5,___L5_heartbeat)
   ___ADJFP(-4)
   ___JUMPPRM(___NOTHING,___STK(1))
___DEF_GLBL(___L10_heartbeat)
   ___SET_R1(___STK(-6))
   ___ADJFP(-4)
   ___GOTO(___L12_heartbeat)
___DEF_SLBL(6,___L6_heartbeat)
   ___SET_R2(___R1)
   ___SET_R1(___STK(-6))
   ___ADJFP(-4)
   ___IF(___NOT(___EQP(___GLO_not,___PRM_not)))
   ___GOTO(___L13_heartbeat)
   ___END_IF
___DEF_GLBL(___L11_heartbeat)
   ___IF(___NOT(___FALSEP(___R2)))
   ___GOTO(___L9_heartbeat)
   ___END_IF
___DEF_GLBL(___L12_heartbeat)
   ___SET_R2(___FIX(0L))
   ___SET_STK(-2,___R1)
   ___SET_R1(___KEY_timeout)
   ___SET_R0(___STK(-3))
   ___POLL(7)
___DEF_SLBL(7,___L7_heartbeat)
   ___ADJFP(-4)
   ___JUMPGENSAFE(___SET_NARGS(2),___STK(2))
___DEF_SLBL(8,___L8_heartbeat)
   ___IF(___NOT(___EQP(___GLO__23__23_unbound_3f_,___PRM__23__23_unbound_3f_)))
   ___GOTO(___L14_heartbeat)
   ___END_IF
   ___SET_R2(___BOOLEAN(___UNBOUNDP(___R1)))
   ___IF(___EQP(___GLO_not,___PRM_not))
   ___GOTO(___L11_heartbeat)
   ___END_IF
___DEF_GLBL(___L13_heartbeat)
   ___SET_STK(-2,___R1)
   ___SET_R1(___R2)
   ___SET_R0(___LBL(4))
   ___ADJFP(4)
   ___JUMPGLOSAFE(___SET_NARGS(1),21,___G_not)
___DEF_GLBL(___L14_heartbeat)
   ___SET_STK(-2,___R1)
   ___SET_R0(___LBL(6))
   ___ADJFP(4)
   ___JUMPGLOSAFE(___SET_NARGS(1),18,___G__23__23_unbound_3f_)
___DEF_GLBL(___L15_heartbeat)
   ___SET_R1(___SYM_jazz_2e_language_2e_runtime_2e_functional_3a_thread_2d_process)
   ___SET_R0(___LBL(8))
   ___JUMPGLOSAFE(___SET_NARGS(1),15,___G__23__23_global_2d_var_2d_ref)
___END_P_SW
___END_P_COD

___END_M_SW
___END_M_COD

___BEGIN_LBL
 ___DEF_LBL_INTRO(___H__20_mylib," mylib",___REF_FAL,1,0)
,___DEF_LBL_PROC(___H__20_mylib,0,-1)
,___DEF_LBL_INTRO(___H__20_mylib_23_0," mylib#0",___REF_FAL,2,0)
,___DEF_LBL_PROC(___H__20_mylib_23_0,1,-1)
,___DEF_LBL_RET(___H__20_mylib_23_0,___IFD(___RETN,2,1,0x3L))
,___DEF_LBL_INTRO(___H__20_mylib_23_1," mylib#1",___REF_FAL,2,0)
,___DEF_LBL_PROC(___H__20_mylib_23_1,2,-1)
,___DEF_LBL_RET(___H__20_mylib_23_1,___IFD(___RETN,3,2,0x7L))
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
,___DEF_LBL_INTRO(___H_eval_2d_string_2d_void,0,___REF_FAL,4,gambit_eval_string_void)
,___DEF_LBL_PROC(___H_eval_2d_string_2d_void,1,-1)
,___DEF_LBL_RET(___H_eval_2d_string_2d_void,___IFD(___RETI,4,0,0x3f1L))
,___DEF_LBL_RET(___H_eval_2d_string_2d_void,___IFD(___RETN,1,0,0x1L))
,___DEF_LBL_RET(___H_eval_2d_string_2d_void,___IFD(___RETI,4,4,0x3f0L))
,___DEF_LBL_INTRO(___H_eval_2d_string_2d_int,0,___REF_FAL,4,gambit_eval_string_int)
,___DEF_LBL_PROC(___H_eval_2d_string_2d_int,1,-1)
,___DEF_LBL_RET(___H_eval_2d_string_2d_int,___IFD(___RETI,4,0,0x3f1L))
,___DEF_LBL_RET(___H_eval_2d_string_2d_int,___IFD(___RETN,1,0,0x1L))
,___DEF_LBL_RET(___H_eval_2d_string_2d_int,___IFD(___RETI,4,4,0x3f0L))
,___DEF_LBL_INTRO(___H_eval_2d_string_2d_string,0,___REF_FAL,4,gambit_eval_string_string)
,___DEF_LBL_PROC(___H_eval_2d_string_2d_string,1,-1)
,___DEF_LBL_RET(___H_eval_2d_string_2d_string,___IFD(___RETI,4,0,0x3f1L))
,___DEF_LBL_RET(___H_eval_2d_string_2d_string,___IFD(___RETN,1,0,0x1L))
,___DEF_LBL_RET(___H_eval_2d_string_2d_string,___IFD(___RETI,4,4,0x3f0L))
,___DEF_LBL_INTRO(___H_eval_2d_string,0,___REF_FAL,5,gambit_eval_string)
,___DEF_LBL_PROC(___H_eval_2d_string,1,-1)
,___DEF_LBL_RET(___H_eval_2d_string,___IFD(___RETI,4,0,0x3f1L))
,___DEF_LBL_RET(___H_eval_2d_string,___IFD(___RETN,1,0,0x1L))
,___DEF_LBL_RET(___H_eval_2d_string,___IFD(___RETN,1,0,0x1L))
,___DEF_LBL_RET(___H_eval_2d_string,___IFD(___RETI,4,4,0x3f0L))
,___DEF_LBL_INTRO(___H_eval_2d_string_2d_catch,0,___REF_FAL,8,gambit_eval_string_catch)
,___DEF_LBL_PROC(___H_eval_2d_string_2d_catch,1,-1)
,___DEF_LBL_RET(___H_eval_2d_string_2d_catch,___IFD(___RETI,1,4,0x3f0L))
,___DEF_LBL_RET(___H_eval_2d_string_2d_catch,___IFD(___RETI,1,4,0x3f0L))
,___DEF_LBL_PROC(___H_eval_2d_string_2d_catch,0,1)
,___DEF_LBL_RET(___H_eval_2d_string_2d_catch,___IFD(___RETI,4,0,0x3f1L))
,___DEF_LBL_RET(___H_eval_2d_string_2d_catch,___IFD(___RETN,1,0,0x1L))
,___DEF_LBL_RET(___H_eval_2d_string_2d_catch,___IFD(___RETN,1,0,0x1L))
,___DEF_LBL_RET(___H_eval_2d_string_2d_catch,___IFD(___RETI,4,4,0x3f0L))
,___DEF_LBL_INTRO(___H_heartbeat,0,___REF_FAL,9,gambit_heartbeat)
,___DEF_LBL_PROC(___H_heartbeat,0,-1)
,___DEF_LBL_RET(___H_heartbeat,___IFD(___RETI,4,0,0x3f1L))
,___DEF_LBL_RET(___H_heartbeat,___IFD(___RETN,1,0,0x1L))
,___DEF_LBL_RET(___H_heartbeat,___IFD(___RETN,1,0,0x1L))
,___DEF_LBL_RET(___H_heartbeat,___IFD(___RETN,5,0,0x3L))
,___DEF_LBL_RET(___H_heartbeat,___IFD(___RETI,4,0,0x3f1L))
,___DEF_LBL_RET(___H_heartbeat,___IFD(___RETN,5,0,0x3L))
,___DEF_LBL_RET(___H_heartbeat,___IFD(___RETI,4,4,0x3f2L))
,___DEF_LBL_RET(___H_heartbeat,___IFD(___RETN,1,0,0x1L))
___END_LBL

___BEGIN_MOD_PRM
___DEF_MOD_PRM(0,___G__20_mylib,1)
___DEF_MOD_PRM(1,___G__20_mylib_23_0,3)
___DEF_MOD_PRM(2,___G__20_mylib_23_1,6)
___END_MOD_PRM

___BEGIN_MOD_C_INIT
___END_MOD_C_INIT

___BEGIN_MOD_GLO
___DEF_MOD_GLO(0,___G__20_mylib,1)
___DEF_MOD_GLO(1,___G__20_mylib_23_0,3)
___DEF_MOD_GLO(2,___G__20_mylib_23_1,6)
___END_MOD_GLO

___BEGIN_MOD_SYM_KEY
___DEF_MOD_SYM(0,___S_jazz_2e_language_2e_runtime_2e_functional_3a_thread_2d_process,"jazz.language.runtime.functional:thread-process")

___DEF_MOD_SYM(1,___S_mylib,"mylib")
___DEF_MOD_KEY(0,___K_timeout,"timeout")
___END_MOD_SYM_KEY

#endif
