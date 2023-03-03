#ifndef MEUALOCADOR_H
#define MEUALOCADOR_H
//estrutura:

typedef struct MemHeader {
    size_t size;
    int free;
    struct MemHeader *next;
} MemHeader;
void *Alocar(size_t size);

void Liberar(void *alocado);

// void Compare();
#endif