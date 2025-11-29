#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5

typedef struct {
    char nome; // Tipo: I, O, T, L, etc.
    int id;    // Identificador único
} Peca;

// ---------------------- VARIÁVEIS GLOBAIS DA FILA ----------------------
Peca fila[TAM];
int inicio = 0;
int fim = 0;
int qtd = 0;
int contadorID = 1;

// ---------------------- FUNÇÃO GERAR PEÇA ----------------------
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = contadorID++;
    return p;
}

// ---------------------- ENFILEIRAR (enqueue) ----------------------
void enfileirar(Peca p) {
    if (qtd == TAM) {
        printf("Fila cheia! (Mas como é Tetris futuro, sempre substituímos)\n");
        return;
    }
    fila[fim] = p;
    fim = (fim + 1) % TAM;
    qtd++;
}

// ---------------------- DESENFILEIRAR (dequeue) ----------------------
Peca desenfileirar() {
    if (qtd == 0) {
        printf("Fila vazia! Nada para jogar.\n");
        Peca vazio = {'-', -1};
        return vazio;
    }
    Peca removida = fila[inicio];
    inicio = (inicio + 1) % TAM;
    qtd--;
    return removida;
}

// ---------------------- VISUALIZAR FILA ----------------------
void exibirFila() {
    printf("\n--- FILA DE PEÇAS FUTURAS ---\n");

    if (qtd == 0) {
        printf("Fila vazia!\n");
        return;
    }

    int i;
    int pos = inicio;

    for (i = 0; i < qtd; i++) {
        printf("[%d] Peça %c (ID %d)\n", i, fila[pos].nome, fila[pos].id);
        pos = (pos + 1) % TAM;
    }
    printf("------------------------------\n");
}

// ---------------------- INICIALIZAR FILA ----------------------
void inicializarFila() {
    for (int i = 0; i < TAM; i++) {
        enfileirar(gerarPeca());
    }
}

// ---------------------- MENU ----------------------
int main() {
    srand(time(NULL));

    inicializarFila();

    int opcao;

    do {
        printf("\n=== MENU TETRIS STACK ===\n");
        printf("1 - Visualizar fila\n");
        printf("2 - Jogar peça (dequeue)\n");
        printf("3 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirFila();
                break;

            case 2: {
                Peca jogada = desenfileirar();
                if (jogada.id != -1) {
                    printf("\nPeça jogada: %c (ID %d)\n", jogada.nome, jogada.id);
                }
                break;
            }

            case 3: {
                Peca nova = gerarPeca();
                printf("\nNova peça gerada: %c (ID %d)\n", nova.nome, nova.id);
                enfileirar(nova);
                break;
            }

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

        if (opcao != 0)
            exibirFila();

    } while (opcao != 0);

    return 0;
}