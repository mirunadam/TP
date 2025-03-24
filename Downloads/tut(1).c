#include<stdio.h>
#include <math.h>

unsigned long int factorial(unsigned n){
    if(n<=1)
        return 1;
    return n*factorial(n-1);
}

double taylor(double x, unsigned int n){
    double term=pow(x,n)/factorial(n);
    if (term<1e-6){
        return term;
    }
    return term+taylor(x,n+1, sum);
}

double taylor_wrapper(double x){
    return taylor(x,0);
}

int main(){
    printf("Taylor series for x=2 is %lf", taylor_wrapper(2));
    return 0;
}

//3 midterm
void trans(int n, int x, int k){

}
int get_max_num(){
    char ch;
    int x=0;
    int max=0;
    while((ch=getchar())!=EOF){
        if(isdigit(ch)==1){
            x=x*10+(ch-'0');
        }
        else if(isspace(ch || ch=='\n')){
            if(max<x){
                max=x;
            }
                x=0;
        }
        else{
            
        }
    }
}


