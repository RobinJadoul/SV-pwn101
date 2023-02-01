#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAN_LOGIN (1<<0)
#define CAN_CHANGE_NAME (1 << 1)
#define IS_ADMIN (1 << 2)
#define LEN 0x40
#define NUM_USERS 2

typedef struct User {
    char username[LEN];
    char password[LEN];
    uint8_t flags;
} User;

User* all_users[NUM_USERS];

void init_users() {
    all_users[0] = malloc(sizeof(User));
    strcpy(all_users[0]->username, "admin");
    FILE* urandom = fopen("/dev/urandom", "r");
    fread(all_users[0]->password, LEN - 1, 1, urandom);
    all_users[0]->password[LEN - 1] = 0;
    fclose(urandom);
    all_users[0]->flags = IS_ADMIN;

    all_users[1] = malloc(sizeof(User));
    strcpy(all_users[1]->username, "user");
    strcpy(all_users[1]->password, "password");
    all_users[1]->flags = CAN_LOGIN | CAN_CHANGE_NAME;
}

User* login() {
    char input[0x100];
    User* user = NULL;
    printf("Username: ");
    scanf("%s", input);
    for (int i = 0; i < NUM_USERS; i++) {
        if (!strcmp(all_users[i]->username, input)) {
            user = all_users[i];
        }
    }
    if (!user) return user;
    if (!(user->flags & CAN_LOGIN)) {
        printf("This user cannot login!\n");
        return NULL;
    }
    printf("Password: ");
    scanf("%s", input);
    if (strcmp(input, user->password)) {
        printf("Wrong password!\n");
        return NULL;
    }
    return user;
}

void show_bool(int b) {
    printf(b ? "✅" : "❌");
}

void show_user(User* user) {
    printf("Username: ");
    printf(user->username);
    printf("\nPassword: <hah, as if>\n");
    printf("Can login: ");
    show_bool(user->flags & CAN_LOGIN);
    printf("\nCan change username: ");
    show_bool(user->flags & CAN_CHANGE_NAME);
    printf("\nIs admin: ");
    show_bool(user->flags & IS_ADMIN);
    printf("\n");
    
}

void change_username(User* user) {
    if (!(user->flags & CAN_CHANGE_NAME)) {
        printf("I'm afraid I can't let you do that!");
        return;
    }
    printf("New username? > ");
    scanf("%s", user->username);
}

void get_flag(User* user) {
    if (!(user->flags & IS_ADMIN)) {
        printf("Only the admin can do that...\n");
        return;
    }
    FILE* f = fopen("flag.txt", "r");
    char flag[0x100];
    flag[fread(flag, 1, 0x100, f)] = 0;
    fclose(f);
    printf(flag);
}

void init_buffering() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

int main() {
    init_buffering();
    init_users();
    User* user = NULL;
    while (1) {
        if (!user) {
            user = login();
            if (!user) continue;
            printf("Logged in as:\n");
            show_user(user);
        }

        printf("Options:\n\t[0] Logout\n\t[1] Show user info\n\t[2] Change username\n\t[3] Get the flag!\n\t[*] Quit\n> ");
        int choice = 42;
        scanf("%d", &choice);
        switch (choice) {
        case 0:
            user = NULL;
            break;
        case 1:
            show_user(user);
            break;
        case 2:
            change_username(user);
            printf("Username changed successfully, please log in again with your new username now.\n");
            user = NULL;
            break;
        case 3:
            get_flag(user);
            break;
        default:
            return 0;
        }
    }
}
