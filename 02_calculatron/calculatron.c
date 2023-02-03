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

#define byte(x, i) (((char*)&x)[i])

int main() {
    long long public = random();
    long long my_secret = random();
    char name[32];

    setup();
    puts("What is your name?");
    fgets(name, 0x32, stdin);
    printf("Welcome %s, can you make it onto the leaderboard?\n", name);

    // Ensure we have enough entropy
    for (int i = 0; i < sizeof(long long); i++) {
        for (int j = 0; j < i; j++) {
            if (byte(my_secret, i) == byte(my_secret, j)) {
                puts("Out of entropy, please order a new computer!");
                return 2;
            }
        }
    }
    
    for (int i = 0; i < 0x100; i++) {
        public = random();
        printf("What is <REDACTED VALUE> + %lld?\n> ", public);
        long long answer;
        scanf("%lld", &answer);
        if (answer != public + my_secret) {
            return 1;
        }
    }

    printf("Congratulations %s, you solved my riddle. Have your reward: ", name);
    get_flag();
    return 0;
}
