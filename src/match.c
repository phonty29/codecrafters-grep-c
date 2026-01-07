#include "match.h"

bool match_digit(const char* input_line) {
    for (int i = 0; i < strlen(input_line); i++) {
        if (isdigit((unsigned char) input_line[i])) {
            return true;
        }
    }
    return false;
}

bool match_word(const char* input_line) {
    for (int i = 0; i < strlen(input_line); i++) {
        if (isalnum(input_line[i]) || input_line[i] == '_') {
            return true;
        }
    }
    return false;
}

bool match_positive_char_groups(const char* input_line, const char* pattern) {
    for (int i = 1; i < strlen(pattern) - 1; i++) {
        if (strchr(input_line, pattern[i])) {
            return true;
        }
    }
    return false;
}

bool match_negative_char_groups(const char* input_line, const char* pattern) {
    for (int i = 2; i < strlen(pattern) - 1; i++) {
        if (!strchr(input_line, pattern[i])) {
            return true;
        }
    }
    return false;
}

bool match_pattern(const char* input_line, const char* pattern) {
    if (strlen(pattern) == 1) {
        return strchr(input_line, pattern[0]) != NULL;
    }
    else if (strcmp(pattern, "\\d") == 0) {
        return match_digit(input_line);
    }
    else if (strcmp(pattern, "\\w") == 0) {
        return match_word(input_line);
    }
    else if (pattern[0] == '[' && pattern[strlen(pattern)-1] == ']') {
        if (pattern[1] == '^') {
            return match_negative_char_groups(input_line, pattern);
        } else {
            return match_positive_char_groups(input_line, pattern);
        }
    }
    fprintf(stderr, "Unhandled pattern %s\n", pattern);
    return false;
}