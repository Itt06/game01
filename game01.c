#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char** argv){

    int T[51];
    
    //トランプ用意
    for(int i=0; i<52; i++){
        T[i] = i;
    }


    //トランプシャッフル
    srand((unsigned) time(NULL));
    int ransu, tmp;
    for(int i=0; i<50; i++){
        ransu = rand() % (51-i);
        tmp = T[ransu];
        T[ransu] = T[51-i];
        T[51-i] = tmp;
    }

    for(int i=0; i<50; i++){
        printf("%d\n",T[i]);
    }
    return 0;
}