#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

typedef enum {
    INCREASING,
    DECREASING
} SortType;

int is_safe(int* report, int level_c)
{
    SortType type;
    int diff;

    // check first two and determine if increasing or decreasing
    diff = report[0]-report[1];
    if ( diff > 3 || diff < -3 || diff == 0 ) {
        return 0;
    }
    
    if (diff > 0) {
        type = DECREASING;
    } else if (diff < 0)
    {
        type = INCREASING;
    }

    // check the rest
    for (int i=1; i<level_c-1; i++) {
        diff = report[i]-report[i+1];
        if ( (diff == 0) || (diff > 3) || (diff < -3) || (diff > 0 && type == INCREASING) || (diff < 0 && type == DECREASING) )
            return 0;
    }

    // for (int i = 0; i < level_c; i++) {
    //     printf("%d ", report[i]);
    // }
    // printf(" is safe!\n");

    return 1;
}

int part1(char* filename)
{
    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int report[MAX_LINE_LENGTH];
    int level_c;
    int safe_c = 0;

    while (fgets(line, sizeof(line), fp)) {
        level_c = 0;
        char *token = strtok(line, " "); // the first token
        while (token != NULL) {
            report[level_c] = atoi(token);
            level_c++;
            token = strtok(NULL, " "); // get the next token
        }
        
        if (is_safe(report, level_c))
            safe_c++;
    }

    fclose(fp);

    return safe_c;
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