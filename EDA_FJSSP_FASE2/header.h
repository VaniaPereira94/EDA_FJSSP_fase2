/**
 * @brief	Ficheiro com todas as assinaturas globais necess�rios para a aplica��o
 * @file	header.h
 * @author	V�nia Pereira
 * @email	a19264@alunos.ipca.pt
 * @date	2022
 * @Disciplina Estruturas de Dados Avan�adas
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
  * @brief	Nomes para os ficheiros onde os dados s�o armazenados
  */
#define JOBS_FILENAME_BINARY "jobs.bin"
#define MACHINES_FILENAME_BINARY "machines.bin"
#define OPERATIONS_FILENAME_BINARY "operations.bin"
#define EXECUTIONS_FILENAME_BINARY "executions.bin"

#pragma endregion


#pragma region estruturas de dados em mem�ria

  /**
   * @brief	Estrutura de dados para representar a lista de trabalhos (em mem�ria)
   */
typedef struct Job
{
	int id;
	struct Job* next;
} Job;

extern Job* jobs; // extern: informa o compilador que esta vari�vel est� definida algures no c�digo

/**
 * @brief	Estrutura de dados para representar a lista de m�quinas (em mem�ria)
 */
typedef struct Machine
{
	int id;
	bool isBusy; // se a m�quina est� ou n�o em utiliza��o
	struct Machine* next;
} Machine;

extern Machine* machines;// lista de m�quinas

/**
 * @brief	Estrutura de dados para representar a lista de opera��es (em mem�ria)
 */
typedef struct Operation
{
	int id;
	int jobID;
	struct Operation* next;

} Operation;

extern Operation* operations; // lista de opera��es

/**
 * @brief	Estrutura de dados para representar a lista das execu��es das opera��es em m�quinas (em mem�ria)
 */
typedef struct Execution
{
	int operationID;
	int machineID;
	int runtime; // unidades de tempo necess�rias para a execu��o da opera��o
	struct Execution* next;
} Execution;

extern Execution* executions; // lista de execu��es

/**
 * @brief	Estrutura de dados para representar cada n� (posi��o) da tabela hash das execu��es (em mem�ria)
 */
typedef struct {
	Execution* start; // apontador para o primeiro elemento de cada posi��o da tabela
	int numberOfExecutions; // quantidade de execu��es de cada posi��o da tabela
} ExecutionNode;

// tabela hash para armazenar as execu��es e fazer buscas de forma mais eficiente,
// � um array de apontadores para listas de execu��es
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
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de m�quinas
 */
typedef struct MachineFile
{
	int id;
	bool isBusy; // se a m�quina est� ou n�o em utiliza��o
} MachineFile;

/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de opera��es
 */
typedef struct FileOperation
{
	int id;
	int jobID;
} FileOperation;

/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de execu��es das opera��es em m�quinas
 */
typedef struct FileExecution
{
	int operationID;
	int machineID;
	int runtime; // unidades de tempo necess�rias para a execu��o da opera��o
} FileExecution;

#pragma endregion


#pragma region fun��es

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
 * @brief	Sobre m�quinas
 */
Machine* newMachine(int id, bool isBusy);
Machine* insertMachineAtStart(Machine* head, Machine* new);
bool writeMachines(char* fileName, Machine* head);
Machine* readMachine(char* fileName);
bool displayMachines(Machine* head);
bool searchMachine(Machine* head, int id);

/**
 * @brief	Sobre opera��es
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
 * @brief	Sobre execu��es com listas
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
 * @brief	Sobre execu��es com tabela hash
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
 * @brief	Carregar dados para as estruturas em mem�ria
 */
Job* loadJobs(Job* jobs);
Machine* loadMachines(Machine* machines);
Operation* loadOperations(Operation* operations);
ExecutionNode** loadExecutionsTable(ExecutionNode* table[]);

#pragma endregion

#endif