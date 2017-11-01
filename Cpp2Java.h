// Test_Interface.cpp : Defines the entry point for the console application.
//
#ifndef CPP2JAVA_H
#define CPP2JAVA_H

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <utility>
#include <stdexcept>
#if defined(_WIN32)|| defined(_WIN64)
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#endif

#define BUFSIZE 512

using namespace std;

string pipedCommand;

void sendCommandsThroughPipe(vector<string> cmnds, wstring pipeName)
{
	//START WINDOWS CODE
#if defined(_WIN32) || defined(_WIN64)
	//cout << "Creating an instance of a named pipe..." << endl;

	// Create a pipe to send data
	wstring pipeN = L"\\\\.\\pipe\\" + pipeName;
	LPCWSTR pipeNN = pipeN.c_str();
	//wcout << pipeName << endl;
	HANDLE pipe = CreateNamedPipe(
		pipeNN, // name of the pipe
		PIPE_ACCESS_DUPLEX, // 1-way pipe -- send only
		PIPE_TYPE_BYTE, // send data as a byte stream
		1, // only allow 1 instance of this pipe
		100, // no outbound buffer
		100, // no inbound buffer
		0, // use default wait time
		PIPE_ACCEPT_REMOTE_CLIENTS // use default security attributes
	);

	if (pipe == NULL || pipe == INVALID_HANDLE_VALUE) {
		// look up error code here using GetLastError()
		system("pause");
	}

	//cout << "Waiting... Have you made sure that Cpp2Java is open in the background?" << endl;

	// This call blocks until a client process connects to the pipe
	BOOL result = ConnectNamedPipe(pipe, NULL);
	if (!result) {
		cout << "Failed to connect to Java. Check to make sure it is open.";
		// look up error code here using GetLastError()
		//cout << GetLastError() << endl;
		CloseHandle(pipe); // close the pipe
						   //system("pause");
	}

	for (string cmnd : cmnds)
	{
		//cout << cmnd << endl;
		//Sleep(10);
		//cout << "Sending data to pipe..." << endl;
		// This call blocks until a client process reads all the data
		//const wchar_t *data = L"1,add,2\n";
		string wCmnd = cmnd + "\n";

		const char *data = wCmnd.c_str();
		//const wchar_t *data = L"1,1,1,1,1,1,1\r\n";
		DWORD numBytesWritten = 0;
		result = WriteFile(
			pipe, // handle to our outbound pipe
			data, // data to send
			strlen(data) * sizeof(char), // length of data to send (bytes)
			&numBytesWritten, // will store actual amount of data sent
			NULL // not using overlapped IO
		);


		if (result) {
			//cout << "Number of bytes sent: " << numBytesWritten << endl;
		}
		else {
			//cout << "Failed to send data." << endl;
			// look up error code here using GetLastError()
		}
	}
	// Close the pipe (automatically disconnects client too)
	CloseHandle(pipe);

	//cout << "Done." << endl;

	//system("pause");

	//END WINDOWS CODE

	//START UNIX CODE
#elif __unix || __unix__ || __APPLE__ || __MACH__ || __linux__

	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)

#else
#endif // END UNIX CODE
};

class Commands {
public:
	vector<string> gui;
	vector<string> paint;
	int instanceCounter;
	int instanceCounter2;
};
Commands c;

class KeyEvent {
public:
	KeyEvent(char keyPressed);
	string getKeyChar();
private:
	char key;
};
KeyEvent::KeyEvent(char keyPressed)
{
	key = keyPressed;
}
string KeyEvent::getKeyChar()
{
	string s; s.push_back(key);
	return s;
}
class KeyListener {
public:
	virtual void keyReleased(KeyEvent ke) {};
};

class MouseEvent {
public:
	MouseEvent(int clickX, int clickY, int buttonClicked, int clicksCount);
	int getMouseClickX();
	int getMouseClickY();
	int getButtonClicked();
	int getClickCount();
private:
	int x;
	int y;
	int button;
	int clickCount;
};
MouseEvent::MouseEvent(int clickX, int clickY, int buttonClicked, int clicksCount)
{
	x = clickX;
	y = clickY;
	button = buttonClicked;
	clickCount = clicksCount;
}
int MouseEvent::getMouseClickX()
{
	return x;
}
int MouseEvent::getMouseClickY()
{
	return y;
}
int MouseEvent::getButtonClicked()
{
	return button;
}
int MouseEvent::getClickCount()
{
	return clickCount;
}
class MouseListener {
public:
	virtual void mouseClicked(MouseEvent me) {};
	virtual void mousePressed(MouseEvent me) {};
};

class MouseMotionEvent {
public:
	MouseMotionEvent(int clickX, int clickY);
	int getMouseClickX();
	int getMouseClickY();
private:
	int x;
	int y;
};
MouseMotionEvent::MouseMotionEvent(int clickX, int clickY)
{
	x = clickX;
	y = clickY;
}
int MouseMotionEvent::getMouseClickX()
{
	return x;
}
int MouseMotionEvent::getMouseClickY()
{
	return y;
}
class MouseMotionListener {
public:
	virtual void mouseMoved(MouseMotionEvent mme) {};
	virtual void mouseDragged(MouseMotionEvent mme) {};
};
/*class Polygon {
public:
Polygon() {};
void addPoint(int x, int y);
pair<int, int> point;
vector<pair<int, int> > coord;
};
void Polygon::addPoint(int x, int y)
{
point = make_pair(x, y);
coord.push_back(point);
}*/

