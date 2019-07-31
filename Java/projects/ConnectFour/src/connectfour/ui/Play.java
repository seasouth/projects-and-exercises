package connectfour.ui;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextPane;

@SuppressWarnings("serial")
public class Play extends JFrame implements ActionListener {
    static ConnectFourGUI gui = null;
    static Container c;
    static JPanel gameChoice = new JPanel();
    JButton comp = new JButton();
    JButton player = new JButton();
    
    public Play() {
        c = getContentPane();
        this.setTitle("Connect Four!");
        this.setSize(300, 300);
        this.setLocation(400, 100);
        this.setVisible(true);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        c.setLayout(new GridLayout(1, 1));
        gameChoice.setLayout(new GridLayout(1, 2));
        comp.setText("Play Against Computer");
        comp.addActionListener(this);
        player.setText("Play Against Person");
        player.addActionListener(this);
        gameChoice.add(comp);
        gameChoice.add(player);
        c.add(gameChoice);
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource().equals(comp)) {
            new ChooseDifficulty();
        } else if (e.getSource().equals(player)) {
            gui = new ConnectFourGUI(0);
        }
        
    }
    
    public static void main(String[] args) {
        new Play();
    }

}
