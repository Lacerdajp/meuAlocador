#include<stdio.h>
#include<stdlib.h>
#include"meuAlocador.h"
int main(){
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
    
    return 0;
}