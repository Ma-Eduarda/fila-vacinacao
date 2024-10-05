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

void adicionarNaFila(PESSOA** primeiro, string cpf, string nome, int idade) {
    PESSOA* novaPessoa = new PESSOA;  // Usando new ao invés de malloc
    novaPessoa->cpf = cpf;
    novaPessoa->nome = nome;
    novaPessoa->idade = idade;
    novaPessoa->prox = NULL;

    if (*primeiro == NULL) {
        *primeiro = novaPessoa;  // Primeira pessoa na fila
    } else {
        PESSOA* atual = *primeiro;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novaPessoa;  // Adiciona ao final da fila
    }
    cout << "\nPessoa adicionada na fila\n";  
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

void liberarFila(PESSOA** fila) {
    while (*fila != NULL) {
        PESSOA* aux = *fila;
        *fila = (*fila)->prox;
        delete aux;  // Usando delete ao invés de free
    }
}

// Funções da pilha
void empilharFrasco(FRASCO** topo, string nome) {
    FRASCO* novoFrasco = new FRASCO;  // Usando new ao invés de malloc
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
        return aux;
    }
}

void descartarFrasco(FRASCO** topo) {
    if (*topo == NULL) {
        cout << "PILHA VAZIA";
        return;
    } else {
        FRASCO* aux = *topo;
        *topo = aux->prox;
        delete aux;  // Usando delete ao invés de free
    }
}

void liberarPilha(FRASCO** pilha) {
    while (*pilha != NULL) {
        FRASCO* aux = *pilha;
        *pilha = (*pilha)->prox;
        delete aux;  // Usando delete ao invés de free
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
    
    // Verifica se removida não é NULL antes de acessar seus dados
    if (removida != NULL) {
        cout << "\nUma pessoa saiu da fila!\n";
        cout << "Nome: " << removida->nome << ", CPF: " << removida->cpf << ", Idade: " << removida->idade << endl;  

        (*pilha)->dosesRestantes--;

        if ((*pilha)->dosesRestantes == 0) {
            string nomeFrascoAtual = (*pilha)->nome;  
            descartarFrasco(pilha);

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
        cout << "2. Tirar pessoa da fila\n";
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
