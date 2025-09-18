#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char tipo;
    int id;
} Peca;

#define MAX 5

typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

int proximoId = 1;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}
    


int filaCheia(Fila *f) {
    return f->total == MAX;
}

int filaVazia(Fila *f) {
    return f->total = 0;
}

Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.tipo = tipos[rand() % 4];
    nova.id = proximoId++;

    return nova;

}

void inserir(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia. Não é possível inserir.\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

Peca remover(Fila *f, Peca *p) {
    Peca removida = {'-', -1};
    if (filaVazia(f)) {
        printf("Fila vazia. Não é possivel remover.\n");
        return removida;
    }

    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    return *p;
}

void exibirFila(Fila *f) {
    printf("Fila: ");

    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c, %d] ", f->itens[idx].tipo, f->itens[idx].id);
    }

    printf("\n");
}

int main() {
    Fila fila;
    Peca jogada;
    inicializarFila(&fila);
    srand(time(NULL));

    for (int i = 0; i < MAX; i++) {
        inserir(&fila, gerarPeca());
    }

    int opcao;
    
    do {
        printf("\n=== MENU ===\n");
        printf("1. Exibir fila\n");
        printf("2. Jogar peça\n");
        printf("3. Adicionar nova peça\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                exibirFila(&fila);
                break;

            case 2:
                Peca jogada = remover(&fila, &jogada);
                if (jogada.id != -1)
                printf("Peça jogada: [%c - id:%d]\n", jogada.tipo, jogada.id);
                exibirFila(&fila);
                break;

            case 3:
                if (!filaCheia(&fila)) {
                    Peca nova = gerarPeca();
                    inserir(&fila, nova);
                    printf("Peça adicionada: [%c - id:%d]\n", nova.tipo, nova.id);
                }
                exibirFila(&fila);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Escolha inválida.\n");
                break;
        }
    } while(opcao != 0);

    return 0;
}