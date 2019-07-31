package connectfour.board;

import connectfour.color.Piece;

public class Board {
    private Piece[][] board;
    
    public Board() {
        this.board = new Piece[7][6];
    }
    
    public Piece[][] getBoard() {
        return this.board;
    }
    
    public String addPiece(int row) {
        if (row < 0 || row > 6) {
            throw new IndexOutOfBoundsException();
        }
        for (int i = board[row].length - 1; i >= 0; i--) {
            if (board[row][i] == null) {
                board[row][i] = new Piece();
                return isWon();
            }
        }
        return null;
    }

    /*
     * Returns null is there's no winner, and the Color of the winner if there is one
     */
    public String isWon() {
        int inARow = 0;
        for (int i = 0; i < board.length; i++) {
            for (int j = board[i].length - 1; j >= 0; j--) {
                /**
                 * Checks for Vertical wins.
                 */
                if (board[i][j] != null) {
                    String check = board[i][j].getColor();
                    int count = j;
                    while (count >= 0) {
                        if (board[i][count] != null && board[i][count].getColor().equals(check)) {
                            inARow++;
                        } else {
                            inARow = 0;
                        }
                    
                        if (inARow >= 4) {
                            return check + " Wins!";
                        }
                        count--;
                    }
                }
                inARow = 0;
                
                /**
                 * Checks for Horizontal wins.
                 */
                if (board[i][j] != null) {
                    String check = board[i][j].getColor();
                    int count = i;
                    while (count < board.length) {
                        if (board[count][j] != null && board[count][j].getColor().equals(check)) {
                            inARow++;
                        } else {
                            inARow = 0;
                        }
                        if (inARow >= 4) {
                            return check + " Wins!";
                        }
                        count++;
                    }
                }
                inARow = 0;
                
                /**
                 * Checks for Diagonal wins.
                 */
                if (board[i][j] != null) {
                    String check = board[i][j].getColor();
                    int countI = i;
                    int countJ = j;
                    while (countI < board.length && countJ >= 0) {
                        if (board[countI][countJ] != null && board[countI][countJ].getColor().equals(check)) {
                            inARow++;
                        } else {
                            inARow = 0;
                        }
                        if (inARow >= 4) {
                            return check + " Wins!";
                        }
                        countI++;
                        countJ--;
                    }
                    inARow = 0; 
                    countI = i;
                    countJ = j;
                    while (countI >= 0 && countJ >= 0) {
                        if (board[countI][countJ] != null && board[countI][countJ].getColor().equals(check)) {
                            inARow++;
                        } else {
                            inARow = 0;
                        }
                        if (inARow >= 4) {
                            return check + " Wins!";
                        }
                        countI--;
                        countJ--;
                    }
                }
                inARow = 0;
            }
        }
        return null;
    }
}
