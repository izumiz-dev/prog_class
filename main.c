#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct Dict{
    char en[32];
    char ja[32];
} Dict;

Dict words[100];


void viewDict(void);
void readDict(char *);
void progressBar(void);

int main(int argc, char *argv[]) {

    if (argc == 1) {
        printf("Loading build-in en-ja.csv\n");
        readDict("en-ja.csv");
    } else if (argc == 2) {
        printf("Load %s\n", argv[1]);
        readDict(argv[1]);
    }
    viewDict();
    int i = 0;
    return (0);
}


void viewDict(void) {
    // 読み込んだ.csvの内容をprintfするサブルーチン 
    int i = 0;
    i = 0;
    while (strlen(words[i].en) != 0) {
        printf("%s %s", words[i].en, words[i].ja);
        i++;
    }
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
    fclose(fp);
}

void progressBar(void) {
    Sleep(500);
    int i = 0;
    for (i = 0; i < 60; i++) {
        printf("*");
        Sleep(20);
    }
    printf("\n");
    Sleep(100);
}