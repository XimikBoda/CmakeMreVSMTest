#include "vmsys.h"
#include "vmsm.h"
#include <string.h>

VMINT handle_smevt(VMINT message, VMINT param);
void get_hello_string(VMSTR str, VMINT len);

void vm_main(void) {
    vm_reg_sm_callback(handle_smevt);
}

VMINT handle_smevt(VMINT message, VMINT param)
{
    switch (message)
    {
    case VM_SM_MSG_LOAD:
        break;
    case VM_SM_MSG_QUERY:
        switch (param)
        {
        case 1:
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

void get_hello_string(VMSTR str, VMINT len){
    SM_PROCESS_BEGIN()

    strncpy(str, "Hello SM2 !!!", len);

    SM_PROCESS_END()
}
