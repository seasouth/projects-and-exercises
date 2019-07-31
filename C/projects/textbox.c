/**
  */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** Width of each line of text in the box. */
#define LINE_WIDTH 60

/** Symbol used to draw the border around the box. */
#define BORDER '*'

/**
  * Prints charcters from the given file until it reaches the Max line width of 60, and ignores
  * the remaining characters, or if there are less than 60 characters on the given line, it "pads"
  * the line with spaces to ensure the line has 60 characters.
  * @return bool indicating if there are more lines or if we have reached the end of the file
  */
bool paddedLine()
{
    int ch = getchar();
    int count = LINE_WIDTH;
    if (ch == EOF) {
        return false;
    }
    printf("%c", BORDER);
    while (ch != '\n' && count > 0) {
        putchar(ch);
        ch = getchar();
        count--;
        if (count == 0) {
            printf("%c\n", BORDER);
            while (ch != '\n' && ch != EOF) {
                ch = getchar();
            }
            return true;
        }
        if (ch == EOF) {
            printf("%c\n", BORDER);
            return false;
        }
    }
    if (count != 0) {
        while (count > 0) {
            printf(" ");
            count--;
        }
    }
    printf("%c\n", BORDER);
    return true;
}

/**
  * Prints out 62 lines of characters specified by the BORDER variable.
  * @param ch character to make up the border specified by main, in this 
  * case the BORDER variable.
  * @param count limiter for the number of characters being printed, in this
  * case not to surpass the LINE_WIDTH variable.
  */
void lineOfChars( char ch, int count )
{
    printf("%c", ch);
    for (int i = count; i > 0; i--) {
        printf("%c", ch);
    }
    printf("%c\n", ch);
}

/**
  * Program starting point. Calls lineOfChars, and then paddedLine until it returns
  * false, and then lineOfChars again. Created a box around text.
  * @return 0 to terminate the function call
  */
int main()
{
    lineOfChars(BORDER, LINE_WIDTH);
    while (paddedLine());
    lineOfChars(BORDER, LINE_WIDTH);
    return 0;
}
