/**
 * @brief	Ficheiro com todas as funções relativas aos trabalhos
 * @file	jobs.c
 * @author	Vânia Pereira
 * @email	a19264@alunos.ipca.pt
 * @date	2022
 * @Disciplina Estruturas de Dados Avançadas
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"


/**
* @brief	Criar novo trabalho
* @param	id	Identificador do trabalho
* @return	Novo trabalho
*/
Job* newJob(int id)
{
	Job* new = (Job*)malloc(sizeof(Job));
	if (new == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	new->id = id;
	new->next = NULL;

	return new;
}


/**
* @brief	Inserir novo trabalho no início da lista de trabalhos
* @param	head	Lista de trabalhos
* @param	new		Novo trabalho
* @return	Lista de trabalhos atualizada
*/
Job* insertJobAtStart(Job* head, Job* new)
{
	if (searchJob(head, new->id)) // não permitir inserir um novo com o mesmo ID
	{
		return NULL;
	}

	if (head == NULL) // se a lista estiver vazia
	{
		head = new;
	}
	else // se existir algum elemento na lista
	{
		new->next = head;
		head = new;
	}

	return head;
}


/**
* @brief	Remover um trabalho da lista de trabalhos
* @param	head	Apontador para a lista de trabalhos
* @param	id		Identificador do trabalho
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool deleteJob(Job** head, int id)   //aponta para o endereço de outro apontador
{

	if (*head == NULL)
	{
		return false;
	}

	Job* aux = *head;   //o aux começa em *head
	Job* auxAnt = NULL;

	if (aux != NULL && aux->id == id) { // se o elemento que será apagado é o primeiro da lista
		*head = aux->next;
		free(aux);
		return true;
	}

	while (aux != NULL && aux->id != id) // procurar o elemento a ser apagado
	{
		auxAnt = aux;       // o auxant na posição do aux e avanço o aux
		aux = aux->next;
	}

	if (aux == NULL) // se o elemento não foi encontrado
	{
		return false;
	}

	auxAnt->next = aux->next; // desassociar o elemento da lista
	free(aux);

	return true;
}


/**
* @brief	Armazenar lista de trabalhos em ficheiro binário
* @param	fileName	Nome do ficheiro para armazenar a lista
* @param	head		Lista de trabalhos
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool writeJobs(char* fileName, Job* h) {
	FILE* fp;

	if (h == NULL) return false;

	if ((fp = fopen(fileName, "wb")) == NULL) return false;

	Job* aux = h;
	JobFile auxJob;	//para gravar em ficheiro!

	while (aux) {		//while(aux!=NULL)

		auxJob.id = aux->id;

		fwrite(&auxJob, sizeof(JobFile), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}


/**
* @brief	Ler lista de trabalhos de ficheiro binário
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de trabalhos
*/
Job* readJobs(char* fileName)
{

	FILE* fp;
	Job* h = NULL;
	Job* aux;

	if ((fp = fopen(fileName, "rb")) == NULL) return NULL;

	//lê n registos no ficheiro
	JobFile auxJob;
	while (fread(&auxJob, sizeof(JobFile), 1, fp)) {

		aux = newJob(auxJob.id);
		h = insertJobAtStart(h, aux);   //inserir a lista na ficha
	}
	fclose(fp);
	return h;
}


/**
* @brief	Mostrar a lista de trabalhos na consola
* @param	head	Lista de trabalhos
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
void displayJob(Job* head) {
	Job* aux = head;
	while (aux) {		//mesmo que while (aux!=NULL)
		printf("ID: %d\n", aux->id);
		aux = aux->next;
	}
}


/**
* @brief	Procurar por um trabalho na lista de trabalhos
* @param	head	Lista de trabalhos
* @param	id		Identificador do trabalho
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool searchJob(Job* head, int id)
{
	if (head == NULL) // se lista está vazia
	{
		return false;
	}

	Job* aux = head;

	while (aux != NULL)
	{
		if (aux->id == id)
		{
			return true;
		}
		aux = aux->next;
	}

	return false;
}