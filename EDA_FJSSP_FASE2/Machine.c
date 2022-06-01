/**
 * @brief	Ficheiro com todas as fun��es relativas �s m�quinas
 * @file	machines.c
 * @author	V�nia Pereira
 * @email	a19264@alunos.ipca.pt
 * @date	2022
 * @Disciplina Estruturas de Dados Avan�adas
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"


/**
* @brief	Criar nova m�quina
* @param	id		Identificador da m�quina
* @param	isBusy	Booleano para se a m�quina est� ou n�o em utiliza��o
* @return	Nova m�quina
*/
Machine* newMachine(int id, bool isBusy)
{
	Machine* new = (Machine*)malloc(sizeof(Machine));
	if (new == NULL) // se n�o houver mem�ria para alocar
	{
		return NULL;
	}

	new->id = id;
	new->isBusy = isBusy;
	new->next = NULL;

	return new;
}


/**
* @brief	Inserir nova m�quina no in�cio da lista de m�quinas
* @param	head	Lista de m�quinas
* @param	new		Nova m�quina
* @return	Lista de m�quinas atualizada
*/
Machine* insertMachineAtStart(Machine* head, Machine* new)
{
	if (searchMachine(head, new->id)) // n�o permitir inserir uma nova com o mesmo ID
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
* @brief	Armazenar lista de m�quinas em ficheiro bin�rio
* @param	fileName	Nome do ficheiro para armazenar a lista
* @param	head		Lista de m�quinas
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeMachines(char* fileName, Machine* head) {
	FILE* fp;

	if (head == NULL) return false;

	if ((fp = fopen(fileName, "wb")) == NULL) return false;

	Machine* aux = head;
	MachineFile auxMachine;	//para gravar em ficheiro!

	while (aux) {		//while(aux!=NULL)

		auxMachine.id = aux->id;
		auxMachine.isBusy = aux->isBusy;
		fwrite(&auxMachine, sizeof(MachineFile), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}


/**
* @brief	Ler lista de m�quinas de ficheiro bin�rio
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de m�quinas
*/
Machine* readMachine(char* fileName)
{

	FILE* fp;
	Machine* head = NULL;
	Machine* aux;

	if ((fp = fopen(fileName, "rb")) == NULL) return NULL;

	//l� n registos no ficheiro
	MachineFile auxMachine;
	while (fread(&auxMachine, sizeof(MachineFile), 1, fp)) {

		aux = newMachine(auxMachine.id, auxMachine.isBusy);
		head = insertMachineAtStart(head, aux);
	}
	fclose(fp);
	return head;
}


/**
* @brief	Mostrar a lista de m�quinas na consola
* @param	head	Lista de m�quinas
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool displayMachines(Machine* head)
{
	if (head == NULL) // se lista est� vazia
	{
		return false;
	}

	Machine* aux = head;

	while (aux != NULL)
	{
		printf("ID: %d, Ocupada?: %s;\n", aux->id, aux->isBusy ? "Sim" : "N�o");
		aux = aux->next;
	}

	return true;
}


/**
* @brief	Procurar por uma m�quina na lista de m�quinas
* @param	head	Lista de m�quinas
* @param	id		Identificador da m�quina
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool searchMachine(Machine* head, int id)
{
	if (head == NULL) // se lista est� vazia
	{
		return false;
	}

	Machine* aux = head;

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