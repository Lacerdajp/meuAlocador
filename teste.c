#include<stdio.h>
#include<stdlib.h>
#include"meuAlocador.h"
int main(){
    printf("OII");
    void *p3=Alocar(10);
    void *p4=Alocar(10);
    int diferenca=p4-p3;
    printf("diferenca: %d\n",diferenca);
    Liberar(p3);
    Liberar(p4);
    return 0;
}