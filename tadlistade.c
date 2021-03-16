/* Dupla:
        Rafael Walace Sampogna
        Romildo Costa
 */

#include "tadlistade.h"

/* Corpo das fçs. */

Plista init_lst(){
    //Plista vet = (Plista *) malloc(sizeof())
    Plista cabecalho = malloc(sizeof(Tlista));
	if(cabecalho != NULL){
		//Alocado corretamente.
		cabecalho->prim = NULL;
		cabecalho->ulti = NULL;
		cabecalho->tam = 0;
	}

    return cabecalho;

} 

int len_lst(Plista lst)
{
    if( (lst == NULL) || (lst->tam == 0) ) 
    {
        return 0;
    }
    else {
        return lst->tam;
    }
}

int in_lst(Plista lst, Taluno pessoa)
{
	Pno aux;

	if(lst != NULL)
	{
		aux = lst->prim;
		while(aux != NULL)
		{
			if ( (alunocmp(aux->aluno, pessoa) == 1) )
				return 1; // Achou o elemento, retorna true.
			aux = aux->prox;
		}
	}
	return 0; //Se chegou a null nao achou e eh falso.
}

/* in_lst_matricula */

int in_lst_matricula(Plista lst, int matricula)
{
	Pno aux;

	if(lst != NULL)
	{
		aux = lst->prim;
		while(aux != NULL)
		{
			if ( matricula == aux->aluno.matricula )
				return 1; // Achou o elemento, retorna true.
			aux = aux->prox;
		}
	}
	return 0; //Se chegou a null nao achou e eh falso.
}

/* End - in_lst_matricula */

int empty_lst(Plista lst)
{
	if (lst != NULL)
		if (lst->tam == 0)
			return 1;
	return 0;
}

void print_lst(Plista lst)
{
	int i = 0;
	printf("\n");
	Pno aux = lst->prim;

	if(lst != NULL)
	{
		if(lst->tam != 0)
		{
			for(i=0; i< lst->tam; i++) 
			{
				printf("\nAluno %d\n", i+1);
				printf("Nome: %s\n", aux->aluno.nome);
				printf("Matricula: %d\n", aux->aluno.matricula);
				printf("Turma: %c\n", aux->aluno.turma);
				printf("Email: %s\n", aux->aluno.email);
				aux = aux->prox;

			}
		}
	}
}

void append_lst(Plista lst, Taluno pessoa) 
{
	Pno aux = malloc(sizeof(Tno));
	aux->prox = NULL;

	aux->aluno.matricula = pessoa.matricula;
	strcpy(aux->aluno.nome, pessoa.nome);
	aux->aluno.turma = pessoa.turma;
	strcpy(aux->aluno.email, pessoa.email);

	
	

	if(lst != NULL)
	{
		if(lst->tam == 0) 
		{
			//Lista nao tem elementos
			lst->ulti = aux;
			lst->prim = aux;
			aux->ante = NULL;
			lst->tam++;
		}
		else
		{
			aux->ante = lst->ulti;
			lst->ulti->prox = aux;
			lst->ulti = aux;
			lst->tam++;
		}
	}
}

