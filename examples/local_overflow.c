/* Data-only attack: safestack does not protect against data overflow between local variables */

#include <stdio.h>
#include <string.h>

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
extern char* gets(char* str);

struct User {
    char user_email[16];
    int is_admin;
};

int is_user_admin(char* input) {
    struct User user;
    user.is_admin = 0;

    strcpy(user.user_email, input);

    // ... other logic ...

    return user.is_admin;
}

int main() {
    char input[32];
    gets(input);
    if (is_user_admin(input)) {
        puts("User is admin");
    } else {
        puts("User is not admin");
    }
    return 0;
}

/*
Example attack: printf 'AAAAAAAAAAAAAAAA\x01\x00\x00\x00' | ./build/examples/local_overflow_safestack
*/