#include <unistd.h> // for write()
#include <stdio.h> // for printf() ~ to be deleted
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */
#include <stdint.h>

// Do we need to do width, precision, & length specifiers ??

void my_putchar(char c) {
  write(1, &c, 1);
}

int my_printf(char* format, ...) {
    int print_count = 0;
    va_list vl;
    va_start(vl,format);
    for (int i = 0; format[i] != 0; i++) {
        if (format[i] == '%') {
            i++;
            if (format[i] == '%') {
                my_putchar(format[i]);
                print_count++;
            }
            else if (format[i] == 'd' || format[i] == 'i' || format[i] == 'o' || format[i] == 'u' || format[i] == 'x' || format[i] == 'X') {
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
                if (format[i] == 'd' || format[i] == 'i' || format[i] == 'u') {
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
                else if (format[i] == 'x' || format[i] == 'X') {
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
                    // my_putchar('0');
                    // print_count++;
                    // my_putchar('x');
                    // print_count++;
                    for ( ; j >= 0; j--) {
                        my_putchar(hexdecnum[j]);
                        print_count++;
                    }
                }
                else if (format[i] == 'o') {
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
                    // my_putchar('0');
                    // print_count++;
                    // my_putchar('o');
                    // print_count++;
                    for ( ; j >= 0; j--) {
                        my_putchar(octdecnum[j]);
                        print_count++;
                    }
                }
            }
            else if (format[i] == 'f'|| format[i] == 'e' || format[i] == 'E' || format[i] == 'g' || format[i] == 'G') {
                // double (precision 6)
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

                uintptr_t x = (uintptr_t)val;

                char buf[2 + sizeof(x) * 2];
                size_t i;

                buf[0] = '0';
                buf[1] = 'x';
                for (i = 0; i < sizeof(x) * 2; i++) {
                    buf[i + 2] = "0123456789abcdef"[(x >> ((sizeof(x) * 2 - 1 - i) * 4)) & 0xf];
                }

                write(1, buf, sizeof(buf));
            }
        }
        else {
            my_putchar(format[i]);
            print_count++;
        }
    }
    va_end(vl);

    return print_count;
}


int main() {
    int s = 7;
    my_printf("hello%% %c%s %d %d %x %o %p\n", 'a', "Hi", 16087578, -1, 271, 271, &s);
    
    // int* ptr = &s;
    // char* str = (char*)ptr;
    printf("hello%% %c%s %d %d %x %o %p\n", 'a', "Hi", 16087578, -1, 271, 271, &s);
    return 0;
}