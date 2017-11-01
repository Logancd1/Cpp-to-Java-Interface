import javax.swing.*;
import java.awt.event.*;
import java.io.*;

public class DynamicItemListener implements ItemListener
{
   public DynamicItemListener()
   {
      super();
   }
   public void itemStateChanged(ItemEvent ie)	{
      
      Object src = ie.getSource();
      
      if (src instanceof DynamicJCheckBox)
      {
         System.out.println(((DynamicJCheckBox)src).ID);
         Cpp2Java.sendCommandThroughPipe("1,"+((DynamicJCheckBox)src).ID+",itemStateChanged,"+ ie.getStateChange() + "~");
      }
      else if (src instanceof DynamicJRadioButton)
      {
          System.out.println(((DynamicJRadioButton)src).ID);
         Cpp2Java.sendCommandThroughPipe("1,"+((DynamicJRadioButton)src).ID+",itemStateChanged,"+ ie.getStateChange() + "~");
      }
   }
}