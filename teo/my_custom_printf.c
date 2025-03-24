#include "my_custom_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to print an integer with padding
void print_integer_with_padding(int value, int width, char padding_char) {
    char buffer[20];  // Adjust buffer size as needed
    snprintf(buffer, sizeof(buffer), "%*d", width, value);
    fputs(buffer, stdout);
}

// Helper function to print an integer in hexadecimal with padding
void print_hex_with_padding(int value, int width, char padding_char, int uppercase) {
    char buffer[20];  // Adjust buffer size as needed
    const char *format = uppercase ? "%0*X" : "%0*x";
    snprintf(buffer, sizeof(buffer), format, width, value);
    fputs(buffer, stdout);
}

// Helper function to print a string
void print_string(const char *str) {
    fputs(str, stdout);
}

// Helper function to print an integer in binary
void print_binary(int value) {
    char buffer[33];  // Adjust buffer size as needed
     sprintf(buffer, "%d", value);
    fputs(buffer, stdout);
}

// Custom printf function
int my_custom_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int printed_chars = 0;
    char ch;

    while ((ch = *format++) != '\0') {
        if (ch != '%') {
            putchar(ch);
            printed_chars++;
            continue;
        }

        // Handle formatting tags
        switch (*format++) {
            case 'c': {
                char c = va_arg(args, int); // char is promoted to int in varargs
                putchar(c);
                printed_chars++;
                break;
            }
            case 'd': {
                int value = va_arg(args, int);
                printf("%d", value);
                break;
            }
            case 's': {
                const char *str = va_arg(args, const char *);
                fputs(str, stdout);
                printed_chars += strlen(str);
                break;
            }
            // Add more cases for other formatting tags...
            default:
                putchar(ch);
                printed_chars++;
                break;
        }
    }

    va_end(args);
    return printed_chars;
}

//the custom printf function
//parses the format string and
//calls the appropriate helper functions based on the formatting tags encountered.

