import java.awt.event.KeyAdapter;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.io.*;

public class DynamicKeyAdapter extends KeyAdapter
{
   public void keyReleased (KeyEvent ke)
   {
      Cpp2Java.sendCommandThroughPipe("-1,KeyEvent,"+(ke.getKeyChar())+"~" );
   }
}

