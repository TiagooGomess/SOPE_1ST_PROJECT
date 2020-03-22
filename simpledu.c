#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Se um elemento da struct foi especificado nos argumentos da linha de comandos,
 * fica a 1 na struct Arguments, senão fica a 0.
 */
typedef struct {
    int all;
    int bytes;
    int blockSize;
    int countLinks;
    int dereference;
    int separateDirs;
    int maxDepth;
} Arguments;

void initializeArgumentsStruct(Arguments* arguments) {
    printf("start\n");
    arguments->all = 0;
    arguments->bytes = 0;
    arguments->blockSize = 0;
    arguments->countLinks = 1;
    printf("I DID IT!\n");
    arguments->dereference = 0;
    arguments->separateDirs = 0;
    arguments->maxDepth = 0;
}

void checkArguments(Arguments* arguments, int argc, char* argv[]) {
    //for (int i = 1; i < argc; )
}

int main(int argc, char* argv[]) {
    if (argc < 2 || strcmp(argv[1], "-l") != 0) {
        fprintf(stderr, "Usage: %s -l [path] [-a] [-b] [-B size] [-L] [-S] [--max-depth=N]\n", argv[0]);
        exit(1);
    }
    
    Arguments arguments;
    fodasew

    printf("before\n");
    initializeArgumentsStruct(&arguments);
    printf("after\n");

    printf("TEST: %d\n", arguments.countLinks);

    //checkArguments(&arguments, argc, argv);

}