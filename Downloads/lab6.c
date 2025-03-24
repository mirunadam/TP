#include <stdio.h>
#include <math.h>
#include <time.h>

int ex1(int k)
{
  int a=1, b=1, c=(-2)*k;
  int delta = b*b-4*a*c;
  float x1 = (-b-sqrt(delta))/2*a;
  float x2 = (-b+sqrt(delta))/2*a;
  int n=0;
  if(x1>0)
    n=(int)x1;
  else
    n=(int)x2;
  if(k == (n*(n+1))/2)
    return n;
  return k-(n*(n+1))/2;
}

int ex2(int k)
{
  int a=1, b=1, c=(-2)*k;
  int delta = b*b-4*a*c;
  float x1 = (-b-sqrt(delta))/2*a;
  float x2 = (-b+sqrt(delta))/2*a;
  int n=0;
  if(x1>0)
    n=(int)x1;
  else
    n=(int)x2;
  if(k == (n*(n+1))/2)
    return 1;
  return n+2-(k-(n*(n+1))/2);
}

void ex3()
{
  int ap[999] = {0};
  int nr;
  while((scanf("%d",&nr)))
    {
      if(nr<=999 && nr>=100)
	{
	   ap[nr]++;
	}
      if(nr==0)
	break;
    }
  int ct=0;
  for(int i=999; i>=100; i--)
    {
      if(ap[i] == 0)
	{
	  printf("%d \n",i);
	  ct++;
	}
      if(ct==3)
	break;
    }
}

int main(void)
{
  clock_t start, end;
  double cpu_time_used;
  start = clock();

  //printf("%d \n", ex2(10));
  //printf("%d \n", ex2(3));
  ex3();

  end = clock();
  cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
  printf("%f \n", cpu_time_used);
  return 0;
}
