#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int print_int(int value, int padding, char pad_char, int prefix);
int print_string(const char* str);
int print_hex(int value, int padding, char pad_char, int upper, int prefix);
int print_binary(int value, int padding, char pad_char);

int my_custom_printf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  int num_written = 0;

  while (*format) {
    if (*format != '%') {
      putchar(*format);
      format++;
      num_written++;
    } else {
      format++;
      int padding = 0;
      char pad_char = ' ';

      // Check for padding specifier
      if (*format >= '0' && *format <= '9') {
        while (*format >= '0' && *format <= '9') {
          padding *= 10;
          padding += *format - '0';
          format++;
        }
      }

      // Check for zero padding
      if (*format == '0') {
        pad_char = '0';
        format++;
      }

      switch (*format) {
        case 'c':
          putchar(va_arg(args, int));
          num_written++;
          break;
        case 'd':
          num_written += print_int(va_arg(args, int), padding, pad_char, 0);
          break;
        case 's':
          num_written += print_string(va_arg(args, char*));
          break;
        case 'x':
        case 'X': {
          int upper = (*format == 'X');
          num_written += print_hex(va_arg(args, int), padding, pad_char, upper, (*format == 'x' || *format == 'X'));
          break;
        }
        case 'b':
          num_written += print_binary(va_arg(args, int), padding, pad_char);
          break;
        case 'p':
          format++; // Skip 'p'
          switch (*format) {
            case 'd':
              num_written += print_int(va_arg(args, int), padding, pad_char, 0);
              break;
            case 'x':
            case 'X': {
              int upper = (*format == 'X');
              num_written += print_hex(va_arg(args, int), padding, pad_char, upper, (*format == 'x' || *format == 'X'));
              break;
            }
            case 'b':
              num_written += print_binary(va_arg(args, int), padding, pad_char);
              break;
          }
          break;
        default:
          putchar(*format);
          num_written++;
      }
      format++;
    }
  }
  va_end(args);
  return num_written;
}

// Helper functions for printing different data types
int print_int(int value, int padding, char pad_char, int prefix) {
  int num_digits = 0;
  int temp = value;
  if (temp < 0) {
    putchar('-');
    temp = -temp;
    num_digits++;
  }
  while (temp > 0) {
    temp /= 10;
    num_digits++;
  }
  int total_print_len = (prefix ? 2 : 0) + (padding > num_digits ? padding : num_digits);
  for (int i = 0; i < total_print_len - num_digits; i++) {
    putchar(pad_char);
  }
  if (prefix) {
    putchar('0');
    putchar('x');
  }
  for (int i = num_digits - 1; i >= 0; i--) {
    putchar((value / (int)(pow(10, i))) % 10 + '0');
  }
  return total_print_len;
}

int print_string(const char* str) {
  int num_written = 0;
  while (*str) {
    putchar(*str);
    str++;
    num_written++;
  }
  return num_written;
}

int print_hex(int value, int padding, char pad_char, int upper, int prefix) {
  static const char hex_digits_lower[] = "0123456789abcdef";
  static const char hex_digits_upper[] = "0123456789ABCDEF";
  const char* digits = upper ? hex_digits_upper : hex_digits_lower;

  int num_digits = 0;
  unsigned int temp = (unsigned int)value; // Convert to unsigned for handling negative values
  if (temp == 0) {
    num_digits = 1;
  }
  while (temp > 0) {
    temp /= 16;
    num_digits++;
  }

  int total_print_len = (prefix ? 2 : 0) + (padding > num_digits ? padding : num_digits);
  for (int i = 0; i < total_print_len - num_digits; i++) {
    putchar(pad_char);
  }
  if (prefix) {
    putchar('0');
    if (upper) {
      putchar('X');
    } else {
      putchar('x');
    }
  }
  for(int i = num_digits - 1; i >= 0; i--) {
    putchar(digits[(value >> (i * 4)) & 0xF]);
  }
  return total_print_len;
}
int main() {
  int num = 1234;
  char *str = "Hello, world!";

  // Basic printing
  my_custom_printf("This is a string\n");
  my_custom_printf("An integer: %d\n", num);
  my_custom_printf("A string with pointer: %s\n", str);

  // Printing with padding
  my_custom_printf("Integer with padding: %10d\n", num);
  my_custom_printf("Integer with zero padding: %08d\n", num);

  // Printing Hexadecimal
  my_custom_printf("Hex (lowercase): %x\n", num);
  my_custom_printf("Hex (uppercase) with padding: %08X\n", num);
  my_custom_printf("Hex (lowercase) with prefix: %#x\n", num);

  // Printing Binary
  my_custom_printf("Binary: %b\n", num);
  my_custom_printf("Binary with padding: %10b\n", num);

  // Printing with custom format specifiers (%pd, %px, etc.)
  my_custom_printf("Integer with decimal padding: %5d\n", num);
  my_custom_printf("Integer with hex padding (lowercase): %7x\n", num);
  my_custom_printf("Integer with hex padding (uppercase) with prefix: %#06X\n", num);

  return 0;
}
