package connectfour.ui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JPanel;

@SuppressWarnings("serial")
public class CirclePanel extends JPanel {
    private Circle circle;
    
    public CirclePanel(java.awt.Color color)  {
    	    circle = new Circle(color);
    }

    public void setCircle(Circle circle) {
        this.circle = circle;
        repaint();
    }

    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        if (circle != null) {
            g.setColor(circle.color);
            g.fillOval(circle.getX() + 8, circle.getY() + 8, getWidth() - 17, getHeight() - 17);
        }
    }
    
    class Circle extends JPanel {
        private boolean draw = false;
        public java.awt.Color color;
        
        public Circle(java.awt.Color color) {
        	this.setColor(color);
        }

        public void setColor(java.awt.Color color) {
            this.color = color;
        }

        @Override
        public Dimension getPreferredSize() {
            return new Dimension(75, 75);
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            if (draw) {
                g.setColor(color);
                g.fillOval(0, 0, getWidth(), getHeight());
            }
        }
    }

	    public void setColor(Color color) {
	        this.circle.setColor(color);
	    }

    public void callRepaint() {
        repaint();
    }
}