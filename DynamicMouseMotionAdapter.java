import java.awt.event.MouseMotionAdapter;
import java.awt.event.MouseEvent;
import java.io.*;

public class DynamicMouseMotionAdapter extends MouseMotionAdapter
{
   public void mouseMoved(MouseEvent me)
   {
      Cpp2Java.sendCommandThroughPipe("-1,MouseMotionEvent,0"+me.getX()+","+me.getY());
   }
   
   public void mouseDragged(MouseEvent me)
   {
      Cpp2Java.sendCommandThroughPipe("-1,MouseMotionEvent,1"+me.getX()+","+me.getY());
   }
}
