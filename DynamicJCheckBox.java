import javax.swing.*;

public class DynamicJCheckBox extends JCheckBox
{
   public int ID;
   public DynamicJCheckBox(String text, int id)
   {
      super(text);
      ID = id;
   }
}