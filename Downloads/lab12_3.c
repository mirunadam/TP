#include <stdio.h>
#include <stdlib.h>

int st[100] = {0};

int succesor(int st[], int k, int n)
{
  if(st[k] < 1)
    {
      st[k]++;
      return 1;
    }
  return 0;
}

int solutie(int st[], int k, int n)
{
  return k==n;
}

int valid(int st[], int k)
{
  if(k > 1)
    {
      if(abs(st[k]-st[k-1]) != 1 || st[1] != 0)
	return 0;
    }
  return 1;
}

void tipar(int st[], int k)
{
  for(int i=1; i<=k; i++)
    printf("%d ", st[i]);
  printf("\n");
}

void back(int n)
{
  int k = 1;
  st[k] = -1;
  while(k > 0)
    {
      if(succesor(st,k,n))
	{
	  if(valid(st,k))
	    {
	      if(solutie(st,k,n))
		tipar(st,k);
	      else
		{
		  k++;
		  st[k] = -1;
		}
	    }
	}
      else
	k--;
    }
}

int main(void)
{
  back(7);
  return 0;
}
