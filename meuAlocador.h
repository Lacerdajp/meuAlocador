#ifndef MEUALOCADOR_H
#define MEUALOCADOR_H
//estrutura:
struct Malloc{
void *ponteiro;
int tamanho;
int livre;
};typedef struct Malloc HeapStruct;
void* Alocar(int tamanhoAlocar);

int  Liberar(void *alocado);

#endif