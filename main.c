#include <stdio.h>

FILE *filePointer;

int main(int argc, char *argv[]) {

    char *fileName = "en-ja.csv";
    char enDict[100][100];
    char jaDict[100][100];  //.csvから読み込んだ単語の配列
    int i;

    filePointer = fopen(fileName, "r");
    if (filePointer == NULL) {
        printf("%s does not exist.\n", fileName);
        return 8;
    }

    // while　(( ret = fscanf(filePointer, "%[^,],%s", &dict[1] ) ) != EOF )　{
    //     printf( "%s %d %d %f %f", s, n1, n2, f1, f2 );
    // }

    for (i = 0; i < 100; i++) {
        if (fscanf(filePointer, "%[^,],%s", &enDict[i], &jaDict[i]) != EOF) {
            break;
        } else {
            fscanf(filePointer, "%[^,],%s", &enDict[i], &jaDict[i]);
        }
    }

    for (i = 0; i < 100; i++) {
        // if (fscanf(filePointer, "%s,%s", &dict[i][0], &dict[i][1]) != EOF) {
        //     break;
        // } else {
        //     printf("%s %s\n", &dict[i][0], &dict[i][1]);
        // }
        printf("%s %s\n", enDict[i], jaDict[i]);
    }

    fclose(filePointer);

    return (0);
}