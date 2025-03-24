#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

void print_number(unsigned int number, int base, bool convert_to_uppercase) 
{
    char digits[] = "0123456789abcdef0123456789ABCDEF";
    char buffer[33];
    int buffer_index = 32;

    buffer[buffer_index] = '\0';

    do 
    {
        if (convert_to_uppercase) 
        {
            buffer[--buffer_index] = digits[number % base + 16];
        } 
        else 
        {
            buffer[--buffer_index] = digits[number % base];
        }

        number /= base;
    } 
    while (number != 0);

    printf("%s", &buffer[buffer_index]);
}

void print_padding(int width, char padding_character) 
{
    for (int i = 0; i < width; i++) 
    {
        putchar(padding_character);
    }
}

int calculate_padding(unsigned int number, int base, int desired_width, bool add_prefix) 
{
    int number_of_digits = 1;
    while (number /= base) 
    {
        number_of_digits++;
    }

    if (add_prefix && base == 16) 
    {
        number_of_digits += 2; // For "0x" or "0X"
    }

    if (desired_width > number_of_digits) 
    {
        return desired_width - number_of_digits;
    } 
    else 
    {
        return 0;
    }
}

int custom_printf_function(const char *format_string, ...) 
{
    va_list args;
    va_start(args, format_string);

    bool convert_to_uppercase = false;
    bool include_prefix = false;
    char padding_character = ' ';
    int field_width = 0;
    int padding_size = 0;

    while (*format_string) 
    {
        if (*format_string == '%') 
        {
            format_string++; // Skip '%'

            if (*format_string == '0') 
            {
                padding_character = '0';
                format_string++;
            }

            field_width = 0;
            while (*format_string >= '0' && *format_string <= '9') 
            {
                field_width = field_width * 10 + (*format_string - '0');
                format_string++;
            }

            if (*format_string == 'X') 
            {
                convert_to_uppercase = true;
            } 
            else if (*format_string == 'x') 
            {
                convert_to_uppercase = false;
            }

            if ((*format_string == 'x' || *format_string == 'X') && (*(format_string + 1) == 'x' || *(format_string + 1) == 'X')) 
            {
                include_prefix = true;
                format_string++; // Skip the next 'x' or 'X'
            } 
            else 
            {
                include_prefix = false;
            }

            switch (*format_string) 
            {
                case 'c':
                {
                    putchar((char)va_arg(args, int));
                    break;
                }
                case 'd':
                {
                    int number = va_arg(args, int);
                    if (number < 0) 
                    {
                        putchar('-');
                        number = -number;
                        field_width--;
                    }
                    padding_size = calculate_padding(number, 10, field_width, false);
                    print_padding(padding_size, padding_character);
                    print_number(number, 10, false);
                    break;
                }
                case 's':
                {
                    printf("%s", va_arg(args, char *));
                    break;
                }
                case 'x':
                case 'X':
                {
                    unsigned int number = va_arg(args, unsigned int);
                    padding_size = calculate_padding(number, 16, field_width - (include_prefix ? 2 : 0), false);
                    print_padding(padding_size, padding_character);

                    if (include_prefix) 
                    {
                        printf(convert_to_uppercase ? "0X" : "0x");
                    }

                    print_number(number, 16, convert_to_uppercase);
                    break;
                }
                case 'b':
                {
                    unsigned int number = va_arg(args, unsigned int);
                    padding_size = calculate_padding(number, 2, field_width, false);
                    print_padding(padding_size, padding_character);
                    print_number(number, 2, false);
                    break;
                }
                default:
                {
                    putchar('%');
                    if (*format_string) 
                    {
                        putchar(*format_string);
                    }
                    break;
                }
            }
        } 
        else 
        {
            putchar(*format_string);
        }
        format_string++;
    }

    va_end(args);
    return 0;
}

int main() 
{
    custom_printf_function("Displaying Character: %c\n", 'A');
    custom_printf_function("Showing Decimal: %d\n", 54321);
    custom_printf_function("Printing String: %s\n", "World, Hello!");
    custom_printf_function("Lowercase Hex: %x\n", 0x3c2b1a);
    custom_printf_function("Uppercase Hex: %X\n", 0x3c2b1a);
    custom_printf_function("Hex with Prefix (lower): %xx\n", 0x2b1a);
    custom_printf_function("Hex with Prefix (upper): %xX\n", 0x2b1a);
    custom_printf_function("Binary Representation: %b\n", 21);
    custom_printf_function("Decimal with Space Padding: %8d\n", 321);
    custom_printf_function("Decimal with Zero Padding: %08d\n", 321);
    custom_printf_function("Hex with Zero Padding (lower): %08x\n", 0x2b1a);
    custom_printf_function("Hex with Zero Padding (upper): %08X\n", 0x2b1a);
    custom_printf_function("Binary with Space Padding: %10b\n", 12);
    custom_printf_function("Binary with Zero Padding: %010b\n", 12);

    return 0;
}