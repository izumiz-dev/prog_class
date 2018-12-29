/****************************************************
 * main.c
 * 
 * �ϐ��� snake_case
 * �֐����� camelCase
 * �C���f���g space 4����
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

Dict words[MAX_VALUE];      // �P��̉p��A���{��̍\���̂̕ϐ�

int row_count;              // �o�^�P�ꐔ
int histories[MAX_VALUE];   // �o�藚�����i�[����
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
    printf("�Q�[������߂�: 1\t");
    printf("�Q�[���𑱂���: 2\t");
    printf("���ꗗ��\������: 3\n");
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
 * ���e
 *      words�̓��e �ꗗ��\������
 ****************************************************/
void displayWords(void)
{
    int i = 0;

    if (file_pointer == NULL) {
        printf("�܂�.csv���ǂݍ��܂�Ă��܂���\n");
    }

    while (strlen(words[i].en) != 0) {
        printf("%s %s", words[i].en, words[i].ja);
        Sleep(20);
        i++;
    }
}


/****************************************************
 *  void readDict(char *input_file)
 * ����     char* 
 *      ���̓t�@�C���̃|�C���^���Ƃ�                      
 * �߂�l   void
 * ���e
 *      .csv�t�@�C����ǂݍ��ށB����.csv�̓��e���\���̂�
 * �z��words�Ɋi�[����B�Ō�ɁArow_count�Ƀ��R�[�h�̐���
 * �o�^����B
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
 * - ����   void
 * - �߂�l void
 * ���e
 *      �Ȃ񂿂���ăv���O���X�o�[��\������
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
 * - ����     �Ȃ�                                        
 * - �߂�l   int
 *      �o�肵��question_number�̒l��Ԃ��B 
 * ���e
 *      �o�肷��֐��B���߂�rand()��p���āA�o�肷����
 * �̔ԍ���question_number�ɑ������B���ɁA�ꎞ�I�ȕϐ�answer_string
 ****************************************************/
int setQuestions(int number)
{
    char buff[MAX_VALUE];
    char answer_string[MAX_VALUE];
    int i, question_number;
    int is_correct;                 // 0:Correct, else: Incorrect

    do {
        question_number = rand() % row_count;
    } while (question_number == 0); // 0��csv�̏����̂��ߏo��ł��Ȃ��悤�ɂ���

    strcpy(answer_string, words[question_number].en);
    for (i = 0; i < strlen(answer_string); i++) {
        answer_string[i] = answer_string[i + 1];
    }

    printf("%d/10���:   �p���[ %s ]�́H\n", number, words[question_number].ja);
    printf(" > ");
    fgets(buff, sizeof(buff), stdin);
    for (i = 0; i < strlen(buff); i++) {
        if (buff[i] == '\n') {
            buff[i] = '\0';
        }
    }

    is_correct = strcmp(buff, answer_string);   // ���𔻒�
    results[number] = is_correct;               // results�ɐ������ǂ������i�[

    if (is_correct == 0) {
        printf("����!!\n\n");
    } else {
        printf("�s���� ");
        printf("������[ %s ]\n\n", answer_string);
    }
    return (question_number);
}


void showResult(void) {
    int i;
    int j = 0; //incorrects��index
    int correct_answer_count = 0;
    char buff[MAX_VALUE];

    for (i = 0; i < 10; i++) {
        if (results[i] == 0) {
            correct_answer_count++;
        } else {
            results[i] = -1;    // �s������-1�Ƃ���
        }
    }

    printf("�X�R�A�@%d / 10 �_�I\n\n", correct_answer_count);

    // �ԈႦ�����̈ꗗ��\������
    printf("�ԈႦ�����");
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
            printf("�N�����Ɏ����ŗp�ӂ���.csv�t�@�C����ǂݍ��܂����Ƃ��ł����I[main.exe .csv]\n");
            break;
        default:
            break;
    }
}