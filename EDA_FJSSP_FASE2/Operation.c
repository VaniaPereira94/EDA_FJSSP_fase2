/**
 * @brief	Ficheiro com todas as funções relativas às operações
 * @file	operations.c
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
* @brief	Criar nova operação
* @param	id			Identificador da operação
* @param	jobID		Identificador do trabalho
* @param	position	Posição da operação relativamente ao trabalho
* @return	Nova operação
*/
Operation* newOperation(int id, int jobID)
{
	Operation* new = (Operation*)malloc(sizeof(Operation));
	if (new == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	new->id = id;
	new->jobID = jobID;
	new->next = NULL;

	return new;
}


/**
* @brief	Inserir nova operação no início da lista de operações
* @param	head	Lista de operações
* @param	new		Nova operação
* @return	Lista de operações atualizada
*/
Operation* insertOperation_AtStart(Operation* head, Operation* new)
{
	if (searchOperation(head, new->id)) // não permitir inserir uma nova com o mesmo ID
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
* @brief	Remover uma operação da lista de operações
* @param	head	Apontador para a lista de operações
* @param	id		Identificador da operação
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool deleteOperation(Operation** head, int id)
{
	if (*head == NULL)
	{
		return false;
	}

	Operation* aux = *head;
	Operation* auxAnt = NULL;

	if (aux != NULL && aux->id == id) { // se o elemento que será apagado é o primeiro da lista
		*head = aux->next;
		free(aux);
		return true;
	}

	while (aux != NULL && aux->id != id) // procurar o elemento a ser apagado
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
* @brief	Remover operação pelo identificador do trabalho
* @param	head			Apontador para a lista de operações
* @param	jobID			Identificador do trabalho
* @return	Inteiro com o identificador da operação removida
*/
int deleteOperation_ByJob(Operation** head, int jobID)
{
	if (*head == NULL) // se a lista estiver vazia
	{
		return -1;
	}

	Operation* aux = *head;
	Operation* auxAnt = NULL;
	int operationDeleted = 0;

	if (aux != NULL && aux->jobID == jobID) { // se o elemento que será apagado é o primeiro da lista
		operationDeleted = aux->id;
		*head = aux->next;
		free(aux);

		return operationDeleted;
	}

	while (aux != NULL && aux->jobID != jobID) // procurar o elemento a ser apagado
	{
		auxAnt = aux;
		aux = aux->next;
	}

	if (aux == NULL) // se o elemento não foi encontrado
	{
		return -1;
	}

	operationDeleted = aux->id;
	auxAnt->next = aux->next; // desassociar o elemento da lista
	free(aux);

	return operationDeleted;
}


/**
* @brief	Armazenar lista de operações em ficheiro binário
* @param	fileName	Nome do ficheiro para armazenar a lista
* @param	head		Lista de operações
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool writeOperations(char fileName[], Operation* head)
{
	if (head == NULL) // se lista está vazia
	{
		return false;
	}

	FILE* file = NULL;

	if ((file = fopen(fileName, "wb")) == NULL) // erro ao abrir o ficheiro
	{
		return false;
	}

	Operation* current = head;
	FileOperation currentInFile; // é a mesma estrutura mas sem o campo *next, uma vez que esse campo não é armazenado no ficheiro

	while (current != NULL)
	{
		currentInFile.id = current->id;
		currentInFile.jobID = current->jobID;

		fwrite(&currentInFile, sizeof(FileOperation), 1, file); // guarda cada registo da lista no ficheiro

		current = current->next;
	}

	fclose(file);

	return true;
}


/**
* @brief	Ler lista de operações de ficheiro binário
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de operações
*/
Operation* readOperations(char fileName[])
{
	FILE* file = NULL;

	if ((file = fopen(fileName, "rb")) == NULL) // erro ao abrir o ficheiro
	{
		return NULL;
	}

	Operation* head = NULL;
	Operation* current = NULL;
	FileOperation currentInFile; // é a mesma estrutura mas sem o campo *next, uma vez que esse campo não é armazenado no ficheiro

	while (fread(&currentInFile, sizeof(FileOperation), 1, file)) // lê todos os registos do ficheiro e guarda na lista
	{
		current = newOperation(currentInFile.id, currentInFile.jobID);
		head = insertOperation_AtStart(head, current);
	}

	fclose(file);

	return head;
}


/**
* @brief	Mostrar a lista de operações na consola
* @param	head	Lista de operações
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool displayOperations(Operation* head)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	Operation* aux = head;

	while (aux != NULL)
	{
		printf("ID: %d, ID Trabalho: %d\n", aux->id, aux->jobID);
		aux = aux->next;
	}

	return true;
}


/**
* @brief	Procurar por uma operação na lista de operações
* @param	head	Lista de operações
* @param	id		Identificador da operação
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool searchOperation(Operation* head, int id)
{
	if (head == NULL) // se lista está vazia
	{
		return false;
	}

	Operation* aux = head;

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


/**
* @brief	Procurar por uma operação através do identificador do trabalho, na lista de operações
* @param	head			Lista de operações
* @param	jobID			Identificador do trabalho
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool searchOperation_ByJob(Operation* head, int jobID)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	Operation* aux = head;

	while (aux != NULL)
	{
		if (aux->jobID == jobID)
		{
			return true;
		}
		aux = aux->next;
	}

	return false;
}


/**
* @brief	Obter uma operação da lista de operações
* @param	head	Lista de operações
* @param	id		Identificador da operação
* @return	Operação encontrada (ou NULL se não encontrou)
*/
Operation* getOperation(Operation* head, int id)
{
	if (head == NULL) // se lista está vazia
	{
		return NULL;
	}

	Operation* aux = head;

	while (aux != NULL)
	{
		if (aux->id == id)
		{
			Operation* operation = newOperation(aux->id, aux->jobID); // criar cópia da operação
			return operation;
		}
		aux = aux->next;
	}

	return NULL;
}


/**
* @brief	Obter o mínimo de tempo necessário para completo um trabalho e as respetivas execuções
* @param	operations		Lista de operações
* @param	executions		Lista de execuções
* @param	jobID			Identificador do trabalho
* @param	minExecutions	Apontador para a lista de execuções a ser devolvida, relativamente ao tempo mínimo
* @return	Quantidade de tempo
*/
int getMinTimeToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** minExecutions)
{
	if (operations == NULL || executions == NULL) // se as listas estiverem vazias
	{
		return -1;
	}

	int time = 999;
	int counter = 0;

	Operation* auxOperation = operations;
	Execution* auxExecution = executions;
	Execution* minExecution = NULL;

	while (auxOperation != NULL) // percorrer lista de operações
	{
		if (auxOperation->jobID == jobID) // se encontrar o job relativo à operação
		{
			while (auxExecution != NULL) // percorrer lista de execução de operações
			{
				if (auxExecution->operationID == auxOperation->id) // se encontrar a execução de operação relativa à operação
				{
					// guardar execução de operação com menor tempo de utilização
					if (auxExecution->runtime < time)
					{
						time = auxExecution->runtime;
						minExecution = newExecution(auxExecution->operationID, auxExecution->machineID, auxExecution->runtime);
					}
				}

				auxExecution = auxExecution->next;
			}

			*minExecutions = insertExecutionAtStart(*minExecutions, minExecution);

			// repor lista percorrida (currentExecution), para que se for necessário voltar a percorrer o while da execução de operações de novo
			auxExecution = NULL;
			auxExecution = executions;
			counter += time; // acumular o tempo de utilização de cada execução de operação
			time = 999; // resetar tempo para a próxima iteração

		}

		auxOperation = auxOperation->next;
	}

	return counter;
}


/**
* @brief	Obter o máximo de tempo necessário para completo um trabalho e as respetivas execuções
* @param	operations		Lista de operações
* @param	executions		Lista de execuções
* @param	jobID			Identificador do trabalho
* @param	maxExecutions	Apontador para a lista de execuções a ser devolvida, relativamente ao tempo máximo
* @return	Quantidade de tempo
*/
int getMaxTimeToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** maxExecutions)
{
	if (operations == NULL || executions == NULL) // se as listas estiverem vazias
	{
		return -1;
	}

	int time = 0;
	int counter = 0;

	Operation* auxOperation = operations;
	Execution* auxExecution = executions;
	Execution* maxExecution = NULL;

	while (auxOperation != NULL) // percorrer lista de operações
	{
		if (auxOperation->jobID == jobID) // se encontrar o job relativo à operação
		{
			while (auxExecution != NULL) // percorrer lista de execução de operações
			{
				if (auxExecution->operationID == auxOperation->id) // se encontrar a execução de operação relativa à operação
				{
					// guardar execução de operação com maior tempo de utilização
					if (auxExecution->runtime > time)
					{
						time = auxExecution->runtime;
						maxExecution = newExecution(auxExecution->operationID, auxExecution->machineID, auxExecution->runtime);
					}
				}

				auxExecution = auxExecution->next;
			}

			*maxExecutions = insertExecutionAtStart(*maxExecutions, maxExecution);

			// repor lista percorrida (currentExecution), para que se for necessário voltar a percorrer o while da execução de operações de novo
			auxExecution = NULL;
			auxExecution = executions;
			counter += time; // acumular o tempo de utilização de cada execução de operação
			time = 0; // resetar tempo de utilização para a próxima iteração

		}

		auxOperation = auxOperation->next;
	}

	return counter;
}

/**
* @brief	Obter a média de tempo necessário para completar uma operação, considerando todas as alternativas possíveis
* @param	head			Lista de execuções
* @param	operationID		Identificador da operação
* @return	Valor da média de tempo
*/
float getAverageTimeToCompleteOperation(Execution* head, int operationID)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return -1.0f;
	}

	int sum = 0;
	float average = 0;
	float numberOfExecutions = 0;

	Execution* aux = head;

	while (aux != NULL)
	{
		if (aux->operationID == operationID) // se encontrar a execução de operação relativa à operação
		{
			sum += aux->runtime;
			numberOfExecutions++;
		}
		aux = aux->next;
	}

	if (numberOfExecutions > 0) // para não permitir divisão por 0
	{
		average = sum / numberOfExecutions;
	}

	return average;
}