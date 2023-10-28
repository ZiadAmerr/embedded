#include <stdio.h>
#include <stdlib.h>

#define TASK7

#ifdef TASK1
    int add(int *a, int *b) {
        return *a + *b;
    }

    int main() {

        int a = 10, b = 20;
        int *p1 = &a, *p2 = &b;

        printf("Sum of %d and %d is %d\n", a, b, add(p1, p2));

        return 0;
    }
#endif

#ifdef TASK2

    void multiply_arr_by_num(int *arr, int size, int num) {
        for (int i = 0; i < size; i++) {
            arr[i] *= num;
        }
    };

    int main() {
        int arr[] = {1, 2, 3, 4, 5};
        int size = sizeof(arr) / sizeof(arr[0]);
        int num = 2;

        multiply_arr_by_num(arr, size, num);

        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
    }
#endif


#ifdef TASK3

    void swap(int *a, int *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    int main() {
        int a = 10, b = 20;
        int *p1 = &a, *p2 = &b;

        printf("Before swap: a = %d, b = %d\n", a, b);
        swap(p1, p2);
        printf("After swap: a = %d, b = %d\n", a, b);

        return 0;
    }
#endif


#ifdef TASK4

    int get_str_len(char *str) {
        int len = 0;
        while (*str != '\0') {
            len++;
            str++;
        }
        return len;
    }

    int main() {
        char str[] = "Hello World!";
        printf("Length of string \"%s\" is %d\n", str, get_str_len(str));
        return 0;
    }
#endif


#ifdef TASK5

    int get_str_len(char *str) {
        int len = 0;
        while (*str != '\0') {
            len++;
            str++;
        }
        return len;
    }

    char *concat(char *str1, char *str2) {
        int len1 = get_str_len(str1);
        int len2 = get_str_len(str2);
        char *new_str = malloc(len1 + len2 + 1);
        char *p = new_str;

        while (*str1 != '\0') {
            *p = *str1;
            p++;
            str1++;
        }

        while (*str2 != '\0') {
            *p = *str2;
            p++;
            str2++;
        }

        *p = '\0';

        return new_str;
    }

    int main() {
        char str1[] = "Hello";
        char str2[] = " World!";
        char *new_str = concat(str1, str2);
        printf("Concatenated string: %s\n", new_str);
        free(new_str);
        return 0;
    }

#endif


#ifdef TASK6

    int* sort(int *arr, int size) {
        int *sorted_arr = malloc(size * sizeof(int));
        int *p = sorted_arr;

        for (int i = 0; i < size; i++) {
            *p = arr[i];
            p++;
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (*(sorted_arr + j) > *(sorted_arr + j + 1)) {
                    int temp = *(sorted_arr + j);
                    *(sorted_arr + j) = *(sorted_arr + j + 1);
                    *(sorted_arr + j + 1) = temp;
                }
            }
        }

        return sorted_arr;
    }

    int main() {
        int arr[] = {1, 2, 3, 4, 5};
        int size = sizeof(arr) / sizeof(arr[0]);
        int *sorted_arr = sort(arr, size);

        for (int i = 0; i < size; i++) {
            printf("%d ", *(sorted_arr + i));
        }

        free(sorted_arr);
        return 0;
    }

#endif

#ifdef TASK7

    // return index of element

    int find_idx(int *arr, int size, int num) {
        for (int i = 0; i < size; i++) {
            if (*(arr + i) == num) {
                return i;
            }
        }
        return -1;
    }

    int main() {
        int arr[] = {1, 2, 3, 4, 5};
        int size = sizeof(arr) / sizeof(arr[0]);
        int num = 3;

        printf("Index of %d is %d\n", num, find_idx(arr, size, num));
        printf("Index of %d is %d\n", 10, find_idx(arr, size, 10));

        return 0;
    }

#endif