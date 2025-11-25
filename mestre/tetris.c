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
    printf("4. Trocar peça da frente com topo da pilha\n");
    printf("5. Trocar 3 primeiros da fila com os 3 da pilha\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int main()
{

    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha

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
        case 4: {
            // trocar peça da frente com topo da pilha
            if (filaVazia(&filaPecas) || pilhaVazia(&pilhaReserva)) {
                printf("Não é possível trocar: fila vazia ou pilha vazia.\n");
            } else {
                Peca temp = filaPecas.pecas[filaPecas.inicio];
                filaPecas.pecas[filaPecas.inicio] = pilhaReserva.pecas[pilhaReserva.topo];
                pilhaReserva.pecas[pilhaReserva.topo] = temp;
                printf("Troca realizada entre a peça da frente da fila e o topo da pilha.\n");
            }
            break;
        }
        case 5: {
            // trocar 3 primeiros da fila com os 3 da pilha
            if (pilhaReserva.topo < 2 || filaPecas.total < 3) {
                printf("Não é possível trocar: pilha não tem 3 peças ou fila não tem 3 peças.\n");
            } else {
                for (int i = 0; i < 3; i++) {
                    int filaIndex = (filaPecas.inicio + i) % MAX_FILA;
                    Peca temp = filaPecas.pecas[filaIndex];
                    filaPecas.pecas[filaIndex] = pilhaReserva.pecas[pilhaReserva.topo - i];
                    pilhaReserva.pecas[pilhaReserva.topo - i] = temp;
                }
                printf("Troca realizada entre os 3 primeiros da fila e os 3 da pilha.\n");
            }
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