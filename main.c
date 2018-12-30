/**********************************************************************
 * �p�P��N�C�Y�Q�[��
 * https://github.com/polyiz/prog_class
 * ���[�U�̗p�ӂ���.csv��f�t�H���g�œǂݍ��܂��.csv���g�����p�P��̃N�C�Y
 * ���ł���\�t�g�E�F�A�BWindows�̃R�}���h�v�����v�g��œ����B
 * 
 * �ϐ��� snake_case
 * �֐����� camelCase
 * �C���f���g space 4����
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define MAX_VALUE 1024

FILE *file_pointer;
typedef struct Dict
{
    char en[MAX_VALUE];
    char ja[MAX_VALUE];
} Dict;

Dict words[MAX_VALUE]; // �P��̉p��A���{��̍\���̂̕ϐ�

int row_number;    // �o�^�P�ꐔ
int histories[10]; // �o�藚�����i�[����
int results[10];   // �������ǂ����̔�����i�[����

WORD Attributes = 0;

void displayWords(void);                             // csv����ǂݍ��񂾃f�[�^�ꗗ��\��
void loadDict(char *);                               // csv��Ǎ��݁A�\���̔z��ɑ�����s��
int setQuestions(int);                               // �N�C�Y�̏o��,�����̔�����s��
void showResult(void);                               // �N�C�Y�̌���,�s�����̈ꗗ��\������
void setConsoleColor(WORD *Attributes, DWORD Color); // �����ɐF��t���邽�߂̊֐�
void resetConsoleColor(WORD Attributes);             // �����̐F�����Z�b�g����֐�

int main(int argc, char *argv[])
{
    int i = 0;
    char buff[MAX_VALUE];
    int choice;
    srand((unsigned int)time(NULL));
    if (argc == 1)
    {
        printf("Loading build-in en-ja.csv\n");
        loadDict("en-ja.csv");
    }
    else if (argc == 2)
    {
        printf("Load %s\n", argv[1]);
        loadDict(argv[1]);
    }
    printf("�N�����Ɏ����ŗp�ӂ���.csv�t�@�C����ǂݍ��܂��邱�Ƃ��ł��܂��B[main.exe example.csv]\n");

quiz:
    for (i = 0; i < 10; i++)
    {
        histories[i] = setQuestions(i);
    }

    showResult();
menu:
    setConsoleColor(&Attributes, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    printf("�Q�[������߂�: 1\t");
    printf("�Q�[���𑱂���: 2\t");
    printf("���ꗗ��\������: 3  \n");
    resetConsoleColor(Attributes);
    printf(" > ");
    fgets(buff, sizeof(buff), stdin);
    choice = atoi(buff);
    switch (choice)
    {
    case 1:
        resetConsoleColor(Attributes);
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

/**********************************************************************
 * void displayWords(void)
 * ���e
 *      words�̓��e �ꗗ��\������
 **********************************************************************/
void displayWords(void)
{
    int i = 1; // 0�͒P��ł͂Ȃ�����1����X�^�[�g����
    if (file_pointer == NULL)
    {
        printf("�܂�.csv���ǂݍ��܂�Ă��܂���\n");
    }

    while (strlen(words[i].en) != 0)
    {
        printf("%-20s %s", words[i].en, words[i].ja);
        Sleep(20);
        i++;
    }
    printf("\n");
}

/**********************************************************************
 *  void loadDict(char *input_file)
 * ����
 *      ���̓t�@�C���̃|�C���^
 * ���e
 *      .csv�t�@�C����ǂݍ��ށB����.csv�̓��e���\���̂�
 * �z��words�Ɋi�[����B�Ō�ɁArow_number�Ƀ��R�[�h�̐���
 * �o�^����B
 **********************************************************************/
void loadDict(char *input_file)
{
    int i = 0;
    char *file_name = input_file;
    file_pointer = fopen(file_name, "r");

    if (file_pointer == NULL)
    {
        printf("%s does not exist.\n", file_name);
    }
    else
    {
        printf("File load complete!!\n");
    }

    while (1)
    {
        fscanf(file_pointer, "%[^,],%s", &words[i].en, &words[i].ja);
        if (strlen(words[i].en) == 1)
        {
            break;
        }
        i++;
    }

    row_number = i;
    fclose(file_pointer);
}

