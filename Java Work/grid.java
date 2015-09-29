import java.awt.*;
import javax.swing.*;

public class grid extends JFrame{
	private static final long serialVersionUID = 1L;
	private final int WINDOW_WIDTH = 300;
	private final int WINDOW_HEIGHT = 200;
	
	public grid()
	{
		super("Grid Window");
		
		setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		setLayout(new GridLayout(2,1));
		
		JButton button1 = new JButton("7");
		JButton button2 = new JButton("8");
		
		
		add(button1);
		add(button2);
		
		
		setVisible(true);
	}
}