class Image {
public:
	Image(string file);
	string filename;
};
Image::Image(string file)
{
	filename = file;
}

class LayoutManager {
private:
	string type;

public:
	void setLayoutType(string type_in);
	string getLayoutType();
};
string LayoutManager::getLayoutType()
{
	return type;
}
void LayoutManager::setLayoutType(string type_in)
{
	type = type_in;
}

class BorderLayout : public LayoutManager {
public:
	BorderLayout();
	BorderLayout(int hGap, int vGap);
	int verticalGap;
	int horizontalGap;
};
BorderLayout::BorderLayout() //0
{
	setLayoutType("BorderLayout,0");
}
BorderLayout::BorderLayout(int hGap, int vGap) //1
{
	setLayoutType("BorderLayout,1");
	verticalGap = vGap;
	horizontalGap = hGap;
}

class GridLayout : public LayoutManager {
public:
	GridLayout(int numberOfRows, int numberOfColumns);
	GridLayout(int numberOfRows, int numberOfColumns, int hGap, int vGap);
	int numRows;
	int numCols;
	int horzontalGap;
	int verticalGap;
};
GridLayout::GridLayout(int numberOfRows, int numberOfColumns)
{
	setLayoutType("GridLayout,0");
	numRows = numberOfRows;
	numCols = numberOfColumns;
}
GridLayout::GridLayout(int numberOfRows, int numberOfColumns, int hGap, int vGap)
{
	setLayoutType("GridLayout,1");
	numRows = numberOfRows;
	numCols = numberOfColumns;
	horzontalGap = hGap;
	verticalGap = vGap;
}

class JComponent {
	friend class Cpp2Java;
	friend class Polygon;
	friend class ActionListener;
	friend class ItemListener;
	friend class MouseListener;
	friend class MouseMotionListener;

public:
	JComponent() {};
	JComponent(const JComponent & copy) {
		instanceName = copy.instanceName;
	};
	bool operator==(JComponent& jC);
	void operator = (JComponent & jC)
	{
		instanceName = jC.instanceName;
	}
	void operator = (JComponent * jC)
	{
		instanceName = jC->instanceName;
	}
	virtual void add(JComponent& jc);
	virtual void drawRect(int x, int y, int width, int height);
	virtual void drawLine(int xStart, int yStart, int xEnd, int yEnd);
	virtual void fillRect(int x, int y, int width, int height);
	virtual void clearRect(int x, int y, int width, int height);
	virtual void drawOval(int x, int y, int width, int height);
	virtual void fillOval(int x, int y, int width, int height);
	//virtual void drawPolygon(Polygon p);
	//virtual void fillPolgon(Polygon p);
	virtual void drawString(string s, int x, int y);
	virtual void drawImage(Image & i, int x, int y);
	virtual void drawImage(Image * i, int x, int y);
	virtual void setColor(string color);
	virtual void setForeground(string color);
	virtual void setBackground(string color);
	virtual void repaint();
	string getInstanceName();
	ofstream file1;
	string instanceName;
	ActionListener* al1;
	ItemListener* il1;
	//MouseListener* ml1;
	//MouseMotionListener mml1;

protected:
	void setInstanceName();
};
/*ostream& operator<<(ostream& os, JComponent& jC)
{
os << "InstanceName:" << jC.instanceName;
return os;
}*/
ostream& operator<<(ostream& os, JComponent* jC)
{
	os << "InstanceName:" << jC->instanceName;
	return os;
}
ostream& operator<<(ostream& os, JComponent jC)
{
	os << "InstanceName:" << jC.instanceName;
	return os;
}
bool JComponent::operator==(JComponent & jC)
{
	return instanceName.compare(jC.instanceName) == 0;
};
void JComponent::add(JComponent& jc)
{
	c.gui.push_back(instanceName + ",add," + jc.instanceName);
}
void JComponent::drawRect(int x, int y, int width, int height)
{
	c.paint.push_back(instanceName + ",drawRect," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height));
}
void JComponent::drawLine(int xStart, int yStart, int xEnd, int yEnd)
{
	c.paint.push_back(instanceName + ",drawLine," + to_string(xStart) + "," + to_string(yStart) + "," + to_string(xEnd) + "," + to_string(yEnd));
}
void JComponent::fillRect(int x, int y, int width, int height)
{
	c.paint.push_back(instanceName + ",fillRect," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height));
}
void JComponent::clearRect(int x, int y, int width, int height)
{
	c.paint.push_back(instanceName + ",clearRect," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height));
}
void JComponent::drawOval(int x, int y, int width, int height)
{
	c.paint.push_back(instanceName + ",drawOval," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height));
}
void JComponent::fillOval(int x, int y, int width, int height)
{
	c.paint.push_back(instanceName + ",fillOval," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height));
}
void JComponent::drawString(string s, int x, int y)
{
	c.paint.push_back(instanceName + ",drawString," + s + "," + to_string(x) + "," + to_string(y));
}
/*void JComponent::drawPolygon(Polygon p)
{
string line;
line = instanceName + ",drawPolygon";
for (pair<int, int> pr : p.coord) {
line += "," + to_string(pr.first) + "*" + to_string(pr.second);
}
c.paint.push_back(line);
}
void JComponent::fillPolgon(Polygon p)
{
string line;
line = instanceName + "fillPolygon";
for (pair<int, int> pr : p.coord) {
line += "," + to_string(pr.first) + "*" + to_string(pr.second);
}
c.paint.push_back(line);
}*/
void JComponent::drawImage(Image & i, int x, int y)
{
	c.paint.push_back(instanceName + ",drawImage," + i.filename + "," + to_string(x) + "," + to_string(y));
}
void JComponent::drawImage(Image * i, int x, int y)
{
	c.paint.push_back(instanceName + ",drawImage," + i->filename + "," + to_string(x) + "," + to_string(y));
}
void JComponent::setColor(string color)
{
	c.paint.push_back(instanceName + ",setColor," + color);
}
void JComponent::setForeground(string color)
{
	c.gui.push_back(instanceName + ",setForeground," + color);
}
void JComponent::setBackground(string color)
{
	c.gui.push_back(instanceName + ",setBackground," + color);
}
void JComponent::repaint()
{
	sendCommandsThroughPipe(c.paint, L"Cpp2Java_paint");
	c.paint.clear();
}

