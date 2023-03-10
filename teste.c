#include<stdio.h>
#include<stdlib.h>
#include"meuAlocador.h"
int main(){
       printf("TESTE 1 \n") ;
     printf("My Malloc:\n");
     void* ponteir[20];
     int quantidadeArmazenada=0;
     int quantidadeFragementada=0;
    for (int i = 0; i < 20; i++)
    {
        int diferenca=0;
        ponteir[i]=Alocar(i);
        if (i>1)
        {
            diferenca=ponteir[i]-ponteir[i-2];
            
        }
        
       
        if(i%2==0){
            Liberar(ponteir[i]);
        }else{
           i==1? printf("memoria:%p, armazeno:%d\n",ponteir[i],i):printf("memoria:%p, armazeno:%d, diferenca ultimo: %d\n",ponteir[i],i,diferenca);
           quantidadeArmazenada=i+quantidadeArmazenada;
            quantidadeFragementada=diferenca-i+quantidadeFragementada;
        }
        
        
    }
    printf("quantidade de armazenamentos:%d,quantidade Fragementada: %d\n",quantidadeArmazenada,quantidadeFragementada);
    printf("Malloc Original:\n");
    quantidadeArmazenada=0;
    quantidadeFragementada=0;
    for (int i = 0; i < 20; i++)
    {
        int diferenca=0;
        ponteir[i]=malloc(i);
        if (i>1){
            diferenca=ponteir[i]-ponteir[i-2];
            
        }
        
       
        if(i%2==0){
            free(ponteir[i]);
        }else{
           i==1? printf("memoria:%p, armazeno:%d\n",ponteir[i],i):printf("memoria:%p, armazeno:%d, diferenca ultimo: %d\n",ponteir[i],i,diferenca);
            quantidadeArmazenada=i+quantidadeArmazenada;
            quantidadeFragementada=diferenca-i+quantidadeFragementada;
        }
        
        
    }
    printf("quantidade de armazenamentos:%d,quantidade Fragementada: %d\n",quantidadeArmazenada,quantidadeFragementada);
    // printf("--------------------------------\n");
    // printf("TESTE 2\n");
    // printf("Malloc Original\n");
    // void *p1=malloc(20);
    // void *p2=malloc(20);
    // int diferenca=p2-p1;
    // printf("diferenca: %d\n",diferenca);
   
    // free(p1);
    // free(p2);  
    // printf("My Malloc\n");
    // void *p3=Alocar(20);
    // void *p4=Alocar(20);
    //  diferenca=p4-p3;
    // printf("diferenca: %d\n",diferenca);
    // Liberar(p3);
    // Liberar(p4);
    //  printf("--------------------------------\n");
    // printf("TESTE 3\n");
    // printf("My Malloc\n");
    // void *temp=NULL;
    // for (int i = 0; i < 10; i++)
    // {
    //      int diferenca=0;
    //     void *p=Alocar(100*i);
    //     if (temp!=NULL)
    //     {
    //         diferenca=p-temp;
    //     }
        
    //     temp=p;

    //     printf("memoria:%p, armazeno:%d,Diferença com a ultima alocação: %d\n",p,i*100,diferenca);
    // }
    //  printf("Malloc Original\n");
    //  temp=NULL;
    // for (int i = 0; i < 10; i++)
    // {
    //     int diferenca=0;
    //     void *p=malloc(100*i);
    //     if (temp!=NULL)
    //     {
    //         diferenca=p-temp;
    //     }
        
    //     temp=p;

    //     printf("memoria:%p, armazeno:%d,Diferença com a ultima alocação: %d\n",p,i*100,diferenca);
    // }
    
    
    return 0;
}