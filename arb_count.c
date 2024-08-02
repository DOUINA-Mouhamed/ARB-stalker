/*
** File:        arb_count.c
**
** Created by:  DOUINA Mouhamed
** GitHub : DOUINA-Mouhamed
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* function to handle input errors and ensure valid input */
void userInputError(const char *prompt, int min, int max, int *value) {
    int valid = 0;
    while (!valid) {
        printf("%s", prompt);
        if (scanf("%d", value) != 1) {
            /* check for EOF (Ctrl+D) */
            if (feof(stdin)) {
                printf("\nEOF detected. Exiting.\n");
                exit(EXIT_FAILURE);
            }
            printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
            /* clear the input buffer */
            while (getchar() != '\n');
        } else if (*value < min || *value > max) {
            printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
        } else {
            valid = 1;
        }
    }
}

/* function to handle input errors for float values */
void userInputErrorFloat(const char *prompt, float *value) {
    int valid = 0;
    while (!valid) {
        printf("%s", prompt);
        if (scanf("%f", value) != 1) {
            /* check for EOF (Ctrl+D) */
            if (feof(stdin)) {
                printf("\nEOF detected. Exiting.\n");
                exit(EXIT_FAILURE);
            }
            printf("Invalid input. Please enter a positive number.\n");
            /* clear the input buffer */
            while (getchar() != '\n');
        } else if (*value < 0) {
            printf("Invalid input. Please enter a positive number.\n");
        } else {
            valid = 1;
        }
    }
}

/* function to add a new transaction to the file */
void addTransaction(const char *filename) {
    FILE *file;
    int day, month, year;
    float eur, arb;

    /* open the file in append mode */
    file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file for appending");
        exit(EXIT_FAILURE);
    }

    /* prompt the user for transaction details with validation */
    userInputError("Day (DD): ", 1, 31, &day);
    userInputError("Month (MM): ", 1, 12, &month);
    userInputError("Year (YYYY): ", 1900, 2100, &year);
    userInputErrorFloat("EUR (00.00): ", &eur);
    userInputErrorFloat("ARB (00.00): ", &arb);

    /* write the transaction to the file */
    fprintf(file, "%02d/%02d/%04d:%.2fE:%.2fARB\n", day, month, year, eur, arb);

    fclose(file);

    printf("\n\033[1;32mTransaction added successfully.\033[0m\n");
}

/* function to calculate and display the total invested amount and ARB in possession */
void calculateTotal(const char *filename, float *totalInvested, float *totalARB) {
    FILE *file;
    char *line = NULL;
    size_t linecap = 0;
    *totalInvested = 0.0f;
    *totalARB = 0.0f;

    /* open the file in read mode */
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    /* read each line from the file using fgets and realloc */
    while (1) {
        size_t len = 0;
        int c;

        /* read until newline or EOF */
        while ((c = fgetc(file)) != EOF && c != '\n') {
            if (len + 1 >= linecap) {
                linecap = linecap ? linecap * 2 : 128;
                line = realloc(line, linecap);
                if (line == NULL) {
                    perror("Unable to allocate memory");
                    exit(EXIT_FAILURE);
                }
            }
            line[len++] = c;
        }

        /* break if EOF and no characters read */
        if (c == EOF && len == 0) {
            break;
        }

        /* null-terminate the string */
        line[len] = '\0';

        /* skip header */
        if (line[0] == '#') {
            continue;
        }

        char *euroStr, *arbStr;
        float euroValue, arbValue;

        strtok(line, ":"); /* skip the date */
        euroStr = strtok(NULL, ":");
        arbStr = strtok(NULL, ":");

        /* check if euroStr is not NULL and is a valid number */
        if (euroStr != NULL && isdigit(euroStr[0])) {
            euroValue = atof(euroStr);
            *totalInvested += euroValue;
        }

        /* check if arbStr is not NULL and is a valid number */
        if (arbStr != NULL && isdigit(arbStr[0])) {
            arbValue = atof(arbStr);
            *totalARB += arbValue;
        }
    }

    /* free the allocated line buffer */
    free(line);
    
    /* close the file */
    fclose(file);
}