void JComponent::setInstanceName()
{
	instanceName = to_string(c.instanceCounter);
	c.instanceCounter++;
}
string JComponent::getInstanceName()
{
	return instanceName;
}


// This vector is used to reference action events.
// It must be declared after JComponent is defined.
vector<JComponent> jComps;
KeyListener * storedKL = new KeyListener();
//MouseListener * ml1 = new MouseListener();
//MouseMotionListener * mml1 = new MouseMotionListener();
MouseListener * storedML = new MouseListener();
MouseMotionListener * storedMML = new MouseMotionListener();

class ItemEvent
{
public:
	ItemEvent(int jc, int newTypeStateChanged);
	JComponent getSource();
	int getStateChange();
	int jC;
	int SELECTED;
	int DESELECTED;
	int typeStateChanged;
};

ItemEvent::ItemEvent(int jc, int newTypeStateChanged)
{
	SELECTED = 1;
	DESELECTED = 2;
	jC = jc;
	typeStateChanged = newTypeStateChanged;
}
JComponent ItemEvent::getSource()
{
	return (jComps[jC]);
}
int ItemEvent::getStateChange()
{
	return typeStateChanged;
}

class ItemListener
{
public:
	//ItemListener() {};
	//ItemListener(const ActionListener & copy) {};
	virtual void itemStateChanged(ItemEvent ae) { /*cout << "calling original!" << endl;*/ }
	virtual void itemStateChanged(ItemEvent * ae) {};
};

vector<ItemListener *> storedILs(64);


class JRadioButton : public JComponent
{
public:
	JRadioButton(string s);
	JRadioButton(JRadioButton & copy) {
		instanceName = copy.instanceName;
	};
	bool operator==(JRadioButton & jRB)
	{
		return instanceName.compare(jRB.instanceName) == 0;
	}
	bool operator==(JComponent & jC)
	{
		return instanceName.compare(jC.getInstanceName()) == 0;
	}
	void operator = (JComponent & jC)
	{
		instanceName = jC.getInstanceName();
	}
	void operator = (JComponent * jC)
	{
		instanceName = jC->getInstanceName();
	}
	void addItemListener(ItemListener * iL);
	void addItemListener(ItemListener & iL);

};
JRadioButton::JRadioButton(string s)
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,0,JRadioButton," + s);
	jComps.push_back(*this);
}
void JRadioButton::addItemListener(ItemListener * iL)
{
	c.gui.push_back(instanceName + ",addItemListener");
	storedILs[stoi(instanceName)] = iL;
}
void JRadioButton::addItemListener(ItemListener & iL)
{
	c.gui.push_back(instanceName + ",addItemListener");
	storedILs[stoi(instanceName)] = &iL;
}

class JCheckBox : public JComponent
{
public:
	JCheckBox(string s);
	JCheckBox(JCheckBox & copy) {
		instanceName = copy.instanceName;
	};
	bool operator==(JCheckBox & jCB)
	{
		return instanceName.compare(jCB.instanceName) == 0;
	}
	bool operator==(JComponent & jC)
	{
		return instanceName.compare(jC.getInstanceName()) == 0;
	}
	void operator = (JComponent & jC)
	{
		instanceName = jC.getInstanceName();
	}
	void operator = (JComponent * jC)
	{
		instanceName = jC->getInstanceName();
	}
	void addItemListener(ItemListener * iL);
	void addItemListener(ItemListener & iL);
};
JCheckBox::JCheckBox(string s)
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,0,JCheckBox," + s);
	jComps.push_back(*this);
}
void JCheckBox::addItemListener(ItemListener * iL)
{
	c.gui.push_back(instanceName + ",addItemListener");
	storedILs[stoi(instanceName)] = iL;
}
void JCheckBox::addItemListener(ItemListener & iL)
{
	c.gui.push_back(instanceName + ",addItemListener");
	storedILs[stoi(instanceName)] = &iL;
}

class ButtonGroup
{
public:
	ButtonGroup();
	//void add(JRadioButton	jrb);
	void add(JRadioButton * jrb);
	void add(JRadioButton & jrb);
	void add(JCheckBox * jcb);
	void add(JCheckBox & jcb);
	void setInstanceName();
	string instanceName;
};
vector<ButtonGroup> Bgroups;

