import javax.swing.JRadioButton;

public class DynamicJRadioButton extends JRadioButton
{
   public int ID;
   public DynamicJRadioButton(String text, int id)
   {
      super(text);
      ID = id;
   }
}