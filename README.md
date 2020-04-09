# SOPE_1ST_PROJECT
First Project of SOPE (MIEIC 2nd year / 2nd semester)

#### NOTAS:
Para mudar o nome do log_file, temos que definir a variável de ambiente LOG_FILENAME antes de executar o programa (export LOG_FILENAME="nome_desejado.txt"). Caso essa variável não seja definida, o nome por default do log_file é "log.txt".

Sempre que se executar o programa num diretório que contenha o ficheiro log_file, o tamanho deste ficheiro e do diretório pai apresentado não estará correto, uma vez que o programa está sempre a escrever no ficheiro.

Ao compilar o programa com "gcc" ou "cc", é necessário que a opção -lm esteja ativa.

Relativamente à opção de CTRL^C é necessário executar em diretórios relativamente pequenos. Caso contrário o programa bloqueará. Aconselha-se a adição da opção sleep(1) na parte final da função main(). Infelizmente fizemos inúmeros testes onde a opção pudesse falhar e não conseguimos encontrar o erro para o qual os testes "grandes" falhassem.
