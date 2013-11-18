#ifndef BEHAVIORAL_H
#define BEHAVIORAL_H

//////////////////////////////////Chain of responsibility//////////////////////////////////////////////////
typedef int Topic;
const Topic NO_HELP_TOPIC = -1;
class HelpHandler
{
public:
	HelpHandler(HelpHandler* = 0, Topic = NO_HELP_TOPIC);

	virtual bool HasHelp();

	virtual void SetHandler(HelpHandler*, Topic)
	{

	}

	virtual void HandleHelp();

private:
	HelpHandler* _successor;
	Topic _topic;
};

HelpHandler::HelpHandler(HelpHandler* h, Topic t) :
		_successor(h), _topic(t)
{
}
bool HelpHandler::HasHelp()
{
	return _topic != NO_HELP_TOPIC;
}
void HelpHandler::HandleHelp()
{
	if (_successor != 0)
	{
		_successor->HandleHelp();
	}
}

class Widget: public HelpHandler
{
protected:
	Widget(Widget* parent, Topic t = NO_HELP_TOPIC);
private:
	Widget* _parent;
};
Widget::Widget(Widget* w, Topic t) :
		HelpHandler(w, t)
{
	_parent = w;
}

class Button: public Widget
{
public:
	Button(Widget* d, Topic t = NO_HELP_TOPIC);
	virtual void HandleHelp();
// Widget operations that Button overrides...
};

Button::Button(Widget* h, Topic t) :
		Widget(h, t)
{
}
void Button::HandleHelp()
{
	if (HasHelp())
	{
		// offer help on the button
	}
	else
	{
		HelpHandler::HandleHelp();
	}
}

class Dialog: public Widget
{
public:
	Dialog(HelpHandler* h, Topic t = NO_HELP_TOPIC);
	virtual void HandleHelp();
// Widget operations that Dialog overrides...
// ...
};
Dialog::Dialog(HelpHandler* h, Topic t) :
		Widget(0)
{
	SetHandler(h, t);
}
void Dialog::HandleHelp()
{
	if (HasHelp())
	{
// offer help on the dialog
	}
	else
	{
		HelpHandler::HandleHelp();
	}
}

const Topic PRINT_TOPIC = 1;
const Topic PAPER_ORIENTATION_TOPIC = 2;
const Topic APPLICATION_TOPIC = 3;

class Application: public HelpHandler
{
public:
	Application(Topic t) :
			HelpHandler(0, t)
	{
	}
	virtual void HandleHelp();
// application-specific operations...
};
void Application::HandleHelp()
{
// show a list of help topics
}

///////////////////////////////////Command pattern /////////////////////////////////////////////

class Document
{
public:
	void Paste()
	{

	}
};

class Command
{
public:
	virtual ~Command()
	{

	}
	virtual void Execute() = 0;
protected:
	Command()
	{

	}
};

class MenuItem
{
public:

	MenuItem(Command* command) :
		m_command(command)
	{

	}

	void onButtonClick()
	{

	}

private:
	Command* m_command;
};


class PasteCommand: public Command
{
public:
	PasteCommand(Document*);
	virtual void Execute();
private:
	Document* _document;
};
PasteCommand::PasteCommand(Document* doc)
{
	_document = doc;
}
void PasteCommand::Execute()
{
	_document->Paste();
}

////////////////////////////////Iterator Pattern/////////////////////////////////////////////////////////////////////

class Container;

class Iterator
{

public:
	Iterator()
	{

	}
	virtual void first()= 0;
	virtual void next()= 0;
	virtual int getCurrentItenm()= 0;
	virtual bool isDone()= 0;

};

class Container
{
public:
	virtual Iterator* createIterator()= 0;

	virtual ~Container()
	{

	}
};

struct ListNode;

struct ListNode
{
	int data;
	ListNode* psNext;
};

class ListContainer: public Container
{

public:

	ListContainer() :
		m_currentNode(NULL),
		m_head(NULL),
		m_tail(NULL)
	{

	}

	Iterator* createIterator();

	void push(int data);

