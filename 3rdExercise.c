#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long calculate_sum(long n);
int get_valid_input(long *result);
void print_banner();

int main(void) {
    long n, sum;
    
    print_banner();
    
    while (1) {
        printf("\nEnter a positive integer (0 to exit): ");
        
        if (!get_valid_input(&n)) {
            fprintf(stderr, "Error: Invalid input. Please try again.\n");
            continue;
        }
        
        if (n == 0) {
            printf("\nProgram terminated. Goodbye!\n");
            break;
        }
        
        if (n < 0) {
            fprintf(stderr, "Error: Negative numbers not allowed.\n");
            continue;
        }
        
        if (n > 1000000L) {
            printf("Warning: Large input might cause integer overflow.\n");
        }
        
        sum = calculate_sum(n);
        printf("\nSum of first %ld natural numbers = %ld\n", n, sum);
        printf("Formula verification: %ld * (%ld + 1)/2 = %ld\n", 
               n, n, (n * (n + 1)) / 2);
    }

    return 0;
}

int get_valid_input(long *result) {
    char input[50];
    char *endptr;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }
    
    errno = 0;
    long value = strtol(input, &endptr, 10);
    
    if (endptr == input) return 0;
    if (*endptr != '\n' && *endptr != '\0') return 0;
    if (errno == ERANGE) return 0;
    if (value > INT_MAX) return 0;
    
    *result = value;
    return 1;
}

long calculate_sum(long n) {
    if (n > 0 && n > LONG_MAX / (n + 1)) {
        fprintf(stderr, "Error: Integer overflow detected.\n");
        return -1;
    }
    return n * (n + 1) / 2;
}

void print_banner() {
    printf("=============================================\n");
    printf(" Natural Number Sum Calculator\n");
    printf("=============================================\n");
    printf("Calculates sum of first N natural numbers\n");
    printf("Uses efficient mathematical formula: n(n+1)/2\n\n");
}