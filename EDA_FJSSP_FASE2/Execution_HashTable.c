#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

#pragma region trabalhar com tabela hash

/**
* @brief	Criar tabela hash das execuções vazia
* @param	table	Tabela hash das execuções
* @return	Tabela hash das execuções criada
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
* @brief	Criar nó vazio para uma posição da tabela hash das execuções
* @return	Nó vazio da tabela hash das execuções criado
*/
ExecutionNode* createExecutionNode()
{
	ExecutionNode* node = malloc(sizeof(ExecutionNode));

	node->start = NULL;
	node->numberOfExecutions = 0;

	return node;
}


/**
* @brief	Gerar hash através de uma função.
*			A função é representada pelo resto da divisão do identificador da operação pelo tamanho da tabela
* @param	operationID		Identificador da operação
* @return	Valor calculado pela função hash
*/
int generateHash(int operationID)   //função de hash
{
	return operationID % HASH_TABLE_SIZE;     //para ver qual o valor onde vai entrar a chave, temos que dividir o id pelo tamanho da tabale hash 13 

	//exemplo uma chave de 50, vai entrar na posição 80000
}


/**
* @brief	Inserir nova execução na tabela hash das execuções, numa determinada posição
* @param	table	Tabela hash das execuções
* @return	Tabela hash das execuções atualizada
*/
ExecutionNode** insertExecution_AtTable(ExecutionNode* table[], Execution* new)
{
	int index = generateHash(new->operationID);

	table[index]->start = insertExecutionAtStart(table[index]->start, new);
	table[index]->numberOfExecutions++;

	return *table;
}


/**
* @brief	Atualizar as unidades de tempo necessárias para a execução de uma operação na tabela hash
* @param	table			Tabela hash das execuções
* @param	operationID		Identificador da operação
* @param	machineID		Identificador da máquina
* @param	runtime			Unidades de tempo
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool updateRuntime_ByOperation_AtTable(ExecutionNode** table[], int operationID, int machineID, int runtime)
{
	ExecutionNode** current = table;

	int index = generateHash(operationID);
	bool updated = updateRuntime(&current[index]->start, operationID, machineID, runtime);

	return updated;
}


/**
* @brief	Remover todas as execuções pelo identificador da operação na tabela
* @param	table			Tabela hash das execuções
* @param	operationID		Identificador da operação
* @return	Booleano para o resultado da função (se funcionou ou não)
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
		// enquanto que remover, significa que ainda existe operações e portanto continuará a remover, até remover todas
		deleted = deleteExecutionByOperation(&current[index]->start, operationID);

		if (deleted)
		{
			current[index]->numberOfExecutions--;
		}
	} while (deleted == true);

	return deleted;
}


/**
* @brief	Armazenar os registos de todas as listas de execuções na tabela hash, em ficheiro binário
* @param	fileName	Nome do ficheiro para armazenar os registos
* @param	head		Lista de execuções
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool writeExecutions_AtTable(char fileName[], ExecutionNode* table[])
{
	if (table == NULL) // se tabela está vazia
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
* @brief	Armazenar os registos de todas as listas de execuções na tabela hash, em ficheiro binário
* @brief	Ler de ficheiro binário, os registos de todas as execuções para a tabela hash
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Tabela hash de execuçõess
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
* @brief	Mostrar a tabela hash com as listas de execuções na consola
* @param	table	Tabela hash das execuções
* @return	Booleano para o resultado da função (se funcionou ou não)
*/
bool displayExecutions_AtTable(ExecutionNode* table[])
{
	if (table == NULL)
	{
		return false;
	}

	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		printf("Lista %d - Número de elementos: %d\n", i + 1, table[i]->numberOfExecutions);
		displayExecutions
		(table[i]->start);
	}

	return true;
}


/**
* @brief	Procurar por uma execução na tabela hash
* @param	table			Tabela hash das execuções
* @param	operationID		Identificador da operação
* @param	machineID		Identificador da máquina
* @return	Execução encontrada ou retorna nulo se não encontrar
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
* @brief	Libertar a tabela hash de execuções da memória
* @param	head	Lista de execuções
* @return	Tabela hash libertada da memória
*/



#pragma endregion
