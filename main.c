#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024

typedef struct Dict{
    char en[32];
    char ja[32];
} Dict;

Dict words[256];

int main(int argc, char *argv[]) {
    FILE *fp;
    char *fname = "en-ja.csv";
    int i, ret;

    fp = fopen(fname, "r");

    if (fp == NULL) {
        printf("%s does not exist.\n", fname);
        return -1;
    } else {
        printf("%s file has opened\n", fname);
    }

    fscanf(fp, "%[^,],%s", &words[0].en, &words[0].ja);
    fclose(fp);
    printf("%s %s\n",  words[0].en, words[0].ja);

    return (0);
}