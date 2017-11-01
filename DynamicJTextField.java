import javax.swing.*;
import java.awt.event.*;
import java.io.*;

public class DynamicJTextField extends JTextField implements ActionListener
{
  private int id;
   
   public DynamicJTextField(String text, int other,int ID){
     
      super(text,other); //I think...
      id = ID;
   }
   
   public DynamicJTextField(int other, int ID){
   id = ID;
   }
   public int getID(){
      return id;
   }
   
   public void addActionListener()
   {
        addActionListener(this);
   }
   
   public void actionPerformed(ActionEvent ae)
   {
      
      try
      {
         /*FileWriter output = new FileWriter("Java2Cpp.csv");
         BufferedWriter writer = new BufferedWriter(output);
        DynamicJButton temp = (DynamicJButton)ae.getSource();*/
        
        
        DynamicJTextField temp = (DynamicJTextField)ae.getSource();             
        Cpp2Java.sendCommandThroughPipe("0,"+temp.getID()+",ActionPerformed" + "~");
         
      }
      
      catch(Exception e)
      {
      
      }

      
   }
 }
