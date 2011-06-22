#include <stdio.h>
#include <stdlib.h>

#define MAX_CONJ 10     //numero maximo de entradas
#define MAX_SUBCONJ 30   //numero maximo de subconjuntos por alfabeto
#define MAX_ALFABETO 10  //tamanho maximo de um alfabeto
#define VAL_ELEM 20      //valor maximo de um elemento


int pertence(int elem, int* vetor,int tam) //verifica se elemento pertence ao alfabeto "vetor"
{
	int i;
	for(i=1;i<=tam;i++){
		if(elem == vetor[i])
			return 0;
	}
	return 1;		
}

int insere(int elem,int*vetor,int tam) //essa eh obvia neh?
{
	int i=1;

	while(elem > vetor[i] && vetor[i]!=NULL && i<tam)
	{	
				i++;
	}

	vetor[i] = elem;
	return 1;
}

int ordena(int*vetor,int tam)
{
 int i, j, chave;
 
        for(j=1; j<tam+1; j++) 
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



int *gera_conjunto(int *alfabeto,int tam_subconjunto, int tam_alfabeto)
{
	int i,k=0;	
	int* subconjunto;
	subconjunto = malloc((tam_subconjunto+1)*sizeof(int));
	subconjunto[0] = tam_subconjunto;

	for(i=1;i <= tam_subconjunto;i++)
	{
		k = rand()%tam_alfabeto;		
		subconjunto[i] = alfabeto[k];
	}
	ordena(subconjunto,tam_subconjunto);
	return subconjunto;
}

int gera_entrada(FILE *arquivo)
{
	int nro_entradas,tam_alfabeto,nro_subconj,tam_subconj,cont,flag,elem,i,indice,chuchu;
	int *alfabeto,*conj;	
	arquivo = fopen("entrada.txt","a");
	nro_entradas = rand()%MAX_CONJ;  // %10	
	

	for(i=0;i<nro_entradas;i++)
	{
		fprintf(arquivo,"%s","inicio");	
		cont = 0;
		tam_alfabeto = rand()%MAX_ALFABETO+1;// %8
		alfabeto = malloc((tam_alfabeto+1)*sizeof(int)); //+1 pq a primeira posicao eh o tamanho dele
		alfabeto[0] = tam_alfabeto;
		
		while(cont != tam_alfabeto)
		{
			//flag = 0;
			elem = rand()%VAL_ELEM;			//elemento do alfabeto %20
			
			if(pertence(elem,alfabeto,tam_alfabeto))
			{
				alfabeto[cont+1] = elem;				
				//insere(elem,alfabeto,tam_alfabeto);
				cont++;
			}		
		}
		ordena(alfabeto,tam_alfabeto); //alfabeto vai estar em ordem crescente
		fprintf(arquivo,"\n");
		for(indice=0; indice < tam_alfabeto+1;indice++)
			fprintf(arquivo,"%d ",alfabeto[indice]);				
				
		nro_subconj = rand()%MAX_SUBCONJ; //%20
		fprintf(arquivo,"\nnro de subconj=%d \n",nro_subconj);

		for(indice=0;indice<nro_subconj;indice++)
		{
			//printf("\n%d %d",tam_alfabeto,tam_subconj);
			tam_subconj = rand()%tam_alfabeto;
			conj = gera_conjunto(alfabeto,tam_subconj,tam_alfabeto);
			
			for(chuchu=0;chuchu<tam_subconj+1;chuchu++)
			{
				fprintf(arquivo,"%d ",conj[chuchu]);
			}
			fprintf(arquivo,"\n");

		}

	}
	free(alfabeto);
	free(conj);
	fprintf(arquivo,"\nfim");
	fclose(arquivo);
}

int main()
{
	int status;	
	FILE *arquivo;
	status = gera_entrada(arquivo);
	return 1;
}


