#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char** argv){

    //カード準備　cards[0][j]が黒、cards[1][j]が赤
    int cards[2][26];
    for(int i=0; i<2; i++){
        for(int j=0; j<25; j++){
            cards[i][j] = j;
        }
    }


    //フィッシャー・イェーツシャッフル
    srand((unsigned) time(NULL));
    int ransu_i, ransu_j, tmp;
    for(int i=0; i<50; i++){
        if(i<26){
            ransu_i = rand() % 2;
            ransu_j = rand() % (26-i);
            tmp = cards[ransu_i][ransu_j];
            cards[ransu_i][ransu_j] = cards[1][25-i];
            cards[1][25-i] = tmp;
        }
        else{
        ransu_j = rand() % (51-i);
        tmp = cards[0][ransu_j];
        cards[0][ransu_j] = cards[0][51-i];
        cards[0][51-i] = tmp;
        }
    }

    for(int i=0; i<2; i++){
        for(int j=0; j<52; j++){
            printf("%d\n", cards[i][j] );
        }
    }

    return 0;
}