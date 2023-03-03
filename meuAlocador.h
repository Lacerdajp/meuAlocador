#ifndef MEUALOCADOR_H
#define MEUALOCADOR_H
//estrutura:
typedef struct Malloc HeapStruct;
struct Malloc{
void *ponteiro;
int tamanho;
int livre;
HeapStruct*prox;
HeapStruct*ant;

};
void* Alocar(int tamanhoAlocar);

void Liberar(void *alocado);

void Compare();
#endif