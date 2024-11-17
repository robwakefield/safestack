/* Example of a program protected by SafeStack */

#include <stdio.h>
#include <string.h>

void process_user_input(char *input) {
    char buffer[8];
    strcpy(buffer, input);
    printf("Buffer: %s\n", buffer);
}

int main() {
    char input[32];
    printf("Enter input: ");
    fgets(input, sizeof(input), stdin);
    process_user_input(input);
    return 0;
}

/*
Example attack: 
printf 'AAAAAAAABBBBBBBBCCCCCCCC\n' | ./build/examples/safestack

The attack string is constructed as:
- 8 bytes ('AAAAAAAA') to fill the buffer
- 8 bytes ('BBBBBBBB') to overflow past buffer 
- 8 bytes ('CCCCCCCC') to overwrite return address

Expect to see a seg fault without SafeStack, and no seg fault with SafeStack.
*/
