#include <stdio.h>
#include <stdlib.h>

#define MAX_CONJ 10     //numero de entradas
#define MAX_SUBCONJ 30   //numero maximo de subconjuntos por alfabeto
#define MAX_ALFABETO 10  //tamanho maximo de um alfabeto
#define VAL_ELEM 20      //valor maximo de um elemento


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

void gera_conjunto(int *alfabeto,int tam_subconjunto, int tam_alfabeto,int *subconjunto,int *aux)
{
	int i,k;
	subconjunto[0] = tam_subconjunto;

	for(i=1;i <= tam_subconjunto;i++)
	{
		k = rand()%tam_alfabeto + 1;
		subconjunto[i] = alfabeto[k];
		aux[k] = aux[k]+1;
	}
	ordena(subconjunto,tam_subconjunto);
}

int calcula_vetor_complemento(int *aux,int tam_alfabeto)
{
	int i,cont=0;
	for(i=1;i<=tam_alfabeto;i++)
	{
		if(aux[i]==0)
			cont++;
	}
	return cont;
}

int gera_conjunto_complemento(int *alfabeto,int *aux,int tam_alfabeto,int *conj_compl,int tam_compl)
{
	int i,k=1;
	if(tam_compl!=0)
	{
		//conj_compl = malloc((cont+1)*sizeof(int));
		conj_compl[0] = tam_compl;
		for(i=1;i<=tam_alfabeto;i++){
			if(aux[i]==0){
				conj_compl[k] = aux[i];
				k++;
			}
		}
		//tam_compl = malloc(1*sizeof(int));
		//ordena(conj_compl,tam_compl);
		return 1;
	}
	else
		return 0;
}

int gera_entrada(FILE *arquivo)
{
	int nro_entradas,tam_alfabeto,nro_subconj,tam_subconj,cont,flag,elem,i,indice,chuchu;
	int *alfabeto,*conj,*aux,*conj_compl,*tam_compl;
	arquivo = fopen("entrada.txt","a");
	nro_entradas = MAX_CONJ;


	for(i=0;i<nro_entradas;i++)
	{
		fprintf(arquivo,"%s","inicio");
		cont = 0;
		tam_alfabeto = rand()%MAX_ALFABETO+1;
		alfabeto = malloc((tam_alfabeto+1)*sizeof(int)); //+1 pq a primeira posicao eh o tamanho dele
		alfabeto[0] = tam_alfabeto;
		aux = malloc((tam_alfabeto+1)*sizeof(int));

		for(indice=0;indice<=tam_alfabeto;indice++)
			aux[indice] = 0;

		while(cont != tam_alfabeto)
		{
			elem = rand()%VAL_ELEM;			//elemento do alfabeto %20

			if(pertence(elem,alfabeto,tam_alfabeto)==1)
			{
				alfabeto[cont+1] = elem;
				cont++;
			}
		}
		ordena(alfabeto,tam_alfabeto); //alfabeto vai estar em ordem crescente
		fprintf(arquivo,"\n");
		for(indice=0; indice < tam_alfabeto+1;indice++)
			fprintf(arquivo,"%d ",alfabeto[indice]);

		nro_subconj = rand()%MAX_SUBCONJ; //%20
		fprintf(arquivo,"\n%d \n",nro_subconj);

		for(indice=0;indice<nro_subconj;indice++)
		{
			tam_subconj = rand()%tam_alfabeto;
			conj = malloc((tam_subconj+1)*sizeof(int));
			gera_conjunto(alfabeto,tam_subconj,tam_alfabeto,conj,aux);

			for(chuchu=0;chuchu<tam_subconj+1;chuchu++)
			{
				fprintf(arquivo,"%d ",conj[chuchu]);
			}
			fprintf(arquivo,"\n");

		}

		int tam_compl = calcula_vetor_complemento(aux,tam_alfabeto);
		conj_compl = malloc((tam_compl+1)*sizeof(int));
		int chuchu2 = gera_conjunto_complemento(alfabeto,aux,tam_alfabeto,conj_compl,tam_compl);

		if(chuchu2!=0){
			for(chuchu=0;chuchu <= tam_compl; chuchu++)
				{
					fprintf(arquivo,"%d ",conj_compl[chuchu]);
				}
				fprintf(arquivo,"\n");
			}
	}
	free(alfabeto);
	free(conj);
	fprintf(arquivo,"\nfim");
	fclose(arquivo);
}

//int main()
//{
//	int status;
//	FILE *arquivo;
//	status = gera_entrada(arquivo);
//	return 1;
//}


