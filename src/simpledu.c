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

/**
 * Inicializa a struct Arguments com os valores default.
 */
void initializeArgumentsStruct(Arguments* arguments) {
    arguments->all = 0;
    arguments->bytes = 0;
    arguments->blockSize = 0;
    arguments->countLinks = 1;
    arguments->dereference = 0;
    arguments->separateDirs = 0;
    arguments->maxDepth = 0;
}

/**
 * Verifica se os argumentos passados na linha de comandos estão corretos.
 * Retorna 1 se está tudo OK, 0 caso haja algum erro.
 */
int checkArguments(Arguments* arguments, int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0) {
            arguments->all = 1;
        }
        else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--bytes") == 0) {
            arguments->bytes = 1;
        }
        else if (strcmp(argv[i], "-B") == 0 || strcmp(argv[i], "--block-size=") == 0) {
            arguments->blockSize = 1;
            /* 
            --> Precisamos de verificar qual o número ou caracteres que vêm depois de -B, sendo que pode ou não
            haver espaços.
            --> O mesmo se aplica para a segunda condição do if, já que só funciona da forma "--block-size=N",
            sendo N o size; precisamos, portanto, de testar se argv[i] começa pela sub-string "--block-size=", 
            e verificar qual / quais o(s) algarismo(s) ou caracteres (kB, K, MB, etc.) vêm a seguir ao "=" 
            */
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
        else if (strcmp(argv[i], "--max-depth=") == 0) {
            arguments->bytes = 1;
            // Temos que mudar esta condição para aceitar um inteiro a seguir ao igual, sem espaço.
        }
        else {
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

}