ButtonGroup::ButtonGroup()
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,0,ButtonGroup");
	Bgroups.push_back(*this);
	//jComps.push_back(*this);
}
//void ButtonGroup::add(JRadioButton jrb)
//{
//	c.gui.push_back(instanceName + ",addToButtonGroup," + jrb.getInstanceName);
//}
void ButtonGroup::add(JRadioButton * jrb)
{
	c.gui.push_back(instanceName + ",addToButtonGroup," + jrb->getInstanceName());

}
void ButtonGroup::add(JRadioButton & jrb)
{
	c.gui.push_back(instanceName + ",addToButtonGroup," + jrb.getInstanceName());

}
void ButtonGroup::add(JCheckBox * jcb)
{
	c.gui.push_back(instanceName + ",addToButtonGroup," + jcb->getInstanceName());

}
void ButtonGroup::add(JCheckBox & jcb)
{
	c.gui.push_back(instanceName + ",addToButtonGroup," + jcb.getInstanceName());

}
void ButtonGroup::setInstanceName()
{
	instanceName = to_string(c.instanceCounter2);
	c.instanceCounter2++;
}



class ActionEvent
{
public:
	ActionEvent(int jc);
	JComponent getSource();
	int jC;
};

ActionEvent::ActionEvent(int jc)
{
	jC = jc;
}
JComponent ActionEvent::getSource()
{
	return (jComps[jC]);
}

class ActionListener
{
public:
	//ActionListener() {};
	//ActionListener(const ActionListener & copy) {};
	virtual void actionPerformed(ActionEvent ae) { /*cout << "calling original!" << endl;*/ }
	virtual void actionPerformed(ActionEvent * ae) {};
};

vector<ActionListener *> storedALs(64);



#if defined(_WIN32) || defined(_WIN64)
DWORD WINAPI InstanceThread(LPVOID);
VOID GetAnswerToRequest(LPTSTR, LPTSTR, LPDWORD);
#endif

int startListeningToJava()
{
#if defined(_WIN32) || defined(_WIN64)
	BOOL   fConnected = FALSE;
	DWORD  dwThreadId = 0;
	HANDLE hPipe = INVALID_HANDLE_VALUE, hThread = NULL;
	LPTSTR lpszPipename = TEXT("\\\\.\\pipe\\Java2Cpp");

	// The main loop creates an instance of the named pipe and 
	// then waits for a client to connect to it. When the client 
	// connects, a thread is created to handle communications 
	// with that client, and this loop is free to wait for the
	// next client connect request. It is an infinite loop.

	//_tprintf(TEXT("\nPipe Server: Main thread awaiting client connection on %s\n"), lpszPipename);
	hPipe = CreateNamedPipe(
		lpszPipename,             // pipe name 
		PIPE_ACCESS_DUPLEX,       // read/write access 
		PIPE_TYPE_MESSAGE |       // message type pipe 
		PIPE_READMODE_MESSAGE |   // message-read mode 
		PIPE_WAIT,                // blocking mode 
		PIPE_UNLIMITED_INSTANCES, // max. instances  
		BUFSIZE,                  // output buffer size 
		BUFSIZE,                  // input buffer size 
		0,                        // client time-out 
		NULL);                    // default security attribute 

	if (hPipe == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("CreateNamedPipe failed, GLE=%d.\n"), GetLastError());
		return -1;
	}

	// Wait for the client to connect; if it succeeds, 
	// the function returns a nonzero value. If the function
	// returns zero, GetLastError returns ERROR_PIPE_CONNECTED. 

	fConnected = ConnectNamedPipe(hPipe, NULL) ?
		TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

	if (fConnected)
	{
		//printf("Client connected, creating a processing thread.\n");

		//cout << "Successfully connected to Java." << endl;
		// Create a thread for this client. 
		hThread = CreateThread(
			NULL,              // no security attribute 
			0,                 // default stack size 
			InstanceThread,    // thread proc
			(LPVOID)hPipe,    // thread parameter 
			0,                 // not suspended 
			&dwThreadId);      // returns thread ID 

		if (hThread == NULL)
		{
			_tprintf(TEXT("CreateThread failed, GLE=%d.\n"), GetLastError());
			return -1;
		}
		else CloseHandle(hThread);
	}
	else
		// The client could not connect, so close the pipe. 
		CloseHandle(hPipe);

	return 0;
}

