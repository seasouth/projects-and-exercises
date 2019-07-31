/**
 * @file edit.c
 * @author Cole Southern (csouthe)
 *
 * This program receives specifications from main in chop.c for
 * editing a text representation. The edits can be done on lines
 * or columns and are specified by a starting and ending index for
 * lines or columns to remove.
 */

#include "edit.h"
#include "text.h"

/**
 * Modifies the global text representation to remove lines in the given
 * range. Uses command line arguments to determine which and how many
 * lines and/or columns are to be removed.
 * @param int start starting index of line(s) to be removed
 * @param int end ending index of line(s) to be removed
 */
void removeLines(int start, int end)
{
    for (int i = 0; i < lines; i++) {
        if (i == start - 1) {
            int count = end - start + 1;
            while (count >= 0) {
                strcpy(text[i], text[i + (end - start + 1)]);
                i++;
                count--;
            }
        }
        if (i > start - 1) {
            strcpy(text[i], text[i + (end - start + 1)]);
        }
    }
}

/**
 * Removes characters in the range determined by the parameters on just
 * one line, which is determined by parameter lno.
 * @param int lno index of line to remove characters from
 * @param int start starting index of characters to be removed
 * @param int end ending index of characters to be removed
 */
void editLine(int lno, int start, int end)
{
    for (int i = 0; i < strlen(text[lno]); i++) {
        int tend = end;
        if (end > strlen(text[lno])) {
            tend = strlen(text[lno]) - 1;
        }
        if (i == start - 1) {
            int count = tend - start + 1;
            while (count >= 0) {
                text[lno][i] = text[lno][i + (tend - start + 1)];
                i++;
                count--;
            }
        }
        if (i > start - 1) {
            text[lno][i] = text[lno][i + (tend - start + 1)];
        }
    }
}

/**
 * Uses the editLine() function (declared above) to remove the given range
 * of columns from all the lines of the text.
 * @param int start starting index, provided by editLine(), of characters
 * to be removed
 * @param int end ending index, provided by editLine(), of characters to
 * be removed
 */
void removeCols(int start, int end)
{
    for (int i = 0; i < lines; i++) {
        editLine(i, start, end);
    }
}
