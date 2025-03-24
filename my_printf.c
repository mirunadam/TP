//FINAL
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void padding_d(char padding_char, int width, int number) {
    char buffer[20]; 
    int printed_chars = snprintf(buffer, sizeof(buffer), "%d", number);
    int padding = width - printed_chars;
    if (padding > 0) {
        for (int i = 0; i < padding; i++) {
            putchar(padding_char);
        }
    }
    printf("%s", buffer);
}

void padding_hexa_low(char padding_char, int width, int number) {
    char buffer[20]; 
    int printed_chars = snprintf(buffer, sizeof(buffer), "%x", number); //convert to hexadecimal string
    int padding = width - printed_chars;
    if (padding > 0) {
        for (int i = 0; i < padding; i++) {
            putchar(padding_char);
        }
    }
    printf("%s", buffer);
}

void padding_hexa_upper(char padding_char, int width, int number) {
    char buffer[20]; 
    int printed_chars = snprintf(buffer, sizeof(buffer), "%X", number); //convert to hexadecimal string
    int padding = width - printed_chars;
    if (padding > 0) {
        for (int i = 0; i < padding; i++) {
            putchar(padding_char);
        }
    }
    printf("%s", buffer);
}

void print_hex(int uppercase, int value) {
    char hexLower[] = "0123456789abcdef";
    char hexUpper[] = "0123456789ABCDEF";
    char *hexDigits = (uppercase) ? hexUpper : hexLower;

    char buffer[9]; // 8 hexadecimal digits + null terminator
    int i = 0;

    for (int j = 7; j >= 0; j--) { // convert each nibble of the integer to hexadecimal
        buffer[j] = hexDigits[value & 0xF]; // mask to get the least significant nibble
        value >>= 4; // shift right by 4 bits to get the next nibble
    }
    buffer[8] = '\0'; 

    while (buffer[i] == '0' && i < 7) { // akip leading zeroes
        i++;
    }

    for (i=0; i < 8; i++) {
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
        } 
        else {
            putchar(*fmt);
        }
        fmt++;
    }
    va_end(ap);
}

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
    my_printf("Hex with 0x: %xx", 0x3b2c1a);
    my_printf("Hex with 0X: %xX", 0x3b2c1a);
    my_printf("Binary: %b\n", 21);
    my_printf("Binary with space padding: %8b", 21);
    my_printf("Binary with 0 padding: %08b\n", 21);

    return 0;
}
//gcc -Wall -o my_printf my_printf.c