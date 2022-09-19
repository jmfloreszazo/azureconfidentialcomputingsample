#include "Enclave_t.h"
#include <stdio.h>
#include <string.h>

int trusted_function()
{
    int trusted_value = 987654321;
    wait_keyinput("Enter key to show variables values in memory...");
    return trusted_value;
}
