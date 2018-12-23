#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

typedef struct Dict{
    char en[32];
    char ja[32];
} Dict;

Dict words[100];
int dictCnt;

void viewDict(void);
void readDict(char *);
void progressBar(void);
void setQuestions(void);
void ansQuestions(int);


int main(int argc, char *argv[]) {

    srand((unsigned)time(NULL));
    if (argc == 1) {
        printf("Loading build-in en-ja.csv\n");
        readDict("en-ja.csv");
    } else if (argc == 2) {
        printf("Load %s\n", argv[1]);
        readDict(argv[1]);
    }

    setQuestions();

    return (0);
}


void viewDict(void) {
    // 読み込んだ.csvの内容をprintfするサブルーチン 
    int i = 0;
    printf("\n\n##########  単語一覧 %d個  ##########\n", dictCnt);
    while (strlen(words[i].en) != 0) {
        printf("%s %s", words[i].en, words[i].ja);
        Sleep(20);
        i++;
    }
    printf("\n終了\n");
}


void readDict(char *inputFile) {
    // csvの読み込みを行うサブルーチン
    int i = 0;
    FILE *fp;
    char *fname = inputFile;
    fp = fopen(fname, "r");

    if (fp == NULL) {
        printf("%s does not exist.\n", fname);
    } else {
        progressBar();
        printf("File load complete!!\n");
    }
    
    while (1) {
        fscanf(fp, "%[^,],%s", &words[i].en, &words[i].ja);
        if (strlen(words[i].en) == 1)
            break;
        i++;
    }

    dictCnt = i;
    fclose(fp);
}

void progressBar(void) {
    Sleep(500);
    int i = 0;
    for (i = 0; i < 60; i++) {
        printf("*");
        Sleep(10);
    }
    printf("\n");
    Sleep(100);
}

void setQuestions(void) {
    int r = rand() % dictCnt;
    printf("Question %10s \n", words[r].ja);
    
    ansQuestions(r);
}

void ansQuestions(int correctVal) {
    int choice[4], i;
    int indexCorrVal = rand() % 4;
    choice[indexCorrVal] = correctVal;

    for (i=0; i<4; i++) {
        if (i == indexCorrVal) {
            ;;
        } else {
            choice[i] = rand() % dictCnt;
        }

    }
    printf("1:[%s] 2:[%s] 3:[%s] 4:[%s]", words[choice[0]].en, words[choice[1]].en, words[choice[2]].en, words[choice[3]].en);
}