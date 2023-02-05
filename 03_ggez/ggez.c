#include <stdio.h>
#include <unistd.h>

void setup() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void ez() {
    execl("/bin/sh", "/bin/sh", NULL);
}

void gg() {
    char *questions[] = {"What is your name?", "What is your quest?", "What is the airspeed velocity of an unladen swallow?"};
    char answer[0x40];
    for (int i = 0; i < sizeof(questions)/sizeof(questions[0]); i++) {
        puts(questions[i]);
        gets(answer);
        puts("Hmm, I see.");
    }
    puts("Aaaaaaaaaaaaa");
}

int main() {
    setup();
    gg();
}
