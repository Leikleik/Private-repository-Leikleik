#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

int s21_string_equal(const char *left, const char *right) {
    size_t index = 0;
    while (left[index] != '\0' || right[index] != '\0') {
        if (left[index] != right[index]) {
            return 0;
        }
        index++;
    }
    return 1;
}

int compare_strings_expected(const char *left, const char *right) {
    size_t index = 0;
    while (left[index] != '\0' && right[index] != '\0' && left[index] == right[index]) {
        index++;
    }
    if ((unsigned char)left[index] < (unsigned char)right[index]) {
        return -1;
    }
    if ((unsigned char)left[index] > (unsigned char)right[index]) {
        return 1;
    }
    return 0;
}

int find_char_index_expected(const char *str, int c) {
    char target = (char)c;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == target) {
            return i;
        }
    }
    if (target == '\0') {
        return (int)s21_strlen(str);
    }
    return -1;
}

int find_substring_index_expected(const char *haystack, const char *needle) {
    if (needle[0] == '\0') {
        return 0;
    }
    for (int i = 0; haystack[i] != '\0'; i++) {
        int j = 0;
        while (haystack[i + j] != '\0' && needle[j] != '\0' &&
               haystack[i + j] == needle[j]) {
            j++;
        }
        if (needle[j] == '\0') {
            return i;
        }
    }
    return -1;
}

void s21_strlen_test() {
    const char *inputs[] = {"hello", "", "hello world"};
    size_t expected[] = {5, 0, 11};

    for (int i = 0; i < 3; i++) {
        size_t result = s21_strlen(inputs[i]);
        printf("s21_strlen(\"%s\") = %zu | expected %zu | %s\n", inputs[i], result,
               expected[i], result == expected[i] ? "SUCCESS" : "FAIL");
    }
}

void s21_strcmp_test() {
    const char *left[] = {"abc", "abc", "abcd"};
    const char *right[] = {"abd", "abc", "abc"};

    for (int i = 0; i < 3; i++) {
        int result = s21_strcmp(left[i], right[i]);
        int expected = compare_strings_expected(left[i], right[i]);
        int pass = (result == 0 && expected == 0) || (result < 0 && expected < 0) ||
                   (result > 0 && expected > 0);
        printf("s21_strcmp(\"%s\", \"%s\") = %d | expected %d | %s\n", left[i], right[i],
               result, expected, pass ? "SUCCESS" : "FAIL");
    }
}

void s21_strcpy_test() {
    const char *inputs[] = {"hello", "", "copy me"};
    for (int i = 0; i < 3; i++) {
        char buffer[64];
        s21_strcpy(buffer, inputs[i]);
        printf("s21_strcpy(\"%s\") -> \"%s\" | expected \"%s\" | %s\n", inputs[i], buffer,
               inputs[i], s21_string_equal(buffer, inputs[i]) ? "SUCCESS" : "FAIL");
    }
}

void s21_strcat_test() {
    const char *left[] = {"hi", "", "abc"};
    const char *right[] = {" there", "empty", ""};
    const char *expected[] = {"hi there", "empty", "abc"};

    for (int i = 0; i < 3; i++) {
        char buffer[64];
        s21_strcpy(buffer, left[i]);
        s21_strcat(buffer, right[i]);
        printf("s21_strcat(\"%s\", \"%s\") -> \"%s\" | expected \"%s\" | %s\n", left[i],
               right[i], buffer, expected[i],
               s21_string_equal(buffer, expected[i]) ? "SUCCESS" : "FAIL");
    }
}

void s21_strchr_test() {
    const char *input = "hello world";
    int targets[] = {'o', 'z', '\0'};

    for (int i = 0; i < 3; i++) {
        char *result = s21_strchr(input, targets[i]);
        int index = result ? (int)(result - input) : -1;
        int expected = find_char_index_expected(input, targets[i]);
        printf("s21_strchr(\"%s\", '%c') -> %d | expected %d | %s\n", input,
               targets[i] == '\0' ? '0' : targets[i], index, expected,
               index == expected ? "SUCCESS" : "FAIL");
    }
}

void s21_strstr_test() {
    const char *haystack = "hello world";
    const char *needles[] = {"world", "nope", ""};

    for (int i = 0; i < 3; i++) {
        char *result = s21_strstr(haystack, needles[i]);
        int index = result ? (int)(result - haystack) : -1;
        int expected = find_substring_index_expected(haystack, needles[i]);
        printf("s21_strstr(\"%s\", \"%s\") -> %d | expected %d | %s\n", haystack, needles[i],
               index, expected, index == expected ? "SUCCESS" : "FAIL");
    }
}

int main() {
    s21_strlen_test();
    s21_strcmp_test();
    s21_strcpy_test();
    s21_strcat_test();
    s21_strchr_test();
    s21_strstr_test();
    return 0;
}
