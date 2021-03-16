/* Dupla:
        Rafael Walace Sampogna
        Romildo Costa
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



typedef struct aluno {

  int matricula; /* chave */

  char nome[81];

  char turma;

  char email[41];

} Taluno, * Paluno;

typedef struct no{
	Taluno aluno;
	struct no * ante;
	struct no * prox;
} Tno, * Pno ;
	
typedef struct {
	Tno * prim;
	Tno * ulti;
	int tam;
} Tlista, * Plista;


Plista init_lst(void); 

/* Fçs principais */

int len_lst(Plista lst);

int in_lst(Plista lst, Taluno pessoa);

int in_lst_matricula(Plista lst, int matricula);

int empty_lst(Plista lst);

void print_lst(Plista lst);

void print_reverse_lst(Plista lst);
  
void append_lst(Plista lst, Taluno pessoa);

void insert_lst(Plista lst, int pos, Taluno pessoa);

void del_ult_lst(Plista lst);

void del_lst(Plista lst);

Plista load_lst(FILE * arq);

void save_lst(Plista lst, FILE * arq);

void del_pos_lst(Plista lst, int pos);

void del_info_lst(Plista lst, Taluno pessoa); 

int index_lst(Plista lst, Taluno pessoa);

int index_lst_matricula(Plista lst, int matricula);

void get_pos_lst (Plista lst, int pos, Paluno pessoa);

void insert_ord_lst(Plista lst, Taluno pessoa);

/* End - Fçs principais */

/* Fçs auxiliares */

int alunocmp(Taluno aluno1, Taluno aluno2);

/* End - Fçs auxiliares */
