#include <stdio.h>
#include <string.h>
#include <ctype.h>

int st[100] = {0};

int succesor(int st[], int k, int n)
{
  if(st[k] < n)
    {
      st[k]++;
      return 1;
    }
  return 0;
}

int vocala(char c)
{
  if(strchr("aeiou",c))
    return 1;
  return 0;
}

int consoana(char c)
{
  if(!vocala(c) && isalpha(c))
    return 1;
  return 0;
}

int valid(int st[], int k, char* cuv)
{
  if((vocala(cuv[st[k]-1]) && vocala(cuv[st[k-1]-1])) || (consoana(cuv[st[k]-1]) && consoana(cuv[st[k-1]-1])))
    return 0;
  else
    for(int i=0; i<k; i++)
      if(st[i] == st[k])
        return 0;
  return 1;
}

int solutie(int st[], int k, int n)
{
  return k==n;
}

void tipar(int st[], int k, char* cuv)
{
  for(int i=1; i<=k; i++)
    printf("%c", cuv[st[i]-1]);
  printf("\n");
}

  void back(int n, char* cuv)
{
  int k = 1;
  st[k] = 0;
  while(k > 0)
    {
      if(succesor(st,k,n))
	{
	  if(valid(st,k,cuv))
	    {
	      if(solutie(st,k,n))
		tipar(st,k,cuv);
	      else
		{
		  k++;
		  st[k] = 0;
		}
	    }
	}
      else
	k--;
    }
}

int main(void)
{
  char cuv[] = "cosmina";
  back(strlen(cuv), cuv);
  return 0;
}
