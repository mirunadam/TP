#include<stdio.h>
#include<stdlib.h>
#include "coada.h"

struct coada{
  unsigned dim;
  unsigned cap;
  Element_t *data;
};


PQ_t creare_coada(unsigned cap)
{
  PQ_t cd=malloc(sizeof(struct coada));
  cd->dim=0;
  cd->data=malloc(cap*sizeof(Element_t));
  if(cd->data == NULL)
    {
      cd->cap=0;
      retur cd;
    }
  cd->cap=cap;
  return cd;
}

void afisare_coada(PQ_t cd)
{
  for(int i=0; i<cd->dim; i++)
    {
      printf("%d", cd->data[i]);
    }
}
