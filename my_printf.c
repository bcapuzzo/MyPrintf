#include <unistd.h> // for write()
#include <stdio.h> // for printf() ~ to be deleted
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

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
            else if (format[i] == 'd' || format[i] == 'o' || format[i] == 'u' || format[i] == 'x') {
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
                while (val != 0) {
                    temp *= 10;
                    temp += val % 10;
                    val /= 10;
                }
                if (negative == 1) {
                    my_putchar('-');
                    print_count++;
                }
                while (temp != 0) {
                    my_putchar(48+(temp % 10));
                    print_count++;
                    temp /= 10;
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

                // void* val;
                // val=va_arg(vl,void*);
                // for (int j = 0; &val[j] != 0; j++) {
                //     my_putchar(&val[j]);
                //     print_count++;
                // }
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
    my_printf("hello%% %c%s %d %d\n", 'a', "Hi", 16087578, -1);
    return 0;
}




/* va_start example */
// #include <stdio.h>      /* printf */
// #include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

// void PrintFloats (int n, ...)
// {
//   int i;
//   double val;
//   printf ("Printing floats:");
//   va_list vl;
//   va_start(vl,n);
//   for (i=0;i<n;i++)
//   {
//     val=va_arg(vl,double);

//     printf (" [%.2f]",val);
//   }
//   va_end(vl);
//   printf ("\n");
// }

// int main ()
// {
//   PrintFloats (3,3.14159,2.71828,1.41421);
//   return 0;
// }
