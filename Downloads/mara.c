#include <stdio.h>

void count_character_frequencies() {
    // Initialize an array to store character frequencies
    int frequencies[256] = {0}; // Assuming ASCII characters
    
    // Read characters from stdin until EOF
    int c;
    while ((c = getchar()) != '0') {
        // Increment the frequency of the character
        frequencies[c]++;
    }
    
    // Print the frequencies of characters
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            printf("Character '%c' appeared %d times\n", i, frequencies[i]);
        }
    }
}

int main() {
    printf("Enter characters:\n");
    count_character_frequencies();
    return 0;
}