/* function to call the JavaScript file to fetch the ARB price */
float fetchArbPrice() {
    /* fetch the price and store in a temporary file */
    system("node fetchArbPrice.js > arb_price.txt");

    /* open the file and read the price */
    FILE *file = fopen("arb_price.txt", "r");
    if (file == NULL) {
        perror("Error opening arb_price.txt");
        exit(EXIT_FAILURE);
    }

    float arbPrice = 0.0f;
    fscanf(file, "%f", &arbPrice); /* read the price */
    fclose(file);

    /* remove the temporary file */
    remove("arb_price.txt");

    return arbPrice;
}

/* function to display help information */
void displayHelp(const char *programName) {
    printf("Usage: %s [options] <filename>\n", programName);
    printf("\nOptions:\n");
    printf("  -h               Display this help message and exit.\n");
    printf("  -t <filename>    Add a new transaction to the specified file.\n");
    printf("  -s <filename>    Calculate and display the potential profit/loss based on the current ARB price.\n");
    printf("  <filename>       Calculate the total investment and ARB in possession.\n");
    printf("\nExamples:\n");
    printf("  %s transactions.txt          Calculate total investment and ARB in possession.\n", programName);
    printf("  %s -t transactions.txt       Add a new transaction.\n", programName);
    printf("  %s -s transactions.txt       Calculate profit/loss.\n", programName);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-h] [-t] [-s] <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    float totalInvested = 0.0f;
    float totalARB = 0.0f;
    float cashOutTax = 1.0f; /* cash-out tax of 1 EUR */

    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        /* -h flag, display help information */
        displayHelp(argv[0]);
        return EXIT_SUCCESS;
    } else if (argc == 2) {
        /* no flag, just calculate the total investment and ARB in possession */
        calculateTotal(argv[1], &totalInvested, &totalARB);

        /* fetch and display the current ARB price */
        float currentPrice = fetchArbPrice();
        printf("\033[1;36mFetching current ARB price...\033[0m\n");
        printf("\033[1;36mCurrent ARB value in EUR:\033[0m \033[1;37m%.5fE\033[0m\n", currentPrice);

        /* display the totals */
        printf("\033[1;32mTotal invested (tax included):\033[0m \033[1;37m%.2fE\033[0m\n", totalInvested);
        printf("\033[1;34mTotal Arbitrum in possession:\033[0m \033[1;37m%.2fARB\033[0m\n", totalARB);

    } else if (argc == 3 && strcmp(argv[1], "-t") == 0) {
        /* -t flag, add a new transaction and then calculate the total investment and ARB */
        addTransaction(argv[2]);
        calculateTotal(argv[2], &totalInvested, &totalARB);

        /* fetch and display the current ARB price */
        float currentPrice = fetchArbPrice();
        printf("\033[1;36mFetching current ARB price...\033[0m\n");
        printf("\033[1;36mCurrent ARB value in EUR:\033[0m \033[1;37m%.5fE\033[0m\n", currentPrice);

        /* display the totals */
        printf("\033[1;32mTotal invested (tax included):\033[0m \033[1;37m%.2fE\033[0m\n", totalInvested);
        printf("\033[1;34mTotal Arbitrum in possession:\033[0m \033[1;37m%.2fARB\033[0m\n", totalARB);

    } else if (argc == 3 && strcmp(argv[1], "-s") == 0) {
        /* -s flag, calculate potential profit/loss */
        calculateTotal(argv[2], &totalInvested, &totalARB);
        float currentPrice = fetchArbPrice();
        float currentValue = currentPrice * totalARB;
        float difference = currentValue - totalInvested - cashOutTax; /* include cash-out tax in the calculation */


        printf("\033[1;32mTotal invested (tax included):\033[0m \033[1;37m%.2fE\033[0m\n", totalInvested);

        printf("\033[1;34mTotal Arbitrum in possession:\033[0m \033[1;37m%.2fARB\033[0m\n", totalARB);

        printf("\033[1;36mCurrent ARB value in EUR:\033[0m \033[1;37m%.2fE\033[0m\n", currentValue);

        if (difference > 0) {
            printf("\033[1;32mProfit:\033[0m \033[1;37m%.2fE\033[0m\n", difference);
        } else {
            printf("\033[1;31mLoss:\033[0m \033[1;37m%.2fE\033[0m\n", difference);
        }
    } else {
        /* incorrect usage */
        fprintf(stderr, "Usage: %s [-h] [-t] [-s] <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