void insert_lst(Plista lst, int pos, Taluno pessoa) 
{
	
	/*pré-condição: lst diferente de NULL
	pós-condição: se pos <=0 elem é 
					inserido na posição 0
					se pos >=n n=tamanho 
					elem é inserido na posição na
					se 0<pos<n elem é inserido em 
					uma posição 0<pos<n
	*/

	Pno novo = malloc(sizeof(Tno));
	strcpy(novo->aluno.nome, pessoa.nome);
	novo->aluno.turma = pessoa.turma;
	strcpy(novo->aluno.email, pessoa.email);
	novo->aluno.matricula = pessoa.matricula;

	


	if(lst != NULL) 
	{
		//condicoes de pos de insercao
		if(pos <=0)
		{
			//Insere na 0
			if(lst->tam == 0)
			{
				lst->ulti = novo;
				lst->prim = novo;
				novo->ante = NULL;
				lst->tam++;
			}
			else
			{
				lst->prim->ante = novo;
				novo->prox = lst->prim;
				lst->prim = novo;
				novo->ante = NULL;
				lst->tam++;
			}
		}
		else if(pos >= lst->tam)
		{
			novo->ante = lst->ulti;
			lst->ulti->prox = novo;
			lst->ulti = novo;
			lst->tam++;
		}
		else if (pos < lst->tam)
		{
			if(lst->tam == 0)
			{
				novo->ante = lst->ulti;
				lst->ulti->prox = novo;
				lst->ulti = novo;
				lst->tam++;
			}
			else {
				Pno auxAnt = lst->prim;
				Pno auxProx = lst->prim;
				int count = 0;
				while(count < pos - 1)
				{
					auxAnt = auxAnt->prox;
					auxProx = auxProx->prox;
					count++;
				}
				auxProx = auxProx->prox;
				auxAnt->prox = novo;
				auxProx->ante = novo;
				novo->ante = auxAnt;
				novo->prox = auxProx;
				lst->tam++;
			}
		}

	}
}
void del_ult_lst(Plista lst)
{
	Pno aux;

	if(lst != NULL)
	{
		if (len_lst(lst) > 0)
		{
			aux = lst->ulti;
			if(len_lst(lst) == 1)
			{
				lst->ulti = NULL;
				lst->prim = NULL;
			}
			else 
			{
				aux = lst->ulti;
				lst->ulti = lst->ulti->ante;
				lst->ulti->prox = NULL;
			}
			lst->tam--;
			free(aux);
		}
	}
}

void del_lst(Plista lst)
{
	if (lst != NULL) {
		while (len_lst(lst) > 0)  {
			del_ult_lst(lst);
		}
		free(lst);
	}
}

Plista load_lst(FILE * arq)
{

	/*
		Forma de leitura: 
			1- Matricula
			2- Nome
			3- Turma
			4- Email
	*/

	Plista lst = init_lst();
	Taluno pessoa;

	while( !feof(arq) )
	{
		fscanf(arq, "%d\n", &(pessoa.matricula));
		fscanf(arq, "%[^\n]s", pessoa.nome);
		fscanf(arq, "\n%c\n", &(pessoa.turma));
		fscanf(arq, "%s\n", pessoa.email);
		append_lst(lst, pessoa);
	}

	fclose(arq);

	return lst;
}

void save_lst(Plista lst, FILE * arq)
{
	int count;
	Pno aux;

	if ( lst != NULL )
	{
		if ( len_lst(lst) > 0 )
		{
			aux = lst->prim;
			for ( count=0; count < len_lst(lst); count++ )
			{
				fprintf(arq, "%d\n", aux->aluno.matricula);
				fprintf(arq, "%s", aux->aluno.nome);
				fprintf(arq, "\n%c\n", aux->aluno.turma);
				fprintf(arq, "%s\n", aux->aluno.email);
				aux = aux->prox;
			}
		}
	}

	//fclose(arq);
}

void del_pos_lst(Plista lst, int pos)
{
	Pno aux;
	int count = 0;

	if (lst != NULL)
	{
		if ((pos >= 0) && (pos < len_lst(lst)))
		{
			aux = lst->prim;
			//Deleta o elemento de pos.
			while ( count < pos )
			{
				aux = aux->prox;
				count++;
				//Navegou ate a pos que desejamos deletar.
			}
			if ( pos == 0 )
			{
				if (len_lst(lst) == 1)
				{
					free(aux);
				}
				else 
				{
					lst->prim = aux->prox;
					//lst->prim->ante = NULL;
					free(aux);
				}
				lst->tam--;
				
			}
			else if(pos == (len_lst(lst) - 1))
			{
				del_ult_lst(lst);
			}
			else
			{
				aux->ante->prox = aux->prox;
				aux->prox->ante = aux->ante;
				free(aux); 
				lst->tam--;
			}
			
		}
	}
}

void del_info_lst(Plista lst, Taluno pessoa)
{
	int pos = 0, achou = 0;
	Pno aux;


	//Como so devemos excluir o primeiro, utilizaremos uma variavel 'booleana' para controlar os deletes

	if ( lst != NULL )
	{
		if ( len_lst(lst) > 0 )
		{
			aux = lst->prim;
			while ( ( aux != NULL ) || ( achou != 1 ) )
			{
				if ( alunocmp(pessoa, aux->aluno) == 1 )
				{
					del_pos_lst(lst, pos);
					achou = 1;
				}
				pos++;
				aux = aux->prox;
			}

		}
	}
}

