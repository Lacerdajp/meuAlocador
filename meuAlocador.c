
#include<stdio.h>
#include"meuAlocador.h"
#define ALINHAMENTO(x) (((x)+(8-1))&~(8-1))//alinhamento de tamanho de 8 bytes
#define TAMANHO_HEAP (int)sizeof(HeapStruct)//tamanho de acordo com a struct
// HeapStruct memoriaLivre;
HeapStruct *ponteiroInicial=NULL;


HeapStruct*  EncontrarPosicao(HeapStruct *antiga,int tamanho){
    HeapStruct *posicaoEncontrada= ponteiroInicial;
    while (posicaoEncontrada && !( posicaoEncontrada->livre&& posicaoEncontrada->tamanho>= tamanho ))
    {
        *antiga=*posicaoEncontrada;
        posicaoEncontrada=posicaoEncontrada->prox;
    }
    return posicaoEncontrada;
    
}
HeapStruct *IncluirHeap(HeapStruct *anterior, int tamanho){
     HeapStruct *ptr;
     ptr=sbrk(0);
     if (sbrk(TAMANHO_HEAP + tamanho)==(void*)-1)
     {
        return NULL;
     }
    ptr->tamanho=tamanho;
    ptr->prox=NULL;
    ptr->ant=anterior;
    ptr->livre=0;
    if (anterior)
    {
        anterior->prox=ptr;
    }
    return ptr;
}
   


// void* InitAlocador(){
//     memoriaLivre.tamanho=NULL;
//     memoriaLivre.livre=1;
//     memoriaLivre.anterior=NULL;
//     memoriaLivre.prox=NULL;
// }

void* Alocar(int tamanhoAlocar){
        HeapStruct memoriaAlocar, memoriaAnterior;
        int tamanho=ALINHAMENTO(tamanhoAlocar);
        if (ponteiroInicial)
        {
            /* code */
        }else{
            memoriaAlocar
        }
        
         return ptr;
}
// int  Liberar(void *alocado){
    
   
    
    
// }
// void Compare(){
//      printf("teste1:aloca todos os numeros de 0 a 9, caso seje par o teste libera a memoriaque deveria ser armazenada. \n") ;
//      printf("My Malloc:\n");
//     for (int i = 0; i < 10; i++)
//     {
//         void *p=Alocar(i);
//         if(i%2==0){
//             Liberar(p);
//         }else{
//             printf("memoria:%p, armazeno:%d\n",p,i);
//         }
        
        
//     }
//     printf("Malloc Original:\n");
//       for (int i = 0; i < 10; i++)
//     {
//         void *p=malloc(i);
//         if(i%2==0){
//             free(p);
//         }
//         else{
//             printf("memoria:%p, armazeno:%d\n",p,i);
//         }
        
//     }
//     printf("--------------------------------\n");
//     printf("teste2:compara quantos espacos em bytes ele e separado em um alocador 0\n");
//     printf("Malloc Original\n");
//     void *p1=malloc(sizeof (int));
//     void *p2=malloc(sizeof (int));
//     int diferenca=p2-p1;
//     printf("diferenca: %d\n",diferenca);
   
//     free(p1);
//     free(p2);  
//     printf("My Malloc\n");
//     void *p3=Alocar(sizeof (int));
//     void *p4=Alocar(sizeof (int));
//      diferenca=p4-p3;
//     printf("diferenca: %d\n",diferenca);
//     Liberar(p3);
//     Liberar(p4);
    
// }