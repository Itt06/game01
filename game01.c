#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void showCards(int x, int y);
int cards[2][26];

int main(int argc,char** argv){

    //カード準備　cards[0][j]が黒、cards[1][j]が赤
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


    //説明
    printf("神経衰弱\nこの神経衰弱は色も一致しなければとれません。\n");


    //
    int x1, y1, x2, y2;

    showCards(-1, -1);
    while(1){
        //一枚目のカード
        printf("最初に選ぶカードの座標を入力してください。\n");
        printf("X = ");
        scanf("%d", &x1);
        printf("Y = ");
        scanf("%d", &y1);
        showCards(x1, y1);

        //二枚目のカード
        printf("次に選ぶカードの座標を入力してください。\n");
        printf("X = ");
        scanf("%d", &x2);
        printf("Y = ");
        scanf("%d", &y2);

        //判定
        if(cards[x1][y1] == cards[x2][y2]){
            cards[x1][y1] = -1;
            cards[x2][y2] = -1;
            printf("正解\n");
        }
        else{
            printf("不正解\n");
        }
        showCards(-1,-1);



        break;
    }


    
    


    //答え合わせ
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            if(cards[i % 2][i / 2 * 13 + j] - 10 < 0){
                printf(" ");
            }
            printf("%d  ", cards[i % 2][i / 2 * 13 + j]);
        }
        printf("\n");
    }
}


//カード表示
void showCards(int x, int y){
    printf("  1  2  3  4  5  6  7  8  9 10 11 12 13\n");
    for(int i = 0; i < 4; i++){
        printf("%d ", i + 1);
        for(int j = 0; j < 13; j++){
            if(cards[i][j] == 100){
                printf("   ");
            }
            else if(j == x -1 && i == y -1){
                printf("□  ");
            }
            else{
                printf("■  ");
            }
        }
        printf("\n");
    }
}