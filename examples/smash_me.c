#include <stdio.h>
#include <string.h>

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
extern char* gets(char* str);

void smash_me() {
    char buffer[16];
    gets(buffer);
}

int main() {
    char buffer[16];
    memset(buffer, 0, sizeof(buffer));
    smash_me();
    puts(buffer);
    return 0;
}
