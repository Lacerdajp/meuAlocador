
#include<stdio.h>
#include"meuAlocador.h"
//tamanho maximo  da memoria:
#define TAMANHO_HEAP_TOTAL 640000//64 bytes
#define TAMANHO_HEAP_ALOCADA_TOTAL 1024//1byte

//heap Memoria:
char heap[TAMANHO_HEAP_TOTAL]={0};
int tamanhoHeap=0;
//heap alocadas:
HeapStruct heapAlocada[TAMANHO_HEAP_ALOCADA_TOTAL]={0};
int tamanhoHeapAlocada=0;

void* Alocar(int tamanhoAlocar){
  if(tamanhoAlocar+tamanhoHeap<=TAMANHO_HEAP_TOTAL&&tamanhoAlocar>0){
         void*ptr=heap+tamanhoHeap;
         tamanhoHeap+=tamanhoAlocar;
        for (int i = 0; i < tamanhoHeapAlocada; i++)
        {
            if(heapAlocada[i].livre!=0){
                heapAlocada[i].ponteiro=ptr;
                heapAlocada[i].tamanho=tamanhoAlocar;
                heapAlocada[i].livre=0;
                return ptr;
            }
        }
        
        HeapStruct  pedaco;
        pedaco.ponteiro=ptr;
        pedaco.tamanho=tamanhoAlocar;
        pedaco.livre=0;
        if (tamanhoHeapAlocada<TAMANHO_HEAP_ALOCADA_TOTAL)
        {
            heapAlocada[tamanhoHeapAlocada++]=pedaco;
        }
         return ptr;
    }else if(tamanhoAlocar==0){
        return  NULL;
    }
    else{
        printf("Memoria cheia impossivel Alocar");
    }
}
int  Liberar(void *alocado){
    HeapStruct temp;
    int x=0;
    for (int i = 0; i < tamanhoHeapAlocada; i++)
    {
        if (heapAlocada[i].ponteiro==alocado)
        {
            tamanhoHeap-=heapAlocada[i].tamanho;
            x=1;
            heapAlocada[i].ponteiro=NULL;
            heapAlocada[i].tamanho=NULL; 
            heapAlocada[i].livre=1;

        }
        if(x==1){
            temp=heapAlocada[i];
            heapAlocada[i]=heapAlocada[i+1];
            heapAlocada[i+1]=temp;
        }
        
    }
   
    
    
}
