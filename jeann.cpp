#include <iostream>
#include <cstdlib>
#include <math.h>

using namespace std;

typedef struct Node {
    int iPayLoad;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

typedef struct Cicle {
    Node* head;
    Node* tail;
} Cicle;

// ------------------------ FUNÇÕES PARA LISTA DUPLAMENTE ENCADEADA ------------------------

Node* createNode(int);
void printList(Node**);
void addElementList(Node**, int iPayLoad);
bool thereCicle(Node**);
//void deleteList(Node**);

// -------------------- FUNÇÕES PARA LISTA CÍCLICA DUPLAMENTE ENCADEADA --------------------

Cicle* createCicle();
void printCicle(Cicle*);
void addElementCicle(Cicle*, int);
Cicle* createCiclebyArray(int*, int);
int updateUp(Cicle*);
int updateDown(Cicle*);
void removeNodebyPosition(Cicle*, int);
void deleteCicle(Cicle*);
Cicle* intercallCicles(Cicle*, Cicle*);

Cicle* Ouroboros(int, int);

// -------------------------------------- DRIVER CODE --------------------------------------

int main() {
    
    // Seja Bem-Vindo a Questao 1 (^_^): PLAYLIST DE ELON LAGES
    
    // Criando uma Lista Cíclica por um Array
    int arr1[10] = {9, 2, 44, -2, 77, 9, 0, 0, 12, -999};
    Cicle* cicle1 = createCiclebyArray(arr1, 10);
    cout << "Ciclo 1: "; printCicle(cicle1);
    
    // Retornar ID e avançar a Lista
    cout << "ID (Ciclo 1): "; cout << updateUp(cicle1) << endl;
    cout << "Ciclo 1 - Apos Avancar: "; printCicle(cicle1);

    // Retornar ID e retroceder a Lista    
    cout << "ID (Ciclo 1): "; cout << updateDown(cicle1) << endl;
    cout << "Ciclo 1 - Apos Retroceder: "; printCicle(cicle1);
    
    // Removendo nó
    cout << "Removendo Primeiro Nó: "; removeNodebyPosition(cicle1, 9);
    printCicle(cicle1);
    
    // Intercalando Listas
    int arr2[7] = {1, 2, 3, 4, 5, 6, 7};
    Cicle* cicle2 = createCiclebyArray(arr2, 7);
    cout << "Ciclo 2: "; printCicle(cicle2);
    Cicle* cicle3 = intercallCicles(cicle1, cicle2);
    cout << "Ciclo 3: "; printCicle(cicle3);
    
    cout << "===============================================================================" << endl;
    
    // Seja Bem-Vindo a Questao 2 (^_^): LOOP EM LISTA DUPLAMENTE ENCADEADA
    
    // Criando Lista
    Node* list1 = createNode(0);
    for (int i = 1; i < 10; i++) {
        addElementList(&list1, i);
    }
    cout << "Lista 1: "; printList(&list1);
    
    // Criando um Loop na Lista Criada
    
    Node* current1;
    for (current1 = list1; current1->ptrNext != nullptr; current1 = current1->ptrNext);
    current1->ptrNext = list1;
    list1->ptrPrev = current1;
    
    // Verificando se há Loop na Lista Acima
    cout << "Há ciclo na Lista 1 (1 - SIM, 0 - NÃO): " << thereCicle(&list1) << endl;
    
    // Verificando se há Loop numa Lista sem Loop
    Node* list2 = createNode(0);
    for (int i = 1; i < 9; i++) {
        addElementList(&list2, i);
    }
    cout << "Lista 2: "; printList(&list2);
    
    cout << "Há ciclo na Lista 2 (1 - SIM, 0 - NÃO): " << thereCicle(&list2) << endl;
    
    // Verificando se há Loop numa Lista com Loop iniciando no meio
    // Criando a lista
    Node* list3 = createNode(0);
    for (int i = 1; i < 10; i++) {
        addElementList(&list3, i);
    }
    
    cout << "Lista 3: "; printList(&list3);
    
    // Construindo o loop a partir da 3ª posição (valor 3)
    Node* current3;
    for (current3 = list3; current3->ptrNext != nullptr; current3 = current3->ptrNext);
    current3->ptrNext = list3->ptrNext->ptrNext;
    
    cout << "Há ciclo na Lista 3 (1 - SIM, 0 - NÃO): " << thereCicle(&list3) << endl;
    
    cout << "===============================================================================" << endl;
    
    // Seja Bem-Vindo a Questao 3 (^_^): OUROBOROS
    
    // Validando Ouroboros Final = 320 -> (1, 2, 3)
    
    Cicle* cicle4 = Ouroboros(320, 3);
    cout << "OUROBOROS para (320, 3): "; printCicle(cicle4);
    
    // Validando Ouroboros Final = 12 -> (1, 1, 1)
    
    Cicle* cicle5 = Ouroboros(12, 3);
    cout << "OUROBOROS para (12, 3): "; printCicle(cicle5);
    
    // Validando Ouroboros Final = pow(2, 19) * 7 -> (1, 2, 3, 1)
    
    Cicle* cicle6 = Ouroboros(pow(2, 19) * 7, 4);
    cout << "OUROBOROS para (7*2^19, 4): "; printCicle(cicle6);
    
    cout << "===============================================================================" << endl;
    
    // Deletando os Ciclos
    deleteCicle(cicle1);
    deleteCicle(cicle2);
    deleteCicle(cicle3);
    deleteCicle(cicle4);
    deleteCicle(cicle5);
    deleteCicle(cicle6);
    
    //deleteList(list1);
    //deleteList(list2);
    
    cout << "Finalizando o Programa, BYE BYE (^_^) ..." << endl;
    
    return 0;
}



// -------------------- FUNÇÕES PARA LISTA DUPLAMENTE ENCADEADA --------------------

Node* createNode(int iPayLoad) {
    Node* node = (Node*) malloc(sizeof(Node));
    
    if (node != nullptr) {
        node->iPayLoad = iPayLoad;
        node->ptrPrev = nullptr;
        node->ptrNext = nullptr;
    }
    return node;
}

void printList(Node** head) {
    if (*head == nullptr) {
        cout << "Lista Vazia" << endl;
        return;
    }
    
    Node* current;
    for (current = *head; current->ptrNext != nullptr; current = current->ptrNext) {
        cout << current->iPayLoad << " ";
    }
    cout << current->iPayLoad << endl;
}

void addElementList(Node** head, int iPayLoad) {
    Node* temp = createNode(iPayLoad);
        
    if (*head == nullptr) {
        *head = temp;
    } else {
        Node* current;
        for (current = *head; current->ptrNext != nullptr; current = current->ptrNext);
        current->ptrNext = temp;
        temp->ptrPrev = current;
    }
}

bool thereCicle(Node** head) {
    Node* current1 = *head; //slow
    Node* current2 = *head; //fast
    
    while (current2 != nullptr) {
        current1 = current1->ptrNext;
        
        if (current2->ptrNext != nullptr) {
            if (current2->ptrNext->ptrNext != nullptr) {
                current2 = current2->ptrNext->ptrNext;
            } else {
                break;
            }
        } else {
            break;
        }
        
        if (current1 == current2) {
            return true;
        }
    }
    return false;
}

/*void deleteList(Node** head) {
    
}*/


// -------------------- FUNÇÕES PARA LISTA CÍCLICA DUPLAMENTE ENCADEADA --------------------

Cicle* createCicle() {
    Cicle* cicle = (Cicle*) malloc(sizeof(Cicle));
    
    if (cicle != nullptr) {
        cicle->head = nullptr;
        cicle->tail = nullptr;
    }
    return cicle;
}

void printCicle(Cicle* cicle) {
    if (cicle == nullptr) {
        cout << "Lista Vazia" << endl;
        return;
    }
    
    Node* current;
    for (current = cicle->head; current->ptrNext != cicle->head; current = current->ptrNext) {
        cout << current->iPayLoad << " ";
    }
    cout << current->iPayLoad << endl;
}

void addElementCicle(Cicle* cicle, int iPayLoad) {
    Node* node = createNode(iPayLoad);
    
    if (cicle->head == nullptr) {
        cicle->head = node;
        cicle->tail = node;
        cicle->head->ptrNext = cicle->tail;
        cicle->head->ptrPrev = cicle->tail;
        cicle->tail->ptrNext = cicle->head;
        cicle->tail->ptrPrev = cicle->head;
    } else {
        cicle->tail->ptrNext = node;
        node->ptrPrev = cicle->tail;
        node->ptrNext = cicle->head;
        cicle->head->ptrPrev = node;
        cicle->tail = node;
    }
}

Cicle* createCiclebyArray(int* arr, int iSize) {
    Cicle* cicle = createCicle();
    
    for (int i = 0; i < iSize; i++) {
        addElementCicle(cicle, arr[i]);
    }
    return cicle;
}

int updateUp(Cicle* cicle) {
    if (cicle->head == nullptr) {
        cout << "Lista Vazia" << endl;
        return 0;
    }
    
    int iPayLoad = cicle->head->iPayLoad;
    cicle->head = cicle->head->ptrNext;
    cicle->tail = cicle->tail->ptrNext;
    
    return iPayLoad;
}

int updateDown(Cicle* cicle) {
    if (cicle->head == nullptr) {
        cout << "Lista Vazia" << endl;
        return 0;
    }
    
    int iPayLoad = cicle->head->iPayLoad;
    cicle->head = cicle->head->ptrPrev;
    cicle->tail = cicle->tail->ptrPrev;
    
    return iPayLoad;
}

void removeNodebyPosition(Cicle* cicle, int iPayLoad) {
    if (cicle->head == nullptr) {
        cout << "Lista Vazia" << endl;
        return;
    }
    
    Node* current;
    for (current = cicle->head; current->ptrNext != cicle->head; current = current->ptrNext) {
        if (current->iPayLoad == iPayLoad) {
            break;
        }
    }

    if (current->iPayLoad != iPayLoad) {
        cout << "Valor não está na Lista" << endl;
    }

    if (current == cicle->head) {
        cicle->head = current->ptrNext;
    } else if (current == cicle->tail) {
        cicle->tail = current->ptrPrev;
    }
    
    current->ptrPrev->ptrNext = current->ptrNext;
    current->ptrNext->ptrPrev = current->ptrPrev;
    current->ptrPrev = nullptr;
    current->ptrNext = nullptr;
    
    free(current);
}

void deleteCicle(Cicle* cicle) {
    while (cicle->head != cicle->tail) {
        removeNodebyPosition(cicle, cicle->head->iPayLoad);
    }
    removeNodebyPosition(cicle, cicle->head->iPayLoad);
    free(cicle);
}

Cicle* intercallCicles(Cicle* cicle1, Cicle* cicle2) {
    Cicle* cicle = createCicle();
    
    Node* current1;
    Node* current2;
    
    for (current1 = cicle1->head, current2 = cicle2->head; (current1->ptrNext != cicle1->head && current2->ptrNext != cicle2->head); current1 = current1->ptrNext, current2 = current2->ptrNext) {
        addElementCicle(cicle, current1->iPayLoad);
        addElementCicle(cicle, current2->iPayLoad);
    }
    
    if (current1->ptrNext != cicle1->head) {
        addElementCicle(cicle, current2->iPayLoad);
        while (current1->ptrNext != cicle1->head) {
            addElementCicle(cicle, current1->iPayLoad);
            current1 = current1->ptrNext;
        }
        addElementCicle(cicle, current1->iPayLoad);
    } else if (current2->ptrNext != cicle2->head) {
        addElementCicle(cicle, current1->iPayLoad);
        while (current2->ptrNext != cicle2->head) {
            addElementCicle(cicle, current2->iPayLoad);
            current1 = current1->ptrNext;
        }
        addElementCicle(cicle, current2->iPayLoad);
    } else {
        addElementCicle(cicle, current1->iPayLoad);
        addElementCicle(cicle, current2->iPayLoad);
    }
    
    return cicle;
}

Cicle* Ouroboros(int iFinal, int iSize) {
    Cicle* cicle = createCicle();
    addElementCicle(cicle, iFinal);
    
    int iA, iB;
    for (int i = 0; i < iSize - 1; i++) {
        iA = 0, iB = 0;
        while ((cicle->head->iPayLoad % ((int) pow(2, iA))) == 0) {
            iA += 1;
        }
        iA -= 1;
        int iB = cicle->head->iPayLoad / pow(2, iA);
        iB = (iB - 1) / 2;
        addElementCicle(cicle, iB);
        cicle->head->iPayLoad = iA + 1;
    }
    
    return cicle;
}