DWORD WINAPI InstanceThread(LPVOID lpvParam)
// This routine is a thread processing function to read from and reply to a client
// via the open pipe connection passed from the main loop. Note this allows
// the main loop to continue executing, potentially creating more threads of
// of this procedure to run concurrently, depending on the number of incoming
// client connections.
{
	HANDLE hHeap = GetProcessHeap();
	//TCHAR* pchRequest = (TCHAR*)HeapAlloc(hHeap, 0, BUFSIZE*sizeof(TCHAR));
	char pchRequest[64];
	TCHAR* pchReply = (TCHAR*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(TCHAR));

	DWORD cbBytesRead = 0, cbReplyBytes = 0, cbWritten = 0;
	BOOL fSuccess = FALSE;
	HANDLE hPipe = NULL;

	// Do some extra error checking since the app will keep running even if this
	// thread fails.

	if (lpvParam == NULL)
	{
		/*printf("\nERROR - Pipe Server Failure:\n");
		printf("   InstanceThread got an unexpected NULL value in lpvParam.\n");
		printf("   InstanceThread exitting.\n");*/
		if (pchReply != NULL) HeapFree(hHeap, 0, pchReply);
		if (pchRequest != NULL) HeapFree(hHeap, 0, pchRequest);
		return (DWORD)-1;
	}

	if (pchRequest == NULL)
	{
		/*printf("\nERROR - Pipe Server Failure:\n");
		printf("   InstanceThread got an unexpected NULL heap allocation.\n");
		printf("   InstanceThread exitting.\n");*/
		if (pchReply != NULL) HeapFree(hHeap, 0, pchReply);
		return (DWORD)-1;
	}

	if (pchReply == NULL)
	{
		/*printf("\nERROR - Pipe Server Failure:\n");
		printf("   InstanceThread got an unexpected NULL heap allocation.\n");
		printf("   InstanceThread exitting.\n");*/
		if (pchRequest != NULL) HeapFree(hHeap, 0, pchRequest);
		return (DWORD)-1;
	}

	// Print verbose messages. In production code, this should be for debugging only.
	//printf("InstanceThread created, receiving and processing messages.\n");

	// The thread's parameter is a handle to a pipe object instance. 

	hPipe = (HANDLE)lpvParam;

	std::cout << "Successfully connected to Java." << endl;
	// Loop until done reading
	while (1)
	{
		// Read client requests from the pipe. This simplistic code only allows messages
		// up to BUFSIZE characters in length.
		fSuccess = ReadFile(
			hPipe,        // handle to pipe 
			pchRequest,    // buffer to receive data 
			64 * sizeof(char), // size of buffer 
			&cbBytesRead, // number of bytes read 
			NULL);        // not overlapped I/O 

		if (!fSuccess || cbBytesRead == 0)
		{
			if (GetLastError() == ERROR_BROKEN_PIPE)
			{
				_tprintf(TEXT("InstanceThread: client disconnected.\n"), GetLastError());
			}
			else
			{
				_tprintf(TEXT("InstanceThread ReadFile failed, GLE=%d.\n"), GetLastError());
			}
			break;
		}

		//cout << "printing:" << pchRequest << endl;

		string command = "";
		for (char c : pchRequest)
		{
			if (c == '~')
				break;
			command += c;
		}
		//cout << "printing2:" << command << endl;
		string CC(command);
		size_t pos = 0;
		string token;
		vector<string> JavaCommand;
		string delimiter = ",";
		command += ",";
		while ((pos = command.find(delimiter)) != string::npos) {
			token = command.substr(0, pos);
			JavaCommand.push_back(token);
			command.erase(0, pos + delimiter.length());
		}

		/*for (string s : JavaCommand)
		{
		cout << s << " ";
		}
		cout << endl;*/

		//storedKL->keyReleased(*new KeyEvent(CC.at(12)));
		//cout << "press2" << endl;
		switch (stoi(JavaCommand.at(0)))
		{
		case -1:
			if (JavaCommand.at(1).compare("KeyEvent") == 0) //Key Listeners
			{
				// Use Java Command vector to call commands here
				storedKL->keyReleased(*new KeyEvent(JavaCommand.at(2).at(0)));
				/*std::cout << "press ";
				std::cout << JavaCommand.at(2) << endl;*/

			}
			else if (JavaCommand.at(1).compare("MouseEvent") == 0) //Mouse and MouseMotion Listeners
			{
				if (JavaCommand.at(2).compare("0") == 0)
				{
					storedML->mouseClicked(*new MouseEvent(stoi(JavaCommand.at(3)), stoi(JavaCommand.at(4)), stoi(JavaCommand.at(5)), stoi(JavaCommand.at(6))));
				}
				else
				{
					storedML->mousePressed(*new MouseEvent(stoi(JavaCommand.at(3)), stoi(JavaCommand.at(4)), stoi(JavaCommand.at(5)), stoi(JavaCommand.at(6))));
				}
			}
			else if (JavaCommand.at(1).compare("MouseMotionEvent") == 0) //Mouse Motion Listeners
			{
				if (JavaCommand.at(2).compare("0") == 0)
				{
					storedMML->mouseMoved(*new MouseMotionEvent(stoi(JavaCommand.at(3)), stoi(JavaCommand.at(4))));
				}
				else
				{
					storedMML->mouseDragged(*new MouseMotionEvent(stoi(JavaCommand.at(3)), stoi(JavaCommand.at(4))));
				}
			}
			//else if (JavaCommand.at(1).compare("MouseEvent") == 0) //Mouse and MouseMotion Listeners
			//{
			//	if (JavaCommand.at(2).compare("0") == 0)
			//	{
			//		ml1->mouseClicked(*new MouseEvent(stoi(JavaCommand.at(3)), stoi(JavaCommand.at(4)), stoi(JavaCommand.at(5)), stoi(JavaCommand.at(6))));
			//	}
			//	else
			//	{
			//		ml1->mousePressed(*new MouseEvent(stoi(JavaCommand.at(3)), stoi(JavaCommand.at(4)), stoi(JavaCommand.at(5)), stoi(JavaCommand.at(6))));
			//	}
			//}
			//else if (JavaCommand.at(1).compare("MouseMotionEvent") == 0) //Mouse Motion Listeners
			//{
			//	if (JavaCommand.at(2).compare("0") == 0)
			//	{
			//		mml1->mouseMoved(*new MouseMotionEvent(stoi(JavaCommand.at(3)), stoi(JavaCommand.at(4))));
			//	}
			//	else
			//	{
			//		mml1->mouseDragged(*new MouseMotionEvent(stoi(JavaCommand.at(3)), stoi(JavaCommand.at(4))));
			//	}
			//}
			break;
		case 0:
			//Action Listeners
			//cout << "called case 0 " << endl;

			if (JavaCommand.at(2).compare("ActionPerformed") == 0)
			{
				storedALs[stoi(JavaCommand.at(1))]
					->
					actionPerformed(
						*new ActionEvent(
							stoi(
								jComps.at(stoi(JavaCommand.at(1))).getInstanceName()
							)
						)
					);
			}
			break;
		case 1:
			//Item Listeners

			if (JavaCommand.at(2).compare("itemStateChanged") == 0)
			{
				storedILs[stoi(JavaCommand.at(1))]
					->
					itemStateChanged(
						*new ItemEvent(
							stoi(
								jComps.at(stoi(JavaCommand.at(1))).getInstanceName()
							), stoi(JavaCommand.at(3))
						)
					);
			}
			break;
		default:
			break;
		}
		//cout << "here!!!R" << endl;
		// Process the incoming message.
		//GetAnswerToRequest(pchRequest, pchReply, &cbReplyBytes);

		// Write the reply to the pipe. 
		//fSuccess = WriteFile(
		//	hPipe,        // handle to pipe 
		//	pchReply,     // buffer to write from 
		//	cbReplyBytes, // number of bytes to write 
		//	&cbWritten,   // number of bytes written 
		//	NULL);        // not overlapped I/O 

		//if (!fSuccess || cbReplyBytes != cbWritten)
		//{
		//	_tprintf(TEXT("InstanceThread WriteFile failed, GLE=%d.\n"), GetLastError());
		//	break;
		//}
		FlushFileBuffers(hPipe);

	}

	// Flush the pipe to allow the client to read the pipe's contents 
	// before disconnecting. Then disconnect the pipe, and close the 
	// handle to this pipe instance. 


	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);

	HeapFree(hHeap, 0, pchRequest);
	HeapFree(hHeap, 0, pchReply);

	//printf("InstanceThread exitting.\n");
	return 1;

	//END WINDOWS CODE 


	//START UNIX CODE
