#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
using std::string;
using std::getline;

//  fila de pessoas
typedef struct pessoa {
    string cpf;
    string nome;
    int idade;
    struct pessoa* prox;
} PESSOA;

// pilha de frascos
typedef struct frasco {
    string nome;
    int dosesRestantes;
    struct frasco* prox;
} FRASCO;

// Funções da fila
void adicionarNaFila(PESSOA** primeiro, string cpf, string nome, int idade) {
    PESSOA* novaPessoa = (PESSOA*) malloc(sizeof(PESSOA));
    novaPessoa->cpf = cpf;
    novaPessoa->nome = nome;
    novaPessoa->idade = idade;
    novaPessoa->prox = NULL;

    if (*primeiro == NULL) {
        *primeiro = novaPessoa;  
    } else {
        PESSOA* atual = *primeiro;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novaPessoa;  
    }
    cout << "\nPessoa adicionada na fila\n";  
}

void imprimeFila(PESSOA* primeiro) {
    if (primeiro == NULL) {
        cout << "\nFILA VAZIA!";
    } else {
        while (primeiro != NULL) {
            cout << "\nNome: " << primeiro->nome << ", CPF: " << primeiro->cpf << ", Idade: " << primeiro->idade;
            primeiro = primeiro->prox;
        }
    }
    cout << "\n";
}

PESSOA* removerDaFila(PESSOA** primeiro) {
    if (*primeiro == NULL) {
        cout << "FILA VAZIA\n";
        return NULL;
    } else {
        PESSOA* aux = *primeiro;
        *primeiro = aux->prox;
        return aux;
    }
}

// Funções da pilha
void empilharFrasco(FRASCO** topo, string nome) {
    FRASCO* novoFrasco = (FRASCO*) malloc(sizeof(FRASCO));
    novoFrasco->nome = nome;
    novoFrasco->dosesRestantes = 5;  
    novoFrasco->prox = *topo;
    *topo = novoFrasco;
}

FRASCO* desempilharFrasco(FRASCO** topo) {
    if (*topo == NULL) {  
        cout << "PILHA VAZIA!";
        return NULL;
    } else {
        FRASCO* aux = *topo;  
        *topo = aux->prox;    

        if (aux->dosesRestantes == 0) {
            free(aux);  
            return NULL; 
        }
        return aux;
    }
}

// Função para vacinar uma pessoa
void vacinarPessoa(PESSOA** fila, FRASCO** pilha, int* vacinados) {
    if (*fila == NULL) {
        cout << "A fila está vazia.\n";
        return;
    }

    if (*pilha == NULL) {
        cout << "\nTodos os frascos de vacina acabaram!\n";
        return;
    }

    PESSOA* removida = removerDaFila(fila);
    
    if (removida != NULL) {
        cout << "\nPessoa vacinada:\n";
        cout << "Nome: " << removida->nome << ", CPF: " << removida->cpf << ", Idade: " << removida->idade << endl;  

        (*pilha)->dosesRestantes--;

        if ((*pilha)->dosesRestantes == 0) {
            string nomeFrascoAtual = (*pilha)->nome;  
            desempilharFrasco(pilha);

            if (*pilha != NULL) {
                cout << "\n";
                cout << nomeFrascoAtual << " acabou. " << (*pilha)->nome << " em uso.\n";  
            } else {
                cout << "\nTodos os frascos de vacina acabaram!\n";
            }
        }
        (*vacinados)++;
    }
}

// Função para liberar a fila
void liberarFila(PESSOA** fila) {
    while (*fila != NULL) {
        PESSOA* aux = *fila;
        *fila = (*fila)->prox;
        free(aux);
    }
}

// Função para liberar a pilha
void liberarPilha(FRASCO** pilha) {
    while (*pilha != NULL) {
        FRASCO* aux = *pilha;
        *pilha = (*pilha)->prox;
        free(aux);
    }
}

int main() {
    PESSOA* fila = NULL;
    FRASCO* pilha = NULL;
    int vacinados = 0;
    int opcao;

    // Empilhar os frascos no início
    empilharFrasco(&pilha, "Frasco 3");
    empilharFrasco(&pilha, "Frasco 2");
    empilharFrasco(&pilha, "Frasco 1");

    cout << "\nSistema de Vacinacao 07/10" << endl;

    do { 
        cout << "\n------------------------------------------\n";
        cout << "MENU:\n";
        cout << "1. Adicionar pessoa na fila\n";
        cout << "2. Tirar pessoa da fila e vacinar\n";
        cout << "3. Imprimir os nomes de todo mundo da fila\n";
        cout << "4. Total de pessoas vacinadas\n";
        cout << "0. Sair\n";
        cout << "------------------------------------------\n";
        cout << "Opcao: ";
        cin >> opcao;
        cin.ignore(); 

        switch (opcao) {
            case 1: {
                string cpf, nome;
                int idade;
                cout << "\nDigite o CPF: ";
                getline(cin, cpf);
                cout << "Digite o Nome: ";
                getline(cin, nome);
                cout << "Digite a Idade: ";
                cin >> idade;
                adicionarNaFila(&fila, cpf, nome, idade);
                break;
            }
            case 2: {
                if (fila != NULL) {
                    vacinarPessoa(&fila, &pilha, &vacinados);
                } else {
                    cout << "\nFILA VAZIA!\n";
                }
                break;
            }
            case 3:
                imprimeFila(fila);
                break;
            case 4:
                cout << "\nTotal de pessoas vacinadas: " << vacinados << endl;
                break;
            case 0:
                cout << "\nSaindo...\n";
                break;
            default:
                cout << "\nOpcao invalida!\n";
        }
    } while (opcao != 0);

    liberarFila(&fila);
    liberarPilha(&pilha);

    return 0;
}
