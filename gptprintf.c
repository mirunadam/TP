/*#include <stdarg.h>
#include <stdio.h>

// Function to calculate the number of digits in an integer
int count_digits(int num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        ++count;
    }
    return count;
}

// Function to print a string with padding
void print_with_padding(const char *str, int width, char padding) {
    int len = 0;
    while (str[len] != '\0')
        len++;

    if (len >= width) {
        for (int i = 0; i < len; ++i)
            putchar(str[i]);
    } else {
        for (int i = 0; i < width - len; ++i)
            putchar(padding);
        for (int i = 0; i < len; ++i)
            putchar(str[i]);
    }
}

// Function to print an integer in binary format
void print_binary(int num) {
    if (num > 1)
        print_binary(num / 2);
    putchar('0' + num % 2);
}

// Function to convert decimal number to hexadecimal in uppercase letters
void change_to_hexadecimal_uppercase_letters(unsigned decimal_number) {
    char hexadecimal_num[32];
    int i = 0;

    if (decimal_number == 0) {
        putchar('0');
        putchar('\n');
        return;
    }

    while (decimal_number > 0) {
        int remainder = decimal_number % 16;
        if (remainder < 10) {
            hexadecimal_num[i] = remainder + '0';
        } else {
            hexadecimal_num[i] = remainder - 10 + 'A';
        }
        decimal_number /= 16;
        i++;
    }

    for (int j = i - 1; j >= 0; j--) {
        putchar(hexadecimal_num[j]);
    }
    putchar('\n');
}

// Custom printf implementation
int my_custom_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            ++format;
            int width = 0;
            char padding = ' ';
            while (*format >= '0' && *format <= '9') {
                width = width * 10 + (*format - '0');
                ++format;
            }
            if (*format == '0') {
                padding = '0';
                ++format;
            }
            if (*format == 'b') {
                int num = va_arg(args, int);
                print_binary(num);
            } else if (*format == 'c') {
                char c = (char)va_arg(args, int);
                putchar(c);
            } else if (*format == 'd') {
                int num = va_arg(args, int);
                char num_str[12]; // Assuming a maximum of 12 digits for an integer
                sprintf(num_str, "%d", num);
                print_with_padding(num_str, width, padding);
            } else if (*format == 's') {
                char *str = va_arg(args, char*);
                while (*str != '\0') {
                    putchar(*str);
                    ++str;
                }
            } else if (*format == 'x' || *format == 'X') {
                unsigned int num = va_arg(args, unsigned int);
                change_to_hexadecimal_uppercase_letters(num);
            } else if (*format == 'p') {
                ++format;
                void *ptr = va_arg(args, void*);
                printf("%p", ptr);
            }
        } else {
            putchar(*format);
        }
        ++format;
    }
    va_end(args);
    return 0;
}

int main() {
    my_custom_printf("%03X\n", 45057);  // Output: "11A1"
    my_custom_printf("%05X\n", 45057);  // Output: "011A1"
    my_custom_printf("%08X\n", 45057);  // Output: "00011A1"
    return 0;
}*/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


void padding_d(char padding_char, int width, int number) {
    char buffer[20]; // Assuming maximum width of 20 characters
    int printed_chars = snprintf(buffer, sizeof(buffer), "%d", number);
    int padding = width - printed_chars;
    if (padding > 0) {
        for (int i = 0; i < padding; i++) {
            putchar(padding_char);
        }
    }
    printf("%s", buffer);
}

void print_binary(int value) {
    char buffer[33]; // 32 bits + null terminator
    int i = 0;
    if (value == 0) {
        putchar('0');
        return;
    }
    while (value != 0) {
        buffer[i++] = (value & 1) ? '1' : '0';
        value >>= 1;
    }
    while (i > 0) {
        putchar(buffer[--i]);
    }
    putchar('\n');
}

void print_padding(int width, char padding) 
{
    for (int i = 0; i < width; i++) 
    {
        putchar(padding);
    }
}

void padding_binary(char padding, int width, int value) {
    print_padding(width, padding);
    print_binary(value);

}

void padding_hexa_upper(char padding_char, int width, int number) {
    char buffer[20]; // Assuming maximum width of 20 characters
    int printed_chars = snprintf(buffer, sizeof(buffer), "%X", number); // Convert integer to hexadecimal string
    int padding = width - printed_chars;
    if (padding > 0) {
        for (int i = 0; i < padding; i++) {
            putchar(padding_char);
        }
    }
    printf("%s", buffer);
}

