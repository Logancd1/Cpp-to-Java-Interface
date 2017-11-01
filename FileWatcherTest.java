
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;
import java.lang.Compiler;

public class FileWatcherTest extends JFrame { //One-JFrame setup
      private static Container contents;

   public FileWatcherTest()
   {
      super("Cpp2Java");
		  contents	= getContentPane();
        setSize(720,540);
		setVisible(true);

   }
  public static void main(String args[]) {
    // monitor a single file
    FileWatcherTest fwt = new FileWatcherTest();
   fwt.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
   contents.add(new testPanel());
   fwt.revalidate();
      
    TimerTask task = new FileWatcher( new File("text.txt") ) {
     JPanel test;
      protected void onChange( File file ) {
      
        // here we code the action on a change
        System.out.println( "File "+ file.getName() +" have change !" );
 
        //contents.removeAll();
        contents.add(new testPanel());
        fwt.revalidate();

        /* Swap JPanel (one-JPanel setup)
        
        this.removeAll();
        this.add(new userJPanel());
        
        this.revalidate(); ???
        this.update(); ???
        
        
        */
      }
    };

    java.util.Timer timer = new java.util.Timer();
    // repeat the check every second
    timer.schedule( task , new Date(), 1 );
  }
}