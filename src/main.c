#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool match_pattern(const char* input_line, const char* pattern) {
    bool val = 0;
    switch (strlen(pattern)){
        case 1:
            val = strchr(input_line, pattern[0]) != NULL;
            break;
        case 2:
            if (strcmp(pattern, "-E") != 1) {
                int il_len = strlen(input_line);
                for (int i = 0; i < il_len; i++) {
                    if (isdigit((unsigned char) input_line[i])) {
                        val = 1;
                        break;
                    }
                }
            } 
            break;
        default:
            fprintf(stderr, "Unhandled pattern %s\n", pattern);
    }
    return val;
}

int main(int argc, char* argv[]) {
    // Disable output buffering
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    fprintf(stderr, "Logs from your program will appear here\n");

    if (argc != 3) {
        fprintf(stderr, "Expected two arguments\n");
        return 1;
    }

    const char* flag = argv[1];
    const char* pattern = argv[2];

    if (strcmp(flag, "-E") != 0) {
        fprintf(stderr, "Expected first argument to be '-E'\n");
        return 1;
    }

    char input_line[1024];
    if (fgets(input_line, sizeof(input_line), stdin) == NULL) {
        return 1;
    }
    
    // Remove trailing newline
    input_line[strcspn(input_line, "\n")] = '\0';
    
    if (match_pattern(input_line, pattern)) {
        return 0;
    } else {
        return 1;
    }
}
