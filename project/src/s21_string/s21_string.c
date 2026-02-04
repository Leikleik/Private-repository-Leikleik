#include "s21_string.h"

size_t s21_strlen(const char *str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int s21_strcmp(const char *str1, const char *str2) {
    size_t index = 0;
    while (str1[index] != '\0' && str2[index] != '\0' && str1[index] == str2[index]) {
        index++;
    }
    return (unsigned char)str1[index] - (unsigned char)str2[index];
}

char *s21_strcpy(char *dest, const char *src) {
    size_t index = 0;
    while (src[index] != '\0') {
        dest[index] = src[index];
        index++;
    }
    dest[index] = '\0';
    return dest;
}

char *s21_strcat(char *dest, const char *src) {
    size_t dest_len = s21_strlen(dest);
    size_t index = 0;
    while (src[index] != '\0') {
        dest[dest_len + index] = src[index];
        index++;
    }
    dest[dest_len + index] = '\0';
    return dest;
}

char *s21_strchr(const char *str, int c) {
    char target = (char)c;
    for (size_t i = 0;; i++) {
        if (str[i] == target) {
            return (char *)(str + i);
        }
        if (str[i] == '\0') {
            break;
        }
    }
    return NULL;
}

char *s21_strstr(const char *haystack, const char *needle) {
    if (*needle == '\0') {
        return (char *)haystack;
    }

    for (size_t i = 0; haystack[i] != '\0'; i++) {
        size_t j = 0;
        while (haystack[i + j] != '\0' && needle[j] != '\0' &&
               haystack[i + j] == needle[j]) {
            j++;
        }
        if (needle[j] == '\0') {
            return (char *)(haystack + i);
        }
    }
    return NULL;
}
