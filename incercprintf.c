/*#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

// Function to calculate the number of digits in an integer
int count_digits(int num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}

// Function to print an integer with padding
void print_padded_int(int num, int width, char padding_char) {
    int num_digits = count_digits(num);
    if (num < 0) {
        putchar('-');
        num = -num;
    }
    for (int i = 0; i < width - num_digits; i++) {
        putchar(padding_char);
    }
    printf("%d", num);
}

// Function to print an integer in binary
void print_binary(int num) {
    if (num == 0) {
        putchar('0');
        return;
    }
    print_binary(num / 2);
    putchar('0' + num % 2);
}

// Custom printf function
int my_custom_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;
            if (*format == 'c') {
                char c = va_arg(args, int);
                putchar(c);
            } else if (*format == 'd') {
                int num = va_arg(args, int);
                printf("%d", num);
            } else if (*format == 's') {
                char *str = va_arg(args, char *);
                while (*str != '\0') {
                    putchar(*str);
                    str++;
                }
            } else if (isdigit(*format)) {
                int width = atoi(format);
                format++;
                char padding_char = ' ';
                //int width = atoi(format);
                int num = va_arg(args, int);
                if (*format == 'd') {
                    format++;
                    print_padded_int(num, width, padding_char);
                    padding_char = '0';
                }
                //int width = atoi(format);
                //int num = va_arg(args, int);
                //print_padded_int(num, width, padding_char);
            } else if (*format == 'x' || *format == 'X' || *format == 'b') {
                int uppercase = (*format == 'X') ? 1 : 0;
                int binary = (*format == 'b') ? 1 : 0;
                int padding = 0;
                char padding_char = ' ';
                format++;
                if (*format == 'p') {
                    format++;
                    if (*format == '0') {
                        format++;
                        padding_char = '0';
                    }
                    padding = atoi(format);
                    format++;
                }
                if (*format == 'X') {
                    putchar('0');
                    putchar(*format);
                } else if (*format == 'x') {
                    putchar('0');
                    putchar(*format);
                } else if (*format == 'b') {
                    // No prefix for binary
                }
                if (padding > 0) {
                    int num = va_arg(args, int);
                    if (binary) {
                        int num_digits = count_digits(num);
                        print_padded_int(num, padding + ((uppercase || *format == 'b') ? 0 : 2), padding_char);
                    } else {
                        print_padded_int(num, padding, padding_char);
                    }
                } else {
                    int num = va_arg(args, int);
                    if (binary) {
                        print_binary(num);
                    } else {
                        if (uppercase) {
                            printf("%X", num);
                        } else {
                            printf("%x", num);
                        }
                    }
                }
            }
        } else {
            putchar(*format);
        }
        format++;
    }
    va_end(args);
    return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void putchar_hexa_upper(unsigned decimal_number)
{
    char hexadecimal_num[32]; // Array to store hexadecimal digits
    int i = 0;                 // Counter for hexadecimal array

    if (decimal_number == 0)
    {
        putchar('0');
        putchar('\n');
        return;
    }

    while (decimal_number > 0)
    {
        int remainder = decimal_number % 16;
        if (remainder < 10)
        {
            hexadecimal_num[i] = remainder + '0';
        }
        else
        {
            switch (remainder)
            {
            case 10:
                hexadecimal_num[i] = 'A';
                break;
            case 11:
                hexadecimal_num[i] = 'B';
                break;
            case 12:
                hexadecimal_num[i] = 'C';
                break;
            case 13:
                hexadecimal_num[i] = 'D';
                break;
            case 14:
                hexadecimal_num[i] = 'E';
                break;
            case 15:
                hexadecimal_num[i] = 'F';
                break;
            }
        }
        decimal_number /= 16;
        i++;
    }

    for (int j = i - 1; j >= 0; j--)
    {
        putchar(hexadecimal_num[j]);
    }
    putchar('\n');
}

void putchar_n_times(char char_to_print, int n)
{
    for (int i = 0; i < n; i++)
    {
        putchar(char_to_print);
    }
}

void pd_or_0pd_hexa_uppercase_letters(char char_to_print, unsigned p, int number)
{
    int aux = number;
    int counter = 0;

    while (aux > 0)
    {
        aux = aux / 10;
        counter++;
    }

    int Char_not_to_print = p - counter;

    for (int i = 0; i <= Char_not_to_print; i++)
    {
        putchar(char_to_print);
    }

    putchar_hexa_upper(number);
}

int my_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int d;
    char c;
    char *s;
    int x;

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
            case 'd':
                d = va_arg(args, int);
                // printf("%d\n", d);
                // Instead of printf, using putchar
                // (Assuming d is a single-digit integer)
                putchar(d + '0');
                putchar('\n');
                break;
            case 's':
                s = va_arg(args, char *);
                // printf("%s\n", s);
                // Instead of printf, using putchar
                while (*s)
                {
                    putchar(*s++);
                }
                putchar('\n');
                break;
            case 'c':
                c = va_arg(args, int);
                // printf("%c\n", c);
                // Instead of printf, using putchar
                putchar(c);
                putchar('\n');
                break;
            case 'x':
                x = va_arg(args, unsigned int);
                // printf("%x\n", x);
                // Instead of printf, using putchar_hexa_upper
                putchar_hexa_upper(x);
                break;
            case 'X':
                pd_or_0pd_hexa_uppercase_letters('0', *(format + 1) - '0', va_arg(args, int));
                format++;
                break;
            case '0':
                switch (*(format + 1))
                {
                case 'd':
                    d = va_arg(args, int);
                    // printf("%0*d\n", (*(format + 2) - '0'), d);
                    // Instead of printf, using putchar_n_times and putchar
                    putchar_n_times('0', (*(format + 2) - '0'));
                    putchar(d + '0');
                    putchar('\n');
                    format += 2;
                    break;
                case 'x':
                    x = va_arg(args, unsigned int);
                    // printf("%0*x\n", (*(format + 2) - '0'), x);
                    // Instead of printf, using putchar_n_times and putchar_hexa_upper
                    putchar_n_times('0', (*(format + 2) - '0'));
                    putchar_hexa_upper(x);
                    putchar('\n');
                    format += 2;
                    break;
                case 'X':
                    pd_or_0pd_hexa_uppercase_letters('0', (*(format + 2) - '0'), va_arg(args, int));
                    format += 2;
                    break;
                default:
                    putchar(*format);
                    break;
                }
                break;
            default:
                putchar(*format);
                break;
            }
        }
        else
        {
            putchar(*format);
        }
        format++;
    }

    va_end(args);
    return 0;
}
int main() {
    my_printf("Testing my_printf function:\n");
    my_printf("Integer: %d\n", 123);
    my_printf("String: %s\n", "Hello, world!");
    my_printf("Character: %c\n", 'A');
    my_printf("Hexadecimal (lowercase): %x\n", 255);
    my_printf("Hexadecimal (uppercase): %X\n", 255);
    my_printf("Zero-padded integer: %0d\n", 5);
    my_printf("Zero-padded hexadecimal (lowercase): %0x\n", 10);
    my_printf("Zero-padded hexadecimal (uppercase): %0X\n", 10);
    return 0;
}

