
#include<stdio.h>
#include"meuAlocador.h"
#include <stdio.h>
#include <unistd.h>
#define TRUE 1;
#define FALSE 0;
 #define ALINHAMENTO(x) ((x)) // alinhamento de tamanho de 8 bytes
// #define ALINHAMENTO(x) (((x) + (8 - 1)) & ~(8 - 1)) // alinhamento de tamanho de 8 bytes


Bloco *ptrBase = NULL;

void juntarBlocos(Bloco* ptrAtual){
       if (ptrAtual->proximo && ptrAtual->proximo->livre) {
        ptrAtual->tamanho += ptrAtual->proximo->tamanho;
        ptrAtual->proximo = ptrAtual->proximo->proximo;
    }
}

void *Alocar(size_t tamanho) {
    //  printf("Vou alocar Agora\n");
    Bloco *ptrAtual = ptrBase;
    Bloco*ptrAnterior = NULL;
    Bloco*ptrMelhor=NULL;
    size_t alinhamentoTamanho = ALINHAMENTO(tamanho + sizeof(Bloco));
    //se o ponteiro nao for nao nulo e tiver tamanho menor que o alinhamento ou o ponteiro nao for livre. é percorrido o bloco
    //  while (ptrAtual && (ptrAtual->tamanho < alinhamentoTamanho || !ptrAtual->livre)) {  
    //         ptrAnterior = ptrAtual;
    //         ptrAtual = ptrAtual->proximo;

    //  }
    Bloco* bestptr=NULL;
      while (ptrAtual) {
        if((ptrAtual->tamanho>alinhamentoTamanho && ptrAtual->livre)
        &&(bestptr==NULL||(bestptr->tamanho>ptrAtual->tamanho))){
            bestptr=ptrAtual;
        }  
            ptrAnterior = ptrAtual;
            ptrAtual = ptrAtual->proximo;
     }
    // if (ptrAtual) {
        
    //     //  printf("Estou alocando um  espaço no meio da memoria \n");
    //     if (ptrAtual->tamanho >= alinhamentoTamanho + sizeof(Bloco)) {
    //         Bloco *novo = (Bloco *)((char *)ptrAtual + alinhamentoTamanho);
    //         novo->tamanho = ptrAtual->tamanho - alinhamentoTamanho;
    //         novo->livre = TRUE;
    //         novo->proximo = ptrAtual->proximo;

    //         if (ptrAnterior) {
    //             ptrAnterior->proximo = novo;
    //         } else {
    //             ptrBase = novo;
    //         }

    //         ptrAtual->tamanho = alinhamentoTamanho;
    //         ptrAtual->livre = FALSE;
    //         ptrAtual->proximo = novo;
    //     } else {
    //         ptrAtual->livre = FALSE;
    //     }
     if (bestptr) {
        
        //  printf("Estou alocando um  espaço no meio da memoria \n");
        if (bestptr->tamanho >= alinhamentoTamanho + sizeof(Bloco)) {
            Bloco *novo = (Bloco *)((char *)bestptr + alinhamentoTamanho);
            novo->tamanho = bestptr->tamanho - alinhamentoTamanho;
            novo->livre = TRUE;
            novo->proximo = bestptr->proximo;

            if (ptrAnterior) {
                ptrAnterior->proximo =novo;
            } else {
                ptrBase = novo;
            }

            bestptr->tamanho = alinhamentoTamanho;
            bestptr->livre = FALSE;
            bestptr->proximo = novo;
        } else {
            bestptr->livre = FALSE;
        }
         return (void *)(bestptr+ 1);
    } else {
        //  printf("Estou alocando um  espaço no Final da memoria \n");
        Bloco *novo= sbrk(alinhamentoTamanho);
       
        if (novo == (void *)-1) {
            return NULL;
        }

        novo->tamanho = alinhamentoTamanho;
        novo->livre = FALSE;
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
    // printf("Estou Liberando\n");
    Bloco *ptrAtual = (Bloco *)ptr - 1;
    ptrAtual->livre = TRUE;
    juntarBlocos(ptrAtual);
    if (ptrAtual->proximo == NULL) {
        Bloco *atual= ptrBase;
        Bloco*anterior = NULL;
        while (atual != ptrAtual) {
                anterior = atual;
                atual = atual->proximo;       
        }
        if (anterior) {
            anterior->proximo = NULL;
        } else {
            ptrBase = NULL;
        }

        brk(ptrAtual);
    }
}
