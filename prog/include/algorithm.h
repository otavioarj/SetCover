#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED

#include "generate_tad.h"

int * brute_force_sc(SUBSET *s);
void greedy_sc(SUBSET *s);
int *  isec(SUBSET *, int  [], int []);
int melhorEscolha(int *, int *, SUBSET *);
void imprime(SUBSET *);
#endif // ALGORITHM_H_INCLUDED
