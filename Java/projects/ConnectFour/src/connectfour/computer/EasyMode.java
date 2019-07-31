package connectfour.computer;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

import connectfour.board.Board;

public class EasyMode {
    public static int bestColumn(Board board) {
        int defense = searchForThrees(board);
        int goodStart = checkforHorizontal2(board);
        
        /**
         * If the methods returned anything other than -1, we'll want to drop a piece in that column.
         */
        int column = 0;
        if (defense > -1) {
            column = defense;
        } else if (goodStart > -1){
            column =  goodStart;
        } else {
            column =  (int) (Math.random() * 7);
        }
        
        /**
         * From here to the end of the method checks to make sure the column is not full, if it is full, it just randomly picks
         * new columns until it finds a free one, but if none are free it displays to the screen "Stalemate"
         */
        if (board.getBoard()[column][0] == null) {
            return column;
        } else {
            int freeColumn = (int) (Math.random() * 7);
            int[] columnArray = new int[7];
            while (board.getBoard()[freeColumn][0] != null) {
                freeColumn = (int) (Math.random() * 7);
                columnArray[freeColumn]++;
                int zeros = 0;
                for (int i = 0; i < columnArray.length; i++) {
                    if (columnArray[i] == 0) {
                        zeros++;
                    }
                }
                if (zeros == 0) {
                    JOptionPane.showMessageDialog(new JFrame(), "Stalemate");
                }
            }
            return freeColumn;
        }
    }

    /**
     * I found with playing against myself (may not be the best method) that it's nice near the beginning of a streak to have 2
     * horizontal pieces in a row. This method checks for that and returns the column to drop the piece in.
     */
    private static int checkforHorizontal2(Board board) {
        int inARow = 0;
        for (int i = 0; i < board.getBoard().length; i++) {
            for (int j = board.getBoard()[i].length - 1; j >= 0; j--) {
                /**
                 * Checks for potential Horizontal wins.
                 */
                if (board.getBoard()[i][j] != null) {
                    String check = board.getBoard()[i][j].getColor();
                    int count = i;
                    while (count < board.getBoard().length) {
                        if (board.getBoard()[count][j] != null && board.getBoard()[count][j].getColor().equals(check)) {
                            inARow++;
                        } else {
                            inARow = 0;
                        }
                        if (inARow >= 2) {
                            if (count + 1 >= board.getBoard().length) {
                                if (i - 1 >= 0 && board.getBoard()[i - 1][j] == null) {
                                    return i - 1;
                                }
                            } else {
                                if (board.getBoard()[count + 1][j] == null) {
                                    if (j == board.getBoard()[i].length - 1 || (j < board.getBoard()[i].length - 1 && board.getBoard()[count + 1][j + 1] != null)) {
                                        return count + 1;
                                    }
                                } else if (i - 1 >= 0 && board.getBoard()[i - 1][j] == null) {
                                    if (j == board.getBoard()[i].length- 1 || (j < board.getBoard()[i].length && board.getBoard()[i - 1][j + 1] != null)) {
                                        return i - 1;
                                    }
                                }
                            }
                        }
                        count++;
                    }
                }
            }
        }
        return -1;
    }

    /**
     * Checks for any streak of three and blocks it (or connects 4 if the streak is its own color)
     */
    private static int searchForThrees(Board board) {
        int inARow =0;
        for (int i = 0; i < board.getBoard().length; i++) {
            for (int j = board.getBoard()[i].length - 1; j >= 0; j--) {
                /**
                 * Checks for potential Vertical wins.
                 */
                if (board.getBoard()[i][j] != null) {
                    String check = board.getBoard()[i][j].getColor();
                    int count = j;
                    while (count >= 0) {
                        if (board.getBoard()[i][count] != null && board.getBoard()[i][count].getColor().equals(check)) {
                            inARow++;
                        } else {
                            inARow = 0;
                        }
                    
                        if (inARow >= 3) {
                            if (count - 1 >= 0 && board.getBoard()[i][count - 1] == null) {
                                return i;
                            }
                        }
                        count--;
                    }
                }
                inARow = 0;
                
                /**
                 * Checks for potential Horizontal wins.
                 */
                if (board.getBoard()[i][j] != null) {
                    String check = board.getBoard()[i][j].getColor();
                    int count = i;
                    while (count < board.getBoard().length) {
                        if (board.getBoard()[count][j] != null && board.getBoard()[count][j].getColor().equals(check)) {
                            inARow++;
                        } else {
                            inARow = 0;
                        }
                        if (inARow >= 3) {
                            if (count + 1 >= board.getBoard().length) {
                                if (i - 1 >= 0 && board.getBoard()[i - 1][j] == null) {
                                    return i - 1;
                                }
                            } else {
                                if (board.getBoard()[count + 1][j] == null) {
                                    if (j == board.getBoard()[i].length - 1 || (j < board.getBoard()[i].length - 1 && board.getBoard()[count + 1][j + 1] != null)) {
                                        return count + 1;
                                    }
                                } else if (i - 1 >= 0 && board.getBoard()[i - 1][j] == null) {
                                    if (j == board.getBoard()[i].length- 1 || (j < board.getBoard()[i].length && board.getBoard()[i - 1][j + 1] != null)) {
                                        return i - 1;
                                    }
                                }
                            }
                        }
                        count++;
                    }
                }
                inARow = 0;
                
                /**
                 * Checks for potential Diagonal wins.
                 */
                if (board.getBoard()[i][j] != null) {
                    String check = board.getBoard()[i][j].getColor();
                    int countI = i;
                    int countJ = j;
                    while (countI < board.getBoard().length && countJ >= 0) {
                        if (board.getBoard()[countI][countJ] != null && board.getBoard()[countI][countJ].getColor().equals(check)) {
                            inARow++;
                        } else {
                            inARow = 0;
                        }
                        if (inARow >= 3) {
                            if (countI + 1 >= board.getBoard().length || countJ - 1 < 0) {
                                if (i > 0 && j < board.getBoard()[i].length - 1) {
                                    if (board.getBoard()[i - 1][j + 1] == null) {
                                        return i - 1;
                                    }
                                }
                            } else {
                                if (board.getBoard()[countI + 1][countJ - 1] == null && board.getBoard()[countI + 1][countJ] != null) {
                                    return countI + 1;
                                }
                            }
                        }
                        countI++;
                        countJ--;
                    }
                    inARow = 0;
                    countI = i;
                    countJ = j;
                    while (countI >= 0 && countJ >= 0) {
                        if (board.getBoard()[countI][countJ] != null && board.getBoard()[countI][countJ].getColor().equals(check)) {
                            inARow++;
                        } else {
                            inARow = 0;
                        }
                        if (inARow >= 3) {
                            if (countI - 1 < 0 || countJ - 1 < 0) {
                                if (i + 1 < board.getBoard().length - 1 && j + 1 < board.getBoard()[i].length) {
                                    if (board.getBoard()[i + 1][j + 1] == null) {
                                        return i + 1;
                                    }
                                }
                            } else {
                                if (board.getBoard()[countI - 1][countJ - 1] == null && board.getBoard()[countI - 1][countJ] != null) {
                                    return countI - 1;
                                }
                            }
                        }
                        countI--;
                        countJ--;
                    }
                }
            }
        }
        
        return -1;
    }
}