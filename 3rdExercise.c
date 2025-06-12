#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEMBERS 5
#define MAX_RESPONSES 3
#define MAX_LEN 100

typedef struct { char nickname[50]; int age; char trauma[256]; } Member;
typedef struct { int id; char question[256]; } Question;
typedef struct { char question[256], response[MAX_LEN + 1]; int answered; } Counseling;

Member members[MAX_MEMBERS] = {
    {"Hana", 21, ""}, {"Mina", 22, ""}, {"Yuna", 20, ""}, {"Jisu", 23, ""}, {"Dami", 19, ""}
};

const Question questions[] = {
    {1, "In what situations have you experienced this trauma?"},
    {2, "How has this situation affected your daily life and emotions?"},
    {3, "How have you tried to overcome this trauma?"},
    {4, "What emotions do you associate with this trauma?"},
    {5, "What kind of support do you think is necessary to overcome this trauma?"}
};

Counseling logs[MAX_MEMBERS][MAX_RESPONSES];
int questionIDs[MAX_MEMBERS][MAX_RESPONSES], done[MAX_MEMBERS] = {0};

int findIdx(char *nick) {
    for (int i = 0; i < MAX_MEMBERS; i++) if (!strcmp(nick, members[i].nickname)) return i;
    return -1;
}

void inputTrauma() {
    char nick[50], trauma[256];
    while (1) {
        printf("\nNickname (or 'exit'): "); scanf("%s", nick);
        if (!strcmp(nick, "exit")) break;
        int i = findIdx(nick);
        i != -1 ? (
            printf("Trauma: "), getchar(), fgets(trauma, 256, stdin),
            trauma[strcspn(trauma, "\n")] = 0, strcpy(members[i].trauma, trauma),
            printf("Saved.\n")
        ) : printf("Not found.\n");
    }
}

void shuffle(int *a, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1), t = a[i]; a[i] = a[j]; a[j] = t;
    }
}

void session() {
    char nick[50], resp[MAX_LEN + 1];
    int i;
    printf("\nMembers with trauma:\n");
    for (i = 0; i < MAX_MEMBERS; i++) if (strlen(members[i].trauma)) printf("- %s\n", members[i].nickname);
    printf("\nEnter nickname: "); scanf("%s", nick);
    if ((i = findIdx(nick)) == -1 || !strlen(members[i].trauma)) return;

    if (!done[i]) {
        int ids[5] = {0, 1, 2, 3, 4};
        shuffle(ids, 5);
        for (int j = 0; j < MAX_RESPONSES; j++) {
            strcpy(logs[i][j].question, questions[ids[j]].question);
            logs[i][j].answered = 0;
            questionIDs[i][j] = ids[j];
        }
    }

    printf("\n%s's trauma: %s\n", members[i].nickname, members[i].trauma);
    for (int j = 0; j < MAX_RESPONSES; j++) {
        if (logs[i][j].answered) continue;
        do {
            printf("\nQ: %s\nA: ", logs[i][j].question);
            getchar(); fgets(resp, MAX_LEN + 1, stdin);
            resp[strcspn(resp, "\n")] = 0;
            if (!strcmp(resp, "pause")) return;
        } while (!strlen(resp) || strlen(resp) > MAX_LEN);
        strcpy(logs[i][j].response, resp);
        logs[i][j].answered = 1;
    }

    done[i] = 1;
    printf("\nSession complete.\n");
}

void viewData() {
    char nick[50]; printf("Nickname: "); scanf("%s", nick);
    int i = findIdx(nick);
    if (i == -1 || !done[i]) return;
    printf("\n--- %s ---\nTrauma: %s\n", members[i].nickname, members[i].trauma);
    for (int j = 0; j < MAX_RESPONSES; j++) {
        printf("\nQ: %s\nA: %s\n", logs[i][j].question, logs[i][j].response);
    }
}

void overcomeTrauma() {
    char c;
    srand(time(NULL));
    do {
        printf("\n--- Trauma Management ---\nA. Input Trauma\nB. Counseling\nC. View Results\nX. Back\nChoice: ");
        scanf(" %c", &c);
        c == 'A' || c == 'a' ? inputTrauma() :
        c == 'B' || c == 'b' ? session() :
        c == 'C' || c == 'c' ? viewData() :
        (void)0;
    } while (c != 'X' && c != 'x');
}

void trainingMenu() {
    char c;
    do {
        printf("\n--- II. Training ---\n1. Daily Practice\n2. Self-Management and Teamwork\nX. Back\nChoice: ");
        scanf(" %c", &c);
        if (c == '2') {
            char sub;
            do {
                printf("\n--- 2. Self-Management and Teamwork ---\nA. Mental Check\nB. Trauma Management\nX. Back\nChoice: ");
                scanf(" %c", &sub);
                (sub == 'B' || sub == 'b') ? overcomeTrauma() : (void)0;
            } while (sub != 'X' && sub != 'x');
        }
    } while (c != 'X' && c != 'x');
}

int main() {
    char choice;
    do {
        printf("\n=== Main Menu ===\nI. Performance\nII. Training\nX. Exit\nSelect: ");
        scanf(" %c", &choice);
        (choice == 'I' || choice == 'i') ? printf("Performance section.\n") :
        (choice == 'II' || choice == 'i') ? trainingMenu() :
        (void)0;
    } while (choice != 'X' && choice != 'x');
    return 0;
}
