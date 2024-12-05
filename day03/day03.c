#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 10240

int execute(char *line) {
    const char *pos = line;
    int sum = 0;

    while ((pos = strstr(pos, "mul(")) != NULL) {
        int x, y;
        char c;
        
        // printf("Start found at pos: %d\n", pos - line);
        if (sscanf(pos+4, "%d,%d%c", &x, &y, &c) == 3) {
            if (c==')') {
                // printf("X: %d, Y: %d\n", x, y);
                sum += x*y;
            }
        }
        pos++;
    }

    return sum;
}

int part1(char* filename)
{
    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int sum = 0;

    while (fgets(line, sizeof(line), fp)) {
        sum += execute(line);
    }

    fclose(fp);

    return sum;
}

int part2(char* filename)
{
    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    fclose(fp);

    return 0;
}

int main(int argc, char** argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <1|2> <inputfile>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "1") == 0) {
        printf("\nSum: %d\n", part1(argv[2]));
    } else if (strcmp(argv[1], "2") == 0) {
        printf("\nSum: %d\n", part2(argv[2]));
    } else {
        fprintf(stderr, "Usage: %s <1|2> <inputfile>\n", argv[0]);
        return 1;
    }

    return 0;
}