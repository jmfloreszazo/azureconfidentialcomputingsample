#include <stdio.h>
#include <string.h>

# define ENCLAVE_FILENAME "enclave.signed.so"

#include "sgx_urts.h"
#include "App.h"
#include "Enclave_u.h"

sgx_enclave_id_t global_eid = 0;

/* ocall functions (untrusted) */
void wait_keyinput(const char *str)
{
    printf("%s", str);
    getchar();
}

/* application entry */
int SGX_CDECL main(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);

    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    int untrusted_value = 12345;

    // init enclave
    ret = sgx_create_enclave(ENCLAVE_FILENAME, SGX_DEBUG_FLAG, NULL, NULL, &global_eid, NULL);
    if (ret != SGX_SUCCESS) {
        printf("Enclave init error\n");
        getchar();
        return -1;
    }
 
    // invoke enclave();
    int returned_result;
    ret = trusted_function(global_eid, &returned_result);
    if (ret != SGX_SUCCESS) {
        printf("Enclave call error\n");
        return -1;
    }

    // destroy the enclave
    sgx_destroy_enclave(global_eid);

    printf ("X (untrusted value): %d\n", untrusted_value);
    printf ("X (trusted value): %d\n", returned_result);

    return 0;
}

