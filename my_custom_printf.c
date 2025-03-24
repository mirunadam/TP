#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void hexa_upper(unsigned decimal_number)
{
    char hexadecimal_num[32]; // Array to store hexadecimal digits
    int i = 0;                 // Counter for hexadecimal array

    if (decimal_number == 0)
    {
        putchar('0');
        putchar('\n');
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

    for (int i = 0; i <=Char_not_to_print; i++)
    {
        putchar(char_to_print);
    }

   hexa_upper(number);
    
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
                printf("%d\n", va_arg(args, int)); 
                break;
            case 's':
                printf("%s\n", va_arg(args, char *)); 
                break;
            case 'c':
                printf("%c\n", va_arg(args, int)); 
                break;
            case 'x':
                printf("%x\n", va_arg(args, unsigned int));
                break;
            case 'X':
                pd_or_0pd_hexa_uppercase_letters('0', *(format + 1) - '0', va_arg(args, int));
                format++; 
                break;
            case '0':
                switch (*(format + 1)){
                    case 'd':
                        printf("%0*d\n", (*(format + 2) - '0'), va_arg(args, int)); 
                        format += 2; 
                        break;
                    case 'x':
                        printf("%0*x\n", (*(format + 2) - '0'), va_arg(args, unsigned int)); 
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
            case 'p':

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


int main()
{
    //my_printf("Testing my_printf: %d, %s, %c, %x, %X, %0d, %0x, %0X\n", 42, "Hello", 'A', 255, 255, 42, 255, 255);
   /* my_printf("%x\n", 255);
    my_printf("%X\n", 255);
    my_printf("%0d\n", 42);
    my_printf("%0x\n", 255);
    my_printf("%0X\n", 255);*/
    my_printf("%c\n", 'A');
    my_printf("%d\n", 123);
    my_printf("%s\n", "Hello, World!");
    my_printf("%pd\n", 450);
    my_printf("%0pd\n", 450);
    my_printf("%x\n", 450);
    my_printf("%px\n", 450);
    my_printf("%0px\n", 450);
    my_printf("%X\n", 450);
    my_printf("%pX\n", 450);
    my_printf("%0pX\n", 450);
    my_printf("%08xx\n", 450);
    my_printf("%08xX\n", 450);
    my_printf("%b\n", 451);
    my_printf("%pb\n", 451);
    my_printf("%0pb\n", 451);
    return 0;
}
