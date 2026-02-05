#include <stdio.h>
#include <stdlib.h>

#include "print_module.h"
#ifdef DOCUMENTATION_MODULE
#include "documentation_module.h"
#endif

#ifdef DOCUMENTATION_MODULE
static void print_documentation_status(char** documents, int* availability, int count)
{
    for (int i = 0; i < count; i++) {
        const char* status = availability[i] ? "available" : "unavailable";
        printf("[%15s : %s]\n", documents[i], status);
    }
}
#endif

int main(void)
{
    print_log(print_char, Module_load_success_message);

#ifdef DOCUMENTATION_MODULE
    char* documents[] = {Documents};
    int* availability_mask = check_available_documentation_module(validate, Documents_count, Documents);
    if (availability_mask != NULL) {
        print_documentation_status(documents, availability_mask, Documents_count);
        free(availability_mask);
    }
#endif

    return 0;
}
