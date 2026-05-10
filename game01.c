#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define KAISU 20    //何回選択するか

typedef struct {
    int suit; // 0,1: 黒, 2,3: 赤 
    int number; // 1-13
    bool isGotten; // カードが取られたかどうか
    bool isSelected; // カードが選択されているかどうか
} Card;

void showCards(void);
void judgement(Card* idx1, Card* idx2);
void cardsMark(Card card);
Card* inputCard(const char* message);

Card correctAnswer[13][4];  //正解を記録
int score = 0;


int main(void){


    //カード準備
    for(int i = 0; i < 13; i++){
        for(int j = 0; j < 4; j++){
            correctAnswer[i][j].suit = j;
            correctAnswer[i][j].number = i + 1;
            correctAnswer[i][j].isGotten = false;
            correctAnswer[i][j].isSelected = false;
        }
    }


    //フィッシャー・イェーツシャッフル
    srand((unsigned) time(NULL));
    for (int i = 0; i < 51; i++) {
        int i_x = (51 - i) % 13;
        int i_y = (51 - i) / 13;

        int ransu = rand() % (52 - i);
        int ransu_x = ransu % 13;
        int ransu_y = ransu / 13;

        Card tmp = correctAnswer[ransu_x][ransu_y];
        correctAnswer[ransu_x][ransu_y] = correctAnswer[i_x][i_y];
        correctAnswer[i_x][i_y] = tmp;
    }


    //説明
    printf("神経衰弱\nこの神経衰弱は黒、赤それぞれ26枚のカードを用います。数字の範囲は1～13です。色、数字共に一致。\n%d回選択した時点で終了します。\n", KAISU);


    showCards();
    int count = 0;
    while(count < KAISU){


        //一枚目のカード
        printf("残り回数：%d\n", KAISU - count);
        Card *idx1 = inputCard("--- 1枚目のカードを選んでください ---");
        cardsMark(*idx1);
        // 選択したカードであることを示す
        idx1->isSelected = true;
        printf("\n\n");
        showCards();


        //二枚目のカード
        Card *idx2 = inputCard("--- 2枚目のカードを選んでください ---");
        judgement(idx1, idx2);
        cardsMark(*idx2);
        // 選択したカードであることを示す
        idx2->isSelected = true;
        printf("\n\n-------------------------------------------------\n\n");
        showCards();

        // 選択状態をリセット
        idx1->isSelected = false;
        idx2->isSelected = false;

        count++;
        
        
        Card hintCard[2];
        for(int i = 0; i < 2; i++){
            int hintCount = 0;
            int hintRansu = rand() % 52;
            while(true)
            {
                if(!correctAnswer[hintRansu % 13][hintRansu / 13].isGotten){
                    hintCard[i] = correctAnswer[hintRansu % 13][hintRansu / 13];
                    break;
                }
                // ヒントが既に取られているカードであれば、次のカードをヒントにする
                hintRansu = (hintRansu + 1) % 52;
                hintCount++;

                if(hintCount > 52){
                    hintCard[i].suit = -1; // ヒントがないことを示す
                    break;
                }

            }
        }

        printf("ヒント：");
        if(hintCard[0].suit != -1){
            cardsMark(hintCard[0]);
            printf(" → (%d,%d)    ", hintCard[0].number, hintCard[0].suit + 1);
        }

        if(hintCard[1].suit != -1){
            cardsMark(hintCard[1]);
            printf(" → (%d,%d)", hintCard[1].number, hintCard[1].suit + 1);
        }
        printf("\n");
    }


    //答え表示
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            cardsMark(correctAnswer[j][i]);

            // カードの数字が 1〜9 の時だけスペースを追加
            if(correctAnswer[j][i].number < 10){
                printf(" ");
            }
            printf("  ");
        }
        printf("\n");
    }

    printf("終了です。スコア：%d\n", score);
    return 0;
}


//カード表示 xとyは選択したカードの座標
void showCards(){
 
    printf("  1  2  3  4  5  6  7  8  9 10 11 12 13\n");
    for(int i = 0; i < 4; i++){
        printf("%d ", i + 1);
        for(int j = 0; j < 13; j++){
            // カードが取られた場合はスペース、選択されている場合は□、それ以外は■を表示
            if(correctAnswer[j][i].isGotten){
                printf("   ");
            }
            else if(correctAnswer[j][i].isSelected){
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
Card* inputCard(const char* message) {
    int x, y, idx;

    while (1) {
        printf("\n%s\n", message);
        printf("座標を X Y の順に入力してください（X Y）: ");
        if (scanf("%d %d", &x, &y) != 2) {
            printf("【エラー】数値で入力してください。\n");
            while (getchar() != '\n');
            continue;
        }

        if (x < 1 || x > 13 || y < 1 || y > 4) {
            printf("【エラー】範囲外です（X:1-13, Y:1-4）。\n");
        } 
        else if (correctAnswer[x - 1][y - 1].isGotten) {
            printf("【エラー】そのカードは既に取られています。\n");
        } 
        else if (correctAnswer[x - 1][y - 1].isSelected) {
            printf("【エラー】1枚目と同じカードは選べません。\n");
        } 
        else {
            return &correctAnswer[x - 1][y - 1];
        }
    }
}


//正誤判定
void judgement(Card* idx1, Card* idx2){
    // 色と数字が両方とも一致しているかどうかを判定
    // suitは0,1が黒、2,3が赤なので、suitを2で割った商が同じであれば色が一致していると判断できる
    if((idx1->suit / 2 == idx2->suit / 2) && (idx1->number == idx2->number)){
        printf("正解\n");
        idx1->isGotten = true;
        idx2->isGotten = true;
        score++;
    }
    else{
        printf("不正解\n");
    }
}


//カードに対応させる
void cardsMark(Card card){ 
    if(card.suit < 2){
        printf("黒%d", card.number);
    } else {
        printf("赤%d", card.number);
    }
}