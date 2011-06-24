#include "../include/algorithm.h"

/* intersection of sets
 * subsets DEVEM estar ordenados!!
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
	for(x=1;x<s->qt_subsets;++x)
	{
	 	for(i=0;i<s->qt_subsets;++i)
	   {
		  for(k=i;k<x + i  && x>1 && k<s->qt_subsets;++k)
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
			for(j=i+1;j<s->qt_subsets;++j)
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
						free(aux);
						free(intsec);
						return set_cover;
					}
				 free(aux);
			 }
			free(intsec);
		 }
  }
}


int melhorEscolha(int *vetAux, int *controleConjUsado, SUBSET *s){

	int qntElemDistintos=0, conjEscolhido=-1, i, j, qntElemDist=0, k, encontrado=0;

	for(i=0;i<s->qt_subsets;i++){
	   qntElemDist=0;
	   if(controleConjUsado[i]==0){
		for(j=1;j<=s->subsets[i][0];j++){
		     encontrado=0;
		     for(k=1;k<=vetAux[0];k++){
			if(s->subsets[i][j]==vetAux[k]){
				encontrado=1;
			}
		     }
		     if(encontrado==0){
		     	qntElemDist++;
		     }

		}

		if(qntElemDist==0){
			controleConjUsado[i]=1;//caso em que todos os elementos de um conjunto ja foram cobertos, então ele não é mais utilizado
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




void *greedy_sc(SUBSET *s){

	int *setCover=(int*)malloc((s->qt_subsets+1)*sizeof(int));
	int qntAlfabetoNaoIncluso=s->size_alphabet, vetAux[s->size_alphabet+1],i, posLivre=1, jaIncluso=0, j, controleConjUsado[s->qt_subsets];

	vetAux[0]=0;//qnt de elementos ja cobertos
	for(i=1;i<s->size_alphabet;i++){
		vetAux[i]=-1;
	}

	for(i=0;i<s->qt_subsets;i++){
		controleConjUsado[i]=0;
	}

	setCover[0]=0;//qnt inicial de conjuntos na cobertura
	while(qntAlfabetoNaoIncluso>0){
		setCover[posLivre]=melhorEscolha(vetAux,controleConjUsado,s);
		printf("\nsetcover: %d",setCover[posLivre]);

		for(j=1;j<=s->subsets[setCover[posLivre]][0];j++){
			for(i=1;i<=vetAux[0];i++){
				if(vetAux[i]==s->subsets[setCover[posLivre]][j]){
					jaIncluso=1;
				}
			}
			if(jaIncluso==0){//registra os elementos que foram cobertos
				vetAux[(s->size_alphabet+1)-qntAlfabetoNaoIncluso]=s->subsets[setCover[posLivre]][j];
				vetAux[0]=(s->size_alphabet+1)-qntAlfabetoNaoIncluso;
				qntAlfabetoNaoIncluso--;
			}
			jaIncluso=0;
		}
		posLivre++;
		setCover[0]++;

	}

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