void padding_hexa_low(char padding_char, int width, int number) {
    char buffer[20]; // Assuming maximum width of 20 characters
    int printed_chars = snprintf(buffer, sizeof(buffer), "%x", number); // Convert integer to hexadecimal string
    int padding = width - printed_chars;
    if (padding > 0) {
        for (int i = 0; i < padding; i++) {
            putchar(padding_char);
        }
    }
    printf("%s", buffer);
}

void print_hex(int uppercase, int value) {
    char hexDigitsLower[] = "0123456789abcdef";
    char hexDigitsUpper[] = "0123456789ABCDEF";
    char *hexDigits = (uppercase) ? hexDigitsUpper : hexDigitsLower;

    char buffer[9]; // Assuming 32-bit integer, 8 hexadecimal digits + null terminator
    int i = 0;

    // Convert each nibble of the integer to hexadecimal
    for (int j = 7; j >= 0; j--) {
        buffer[j] = hexDigits[value & 0xF]; // Mask to get the least significant nibble
        value >>= 4; // Shift right by 4 bits to get the next nibble
    }
    buffer[8] = '\0'; // Null-terminate the string

    // Skip leading zeroes
    while (buffer[i] == '0' && i < 7) {
        i++;
    }

    // Print the hexadecimal digits
    for (; i < 8; i++) {
        putchar(buffer[i]);
    }
    putchar('\n');
}

void check_prefix(int next_char) {
    if (next_char == 'x' || next_char == 'X') {
        putchar('0');
        putchar(next_char);
    }
}



void my_printf(char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            char padding=' ';
            int width=0;
            if(*fmt=='0')
            {
                padding='0';
                fmt++;
            }

            if (isdigit(*fmt)) {
                if ( *fmt >= '1' && *fmt <= '9') 
                {
                    width=(*fmt-'0')+width*10;
                    fmt++;
                }
                if(width>0){
                switch (*fmt) {
                        case 'd':
                            if(padding==' ')
                                padding_d(' ', width, va_arg(ap, int));
                            else 
                                padding_d('0', width, va_arg(ap, int));
                            break;
                        case 'X':
                            if(padding == ' ')
                                padding_hexa_upper(' ', width, va_arg(ap, int));
                            else
                                padding_hexa_upper('0', width, va_arg(ap, int));
                            break;
                        case 'x':
                            if(padding == ' ')
                                padding_hexa_low(' ', width, va_arg(ap, int));
                            else 
                                padding_hexa_low('0', width, va_arg(ap, int));
                            break;
                        case 'b':
                            if(padding == ' ')
                                padding_binary(' ', width, va_arg(ap, int));
                            else 
                                padding_binary('0', width, va_arg(ap, int));
                            break;
                    }

                }
            }
              else {
                switch (*fmt++) {
                    case 's':
                        printf("%s\n", va_arg(ap, char *));
                        break;
                    case 'd':
                        printf("%d\n", va_arg(ap, int));
                        break;
                    case 'c':
                        printf("%c\n", (char)va_arg(ap, int));
                        break;
                    case 'b':
                        print_binary(va_arg(ap, int));
                        break;
        
                    case 'x':
                        check_prefix(*fmt); 
                        print_hex(0, va_arg(ap, int));
                        break;
                    case 'X':
                        check_prefix(*fmt); 
                        print_hex(1, va_arg(ap, int));
                        break;
                    
                }
            }
        } else {
            putchar(*fmt);
        }
        fmt++;
    }
    
    va_end(ap);
}

// Example usage of foo
int main() {
    my_printf("Character: %c\n", 'A');
    my_printf("Integer: %d\n", 1234);
    my_printf("String: %s\n", "Hello stringg");
    my_printf("Integer with space padding: %8d\n", 1234);
    my_printf("Integer with 0 padding: %08d\n", 1234);
    my_printf("Hex lowercase: %x\n", 0xa3b2c1);
    my_printf("Hex uppercase: %X\n", 0xa3b2c1);
    my_printf("Hex with space padding - lowercase: %8x\n", 0x2b1a);
    my_printf("Hex with space padding - uppercase: %8X\n", 0x2b1a);
    my_printf("Hex with 0 padding - lowercase: %08x\n", 0x1A3F7B9C);
    my_printf("Hex with 0 padding - uppercase: %08X\n", 0x1A3F7B9C);
    my_printf("Hex with 0x (lower): %xx", 0x3b2c1a);
    my_printf("Hex with 0X (upper): %xX", 0x2b1a);
    my_printf("Binary: %b\n", 21);
    my_printf("Binary with space padding: %8b", 21);
    my_printf("Binary with 0 padding: %08b\n", 21);

    return 0;
}