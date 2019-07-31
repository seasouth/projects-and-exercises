package connectfour.ui;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.Timer;

import connectfour.board.Board;
import connectfour.color.Piece;
import connectfour.computer.EasyMode;
import connectfour.computer.HardMode;
import connectfour.computer.MediumMode;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.GridLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;


@SuppressWarnings("serial")
public class ConnectFourGUI extends JFrame {
    static JPanel gameGrid = new JPanel();
    static CirclePanel[][] panel = new CirclePanel[7][6];
    static Board board = new Board();
    static Container c;

    static int comp;
    int turn = 1;
    
    /**
     * Sets up the gui for the actual play board.
     * @param choice determines if computer was chose and what level of difficulty
     */
    public ConnectFourGUI(int choice) {
        if (choice == 0) {
            comp = 0;
        } else if (choice == 1) {
            comp = 1;
        } else if (choice == 2) {
            comp = 2;
        } else if (choice == 3) {
            comp = 3;
        }
        
        c = getContentPane();
        this.setTitle("Connect Four!");
        this.setSize(600, 600);
        this.setLocation(350, 30);
        this.setVisible(true);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        c.setLayout(new BorderLayout());
        
        JPanel topPanel = new JPanel();
        
        topPanel.setLayout(new GridLayout(3, 7));
        
        c.add(topPanel, BorderLayout.NORTH);
        c.add(gameGrid, BorderLayout.CENTER);
        
        JPanel one = new JPanel();
        JPanel two = new JPanel();
        JPanel three = new JPanel();
        JPanel four = new JPanel();
        JPanel five = new JPanel();
        JPanel six = new JPanel();
        JPanel seven = new JPanel();
        
        topPanel.add(one);
        topPanel.add(two);
        topPanel.add(three);
        topPanel.add(four);
        topPanel.add(five);
        topPanel.add(six);
        topPanel.add(seven);
        
        gameBoard();
        
    }
    
    /**
     * This is where most of the front-end work gets done, the panels are added and drawn and mouse listeners are added so it can highlight the column
     * the cursor is on and register the choice with a mouse click.
     */
    public static void gameBoard() {
        gameGrid.removeAll();
        gameGrid.setLayout(new GridLayout(6, 7));
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                final int jj = j;
                if (board.getBoard()[j][i] == null) {
                    panel[j][i] = new CirclePanel(Color.WHITE);
                } else if (board.getBoard()[j][i].getColor().equals("Red")) {
                    panel[j][i] = new CirclePanel(Color.RED);
                } else {
                    panel[j][i] = new CirclePanel(Color.BLUE);
                }
                panel[j][i].setBackground(new Color(255, 215, 0));
                gameGrid.add(panel[j][i]);
                
                panel[j][i].addMouseListener(new MouseAdapter() {
                    @Override
                    public void mouseEntered(MouseEvent e) {
                        /**
                        ActionListener taskPerformer = new ActionListener() {
                            
                            @Override
                            public void actionPerformed(ActionEvent e) {
                                for (int i = 0; i < panel[jj].length; i++) {
                                    panel[jj][i].setBackground(Color.YELLOW);
                                }
                            }
                            
                        };
                        new Timer(100, taskPerformer).start();
                        */
                        for (int i = 0; i < panel[jj].length; i++) {
                            panel[jj][i].setBackground(Color.YELLOW);
                        }
                    }
                    @Override
                    public void mouseExited(MouseEvent e) {
                        for (int i = 0; i < panel[jj].length; i++) {
                            panel[jj][i].setBackground(new Color(255, 215, 0));
                        }
                    }
                    @Override
                    public void mouseClicked(MouseEvent e) {
                        int column = jj;
                        if (board.getBoard()[column][0] == null) {
                            board.addPiece(column);
                        } else {
                            JOptionPane.showMessageDialog(new JFrame(), "Stalemate");
                        }
                        
                        JFrame win = new JFrame();
                        String winner = board.isWon();
                        if (winner != null) {
                            JOptionPane.showMessageDialog(win, winner);
                            System.exit(0);
                        } else if (comp == 1) {
                            board.addPiece(EasyMode.bestColumn(board));
                            winner= board.isWon();
                            if (winner != null) {
                                //drawBoard();
                                JOptionPane.showMessageDialog(win, winner);
                                System.exit(0);
                            }
                        } else if (comp == 2) {
                            board.addPiece(MediumMode.bestColumn(board));
                            winner= board.isWon();
                            if (winner != null) {
                                //drawBoard();
                                JOptionPane.showMessageDialog(win, winner);
                                System.exit(0);
                            }
                        } else if (comp == 3) {
                            board.addPiece(HardMode.bestColumn(board));
                            winner= board.isWon();
                            if (winner != null) {
                                //drawBoard();
                                JOptionPane.showMessageDialog(win, winner);
                                System.exit(0);
                            }
                        }
                        gameBoard();
                        
                    }
                });
            }
        }
        gameGrid.revalidate();
    }
}
