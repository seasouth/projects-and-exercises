#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void readGrid( int rows, int cols, int grid[ rows ][ cols ] )
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int element;
			scanf("%d", &element);
			grid[i][j] = element;
        }
    }
}

// Add parameters to to pass a variable-sized array to the following
// function.  It's the same as the previous function, but I want you
// to get a chance to type it in yourself.
void reportMaxima(int rows, int cols, int grid[rows][cols])
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 && j == 0) {
                if (grid[i][j] > grid[i + 1][j] && grid[i][j] > grid[i + 1][j + 1]
                        && grid[i][j] > grid[i][j + 1]) {
                    printf("%d %d\n", i, j);
                }
            } else if (i == 0 && j == cols - 1) {
                if (grid[i][j] > grid[i + 1][j] && grid[i][j] > grid[i + 1][j -1]
                        && grid[i][j] > grid[i][j - 1]) {
                    printf("%d %d\n", i, j);
                }
            } else if (i == rows - 1 && j == 0) {
                if (grid[i][j] > grid[i - 1][j] && grid[i][j] > grid[i - 1][j + 1]
                        && grid[i][j] > grid[i][j + 1]) {
                    printf("%d %d\n", i, j);
                }
            } else if (i == rows - 1 && j == cols - 1) {
                if (grid[i][j] > grid[i - 1][j] && grid[i][j] > grid[i - 1][j - 1]
                        && grid[i][j] > grid[i][j - 1]) {
                    printf("%d %d\n", i, j);
                }
            } else if (i == 0) {
                if (grid[i][j] > grid[i][j - 1] && grid[i][j] > grid[i][j + 1]
                        && grid[i][j] > grid[i + 1][j - 1] && grid[i][j] > grid[i + 1][j]
                        && grid[i][j] > grid[i + 1][j + 1]) {
                    printf("%d %d\n", i, j);
                }
            } else if (i == rows - 1) {
                if (grid[i][j] > grid[i][j - 1] && grid[i][j] > grid[i][j + 1]
                        && grid[i][j] > grid[i - 1][j - 1] && grid[i][j] > grid[i - 1][j]
                        && grid[i][j] > grid[i - 1][j + 1]) {
                    printf("%d %d\n", i, j);
                }
            } else if (j == 0) {
                if (grid[i][j] > grid[i - 1][j] && grid[i][j] > grid[i - 1][j + 1]
                        && grid[i][j] > grid[i][j + 1] && grid[i][j] > grid[i + 1][j]
                        && grid[i][j] > grid[i + 1][j + 1]) {
                    printf("%d %d\n", i, j);
                }
            } else if (j == cols -1) {
                if (grid[i][j] > grid[i - 1][j - 1] && grid[i][j] > grid[i - 1][j]
                        && grid[i][j] > grid[i][j - 1] && grid[i][j] > grid[i + 1][j - 1]
                        && grid[i][j] > grid[i + 1][j]) {
                    printf("%d %d\n", i, j);
                }
            } else {
                if (grid[i][j] > grid[i - 1][j - 1] && grid[i][j] > grid[i - 1][j] 
                        && grid[i][j] > grid[i - 1][j + 1] && grid[i][j] > grid[i][j - 1]
                        && grid[i][j] > grid[i][j + 1] && grid[i][j] > grid[i + 1][j - 1]
                        && grid[i][j] > grid[i + 1][j] && grid[i][j] > grid[i + 1][j + 1]) {
                    printf("%d %d\n", i, j);
                }
            }
        }
    }
}

int main()
{
  // Add code to read in the grid size from standard input.
  int rows = 0;
  int columns = 0;
  scanf("%d%d", &rows, &columns);

  // Declare a variable-sized array to hold the grid.
  int grid[rows][columns];

  // Call readGrid() to populate the array.
  readGrid(rows, columns, grid);
  
  // Call reportMaxima() to print out all local maxima.
  reportMaxima(rows, columns, grid);
  
  return EXIT_SUCCESS;
}
