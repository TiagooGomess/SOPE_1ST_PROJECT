#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>
#include <dirent.h> 
#include <errno.h>
#include <unistd.h>

#define PATH_MAX_LEN 256
#define FILENAME_MAX_LEN 64
#define DEFAULT_BLOCK_SIZE 1024

/**
 * Se um elemento do tipo int da struct não foi especificado nos argumentos da linha de comandos, fica
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
    char* path; /* caminho inicial (default = .) */
    char* log_filename; /* nome da variável de ambiente LOG_FILENAME */
} Arguments;

/**
 * Inicializa a struct Arguments com os valores default.
 */
void initializeArgumentsStruct(Arguments* arguments) {
    arguments->all = 0;
    arguments->bytes = 0;
    arguments->blockSize = DEFAULT_BLOCK_SIZE;
    arguments->countLinks = 1;
    arguments->dereference = 0;
    arguments->separateDirs = 0;
    arguments->maxDepth = INT_MAX;
    arguments->path = malloc(PATH_MAX_LEN + 1);
    arguments->path = ".";
    arguments->log_filename = malloc(FILENAME_MAX_LEN + 1);
    arguments->log_filename = "";
}

/**
 * Verifica se os caracteres do tamanho dos blocos são compatíveis (k, K, kB, KB, m, M, mB, MB)
 * Retorna o tamanho em bytes que os caracteres representam, e 0 caso os caracteres não sejam compatíteis.
 */
int checkCompatibleCharactersSize(int* size, char* sizeString) {
    if (strcmp(sizeString, "kB") == 0) {
        *size = 1000;
    }
    else if (strcmp(sizeString, "KB") == 0) {
        *size = 1000;
    }
    else if (strcmp(sizeString, "k") == 0) {
        *size = 1024;
    }
    else if (strcmp(sizeString, "K") == 0) {
        *size = 1024;
    }
    else if (strcmp(sizeString, "mB") == 0) {
        *size = 1000*1000;
    }
    else if (strcmp(sizeString, "MB") == 0) {
        *size = 1000*1000;
    }
    else if (strcmp(sizeString, "m") == 0) {
        *size = 1024*1024;
    }
    else if (strcmp(sizeString, "M") == 0) {
        *size = 1024*1024;
    }
    // Consideramos que não há compatibilidade com tamanhos iguais ou superiores ao GB.
    else {
        return 0;
    }
    return *size;
}

/**
 * Verifica se um determinado path é um diretório válido.
 * Retorna 1 caso seja diretório, 0 caso contrário.
 */
int isDirectory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}

/**
 * Verifica se os argumentos passados na linha de comandos estão corretos.
 * Retorna 1 se está tudo OK, 0 caso haja algum erro.
 */
int checkArguments(Arguments* arguments, int argc, char* argv[]) {
    arguments->log_filename = getenv("LOG_FILENAME");
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
                if (!checkCompatibleCharactersSize(&size, sizeString))
                    return 0;
            }
            jumpIteration = 1;
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
                if (!checkCompatibleCharactersSize(&size, sizeString))
                    return 0;
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
                if (!checkCompatibleCharactersSize(&size, sizeString))
                    return 0;
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
        else if (strcmp(argv[i], "-S") == 0 || strcmp(argv[i], "--separate-dirs") == 0) {
            arguments->separateDirs = 1;
        }
        else if (strstr(argv[i], "--max-depth=") != NULL) {
            int depth;
            if (sscanf(argv[i], "--max-depth=%d", &depth) != 1)
                return 0;
            arguments->maxDepth = depth;
        }
        else if (strstr(argv[i], ".") != NULL || strstr(argv[i], "/") != NULL) {
            // se passarmos ~ como path, é convertido automaticamente para "/home/user" 
            if (isDirectory(argv[i])) {
                arguments->path = argv[i];
            }
            else {
                fprintf(stderr, "\n%s is not a directory!\n\n", argv[i]);
                return 0;
            }
        }
        else {
            return 0;
        }
    }
    return 1;
}

