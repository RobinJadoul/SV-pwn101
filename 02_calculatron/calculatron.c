#include <stdio.h>
#include <unistd.h>

void setup() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    alarm(30);
}

long long random() {
    long long x;
    static FILE* f = NULL;
    if (!f)
        f = fopen("/dev/urandom", "r");
    fread(&x, sizeof(x), 1, f);
    return x;
}

void get_flag() {
    char flag[0x100] = {0};
    FILE* f = fopen("flag.txt", "r");
    fread(flag, sizeof(flag), 1, f);
    fclose(f);
    puts(flag);
}

int main() {
    char name[24];
    long long my_secret = random();
    long long public = random();

    setup();
    puts("What is your name?");
    fread(name, 0x24, 1, stdin);
    printf("Welcome %s, can you make it onto the leaderboard?\n", name);

    for (int i = 0; i < 0x100; i++) {
        public = random();
        printf("What is <REDACTED VALUE> + %lld?\n> ", public);
        long long answer;
        scanf("%lld", &answer);
        if (answer != public + my_secret) return 1;
    }

    printf("Congratulations %s, you solved my riddle. Have your reward: ", name);
    get_flag();
    return 0;
}
