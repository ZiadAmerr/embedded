#include <stdio.h>

void get_grade(int score);

int main() {
    int score;

    printf("Enter your score: ");
    scanf("%d", &score);

    get_grade(score);

    return 0;
}

void get_grade(int score) {
    if (100 >= score && score >= 93) {
        printf("A");
    } else if (score <= 92 && score >= 85) {
        printf("B+");
    } else if (score <= 84 && score >= 75) {
        printf("B");
    } else if (score <= 74 && score >= 70) {
        printf("C+");
    } else if (score <= 69 && score >= 61) {
        printf("C");
    } else if (score <= 60 && score >= 0) {
        printf("D");
    } else {
        printf("Invalid score");
        return;
    }
    printf("\n");
}