#pragma once
#include <vmsm.h>

// this does not call mre_entry every time, 
// compared to the standard implementation

#define SM_PROCESS_BEGIN() {\
	if (vm_sm_set_sb_by_ptr((VMINT)SM_HANDLE) == 0) {

#define SM_PROCESS_RETURN() vm_sm_reset_sb();

#define SM_PROCESS_END() SM_PROCESS_RETURN() } }

#define SM_CALLBACK_BEGIN() {\
	if (vm_sm_set_sb_for_invoker() == 0) { 

#define SM_CALLBACK_END() SM_PROCESS_END()

#define SM_SAFE_CALLBACK(PTR) \
	SM_CALLBACK_BEGIN() \
	PTR; \
	SM_CALLBACK_END()

#define SM_SAFE_CALLBACK_RETURN(PTR, RET) \
	SM_CALLBACK_BEGIN() \
	RET = PTR; \
	SM_CALLBACK_END()

/* Macros for SM STUB */

#define SM_INVOKE_BEGIN(SM)  {\
	if (vm_sm_set_sb_by_handle(SM) == 0) {

#define SM_INVOKE_END() SM_PROCESS_END()

#define SM_SAFE_INVOKE(SM, PTR) \
	SM_INVOKE_BEGIN(SM) \
	PTR; \
	SM_INVOKE_END() 

#define SM_SAFE_INVOKE_RETURN(SM, PTR, RET) \
	SM_INVOKE_BEGIN(SM) \
	RET = PTR; \
	SM_INVOKE_END() 