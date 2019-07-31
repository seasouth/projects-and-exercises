package connectfour.color;

public class Piece {
    public static int colorNum = 0;
    public String color;
    
    public Piece(int colorNum) {
        if (colorNum % 2 == 0) {
            color = "Red";
        } else {
            color = "Blue";
        }
    }
    
    public Piece() {
        this(colorNum++);
    }
    
    public String getColor() {
        return this.color;
    }
}

