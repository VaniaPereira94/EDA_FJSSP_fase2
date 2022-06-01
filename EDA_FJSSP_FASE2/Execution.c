/**
 * @brief	Ficheiro com todas as funções relativas às execuções de operações
 * @file	executions.c
 * @author	Vânia Pereira
 * @email	a19264@alunos.ipca.pt
 * @date	2022
 * @Disciplina Estruturas de Dados Avançadas
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"


#pragma region trabalhar com listas

/**
* @brief	Criar nova execução
* @param	operationID		Identificador da operação
* @param	machineID		Identificador da máquina
* @param	runtime			Unidades de tempo necessárias para a execução da operação
* @return	Nova execução
*/
Execution* newExecution(int operationID, int machineID, int runtime)
{
	Execution* new = (Execution*)malloc(sizeof(Execution));
	if (new == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	new->operationID = operationID;
	new->machineID = machineID;
	new->runtime = runtime;
	new->next = NULL;

	return new;
}


/**
* @brief	Inserir nova execução no início da lista de execuções
* @param	head	Lista de execuções
* @param	new		Nova execução
* @return	Lista de execuções atualizada
*/
Execution* insertExecutionAtStart(Execution* head, Execution* new)
{
	if (searchExecution(head, new->operationID, new->machineID)) // não permitir inserir uma nova com o mesmo ID de operação e ID de máquina
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
* @brief	Inserir execução ordenada pelo ID da operação na lista de execuções
* @param	head	Lista de execuções
* @param	new		Nova execução
* @return	Lista de execuções atualizada
*/
Execution* insertExecutionByOperation(Execution* head, Execution* new)
{
	if (searchExecution(head, new->operationID, new->machineID)) // não permitir inserir uma nova com o mesmo ID de operação e ID de máquina
	{
		return NULL;
	}

	if (head == NULL)
	{
		head = new; // inserir no início se alista estiver vazia
	}
	else
	{
		Execution* aux = head;
		Execution* auxAnt = NULL;

		// enquanto que a atual tem o ID menor que a nova
		while (aux != NULL && aux->operationID < new->operationID)
		{
			auxAnt = aux;
			aux = aux->next;
		}

		if (auxAnt == NULL)
		{
			new->next = head;
			head = new; // inserir no meio
		}
		else
		{
			auxAnt->next = new;
			new->next = aux; // inserir no fim
		}
	}

	return head;
}

/**
* @brief	Atualizar as unidades de tempo necessárias para a execução de uma operação
* @param	head			Apontador para a lista de execuções
* @param	operationID		Identificador da operação
* @param	machineID		Identificador da máquina
* @param	runtime			Unidades de tempo
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool updateRuntime(Execution** head, int operationID, int machineID, int runtime)
{
	if (*head == NULL) // se lista está vazia
	{
		return false;
	}

	if (!searchExecution(*head, operationID, machineID)) // se não existir a execução para remover
	{
		return false;
	}


	Execution* aux = *head;

	while (aux != NULL)
	{
		if (aux->operationID == operationID && aux->machineID == machineID)
		{
			aux->runtime = runtime;
			return true;
		}
		aux = aux->next;
	}

	return false;
}


/**
* @brief	Remover execução pelo identificador da operação
* @param	head			Apontador para a lista de execuções
* @param	operationID		Identificador da operação
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool deleteExecutionByOperation(Execution** head, int operationID)
{
	if (*head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	Execution* aux = *head;
	Execution* auxAnt = NULL;

	if (aux != NULL && aux->operationID == operationID) { // se o elemento que será apagado é o primeiro da lista
		*head = aux->next;
		free(aux);
		return true;
	}

	while (aux != NULL && aux->operationID != operationID) // procurar o elemento a ser apagado
	{
		auxAnt = aux;
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
* @brief	Armazenar lista de execuções em ficheiro binário
* @param	fileName	Nome do ficheiro para armazenar a lista
* @param	head		Lista de execuções
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool writeExecutions(char fileName[], Execution* head)
{
	if (head == NULL) // se lista está vazia
	{
		return false;
	}

	FILE* file = NULL;

	if ((file = fopen(fileName, "wb")) == NULL) // se não foi possível abrir o ficheiro
	{
		return false;
	}

	Execution* current = head;
	FileExecution currentInFile; // é a mesma estrutura mas sem o campo *next, uma vez que esse campo não é armazenado no ficheiro

	while (current != NULL)
	{
		currentInFile.operationID = current->operationID;
		currentInFile.machineID = current->machineID;
		currentInFile.runtime = current->runtime;
		fwrite(&currentInFile, sizeof(FileExecution), 1, file); // guarda cada registo da lista no ficheiro

		current = current->next;
	}

	fclose(file);

	return true;
}


/**
* @brief	Ler lista de execuções de ficheiro binário
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de execuçõess
*/
Execution* readExecutions(char fileName[])
{
	FILE* file;

	if ((file = fopen(fileName, "rb")) == NULL) // se não foi possível abrir o ficheiro
	{
		return NULL;
	}

	Execution* head = NULL;
	Execution* current = NULL;
	FileExecution currentInFile; // é a mesma estrutura mas sem o campo *next, uma vez que esse campo não é armazenado no ficheiro

	while (fread(&currentInFile, sizeof(FileExecution), 1, file)) // lê todos os registos do ficheiro e guarda na lista
	{
		current = newExecution(currentInFile.operationID, currentInFile.machineID, currentInFile.runtime);
		head = insertExecutionAtStart(head, current);
	}

	fclose(file);

	return head;
}


/**
* @brief	Mostrar a lista de execuções na consola
* @param	head	Lista de execuções
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool displayExecutions(Execution* head)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	Execution* aux = head;

	while (aux != NULL)
	{
		printf("ID Operação: %d, ID Máquina: %d, Tempo de Execução: %d;\n", aux->operationID, aux->machineID, aux->runtime);
		aux = aux->next;
	}

	return true;
}

/**
* @brief	Procurar por uma execução na lista de execuções
* @param	head			Lista de execuções
* @param	operationID		Identificador da operação
* @param	machineID		Identificador da máquina
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
Execution* searchExecution(Execution* head, int operationID, int machineID)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return	NULL;
	}

	Execution* aux = head;

	while (aux != NULL)
	{
		if (aux->operationID == operationID && aux->machineID == machineID)
		{
			return aux;
		}
		aux = aux->next;
	}

	return NULL;
}


/**
* @brief	Procurar por uma execução através do identificador da operação, na lista de execuções
* @param	head			Lista de execuções
* @param	operationID		Identificador da operação
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
Execution* searchExecutionByOperation(Execution* head, int operationID)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	Execution* aux = head;

	while (aux != NULL)
	{
		if (aux->operationID == operationID)
		{
			return true;
		}
		aux = aux->next;
	}

	return false;
}



/**
* @brief	Ordenar lista de execuções por ordem crescente do identificador da operação
* @param	head			Lista de execuções
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
Execution* sortExecutionsByOperation(Execution* head)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return NULL;
	}

	Execution* aux = head;
	Execution* sorted = NULL;
	Execution* new = NULL;

	while (aux != NULL)
	{
		new = newExecution(aux->operationID, aux->machineID, aux->runtime);
		sorted = insertExecutionByOperation(sorted, new);
		aux = aux->next;
	}

	return sorted;
}


/**
* @brief	Obter a última execução de uma lista de execuções
* @param	head			Lista de execuções
* @return	Última execução da lista
*/
Execution* getLastExecution(Execution* head)
{
	if (head == NULL) // return NULL is list is empty cf (Captain girafe && learningC)
	{
		return NULL;
	}

	Execution* aux = head;

	while (aux->next != NULL) // check if next element is null then currentElement = next else return currentElement
	{
		aux = aux->next;
	}

	return aux;
}



#pragma endregion


