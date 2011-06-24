#include "../include/main.h"

int main(int argc,char * argv[]){


    char end[3];
    FILE *report;
    SUBSET *s;
    clock_t t1,t2;
    int *sub1,*sub2,i;
    report = fopen("report.csv","w");
    scanf("%s",end);
    while(strcmp("fim",end)!=0){
        s=malloc(sizeof(SUBSET));
        getSUBSET(s);
        imprime(s);
        t1 = clock();
<<<<<<< HEAD
 //       sub1=brute_force_sc(s);
        printf("Calculou o forca bruta\n");
=======
        sub1=brute_force_sc(s);
        printf("Calculou o forca bruta\n");// %d %d %d %d %d\n",sub1[0],sub1[1],sub1[2],sub1[3],sub1[4]);
>>>>>>> b184418c03fb7e418ad425af7280678d267e60b5
        t2 = clock();
        //calcula o tempo total do forca bruta em ms
        float a = ((float) (t2-t1))/1000;
        t1 = clock();
        sub2=greedy_sc(s);
        printf("Calculou o guloso\n");
        t2 = clock();
        float b = ((float) (t2-t1))/1000;
        fprintf(report,"%d,%d,%6.6f,%6.6f;\n",s->size_alphabet,s->qt_subsets,a,b);
        scanf("%s",end);
        free(s->alphabet);
        for(i=0;i<s->qt_subsets;i++){
           free(s->subsets[i]); //desaloca cada subconjunto
        }
        free(s->subsets);//desaloca matriz*/
        free(s);
    }
    fclose(report);
    return 0;
}
