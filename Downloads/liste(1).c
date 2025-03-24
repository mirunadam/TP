#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long Payload_t;

typedef struct nod
{
  Payload_t info;
  struct nod* urm;
}Nod_t;

typedef Nod_t* Lista_t;


Nod_t* make_nod(Payload_t info)
{
  Nod_t* nod = malloc(sizeof(Nod_t));
  if(!nod)
    return NULL;
  nod->info = info;
  nod->urm = NULL;
  return nod;
}

Lista_t add_front(Lista_t lista, Nod_t* nod)
{
  if(lista == NULL)
    {
      nod->urm = NULL;
      return nod;
    }
  else
    {
      nod->urm = lista;
      lista = nod;
      return lista;
    }
}

void print_lista(Lista_t lista)
{
  for(Nod_t* nod=lista; nod!=NULL; nod=nod->urm)
    printf("%llu ", nod->info);
  printf("\n");
}

Payload_t* make_tab_elem(int nr_elem)
{
  Payload_t* elem = malloc(nr_elem*sizeof(Payload_t));
  if(elem == NULL)
    {
      printf("Eroare la alocare \n");
      exit(EXIT_FAILURE);
    }
  for(int i=0; i<nr_elem; i++)
    elem[i] = i+1;
  return elem;
}

Lista_t make_lista(Payload_t* elem, int nr_elem)
{
  Lista_t lista = NULL;
  for(int i=0; i<nr_elem; i++)
    {
      lista = add_front(lista, make_nod(elem[i]));
    }
  return lista;
}

Payload_t* elem_from_list(Lista_t lista)
{
  Payload_t *elem = NULL;

  int nr_elem = 0;
  for(Nod_t* nod=lista; nod!=NULL; nod=nod->urm)
    nr_elem++;

  elem = malloc(nr_elem*sizeof(Payload_t));

  if(elem == NULL)
    {
      printf("Eroare la alocare \n");
      exit(EXIT_FAILURE);
    }

  Nod_t* nod = lista;
  for(int i=0; i<nr_elem; i++)
    {
      elem[i] = nod->info;
      nod = nod->urm;
    }
  return elem;
}

Lista_t add_poz(Lista_t lista, int k, Nod_t* nod)
{
  if(k==0)
    return add_front(lista, nod);

  Lista_t aux = lista;
  for(int i=0; aux->urm!=NULL && i<k-1; aux=aux->urm, i++);
  nod->urm = aux->urm;
  aux->urm = nod;
  return lista;
}

Lista_t delete_front(Lista_t lista)
{
  Nod_t* aux = lista;
  lista = lista->urm;
  free(aux);
  return lista;
}

Lista_t delete_poz(Lista_t lista, int k)
{
  if(k==0)
    return delete_front(lista);

  Lista_t l = lista;
  
  for(int i=0; i<k-2 && l->urm->urm!=NULL; i++)
    l=l->urm;
  if(l->urm->urm != NULL)
    {
      Nod_t* aux = l->urm->urm;
      l->urm->urm = l->urm->urm->urm;
      free(aux);
    }
  else
    {
      Nod_t* aux = l->urm;
      l->urm = NULL;
      free(aux);
    }
  return lista;
}


int main(void)
{
  Lista_t l1 = NULL, l2 = NULL;

  l1 = add_front(l1, make_nod(1));
  l1 = add_front(l1, make_nod(2));
  l1 = add_front(l1, make_nod(3));
  l1 = add_front(l1, make_nod(4));

  print_lista(l1);
  
  l1 = add_poz(l1,1, make_nod(10));
  l1 = add_poz(l1, 2, make_nod(20));
  l1 = add_poz(l1, 0, make_nod(30));
  l1 = add_poz(l1, 100, make_nod(999));
 
  print_lista(l1);

  l1 = delete_front(l1);

  print_lista(l1);

  l1 = delete_poz(l1, 0);
  print_lista(l1);
  l1 = delete_poz(l1, 2);
  print_lista(l1);
  l1 = delete_poz(l1, 100);
  print_lista(l1);
  

  //Payload_t* elem1 = elem_from_list(l1);
  

  /*int nr_elem2 = 10;
  Payload_t* elem2 = make_tab_elem(nr_elem2);
  l2 = make_lista(elem2, nr_elem2);
  print_lista(l2);*/
  
  return 0;
}