/**
 * Converte de número de bytes para número de blocos, de acordo com o blockSize atual.
 * Retorna o número de blocos.
 */
int convertFromBytesToBlocks(int numBytes, int blockSize) { // ISTO NÃO ESTÁ BEM (COMPAREM COM O DU)
    return numBytes / blockSize;
}




int recursionCount = 0;

void executeRecursiveFunction(Arguments arguments) { // SHITTY FUNCTION WITHOUT FORKS AND VERY UGLY

    if (arguments.maxDepth <= recursionCount) {
        return;
    }

    DIR* dir;
    if ((dir = opendir(arguments.path)) == NULL) {
        perror(arguments.path);
        exit(4);
    }
    chdir(arguments.path);
    
    struct dirent *dentry;
    struct stat stat_entry;
    char filename[FILENAME_MAX_LEN];
    while ((dentry = readdir(dir)) != NULL) {

        filename[0] = '.';
        filename[1] = '/';
        filename[2] = '\0';

        stat(dentry->d_name, &stat_entry);
        if (arguments.bytes) { // mostrar o tamanho em bytes
            if (arguments.all) { // mostar também ficheiros regulares
                if (S_ISREG(stat_entry.st_mode)) {
                    printf("%-d\t%-s\n", (int)stat_entry.st_size, strcat(filename, dentry->d_name));
                }
            }
            if (S_ISDIR(stat_entry.st_mode) && (strcmp(dentry->d_name, ".") != 0) && (strcmp(dentry->d_name, "..") != 0)) {
                printf("%-d\t%-s\n", (int)stat_entry.st_size, strcat(filename, dentry->d_name));
                arguments.path = dentry->d_name;
               

                
                //printf("\n-------RECURSION---------\n");
                recursionCount++;
                executeRecursiveFunction(arguments);
            }
        }
        else { // mostrar o tamanho em blocos (CORRIGIR FUNÇÃO convertFromBytesToBlocks)
            if (arguments.all) { // mostar também ficheiros regulares
                if (S_ISREG(stat_entry.st_mode)) {
                    printf("%-d\t%-s\n", convertFromBytesToBlocks((int)stat_entry.st_size, arguments.blockSize), strcat(filename, dentry->d_name));
                }
            }
            if (S_ISDIR(stat_entry.st_mode) && (strcmp(dentry->d_name, ".") != 0) && (strcmp(dentry->d_name, "..") != 0)) {
                printf("%-d\t%-s\n", convertFromBytesToBlocks((int)stat_entry.st_size, arguments.blockSize), strcat(filename, dentry->d_name));
                arguments.path = dentry->d_name;

                
                //printf("\n-------RECURSION---------\n");
                recursionCount++;
                executeRecursiveFunction(arguments);
            }
        }
        
    } 
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

    // TESTED :)
    /*printf("\nBLOCK SIZE: %d\n", arguments.blockSize);
    printf("\nALL: %d\n", arguments.all);
    printf("\nBYTES: %d\n", arguments.bytes);
    printf("\nCOUNT LINKS: %d\n", arguments.countLinks);
    printf("\nDEREFERENCE: %d\n", arguments.dereference);
    printf("\nSEPARATE DIRS: %d\n", arguments.separateDirs);
    printf("\nMAX DEPTH: %d\n", arguments.maxDepth);
    printf("\nPATH: %s\n", arguments.path);
    printf("\nLOG_FILENAME: %s\n", arguments.log_filename);*/ /* antes de correr o programa, escrever o comando:
                                                                export LOG_FILENAME=log.txt */
    /*
    FILE* log_file;
    if (arguments.log_filename != NULL) { // criar o ficheiro de registo dos processos
        log_file = fopen(arguments.log_filename, "w");
    }
    else {
        fprintf(stderr, "\nMust set the ambient variable LOG_FILENAME!\n");
        //exit(3);
    }
    */

    
    executeRecursiveFunction(arguments);


    //fclose(log_file);
    exit(0);
}