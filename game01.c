#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void showCards(int x, int y);
void judgement(int x1, int y1, int x2, int y2);
void cardsMark(int i);

int cards[52], correctAnswer[52], score = 0;
int main(int argc,char** argv){


    //カード準備
    for(int i = 0; i < 52; i++){
        cards[i] = i;
    }


    //フィッシャー・イェーツシャッフル
    srand((unsigned) time(NULL));
    int ransu, tmp;
    for(int i=0; i<50; i++){
        ransu = rand() % (51-i);
        tmp = cards[ransu];
        cards[ransu] = cards[51-i];
        cards[51-i] = tmp;
    }
    for(int i = 0; i<52; i++){
        correctAnswer[i] = cards[i];
    }



    //説明
    printf("神経衰弱\nこの神経衰弱は黒、赤それぞれ26枚のカードを用います。数字の範囲は1～13です。色、数字共に一致。\n20回選択した時点で終了します。\n");


    int x1, y1, x2, y2, count = 0;

    showCards(-1, -1);
    while(1){


        //一枚目のカード
        printf("回数：%d\n", count);
        printf("最初に選ぶカードの座標を入力してください。\n");
        printf("X = ");
        scanf("%d", &x1);
        printf("Y = ");
        scanf("%d", &y1);
        cardsMark((y1 - 1) * 13 + x1 - 1);
        printf("\n");
        showCards(x1, y1);


        //二枚目のカード
        printf("次に選ぶカードの座標を入力してください。\n");
        printf("X = ");
        scanf("%d", &x2);
        printf("Y = ");
        scanf("%d", &y2);
        if(0 < x1 && x1 < 14 && 0 < y1 && y1 < 5 && 0 < x2 && x2 < 14 && 0 < y2 && y2 < 5){
            judgement(x1, y1, x2, y2);
            cardsMark((y2 - 1) * 13 + x2 - 1);
            printf("\n");
            showCards(-1,-1);
            count++;
        }
        else{
            printf("無効な入力です。\n");
            continue;
        }



        //ヒント
        printf("ヒント：");
        ransu = rand() % 52;
        cardsMark(ransu);
        printf(" → (%d,%d)    ", ransu % 13 + 1, ransu / 13 + 1);
        ransu = rand() % 52;
        cardsMark(ransu);
        printf(" → (%d,%d)", ransu % 13 + 1, ransu / 13 + 1);
        printf("\n");


        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 13; j++){
                cardsMark(i * 13 + j);
                if((correctAnswer[i * 13 + j] + 1) % 13 != 0 && (correctAnswer[i * 13 + j] + 1) % 13 < 10){
                    printf(" ");
                }
                printf("  ");
            }
            printf("\n");
        }

        if(count == 24){
            printf("終了です。スコア：%d", score);
            break;
        }
    }


    //答え表示
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            cardsMark(i * 13 + j);
            if((correctAnswer[i * 13 + j] + 1) % 13 != 0 && (correctAnswer[i * 13 + j] + 1) % 13 < 10){
                printf(" ");
            }
            printf("  ");
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
            if(cards[i * 13 + j] == -1){
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

//正誤判定
void judgement(int x1, int y1, int x2, int y2){
    if(abs(cards[(y1 - 1) * 13 + x1 - 1] - cards[(y2 - 1 ) * 13 + x2 - 1]) == 13){
        if(cards[(y1 - 1) * 13 + x1 - 1] < 26 && cards[(y2 - 1) * 13 + x2 - 1] < 26){
            cards[(y1 - 1) * 13 + x1 - 1] = -1;
            cards[(y2 - 1) * 13 + x2 - 1] = -1;
            printf("正解\n");
            score++;
        }
        else if(cards[(y1 - 1) * 13 + x1 - 1] > 25 && cards[(y2 - 1) * 13 + x2 - 1] > 25){
            cards[(y1 - 1) * 13 + x1 - 1] = -1;
            cards[(y2 - 1) * 13 + x2 - 1] = -1;
            printf("正解\n");
            score++;
        }
    }
    else{
        printf("不正解\n");
    }
}

//カードに対応させる
void cardsMark(int i){
    if(correctAnswer[i] < 13){
        printf("黒%d", correctAnswer[i] + 1);
    }
    else if(correctAnswer[i] > 12 && correctAnswer[i] <26){
        printf("黒%d", correctAnswer[i]- 13 + 1);
    }
    else if(correctAnswer[i] > 25 && correctAnswer[i] < 39){
        printf("赤%d", correctAnswer[i] -26 + 1);
    }
    else{
        printf("赤%d", correctAnswer[i] - 39 + 1);
    }
}