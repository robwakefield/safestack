/* Control flow attack: an overflow of buffer can overwrite the function pointer leading to control flow hijacking */

#include <stdio.h>
#include <string.h>

// A Struct forces the buffer and function pointer to be adjacent on the safe stack
struct VulnerableStruct {
    char buffer[8];
    void (*function_pointer)();
};

void vulnerable_function(char *input) {
    // Put struct on unsafe stack
    struct VulnerableStruct vulnerable_data;
    vulnerable_data.function_pointer = NULL;

    // Intentionally overflow to reach function_pointer
    memcpy(vulnerable_data.buffer, input, 16); 

    if (vulnerable_data.function_pointer) {
        // Attacker has control of the program flow
        printf("function_pointer: %p\n", vulnerable_data.function_pointer);
        vulnerable_data.function_pointer();
    } else {
        printf("Function pointer not overwritten.\n");
    }
}

void another_function() {
    printf("Control flow hijacked!\n");
}

int main(int argc, char *argv[]) {
    char input[256];
    void* address_of_another_function = (void*)&another_function;
    printf("Address of another_function: %p\n", address_of_another_function);
    
    // Create payload by filling the buffer and adding the address of function to call
    memset(input, 'A', 8);
    memcpy(input + 8, &address_of_another_function, sizeof(void*));
    
    vulnerable_function(input);
    return 0;
}

/*
Example attack: ./build/examples/control_flow_overflow_safestack (Payload is created in main)
*/
