/**
 * @brief	Ficheiro com todas as assinaturas globais necessários para a aplicação
 * @file	header.h
 * @author	Vânia Pereira
 * @email	a19264@alunos.ipca.pt
 * @date	2022
 * @Disciplina Estruturas de Dados Avançadas
*/


#ifndef HEADER_H

#pragma region constantes

#define HEADER_H

/**
 * @brief	Tamanho relativos a estruturas de dados
 */
#define HASH_TABLE_SIZE 13
#define NUMBER_MACHINES 8
#define MAX_TIME 18

 /**
  * @brief	Nomes para os ficheiros onde os dados são armazenados
  */
#define JOBS_FILENAME_BINARY "jobs.bin"
#define MACHINES_FILENAME_BINARY "machines.bin"
#define OPERATIONS_FILENAME_BINARY "operations.bin"
#define EXECUTIONS_FILENAME_BINARY "executions.bin"

#pragma endregion


#pragma region estruturas de dados em memória

  /**
   * @brief	Estrutura de dados para representar a lista de trabalhos (em memória)
   */
typedef struct Job
{
	int id;
	struct Job* next;
} Job;

extern Job* jobs; // extern: informa o compilador que esta variável está definida algures no código

/**
 * @brief	Estrutura de dados para representar a lista de máquinas (em memória)
 */
typedef struct Machine
{
	int id;
	bool isBusy; // se a máquina está ou não em utilização
	struct Machine* next;
} Machine;

extern Machine* machines;// lista de máquinas

/**
 * @brief	Estrutura de dados para representar a lista de operações (em memória)
 */
typedef struct Operation
{
	int id;
	int jobID;
	struct Operation* next;

} Operation;

extern Operation* operations; // lista de operações

/**
 * @brief	Estrutura de dados para representar a lista das execuções das operações em máquinas (em memória)
 */
typedef struct Execution
{
	int operationID;
	int machineID;
	int runtime; // unidades de tempo necessárias para a execução da operação
	struct Execution* next;
} Execution;

extern Execution* executions; // lista de execuções

/**
 * @brief	Estrutura de dados para representar cada nó (posição) da tabela hash das execuções (em memória)
 */
typedef struct {
	Execution* start; // apontador para o primeiro elemento de cada posição da tabela
	int numberOfExecutions; // quantidade de execuções de cada posição da tabela
} ExecutionNode;

// tabela hash para armazenar as execuções e fazer buscas de forma mais eficiente,
// é um array de apontadores para listas de execuções
extern ExecutionNode* executionsTable[HASH_TABLE_SIZE];

#pragma endregion


#pragma region estruturas de dados em ficheiros

/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de trabalhos
 */
typedef struct JobFile
{
	int id;
} JobFile;

/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de máquinas
 */
typedef struct MachineFile
{
	int id;
	bool isBusy; // se a máquina está ou não em utilização
} MachineFile;

/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de operações
 */
typedef struct FileOperation
{
	int id;
	int jobID;
} FileOperation;

/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de execuções das operações em máquinas
 */
typedef struct FileExecution
{
	int operationID;
	int machineID;
	int runtime; // unidades de tempo necessárias para a execução da operação
} FileExecution;

#pragma endregion


#pragma region funções

/**
 * @brief	Sobre trabalhos
 */

Job* newJob(int id);
Job* insertJobAtStart(Job* head, Job* new);
bool deleteJob(Job** head, int id);
bool writeJobs(char* fileName, Job* h);
Job* readJobs(char* fileName);
void displayJob(Job* head);
bool searchJob(Job* head, int id);

/**
 * @brief	Sobre máquinas
 */
Machine* newMachine(int id, bool isBusy);
Machine* insertMachineAtStart(Machine* head, Machine* new);
bool writeMachines(char* fileName, Machine* head);
Machine* readMachine(char* fileName);
bool displayMachines(Machine* head);
bool searchMachine(Machine* head, int id);

/**
 * @brief	Sobre operações
 */
Operation* newOperation(int id, int jobID);
Operation* insertOperation_AtStart(Operation* head, Operation* new);
bool deleteOperation(Operation** head, int id);
int deleteOperation_ByJob(Operation** head, int jobID);
bool writeOperations(char fileName[], Operation* head);
Operation* readOperations(char fileName[]);
bool displayOperations(Operation* head);
bool searchOperation(Operation* head, int id);
bool searchOperation_ByJob(Operation* head, int jobID);
Operation* getOperation(Operation* head, int id);
int getMinTimeToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** minExecutions);
int getMaxTimeToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** maxExecutions);
float getAverageTimeToCompleteOperation(Execution* head, int operationID);

/**
 * @brief	Sobre execuções com listas
 */
Execution* newExecution(int operationID, int machineID, int runtime);
Execution* insertExecutionAtStart(Execution* head, Execution* new);
Execution* insertExecutionByOperation(Execution* head, Execution* new);
bool updateRuntime(Execution** head, int operationID, int machineID, int runtime);
bool deleteExecutionByOperation(Execution** head, int operationID);
bool writeExecutions(char fileName[], Execution* head);
Execution* readExecutions(char fileName[]);
bool displayExecutions(Execution* head);
Execution* searchExecution(Execution* head, int operationID, int machineID);
Execution* searchExecutionByOperation(Execution* head, int operationID);
Execution* sortExecutionsByOperation(Execution* head);
Execution* getLastExecution(Execution* head);

/**
 * @brief	Sobre execuções com tabela hash
 */
 //ExecutionNode** loadExecutionsTable(char* fileName, ExecutionNode* table[]);
ExecutionNode** createExecutionsTable(ExecutionNode* table[]);
ExecutionNode* createExecutionNode();
int generateHash(int id);
ExecutionNode** insertExecution_AtTable(ExecutionNode* table[], Execution* new);
bool updateRuntime_ByOperation_AtTable(ExecutionNode** table[], int operationID, int machineID, int runtime);
bool deleteExecutions_ByOperation_AtTable(ExecutionNode** table[], int operationID);
bool writeExecutions_AtTable(char fileName[], ExecutionNode* table[]);
ExecutionNode** readExecutions_AtTable(char fileName[], ExecutionNode* tableee[]);
bool displayExecutions_AtTable(ExecutionNode* table[]);
Execution* searchExecution_AtTable(ExecutionNode* table[], int operationID, int machineID);
//ExecutionNode** free_Execution_Table(ExecutionNode* table[]);

/**
 * @brief	Carregar dados para as estruturas em memória
 */
Job* loadJobs(Job* jobs);
Machine* loadMachines(Machine* machines);
Operation* loadOperations(Operation* operations);
ExecutionNode** loadExecutionsTable(ExecutionNode* table[]);

#pragma endregion

#endif