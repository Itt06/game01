#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char** argv){

    //カード準備　cards[0][j]が黒、cards[1][j]が赤
    int cards[2][26];
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 26; j++){
            cards[i][j] = j;
        }
    }


    //フィッシャー・イェーツシャッフル
    int tmp, row, col;
    srand((unsigned) time(NULL));
    for(int i = 0; i < 50; i++){
        int ransu = rand() % (51 - i);
        if(ransu > 25){         //通し番号をつけて二次元配列を一次元に対応させる
            row = 1;
            col = ransu - 26;
        }
        else{
            row = 0;
            col = ransu;
        }
        int row_last = 1, col_last = 25;       //cards[1][j]を全部入れ替えたらcards[0][j]に移行する
        if(i > 25){
            row_last = 0;
            col_last = 51;
        }
        tmp = cards[row][col];
        cards[row][col] = cards[row_last][col_last - i];
        cards[row_last][col_last - i] = tmp;
    }

    //カードを表示する
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            printf("%d", cards[i % 2][i / 2 * 13 + j]);
            printf(" ");
        }
        printf("\n");
    }

    return 0;
}