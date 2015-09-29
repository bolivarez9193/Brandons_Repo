/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package hotel;


import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import javax.swing.JFrame;
import javax.swing.JLabel;

/**
 *
 * @author bjolivarez
 */
public class Hotel extends JFrame{

    /**
     * @param args the command line arguments
     */
    private JLabel message;
	private static final long serialVersionUID = 1L;
	Hotel(){
		/*
		super("A Simple Window");
		
		final int WINDOW_WIDTH = 220;
		final int WINDOW_HEIGHT = 70;
		
		setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		message = new JLabel("Hello World");
		
		add(message);
		
		setVisible(true);
		*/
	}
	
	public static class hotelRoom
	{
		private String ID;
		private boolean empty;
		private String size;
		private boolean smoking;
		
		hotelRoom()
		{
                        ID = null;
			empty = true;
                        size = null;
		}
                
                public void setID(String x)
                {
                    ID = x;
                }
                
                public void setSize(String x)
                {
                    size = x;
                }
                
                public void isItSmoking(boolean x)
                {
                    smoking = x;
                }
                
                public String getSize()
                {
                   return size; 
                }
	}
	
	public static class Customer
	{
		private int ID;
		private String firstName;
		private String lastName;
		private hotelRoom room;
		
		Customer()
		{
			ID = 0;
			room = new hotelRoom();
		}
	}
    public static void main(String[] args) throws FileNotFoundException, IOException {
        hotelRoom[] hotelArray = new hotelRoom[15];
        int count = 0;
        BufferedReader reader = new BufferedReader(new FileReader("rooms.txt"));
        String line = null;
        while((line = reader.readLine()) != null)
        {
           if (line == "A")
           {
               hotelArray[count].setID(line);
               hotelArray[count].setSize("Penthouse Suite");
               hotelArray[count].isItSmoking(false);
           }
           else if(line == "B")
           {
               hotelArray[count].setID(line);
               hotelArray[count].setSize("Suite");
               hotelArray[count].isItSmoking(false);
           }
           else if(line == "C")
           {
               hotelArray[count].setID(line);
               hotelArray[count].setSize("Suite");
               hotelArray[count].isItSmoking(true);
           }
           else if(line == "D")
           {
               hotelArray[count].setID(line);
               hotelArray[count].setSize("Double Queen");
               hotelArray[count].isItSmoking(false);
           }
           else if(line == "E")
           {
               hotelArray[count].setID(line);
               hotelArray[count].setSize("Double Queen");
               hotelArray[count].isItSmoking(true);
           }
           else if(line == "F")
           {
               hotelArray[count].setID(line);
               hotelArray[count].setSize("King");
               hotelArray[count].isItSmoking(false);
           }
           else if (line == "G")
           {
               hotelArray[count].setID(line);
               hotelArray[count].setSize("King");
               hotelArray[count].isItSmoking(true);
           }
           count++;
        }
        
        String z = hotelArray[0].getSize();
        System.out.println(z);
    }
    
}
