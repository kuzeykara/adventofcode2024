#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 10240

int execute(char *line) {
    const char *pos = line;
    int sum = 0;
    int x, y;
    char c;

    while ((pos = strstr(pos, "mul(")) != NULL) {
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

int glob_dont = 0;

int adv_execute(char *line)
{
    const char *pos = line;
    int sum = 0;
    int x, y;
    char c;
    
    while (pos) {
        const char *pos1 = strstr(pos, "don't()");
        const char *pos2 = strstr(pos, "mul(");

        if (glob_dont) {
            pos = strstr(pos+1, "do()"); // search for the next do()
            if (pos == NULL) {
                break;
            } else {
                glob_dont = 0;
            }

            continue;
        }

        if (!pos1 && !pos2) // no match
            break;

        if (pos1 && (!pos2 || (pos1 < pos2))) {                     // don't() found before mul()
            glob_dont = 1;
            pos = strstr(pos1+1, "do()"); // search for the next do()
            if (pos == NULL) {
                break;
            } else {
                glob_dont = 0;
            }
        } else {                                                    // mul() found before don't()
            if (sscanf(pos2+4, "%d,%d%c", &x, &y, &c) == 3) {
                if (c==')') {
                    // printf("X: %d, Y: %d\n", x, y);
                    sum += x*y;
                }
                pos = pos2 + 4;
            } else {
                pos = pos2+1;
            }
        }
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

    char line[MAX_LINE_LENGTH];
    int sum = 0;

    while (fgets(line, sizeof(line), fp)) {
        sum += adv_execute(line);
    }

    fclose(fp);

    return sum;
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