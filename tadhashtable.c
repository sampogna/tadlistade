/*
 * tadhashtable.c 
 *  Dupla:
        Rafael Walace Sampogna
        Romildo Costa
*/


#include "tadhashtable.h"

 /* Operações sobre a tabela de dispersão */


/* CONSTRUTORA */


/* Aloca a struct descritora da tabela de dispersão e inicializa os campos tam e entradas */

int hash(Phashtable tab,Taluno elem){
	
	int tam = tab->tam ;
	int valor = (elem.matricula % tam);
	//printf ('%d' valor);
	return valor ;
	
}


Phashtable init_hashtab(int tam)
{
	
	//Plista vet = (Plista *) malloc(sizeof())
    Phashtable tabela = malloc(sizeof(Thashtable));
    tabela-> tam = tam;
    tabela-> entradas = (Plista *) malloc(tam * sizeof(Plista));
    for (int i = 0; i < tam; i++)
    {
		tabela->entradas[i] = init_lst();
		
	}
	return tabela;	
} 


/* DESTRUTORA */

/* Desaloca todas as áreas alocadas dinamicamente */

void destroy_hashtab(Phashtable tab)
{
	int tam;
	tam = tab->tam;
	
	 for (int i = 0; i < tam; i++)
    {
		
		del_lst(tab->entradas[i]);
		tab->entradas[i] = NULL;

	}
	
	free(tab->entradas);
	tab->entradas= NULL;
	free(tab);
	tab = NULL;	
	//printf("sou nulo");

}

/* Modificadoras */

void ins_item_hashtab (Phashtable tab, Taluno elem) 
{
	 int  valorhash;
	 valorhash = hash(tab,elem);
	 insert_ord_lst(tab->entradas[valorhash],elem);
	 
	
}

void del_item_hashtab (Phashtable tab, Taluno elem)
{
	int  valorhash;
	valorhash = hash(tab,elem);
	del_info_lst(tab->entradas[valorhash],elem);
	
}


/* PERSISTÊNCIA */

Phashtable load_hashtab(FILE * arq)
{

	/*
		Forma de leitura:
		* 1° tamanho da  tabela
		* 
		* Dados do Alunos organizados dessa forma
			1- Matricula
			2- Nome
			3- Turma
			4- Email
	*/
	
	int tam;
	fscanf(arq, "%d\n", &(tam));
	Phashtable tab = init_hashtab(tam);
	Taluno aluno;

	while( !feof(arq) )
	{
		fscanf(arq, "%d\n", &(aluno.matricula));
		fscanf(arq, "%[^\n]s", aluno.nome);
		fscanf(arq, "\n%c\n", &(aluno.turma));
		fscanf(arq, "%s\n", aluno.email);
		ins_item_hashtab (tab, aluno);
	}

	//fclose(arq);

	return tab;

}
void save_hashtab(Phashtable tab, FILE * arq)
{
	
	int tam;
	tam = tab->tam;
	fprintf(arq, "%d\n", (tam));
		
	for (int i = 0; i < tam; i++)
	{	if ( tab->entradas[i] != NULL )
		{
			save_lst(tab->entradas[i],arq);
		}
	}
}

/* ANALISADORAS */


int in_item_hashtab(Phashtable tab, Taluno elem)
{
	 int  valorhash;
	 valorhash = hash(tab,elem);
	 if (in_lst(tab->entradas[valorhash],elem) == 1)
	 {
		 return 1; // Achou o elemento, retorna true.
	 }
	return 0;	
	
}


int index_hash(Phashtable tab, Taluno pessoa)
{
	Pno aux;
	int pos = 0;
	int  valorhash;
	valorhash = hash(tab,pessoa);


	if ( (tab->entradas[valorhash]) != NULL )
	{
		if ( len_lst(tab->entradas[valorhash]) > 0 )
		{
			aux = (tab->entradas[valorhash])->prim;
			while ( aux != NULL )
			{
				if ( alunocmp(pessoa, aux->aluno) == 1 )
				{
					return pos;
				}
				pos++;
				aux = aux->prox;
			}

		}
	}
	/* Retorna -1 se o no com info de valor 'elem' nao for encontrado */
	return -1; 



}



int get_item_hashtab(Phashtable tab, Paluno elem)
{
	//Taluno aux;
	//aux.matricula = (elem->matricula);
	//strcpy(aux.nome, elem->nome);
	//aux.turma =(elem->turma);
	//strcpy(aux.email,elem->email);
	
	Taluno aux;
	int pos;
	aux.matricula = elem->matricula;
	
	int  valorhash;
	valorhash = hash(tab, aux );
	//printf("\n%d\n", valorhash);
	
	//if(in_lst_matricula(tab->entradas[valorhash], elem->matricula)){
	
	pos = index_lst_matricula(tab->entradas[valorhash], aux.matricula);
	
	if( pos != -1 ) {
		//strcpy(string_destino, string_origem);
		
		get_pos_lst(tab->entradas[valorhash], pos, elem);
		
		//strcpy(elem->nome, )
		return 1;
	}
	
	return 0;




}
