#include <iostream>
using namespace std;

struct arvore_bin {
    int valor;
    arvore_bin* esquerda;
    arvore_bin* direita;
};

arvore_bin* insercao(arvore_bin* root, int valor) {
    if (root == nullptr) {
        root = (arvore_bin*)malloc(sizeof(arvore_bin));
        root->esquerda = nullptr;
        root->direita = nullptr;
        root->valor = valor;
        return root;
    }

    if (valor < root->valor) {
        root->esquerda = insercao(root->esquerda, valor);
    }
    else {
        root->direita = insercao(root->direita, valor);
    }

    return root;
}

void imprimir(arvore_bin* root) {
    if (root != nullptr) {
        imprimir(root->esquerda);
        cout << root->valor << " ";
        imprimir(root->direita);
    }
}

arvore_bin* encontrarMinimo(arvore_bin* root) {
    while (root->esquerda != nullptr) {
        root = root->esquerda;
    }
    return root;
}

arvore_bin* deletarNo(arvore_bin* root, int valor) {
    if (root == nullptr) {
        system("cls");
        cout << "\nNo nao encontrado\n";
        return root;
    }

    if (valor < root->valor) {
        root->esquerda = deletarNo(root->esquerda, valor);
    } else if (valor > root->valor) {
        root->direita = deletarNo(root->direita, valor);
    } else {
        if (root->esquerda == nullptr && root->direita == nullptr) {
            free(root);
            system("cls");
            cout << "\nNo removido com sucesso\n";
            return nullptr;
        }
        else if (root->esquerda == nullptr) {
            arvore_bin* temp = root->direita;
            free(root);
            system("cls");
            cout << "\nNo removido com sucesso\n";
            return temp;
        } else if (root->direita == nullptr) {
            arvore_bin* temp = root->esquerda;
            free(root);
            system("cls");
            cout << "\nNo removido com sucesso\n";
            return temp;
        }
        else {
            arvore_bin* temp = encontrarMinimo(root->direita);
            root->valor = temp->valor;
            root->direita = deletarNo(root->direita, temp->valor);
        }
    }
    return root;
}

int main() {
    arvore_bin* root = nullptr;

    int valor, i = 9;

    while(i != 0) {
        cout << "Informe o que deseja fazer: (1 para Insercao, 2 para Imprimir, 3 para Deletar e 0 para Fechar)\n"; cin >> i;
        system("cls");
        if(i == 1) {
            cout << "Informe o valor que deseja inserir: "; cin >> valor;
            root = insercao(root, valor);
            system("cls");
        } else if(i == 2) {
            cout << "Arvore em ordem: ";
            imprimir(root);
            cout << "\n";
            system("pause");
            system("cls");
        } else if(i == 3) {
            cout << "Informe o valor que deseja apagar: "; cin >> valor;
            root = deletarNo(root, valor);
            system("pause");
            system("cls");
        }



    }

    return 0;
}
