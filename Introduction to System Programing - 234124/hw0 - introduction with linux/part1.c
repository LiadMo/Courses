#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int count_pow_of_two(int number) {
    int count = 0;
    while (number != 1) {
        number = number>>1;
        count = count + 1;
    }
    return count;
}

bool is_pow_of_two(int number) {
    if ((number & (number - 1)) == 0) {
        return true;
    } else
        return false;
}

int main (int argc, char **argv) {
    int count = 0;
    int sum_of_exponent = 0;
    int status;

    printf("Enter size of input:\n");
    status = scanf("%d", &count);
    if (status == 0 || count <= 0) {
        printf("Invalid size\n");
        return 0;
    }

    int *numbers_ptr = calloc(count, sizeof(*numbers_ptr));
    if (numbers_ptr == NULL) {
        return 0;
    }

    for (int i = 0; i < count; i++) {
        numbers_ptr[i] = -1;
    }

    int tmp;
    printf("Enter numbers:\n");
    for (int i = 0; i < count; i++) {
        status = scanf("%d", &tmp);
        if (status == 0) {
            printf("Invalid number\n");
            free(numbers_ptr);
            return 0;
        }
        if (tmp > 0 && is_pow_of_two(tmp)) {
            numbers_ptr[i] = tmp;
            sum_of_exponent = sum_of_exponent + count_pow_of_two(tmp);
        }
    }

    for (int i = 0; i < count; i++){
        if(numbers_ptr[i] != -1){
            printf("The number %d is a power of 2: %d = 2^%d\n", numbers_ptr[i], numbers_ptr[i], count_pow_of_two(numbers_ptr[i]));
        }
    }

    free(numbers_ptr);
    numbers_ptr = NULL;

    printf("Total exponent sum is %d\n", sum_of_exponent);
}

