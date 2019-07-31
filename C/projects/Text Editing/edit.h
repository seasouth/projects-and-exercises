/**
 * @file edit.h
 * @author Cole Southern (csouthe)
 *
 * This is a header file for edit.c, which receives specifications
 * from main in chop.c for editing a text representation. The edits
 * can be done on lines or columns and are specified by a starting
 * and ending index for lines or columns to remove.
 */

#include <string.h>

/**
 * Modifies the global text representation to remove lines in the given
 * range. Uses command line arguments to determine which and how many
 * lines and/or columns are to be removed.
 * @param int start starting index of line(s) to be removed
 * @param int end ending index of line(s) to be removed
 */
extern void removeLines(int start, int end);

/**
 * Removes characters in the range determined by the parameters on just
 * one line, which is determined by parameter lno.
 * @param int lno index of line to remove characters from
 * @param int start starting index of characters to be removed
 * @param int end ending index of characters to be removed
 */
extern void editLine(int lno, int start, int end);

/**
 * Uses the editLine() function (declared above) to remove the given range
 * of columns from all the lines of the text.
 * @param int start starting index, provided by editLine(), of characters
 * to be removed
 * @param int end ending index, provided by editLine(), of characters to
 * be removed
 */
extern void removeCols(int start, int end);
