
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
void Compare(){
     printf("teste1:aloca todos os numeros de 0 a 9, caso seje par o teste libera a memoriaque deveria ser armazenada. \n") ;
     printf("My Malloc:\n");
    for (int i = 0; i < 10; i++)
    {
        void *p=Alocar(i);
        if(i%2==0){
            Liberar(p);
        }else{
            printf("memoria:%p, armazeno:%d\n",p,i);
        }
        
        
    }
    printf("Malloc Original:\n");
      for (int i = 0; i < 10; i++)
    {
        void *p=malloc(i);
        if(i%2==0){
            free(p);
        }
        else{
            printf("memoria:%p, armazeno:%d\n",p,i);
        }
        
    }
    printf("--------------------------------\n");
    printf("teste2:compara quantos espacos em bytes ele e separado em um alocador 0\n");
    printf("Malloc Original\n");
    void *p1=malloc(sizeof (int));
    void *p2=malloc(sizeof (int));
    int diferenca=p2-p1;
    printf("diferenca: %d\n",diferenca);
   
    free(p1);
    free(p2);  
    printf("My Malloc\n");
    void *p3=Alocar(sizeof (int));
    void *p4=Alocar(sizeof (int));
     diferenca=p4-p3;
    printf("diferenca: %d\n",diferenca);
    Liberar(p3);
    Liberar(p4);
    
}