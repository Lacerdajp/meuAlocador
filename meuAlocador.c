
#include <stdio.h>
#include "meuAlocador.h"
#include <stdio.h>
#include <unistd.h>
#define TRUE 1
#define FALSE 0
#define ALINHAMENTO(x) ((x)) // alinhamento de tamanho de 8 bytes
// #define ALINHAMENTO(x) (((x) + (8 - 1)) & ~(8 - 1)) // alinhamento de tamanho de 8 bytes

Bloco *ptrBase = NULL;

void juntarBlocos(Bloco *ptrAtual)
{
    // printf("estou juntarBlocos\n");
    Bloco *proximo = (Bloco *)(((char *)ptrAtual) + ptrAtual->proximo);
    // printf("%p,%p\n",ptrAtual,proximo);
    if (ptrAtual->proximo && proximo->livre)
    {
        ptrAtual->tamanho += proximo->tamanho;
        ptrAtual->proximo = proximo->proximo;
       
    } 
    // printf("juntei\n");
}

void *Alocar(size_t tamanho)
{
    //  printf("Vou alocar Agora\n");
    Bloco *ptrAtual = ptrBase;
    Bloco *ptrAnterior = NULL;
    size_t alinhamentoTamanho = ALINHAMENTO(tamanho + sizeof(Bloco));
    // se o ponteiro nao for nao nulo e tiver tamanho menor que o alinhamento ou o ponteiro nao for livre. é percorrido o bloco
    //   while (ptrAtual && (ptrAtual->tamanho < alinhamentoTamanho || !ptrAtual->livre)) {
    //          ptrAnterior = ptrAtual;
    //          ptrAtual = ptrAtual->proximo;

    //  }
    Bloco *bestptr = NULL;
    Bloco *Antbestptr = NULL;
    // printf("Oii");
  
   
    while (ptrAtual)
    {
        if ((ptrAtual->tamanho > alinhamentoTamanho && ptrAtual->livre) && (bestptr == NULL || (bestptr->tamanho > ptrAtual->tamanho)))
        {
            
            Antbestptr = ptrAnterior;
            bestptr = ptrAtual;
        }
        // printf("Loop");
       
        
        ptrAnterior = ptrAtual;
        ptrAtual =(Bloco*)(((char*) ptrAtual)+ptrAtual->proximo);
        if (ptrAtual==ptrAnterior||ptrAnterior->tamanho==0)
        {
             
            break;
            
        }
        
   
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
    
    if (bestptr)
    {

       

        if (bestptr->tamanho >= alinhamentoTamanho + sizeof(Bloco))
        {
            //  printf("Estou dividindo dois blocos\n");
            Bloco *novo = (Bloco *)((char *)bestptr + alinhamentoTamanho);
            novo->tamanho = bestptr->tamanho - alinhamentoTamanho;
            novo->livre = TRUE;
            novo->proximo = (((char *)bestptr)+bestptr->proximo)-(char*)novo;
            // printf("%p,%p\n",novo,(Bloco*)(novo->proximo+(char*)novo));
            if (!Antbestptr)
            {

                ptrBase = novo;
            }

            bestptr->tamanho = tamanho;
            bestptr->livre = FALSE;
            bestptr->proximo = ((char*)novo)-((char*)bestptr);
        }
        else
        {
            //  printf("estou alocando neste bloco\n");
            bestptr->livre = FALSE;
        }
        return (void *)(bestptr + 1);
    }
    else
    {
        //  printf("Estou alocando um  espaço no Final da memoria \n");
        //  printf("Test 3\n");
       
        Bloco *novo = sbrk(alinhamentoTamanho);

        if (novo == (void *)-1)
        {
            return NULL;
        }
       
        
        novo->tamanho = alinhamentoTamanho;
        novo->livre = FALSE;
        novo->proximo = (char*)NULL;
         
        if (ptrAnterior)
        {
            ptrAnterior->proximo = ((char*)novo)-((char*)ptrAnterior);
        }
        else
        {
            ptrBase = novo;
        }

        ptrAtual = novo;
    
    }
    // printf("%d\n",ptrAtual->proximo);
    return (void *)(ptrAtual + 1);
}

void Liberar(void *ptr)
{
    // printf("Estou Liberando a memoria \n");
    if (!ptr)
    {
        return;
    }
    // printf("Estou Liberando\n");
    Bloco *ptrAtual = (Bloco *)ptr - 1;
    ptrAtual->livre = TRUE;
    juntarBlocos(ptrAtual);
    if (ptrAtual->proximo == NULL)
    {
        Bloco *atual = ptrBase;
        Bloco *anterior = NULL;
        while (atual != ptrAtual)
        {
            anterior = atual;
            atual =(Bloco*)((char*)atual+ atual->proximo);
            if (atual==anterior||anterior->tamanho==0)
        {
             
            break;
            
        }
        }
        if (anterior)
        {
            anterior->proximo = NULL;
        }
        else
        {
            ptrBase = NULL;
        }

        brk(ptrAtual);
    }
}
