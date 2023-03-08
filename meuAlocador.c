
#include<stdio.h>
#include"meuAlocador.h"
#include <stdio.h>
#include <unistd.h>

#define ALINHAMENTO(x) (((x) + (8 - 1)) & ~(8 - 1)) // alinhamento de tamanho de 8 bytes


Bloco *ptrBase = NULL;

void percorrerBlocos(Bloco * ptrAtual,Bloco*ptrAnterior){
        ptrAnterior = ptrAtual;
        ptrAtual = ptrAtual->proximo;
    
}
void juntarBlocos(Bloco* ptrAtual){
       if (ptrAtual->proximo && ptrAtual->proximo->livre) {
        ptrAtual->tamanho += ptrAtual->proximo->tamanho;
        ptrAtual->proximo = ptrAtual->proximo->proximo;
    }
}

void *Alocar(size_t tamanho) {
    Bloco *ptrAtual = ptrBase;
    Bloco*ptrAnterior = NULL;
    size_t alinhamentoTamanho = ALINHAMENTO(tamanho + sizeof(Bloco));
    //se o ponteiro nao for nao nulo e tiver tamanho menor que o alinhamento ou o ponteiro nao for livre. é percorrido o bloco
     while (ptrAtual && (ptrAtual->tamanho < alinhamentoTamanho || !ptrAtual->livre)) { 
        percorrerBlocos(ptrAtual,ptrAnterior);
     }
    if (ptrAtual) {
        if (ptrAtual->tamanho >= alinhamentoTamanho + sizeof(Bloco)) {
            Bloco *novo = (Bloco *)((char *)ptrAtual + alinhamentoTamanho);
            novo->tamanho = ptrAtual->tamanho - alinhamentoTamanho;
            novo->livre = 1;
            novo->proximo = ptrAtual->proximo;

            if (ptrAnterior) {
                ptrAnterior->proximo = novo;
            } else {
                ptrBase = novo;
            }

            ptrAtual->tamanho = alinhamentoTamanho;
            ptrAtual->livre = 0;
            ptrAtual->proximo = novo;
        } else {
            ptrAtual->livre = 0;
        }
    } else {
        Bloco *novo= sbrk(alinhamentoTamanho);
        if (novo == (void *)-1) {
            return NULL;
        }

        novo->tamanho = alinhamentoTamanho;
        novo->livre = 0;
        novo->proximo = NULL;

        if (ptrAnterior) {
            ptrAnterior->proximo = novo;
        } else {
            ptrBase = novo;
        }

        ptrAtual = novo;
    }

    return (void *)(ptrAtual+ 1);
}

void Liberar(void *ptr) {
    if (!ptr) {
        return;
    }

    Bloco *ptrAtual = (Bloco *)ptr - 1;
    ptrAtual->livre = 1;
    juntarBlocos(ptrAtual);
    if (ptrAtual->proximo == NULL) {
        Bloco *atual= ptrBase;
        Bloco*anterior = NULL;
        while (atual != ptrAtual) {
            percorrerBlocos(atual,anterior);
        }
        if (anterior) {
            anterior->proximo = NULL;
        } else {
            ptrBase = NULL;
        }

        brk(ptrAtual);
    }
}

