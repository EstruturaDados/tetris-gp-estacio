// Desafio Tetris Stack
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

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
    Peca pecas[MAX];
} Fila;

void inicializarFila(Fila *f)
{
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(Fila *f)
{
    return f->total == MAX;
}

int filaVazia(Fila *f)
{
    return f->total == 0;
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
    f->fim = (f->fim + 1) % MAX;
    f->total++;
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
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;

    printf("Peca jogada: Tipo %s, ID %d\n", p->tipo, p->id);
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
        int index = (f->inicio + i) % MAX;
        printf("Tipo: %s, ID: %d\n", f->pecas[index].tipo, f->pecas[index].id);
    }
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
    printf("1. Jogar peça (dequeue)\n");
    printf("2. Inserir nova peça (enqueue)\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int main()
{

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.

    Fila filaPecas;
    inicializarFila(&filaPecas);

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
            // Peca novaPeca;
            // gerarPeca(&novaPeca);
            // enqueue(&filaPecas, novaPeca);
            break;
        }
        case 2: {
            // inserir nova peça ao final
            Peca novaPeca;
            gerarPeca(&novaPeca);
            enqueue(&filaPecas, novaPeca);
            break;
        }
        case 0:
            printf("Saindo do jogo.\n");
            break;
        default:
            printf("Opção inválida!\n");
        }

        mostrarFila(&filaPecas);
    } while (opcao != 0);

    return 0;
}