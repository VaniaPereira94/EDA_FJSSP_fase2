/**
 * @brief	Ficheiro com fun��o para carregar dados em listas
 * @file	data.c
 * @author	V�nia Pereira
 * @email	a19264@alunos.ipca.pt
 * @date	2022
 * @Disciplina Estruturas de Dados Avan�adas
*/


#include <stdbool.h>
#include <stdio.h>
#include "header.h"


/**
* @brief	Carregar dados de trabalhos para lista em mem�ria
* @param	jobs		Apontador para a lista de jobs
*/
Job* loadJobs(Job* jobs)
{
	Job* job = NULL;

	job = newJob(1);
	jobs = insertJobAtStart(jobs, job);
	job = newJob(2);
	jobs = insertJobAtStart(jobs, job);
	job = newJob(3);
	jobs = insertJobAtStart(jobs, job);
	job = newJob(4);
	jobs = insertJobAtStart(jobs, job);
	job = newJob(5);
	jobs = insertJobAtStart(jobs, job);
	job = newJob(6);
	jobs = insertJobAtStart(jobs, job);
	job = newJob(7);
	jobs = insertJobAtStart(jobs, job);
	job = newJob(8);
	jobs = insertJobAtStart(jobs, job);
}


/**
* @brief	Carregar dados de m�quinas para lista em mem�ria
* @param	machines	Apontador para a lista de m�quinas
*/
Machine* loadMachines(Machine* machines)
{
	Machine* machine = NULL;

	machine = newMachine(1, false);
	machines = insertMachineAtStart(machines, machine);
	machine = newMachine(2, false);
	machines = insertMachineAtStart(machines, machine);
	machine = newMachine(3, false);
	machines = insertMachineAtStart(machines, machine);
	machine = newMachine(4, false);
	machines = insertMachineAtStart(machines, machine);
	machine = newMachine(5, false);
	machines = insertMachineAtStart(machines, machine);
	machine = newMachine(6, false);
	machines = insertMachineAtStart(machines, machine);
	machine = newMachine(7, false);
	machines = insertMachineAtStart(machines, machine);
	machine = newMachine(8, false);
	machines = insertMachineAtStart(machines, machine);
}


/**
* @brief	Carregar dados de opera��es para lista em mem�ria
* @param	operations	Apontador para a lista de opera��es
*/
Operation* loadOperations(Operation* operations)
{
	Operation* operation = NULL;

	// operations - job 1
	operation = newOperation(1, 1);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(2, 1);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(3, 1);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(4, 1);
	operations = insertOperation_AtStart(operations, operation);
	// operations - job 2
	operation = newOperation(5, 2);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(6, 2);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(7, 2);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(8, 2);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(9, 2);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(10, 2);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(11, 2);
	operations = insertOperation_AtStart(operations, operation);
	// operations - job 3
	operation = newOperation(12, 3);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(13, 3);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(14, 3);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(15, 3);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(16, 3);
	operations = insertOperation_AtStart(operations, operation);
	// operations - job 4
	operation = newOperation(17, 4);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(18, 4);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(19, 4);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(20, 4);
	operations = insertOperation_AtStart(operations, operation);
	// operations - job 5
	operation = newOperation(21, 5);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(22, 5);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(23, 5);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(24, 5);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(25, 5);
	operations = insertOperation_AtStart(operations, operation);
	// operations - job 
	operation = newOperation(26, 6);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(27, 6);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(28, 6);
	operations = insertOperation_AtStart(operations, operation);
	// operations - job 7
	operation = newOperation(29, 7);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(30, 7);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(31, 7);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(32, 7);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(33, 7);
	operations = insertOperation_AtStart(operations, operation);
	// operations - job 8
	operation = newOperation(34, 8);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(35, 8);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(36, 8);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(37, 8);
	operations = insertOperation_AtStart(operations, operation);
	operation = newOperation(38, 8);
	operations = insertOperation_AtStart(operations, operation);
}


/**
* @brief	Carregar dados de execu��es de opera��es para a tabela hash em mem�ria
* @param	table	Apontador para a tabela hash das execu��es de opera��es
*/
ExecutionNode** loadExecutionsTable(ExecutionNode* table[])
{
	Execution* execution = NULL;

	// execution - job 1
	execution = newExecution(1, 1, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(1, 3, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(2, 2, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(2, 4, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(3, 3, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(3, 5, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(4, 4, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(4, 5, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(4, 6, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(4, 7, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(4, 8, 9);
	*table = insertExecution_AtTable(table, execution);
	// execution - job 2
	execution = newExecution(5, 1, 1);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(5, 3, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(5, 5, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(6, 4, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(6, 8, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(7, 4, 1);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(7, 6, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(8, 4, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(8, 7, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(8, 8, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(9, 4, 1);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(9, 6, 2);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(10, 1, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(10, 6, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(10, 8, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(11, 4, 4);
	*table = insertExecution_AtTable(table, execution);
	// execution - job 3
	execution = newExecution(12, 2, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(12, 3, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(12, 8, 8);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(13, 4, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(13, 8, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(14, 3, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(14, 5, 8);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(14, 7, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(15, 4, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(15, 6, 8);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(16, 1, 1);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(16, 2, 4);
	*table = insertExecution_AtTable(table, execution);
	// execution - job 4
	execution = newExecution(17, 1, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(17, 3, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(17, 5, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(18, 2, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(18, 8, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(19, 3, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(19, 4, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(19, 6, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(19, 7, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(20, 5, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(20, 6, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(20, 8, 5);
	*table = insertExecution_AtTable(table, execution);
	// execution - job 5
	execution = newExecution(21, 1, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(22, 2, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(22, 4, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(23, 3, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(23, 8, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(24, 5, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(24, 6, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(24, 8, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(25, 4, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(25, 6, 4);
	*table = insertExecution_AtTable(table, execution);
	// execution - job 6
	execution = newExecution(26, 1, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(26, 2, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(26, 3, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(27, 4, 7);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(27, 5, 8);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(28, 3, 9);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(28, 6, 8);
	*table = insertExecution_AtTable(table, execution);
	// execution - job 7
	execution = newExecution(29, 3, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(29, 5, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(29, 6, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(30, 4, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(30, 7, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(30, 8, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(31, 1, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(31, 3, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(31, 4, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(31, 5, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(32, 4, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(32, 6, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(32, 8, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(33, 1, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(33, 3, 3);
	*table = insertExecution_AtTable(table, execution);
	// execution - job 8
	execution = newExecution(34, 1, 3);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(34, 2, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(34, 6, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(35, 4, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(35, 5, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(35, 8, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(36, 3, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(36, 7, 5);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(37, 4, 4);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(37, 6, 6);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(38, 7, 1);
	*table = insertExecution_AtTable(table, execution);
	execution = newExecution(38, 8, 2);
	*table = insertExecution_AtTable(table, execution);

	return *table;
}