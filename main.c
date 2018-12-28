#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

typedef struct Dict
{
    char en[32];
    char ja[32];
} Dict;

Dict words[100];    // 単語の英語、日本語の構造体の変数
int dictCnt;        // 登録単語数

void viewDict(void);
void readDict(char *);
void progressBar(void);
void setQuestions(void);

int main(int argc, char *argv[])
{
    int i;

    srand((unsigned)time(NULL));
    if (argc == 1)
    {
        printf("Loading build-in en-ja.csv\n");
        readDict("en-ja.csv");
    }
    else if (argc == 2)
    {
        printf("Load %s\n", argv[1]);
        readDict(argv[1]);
    }

    for (i = 0; i < 10; i++)
    {
        setQuestions();
    }

    // viewDict();
    return (0);
}

void viewDict(void)
{
    int i = 0;
    while (strlen(words[i].en) != 0)
    {
        printf("%s %s", words[i].en, words[i].ja);
        Sleep(20);
        i++;
    }
}

void readDict(char *inputFile)
{
    int i = 0;
    FILE *fp;
    char *fname = inputFile;
    fp = fopen(fname, "r");

    if (fp == NULL)
    {
        printf("%s does not exist.\n", fname);
    }
    else
    {
        progressBar();
        printf("File load complete!!\n");
    }

    while (1)
    {
        fscanf(fp, "%[^,],%s", &words[i].en, &words[i].ja);
        if (strlen(words[i].en) == 1)
            break;
        i++;
    }

    dictCnt = i;
    fclose(fp);
}

void progressBar(void)
{
    Sleep(500);
    int i = 0;
    for (i = 0; i < 60; i++)
    {
        printf("*");
        Sleep(10);
    }
    printf("\n");
    Sleep(100);
}

void setQuestions(void)
{
    char buff[255];
    char ansStr[255];
    int i, quesNum;
    int isCorrect; // 0:Correct, else: Incorrect

    do
    {
        quesNum = rand() % dictCnt;
    } while (quesNum == 0); // 0はcsvの書式のため出題できないようにする

    strcpy(ansStr, words[quesNum].en);
    for (i = 0; i < strlen(ansStr); i++)
    {
        ansStr[i] = ansStr[i + 1];
    }

    // printf("[ansStr string check:%s]\n", ansStr);

    printf("英語で[ %s ]\n", words[quesNum].ja);
    printf("> ");
    fgets(buff, sizeof(buff), stdin);
    for (i = 0; i < strlen(buff); i++)
    {
        if (buff[i] == '\n')
        {
            buff[i] = '\0';
        }
    }
    isCorrect = strcmp(buff, ansStr);

    if (isCorrect == 0)
    {
        printf("正解!!\n\n");
    }
    else
    {
        printf("不正解 ");
        printf("答えは[ %s ]\n\n", ansStr);
    }
}