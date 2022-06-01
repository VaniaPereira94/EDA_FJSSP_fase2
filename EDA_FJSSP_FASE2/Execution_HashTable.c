#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

#pragma region trabalhar com tabela hash

/**
* @brief	Criar tabela hash das execu��es vazia
* @param	table	Tabela hash das execu��es
* @return	Tabela hash das execu��es criada
*/
ExecutionNode** createExecutionsTable(ExecutionNode* table[])
{
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		table[i] = createExecutionNode();
	}

	return *table;
}


/**
* @brief	Criar n� vazio para uma posi��o da tabela hash das execu��es
* @return	N� vazio da tabela hash das execu��es criado
*/
ExecutionNode* createExecutionNode()
{
	ExecutionNode* node = malloc(sizeof(ExecutionNode));

	node->start = NULL;
	node->numberOfExecutions = 0;

	return node;
}


/**
* @brief	Gerar hash atrav�s de uma fun��o.
*			A fun��o � representada pelo resto da divis�o do identificador da opera��o pelo tamanho da tabela
* @param	operationID		Identificador da opera��o
* @return	Valor calculado pela fun��o hash
*/
int generateHash(int operationID)   //fun��o de hash
{
	return operationID % HASH_TABLE_SIZE;     //para ver qual o valor onde vai entrar a chave, temos que dividir o id pelo tamanho da tabale hash 13 

	//exemplo uma chave de 50, vai entrar na posi��o 80000
}


/**
* @brief	Inserir nova execu��o na tabela hash das execu��es, numa determinada posi��o
* @param	table	Tabela hash das execu��es
* @return	Tabela hash das execu��es atualizada
*/
ExecutionNode** insertExecution_AtTable(ExecutionNode* table[], Execution* new)
{
	int index = generateHash(new->operationID);

	table[index]->start = insertExecutionAtStart(table[index]->start, new);
	table[index]->numberOfExecutions++;

	return *table;
}


/**
* @brief	Atualizar as unidades de tempo necess�rias para a execu��o de uma opera��o na tabela hash
* @param	table			Tabela hash das execu��es
* @param	operationID		Identificador da opera��o
* @param	machineID		Identificador da m�quina
* @param	runtime			Unidades de tempo
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool updateRuntime_ByOperation_AtTable(ExecutionNode** table[], int operationID, int machineID, int runtime)
{
	ExecutionNode** current = table;

	int index = generateHash(operationID);
	bool updated = updateRuntime(&current[index]->start, operationID, machineID, runtime);

	return updated;
}


/**
* @brief	Remover todas as execu��es pelo identificador da opera��o na tabela
* @param	table			Tabela hash das execu��es
* @param	operationID		Identificador da opera��o
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool deleteExecutions_ByOperation_AtTable(ExecutionNode** table[], int operationID)
{
	ExecutionNode** current = table;

	int index = generateHash(operationID);
	if (index <= -1)
	{
		return false;
	}

	bool deleted = false;

	do
	{
		// enquanto que remover, significa que ainda existe opera��es e portanto continuar� a remover, at� remover todas
		deleted = deleteExecutionByOperation(&current[index]->start, operationID);

		if (deleted)
		{
			current[index]->numberOfExecutions--;
		}
	} while (deleted == true);

	return deleted;
}


/**
* @brief	Armazenar os registos de todas as listas de execu��es na tabela hash, em ficheiro bin�rio
* @param	fileName	Nome do ficheiro para armazenar os registos
* @param	head		Lista de execu��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeExecutions_AtTable(char fileName[], ExecutionNode* table[])
{
	if (table == NULL) // se tabela est� vazia
	{
		return false;
	}

	Execution* allList = NULL;
	Execution* last = NULL;

	bool written = false;

	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (i == 0)
		{
			allList = table[0]->start;
		}
		else
		{
			last = getLastExecution(allList);
			last->next = table[i]->start;
		}
	}

	written = writeExecutions(fileName, allList);

	return written;
}


/**
* @brief	Armazenar os registos de todas as listas de execu��es na tabela hash, em ficheiro bin�rio
* @brief	Ler de ficheiro bin�rio, os registos de todas as execu��es para a tabela hash
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Tabela hash de execu��ess
*/
ExecutionNode** readExecutions_AtTable(char fileName[], ExecutionNode* table[])
{
	FILE* file = NULL;

	if ((file = fopen(fileName, "rb")) == NULL) // erro ao abrir o ficheiro
	{
		return NULL;
	}

	Execution* execution = NULL;
	Execution* list = NULL;
	list = readExecutions(fileName);

	if (list == NULL) // erro ao ler dados do ficheiro
	{
		return NULL;
	}

	while (list != NULL) // enquanto que houver dados na lista, guarda-os na tabela
	{
		execution = newExecution(list->operationID, list->machineID, list->runtime);
		*table = insertExecution_AtTable(table, execution);

		list = list->next;
	}

	return *table;
}


/**
* @brief	Mostrar a tabela hash com as listas de execu��es na consola
* @param	table	Tabela hash das execu��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool displayExecutions_AtTable(ExecutionNode* table[])
{
	if (table == NULL)
	{
		return false;
	}

	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		printf("Lista %d - N�mero de elementos: %d\n", i + 1, table[i]->numberOfExecutions);
		displayExecutions
		(table[i]->start);
	}

	return true;
}


/**
* @brief	Procurar por uma execu��o na tabela hash
* @param	table			Tabela hash das execu��es
* @param	operationID		Identificador da opera��o
* @param	machineID		Identificador da m�quina
* @return	Execu��o encontrada ou retorna nulo se n�o encontrar
*/
Execution* searchExecution_AtTable(ExecutionNode* table[], int operationID, int machineID)
{
	if (table == NULL) // se a lista estiver vazia
	{
		return NULL;
	}

	int index = generateHash(operationID);
	Execution* search = searchExecution(table[index]->start, operationID, machineID);

	if (search == NULL) // se a lista estiver vazia
	{
		return NULL;
	}

	return search;
}

/**
* @brief	Libertar a tabela hash de execu��es da mem�ria
* @param	head	Lista de execu��es
* @return	Tabela hash libertada da mem�ria
*/



#pragma endregion
