#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KAISU 20    //何回選択するか

void showCards(int idx);
void judgement(int idx1, int idx2);
void cardsMark(int i);
int inputCard(const char* message, int firstIdx);

int cards[52];          //場のカード状況を記録
int correctAnswer[52];  //正解を記録
int score = 0;


int main(void){


    //カード準備
    for(int i = 0; i < 52; i++){
        cards[i] = i;
    }


    //フィッシャー・イェーツシャッフル
    srand((unsigned) time(NULL));
    int ransu, tmp;
    for(int i = 0; i < 51; i++){
        ransu = rand() % (52-i);
        tmp = cards[ransu];
        cards[ransu] = cards[51-i];
        cards[51-i] = tmp;
    }
    for(int i = 0; i<52; i++){
        correctAnswer[i] = cards[i];
    }


    //説明
    printf("神経衰弱\nこの神経衰弱は黒、赤それぞれ26枚のカードを用います。数字の範囲は1～13です。色、数字共に一致。\n%d回選択した時点で終了します。\n", KAISU);


    showCards(-1);
    int count = 0;
    while(count < KAISU){


        //一枚目のカード
        printf("残り回数：%d\n", KAISU - count);
        int idx1 = inputCard("--- 1枚目のカードを選んでください ---", -1);
        cardsMark(idx1);
        printf("\n\n");
        showCards(idx1);


        //二枚目のカード
        int idx2 = inputCard("--- 2枚目のカードを選んでください ---", idx1);
        judgement(idx1, idx2);
        cardsMark(idx2);
        printf("\n\n-------------------------------------------------\n\n");
        showCards(-1);
        count++;
        

        //ヒント
        int ransu1, ransu2;
        do {
            ransu1 = rand() % 52;
        } while (cards[ransu1] == -1);
        do {
            ransu2 = rand() % 52;
        } while (cards[ransu2] == -1 || ransu1 == ransu2);

        printf("ヒント：");
        cardsMark(ransu1);
        printf(" → (%d,%d)    ", ransu1 % 13 + 1, ransu1 / 13 + 1);
        cardsMark(ransu2);
        printf(" → (%d,%d)", ransu2 % 13 + 1, ransu2 / 13 + 1);
        printf("\n");
    }


    //答え表示
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            int val = correctAnswer[i * 13 + j];
            cardsMark(i * 13 + j);

            // カードの数字が 1〜9 の時だけスペースを追加
            if((val % 13) + 1 < 10){
                printf(" ");
            }
            printf("  ");
        }
        printf("\n");
    }

    printf("終了です。スコア：%d\n", score);
    return 0;
}


//カード表示
void showCards(int idx){
    
    int x = idx % 13 + 1, y = idx / 13 + 1;
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


//数値を入力
int inputCard(const char* message, int firstIdx) {
    int x, y, idx;

    while (1) {
        printf("\n%s\n", message);
        printf("座標を X Y の順に入力してください（X Y）: ");
        if (scanf("%d %d", &x, &y) != 2) {
            printf("【エラー】数値で入力してください。\n");
            while (getchar() != '\n');
            continue;
        }

        idx = (y - 1) * 13 + (x - 1);
        if (x < 1 || x > 13 || y < 1 || y > 4) {
            printf("【エラー】範囲外です（X:1-13, Y:1-4）。\n");
        } 
        else if (cards[idx] == -1) {
            printf("【エラー】そのカードは既に取られています。\n");
        } 
        else if (idx == firstIdx) {
            printf("【エラー】1枚目と同じカードは選べません。\n");
        } 
        else {
            return idx;
        }
    }
}


//正誤判定
void judgement(int idx1, int idx2){
    if((cards[idx1] / 26 == cards[idx2] / 26) && (cards[idx1] % 13 == cards[idx2] % 13)){
        cards[idx1] = cards[idx2] = -1;
        printf("正解\n");
        score++;
    }
    else{
        printf("不正解\n");
    }
}


//カードに対応させる
void cardsMark(int i){ 
    if(correctAnswer[i] < 26){
        printf("黒%d", (correctAnswer[i] % 13) + 1);
    } else {
        printf("赤%d", (correctAnswer[i] % 13) + 1);
    }
}