#elif __unix || __unix__ || __APPLE__ || __MACH__ || __linux__

	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)
	// UNIX CODE (Erik)

#else
#endif // END UNIX CODE

}

//Some more WINDOWS-ONLY code

#if defined(_WIN32) || defined(_WIN64)

VOID GetAnswerToRequest(LPTSTR pchRequest,
	LPTSTR pchReply,
	LPDWORD pchBytes)
	// This routine is a simple function to print the client request to the console
	// and populate the reply buffer with a default data string. This is where you
	// would put the actual client request processing code that runs in the context
	// of an instance thread. Keep in mind the main thread will continue to wait for
	// and receive other client connections while the instance thread is working.
{
	_tprintf(TEXT("Client Request String:\"%s\"\n"), pchRequest);

	// Check the outgoing message to make sure it's not too long for the buffer.
	if (FAILED(StringCchCopy(pchReply, BUFSIZE, TEXT("default answer from server"))))
	{
		*pchBytes = 0;
		pchReply[0] = 0;
		//printf("StringCchCopy failed, no outgoing message.\n");
		return;
	}
	*pchBytes = (lstrlen(pchReply) + 1) * sizeof(TCHAR);

}

#endif

class JPanel : public JComponent {
public:
	JPanel();
	void setLayout(GridLayout* gl);
	void setLayout(BorderLayout* bl);
	void add(JComponent& jc);
	void add(JComponent& jc, string layout);
	void addMouseListener(MouseListener * mL);
	void addMouseListener(MouseListener & mL);
	void addMouseMotionListener(MouseMotionListener * mmL);
	void addMouseMotionListener(MouseMotionListener & mmL);
};
JPanel::JPanel() //0
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,0,JPanel");
	jComps.push_back(*this);
}
void JPanel::setLayout(GridLayout* gl)
{
	if (gl->getLayoutType() == "GridLayout,0")
		c.gui.push_back(instanceName + ",setLayout," + gl->getLayoutType() + "," + to_string(gl->numRows) + "," + to_string(gl->numCols));
	else
		c.gui.push_back(instanceName + ",setLayout," + gl->getLayoutType() + "," + to_string(gl->numRows) + "," + to_string(gl->numCols) + "," + to_string(gl->horzontalGap) + "," + to_string(gl->verticalGap));
}
void JPanel::setLayout(BorderLayout* bl)
{
	if (bl->getLayoutType() == "BorderLayout,0")
		c.gui.push_back(instanceName + ",setLayout," + bl->getLayoutType());
	else
		c.gui.push_back(instanceName + ",setLayout," + bl->getLayoutType() + "," + to_string(bl->horizontalGap) + "," + to_string(bl->verticalGap));
}
void JPanel::add(JComponent& jc)
{
	c.gui.push_back(instanceName + ",add," + jc.getInstanceName());
}
void JPanel::add(JComponent& jc, string layout)
{
	c.gui.push_back(instanceName + ",add," + jc.getInstanceName() + "," + layout);
}

//void JPanel::addMouseListener(MouseListener * mL)
//{
//	c.gui.push_back(instanceName + ",addMouseListener");
//	storedML = mL;
//}
//void JPanel::addMouseListener(MouseListener & mL)
//{
//	c.gui.push_back(instanceName + ",addMouseListener");
//	storedML = &mL;
//}
//void JPanel::addMouseMotionListener(MouseMotionListener * mmL)
//{
//	c.gui.push_back(instanceName + ",addMouseMotionListener");
//	storedMML = mmL;
//}
//void JPanel::addMouseMotionListener(MouseMotionListener & mmL)
//{
//	c.gui.push_back(instanceName + ",addMouseMotionListener");
//	storedMML = &mmL;
//}
void JPanel::addMouseListener(MouseListener * mL)
{
	c.gui.push_back(instanceName + ",addMouseListener");
	storedML = mL;
}
void JPanel::addMouseListener(MouseListener & mL)
{
	c.gui.push_back(instanceName + ",addMouseListener");
	storedML = &mL;
}
void JPanel::addMouseMotionListener(MouseMotionListener * mmL)
{
	c.gui.push_back(instanceName + ",addMouseMotionListener");
	storedMML = mmL;
}
void JPanel::addMouseMotionListener(MouseMotionListener & mmL)
{
	c.gui.push_back(instanceName + ",addMouseMotionListener");
	storedMML = &mmL;
}

