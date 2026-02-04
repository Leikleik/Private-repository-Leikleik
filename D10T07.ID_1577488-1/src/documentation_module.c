#include <stdarg.h>
#include <stdlib.h>

#include "documentation_module.h"

int validate(char* data)
{
    int validation_result = !strcmp(data, Available_document);
    return validation_result;
}

int* check_available_documentation_module(int (*validate) (char*), int document_count, ...)
{
    int* result = NULL;
    if (validate != NULL && document_count > 0) {
        result = malloc(sizeof(int) * document_count);
        if (result != NULL) {
            va_list args;
            va_start(args, document_count);
            for (int i = 0; i < document_count; i++) {
                char* document = va_arg(args, char*);
                result[i] = validate(document) ? 1 : 0;
            }
            va_end(args);
        }
    }
    return result;
}
