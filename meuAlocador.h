#ifndef MEUALOCADOR_H
#define MEUALOCADOR_H
//estrutura:

typedef struct Block {
    size_t tamanho;
    int livre;
    struct Block *proximo;
} Bloco;
void *Alocar(size_t size);

void Liberar(void *alocado);

// void Compare();
#endif