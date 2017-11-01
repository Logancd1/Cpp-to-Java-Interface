
// Test_Interface.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Cpp2Java.h"

Cpp2Java cpp2Java;

JPanel myPanel1;
JPanel myPanel2;
JPanel myPanel3;
JPanel myPanel4;
JButton myBtn1("H,1fdsafsad");
//JButton myBtn11("H,1fasf");
JButton myBtn2("H,sdflo2");
JButton myBtn3("H,ellasfdo3");
JButton myBtn4("H,4");
string myItems [4] = { "op1","op2","op3","op4" };
JComboBox myBox(myItems);

JCheckBox jrb1("first option");
JCheckBox jrb2("second option");
JCheckBox jrb3("third option");
ButtonGroup b1;
int main() {
	
	cout << myItems[0] << endl;
	// SET J FRAME LAYOUT
	cpp2Java.setLayout(new GridLayout(2, 2));

	b1.add(jrb1);
	b1.add(jrb2);
	b1.add(jrb3);
	myPanel1.add(myBtn1);
	myPanel2.add(myBtn2);
	//myPanel2.add(myBtn11);

	myPanel3.add(myBtn3);
	myPanel3.add(jrb1);
	myPanel3.add(jrb2);
	myPanel3.add(jrb3);

	myPanel4.add(myBtn4);
	myPanel4.add(myBox);
	cpp2Java.add(myPanel1);
	cpp2Java.add(myPanel2);
	cpp2Java.add(myPanel3);
	cpp2Java.add(myPanel4);
	

	class KeyHandler : public KeyListener
	{
	public:
		void keyReleased(KeyEvent ke)
		{
			myPanel1.clearRect(0, 0, 600, 600);
			myPanel1.drawString(ke.getKeyChar(), 20, 20);
			myPanel1.repaint();
		}
	};

	KeyHandler myKH;
	cpp2Java.addKeyListener(myKH);
	this_thread::sleep_for(chrono::milliseconds(50));

	class ActionHandler : public ActionListener
	{
	public:
		void actionPerformed(ActionEvent ae)
		{	
			if (ae.getSource() == myBtn1)
			{
				for (int i = 0; i < 100; i++)
				{
					myPanel1.clearRect(0, 0, 600, 600);
					myPanel1.drawRect(20, 20, i, i);
					myPanel1.drawString(to_string(i), i, i);
					myPanel1.repaint();
					this_thread::sleep_for(chrono::milliseconds(30));
				}
			}
			else if (ae.getSource() == myBtn2)
			{
				for (int i = 0; i < 100; i++)
				{
					myPanel1.clearRect(0, 0, 600, 600);
					myPanel1.drawOval(20, 20, i, i);
					myPanel1.drawString(to_string(i), i, i);
					myPanel1.repaint();
					//this_thread::sleep_for(chrono::milliseconds(30));
				}
			}
			else if (ae.getSource() == myBtn3)
			{
				myPanel4.drawImage(new Image("img.jpg"),0,0);
				myPanel4.repaint();
			}
		};

	};
	//cout << "test1" << endl;

	class ItemHandler : public ItemListener
	{
		void itemStateChanged(ItemEvent ie)
		{
			if (ie.getSource() == jrb1)
			{
				if (ie.getStateChange() == ie.SELECTED)
				{	
					myPanel2.setColor("#FF0000");
					myPanel2.fillOval(20, 20, 20, 20);
					myPanel2.repaint();
				}
			}
			else if (ie.getSource() == jrb2)
			{
				if (ie.getStateChange() == ie.SELECTED)
				{
					myPanel2.setColor("#0000FF");
					myPanel2.fillRect(20, 20, 30, 30);
					myPanel2.repaint();
				}
			}
		}
	};

	ItemHandler myIH;
	ActionHandler myAH;

	myBtn1.addActionListener(myAH);
	myBtn2.addActionListener(myAH);
	myBtn4.addActionListener(myAH);

	jrb1.addItemListener(myIH);
	jrb2.addItemListener(myIH);
	jrb3.addItemListener(myIH);

	this_thread::sleep_for(chrono::milliseconds(50));

	cpp2Java.finish();

}