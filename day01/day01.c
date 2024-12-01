#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define LIST_SIZE 1024

int compare_asc(const void *a, const void *b)
{
    int int_a = *(int *)a;
    int int_b = *(int *)b;
    return int_a - int_b;
}

void print_list(int* list, int length)
{
    for (int i=0; i<length; i++) {
        printf("%d\n", list[i]);
    }
    printf("\nLength: %d\n", length);
}

int part1(char* filename)
{
    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int c = 0;
    int list1[LIST_SIZE];
    int list2[LIST_SIZE];
    int sum = 0;

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d %d", &list1[c], &list2[c]);
        c++;
    }
    fclose(fp);

    qsort(list1, c, sizeof(int), compare_asc);
    qsort(list2, c, sizeof(int), compare_asc);

    for (int i=0; i<c; i++) {
        sum += abs(list1[i] - list2[i]);
    }

    return sum;
}

int find_occurences(int list[], int length, int target)
{
    int *found = bsearch(&target, list, length, sizeof(int), compare_asc);
    if (!found)
        return 0;

    int count = 1;
    int *left = found-1;
    int *right = found+1;

    //count to the left
    while (left >= list && *left == target) {
        count++;
        left--;
    }

    //count to the right
    while (right < list + length && *right == target) {
        count++;
        right++;
    }

    // printf("%d found %d time(s).\n", target, count);

    return count;
}

int part2(char* filename)
{
    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int c = 0;
    int list1[LIST_SIZE];
    int list2[LIST_SIZE];
    int similarity_score = 0;

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d %d", &list1[c], &list2[c]);
        c++;
    }
    fclose(fp);

    qsort(list2, c, sizeof(int), compare_asc);

    // print_list(list2, c);

    for (int i=0; i<c; i++) {
        similarity_score += list1[i] * find_occurences(list2, c, list1[i]);
    }

    return similarity_score;
}

int main(int argc, char** argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <1|2> <inputfile>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "1") == 0) {
        printf("Sum: %d\n", part1(argv[2]));
    } else if (strcmp(argv[1], "2") == 0) {
        printf("Sum: %d\n", part2(argv[2]));
    } else {
        fprintf(stderr, "Usage: %s <1|2> <inputfile>\n", argv[0]);
        return 1;
    }

    return 0;
}