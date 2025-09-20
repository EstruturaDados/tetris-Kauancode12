#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Cria 'struct Peca', com 'char tipo' e 'int id'.
typedef struct {
    char tipo;
    int id;
} Peca;

// Define o tamanho maximo da fila.
#define MAX 5

// Cria a struct Fila com 'int inicio', 'fim' e 'total'.
// Cria 'itens' com o tamanho de 'MAX'.
typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// Variavel 'int proximoId' será utilizada para o sistema de IDs proprios das peças.
int proximoId = 1;

// Função que limpa o lixo do buffer e espera o usuario digitar ENTER para continuar o programa.
void pausar() {
    printf("\nPressione ENTER para prosseguir...");
        while(getchar() != '\n');
        getchar();
}

// Inicializa a fila com 0.
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Verifica se a fila está cheia comparando 'total' com o valor de 'MAX'.
int filaCheia(Fila *f) {
    return f->total == MAX;
}

// Verifica se a fila está vazia comparando 'total' com 0.
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Gera peças aleatorias com a função 'rand()'.
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'}; // Letras que representam os formatos utilizados.
    Peca nova;
    nova.tipo = tipos[rand() % 4];
    nova.id = proximoId++; // Incrementa 'proximoId', garantindo IDs diferentes.

    return nova;

}

// Insere nova peça ao final da fila.
void inserir(Fila *f, Peca p) {

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX; // Avança o índice 'fim', se chegar ao limite (MAX), volta para o inicio (comportamento circular).
    f->total++;
}

// Remove a peça que representa o inicio da fila.
Peca remover(Fila *f) {
    Peca removida = {'-', -1};

    removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;// Avança o índice 'inicio', se passar do final do vetor volta para a posição 0 (comportamento circular).
    f->total--;
    return removida;
}

// Mostra o estado atual da fila.
void exibirFila(Fila *f) {

    printf("\nFila: ");

    // Loop 'for' percorre cada posição enquanto (i < f->total), exibindo as posições ocupadas por peças.
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c, %d] ", f->itens[idx].tipo, f->itens[idx].id);
    }

    printf("\n");
    pausar(); // Espera um ENTER para continuar.
}

int main() {
    Fila fila;
    Peca jogada;
    inicializarFila(&fila); // Inicializa a fila chamando a função responsável.
    srand(time(NULL)); // Criação de peças com mais aleatoriedade.

    // Loop 'for' que inicia o programa automaticamente com a fila cheia de peças.
    for (int i = 0; i < MAX; i++) {
        inserir(&fila, gerarPeca());
    }

    int opcao;
    
    // Menu interativo.
    do {
        printf("\n=== MENU ===\n");
        printf("1. Exibir fila\n");
        printf("2. Jogar peça\n");
        printf("3. Adicionar nova peça\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: // Mostra a fila, se estiver vazia exibe mensagem "nada a exibir".
                if (filaVazia(&fila)) {
                    printf("\nFila vazia, Nada a exibir.\n");
                    pausar();
                } else {
                    exibirFila(&fila); // Chama a função que exibe se tiver peças.
                }
                break;

            case 2: // Remove e exibe qual foi removida conforme 'jogada'.
                if (!filaVazia(&fila)) {
                    Peca jogada = remover(&fila);
                    if (jogada.id != -1)
                    printf("\nUltima peça jogada: [%c - ID: %d]\n", jogada.tipo, jogada.id);
                }
                if (filaVazia(&fila)) {
                    printf("\nFila vazia, nada mais a remover ou exibir\n"); // Se estiver vazia exibe "nada mais a remover ou exibir".
                    pausar();
                } else {
                    exibirFila(&fila); // Exibe a fila caso tenha peças.
                }
                break;

            case 3:
                if (filaCheia(&fila)) {
                    printf("\nFila cheia, não é possível inserir.\n"); // Exibe "não é possivel inserir" caso esteja cheia.
                } else {
                    Peca nova = gerarPeca(); // Caso tenha espaço gera uma nova peça.
                    inserir(&fila, nova);
                    printf("\nPeça adicionada: [%c - ID: %d]\n", nova.tipo, nova.id); // Exibe qual peça foi adicionada conforme 'nova'.
                }
                exibirFila(&fila); // Exibe o estado atual da fila a cada inserção.
                break;

            case 0:
                printf("\nSaindo...\n"); // Encerra o programa.
                break;

            default:
                printf("Escolha inválida.\n"); // Exibe escolha invalida se o usuario digitar opção que não exista.
                break;
        }
    } while(opcao != 0);

    return 0;
}