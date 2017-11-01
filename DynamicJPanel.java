import java.util.*;
import javax.swing. * ;
import java.awt. * ;
import javax.imageio.*;
import java.awt.image.*;
import java.io.*;

public class DynamicJPanel extends JPanel {
	private Vector < String > commands = new Vector<String>();

   private class PaintCommandThread implements Runnable   {
      public void run()
      {
         repaint();
      }
   }
   
   Thread pct = new Thread(new PaintCommandThread(), "PaintCommands");
   public void tryPaint()
   {
         while(pct.isAlive())
         {
         };
         pct = new Thread(new PaintCommandThread(), "PaintCommands");
         pct.start();
   
   }
	public void addCommand(String command) {
		commands.add(command);
	}
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		try {
      Iterator<String> iter = commands.iterator();
			while (iter.hasNext()) {
            String C = iter.next();
				String[] command = C.split(",");
				switch (command[0]) {
				case "drawRect":
					g.drawRect(Integer.parseInt(command[1]), Integer.parseInt(command[2]), Integer.parseInt(command[3]), Integer.parseInt(command[4]));
					break;

				case "drawLine":
					g.drawLine(Integer.parseInt(command[1]), Integer.parseInt(command[2]), Integer.parseInt(command[3]), Integer.parseInt(command[4]));
					break;

				case "fillRect":
					g.fillRect(Integer.parseInt(command[1]), Integer.parseInt(command[2]), Integer.parseInt(command[3]), Integer.parseInt(command[4]));
					break;

				case "clearRect":
					g.clearRect(Integer.parseInt(command[1]), Integer.parseInt(command[2]), Integer.parseInt(command[3]), Integer.parseInt(command[4]));
					break;

				case "drawOval":
					g.drawOval(Integer.parseInt(command[1]), Integer.parseInt(command[2]), Integer.parseInt(command[3]), Integer.parseInt(command[4]));
					break;

				case "fillOval":
					g.fillOval(Integer.parseInt(command[1]), Integer.parseInt(command[2]), Integer.parseInt(command[3]), Integer.parseInt(command[4]));
					break;

				case "drawString":
					g.drawString(command[1], Integer.parseInt(command[2]), Integer.parseInt(command[3]));
					break;
               
            case "drawImage":
               BufferedImage temp;
               try
               {
                  // May cause performance issues
                  temp = ImageIO.read(new File(command[1]));
               }
               catch (IOException ioe)
               {
                  temp = null;
               }
					g.drawImage(temp, Integer.parseInt(command[2]), Integer.parseInt(command[3]),null);
					break;
               
               case "setColor":
               g.setColor(Color.decode(command[1]));
               break;

				}
			}
		}
		catch(NullPointerException | ConcurrentModificationException npe) {}
      commands.clear();
	}
}