	int pop();

private:
	ListNode* m_currentNode;
	ListNode* m_head;
	ListNode* m_tail;
	friend class ListIterator;
};


class ListIterator: public Iterator
{
public:
	ListIterator(ListContainer* cont) :
		m_listContainer(cont)
	{

	}

	void first()
	{
		m_listContainer->m_currentNode= m_listContainer->m_head;
	}
	void next()
	{
		if(m_listContainer->m_currentNode)
		{
			m_listContainer->m_currentNode= m_listContainer->m_currentNode->psNext;
		}
	}
	int getCurrentItenm()
	{
		if(m_listContainer->m_currentNode)
		{
			return m_listContainer->m_currentNode->data;
		}
		else
		{
			return -1;
		}
	}
	bool isDone()
	{
		if (m_listContainer->m_currentNode == m_listContainer->m_tail)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	ListContainer* m_listContainer;

};

Iterator* ListContainer::createIterator()
{
	return new ListIterator(this);
}

void ListContainer::push(int data)
{
	if (m_currentNode == NULL)
	{
		m_currentNode = new ListNode();
		m_currentNode->data = data;
		m_head = m_currentNode;
		m_tail = m_currentNode;
	}
	else
	{
		ListNode* newNode = new ListNode();
		newNode->data = data;

		m_currentNode->psNext = newNode;
		m_tail = m_currentNode->psNext;
		m_currentNode = m_currentNode->psNext;
	}
}

int ListContainer::pop()
{
	int data = -1;
	if (m_head)
	{
		ListNode* currentNode = m_head;

		data = currentNode->data;
		m_head = m_head->psNext;

		delete currentNode;
	}

	return data;
}

//////////////////////////////////////Memento//////////////////////////////////////////////////////////

class State
{
public:
	int xCoordinate;
	int yCooridanate;
};

class Memento;

class Originator
{
public:
	Memento* CreateMemento();
	void SetMemento(const Memento*);
	void ChangeState()
	{

	}
// ...
private:
	State* _state;
// internal data structures
// ...
};

class Memento
{
public:
	// narrow public interface
	virtual ~Memento()
	{

	}
private:
	// private members accessible only to Originator
	friend class Originator;
	Memento() :
		_state(NULL)
	{

	}
	void SetState(State* state)
	{
		_state= state;
	}
	State* GetState() const
	{
		return _state;
	}
// ...
private:
	State* _state;
// ...
};

Memento* Originator::CreateMemento()
{
	Memento* memento= new Memento();
	memento->SetState(_state);
	return memento;
}

void Originator::SetMemento(const Memento* memento)
{
	_state= memento->GetState();
}

//////////////////////////////Observer pattern////////////////////////////////////////////////////////

class Subject;

class Observer
{
public:
	virtual ~ Observer()
	{

	}
	virtual void Update(Subject* theChangedSubject) = 0;
protected:
	Observer()
	{

	}
};


class Subject
{
public:
	virtual ~Subject();
	virtual void Attach(Observer* obs)
	{
		_observers->push_back(obs);
	}
	virtual void Detach(Observer* obs)
	{
		_observers->remove(obs);
	}
	virtual void Notify()
	{
		std::list<Observer*>::iterator it;
		for(it= _observers->begin(); it != _observers->end(); ++it)
		{

		}
	}
protected:
	Subject();
private:
	std::list<Observer*>* _observers;
};

class ClockTimer : public Subject {
public:
         ClockTimer();
         virtual int GetHour()
         {
        	 return 1;
         }
         virtual int GetMinute()
         {
        	 return 0;
         }
         virtual int GetSecond()
         {
        	 return 2;
         }

