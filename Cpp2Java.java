import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;

public class Cpp2Java extends JFrame { //One-JFrame setup
    private static Container contents;
    private ArrayList < JComponent > comps = new ArrayList < JComponent > (64);
    private ArrayList < ButtonGroup> butts = new ArrayList < ButtonGroup > (64);

    private class GuiThread extends Thread {
        public void run() {
            while (true) {
                ArrayList < String > cmnds = new ArrayList < String > (64);

                boolean waitForCPP = true;
                RandomAccessFile pipe = null;
                while (waitForCPP) {
                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException ie) {}
                    try {
                        pipe = new RandomAccessFile("\\\\.\\pipe\\Cpp2Java_gui", "r");
                        waitForCPP = false;
                    } catch (FileNotFoundException CPPNotOpened) {
                        // e1.printStackTrace();
                    }
                }
                // Main loop
                try {
                    String inData = "";
                    while ((inData = pipe.readLine()) != null) {
                            cmnds.add(inData);
                    }

                } catch (IOException e) {
                    e.printStackTrace();
                }
                performCommands(cmnds);
                revalidate();
                repaint();
            }
        }
    }
    private class PaintThread extends Thread {
        public void run() {
            while (true) {
                boolean waitForCPP = true;
                RandomAccessFile pipe = null;
                while (waitForCPP) {
                    try {
                        Thread.sleep(10);
                    } catch (InterruptedException ie) {}
                    try {
                        pipe = new RandomAccessFile("\\\\.\\pipe\\Cpp2Java_paint", "r");
                        waitForCPP = false;
                    } catch (FileNotFoundException e1) {
                        // e1.printStackTrace();
                    }
                }

                   try {
                       String fileLine = "";
                       int repaintID = -1;
                       while ((fileLine = pipe.readLine()) != null) {
                           String[] line = fileLine.split(",");
                           String command = "";
                           for (int i = 1; i < line.length; i++) {
                               command += line[i] + ",";
                           }
                           ((DynamicJPanel) comps.get(Integer.parseInt(line[0]))).addCommand(command);
                           
                           //ID is the instanceName from Cpp2Java.h
                           int ID = Integer.parseInt(line[0]);
                           repaintID = ID;
                       }
                       if (repaintID != -1)
                        ((DynamicJPanel) comps.get(repaintID)).tryPaint();
                       else
                        System.out.println("no more commands");
                       
                   } catch (IOException ioe) {}
                try {
                    pipe.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }

            }
        }
    }

    //private ArrayList<JComponent>();
    public Cpp2Java() {
        super("Cpp2Java");
        contents = getContentPane();
        contents.setLayout(new GridLayout(2, 2));

        setSize(720, 540);
        setVisible(true);

        GuiThread gui = new GuiThread();
        PaintThread pnt = new PaintThread();

        gui.start();
        pnt.start();
        startPipe();
    }

    public static void main(String args[]) {
            // monitor a single file
            Cpp2Java frame = new Cpp2Java();

            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);


        } //Main   
    
    public static RandomAccessFile pipe;
    public static void startPipe()
    {
      boolean busyWait1 = true;
                pipe = null;
                while (busyWait1) {
                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException ie) {}
                    try {
                        pipe = new RandomAccessFile("\\\\.\\pipe\\Java2Cpp", "rw");
                        busyWait1 = false;
                    } catch (FileNotFoundException e1) {
                        // e1.printStackTrace();
                    }
                }
    }
    public static void sendCommandThroughPipe(String command)  {
               
                               // Main loop
                try {
                    pipe.writeBytes(command);
                } catch (IOException e) {
                    e.printStackTrace();
                }
                // Close the pipe at the end
                // //System.out.println("here0");

                /*try {
                    pipe.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }*/
               

    }
    
    public void performCommands(ArrayList < String > cmnds) {
        //this.contents.removeAll();
        //this.getContentPane().removeAll();
        for (String l: cmnds) {
            ////System.out.println(l);

            String[] line = l.split(",");
            int ID = Integer.parseInt(line[0]);
            int nRows;
            int nCols;
            int hGap;
            int vGap;
         
            switch (line[1]) { //Type of Command
                case "setFrameSize":
                  setSize(Integer.parseInt(line[2]), Integer.parseInt(line[3]));
                  setVisible(true);
                  break;
                case "addActionListener":
                    {                       
                       if ( comps.get(ID) instanceof JButton) //If component is a DynamicJButton
                        {
                             ((DynamicJButton)comps.get(ID)).addActionListener();
                            
                        } else if (comps.get(ID) instanceof JTextField) //If component is a DynamicTextField
                        {
                            ((DynamicJTextField) comps.get(ID)).addActionListener();
                        }
                    }
                    break;
                case "addItemListener":
                {
                  Object temp = comps.get(ID);
                  if (temp instanceof DynamicJCheckBox)
                     ((DynamicJCheckBox)temp).addItemListener(new DynamicItemListener());
                  else if (temp instanceof DynamicJRadioButton)
                     ((DynamicJRadioButton)temp).addItemListener(new DynamicItemListener());
                }
                break;
                case "removeAll":
                    {
                        comps.clear();
                        this.contents.removeAll();
                        this.getContentPane().removeAll();
                    }
                    break;
                case "instantiate":
                    {
                        switch (line[3]) { // Type of JComponent
                            case "JPanel":
                                comps.add(ID, new DynamicJPanel());
                                break;
                            case "JComboBox":
                                comps.add(ID, new JComboBox());
                                comps.get(ID).setFocusable(false);
                                break;
                            case "JLabel":
                                {
                                    switch (Integer.parseInt(line[2])) { // Type of Constructor Method
                                        case 0:
                                            comps.add(ID, new JLabel(line[4]));
                                            break;
                                        case 1:
                                            comps.add(ID, new JLabel(line[4], Integer.parseInt(line[5])));
                                            break;
                                    }
                                }
                                break;
                            case "JTextField":
                                {
                                    switch (Integer.parseInt(line[2])) {
                                        case 0:
                                            comps.add(ID, new DynamicJTextField(line[4], Integer.parseInt(line[5]), ID));
                                            comps.get(ID).setFocusable(false);
                                            break;
                                        case 1:
                                            comps.add(ID, new DynamicJTextField(Integer.parseInt(line[4]), ID));
                                            comps.get(ID).setFocusable(false);
                                            break;
                                    }
                                }
                                break;
                            case "JTextArea":
                                {
                                    switch (Integer.parseInt(line[2])) {
                                        case 0:
                                            comps.add(ID, new JTextArea(line[4]));
                                            comps.get(ID).setFocusable(false);
                                            break;
                                        case 1:
                                            comps.add(ID, new JTextArea(Integer.parseInt(line[4]), Integer.parseInt(line[5])));
                                            comps.get(ID).setFocusable(false);
                                            break;
                                        case 2:
                                            comps.add(ID, new JTextArea(
                                                Integer.parseInt(line[4]), Integer.parseInt(line[5], Integer.parseInt(line[6]))));
                                                comps.get(ID).setFocusable(false);
                                            break;
                                    }
                                }
                                break;
                            case "JButton":
                                {

                                    switch (Integer.parseInt(line[2])) {
                                        case 0:
                                            comps.add(ID, new DynamicJButton(ID));
                                            comps.get(ID).setFocusable(false); 

                                            break;
                                        case 1:
                                            comps.add(ID, new DynamicJButton(ID, line[4]));
                                            comps.get(ID).setFocusable(false); 
                                            break;
                                    }
                                }
                                break;
                            case "ButtonGroup":
                              butts.add(ID, new ButtonGroup());
                            break;
                            
                            case "JRadioButton":
                              comps.add(ID, new DynamicJRadioButton(line[4],ID));
                              comps.get(ID).setFocusable(false);
                            break;
                            
                            case "JCheckBox":
                              comps.add(ID, new DynamicJCheckBox(line[4],ID));
                              comps.get(ID).setFocusable(false);
                            break;
                            
                            default:
                                break;
                                //JTextField
                                //JButton
                        }
                    }
                    break;
                case "addItemToComboBox":
                  {
                      ( (JComboBox)comps.get(ID) ).addItem( (line[2]) );
                  }
                  break;
                 case "addToButtonGroup":
                  {
                    if ( comps.get(Integer.parseInt(line[2])) instanceof DynamicJRadioButton)
                    {
                      ( (ButtonGroup)butts.get(ID) ).add
                        ( 
                           (DynamicJRadioButton) ( comps.get(Integer.parseInt(line[2])) )
                        );
                    }
                    else if ( comps.get(Integer.parseInt(line[2])) instanceof DynamicJCheckBox)
                    {
                      ( (ButtonGroup)butts.get(ID) ).add
                        ( 
                           (DynamicJCheckBox) ( comps.get(Integer.parseInt(line[2])) )
                        );
                    }
                  }
                  break;
                case "setTextJL":
                    {
                        ((JLabel) comps.get(Integer.parseInt(line[0]))).setText(line[2]);
                    }
                    break;

                case "setTextJTA":
                    {
                        ((JTextArea) comps.get(Integer.parseInt(line[2]))).setText(line[1]);
                    }
                    break;

                case "setTextJTF":
                    {
                        ((JTextField) comps.get(Integer.parseInt(line[2]))).setText(line[1]);
                    }

                case "setLayout":
                    {
                        switch (line[2]) {
                            case "GridLayout":
                                {
                                    switch (Integer.parseInt(line[3])) {
                                        case 0:
                                            nRows = Integer.parseInt(line[4]);
                                            nCols = Integer.parseInt(line[5]);
                                            comps.get(ID).setLayout(new GridLayout(nRows, nCols));
                                            break;
                                        case 1:
                                            nRows = Integer.parseInt(line[4]);
                                            nCols = Integer.parseInt(line[5]);
                                            hGap = Integer.parseInt(line[6]);
                                            vGap = Integer.parseInt(line[7]);
                                            comps.get(ID).setLayout(new GridLayout(nRows, nCols, hGap, vGap));
                                            break;
                                    }
                                }
                                break;
                            case "BorderLayout":
                                {
                                    switch (Integer.parseInt(line[3])) {
                                        case 0:
                                            comps.get(ID).setLayout(new BorderLayout());
                                            break;
                                        case 1:
                                            hGap = Integer.parseInt(line[4]);
                                            vGap = Integer.parseInt(line[5]);
                                            comps.get(ID).setLayout(new BorderLayout(hGap, vGap));
                                            break;
                                    }

                                }
                                break;
                        }
                    }
                    break;

                    // JComponent Methods
                case "add":
                    {
                        // Command [1] is the JComponent you're adding TO
                        // Command [2] is the JComponent that you're adding
                        String layout;
                        String layoutID;
                        try {
                            layout = line[3];
                            switch (layout) {
                                case "BorderLayout.NORTH":
                                    layoutID = BorderLayout.NORTH;
                                    break;
                                case "BorderLayout.EAST":
                                    layoutID = BorderLayout.EAST;
                                    break;
                                case "BorderLayout.SOUTH":
                                    layoutID = BorderLayout.SOUTH;
                                    break;
                                case "BorderLayout.WEST":
                                    layoutID = BorderLayout.WEST;
                                    break;
                                case "BorderLayout.CENTER":
                                    layoutID = BorderLayout.CENTER;
                                    break;
                                default:
                                    layoutID = BorderLayout.CENTER;
                                    break;
                            }
                            comps.get(ID).add(comps.get(Integer.parseInt(line[2])), layoutID);
                        } catch (IndexOutOfBoundsException ie) {
                            comps.get(ID).add(comps.get(Integer.parseInt(line[2])));
                        }
                    }

                    // comps_add.add(
                    break;

                case "setForeground":
                    comps.get(ID).setForeground(Color.decode(line[2]));
                    break;

                case "setBackground":
                    comps.get(ID).setBackground(Color.decode(line[2]));
                    break;


                    // Container Methods
                case "setContainerLayout":
                    {
                        switch (line[2]) {
                            case "GridLayout":
                                {
                                    switch (Integer.parseInt(line[3])) {
                                        case 0:
                                            nRows = Integer.parseInt(line[4]);
                                            nCols = Integer.parseInt(line[5]);
                                            this.contents.setLayout(new GridLayout(nRows, nCols));
                                            break;
                                        case 1:
                                            nRows = Integer.parseInt(line[4]);
                                            nCols = Integer.parseInt(line[5]);
                                            hGap = Integer.parseInt(line[6]);
                                            vGap = Integer.parseInt(line[7]);
                                            this.contents.setLayout(new GridLayout(nRows, nCols, hGap, vGap));
                                            break;
                                    }
                                }
                                break;
                            case "BorderLayout":
                                {
                                    switch (Integer.parseInt(line[3])) {
                                        case 0:
                                            this.contents.setLayout(new BorderLayout());
                                            break;
                                        case 1:
                                            hGap = Integer.parseInt(line[4]);
                                            vGap = Integer.parseInt(line[5]);
                                            this.contents.setLayout(new BorderLayout(hGap, vGap));
                                            break;
                                    }

                                }
                                break;
                        }
                    }
                    break;
                case "addContainer":
                    {
                        String layout;
                        String layoutID;
                        try {
                            layout = line[4];
                            switch (layout) {
                                case "BorderLayout.NORTH":
                                    layoutID = BorderLayout.NORTH;
                                    break;
                                case "BorderLayout.EAST":
                                    layoutID = BorderLayout.EAST;
                                    break;
                                case "BorderLayout.SOUTH":
                                    layoutID = BorderLayout.SOUTH;
                                    break;
                                case "BorderLayout.WEST":
                                    layoutID = BorderLayout.WEST;
                                    break;
                                case "BorderLayout.CENTER":
                                    layoutID = BorderLayout.CENTER;
                                    break;
                                default:
                                    layoutID = BorderLayout.CENTER;
                                    break;
                            }
                            this.contents.add(comps.get(Integer.parseInt(line[2])), layoutID);
                        } catch (IndexOutOfBoundsException ie) {
                            this.contents.add(comps.get(Integer.parseInt(line[2])));
                        }
                    }
                    break;
                case "addKeyListener":
                    contents.addKeyListener(new DynamicKeyAdapter());
                    contents.setFocusable(true);
                    contents.requestFocusInWindow();

                    break;
                case "addMouseListener":
                    contents.addMouseListener(new DynamicMouseListener());
                    break;
                case "addMouseMotionListener":
                     contents.addMouseMotionListener(new DynamicMouseMotionAdapter());
                     break;    
            }
        }
    }
}