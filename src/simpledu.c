#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/**
 * Se um elemento da struct não foi especificado nos argumentos da linha de comandos, fica
 * a 0 ou com um valor default. Caso seja especificado, fica a 1 ou com o valor especificado.
 */
typedef struct {
    int all; /* 0 or 1*/
    int bytes; /* 0 or 1*/
    int blockSize; /* número de bytes default do tamanho dos blocks, ou então um valor especificado */
    int countLinks; /* 0 or 1*/
    int dereference; /* 0 or 1*/
    int separateDirs; /* 0 or 1*/
    int maxDepth; /* número de níveis de profundidade (default = INT_MAX) */
} Arguments;

/**
 * Inicializa a struct Arguments com os valores default.
 */
void initializeArgumentsStruct(Arguments* arguments) {
    arguments->all = 0;
    arguments->bytes = 0;
    arguments->blockSize = 1024;
    arguments->countLinks = 1;
    arguments->dereference = 0;
    arguments->separateDirs = 0;
    arguments->maxDepth = INT_MAX;
}

/**
 * Verifica se os argumentos passados na linha de comandos estão corretos.
 * Retorna 1 se está tudo OK, 0 caso haja algum erro.
 */
int checkArguments(Arguments* arguments, int argc, char* argv[]) {
    int jumpIteration = 0;
    for (int i = 1; i < argc; i++) {
        if (jumpIteration) {
            jumpIteration = 0;
            continue;
        }
        if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0) {
            arguments->all = 1;
        }
        else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--bytes") == 0) {
            arguments->bytes = 1;
        }
        else if (strcmp(argv[i], "-B") == 0) { // com espaço entre o -B e o número de bytes            
            if (i + 1 >= argc) { // se não tiver próximo argumento
                return 0;
            }
            int size;
            if (sscanf(argv[i + 1], "%d", &size) != 1) {
                // verificar os caracteres compatíveis e converter esses caracteres para inteiro
                char* sizeString = malloc(2*sizeof(char));
                if (sscanf(argv[i + 1], "%s", sizeString) != 1) {
                    return 0;
                }
                if (strcmp(sizeString, "kB") == 0) {
                    size = 1000;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "KB") == 0) {
                    size = 1000;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "k") == 0) {
                    size = 1024;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "K") == 0) {
                    size = 1024;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "mB") == 0) {
                    size = 1000*1000;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "MB") == 0) {
                    size = 1000*1000;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "m") == 0) {
                    size = 1024*1024;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "M") == 0) {
                    size = 1024*1024;
                    jumpIteration = 1;
                }
                // Consideramos que não há compatibilidade com tamanhos iguais ou superiores ao GB.
                else {
                    return 0;
                }
            }
            else {
                jumpIteration = 1;
            }
            arguments->blockSize = size;
        }
        else if (strstr(argv[i], "-B") != NULL) { // sem espaço entre o -B e o número de bytes
            int size;
            if (sscanf(argv[i], "-B%d", &size) != 1) {
                // verificar os caracteres compatíveis e converter esses caracteres para inteiro
                char* sizeString = malloc(2*sizeof(char));
                if (sscanf(argv[i], "-B%s", sizeString) != 1) {
                    return 0;
                }
                if (strcmp(sizeString, "kB") == 0) {
                    size = 1000;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "KB") == 0) {
                    size = 1000;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "k") == 0) {
                    size = 1024;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "K") == 0) {
                    size = 1024;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "mB") == 0) {
                    size = 1000*1000;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "MB") == 0) {
                    size = 1000*1000;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "m") == 0) {
                    size = 1024*1024;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "M") == 0) {
                    size = 1024*1024;
                    jumpIteration = 1;
                }
                // Consideramos que não há compatibilidade com tamanhos iguais ou superiores ao GB.
                else {
                    return 0;
                }
            }
            arguments->blockSize = size;
        }
        else if (strstr(argv[i], "--block-size=") != NULL) {
            int size;
            if (sscanf(argv[i], "--block-size=%d", &size) != 1) {
                // verificar os caracteres compatíveis e converter esses caracteres para inteiro
                char* sizeString = malloc(2*sizeof(char));
                if (sscanf(argv[i], "--block-size=%s", sizeString) != 1) {
                    return 0;
                }
                if (strcmp(sizeString, "kB") == 0) {
                    size = 1000;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "KB") == 0) {
                    size = 1000;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "k") == 0) {
                    size = 1024;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "K") == 0) {
                    size = 1024;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "mB") == 0) {
                    size = 1000*1000;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "MB") == 0) {
                    size = 1000*1000;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "m") == 0) {
                    size = 1024*1024;
                    jumpIteration = 1;
                }
                else if (strcmp(sizeString, "M") == 0) {
                    size = 1024*1024;
                    jumpIteration = 1;
                }
                // Consideramos que não há compatibilidade com tamanhos iguais ou superiores ao GB.
                else {
                    return 0;
                }
            }
            arguments->blockSize = size;
        }
        else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--count-links") == 0) {
            arguments->countLinks = 1;
            // Esta condição está aqui porque os argumentos podem ser repetidos
        }
        else if (strcmp(argv[i], "-L") == 0 || strcmp(argv[i], "--dereference") == 0) {
            arguments->dereference = 1;
        }
        else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--separate-dirs") == 0) {
            arguments->separateDirs = 1;
        }
        else if (strstr(argv[i], "--max-depth=") != NULL) {
            int depth;
            if (sscanf(argv[i], "--max-depth=%d", &depth) != 1)
                return 0;
            arguments->maxDepth = depth;
        }
        else {
            printf("I'm quiting2!\n");
            return 0;
        }
    }
    return 1;
}

int main(int argc, char* argv[]) {

    if (argc < 2 || (strcmp(argv[1], "-l") != 0 && strcmp(argv[1], "--count-links") != 0)) {
        fprintf(stderr, "Usage: %s -l [path] [-a] [-b] [-B size] [-L] [-S] [--max-depth=N]\n", argv[0]);
        exit(1);
    }
    
    Arguments arguments;

    initializeArgumentsStruct(&arguments);

    if (!checkArguments(&arguments, argc, argv)) {
        fprintf(stderr, "Usage: %s -l [path] [-a] [-b] [-B size] [-L] [-S] [--max-depth=N]\n", argv[0]);
        exit(2);
    }

    printf("\nBLOCK SIZE: %d\n", arguments.blockSize);

}