         //notify all the observers
         void Tick()
         {
        	 Notify();
         }
};

class TimeObServer: public Observer
{
public:
	virtual ~ TimeObServer()
	{

	}
	void Update(Subject* theChangedSubject)
	{
		ClockTimer* clockTimer= (ClockTimer*)theChangedSubject;
		clockTimer->GetHour();
	}
protected:
	TimeObServer() :
		Observer()
	{

	}
};

////////////////////////////////////State Pattern///////////////////////////////////////////////////////////

#if 0
class TCPOctetStream;
class TCPState;

class TCPConnection
{
public:
	TCPConnection();
	void ActiveOpen();
	void PassiveOpen();
	void Close();
	void Send();
	void Acknowledge();
	void Synchronize();
	void ProcessOctet(TCPOctetStream*);
private:
	friend class TCPState;
	void ChangeState(TCPState*);
private:
	TCPState* _state;
};

class TCPState
{
public:
	virtual void Transmit(TCPConnection*, TCPOctetStream*);
	virtual void ActiveOpen(TCPConnection*);
	virtual void PassiveOpen(TCPConnection*);
	virtual void Close(TCPConnection*);
	virtual void Synchronize(TCPConnection*);

	virtual void Acknowledge(TCPConnection*);
	virtual void Send(TCPConnection*);
protected:
	void ChangeState(TCPConnection*, TCPState*);
};

TCPConnection::TCPConnection()
{
	_state = TCPClosed::Instance();
}
void TCPConnection::ChangeState(TCPState* s)
{
	_state = s;
}
void TCPConnection::ActiveOpen()
{
	_state->ActiveOpen(this);
}
void TCPConnection::PassiveOpen()
{
	_state->PassiveOpen(this);
}
void TCPConnection::Close()
{
	_state->Close(this);
}
void TCPConnection::Acknowledge()
{
	_state->Acknowledge(this);
}

class TCPClosed : public TCPState {
public:
         static TCPState* Instance();
         virtual void ActiveOpen(TCPConnection*);
         virtual void PassiveOpen(TCPConnection*);
         // ...
};

void TCPClosed::ActiveOpen (TCPConnection* t) {
         // send SYN, receive SYN, ACK, etc.
         ChangeState(t, TCPEstablished::Instance());
}
void TCPClosed::PassiveOpen (TCPConnection* t) {
         ChangeState(t, TCPListen::Instance());
}
void TCPEstablished::Close (TCPConnection* t) {
         // send FIN, receive ACK of FIN
         ChangeState(t, TCPListen::Instance());
}
void TCPEstablished::Transmit ( TCPConnection* t, TCPOctetStream* o ) {
         t->ProcessOctet(o);
}
void TCPListen::Send (TCPConnection* t) {
         // send SYN, receive SYN, ACK, etc.
         ChangeState(t, TCPEstablished::Instance());
}
#endif

///////////////////////////////Template method///////////////////////////////////////////////////////


class Renderer
{

public:

	void display()
	{
		if (isVisible())
		{
			doDisplay();
		}
	}

private:
	virtual void doDisplay();

	virtual bool isVisible();

};


class WindowRenderer : public Renderer
{

private:
	virtual void doDisplay()
	{
		//write the concrete display
		return;
	}

	virtual bool isVisible()
	{
		return true;
	}

};

////////////////////////////////////////VISITOR PATTERN///////////////////////////////////////////////

class Motor;
class Brake;

class PriceVisitor
{
public:

	void displayPrice(Motor* motor);

	void displayPrice(Brake* brake);

};

class Equipments
{
public:
	Equipments(PriceVisitor* visitor) :
		m_priceVisitor(visitor)
	{

	}

public:

	virtual int getPrice()= 0;

	virtual void displayPrice()= 0;

protected:
	PriceVisitor* m_priceVisitor;
};

class Motor : public Equipments
{
public:

	Motor(PriceVisitor* visitor) : Equipments(visitor)
	{

	}

	int getPrice()
	{
		return 10;
	}

	void displayPrice()
	{
		m_priceVisitor->displayPrice(this);
	}
};

class Brake : public Equipments
{
public:

	Brake(PriceVisitor* visitor) : Equipments(visitor)
	{

	}

	int getPrice()
	{
		return 20;
	}

	void displayPrice()
	{
		m_priceVisitor->displayPrice(this);
	}
};

void PriceVisitor::displayPrice(Brake* brake)
{
	std::cout << "Brake price is " << brake->getPrice() << std::endl;
}

void PriceVisitor::displayPrice(Motor* motor)
{
	std::cout << "Motor price is " << motor->getPrice() << std::endl;
}


#endif
