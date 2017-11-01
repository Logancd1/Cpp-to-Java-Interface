import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.io.*;

public class testPanel extends JPanel
{
   public testPanel()
   {
      add(new JLabel("123"));
      add(new JLabel("abc"));
      add(new JButton("Test Button"));
      //...
      //...
      //
      
      
      
   }
   public void paint(Graphics g)
   {
      super.paint(g);
      
      g.setColor(Color.RED);
      g.drawRect(0,0,50,50);
      
      
      
      
      
   }
}