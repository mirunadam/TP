#include <stdio.h>
#include <stdint.h>

//ex 1

int isSorted(unsigned t[], unsigned n){
    int count = 1;
    for(int i=0; i<n-2; i++){
        int dif=t[i]-t[i+1];
        int dif2=t[i+1]-t[i+2];
        if((dif)*(dif2)<0){
            count=count*(dif)*(dif2);
        }
    }
    if(count<0)
            return 0;
    return 1;
}

//ex 2
int arr(int x[], unsigned xn, int y[], unsigned yn){
    int count=0;
    for(int i=0; i<yn; i++){
        for(int j=0; j<xn; j++){
            if(x[i]==y[j])
                count=count+1;
        }
    }
    printf("%d", count);
    if(yn<=count)
        return 1;
    else 
        return 0;
}

int main(){
    int x[5]={1,2,3,4,5};
    int y[3]={1,3,5};
    unsigned x1[4]={2,3,5,1};
    printf("ex 1: %d\n", isSorted(x1, 4));
    printf("ex 2: %d\n", arr(x, 5, y, 3));
    return 0;
}