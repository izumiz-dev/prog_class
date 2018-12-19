#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024

typedef struct Dict{
    char en[32];
    char ja[32];
} Dict;

Dict words[100];

int main(int argc, char *argv[]) {
    FILE *fp;
    char *fname = "en-ja.csv";
    char temp[32];
    int i = 0;

    fp = fopen(fname, "r");

    if (fp == NULL) {
        printf("%s does not exist.\n", fname);
        return -1;
    } else {
        printf("%s has opened.\n\n\n", fname);
    }

    for (i=0; i < 32; i++) {
        fscanf(fp, "%[^,],%s", &words[i].en, &words[i].ja);
    }


    // do {
    //     fscanf(fp, "%[^,],%s", &words[i].en, &words[i].ja);
    //     i++;
    // } while (strlen(words[i].en) == 0);


    printf("[%s] [%s]\n\n", words[24].en, words[24].ja);


    i = 0;
    while (strlen(words[i].en) != 0) {
        printf("%s %s", words[i].en, words[i].ja);
        i++;
    }
    
    fclose(fp);
    return (0);
}