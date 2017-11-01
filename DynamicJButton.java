import javax.swing.*;
import java.awt.event.*;
import java.io.*;

public class DynamicJButton extends JButton implements ActionListener
{
  private int id;
   
   public DynamicJButton(int ID){
      id = ID;
      
   }
   
   public DynamicJButton(int ID, String name){
      super(name);
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

         DynamicJButton temp = (DynamicJButton)ae.getSource();   
         Cpp2Java.sendCommandThroughPipe("0,"+temp.getID()+",ActionPerformed" + "~"); 
     }
 }
