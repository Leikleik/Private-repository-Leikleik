#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

#define MAX_TEXT_LENGTH 100
#define MAX_WORDS 120
#define MAX_LINE_LENGTH 120

int is_width_mode(int argc, char **argv) {
    return argc == 2 && argv[1][0] == '-' && argv[1][1] == 'w' && argv[1][2] == '\0';
}

int split_words(const char *text, char words[MAX_WORDS][MAX_TEXT_LENGTH + 1]) {
    int word_count = 0;
    int index = 0;
    int length = (int)s21_strlen(text);

    while (index < length) {
        while (text[index] == ' ') {
            index++;
        }
        if (text[index] == '\0' || text[index] == '\n') {
            break;
        }
        int start = index;
        while (text[index] != ' ' && text[index] != '\0' && text[index] != '\n') {
            index++;
        }
        int word_len = index - start;
        if (word_len > 0 && word_count < MAX_WORDS) {
            for (int i = 0; i < word_len; i++) {
                words[word_count][i] = text[start + i];
            }
            words[word_count][word_len] = '\0';
            word_count++;
        }
    }
    return word_count;
}

void build_justified_line(char words[MAX_WORDS][MAX_TEXT_LENGTH + 1], int word_count,
                          int total_len, int width, char *line) {
    int index = 0;
    if (word_count == 1) {
        for (int i = 0; words[0][i] != '\0'; i++) {
            line[index++] = words[0][i];
        }
        line[index] = '\0';
        return;
    }

    int gaps = word_count - 1;
    int spaces_needed = width - total_len;
    int base_space = spaces_needed / gaps;
    int extra = spaces_needed % gaps;

    for (int i = 0; i < word_count; i++) {
        for (int j = 0; words[i][j] != '\0'; j++) {
            line[index++] = words[i][j];
        }
        if (i < gaps) {
            int spaces = base_space + (i < extra ? 1 : 0);
            for (int s = 0; s < spaces; s++) {
                line[index++] = ' ';
            }
        }
    }
    line[index] = '\0';
}

int append_word(char words[MAX_WORDS][MAX_TEXT_LENGTH + 1], int word_count,
                const char *word) {
    int index = 0;
    while (word[index] != '\0') {
        words[word_count][index] = word[index];
        index++;
    }
    words[word_count][index] = '\0';
    return word_count + 1;
}

int main(int argc, char **argv) {
    if (!is_width_mode(argc, argv)) {
        printf("n/a");
        return 0;
    }

    int width = 0;
    if (scanf("%d", &width) != 1 || width <= 0) {
        printf("n/a");
        return 0;
    }

    int ch = getchar();
    while (ch != '\n' && ch != EOF) {
        ch = getchar();
    }

    char text[MAX_TEXT_LENGTH + 2] = {0};
    if (!fgets(text, sizeof(text), stdin)) {
        printf("n/a");
        return 0;
    }

    char words[MAX_WORDS][MAX_TEXT_LENGTH + 1];
    int word_count = split_words(text, words);

    char lines[MAX_WORDS][MAX_LINE_LENGTH];
    int line_count = 0;

    char current_words[MAX_WORDS][MAX_TEXT_LENGTH + 1];
    int current_count = 0;
    int current_len = 0;

    for (int i = 0; i < word_count; i++) {
        char *word = words[i];
        int word_len = (int)s21_strlen(word);

        if (word_len <= width) {
            int min_line_len = current_len + word_len + (current_count > 0 ? current_count : 0);
            if (current_count == 0 || min_line_len <= width) {
                current_count = append_word(current_words, current_count, word);
                current_len += word_len;
            } else {
                build_justified_line(current_words, current_count, current_len, width,
                                     lines[line_count++]);
                current_count = 0;
                current_len = 0;
                current_count = append_word(current_words, current_count, word);
                current_len += word_len;
            }
        } else {
            int remaining = width - (current_len + (current_count > 0 ? current_count : 0));
            if (current_count > 0 && remaining >= 2) {
                char segment[MAX_TEXT_LENGTH + 1];
                int segment_letters = remaining - 1;
                for (int j = 0; j < segment_letters; j++) {
                    segment[j] = word[j];
                }
                segment[segment_letters] = '-';
                segment[segment_letters + 1] = '\0';
                current_count = append_word(current_words, current_count, segment);
                current_len += segment_letters + 1;
                build_justified_line(current_words, current_count, current_len, width,
                                     lines[line_count++]);
                current_count = 0;
                current_len = 0;
                word += segment_letters;
                word_len -= segment_letters;
            } else if (current_count > 0) {
                build_justified_line(current_words, current_count, current_len, width,
                                     lines[line_count++]);
                current_count = 0;
                current_len = 0;
            }

            while (word_len > width) {
                char segment[MAX_TEXT_LENGTH + 1];
                int segment_letters = width - 1;
                for (int j = 0; j < segment_letters; j++) {
                    segment[j] = word[j];
                }
                segment[segment_letters] = '-';
                segment[segment_letters + 1] = '\0';
                current_count = append_word(current_words, current_count, segment);
                current_len = segment_letters + 1;
                build_justified_line(current_words, current_count, current_len, width,
                                     lines[line_count++]);
                current_count = 0;
                current_len = 0;
                word += segment_letters;
                word_len -= segment_letters;
            }

            if (word_len > 0) {
                current_count = append_word(current_words, current_count, word);
                current_len += word_len;
            }
        }
    }

    if (current_count > 0) {
        build_justified_line(current_words, current_count, current_len, width,
                             lines[line_count++]);
    }

    for (int i = 0; i < line_count; i++) {
        printf("%s", lines[i]);
        if (i < line_count - 1) {
            printf("\n");
        }
    }

    return 0;
}
