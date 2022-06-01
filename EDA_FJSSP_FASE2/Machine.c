/**
 * @brief	Ficheiro com todas as funções relativas às máquinas
 * @file	machines.c
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
* @brief	Criar nova máquina
* @param	id		Identificador da máquina
* @param	isBusy	Booleano para se a máquina está ou não em utilização
* @return	Nova máquina
*/
Machine* newMachine(int id, bool isBusy)
{
	Machine* new = (Machine*)malloc(sizeof(Machine));
	if (new == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	new->id = id;
	new->isBusy = isBusy;
	new->next = NULL;

	return new;
}


/**
* @brief	Inserir nova máquina no início da lista de máquinas
* @param	head	Lista de máquinas
* @param	new		Nova máquina
* @return	Lista de máquinas atualizada
*/
Machine* insertMachineAtStart(Machine* head, Machine* new)
{
	if (searchMachine(head, new->id)) // não permitir inserir uma nova com o mesmo ID
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
* @brief	Armazenar lista de máquinas em ficheiro binário
* @param	fileName	Nome do ficheiro para armazenar a lista
* @param	head		Lista de máquinas
* @return	Booleano para o resultado da função (se funcionou ou não)
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
* @brief	Ler lista de máquinas de ficheiro binário
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de máquinas
*/
Machine* readMachine(char* fileName)
{

	FILE* fp;
	Machine* head = NULL;
	Machine* aux;

	if ((fp = fopen(fileName, "rb")) == NULL) return NULL;

	//lê n registos no ficheiro
	MachineFile auxMachine;
	while (fread(&auxMachine, sizeof(MachineFile), 1, fp)) {

		aux = newMachine(auxMachine.id, auxMachine.isBusy);
		head = insertMachineAtStart(head, aux);
	}
	fclose(fp);
	return head;
}


/**
* @brief	Mostrar a lista de máquinas na consola
* @param	head	Lista de máquinas
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool displayMachines(Machine* head)
{
	if (head == NULL) // se lista está vazia
	{
		return false;
	}

	Machine* aux = head;

	while (aux != NULL)
	{
		printf("ID: %d, Ocupada?: %s;\n", aux->id, aux->isBusy ? "Sim" : "Não");
		aux = aux->next;
	}

	return true;
}


/**
* @brief	Procurar por uma máquina na lista de máquinas
* @param	head	Lista de máquinas
* @param	id		Identificador da máquina
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool searchMachine(Machine* head, int id)
{
	if (head == NULL) // se lista está vazia
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