#include <unistd.h> // for write()
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */
#include <stdint.h>

// helper function to write a character
void my_putchar(char c) {
  write(1, &c, 1);
}

// main printf function
int my_printf(char* format, ...) {
    int print_count = 0; // holds the number of characters that are printed to the screen
    va_list vl;
    va_start(vl,format);
    for (int i = 0; format[i] != 0; i++) { // loops through the format string to print characters
        if (format[i] == '%') { // if reach a specifier, see what to print
            i++;
            if (format[i] == '%') { // 
                my_putchar(format[i]);
                print_count++;
            }
            else if (format[i] == 'd'|| format[i] == 'o' || format[i] == 'u' || format[i] == 'x') {
                // The int (or appropriate variant) argument is converted to 
                // signed decimal (d). unsigned octal (o), unsigned decimal 
                // (u), unsigned hexadecimal (x).
                int val;
                val=va_arg(vl,int);
                int negative = 0;
                // special cases
                if (val == 0) { // val is zero
                    my_putchar(48);
                    print_count++;
                    continue;
                }
                else if (val < 0) { // val is negative
                    val *= -1;
                    negative = 1;
                }
                int temp = 0;
                if (format[i] == 'd' || format[i] == 'u') {
                    // need to reverse in order to print
                    while (val != 0) {
                        temp *= 10;
                        temp += val % 10;
                        val /= 10;
                    }
                    if (negative == 1 && format[i] != 'u') {
                        my_putchar('-');
                        print_count++;
                    }
                    while (temp != 0) {
                        my_putchar(48+(temp % 10));
                        print_count++;
                        temp /= 10;
                    }
                }
                else if (format[i] == 'x') {
                    // need to convert number from decimal to hexadecimal
                    char hexdecnum[100];
                    int j = 0;
                    while (val != 0) { 
                        temp = val % 16; 
                        if (temp < 10) { 
                            temp += 48; 
                        } 
                        else { 
                            temp += 87; 
                        } 
                        hexdecnum[j] = temp; 
                        j++;
                        val = val / 16; 
                    }
                    // print each digit in the number
                    for ( ; j >= 0; j--) {
                        my_putchar(hexdecnum[j]);
                        print_count++;
                    }
                }
                else if (format[i] == 'o') {
                    // need to convert number from decmal to octodecimal
                    char octdecnum[100];
                    int j = 0;
                    while (val != 0) { 
                        temp = val % 8; 
                        if (temp < 10) { 
                            temp += 48; 
                        } 
                        else { 
                            temp += 87; 
                        } 
                        octdecnum[j] = temp; 
                        j++;
                        val = val / 8; 
                    }
                    // print each digit in the number
                    for ( ; j >= 0; j--) {
                        my_putchar(octdecnum[j]);
                        print_count++;
                    }
                }
            }
            else if (format[i] == 'c') {
                // The int argument is converted to an unsigned char, and the 
                // resulting character is written.
                char val;
                val=va_arg(vl,int);
                my_putchar(val);
                print_count++;
            }
            else if (format[i] == 's') {
                // The char * argument is expected to be a pointer to an array 
                // of character type (pointer to a string). Characters from the 
                // array are written up to (but not including) a terminating NUL 
                // character.
                char* val;
                val=va_arg(vl,char*);
                for (int j = 0; val[j] != 0; j++) {
                    my_putchar(val[j]);
                    print_count++;
                }
            }
            else if (format[i] == 'p') {
                // The void * pointer argument is printed in hexadecimal.
                void* val;
                val=va_arg(vl,void*);

                // need to convert pointer to a type that holds the address
                uintptr_t x = (uintptr_t)val;

                // convert to hexadecimal
                int temp = 0;
                char hexdecnum[100];
                int j = 0;
                while (x != 0) { 
                    temp = x % 16; 
                    if (temp < 10) { 
                        temp += 48; 
                    } 
                    else { 
                        temp += 87; 
                    } 
                    hexdecnum[j] = temp; 
                    j++;
                    x = x / 16; 
                }
                // print the address
                my_putchar('0');
                print_count++;
                my_putchar('x');
                print_count++;
                for (j-- ; j >= 0; j--) {
                    my_putchar(hexdecnum[j]);
                    print_count++;
                }
            }
        }
        else {
            // if there is no specifer, then the character is simply printed normally
            my_putchar(format[i]);
            print_count++;
        }
    }
    va_end(vl);

    return print_count; // return the number of characters printed to the screen
}

// #include <stdio.h> // for printf()

// main to show example of printf function
int main() {
    // Example of my_printf() with each type printed
    int s = 7;
    int* ptr = &s;
    my_printf("String: %s\tChar: %c %c\td: %d %d\to: %o\tu: %u\tx: %x\tp: %p %p\n", "Hello", 'a', 74, 168, -1, 271, 42, 271, &s, ptr);
    // Compare to C library printf function
    // Need to uncomment include statement above to compare
    // printf("String: %s\tChar: %c %c\td: %d %d\to: %o\tu: %u\tx: %x\tp: %p %p\n", "Hello", 'a', 74, 168, -1, 271, 42, 271, &s, ptr);
    return 0;
}