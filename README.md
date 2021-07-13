# my_printf

Functionalities

The my_printf() function mirrors the C library printf() function in most of it's
functionalities. It takes a string with the format of the output and a varying number 
of variables of different types to insert into the string. The supported types are 
decimal, octodecimal, unsigned decimal, hexadecimal, char, string, and pointer address.
In order to look at the variables to insert into the printed string, a % sign must be
inserted before the char letter that designates each type.


Description of Code

The code features a main my_printf() function that is the powerhouse of the print
function. The function supports a variable number of variables representing the 
varibales inserted into the string to be printed. It utilizes the #include <stdarg.h>
which allows for va_list, va_start, va_arg, va_end. These C library functions allows
for noen or many additional variables. The function loops through the format string
and prints each character, stopping at the % symbol and then uses many if statements
to find the variable type and properly print it. In order to print each character, 
number, etc. there is a helper function my_putchar that writes a charcter to the
standard output.


Compilation and Execution

This program uses a make file, which combines all .c files into one executable command.
In order to compile all files in one line, just type make into the command line and then
run the executable file as intended. Since the function does not take command line arguments
or any user input, you can adjust and test the pirnt function within the main function 
towards the bottom of the code.

Example below:
$> make
$> ./my_printf


Example of Print Function

Function call:
my_printf("String: %s\tChar: %c %c\td: %d %d\to: %o\tu: %u\tx: %x\tp: %p %p\n", "Hello", 'a', 74, 168, -1, 271, 42, 271, &s, ptr);

Output:
String: Hello   Char: a J       d: 168 -1       o: 417  u: 42   x: 10f  p: 0x7ffe8c516520 0x7ffe8c516520