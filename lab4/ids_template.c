#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2
#define IN_STRING 4
#define IN_ID 8

#define MAX_ID_LEN 64
#define MAX_IDS 1024

int index_cmp(const void*, const void*);
int cmp(const void*, const void*);

char identifiers[MAX_IDS][MAX_ID_LEN];

const char *keywords[] = {
	"auto", "break", "case", "char",
	"const", "continue", "default", "do",
	"double", "else", "enum", "extern",
	"float", "for", "goto", "if",
	"int", "long", "register", "return",
	"short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union",
	"unsigned", "void", "volatile", "while"
};

int find_idents() {
    int character = 0;
    int match = 0;
    int index = 0;
    int unique_count = 0;
    int is_similar = 1;
    char identifier[MAX_ID_LEN];
    char table[MAX_ID_LEN][MAX_ID_LEN];

    for (int i = 0; i < MAX_ID_LEN; i++) {
        identifier[i] = '\0';
    }

    for (int i = 0; i < MAX_ID_LEN; i++) {
        for (int j = 0; j < MAX_ID_LEN; j++) {
            table[i][j] = '\0';
        }
    }

    while ((character = getchar()) != EOF) {
        if (isalpha(character) || character == '_') {
            identifier[index++] = character;
            while ((character = getchar()) != EOF) {
                if (isalnum(character) || character == '_') {
                    identifier[index++] = character;
                } else {
                    break;
                }
            }
            is_similar = 0;
            for (int i = 0; i < 32; i++) {
                if (index == strlen(keywords[i])) {
                    is_similar = 1;
                    for (int j = 0; j < index; j++) {
                        if (keywords[i][j] != identifier[j]) {
                            is_similar = 0;
                            break;
                        }
                    }
                    if (is_similar == 1) {
                        break;
                    }
                }
            }
            if (is_similar == 0) {
                for (int i = 0; i < unique_count; i++) {
                    if (index == strlen(table[i])) {
                        is_similar = 1;
                        for (int j = 0; j < index; j++) {
                            if (table[i][j] != identifier[j]) {
                                is_similar = 0;
                                break;
                            }
                        }
                        if (is_similar == 1) {
                            break;
                        }
                    }
                }
                if (is_similar == 0) {
                    for (int i = 0; i < index; i++) {
                        table[unique_count][i] = identifier[i];
                    }
                    unique_count++;
                }
            }
            for (int i = 0; i < index; i++) {
                identifier[i] = '\0';
            }
            index = 0;
        }
        if (character == '/') {
            character = getchar();
            if (character == '/') {
                while ((character = getchar()) != EOF) {
                    if (character == '\n') {
                        break;
                    }
                }
            } else if (character == '*') {
                match = getchar();
                while ((character = getchar()) != EOF) {
                    if (match == '*' && character == '/') {
                        break;
                    }
                    match = character;
                }
            }
        }
        if (character == '"') {
            match = getchar();
            if (match != '"') {
                while ((character = getchar()) != EOF) {
                    if (match != '\\' && character == '"') {
                        break;
                    }
                    match = character;
                }
            }
        }
        if (character == '\'') {
            while ((character = getchar()) != EOF) {
                if (character == '\'') {
                    break;
                }
            }
        }
    }
    return unique_count;
}

int cmp(const void* first_arg, const void* second_arg) {
	char *a = *(char**)first_arg;
	char *b = *(char**)second_arg;
	return strcmp(a, b);
}

int index_cmp(const void* first_arg, const void* second_arg) {
	int a = *(int*)first_arg;
	int b = *(int*)second_arg;
	return strcmp(identifiers[a], identifiers[b]);
}

int main(void) {
	printf("%d\n", find_idents());
	return 0;
}

