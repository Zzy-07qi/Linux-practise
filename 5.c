#include <stdio.h>


int cal(int num1,int num2){
        int tol=1;
    for(int i=1;i<=num1;i++){
        if(i==1){
            tol=2;
            continue;
        }
        tol+=i;
    }
    int line=num1*2;
    for(int i=1;i<=num2;i++){
        if(i==1){
            tol+=line;
            continue;
        }
        tol+=(line+(i-1)*2);
    }
    return tol;
}
int main(){
    printf("%d\n",cal(20,20));
    return 0;
}