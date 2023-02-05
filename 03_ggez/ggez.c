#include <stdio.h>

void setup() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void ez() {
    char flag[0x100] = {0};
    FILE* f = fopen("flag.txt", "r");
    fread(flag, sizeof(flag), 1, f);
    fclose(f);
    puts(flag);
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
