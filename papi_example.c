#include <papi.h>
#include <stdio.h>

int main() {
    int retval = PAPI_library_init(PAPI_VER_CURRENT);
    if (retval != PAPI_VER_CURRENT) {
        printf("PAPI library initialization error: %s\n", PAPI_strerror(retval));
        return 1;
    }

    printf("PAPI library initialized successfully.\n");
    return 0;
}

