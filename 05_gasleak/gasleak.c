#include <stdio.h>
#include <unistd.h>

void setup() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void boom(long long secret) {
    execl(&"asdffdsaadsfadfadfa/bin/sh"[secret], "/bin/sh", NULL);
}

void do_read(char* addr) {
    while ((*addr++ = getchar()) != '\n');
}

void gg() {
    char *questions[] = {"What is your name?", "What is your quest?", "What is the airspeed velocity of an unladen swallow?"};
    char answer[0x40];
    for (int i = 0; i < sizeof(questions)/sizeof(questions[0]); i++) {
        puts(questions[i]);
        do_read(answer);
        puts("Hmm, I see.");
        puts(answer);
    }
    puts("Aaaaaaaaaaaaa");
}

int main() {
    setup();
    gg();
}
