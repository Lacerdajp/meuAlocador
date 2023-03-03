
#include<stdio.h>
#include"meuAlocador.h"
#define ALINHAMENTO(x) (((x)+(8-1))&~(8-1))//alinhamento de tamanho de 8 bytes
#define TAMANHO_HEAP 0//tamanho de acordo com a struct
// HeapStruct memoriaLivre; 
HeapStruct *ptrInicial=NULL;
HeapStruct* Juntar(HeapStruct* ptr){
    if (ptr->prox&&ptr->prox->livre)
    {
        ptr->tamanho=ptr->tamanho+ptr->prox->tamanho+TAMANHO_HEAP;
        ptr->prox=ptr->prox->prox;
        if (ptr->prox)
        {
            ptr->prox->ant=ptr;
        }
    }
    return ptr;
    
}
HeapStruct* ObterPosicao(void * ptr){
    char*temp=ptr;
    return ptr=temp-=TAMANHO_HEAP;
}
int ValidarPonteiro(void *ptr){
    if (ptrInicial) 
        if (ptr>ptrInicial&&ptr<sbrk(0))
            return ptr== ObterPosicao(ptr)->ponteiro;
    return 0;
    
}
HeapStruct*  EncontrarPosicao(HeapStruct *anterior,int tamanho){
    HeapStruct *posicaoEncontrada= ptrInicial;
    while (posicaoEncontrada && !( posicaoEncontrada->livre&& posicaoEncontrada->tamanho>= tamanho ))
    {
        *anterior=*posicaoEncontrada;
        posicaoEncontrada=posicaoEncontrada->prox;
    }
    return posicaoEncontrada;
    
}
HeapStruct *IncluirInicioHeap(HeapStruct *anterior, int tamanho){
     printf("OII");
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
HeapStruct * IncluirMeioHeap(HeapStruct *ptr,int tamanho){
     printf("OII");
    HeapStruct * nova=ptr+tamanho;
    nova->tamanho=ptr->tamanho-tamanho-TAMANHO_HEAP;
    nova->livre=1;
    nova->ant=ptr;
    ptr->tamanho=tamanho;
    ptr->prox=nova;
}
   


// void* InitAlocador(){
//     memoriaLivre.tamanho=NULL;
//     memoriaLivre.livre=1;
//     memoriaLivre.anterior=NULL;
//     memoriaLivre.prox=NULL;
// }

void* Alocar(int tamanhoAlocar){
        printf("OI");
        HeapStruct *ptr, *anterior;
        
        int tamanho=ALINHAMENTO(tamanhoAlocar);
       
        if (ptrInicial)
        {
            anterior=ptrInicial;
            ptr=EncontrarPosicao(anterior,tamanho);
            if(ptr){
                if (ptr->tamanho-tamanho>=(TAMANHO_HEAP+4))
                {
                    IncluirMeioHeap(ptr,tamanho);
                }
                ptr->livre=0;
                
            }else
            {
                ptr=IncluirInicioHeap(anterior,tamanho);
                if (!ptr)
                {
                    return NULL;
                }
                
            }
            
        }else{
            ptr=IncluirInicioHeap(NULL,tamanho);
            if (!ptr)
            {
                return NULL;
            }
            ptrInicial=ptr;
            
        }
        
         return ptr->ponteiro;
}
void  Liberar(void *alocado){
     printf("OII");
   HeapStruct *ptr;
   if (ValidarPonteiro(alocado))
   {
        ptr=ObterPosicao(alocado);
        ptr->livre=1;
        if (ptr->ant&& ptr->ant->livre)
        {
            ptr=Juntar(ptr->ant);
        }
        if (ptr->prox)
        {
            Juntar(ptr);
        }
        else
        {
            if (ptr->ant)
            {
                ptr->ant->prox=NULL;
            }
            else ptrInicial=NULL;
            brk(ptr);
        }
        
        
   }
   

    
    
 }
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
    
//}