/**********************************************************************
 *          int setQuestions(void)
 * �߂�l 
 *      �o�肵��question_number�̒l��Ԃ��B 
 * ���e
 *      �o�肷��֐��B���߂�rand()��p���āA�o�肷����
 * �̔ԍ���question_number�ɑ������B���ɁA�ꎞ�I�ȕϐ�answer_string����
 * ��A����Ɠ��͂�strcmp�֐���p���āA�����̔�����s���B
 **********************************************************************/
int setQuestions(int number)
{
    char buff[MAX_VALUE];
    char answer_string[MAX_VALUE];
    int i, question_number;
    int is_correct; // 0:Correct, else: Incorrect

    question_number = rand() % row_number;

    for (i = 0; i < 10; i++)
    {
        if ((question_number == histories[i]) || (question_number == 0))
        {
            question_number = rand() % row_number;
        }
    }

    strcpy(answer_string, words[question_number].en);
    for (i = 0; i < strlen(answer_string); i++)
    {
        answer_string[i] = answer_string[i + 1];
    }

    setConsoleColor(&Attributes, BACKGROUND_INTENSITY | BACKGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("%d/10���", number + 1);
    resetConsoleColor(Attributes);
    printf("    �p���[ ");
    setConsoleColor(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    printf("%s", words[question_number].ja);
    resetConsoleColor(Attributes);
    printf(" ]�́H\n");
    printf(" > ");
    fgets(buff, sizeof(buff), stdin);
    for (i = 0; i < strlen(buff); i++)
    {
        if (buff[i] == '\n')
        {
            buff[i] = '\0';
        }
    }

    is_correct = strcmp(buff, answer_string); // ���𔻒�
    results[number] = is_correct;             // results�ɐ������ǂ������i�[

    if (is_correct == 0)
    {
        printf("\t\t");
        setConsoleColor(&Attributes, BACKGROUND_INTENSITY | BACKGROUND_GREEN);
        printf("����!!\n\n");
        resetConsoleColor(Attributes);
    }
    else
    {
        printf("\t\t");
        setConsoleColor(&Attributes, BACKGROUND_INTENSITY | BACKGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("�s����");
        resetConsoleColor(Attributes);
        printf("\n  ������[");
        setConsoleColor(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
        printf(" %s ", answer_string);
        resetConsoleColor(Attributes);
        printf("]\n\n");
    }
    return (question_number);
}

/**********************************************************************
 * void showResult(void)
 * ���e
 *      �N�C�Y�̌��ʂ�\������B�ԈႦ������\������B
 **********************************************************************/
void showResult(void)
{
    int i;
    int j = 0; //incorrects��index
    int correct_answer_count = 0;
    char buff[MAX_VALUE];

    for (i = 0; i < 10; i++)
    {
        if (results[i] == 0)
        {
            correct_answer_count++;
        }
        else
        {
            results[i] = -1; // �s������-1�Ƃ���
        }
    }

    if (correct_answer_count <= 5)
    {
        setConsoleColor(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED);
    }
    else
    {
        setConsoleColor(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    }
    printf("�X�R�A  %d / 10 �_�I\n\n", correct_answer_count);
    resetConsoleColor(Attributes);

    // �ԈႦ�����̈ꗗ��\������
    if (correct_answer_count == 10)
    {
        setConsoleColor(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("�S�␳���I\n");
        resetConsoleColor(Attributes);
    }
    else
    {
        setConsoleColor(&Attributes, BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_RED);
        printf("�ԈႦ�����");
        resetConsoleColor(Attributes);
        for (i = 0; i < 10; i++)
        {
            if (results[i] == -1)
            {
                int temp = histories[i];
                printf("%-20s %s", words[temp].en, words[temp].ja);
            }
        }
    }   

    printf("\n\n");
}

/**********************************************************************
 * void setConsoleColor(WORD* Attributes, DWORD Color);
 * void resetConsoleColor(WORD Attributes);
 * �����̊֐���,
 * how to get background color back to previous color after use of std handle
 * ��Answer
 * https://stackoverflow.com/a/25560218
 * �̈��p�ł��B(Colour��Color�ɂ��Ă��܂�)
 **********************************************************************/
void setConsoleColor(WORD *Attributes, DWORD Color)
{
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &Info);
    *Attributes = Info.wAttributes;
    SetConsoleTextAttribute(hStdout, Color);
}

void resetConsoleColor(WORD Attributes)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
}