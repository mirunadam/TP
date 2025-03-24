//man va_arg
//stdarg.h
// ... e simbolul elypsis
//only with putchar


//innverted index compression
//giulio ermanno, rossano venturini
//TSC time series database (INFLUxDB)
//compression algoritm
//64 bits(8 bytes) unsigned value
//#include <stdint.h>  
//for uint_t

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void change_to_hexadecimal_uppercase_letters(unsigned decimal_number)
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

    change_to_hexadecimal_uppercase_letters(number);
}



void foo(char *fmt, ...)   /* '...' is C syntax for a variadic function */
{
    va_list ap;
    int d;
    char c;
    char *s;
    int x;
    va_start(ap, fmt);
    while (*fmt)
        if(isdigit(*fmt++)){
            if(*fmt++ == '0'){
                
            }

        }
        else
        switch (*fmt++) {
            case 's':              /* string */
                s = va_arg(ap, char *);
                printf("string %s\n", s);
                break;
            case 'd':              /* int */
                d = va_arg(ap, int);
                printf("int %d\n", d);
                break;
            case 'c':              /* char */
                   /* need a cast here since va_arg only
                      takes fully promoted types */
                c = (char) va_arg(ap, int);
                printf("char %c\n", c);
                break;
            case 'x':
                x = va_arg(ap, int);
                printf("int in hex %x\n", x);
            case '0':
                {
                int number;
                int p = *(fmt++) - '0'; // Get width from format string
                char if_x_ord_or_b_orX = *fmt; // Read the specifier character
                if (if_x_ord_or_b_orX == 'd')   {
                    printf("int_0:");
                    number = va_arg(ap, int); // Get the integer argument
                    pd_or_0pd('0', p, number); // Pad with zeros
                    printf("\n");
                }
                else if (if_x_ord_or_b_orX == 'b')
                {
                    printf("binary_0:");
                    number = va_arg(ap, int); // Get the integer argument
                    pd_or_0pd_binary('0', p, number); // Pad with zeros
                    printf("\n");
                }
                else if (if_x_ord_or_b_orX == 'X')
                {
                    printf("hexa_upper__0:");
                    number = va_arg(ap, int); // Get the integer argument
                    pd_or_0pd_hexa_uppercase_letters('0', p, number); // Pad with zeros
                    printf("\n");
            }
            else if (if_x_ord_or_b_orX == 'x')
            {
                printf("hexa_lower_0:");
                number = va_arg(ap, int); // Get the integer argument
                pd_or_0pd_hexa_lowercase_letters('0', p, number);
                printf("\n");
            }
            fmt++;
            break;
        }
        }
           va_end(ap);
}

int my_printf(const char *format, ...){

}

int main(){

    return 0;
}
