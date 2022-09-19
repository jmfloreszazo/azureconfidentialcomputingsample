#include "Enclave_t.h"
#include <stdio.h>
#include <string.h>

int trusted_function()
{
    int trusted_value = 98765;
    wait_keyinput("Please enter key to show variables values allocated in memory...");
    return trusted_value;
}
