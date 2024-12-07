#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void print_word_search(char ws[][MAX_LINE_LENGTH], int lineC)
{
    for (int i=0; i<lineC; i++) {
        for (int j=0; j<lineC; j++) {
            printf("%c", ws[i][j]);
        }
        printf("\n");
    }
}

int find_word(char ws[][MAX_LINE_LENGTH], int lineC, char pattern[], int patternC)
{
    int found_flag;
    int word_count = 0;
    
    for (int y=0; y<lineC; y++) {
        for (int x=0; x<lineC; x++) {
            //up
            found_flag = 0;
            for (int i=0; i<patternC; i++) {
                if (y-i >= 0) {
                    if (pattern[i] == ws[y-i][x]) {
                        found_flag++;
                    }
                }
            }
            if (found_flag == patternC)
                word_count++;

            //down
            found_flag = 0;
            for (int i=0; i<patternC; i++) {
                if (y+i < lineC) {
                    if (pattern[i] == ws[y+i][x]) {
                        found_flag++;
                    }
                }
            }
            if (found_flag == patternC)
                word_count++;

            //left
            found_flag = 0;
            for (int i=0; i<patternC; i++) {
                if (x-i >= 0) {
                    if (pattern[i] == ws[y][x-i]) {
                        found_flag++;
                    }
                }
            }
            if (found_flag == patternC)
                word_count++;

            //right
            found_flag = 0;
            for (int i=0; i<patternC; i++) {
                if (x+i < lineC) {
                    if (pattern[i] == ws[y][x+i]) {
                        found_flag++;
                    }
                }
            }
            if (found_flag == patternC)
                word_count++;
            
            //top left
            found_flag = 0;
            for (int i=0; i<patternC; i++) {
                if (y-i >= 0 && x-i >= 0) {
                    if (pattern[i] == ws[y-i][x-i]) {
                        found_flag++;
                    }
                }
            }
            if (found_flag == patternC)
                word_count++;
            
            //top right
            found_flag = 0;
            for (int i=0; i<patternC; i++) {
                if (y-i >= 0 && x+i < lineC) {
                    if (pattern[i] == ws[y-i][x+i]) {
                        found_flag++;
                    }
                }
            }
            if (found_flag == patternC)
                word_count++;

            //bottom left
            found_flag = 0;
            for (int i=0; i<patternC; i++) {
                if (y+i < lineC && x-i >= 0) {
                    if (pattern[i] == ws[y+i][x-i]) {
                        found_flag++;
                    }
                }
            }
            if (found_flag == patternC)
                word_count++;

            //bottom right
            found_flag = 0;
            for (int i=0; i<patternC; i++) {
                if (y+i < lineC && x+i < lineC) {
                    if (pattern[i] == ws[y+i][x+i]) {
                        found_flag++;
                    }
                }
            }
            if (found_flag == patternC)
                word_count++;
        }
    }

    return word_count;
}

int part1(char* filename)
{
    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char wordSearch[MAX_LINE_LENGTH][MAX_LINE_LENGTH];
    int lineC = 0;

    while (fgets(line, sizeof(line), fp)) {
        strcpy(wordSearch[lineC], line);
        lineC++;
    }

    // print_word_search(wordSearch, lineC);

    fclose(fp);

    return find_word(wordSearch, lineC, "XMAS", 4);
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