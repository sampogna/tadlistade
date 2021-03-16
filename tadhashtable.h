/*
 * tadhashtable.h
 *  
 */


#include <stdio.h>
#include "tadlistade.h"

typedef struct hashtable {
  int tam; /* tamanho do vetor de Plista */
  Plista * entradas; /* vetor de Plista */
}Thashtable, * Phashtable;


/* CONSTRUTORA */


/* Aloca a struct descritora da tabela de dispersão e inicializa os campos tam e entradas */

Phashtable init_hashtab(int tam);

/* DESTRUTORA */


/* Desaloca todas as áreas alocadas dinamicamente */

void destroy_hashtab(Phashtable tab);

/* PERSISTÊNCIA */


/* Constrói uma tabela de dispersão a partir dos dados

   de um arquivo texto já aberto para leitura sequencial.

   Os dados do arquivo texto são:

   1) a primeira linha contém um valor inteiro que representa

   o tamanho da tabela.

   2) as próximas linhas contém os dados de um aluno na

        ordem que os campos foram declarados no Taluno */

Phashtable load_hashtab(FILE * arq);


/* Escreve em um arquivo texto de acesso sequencial os dados da tabela de dispersão

   tab. Os dados escritos devem ficar no mesmo formato dos dados no arquivo utilizada

   pela função load_hashtab. */

void save_hashtab(Phashtable tav, FILE * arq);



/* MODIFICADORAS */


/* Insere um elemento (Taluno) na tabela de acordo com

   sua chave (matrícula). A inserção do aluno na lista deve

   ser uma inserção ordenada pelo campo matrícula. */

void ins_item_hashtab (Phashtable tab, Taluno elem);

/* elimina o aluno da tabela de dispersão tab */

void del_item_hashtab (Phashtable tab, Taluno elem);


/* ANALISADORAS */


/* Recebe a tabela de dispersão tab e a chave de busca (matricula) no

   parâmetro elem. Se elem for encontrado na tabela de dispersão os campos

   do parâmetro elem são atualizados com os valores contidos na tabela e a

   função retorna 1, caso contrário elem permanece inalterado e a função retorna 0 */
int get_item_hashtab(Phashtable tab, Paluno elem);


/* Recebe a tabela de dispersão tab e um dado elem para busca (pelo campo matrícula)

   e retorna:

   - 1 (verdade) se elem pertencer a tab

   - 0 (falso) se elem não pertencer a tab
*/
int in_item_hashtab(Phashtable tab, Taluno elem);



/* auxiliares */

int index_hash(Phashtable tab, Taluno pessoa);

int hash(Phashtable tab,Taluno elem);