class JLabel : public JComponent {
public:
	JLabel(string s);
	JLabel(string s, int alignment);
	JLabel(Image image);
	void setText(string s);
	void addMouseListener(MouseListener * mL);
	void addMouseListener(MouseListener & mL);
	void addMouseMotionListener(MouseMotionListener * mmL);
	void addMouseMotionListener(MouseMotionListener & mmL);
};
JLabel::JLabel(string s) //0
{
	setInstanceName();
	string n;
	for (char i : s)
		if (i != ',')
			n += i;
	c.gui.push_back(instanceName + ",instantiate,0,JLabel," + n);
	jComps.push_back(*this);

}
JLabel::JLabel(string s, int alignment) //1
{
	setInstanceName();
	string n;
	for (char i : s)
		if (i != ',')
			n += i;
	c.gui.push_back(instanceName + ",instantiate,1,JLabel," + n + "," + to_string(alignment));
	jComps.push_back(*this);
}
JLabel::JLabel(Image image)
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instance,2,JLabel," + image.filename);
	jComps.push_back(*this);
}
void JLabel::setText(string s)
{
	string n;
	for (char i : s)
		if (i != ',')
			n += i;
	c.gui.push_back(instanceName + ",setTextJL," + n);
}
//void JLabel::addMouseListener(MouseListener * mL)
//{
//	c.gui.push_back(instanceName + ",addMouseListener");
//	ml1 = mL;
//}
//void JLabel::addMouseListener(MouseListener & mL)
//{
//	c.gui.push_back(instanceName + ",addMouseListener");
//	ml1 = &mL;
//}
//void JLabel::addMouseMotionListener(MouseMotionListener * mmL)
//{
//	c.gui.push_back(instanceName + ",addMouseMotionListener");
//	mml1 = mmL;
//}
//void JLabel::addMouseMotionListener(MouseMotionListener & mmL)
//{
//	c.gui.push_back(instanceName + ",addMouseMotionListener");
//	mml1 = &mmL;
//}
void JLabel::addMouseListener(MouseListener * mL)
{
	c.gui.push_back(instanceName + ",addMouseListener");
	storedML = mL;
}
void JLabel::addMouseListener(MouseListener & mL)
{
	c.gui.push_back(instanceName + ",addMouseListener");
	storedML = &mL;
}
void JLabel::addMouseMotionListener(MouseMotionListener * mmL)
{
	c.gui.push_back(instanceName + ",addMouseMotionListener");
	storedMML = mmL;
}
void JLabel::addMouseMotionListener(MouseMotionListener & mmL)
{
	c.gui.push_back(instanceName + ",addMouseMotionListener");
	storedMML = &mmL;
}

class JTextField : public JComponent {
public:
	JTextField(JTextField & copy) {
		instanceName = copy.instanceName;
	};
	bool operator==(JTextField & jtf)
	{
		return instanceName.compare(jtf.instanceName) == 0;
	}
	bool operator==(JComponent & jC)
	{
		return instanceName.compare(jC.getInstanceName()) == 0;
	}
	void operator = (JComponent & jC)
	{
		instanceName = jC.getInstanceName();
	}
	void operator = (JComponent * jC)
	{
		instanceName = jC->getInstanceName();
	}
	JTextField(string text, int numCol);
	JTextField(int numCol);
	void setEditable(bool mode);
	void setText(string newText);
	void addActionListener(ActionListener * aL);
	void addActionListener(ActionListener & aL);
};
JTextField::JTextField(string text, int numCol) //0
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,0,JTextField," + text + "," + to_string(numCol));
	jComps.push_back(*this);
}
JTextField::JTextField(int numCol) //1
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,1,JTextField," + to_string(numCol));
	jComps.push_back(*this);
}
void JTextField::setEditable(bool mode)
{
	c.gui.push_back(instanceName + ",setEditable," + to_string(mode));
}
void JTextField::setText(string newText)
{
	string n;
	for (char i : newText)
		if (i != ',')
			n += i;
	c.gui.push_back(instanceName + ",setTextJTF," + n);
}
void JTextField::addActionListener(ActionListener * aL)
{
	c.gui.push_back(instanceName + ",addActionListener");
	al1 = aL;
}
void JTextField::addActionListener(ActionListener & aL)
{
	c.gui.push_back(instanceName + ",addActionListener");
}

class JButton : public JComponent {
public:
	JButton(JButton & copy) {
		instanceName = copy.instanceName;
	};
	bool operator==(JButton & jB)
	{
		return instanceName.compare(jB.instanceName) == 0;
	}
	bool operator==(JComponent & jC)
	{
		return instanceName.compare(jC.getInstanceName()) == 0;
	}
	void operator = (JComponent & jC)
	{
		instanceName = jC.getInstanceName();
	}
	void operator = (JComponent * jC)
	{
		instanceName = jC->getInstanceName();
	}
	JButton();
	JButton(string text);
	void addActionListener(ActionListener * aL);
	void addActionListener(ActionListener & aL);
};
JButton::JButton() //0
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,0,JButton");
	jComps.push_back(*this);

}
JButton::JButton(string text) //1
{
	setInstanceName();
	string n;
	for (char i : text)
		if (i != ',')
			n += i;
	c.gui.push_back(instanceName + ",instantiate,1,JButton," + n);
	jComps.push_back(*this);

}
void JButton::addActionListener(ActionListener * aL)
{
	c.gui.push_back(instanceName + ",addActionListener");
	storedALs[stoi(instanceName)] = aL;
}
void JButton::addActionListener(ActionListener & aL)
{
	c.gui.push_back(instanceName + ",addActionListener");
	storedALs[stoi(instanceName)] = &aL;
}

