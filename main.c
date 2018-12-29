/****************************************************
 * main.c
 * 
 * 変数名 snake_case
 * 関数名は camelCase
 * インデント space 4文字
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define MAX_VALUE 1024

FILE *file_pointer;
typedef struct Dict {
    char en[MAX_VALUE];
    char ja[MAX_VALUE];
} Dict;

Dict words[MAX_VALUE];      // 単語の英語、日本語の構造体の変数

int row_count;              // 登録単語数
int histories[MAX_VALUE];   // 出題履歴を格納する
int results[MAX_VALUE]; 

void displayWords(void);
void readDict(char *);
void progressBar(void);
int setQuestions(int);
void showResult(void);
void informTips(void);
int main(int argc, char *argv[])
{
    int i = 0;
    char buff[MAX_VALUE];
    int choice;
    srand((unsigned int)time(NULL));
    if (argc == 1) {
        printf("Loading build-in en-ja.csv\n");
        readDict("en-ja.csv");
    } else if (argc == 2) {
        printf("Load %s\n", argv[1]);
        readDict(argv[1]);
    }

quiz:
    for (i = 0; i < 10; i++) {
        histories[i] = setQuestions(i);
    }

    showResult();
menu:
    printf("ゲームをやめる: 1\t");
    printf("ゲームを続ける: 2\t");
    printf("問題一覧を表示する: 3\n");
    printf(" > ");
    fgets(buff, sizeof(buff), stdin);
    choice = atoi(buff);
    switch (choice) {
        case 1:
            informTips();
            printf("See you!\n");
            return (0);
        case 2:
            goto quiz;
            break;
        case 3:
            displayWords();
            goto menu;
            break;
        default:
            goto menu;
            break;
    }
    return (0);
}




/****************************************************
 * void displayWords(void)
 * 内容
 *      wordsの内容 一覧を表示する
 ****************************************************/
void displayWords(void)
{
    int i = 0;

    if (file_pointer == NULL) {
        printf("まだ.csvが読み込まれていません\n");
    }

    while (strlen(words[i].en) != 0) {
        printf("%s %s", words[i].en, words[i].ja);
        Sleep(20);
        i++;
    }
}


/****************************************************
 *  void readDict(char *input_file)
 * 引数     char* 
 *      入力ファイルのポインタをとる                      
 * 戻り値   void
 * 内容
 *      .csvファイルを読み込む。次に.csvの内容を構造体の
 * 配列wordsに格納する。最後に、row_countにレコードの数を
 * 登録する。
 ****************************************************/
void readDict(char *input_file)
{
    int i = 0;
    char *file_name = input_file;
    file_pointer = fopen(file_name, "r");

    if (file_pointer == NULL) {
        printf("%s does not exist.\n", file_name);
    } else {
        progressBar();
        printf("File load complete!!\n");
    }

    while (1) {
        fscanf(file_pointer, "%[^,],%s", &words[i].en, &words[i].ja);
        if (strlen(words[i].en) == 1)
            break;
        i++;
    }

    row_count = i;
    fclose(file_pointer);
}




/****************************************************
 *          void progressBar(void)
 * - 引数   void
 * - 戻り値 void
 * 内容
 *      なんちゃってプログレスバーを表示する
 ****************************************************/
void progressBar(void)
{
    Sleep(500);
    int i = 0;
    for (i = 0; i < 60; i++) {
        printf("*");
        Sleep(10);
    }
    printf("\n");
    Sleep(100);
}




/****************************************************
 *          int setQuestions(void)
 * - 引数     なし                                        
 * - 戻り値   int
 *      出題したquestion_numberの値を返す。 
 * 内容
 *      出題する関数。初めにrand()を用いて、出題する問題
 * の番号をquestion_numberに代入する。次に、一時的な変数answer_string
 ****************************************************/
int setQuestions(int number)
{
    char buff[MAX_VALUE];
    char answer_string[MAX_VALUE];
    int i, question_number;
    int is_correct;                 // 0:Correct, else: Incorrect

    do {
        question_number = rand() % row_count;
    } while (question_number == 0); // 0はcsvの書式のため出題できないようにする

    strcpy(answer_string, words[question_number].en);
    for (i = 0; i < strlen(answer_string); i++) {
        answer_string[i] = answer_string[i + 1];
    }

    printf("%d/10問目:   英語で[ %s ]は？\n", number, words[question_number].ja);
    printf(" > ");
    fgets(buff, sizeof(buff), stdin);
    for (i = 0; i < strlen(buff); i++) {
        if (buff[i] == '\n') {
            buff[i] = '\0';
        }
    }

    is_correct = strcmp(buff, answer_string);   // 正解判定
    results[number] = is_correct;               // resultsに正解かどうかを格納

    if (is_correct == 0) {
        printf("正解!!\n\n");
    } else {
        printf("不正解 ");
        printf("答えは[ %s ]\n\n", answer_string);
    }
    return (question_number);
}


void showResult(void) {
    int i;
    int j = 0; //incorrectsのindex
    int correct_answer_count = 0;
    char buff[MAX_VALUE];

    for (i = 0; i < 10; i++) {
        if (results[i] == 0) {
            correct_answer_count++;
        } else {
            results[i] = -1;    // 不正解を-1とする
        }
    }

    printf("スコア　%d / 10 点！\n\n", correct_answer_count);

    // 間違えた問題の一覧を表示する
    printf("間違えた問題");
    for (i = 0; i < 10; i++) {
        if (results[i] == -1) {
            int temp = histories[i];
            printf("%-20s %s", words[temp].en, words[temp].ja);
        }
    }

    printf("\n\n");
}

void informTips(void) {
    int num = rand() % 2;
    switch (num) {
        case 0:
            printf("Tips: ");
            printf("起動時に自分で用意した.csvファイルを読み込ますことができるよ！[main.exe .csv]\n");
            break;
        default:
            break;
    }
}