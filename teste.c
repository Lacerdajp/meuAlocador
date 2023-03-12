#include<stdio.h>
#include<stdlib.h>
#include<time.h>
 #include"meuAlocador.h"

int main(){
       printf("TESTE 1 \n") ;
     printf("My Malloc:\n");
     void* ponteir[30];
     int quantidadeArmazenada=0;
     int quantidadeFragementada=0;
    for (int i = 0; i < 30; i++)
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
    for (int i = 0; i < 30; i++)
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
    printf("--------------------------------\n");
    printf("TESTE 2\n");
    printf("Malloc Original\n");
    void *p1=malloc(0);
    void *p2=malloc(0);
    void *p5=malloc(0);
    int diferenca=p5-p2;
    printf("p1= %p, p2=%p,diferenca: %d\n",p2,p5,diferenca);
   
    free(p1);
    free(p2);  
    printf("My Malloc\n");
    void *p3=Alocar(0);
    void *p4=Alocar(0);
     diferenca=p4-p3;
    printf("p1= %p, p2=%p, diferenca: %d\n",p3,p4,diferenca);
    Liberar(p3);
    Liberar(p4);
     printf("--------------------------------\n");
    printf("TESTE 3\n");
    printf("My Malloc\n");
    void *temp=NULL;
    for (int i = 0; i < 10; i++)
    {
         int diferenca=0;
        void *p=Alocar(100*i);
        if (temp!=NULL)
        {
            diferenca=p-temp;
        }
        
        temp=p;

        printf("memoria:%p, armazeno:%d,Diferença com a ultima alocação: %d\n",p,i*100,diferenca);
    }
     printf("Malloc Original\n");
     temp=NULL;
    for (int i = 0; i < 10; i++)
    {
        int diferenca=0;
        void *p=malloc(100*i);
        if (temp!=NULL)
        {
            diferenca=p-temp;
        }
        
        temp=p;

        printf("memoria:%p, armazeno:%d,Diferença com a ultima alocação: %d\n",p,i*100,diferenca);
    }
       printf("--------------------------------\n");
    printf("TESTE 4\n");
    printf("My MAlloc\n");
    clock_t tempo1;
    tempo1=clock();
    void*a=Alocar(10);
    void*b=Alocar(30);
    void *c= Alocar(20);
    printf("a=%p, b=%p, c=%p\n",a,b,c);
    Liberar(b);
    void *d=Alocar(3);
    void *x=Alocar(2);
     printf("d=%p, x=%p\n",d,x);
    
    // printf("d=%p\n",d);
    tempo1=clock()-tempo1;
    printf("Tempo: %lf\n",((double)(tempo1))/(CLOCKS_PER_SEC/1000000));
     printf("Malloc Original:\n");
     clock_t tempo2;
    tempo2=clock();
    void*e=malloc(10);
    void*f=malloc(30);
    void *g= malloc(20);
     printf("a=%p, b=%p, c=%p\n",e,f,g);
    free(f);
    void *h=malloc(3);
    void *y=malloc(2);
        printf("h=%p,y=%p\n",h,y);
        //  printf("h=%p\n",h);
  
    tempo2=clock()-tempo2;
    printf("Tempo: %lf\n",((double)(tempo2))/(CLOCKS_PER_SEC/1000000));
    printf("%d",(int)sizeof(Bloco));
    printf("--------------------------------\n");
    printf("TESTE 5\n");
    printf("My MAlloc\n");
    clock_t tempo3;
    tempo3=clock();
    a=Alocar(10);
    b=Alocar(40);
    c= Alocar(20);
    void*z=Alocar(30);
    void*n=Alocar(10);

    printf("a=%p, b=%p, c=%p,z=%p,n=%p\n",a,b,c,z,n);
    Liberar(b);
    Liberar(z);
    d=Alocar(3);
    x=Alocar(2);
     printf("d=%p, x=%p\n",d,x);
    
    // printf("d=%p\n",d);
 
    tempo3=clock()-tempo3;
    printf("Tempo: %lf\n",((double)(tempo3))/(CLOCKS_PER_SEC/1000000));
     printf("Malloc Original:\n");
     clock_t tempo4;
    tempo4=clock();
    e=malloc(10);
    void*j=malloc(40);
    g= malloc(20);
    void*m=malloc(30);
    void*k=malloc(10);
    printf("a=%p, b=%p, c=%p,z=%p,n=%p\n",e,j,g,m,k);
    free(j);
    free(m);
    void *p=malloc(3);
    void* s=malloc(2);
        printf("h=%p,y=%p\n",p,s);
        //  printf("h=%p\n",h);
    tempo4=clock()-tempo4;
    printf("Tempo: %lf\n",((double)(tempo4))/(CLOCKS_PER_SEC/1000000));
    return 0;
}