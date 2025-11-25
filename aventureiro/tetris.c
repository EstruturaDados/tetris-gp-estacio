// Desafio Tetris Stack
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILA 5
#define MAX_PILHA 3

typedef struct
{
    char tipo[2];
    int id;
} Peca;

typedef struct
{
    int inicio;
    int fim;
    int total;
    Peca pecas[MAX_FILA];
} Fila;

typedef struct {
    Peca pecas[MAX_PILHA];
    int topo;
} Pilha;

void inicializarFila(Fila *f)
{
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int filaCheia(Fila *f)
{
    return f->total == MAX_FILA;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

int filaVazia(Fila *f)
{
    return f->total == 0;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

// inserir
void enqueue(Fila *f, Peca p)
{
    if (filaCheia(f))
    {
        printf("Fila cheia! Nao e possivel inserir nova peca.\n");
        return;
    }

    f->pecas[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

void push(Pilha *p, Peca nova) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia. Não é possível inserir.\n");
        return;
    }
 
    p->topo++;
    p->pecas[p->topo] = nova;
}

// remover
void dequeue(Fila *f, Peca *p)
{
    if (filaVazia(f))
    {
        printf("Fila vazia! Nao ha pecas para jogar.\n");
        return;
    }

    *p = f->pecas[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;

    printf("Peca jogada: Tipo %s, ID %d\n", p->tipo, p->id);
}

void pop(Pilha *p, Peca *removida) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia. Não é possível remover.\n");
        return;
    }

    *removida = p->pecas[p->topo];
    p->topo--;
}

void mostrarFila(Fila *f)
{
    if (filaVazia(f))
    {
        printf("Fila vazia!\n");
        return;
    }

    printf("Pecas na fila:\n");
    for (int i = 0; i < f->total; i++)
    {
        int index = (f->inicio + i) % MAX_FILA;
        printf("Tipo: %s, ID: %d\n", f->pecas[index].tipo, f->pecas[index].id);
    }
}

void mostrarPilha(Pilha *p) {
    printf("Pilha (topo -> base):\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%s, %d]\n", p->pecas[i].tipo, p->pecas[i].id);
    }
    printf("\n");
}

// consulta o elemento no topo
void peek(Pilha *p, Peca *visualizada) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia. Nada para espiar.\n");
        return;
    }

    *visualizada = p->pecas[p->topo];
}

void gerarPeca(Peca *p)
{
    static int idSequencial = 1;
    const char tipos[][2] = {"T", "O", "L", "I", "I"};
    int tipoIndex = rand() % 5;

    strcpy(p->tipo, tipos[tipoIndex]);
    p->id = idSequencial++;
}

void exibirMenu()
{
    printf("1. Jogar peça\n");
    printf("2. Enviar peça da fila para a reserva\n");
    printf("3. Usar peça da reserva\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int main()
{

    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).

    Fila filaPecas;
    inicializarFila(&filaPecas);

    Pilha pilhaReserva;
    inicializarPilha(&pilhaReserva);

    //gera 5 pecas aleatorias para iniciar a fila
    for (int i = 0; i < MAX_FILA; i++) {
        Peca p;
        gerarPeca(&p);
        enqueue(&filaPecas, p);
    }

    int opcao;
    do
    {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            // remover peça da frente
            Peca p;
            dequeue(&filaPecas, &p);

            // inserir nova peça ao final
            Peca novaPeca;
            gerarPeca(&novaPeca);
            enqueue(&filaPecas, novaPeca);
            break;
        }
        case 2: {
            // enviar peça da fila para a reserva
            Peca p;
            dequeue(&filaPecas, &p);
            push(&pilhaReserva, p);

            // inserir nova peça ao final
            Peca novaPeca;
            gerarPeca(&novaPeca);
            enqueue(&filaPecas, novaPeca);
            break;
        }
        case 3: {
            // usar peça da reserva
            Peca p;
            pop(&pilhaReserva, &p);
            break;
        }
        case 0:
            printf("Saindo do jogo.\n");
            break;
        default:
            printf("Opção inválida!\n");
        }

        mostrarFila(&filaPecas);
        mostrarPilha(&pilhaReserva);

    } while (opcao != 0);

    return 0;
}