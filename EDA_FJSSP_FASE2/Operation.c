/**
 * @brief	Ficheiro com todas as fun��es relativas �s opera��es
 * @file	operations.c
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
* @brief	Criar nova opera��o
* @param	id			Identificador da opera��o
* @param	jobID		Identificador do trabalho
* @param	position	Posi��o da opera��o relativamente ao trabalho
* @return	Nova opera��o
*/
Operation* newOperation(int id, int jobID)
{
	Operation* new = (Operation*)malloc(sizeof(Operation));
	if (new == NULL) // se n�o houver mem�ria para alocar
	{
		return NULL;
	}

	new->id = id;
	new->jobID = jobID;
	new->next = NULL;

	return new;
}


/**
* @brief	Inserir nova opera��o no in�cio da lista de opera��es
* @param	head	Lista de opera��es
* @param	new		Nova opera��o
* @return	Lista de opera��es atualizada
*/
Operation* insertOperation_AtStart(Operation* head, Operation* new)
{
	if (searchOperation(head, new->id)) // n�o permitir inserir uma nova com o mesmo ID
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
* @brief	Remover uma opera��o da lista de opera��es
* @param	head	Apontador para a lista de opera��es
* @param	id		Identificador da opera��o
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool deleteOperation(Operation** head, int id)
{
	if (*head == NULL)
	{
		return false;
	}

	Operation* aux = *head;
	Operation* auxAnt = NULL;

	if (aux != NULL && aux->id == id) { // se o elemento que ser� apagado � o primeiro da lista
		*head = aux->next;
		free(aux);
		return true;
	}

	while (aux != NULL && aux->id != id) // procurar o elemento a ser apagado
	{
		auxAnt = aux;
		aux = aux->next;
	}

	if (aux == NULL) // se o elemento n�o foi encontrado
	{
		return false;
	}

	auxAnt->next = aux->next; // desassociar o elemento da lista
	free(aux);

	return true;
}

/**
* @brief	Remover opera��o pelo identificador do trabalho
* @param	head			Apontador para a lista de opera��es
* @param	jobID			Identificador do trabalho
* @return	Inteiro com o identificador da opera��o removida
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

	if (aux != NULL && aux->jobID == jobID) { // se o elemento que ser� apagado � o primeiro da lista
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

	if (aux == NULL) // se o elemento n�o foi encontrado
	{
		return -1;
	}

	operationDeleted = aux->id;
	auxAnt->next = aux->next; // desassociar o elemento da lista
	free(aux);

	return operationDeleted;
}


/**
* @brief	Armazenar lista de opera��es em ficheiro bin�rio
* @param	fileName	Nome do ficheiro para armazenar a lista
* @param	head		Lista de opera��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeOperations(char fileName[], Operation* head)
{
	if (head == NULL) // se lista est� vazia
	{
		return false;
	}

	FILE* file = NULL;

	if ((file = fopen(fileName, "wb")) == NULL) // erro ao abrir o ficheiro
	{
		return false;
	}

	Operation* current = head;
	FileOperation currentInFile; // � a mesma estrutura mas sem o campo *next, uma vez que esse campo n�o � armazenado no ficheiro

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
* @brief	Ler lista de opera��es de ficheiro bin�rio
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de opera��es
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
	FileOperation currentInFile; // � a mesma estrutura mas sem o campo *next, uma vez que esse campo n�o � armazenado no ficheiro

	while (fread(&currentInFile, sizeof(FileOperation), 1, file)) // l� todos os registos do ficheiro e guarda na lista
	{
		current = newOperation(currentInFile.id, currentInFile.jobID);
		head = insertOperation_AtStart(head, current);
	}

	fclose(file);

	return head;
}


/**
* @brief	Mostrar a lista de opera��es na consola
* @param	head	Lista de opera��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
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
* @brief	Procurar por uma opera��o na lista de opera��es
* @param	head	Lista de opera��es
* @param	id		Identificador da opera��o
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool searchOperation(Operation* head, int id)
{
	if (head == NULL) // se lista est� vazia
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
* @brief	Procurar por uma opera��o atrav�s do identificador do trabalho, na lista de opera��es
* @param	head			Lista de opera��es
* @param	jobID			Identificador do trabalho
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
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
* @brief	Obter uma opera��o da lista de opera��es
* @param	head	Lista de opera��es
* @param	id		Identificador da opera��o
* @return	Opera��o encontrada (ou NULL se n�o encontrou)
*/
Operation* getOperation(Operation* head, int id)
{
	if (head == NULL) // se lista est� vazia
	{
		return NULL;
	}

	Operation* aux = head;

	while (aux != NULL)
	{
		if (aux->id == id)
		{
			Operation* operation = newOperation(aux->id, aux->jobID); // criar c�pia da opera��o
			return operation;
		}
		aux = aux->next;
	}

	return NULL;
}


/**
* @brief	Obter o m�nimo de tempo necess�rio para completo um trabalho e as respetivas execu��es
* @param	operations		Lista de opera��es
* @param	executions		Lista de execu��es
* @param	jobID			Identificador do trabalho
* @param	minExecutions	Apontador para a lista de execu��es a ser devolvida, relativamente ao tempo m�nimo
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

	while (auxOperation != NULL) // percorrer lista de opera��es
	{
		if (auxOperation->jobID == jobID) // se encontrar o job relativo � opera��o
		{
			while (auxExecution != NULL) // percorrer lista de execu��o de opera��es
			{
				if (auxExecution->operationID == auxOperation->id) // se encontrar a execu��o de opera��o relativa � opera��o
				{
					// guardar execu��o de opera��o com menor tempo de utiliza��o
					if (auxExecution->runtime < time)
					{
						time = auxExecution->runtime;
						minExecution = newExecution(auxExecution->operationID, auxExecution->machineID, auxExecution->runtime);
					}
				}

				auxExecution = auxExecution->next;
			}

			*minExecutions = insertExecutionAtStart(*minExecutions, minExecution);

			// repor lista percorrida (currentExecution), para que se for necess�rio voltar a percorrer o while da execu��o de opera��es de novo
			auxExecution = NULL;
			auxExecution = executions;
			counter += time; // acumular o tempo de utiliza��o de cada execu��o de opera��o
			time = 999; // resetar tempo para a pr�xima itera��o

		}

		auxOperation = auxOperation->next;
	}

	return counter;
}


/**
* @brief	Obter o m�ximo de tempo necess�rio para completo um trabalho e as respetivas execu��es
* @param	operations		Lista de opera��es
* @param	executions		Lista de execu��es
* @param	jobID			Identificador do trabalho
* @param	maxExecutions	Apontador para a lista de execu��es a ser devolvida, relativamente ao tempo m�ximo
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

	while (auxOperation != NULL) // percorrer lista de opera��es
	{
		if (auxOperation->jobID == jobID) // se encontrar o job relativo � opera��o
		{
			while (auxExecution != NULL) // percorrer lista de execu��o de opera��es
			{
				if (auxExecution->operationID == auxOperation->id) // se encontrar a execu��o de opera��o relativa � opera��o
				{
					// guardar execu��o de opera��o com maior tempo de utiliza��o
					if (auxExecution->runtime > time)
					{
						time = auxExecution->runtime;
						maxExecution = newExecution(auxExecution->operationID, auxExecution->machineID, auxExecution->runtime);
					}
				}

				auxExecution = auxExecution->next;
			}

			*maxExecutions = insertExecutionAtStart(*maxExecutions, maxExecution);

			// repor lista percorrida (currentExecution), para que se for necess�rio voltar a percorrer o while da execu��o de opera��es de novo
			auxExecution = NULL;
			auxExecution = executions;
			counter += time; // acumular o tempo de utiliza��o de cada execu��o de opera��o
			time = 0; // resetar tempo de utiliza��o para a pr�xima itera��o

		}

		auxOperation = auxOperation->next;
	}

	return counter;
}

/**
* @brief	Obter a m�dia de tempo necess�rio para completar uma opera��o, considerando todas as alternativas poss�veis
* @param	head			Lista de execu��es
* @param	operationID		Identificador da opera��o
* @return	Valor da m�dia de tempo
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
		if (aux->operationID == operationID) // se encontrar a execu��o de opera��o relativa � opera��o
		{
			sum += aux->runtime;
			numberOfExecutions++;
		}
		aux = aux->next;
	}

	if (numberOfExecutions > 0) // para n�o permitir divis�o por 0
	{
		average = sum / numberOfExecutions;
	}

	return average;
}