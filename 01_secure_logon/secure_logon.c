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
    uint32_t flags;
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
    char input[LEN];
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
        puts("This user cannot login!");
        return NULL;
    }
    printf("Password: ");
    scanf("%s", input);
    if (!strcmp(input, user->password)) {
        puts("Wrong password!");
        return NULL;
    }
    return user;
}

void show_user(User* user) {
}

void change_username(User* user) {
    
}

void get_flag(User* user) {
    if (!(user->flags & IS_ADMIN)) {
        puts("Only the admin can do that...");
        return;
    }
    FILE* f = fopen("flag.txt", "r");
    char flag[0x100];
    fread(flag, 0x100, 1, f);
    fclose(f);
    puts(flag);
}

int main() {
    init_users();
    User* user = NULL;
    while (1) {
        if (!user) {
            user = login();
            if (!user) continue;
            puts("Logged in as:");
            show_user(user);
        }

        puts("Options:\n\t[0] Logout\n\t[1] Show user info\n\t[2] Change username\n\t[3] Get the flag!\n\t[*] Quit");
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
            break;
        case 3:
            get_flag(user);
            break;
        default:
            return 0;
        }
    }
}