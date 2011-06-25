#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX_INPUT 20
#define MAX_ALFA 10
#define FATOR 0.1


int pertence(int elem, int* vetor,int tam) //verifica se elemento pertence ao alfabeto "vetor"
{
	int i;
	for(i=1;i<tam;i++){
		if(elem == vetor[i])
			return 0;
	}
	return 1;
}

int ordena(int*vetor,int tam)
{
 int i, j, chave;
        for(j=1; j<=tam; j++)
        {
                chave = vetor[j];
                i = j-1;
                while(i >= 1 && vetor[i] > chave)
                {
                        vetor[i+1] = vetor[i];
                        i--;
                }
                vetor[i+1] = chave;
        }
}



void gera_entradaV2(FILE *file,int max_alfabeto,int qt_subconjuntos);
void imprime(int *vetor,int tam){
    int i;
    printf("\n");
    for(i=0;i<tam;i++){
        printf("%d ",vetor[i]);
    }
    printf("\n");
}
int main(){
    FILE *arq = fopen("entrada.in","w");
    int i;
    for(i=0;i<MAX_INPUT;i++){
        printf("Gerando entrada\n");
        gera_entradaV2(arq,MAX_ALFA,(rand()%MAX_ALFA)+1);
        printf("Entrada Gerada!\n");
    }
    fprintf(arq,"fim");
    fclose(arq);
}
void gera_entradaV2(FILE *file,int max_alfabeto,int qt_subconjuntos){
    int *alfabeto;
    int i,j;
    int tam_alfabeto=0;
    int tam_subconjunto;
    int num;
    int k;
    int anterior=0;
    alfabeto = (int *) malloc(sizeof(int)*max_alfabeto);
    int **subsets;
    for(i=0;i<max_alfabeto;i++){
        alfabeto[i] = 0;
    }
    //printf("Alfabeto comcando com tudo 0\n");
    subsets = (int **) malloc(sizeof(int *)*qt_subconjuntos);
    for(i=0;i<qt_subconjuntos;i++){
        srand(clock());

        do{
            srand(NULL);
            tam_subconjunto = ((rand()%max_alfabeto)*(FATOR)+1);
        }while(tam_subconjunto==anterior);
        printf("Tamanho do Subconjunto %d\n",tam_subconjunto);
        int *subconjunto = (int *) malloc(sizeof(int)*tam_subconjunto+1);
        subsets[i] = subconjunto;
        subconjunto[0] = tam_subconjunto;
        for(j=1;j<=tam_subconjunto;j++){
            //Para cada posicao do novo subconjunto
            anterior = tam_subconjunto;
            num = rand()%max_alfabeto;
           // printf("Elemento do Subconjunto %d\n",num);
            if(pertence(num,subconjunto,j)==1){
                //se nao pertence
                subconjunto[j] = num;
                if(alfabeto[num]==0)//novo elemento do alfabeto foi utilizado
                {
           //         printf("Novo elemento %d adicionado ao alfabeto\n",num);
                    tam_alfabeto++;
                }
                alfabeto[num]++;
            }
            else{
             //   printf("Elemento %d ja pertence ao subconjunto\n",num);
                j--;
            }


        }
        ordena(subconjunto,tam_subconjunto);
        imprime(subconjunto,tam_subconjunto);


    }
    fprintf(file,"inicio\n");

    fprintf(file,"%d ",tam_alfabeto);
    for(k=0;k<max_alfabeto;k++){
        if(alfabeto[k]>0)
            fprintf(file,"%d ",k);
    }
    fprintf(file,"\n%d\n",qt_subconjuntos);
    for(i=0;i<qt_subconjuntos;i++){
        fprintf(file,"%d ",subsets[i][0]);
        for(k=1;k<=subsets[i][0];k++){
            fprintf(file,"%d ",subsets[i][k]);
        }
        fprintf(file,"\n");
    }


    free(alfabeto);
    for(k=0;k<qt_subconjuntos;k++){
        free(subsets[k]);
    }
    free(subsets);
    return;
}