class JTextArea : public JComponent {
public:
	JTextArea(string text);
	JTextArea(int numRows, int numCol);
	JTextArea(string text, int numRows, int numCol);
	void setEditable(bool mode);
	void setText(string newText);
};
JTextArea::JTextArea(string text) //0
{
	setInstanceName();
	string n;
	for (char i : text)
		if (i != ',')
			n += i;
	c.gui.push_back(instanceName + ",instantiate,0,JTextArea," + n);
	jComps.push_back(*this);
}
JTextArea::JTextArea(int numRows, int numCol) //1
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,1,JTextArea," + to_string(numRows) + "," + to_string(numCol));
	jComps.push_back(*this);
}
JTextArea::JTextArea(string text, int numRows, int numCol) //2
{
	setInstanceName();
	string n;
	for (char i : text)
		if (i != ',')
			n += i;
	c.gui.push_back(instanceName + ",instantiate,2,JTextArea," + n + "," + to_string(numRows) + "," + to_string(numCol));
	jComps.push_back(*this);
}
void JTextArea::setEditable(bool mode)
{
	c.gui.push_back(instanceName + ",setEditable," + to_string(mode));
}
void JTextArea::setText(string newText)
{
	string n;
	for (char i : newText)
		if (i != ',')
			n += i;
	c.gui.push_back(instanceName + ",setTextJTA," + n);
}

class JComboBox : public JComponent
{
public:
	JComboBox(string items[]);
};
JComboBox::JComboBox(string items[])
{
	/*cout << "here" << endl;*/
	//cout << "here" << endl;
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,0,JComboBox");
	for (int i = 0; i < sizeof(items); i++)
	{
		//cout << items[i] << endl;
		c.gui.push_back(instanceName + ",addItemToComboBox," + items[i]);
	}
	jComps.push_back(*this);
}






class Cpp2Java {
public:
	Cpp2Java()
	{
		removeAll();
	}
	Cpp2Java(int width, int height) {

		removeAll();
		c.gui.push_back("-1,setFrameSize," + to_string(width) + "," + to_string(height));
	};
	void removeAll();
	void update();
	void finish();
	//void pause(double ld);
	void setLayout(GridLayout* gl);
	void setLayout(BorderLayout* bl);
	void addKeyListener(KeyListener * kL);
	void addKeyListener(KeyListener & kL);
	void add(JComponent& jc);
	void add(JComponent& jc, string layout);
	ofstream file;
	ofstream file1;
};

void Cpp2Java::removeAll()
{
	c.gui.push_back("-1,removeAll");

	//might need to move this to finish()
}
void Cpp2Java::update()
{
	sendCommandsThroughPipe(c.gui, L"Cpp2Java_gui");
	c.gui.clear();
}
void Cpp2Java::finish()
{
	sendCommandsThroughPipe(c.gui, L"Cpp2Java_gui");
	c.gui.clear();

	// Loop phase
	startListeningToJava();
	while (1); // Continue listening.
			   // Without this inf. loop, program would end.
}

//void Cpp2Java::pause(double ld)
//{
//	typedef std::chrono::duration<double> seconds_type;
//	if (ld > .01)
//	{
//		seconds_type period(ld);
//		this_thread::sleep_for(period);
//	}
//	else
//	{
//		seconds_type period(.01);
//		this_thread::sleep_for(period);
//	}
//}
void Cpp2Java::setLayout(GridLayout* gl)
{
	if (gl->getLayoutType() == "GridLayout,0")
		c.gui.push_back("-1,setContainerLayout," + gl->getLayoutType() + "," + to_string(gl->numRows) + "," + to_string(gl->numCols));
	else
		c.gui.push_back("-1,setContainerLayout," + gl->getLayoutType() + "," + to_string(gl->numRows) + "," + to_string(gl->numCols) + "," + to_string(gl->horzontalGap) + "," + to_string(gl->verticalGap));
}
void Cpp2Java::setLayout(BorderLayout* bl)
{
	if (bl->getLayoutType() == "BorderLayout,0")
		c.gui.push_back("-1,setContainerLayout," + bl->getLayoutType());
	else
		c.gui.push_back("-1,setContainerLayout," + bl->getLayoutType() + "," + to_string(bl->horizontalGap) + "," + to_string(bl->verticalGap));
}
void Cpp2Java::addKeyListener(KeyListener * kL)
{
	c.gui.push_back("-1,addKeyListener");

	storedKL = kL;
}
void Cpp2Java::addKeyListener(KeyListener & kL)
{
	c.gui.push_back("-1,addKeyListener");

	storedKL = &kL;
}
void Cpp2Java::add(JComponent& jc)
{
	c.gui.push_back("-1,addContainer," + jc.getInstanceName());
}
void Cpp2Java::add(JComponent& jc, string layout)
{
	c.gui.push_back("-1,addContainer," + jc.getInstanceName() + "," + layout);
}
ostream& operator<<(ostream& os, Cpp2Java* jC)
{
	os << "Cpp2Java";
	return os;
}
ostream& operator<<(ostream& os, Cpp2Java jC)
{
	os << "Cpp2Java";
	return os;
}

#endif // !CPP2JAVA_H
