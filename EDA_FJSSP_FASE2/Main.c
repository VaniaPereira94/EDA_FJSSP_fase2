/**
 * @brief	Ficheiro principal da aplicação, com menu e chamada de funções
 * @file	main.c
 * @author	Vânia Pereira
 * @email	a19264@alunos.ipca.pt
 * @date	2022
 * @Disciplina Estruturas de Dados Avançadas
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
* @brief	Função principal do programa
* @return	Resultado do programa na linha de comandos
*/
int main()
{
	setlocale(LC_ALL, "Portuguese"); // permitir caracteres especiais (portugueses)

	// listas
	Job* jobs = NULL;
	Operation* operations = NULL;
	Machine* machines = NULL;

	// tabela hash das execuções
	ExecutionNode* executionsTable[HASH_TABLE_SIZE];


	// fase 2 da aplicação

#pragma region funcionalidade 1: definir estruturas de dados dinâmicas
	printf("-  1. Definir estruturas de dados dinâmicas\n");

	// carregar listas em memória
	jobs = loadJobs(jobs);
	machines = loadMachines(machines);
	operations = loadOperations(operations);

	// iniciar tabela hash das execuções vazia
	*executionsTable = createExecutionsTable(executionsTable);

	// carregar tabela hash em memória
	*executionsTable = loadExecutionsTable(executionsTable);
	printf("Dados carregados em memória com sucesso!\n");
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

	// guardar a nova inserção em ficheiro
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
		// remover as operações associadas ao jobs
		operationDeleted = deleteOperation_ByJob(&operations, 3);
		printf("Operações associadas ao trabalho removida com sucesso!\n");

		// remover as execuções associadas a cada operação
		deleteExecutions_ByOperation_AtTable(&executionsTable, operationDeleted);
		printf("Execuções associadas à operação removidas com sucesso!\n");
	} while (operationDeleted != -1);
#pragma endregion

#pragma region funcionalidade 5: atualizar uma operação
	printf("\n\n-  5. Atualizar uma operação\n");

	// atualizar o tempo de uma execução de operação
	updateRuntime_ByOperation_AtTable(executionsTable, 4, 4, 10);
	printf("Operacao atualizada com sucesso!\n");

#pragma endregion

#pragma region funcionalidade 6: remover uma operação
	printf("\n\n-  6. Remover uma operação\n");

	// remover operação
	deleteOperation(&operations, 35);
	printf("Operação removida com sucesso!\n");

	// remover execuções associadas à operação
	deleteExecutions_ByOperation_AtTable(&executionsTable, 35);
	printf("Execuções associadas à operação removidas com sucesso!\n");
#pragma endregion

#pragma region funcionalidade 7: inserir uma operação
	printf("\n\n-  7. Inserir uma operação\n");

	// inserir nova operação
	Operation* operation = NULL;
	operation = newOperation(39, 2, 8);
	operations = insertOperation_AtStart(operations, operation);

	// inserir nova execução de uma operação
	Execution* execution = NULL;
	execution = newExecution(39, 5, 17);
	*executionsTable = insertExecution_AtTable(executionsTable, execution);

	// guardar as novas inserções em ficheiros
	writeOperations(OPERATIONS_FILENAME_BINARY, operations);
	//writeExecutions_AtTable(EXECUTIONS_FILENAME_BINARY, executionsTable);
	printf("Novos dados exportados com sucesso!\n");
#pragma endregion

}