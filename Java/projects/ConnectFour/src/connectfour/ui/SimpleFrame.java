package connectfour.ui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.TitledBorder;

@SuppressWarnings("serial")
public class SimpleFrame extends JFrame {

   public SimpleFrame() {
      this.setTitle("Simple Frame");
      this.setSize(400, 200);
      this.setLocation(50, 50);
      this.setDefaultCloseOperation(EXIT_ON_CLOSE);
      
      Container c = this.getContentPane();
      JPanel pnlOne = new JPanel();
      JPanel pnlTwo = new JPanel();
      pnlOne.setBackground(Color.RED);
      pnlTwo.setBorder(new TitledBorder("Hello"));
      c.add(pnlOne, BorderLayout.NORTH);
      c.add(pnlTwo, BorderLayout.CENTER);

      this.setVisible(true);
   }

   public static void main(String[] args) {
      new SimpleFrame();
   }
}