#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 256

typedef struct {
    char keyword[8];
    char message[MAX_LEN];
} EasterEgg;

EasterEgg arthurEgg = {
    "specter",
    "I confess. After graduating from university, I was blinded by the arrogance of starting a startup and recklessly blocked my friends' paths. "
    "I painfully learned that when I am the only one convinced by my idea, it leads to disastrous results. "
    "The past Arthur was a ghost of dogmatism and stubbornness."
};

void charToBinary(char c, char *bin) {
    int i;
    for (i = 7; i >= 0; i--) {
        bin[7 - i] = ((c >> i) & 1) + '0';
    }
    bin[8] = '\0';
}

int isRightChar(char bin[][9], char *input) {
    int i, j;
    for (i = 0; i < 7; i++) {
        char expected = 0;
        for (j = 0; j < 8; j++) {
            expected = (expected << 1) | (bin[i][j] - '0');
        }
        if (input[i] != expected) {
            return 0;
        }
    }
    return 1;
}

int isEasterEgg(char *input) {
    return strcmp(input, arthurEgg.keyword) == 0;
}

void find_easter_egg() {
    int i;
    char binaries[7][9];
    char input[8];
    char finalWord[8];

    printf("<<Arthur's Easter Egg>>\n");

    for (i = 0; i < 7; i++) {
        charToBinary(arthurEgg.keyword[i], binaries[i]);
    }

    printf("Enter characters for reversed binary codes:\n");
    for (i = 6; i >= 0; i--) {
        printf("%s ", binaries[i]);
    }
    printf("\n");

    scanf("%7s", input);

    if (!isRightChar(binaries, input)) {
        printf("Incorrect input. Try again.\n");
        return;
    }

    printf("Combine the characters into a word: ");
    scanf("%7s", finalWord);

    if (isEasterEgg(finalWord)) {
        printf("##Easter Egg Discovered!$$\n");
        printf("%s\n", arthurEgg.message);
    } else {
        printf("Wrong word. Returning to menu.\n");
    }
}

void scrambleAndBinary() {
    char temp[8];
    char odd[8], even[8];
    int o = 0, e = 0;
    int i;
    char bin[9];
    strcpy(temp, arthurEgg.keyword);

    for (i = 0; i < 3; i++) {
        char t = temp[i];
        temp[i] = temp[6 - i];
        temp[6 - i] = t;
    }

    for (i = 0; i < 7; i++) {
        if (i % 2 == 1) {
            odd[o++] = temp[i];
        } else {
            even[e++] = temp[i];
        }
    }

    for (i = 0; i < o; i++) {
        charToBinary(odd[i], bin);
        printf("%s ", bin);
    }
    for (i = 0; i < e; i++) {
        charToBinary(even[i], bin);
        printf("%s ", bin);
    }
    printf("\n");
}

void self_management_menu() {
    char input[32];
    printf("2. Self-Management and Teamwork\n");
    printf("Enter your name: ");
    scanf("%31s", input);
    if (strcmp(input, "Arthur") == 0) {
        find_easter_egg();
    } else {
        printf("Welcome, %s\n", input);
    }
}

void training_menu() {
    int choice;
    while (1) {
        printf("\n[II. Training]\n");
        printf("1. Communication\n");
        printf("2. Self-Management and Teamwork\n");
        printf("3. Exit\n");
        printf("Select option: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                printf("Coming soon: Communication Training\n");
                break;
            case 2:
                self_management_menu();
                break;
            case 3:
                return;
            default:
                printf("Invalid option.\n");
        }
    }
}

int main() {
    training_menu();
    return 0;
}
