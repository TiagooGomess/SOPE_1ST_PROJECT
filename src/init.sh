#!/bin/bash

export LOG_FILENAME=log.txt

gcc -Wall -o simpledu simpledu.c

./simpledu -l . -a -L # se correr este comando no terminal, a variável de ambiente fica LOG_FILENAME fica a NULL... Temos que ver como resolver isto.
