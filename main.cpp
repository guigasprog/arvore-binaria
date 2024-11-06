#include <iostream>
#include <cstdlib>
#include <queue>
using namespace std;

struct arvore_bin {
    int valor;
    arvore_bin* esquerda;
    arvore_bin* direita;
};


int profundidade(arvore_bin* root) {
    if (!root) return 0;
    return 1 + max(profundidade(root->esquerda), profundidade(root->direita));
}


int fatorBalanceamento(arvore_bin* root) {
    if (!root) return 0;
    return profundidade(root->esquerda) - profundidade(root->direita);
}


arvore_bin* rotacaoDireita(arvore_bin* y) {
    arvore_bin* x = y->esquerda;
    arvore_bin* T2 = x->direita;
    x->direita = y;
    y->esquerda = T2;
    return x;
}


arvore_bin* rotacaoEsquerda(arvore_bin* x) {
    arvore_bin* y = x->direita;
    arvore_bin* T2 = y->esquerda;
    y->esquerda = x;
    x->direita = T2;
    return y;
}


arvore_bin* rotacaoEsquerdaDireita(arvore_bin* root) {
    root->esquerda = rotacaoEsquerda(root->esquerda);
    return rotacaoDireita(root);
}


arvore_bin* rotacaoDireitaEsquerda(arvore_bin* root) {
    root->direita = rotacaoDireita(root->direita);
    return rotacaoEsquerda(root);
}


arvore_bin* balancear(arvore_bin* root, int valor) {
    int balance = fatorBalanceamento(root);
    if (balance > 1 && valor < root->esquerda->valor) return rotacaoDireita(root);
    if (balance < -1 && valor > root->direita->valor) return rotacaoEsquerda(root);
    if (balance > 1 && valor > root->esquerda->valor) return rotacaoEsquerdaDireita(root);
    if (balance < -1 && valor < root->direita->valor) return rotacaoDireitaEsquerda(root);
    return root;
}


arvore_bin* inserirNo(arvore_bin* root, int valor) {
    if (!root) {
        root = (arvore_bin*)malloc(sizeof(arvore_bin));
        root->valor = valor;
        root->esquerda = nullptr;
        root->direita = nullptr;
        return root;
    }
    if (valor < root->valor) root->esquerda = inserirNo(root->esquerda, valor);
    else if (valor > root->valor) root->direita = inserirNo(root->direita, valor);
    return balancear(root, valor);
}


arvore_bin* encontrarMinimo(arvore_bin* root) {
    while (root->esquerda) root = root->esquerda;
    return root;
}


arvore_bin* deletarNo(arvore_bin* root, int valor) {
    if (!root) return root;
    if (valor < root->valor) root->esquerda = deletarNo(root->esquerda, valor);
    else if (valor > root->valor) root->direita = deletarNo(root->direita, valor);
    else {
        if (!root->esquerda) {
            arvore_bin* temp = root->direita;
            free(root);
            return temp;
        } else if (!root->direita) {
            arvore_bin* temp = root->esquerda;
            free(root);
            return temp;
        }
        arvore_bin* temp = encontrarMinimo(root->direita);
        root->valor = temp->valor;
        root->direita = deletarNo(root->direita, temp->valor);
    }
    return balancear(root, valor);
}


void imprimirHierarquico(arvore_bin* root) {
    if (!root) return;
    queue<arvore_bin*> nivelAtual, nivelSeguinte;
    nivelAtual.push(root);
    while (!nivelAtual.empty()) {
        arvore_bin* noAtual = nivelAtual.front();
        nivelAtual.pop();
        if (noAtual) {
            cout << noAtual->valor << "   ";
            nivelSeguinte.push(noAtual->esquerda);
            nivelSeguinte.push(noAtual->direita);
        }
        if (nivelAtual.empty()) {
            cout << endl;
            swap(nivelAtual, nivelSeguinte);
        }
    }
}


void imprimirEmOrdem(arvore_bin* root) {
    if (root) {
        imprimirEmOrdem(root->esquerda);
        cout << root->valor << " ";
        imprimirEmOrdem(root->direita);
    }
}

int main() {
    arvore_bin* root = nullptr;
    int valor, opcao;
    while (true) {
        cout << "1. Inserir\n2. Imprimir Hierarquico\n3. Imprimir Em Ordem\n4. Deletar\n0. Sair\n";
        cin >> opcao;
        if (opcao == 1) {
            cout << "Valor: ";
            cin >> valor;
            root = inserirNo(root, valor);
            system("cls");
        } else if (opcao == 2) {
            cout << "Arvore Hierarquica:\n";
            imprimirHierarquico(root);
            cout << endl;
            system("pause");
            system("cls");
        } else if (opcao == 3) {
            cout << "Arvore em Ordem: ";
            imprimirEmOrdem(root);
            cout << endl;
            system("pause");
            system("cls");
        } else if (opcao == 4) {
            cout << "Valor para deletar: ";
            cin >> valor;
            root = deletarNo(root, valor);
            system("cls");
        } else if (opcao == 0) {
            break;
        }
    }
    return 0;
}
