package connectfour.ui;

import java.awt.Container;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class ChooseDifficulty extends JFrame implements ActionListener {
    Container c;
    static JPanel chooseDifficulty = new JPanel();
    JButton easy = new JButton();
    JButton medium = new JButton();
    JButton hard = new JButton();
    
    public ChooseDifficulty() {
        c = getContentPane();
        this.setTitle("Connect Four!");
        this.setSize(300, 300);
        this.setLocation(400, 100);
        this.setVisible(true);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        c.setLayout(new GridLayout(1, 1));
        c.add(chooseDifficulty);
        
        chooseDifficulty.setLayout(new GridLayout(1, 3));
        easy.setText("Easy");
        medium.setText("Medium");
        hard.setText("Hard");
        chooseDifficulty.add(easy);
        chooseDifficulty.add(medium);
        chooseDifficulty.add(hard);
        easy.addActionListener(this);
        medium.addActionListener(this);
        hard.addActionListener(this);
        
        
        
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource().equals(easy)) {
            Play.gui = new ConnectFourGUI(1);
        } else if (e.getSource().equals(medium)) {
            Play.gui = new ConnectFourGUI(2);
        } else if (e.getSource().equals(hard)) {
            Play.gui = new ConnectFourGUI(3);
        }
        
    }

}
