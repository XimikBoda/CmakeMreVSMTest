#pragma once
#include <vmsys.h>

enum {
    id_get_hello_string = 1
};

void get_hello_string(VMSTR str, VMINT len);
using get_hello_string_t = decltype(+get_hello_string); //auto generated prototype

//typedef void (*get_hello_string_t)(VMSTR str, VMINT len);