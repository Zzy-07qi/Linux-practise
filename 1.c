#include <stdio.h>

int twoNum(int a){
    int num=0;
    while(a>0){
        int digit = a%10;
        a=a/10;
        if(digit==2){
            num++;
        }
    }
    return num;
}
 int main()
{
        int total=0;
    for(int i=1;i<=2020;i++){
        total+=twoNum(i);
    }
    printf("%d",total);
    return 0;
}
