#include "../include/algorithm.h"

/* intersection of sets
 * subsets DEVEM estar ordenados!!
 OTAVIO VC ESTA RETORNANDO UM VETOR
 ISSO SEGUNDO VC MESMO NAO FUNCIONA
 EM OUTRA FUNCAO VC ESTA FAZENDO O SEGUINTE
 INT *CHUCHU = ISEC(.....);
 E DEPOIS VC ESTA ACESSANDO CHUCHU[0], CHUCHU[1] E CHUCHU[2]
 ISSO NAO VAI DAR CERTO
 * set1 e set2 são 2 vetores que representam 1 conjunto */
int * isec(SUBSET *s, int  set1[], int set2[])
{
	int *intsec,*aux;
	intsec=malloc(sizeof(int)*(set1[0]+set2[0]));
	short int i=0,j=0,k1=1,k2=1;
	int cnt=0;
  for(;i<s->size_alphabet;i++)
		{
			if(k1<=set1[0])
			 {
				if(s->alphabet[i]!=set1[k1])
					++j;
				else
					++k1;
			 }
			else
				j-=2;

			if(k2<=set2[0])
			 {
				if(s->alphabet[i]!=set2[k2])
					++j;
				else
					++k2;
			 }
			else
				j-=2;

			if(j!=2 && j!=-1 && j!=-4)
				intsec[++cnt]=s->alphabet[i];

			j=0;
		}
	intsec[0]=cnt;
	if(cnt>0)
	{
		aux=malloc(sizeof(int)*cnt);
		for(j=0;j<cnt;j++)
			aux[j]=intsec[j];
		free(intsec);
		intsec=aux;
	}
	return intsec;
}


// pelos contadores i,x e j recupera-se o grupo de conjuntos que gera a solução

int * brute_force_sc(SUBSET *s)
{
	short int i,x,k,j;
	int *intsec=0,*aux,tam,*set_cover;
	for(x=1;x<s->size_alphabet;++x)
	{
	 	for(i=0;i<s->size_alphabet;++i)
	   {
		  for(k=i;k<x + i -1 && x>1;++k)
			 {
				 if(k==i)
 				  intsec=isec(s,s->subsets[k],s->subsets[k+1]);
				 else
				  {
					 aux=intsec;
					 tam=intsec[0];
					 free(intsec);
					 aux[0]=tam;
					 intsec=isec(s,aux,s->subsets[k+1]);
			 	 }
			 }
			if(x==1)
			{
				intsec=malloc(sizeof(int)*(s->subsets[i][0]));
				for(k=0;k<s->subsets[i][0];k++)
					intsec[k]=s->subsets[i][k];
			}
			for(j=i+1;j<s->size_alphabet;++j)
			 {
		   	 aux=isec(s,intsec,s->subsets[j]);
				 if(aux[0]==s->size_alphabet)
				  {
						if(x==1)
						 {
							 set_cover=malloc(3*sizeof(int));
							 set_cover[0]=2;
							 set_cover[2]=i;
						 }
						else
						 {
              set_cover=malloc((x+2)*sizeof(int));
						  set_cover[0]=x+1;
						  for(k=0;k<x;k++)
							  set_cover[k+2]=i+k;
						  }
						set_cover[1]=j;
						return set_cover;
					}
				 free(aux);
			 }
			free(intsec);
		 }
  }
    return 0;
}
int melhorEscolha(int *vetAux, int *controleConjUsado, SUBSET *s){

	int qntElemDistintos=0, conjEscolhido=-1, i, j, qntElemDist=0;

	for(i=0;i<s->qt_subsets;i++){
	   if(controleConjUsado[i]==0){
		for(j=1;j<s->subsets[i][0];j++){
			if(vetAux[j-1]!=s->subsets[i][j]){
				qntElemDist++;
			}
		}
		if(qntElemDist>qntElemDistintos){
			qntElemDistintos=qntElemDist;
			conjEscolhido=i;

		}
	   }
	}
	controleConjUsado[conjEscolhido]=1;//registra o uso do conjunto
	return conjEscolhido;

}


void greedy_sc(SUBSET *s){

	int *setCover=(int*)malloc(s->qt_subsets*sizeof(int));
	int qntAlfabetoNaoIncluso=s->size_alphabet, vetAux[s->size_alphabet],i, qntConjUsada=0, jaIncluso=0, j, controleConjUsado[s->qt_subsets];

	for(i=0;i<s->size_alphabet;i++){
		vetAux[i]=-1;
	}

	for(i=0;i<s->qt_subsets;i++){
		controleConjUsado[i]=0;
	}


	while(qntAlfabetoNaoIncluso>0){
		setCover[qntConjUsada]=melhorEscolha(vetAux,controleConjUsado,s);
		printf("\nsetcover: %d",setCover[qntConjUsada]);

		for(j=1;j<s->subsets[setCover[qntConjUsada]][0];j++){
			for(i=0;i<(s->size_alphabet-qntAlfabetoNaoIncluso);i++){
				if(vetAux[i]==s->subsets[setCover[qntConjUsada]][j]){
					jaIncluso=1;
				}
			}
			if(jaIncluso==0){//registra os elementos que foram cobertos
				vetAux[s->size_alphabet-qntAlfabetoNaoIncluso]=s->subsets[setCover[qntConjUsada]][j];
			}
			jaIncluso=0;
			qntAlfabetoNaoIncluso--;
		}
		qntConjUsada++;

	}
	printf("\nQnt conj usada:%d \n",qntConjUsada);
	free(setCover);

}
void imprime(SUBSET *s){
    int i,j,k;
    printf("\nAlfabeto\n");
    for(i=0;i<s->size_alphabet;i++){
        printf("%d ",s->alphabet[i]);
    }
    printf("\nLista de Subconjuntos\n");
    for(j=0;j<s->qt_subsets;j++){
        printf("Subconjunto %d\t",j+1);
        for(k=1;k<=s->subsets[j][0];k++){
            printf("%d ",s->subsets[j][k]);
        }
        printf("\n");
    }
}
