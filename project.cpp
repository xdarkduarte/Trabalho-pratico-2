#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  // incluído para delay

// Definição da struct que representa um processo
typedef struct {
    int pid;            // Identificador do processo
    char command[256];  // Nome do comando ou programa
} valueT;

// Definição da struct que representa um nó na lista ligada
typedef struct _nodeT {
    valueT value;              // Valor do nó
    struct _nodeT *next;       // Ponteiro para o próximo nó
} nodeT;

// Definição da struct que representa a Stack
typedef struct {
    nodeT *head;              // Ponteiro para o topo da Stack
} stackT;

// Função para criar um novo nó
nodeT *NewNode(void) {
    nodeT *newNode = (nodeT *)malloc(sizeof(nodeT));
    if (newNode == NULL) {
        printf("Erro: Nao ha espaço suficiente para criar um novo no.\n");
        return NULL;
    }
    return newNode;
}

// Função para criar uma nova Stack
stackT *NewStack(void) {
    stackT *newStack = (stackT *)malloc(sizeof(stackT));
    if (newStack == NULL) {
        printf("Erro: Nao ha espaço suficiente para criar uma nova Stack.\n");
        return NULL;
    }
    newStack->head = NULL; // Inicializa o ponteiro head como NULL
    return newStack;
}

// Função para adicionar um processo na Stack
void Push(stackT *stack, valueT processo) {
    if (stack == NULL) {
        printf("Erro: Stack nao inicializada.\n");
        return;
    }
    nodeT *newNode = NewNode();
    if (newNode == NULL) return; // Se não conseguiu criar um novo nó

    newNode->value = processo; // Atribui o processo ao novo nó
    newNode->next = stack->head; // O próximo do novo nó aponta para o topo atual
    stack->head = newNode; // O topo da Stack agora é o novo nó
}

// Função para remover e retornar o processo do topo da Stack
valueT Pop(stackT *stack) {
    if (stack == NULL || stack->head == NULL) {
        printf("Erro: Stack vazia.\n");
        valueT emptyProcess = {0, ""}; // Retorna um processo vazio
        return emptyProcess;
    }
    
    nodeT *temp = stack->head; // Guarda o nó do topo
    valueT poppedValue = temp->value; // Armazena o valor do nó do topo
    stack->head = stack->head->next; // Move o topo para o próximo nó
    free(temp); // Libera o nó do topo
    return poppedValue; // Retorna o processo removido
}

// Função para esvaziar a Stack
void EmptyStack(stackT *stack) {
    if (stack == NULL) return;

    while (stack->head != NULL) {
        nodeT *temp = stack->head; // Guarda o nó do topo
        stack->head = stack->head->next; // Move o topo para o próximo nó
        free(temp); // Libera o nó
    }
}

// Função para liberar a Stack
void FreeStack(stackT *stack) {
    if (stack == NULL) {
        printf("Erro: Stack nao inicializada.\n");
        return;
    }
    if (stack->head != NULL) {
        printf("Erro: A Stack nao esta vazia.\n");
        return;
    }
    free(stack); // Libera a estrutura da Stack
}

// Função para verificar se a Stack está vazia
int isEmpty(stackT *stack) {
    if (stack == NULL) return 1; // Considera como vazia se não estiver inicializada
    return stack->head == NULL ? 1 : 0; // Retorna 1 se vazia, 0 caso contrário
}

// Função auxiliar para imprimir a Stack (do topo para baixo)
void PrintStack(stackT *stack) {
    if (isEmpty(stack)) {
        printf("A Stack esta vazia.\n");
        return;
    }
    printf("Conteudo da Stack (do topo para a base):\n");
    nodeT *current = stack->head;
    while (current != NULL) {
        printf("PID: %d, Comando: %s\n", current->value.pid, current->value.command);
        current = current->next;
    }
}

// Função para fazer uma espera de segundos
void wait_seconds(int seconds) {
    clock_t start_time = clock();
    while (clock() < start_time + seconds * CLOCKS_PER_SEC);
}

// Exemplo de uso
int main() {
    stackT *myStack = NewStack();
    if (myStack == NULL) return 1;

    // Criar alguns processos
    valueT p1 = {5, "ProcessoA"};
    valueT p2 = {2, "ProcessoB"};
    valueT p3 = {6, "ProcessoC"};

    Push(myStack, p1);
    Push(myStack, p2);
    Push(myStack, p3);

    PrintStack(myStack);

    // Pop 1
    valueT popped = Pop(myStack);
    if (popped.pid != 0)
        printf("Pop: PID: %d, Comando: %s\n", popped.pid, popped.command);

    PrintStack(myStack);

    // Esvaziar a Stack
    EmptyStack(myStack);

    PrintStack(myStack);

    // Tentar liberar a Stack (deve funcionar porque vazia)
    FreeStack(myStack);

    printf("O programa ira fechar em 5 segundos...\n");
    wait_seconds(5);

    return 0;
}

