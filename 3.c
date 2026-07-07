#include <stdio.h>
int whatmun(int vol,int col){
    int num=0;
    int tar=0;
    for(int i=1;i<=vol;i++){
        for(int j=1;j<=i;j++){
            if(i==vol){
                tar++;
               
            }
            num++;
             if(tar==col){
                    return num;
                }
        }
    }
}
int main()
{
    int vol=20;
    int col=20;
    int num=whatmun(vol,col);
    printf("%d",num);
    return 0;
}
