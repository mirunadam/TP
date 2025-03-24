#include <stdlib.h>
#include <stdio.h>

//rainbow tables --> password crackig
// 95 - ex 4
//Given an amount of money and a set of N coins and their values,
//print all possible ways to make the change

unsigned long long f[1000];

unsigned long int fib2(unsigned long int n){
    long int f[n+1];
    unsigned int i;

    f[0]=0;
    f[1]=1;

    for(i=2; i<=n; i++) f[i]=-1;

    if(n>2){
        for(i=2; i<=n; i++){
            if (f[i]<0)
            {
                f[i]=f[i-1]+f[i-2];
            }
        }
    }

    return (unsigned long int) f[n];
}

unsigned long long fib1(int n){

    if(n==0){
        return 0;
    }
    if(n==1){
        return 1;
    }
    else
        return fib1(n-1)+fib1(n-2);
}

unsigned long long fib3(int n){

    f[0]=0;
    f[1]=1;

    for(int i=2; i<=n; i++) f[i]=-1;

    if(n>2){
        for(int i=2; i<=n; i++){
            if (f[i]<0)
            {
                f[i]=f[i-1]+f[i-2];
            }
        }
    }
    return f[n];
}

unsigned long int fibMemo(int n){
    if (f[n]==-1)
    {
        if(n==0){
            f[n]=0;
        }
        if(n==1){
            f[n]=1;
        }
        f[n]=fibMemo(n-1)+fibMemo(n-2);
    }
    return f[n];
   
}

void fill_table(int n){
    for(int i=0; i<=n; i++){
        f[i]=-1;
    }
    fibMemo(n);
    //return f[n];
}


// 95 - ex 4
//Given an amount of money and a set of N coins and their values,
//print all possible ways to make the change

//sort the values of the coins 
//take the biggest value -> greedy
//pick 1 voin add to the total sum ++ till you dont overflow the sum
//take another value from the other array of coins (smol ones)
// col sum that needs to be computed, on the rows the value of the coins



int main(){
    unsigned long result;
    //result=fib2(100);
    //result = fib2(3);
    fill_table(3);
    printf("%ld\n", result);
    return 0;
}