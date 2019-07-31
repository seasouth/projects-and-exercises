package connectfour.ui;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JPanel;
import javax.swing.Timer;
import javax.swing.border.TitledBorder;

import connectfour.board.Board;
import connectfour.color.Piece;

public class Animation extends JPanel implements ActionListener {
    /**
     * 
     */
    private static final long serialVersionUID = 1L;
    int currentRow = 0;
    int row;
    static Timer timer;
    JPanel gameGrid = ConnectFourGUI.gameGrid;
    Animation(ConnectFourGUI gui, Board board, int row) {
        this.row = row;
        timer = new Timer(1000, this);
        main(null);
    }
    
    public static void main(String[] args) {
        timer.start();
    }
    
    @Override
    public void actionPerformed(ActionEvent e) {
        if (currentRow == 0) {
            ConnectFourGUI.board.getBoard()[row][currentRow] = new Piece(Piece.colorNum);
        } else {
            ConnectFourGUI.board.getBoard()[row][currentRow - 1] = null;
            ConnectFourGUI.board.getBoard()[row][currentRow] = new Piece(Piece.colorNum);
        }
    }
    
}
