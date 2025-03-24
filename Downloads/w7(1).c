//Write a function that takes an unsigned n and returns the value obtained by considering each base-10 digit as hexadecimal digit.
// I.e.   f(1457)=0x1457. Use bitwise operators
#include <stdio.h>
#include <stdint.h>

unsigned f(unsigned n){
    uint32_t r=0;
    int p=0;
    while(n>0){
        int d=n%10;
        r=r|(d<<(p));
        p=p+4;
        n=n/10;
    }
    return r;
}

//Write a function that checks if all nibbles of an unsigned have nondecreasing values from most to least significant. 
// f(0x6AD)=1, f(0x243)=0. Use bitwise operators.
unsigned f2(uint32_t n){
    while((n>>4)!=0){
        if((n&0xF)<((n>>4)&0xF)){
            return 0;
        }
        n=n>>4;
    }
    return 1;

}

int main(){
    uint32_t rhex=f(1247);
    printf("Ox%x\n", rhex);
    printf("Ox%x\n", f(2341));
    printf("%d\n", f2(0x243));
    printf("%d\n", f2(0x6AD));
    printf("%d\n", f2(0xA3E));
    return 0;
}