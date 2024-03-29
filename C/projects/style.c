/**
    @file stylecorrected.c
    @author Cole Southern (csouthe)

    This program generates a paragraph of a given number and length of lines with random words, and counts the
    words generated by the program.
*/

#include <stdio.h>
#include <stdlib.h>

/** Length of each line. */
#define LINE_LENGTH 72
/** Number of lines in the paragraph. */
#define NUMBER_OF_LINES 10
/** Defines the bounds for the random generator, ensuring it will be a letter. */
#define GENERATE_RANDOM_LETTER 97
/** Number of letters in the alphabet. */
#define NUMBER_OF_LETTERS 26

/**
    Takes in the length of a word as an int as a parameter and uses it to construct a random word with the given length.
    @param x represents the length of the word to be randomly generated
*/
void printWord( int x )
{
    for ( int i = 0; i < x; i++ ) {
            // Print a random lower-case letter.
            printf( "%c", GENERATE_RANDOM_LETTER + rand() % NUMBER_OF_LETTERS );
    }
}

/**
    Constructs a line of randomly generated words. Line has a fixed length.
    @return count representing the number of words in the line.
*/
int printLine()
{
    int count = 0, pos = 0, space = 0;
    int len = 1 + rand() % NUMBER_OF_LINES;
    // Print a line of words up to a limited length.
    while ( pos + len + space < LINE_LENGTH ) {
        if ( space > 0 ) {
            printf( " " );
        }
        printWord( len );
        pos += len + space;
        len = 1 + rand() % NUMBER_OF_LINES;
        space = 1;
        count += 1;
    }
    printf( "\n" );
    return count;
}

/**
    Prints the paragraph line by line, by calling the printLine method, until it reaches the number of lines, which is passed in as a parameter.
    @param n integer representing number of lines
    @return total integer representing total number of words in the paragraph
*/
int printParagraph( int n )
{
    int total = 0;
    for ( int i = 0; i < n; i++ ) {
        total += printLine();
    }
    return total;
}
/**
    Program starting point, calls the printParagraph funtion which in turn calls printLine, which in turn calls printWord.
	@return 0 to terminate the function call.
*/
int main()
{
    int w = printParagraph(NUMBER_OF_LINES);
    printf("Words: %d\n",w);
    return 0;
}