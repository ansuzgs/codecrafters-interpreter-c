#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE (1==1)
#define FALSE !TRUE

char *read_file_contents(const char *filename);

int main(int argc, char *argv[]) {
    // Disable output buffering
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    if (argc < 3) {
        fprintf(stderr, "Usage: ./your_program tokenize <filename>\n");
        return 1;
    }

    int error_flag = FALSE;

    const char *command = argv[1];

    if (strcmp(command, "tokenize") == 0) {
        // You can use print statements as follows for debugging, they'll be
        // visible when running tests.
        fprintf(stderr, "Logs from your program will appear here!\n");

        char *file_contents = read_file_contents(argv[2]);

        // Uncomment this block to pass the first stage
        if (strlen(file_contents) > 0) {
            for (int i = 0; i < strlen(file_contents); i++) {
                switch(file_contents[i]) {
                case '(':
                    printf("LEFT_PAREN ( null\n");
                    break;
                case ')':
                    printf("RIGHT_PAREN ) null\n");
                    break;
                case '{':
                    printf("LEFT_BRACE { null\n");
                    break;
                case '}':
                    printf("RIGHT_BRACE } null\n");
                    break;
                case '*':
                    printf("STAR * null\n");
                    break;
                case '.':
                    printf("DOT . null\n");
                    break;
                case ',':
                    printf("COMMA , null\n");
                    break;
                case '+':
                    printf("PLUS + null\n");
                    break;
                case '-':
                    printf("MINUS - null\n");
                    break;
                case ';':
                    printf("SEMICOLON ; null\n");
                    break;
                case '/':
                    if (file_contents[i+1] == '/') {
                        while(file_contents[i++] != '\0');
                        break;
                    } else {
                        printf("SLASH / null\n");
                    }
                    break;
                case '<':
                    if (file_contents[i+1] == '=') {
                        printf("LESS_EQUAL <= null\n");
                        i++;
                    } else {
                        printf("LESS < null\n");
                    }
                    break;
                case '>':
                    if (file_contents[i+1] == '=') {
                        printf("GREATER_EQUAL >= null\n");
                        i++;
                    } else {
                        printf("GREATER > null\n");
                    }
                    break;

                case '!':
                    if (file_contents[i+1] == '=') {
                        printf("BANG_EQUAL != null\n");
                        i++;
                    } else {
                        printf("BANG ! null\n");
                    }
                    break;

                case '=':
                    if(file_contents[i+1] == '=') {
                        printf("EQUAL_EQUAL == null\n");
                        i++;
                    } else {
                        printf("EQUAL = null\n");
                    }
                    break;
                case '\t':
                case ' ':
                case '\n'
                    break;
                default:
                    fprintf(stderr, "[line 1] Error: Unexpected character: %c\n", file_contents[i]);
                    error_flag = TRUE;
                    break;
                }
            }
        }
        printf("EOF  null\n"); // Placeholder, remove this line when
                               // implementing the scanner

        free(file_contents);
    } else {
        fprintf(stderr, "Unknown command: %s\n", command);
        return 1;
    }

    if (error_flag) {
        return 65;
    }
    return 0;
}

char *read_file_contents(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error reading file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *file_contents = malloc(file_size + 1);
    if (file_contents == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(file_contents, 1, file_size, file);
    if (bytes_read < file_size) {
        fprintf(stderr, "Error reading file contents\n");
        free(file_contents);
        fclose(file);
        return NULL;
    }

    file_contents[file_size] = '\0';
    fclose(file);

    return file_contents;
}