int index_lst(Plista lst, Taluno pessoa)
{
	Pno aux;
	int pos = 0;


	if ( lst != NULL )
	{
		if ( len_lst(lst) > 0 )
		{
			aux = lst->prim;
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

int index_lst_matricula(Plista lst, int matricula)
{
	Pno aux;
	int pos = 0;


	if ( lst != NULL )
	{
		if ( len_lst(lst) > 0 )
		{
			aux = lst->prim;
			while ( aux != NULL )
			{
				if ( aux->aluno.matricula == matricula )
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



void get_pos_lst(Plista lst, int pos, Paluno pessoa)
{
	Pno aux;
	int count = 0;

	if ( lst != NULL )
	{
		if ( len_lst(lst) > 0 )
		{
			if ( ( pos >= 0 ) && ( pos < len_lst(lst) ) )
			{
				aux = lst->prim;
				while ( count < pos )
				{
					aux = aux->prox;
					count++;
				}
				
			}

		}
	}

	(pessoa->matricula) = aux->aluno.matricula;
	strcpy(pessoa->nome, aux->aluno.nome);
	(pessoa->turma) = aux->aluno.turma;
	strcpy(pessoa->email, aux->aluno.email);
}

void print_reverse_lst(Plista lst){
	
	int i = 0;
	printf("\n");
	Pno aux = lst->ulti;

	if(lst != NULL)
	{
		if(lst->tam != 0)
		{
			for(i=0; i< lst->tam; i++) 
			{
				printf("\nAluno %d\n", i+1);
				printf("Nome: %s\n", aux->aluno.nome);
				printf("Matricula: %d\n", aux->aluno.matricula);
				printf("Turma: %c\n", aux->aluno.turma);
				printf("Email: %s\n", aux->aluno.email);
				aux = aux->ante;

			}
		}
	}

}

void insert_ord_lst(Plista lst, Taluno pessoa)
{
	Pno novo = malloc(sizeof(Tno));
	novo->prox = NULL;
	novo->ante = NULL;

	novo->aluno.matricula = pessoa.matricula;
	strcpy(novo->aluno.nome, pessoa.nome);
	novo->aluno.turma = pessoa.turma;
	strcpy(novo->aluno.email, pessoa.email);

	if(lst != NULL)
	{
		if(lst->tam == 0) 
		{
			lst->ulti = novo;
			lst->prim = novo;
			novo->ante = NULL;
			lst->tam++;
		}
		else
		{
			if(lst->ulti->aluno.matricula < pessoa.matricula)
			{
				//Insere na ultima posicao
				novo->ante = lst->ulti;
				lst->ulti->prox = novo;
				lst->ulti = novo;
				lst->tam++;
			}
			else
			{
				Pno ante;
				Pno atual;
				ante = lst->prim;
				atual = lst->prim;
				
				while( (atual != NULL) && (atual->aluno.matricula < novo->aluno.matricula) )
				{
					ante = atual;
					atual = atual->prox;
				}
				if(atual->ante == NULL)//if(alunocmp(atual->aluno, lst->prim->aluno) == 1) 
				{
					//Inserir primeira posicao.
					novo->ante = NULL;
					lst->prim->ante = novo;
					novo->prox = lst->prim;
					lst->prim = novo;
				}
				else 
				{
					//Insere entre dois alunos.
					novo->prox = ante->prox;
					novo->ante = ante;
					ante->prox = novo;
					if(atual != NULL)
					{
						atual->ante = novo;
					}
				}
				lst->tam++;
			}
		}
		
		
	}
}

int alunocmp(Taluno aluno1, Taluno aluno2)
{
	int iguais = 1;
	if( aluno1.turma != aluno2.turma )
		iguais = 0;
	if( aluno1.matricula != aluno2.matricula )
		iguais = 0;
	if( strcmp(aluno1.nome, aluno2.nome) != 0 )
		iguais = 0;
	if( strcmp(aluno1.email, aluno2.email) != 0 )
		iguais = 0;

	return iguais;
}

/* End - Fçs auxiliares */
