/**
 * @brief	Ficheiro principal da aplica��o, com menu e chamada de fun��es
 * @file	main.c
 * @author	V�nia Pereira
 * @email	a19264@alunos.ipca.pt
 * @date	2022
 * @Disciplina Estruturas de Dados Avan�adas
 *
 * -----------------
 *
 * @see https://github.com/VaniaPereira94/EDA_FJSSP_fase2
 *
*/

#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include "header.h"


/**
* @brief	Fun��o principal do programa
* @return	Resultado do programa na linha de comandos
*/
int main()
{
	setlocale(LC_ALL, "Portuguese"); // permitir caracteres especiais (portugueses)

	// listas
	Job* jobs = NULL;
	Operation* operations = NULL;
	Machine* machines = NULL;

	// tabela hash das execu��es
	ExecutionNode* executionsTable[HASH_TABLE_SIZE];


	// fase 2 da aplica��o

#pragma region funcionalidade 1: definir estruturas de dados din�micas
	printf("-  1. Definir estruturas de dados din�micas\n");

	// carregar listas em mem�ria
	jobs = loadJobs(jobs);
	machines = loadMachines(machines);
	operations = loadOperations(operations);

	// iniciar tabela hash das execu��es vazia
	*executionsTable = createExecutionsTable(executionsTable);

	// carregar tabela hash em mem�ria
	*executionsTable = loadExecutionsTable(executionsTable);
	printf("Dados carregados em mem�ria com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 2: armazenar e ler as estruturas em ficheiros
	printf("\n\n-  2. Armazenar e ler as estruturas em ficheiros\n");

	// guardar os dados em ficheiros
	writeJobs(JOBS_FILENAME_BINARY, jobs);
	writeMachines(MACHINES_FILENAME_BINARY, machines);
	writeOperations(OPERATIONS_FILENAME_BINARY, operations);
	writeExecutions_AtTable(EXECUTIONS_FILENAME_BINARY, executionsTable);

	printf("Dados exportados com sucesso!\n");

	// definir listas como NULL para ficarem vazias para ler os dados de ficheiros
	jobs = NULL;
	machines = NULL;
	operations = NULL;
	//*executionsTable = free_Execution_Table(executionsTable);

	// ler dados de ficheiros
	jobs = readJobs(JOBS_FILENAME_BINARY);
	machines = readMachine(MACHINES_FILENAME_BINARY);
	operations = readOperations(OPERATIONS_FILENAME_BINARY);
	*executionsTable = createExecutionsTable(executionsTable);
	*executionsTable = readExecutions_AtTable(EXECUTIONS_FILENAME_BINARY, executionsTable);

	printf("Dados importados com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 3: Inserir um trabalho
	printf("\n\n-  3. Inserir um trabalho\n");

	// inserir novo trabalho
	Job* job = NULL;
	job = newJob(9);
	jobs = insertJobAtStart(jobs, job);

	// guardar a nova inser��o em ficheiro
	writeJobs(JOBS_FILENAME_BINARY, jobs);
	printf("Novos dados exportados com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 4: Remover um trabalho
	printf("\n\n-  4. Remover um trabalho\n");

	// remover trabalho
	deleteJob(&jobs, 3);
	printf("trabalho removido com sucesso!\n");

	int operationDeleted = 0;

	do {
		// remover as opera��es associadas ao jobs
		operationDeleted = deleteOperation_ByJob(&operations, 3);
		printf("Opera��es associadas ao trabalho removida com sucesso!\n");

		// remover as execu��es associadas a cada opera��o
		deleteExecutions_ByOperation_AtTable(&executionsTable, operationDeleted);
		printf("Execu��es associadas � opera��o removidas com sucesso!\n");
	} while (operationDeleted != -1);
#pragma endregion

#pragma region funcionalidade 5: atualizar uma opera��o
	printf("\n\n-  5. Atualizar uma opera��o\n");

	// atualizar o tempo de uma execu��o de opera��o
	updateRuntime_ByOperation_AtTable(executionsTable, 4, 4, 10);
	printf("Operacao atualizada com sucesso!\n");

#pragma endregion

#pragma region funcionalidade 6: remover uma opera��o
	printf("\n\n-  6. Remover uma opera��o\n");

	// remover opera��o
	deleteOperation(&operations, 35);
	printf("Opera��o removida com sucesso!\n");

	// remover execu��es associadas � opera��o
	deleteExecutions_ByOperation_AtTable(&executionsTable, 35);
	printf("Execu��es associadas � opera��o removidas com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 7: inserir uma opera��o
	printf("\n\n-  7. Inserir uma opera��o\n");

	// inserir nova opera��o
	Operation* operation = NULL;
	operation = newOperation(39, 2, 8);
	operations = insertOperation_AtStart(operations, operation);

	// inserir nova execu��o de uma opera��o
	Execution* execution = NULL;
	execution = newExecution(39, 5, 17);
	*executionsTable = insertExecution_AtTable(executionsTable, execution);

	// guardar as novas inser��es em ficheiros
	writeOperations(OPERATIONS_FILENAME_BINARY, operations);
	//writeExecutions_AtTable(EXECUTIONS_FILENAME_BINARY, executionsTable);
	printf("Novos dados exportados com sucesso!\n");
#pragma endregion

}