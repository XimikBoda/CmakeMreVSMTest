#include <vmsys.h>
#include <vmsm.h>
#include <string.h>

#define SM_HANDLE handle_smevt //name of callback
#include "vsm_fastmacros.h" // gives faster macros

#include "lib_exports.h"

VMINT handle_smevt(VMINT message, VMINT param);

void vm_main(void) {
	vm_reg_sm_callback(handle_smevt);
}

VMINT handle_smevt(VMINT message, VMINT param) {
	switch (message) {
	case VM_SM_MSG_LOAD:
		break;
	case VM_SM_MSG_QUERY:
		switch (param) {
		case id_get_hello_string:
			return (VMINT)get_hello_string;
		default:
			return NULL;
		}
		break;
	case VM_SM_MSG_UNLOAD:
		break;
	}
	return 0;
}

void get_hello_string(VMSTR str, VMINT len) {
	// main app evriroment
	SM_PROCESS_BEGIN()
		// liblary enviromennt
		strncpy(str, "Hello from vsm!", len);

	SM_PROCESS_END()
}

// also see SM_CALLBACK_BEGIN() SM_CALLBACK_END()
