#include <stdio.h>
#include <string.h>
#include <time.h>

#include "print_module.h"

int print_char(char ch)
{
    return putchar(ch);
}

void print_log(int (*print)(char), char* message)
{
    char time_buffer[9] = "00:00:00";
    char output[256];
    const char* safe_message = message != NULL ? message : "";
    time_t now = time(NULL);
    struct tm* time_info = localtime(&now);
    if (time_info != NULL) {
        strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", time_info);
    }
    snprintf(output, sizeof(output), "%s %s %s", Log_prefix, time_buffer, safe_message);
    for (size_t i = 0; output[i] != '\0'; i++) {
        print(output[i]);
    }
}
