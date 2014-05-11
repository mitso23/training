#ifndef DESIGNPATTERNS_H_
#define DESIGNPATTERNS_H_

/*
 * Singelton class
 */
class HAL
{
private:
	HAL()
	{
		std::cout << "HAL constructor" << std::endl;
	}

public:
	static HAL& getInstanse()
	{
		static HAL hal;
		std::cout << "get Instanse of HAL " << std::endl;
		return hal;
	}

	void getAudioMixEngine()
	{
		std::cout << "Getting the Audio Mix Engine " << std::endl;
	}

	~HAL()
	{
		std::cout << "Destroying HAL" << std::endl;
	}
};

//The implementation should be in a translation unit
static std::ostream& logFile()
{
	static std::ofstream log("test");
	return log;
}

#if 0
class Shape
{
private:
	//Make constructor private so noboady can create a Shape apart from the factory
	Shape() { };

public:
	virtual void draw()= 0;

	virtual ~Shape()
	{

	}

	//ShapeCreator need to be friend in order to create Shape
	friend ShapeCreator;
};

class Square : public Shape
{
	void draw()
	{
		std::cout << "Square draw";
	}
};

class ShapeCreator
{
public:
	//A very naive way for creating Factory class
	static Shape* createShape(std::string shape)
	{
		if (shape == "Square")
		{
			return new Square();
		}
		else
		{
			return NULL;
		}
	}
};
#endif

//Emulate virtual construction
class Shape
{
private:
	Shape* s;
	// Prevent copy-construction & operator=
	Shape(Shape&);
	Shape operator=(Shape&);

protected:
	Shape()
	{
		s = 0;
	};

public:

	Shape(std::string str);

	virtual void draw()
	{
		if (s)
		{
			s->draw();
		}
	}
	virtual void erase()
	{
		if (s)
		{
			s->erase();
		}
	}
	virtual void test()
	{
		if (s)
		{
			s->test();
		}
	};


	virtual ~Shape()
	{
		cout << "~Shape\n";
		if (s)
		{
			cout << "Making virtual call: ";
			s->erase(); // Virtual call
		}

		cout << "delete s: ";
		delete s; // The polymorphic deletion
	}

};

class Circle : public Shape
{
	void draw()
	{
		std::cout << "Drawing a circle" << std::endl;
	}

	~Circle()
	{
		std::cout << "Circle destructore called " << std::endl;
	}
};

Shape::Shape(std::string str)
{
	if (str == "Circle")
	{
		s = new Circle();
	}

	s->draw();

}

/////An example of the Observer pattern used to implement MVC pattern
class Observable;

class Observer
{
public:

	virtual void update(Observable* observable, void* args);

	virtual ~Observer()
	{

	}
};

class Observable
{
public:
	void registerObserver(Observer* obj)
	{
		observers.push_back(obj);
	}

	void notifyChanges()
	{
		if (!getChanged())
		{
			return;
		}

		for (std::vector<Observer*>::iterator it=observers.begin(); it != observers.end(); ++it)
		{
			(*it)->update(this, NULL);
		}
	}

protected:
	void setChanged()
	{
		hasChanged= true;
	}

	bool getChanged()
	{
		return hasChanged;
	}

private:
	std::vector<Observer*> observers;
	bool hasChanged;

};

class Document;

class ChartView : public Observer
{
	ChartView() :
		document(NULL)
	{
		//register with the observer
		//document->registerObserver(this);
	}

	void update(Observable* observable, void* args)
	{

	}

private:
	Document* document;

};

class WebView : public Observer
{
	void update(Observable* observable, void* args)
	{

	}
};

class Document : public Observable
{

	void databaseChanged()
	{
		//mark that something has changed
		setChanged();
	}

	void doWork()
	{
		notifyChanges();
	}
};

//An example of multiple dispatch(visitor pattern)
class Paper;
class Scissors;
class Rock;

typedef enum
{
	WIN,
	LOOSE,
	EQUAL

}outcome_t;

class Item
{
public:
	virtual outcome_t evaluate(Item* rhs);

	virtual outcome_t eval(Paper* paper);

	virtual outcome_t eval(Scissors* scissors);

	virtual outcome_t eval(Rock* rock);

	virtual ~Item()
	{

	}
};

class Paper : public Item
{
	outcome_t evaluate(Item* rhs)
	{
		return rhs->eval(this);
	}

protected:
	outcome_t eval(Paper* paper)
	{
		return EQUAL;
	}

	outcome_t eval(Scissors* scissors)
	{
		return LOOSE;
	}

	virtual outcome_t eval(Rock* rock);

	virtual ~Paper()
	{

	}
};

//Implementation of the Visitor pattern
class Ferrari;
class Mazerrati;

class PriceCalculator
{
public:
	virtual int calculate(Ferrari& ferrari);

	virtual int calculate(Mazerrati& mazzerati);

	virtual ~PriceCalculator()
	{

	}
};


class SimplePriceCalculator : public PriceCalculator
{
public:

	virtual int  calculate(Ferrari& ferrari)
	{
		return 0;
	}

	virtual int calculate(Mazerrati& mazzerati)
	{
		return 1;
	}

	virtual ~SimplePriceCalculator()
	{

	}
};

class Car
{
public:
	virtual void calculatePrise(PriceCalculator& price);

	virtual ~Car()
	{

	}
};

class Ferrari
{
	void calculatePrise(PriceCalculator& price)
	{
		price.calculate(*this);
	}
};


class Mazerrati
{
	void calculatePrise(PriceCalculator& price)
	{
		price.calculate(*this);
	}
};

class Aluminium;
class Paper;

class Visitor
{
public:

	virtual void visit(Aluminium* aluminium);

	virtual void visit(Paper* paper);

	virtual ~Visitor() { };
};


class Trash
{
protected:
	Trash() : m_data(NULL), m_sizeData(0)
	{

	}

	/*
	 * Trash x=y;
	 */
	Trash(const Trash& rhs)
	{
		try
		{
			m_data= new int[rhs.m_sizeData];
			m_sizeData= rhs.m_sizeData;
		}
		catch(...)
		{
			throw;
		}
	}

	/*
	 * Trash x;
	 * Trash y;
	 * x= y;
	 */
	Trash& operator=(const Trash& rhs)
	{
		try
		{
			int* newData= new int[rhs.m_sizeData];
			int newSize= rhs.m_sizeData;

			memcpy(newData, rhs.m_data, m_sizeData);

			delete [] m_data;
			m_data= newData;
			m_sizeData= newSize;

			return *this;
		}
		catch (...)
		{
			throw;
		}

	}

public:

	virtual Trash* clone()= 0;

	virtual int getWeight() const = 0;

	virtual int getCost() const = 0;

	virtual ~Trash()
	{
		delete m_data;
		m_data= NULL;
	};

private:
	int* m_data;
	int m_sizeData;
};

//We can still provide default implementation for pure virtual functions
int Trash::getCost() const
{
	return 10;
}

class Aluminium : public Trash
{
public:

	Aluminium() : Trash(), m_trashType(0)
	{

	}

	Aluminium(const Aluminium& rhs) : Trash(*this), m_trashType(0)
	{
		m_trashType= rhs.m_trashType;
	}

	Aluminium& operator= (const Aluminium& rhs)
	{
		Trash::operator =(rhs);
		m_trashType= rhs.m_trashType;

		return *this;
	}

	Trash* clone()
	{
		return new Aluminium();
	}

	int getWeight() const
	{
		return 10;
	}

	int getCost() const
	{
		return Trash::getCost();
	}

private:
	int m_trashType;
};

#if 0
class Tbin : protected std::vector<Trash*>
{
public:
	virtual bool grub(Trash*)= 0;

	virtual ~Tbin() { };
};

template<typename TrashType>
class TrashBin : public Tbin
{
	bool grub(Trash* trash)
	{
		if (dynamic_cast<TrashType>(trash))
		{
			push_back(trash);
			return true;
		}
		else
		{
			return false;
		}
	}
};

class TrashSorter : protected std::vector<Tbin*>
{
	bool sort(Trash* bin)
	{
		for(std::vector<Tbin*>::const_iterator it=begin(); it != end(); ++it)
		{
			if ((*it)->grub(bin))
			{
				return true;
			}
		}

		return false;
	}

	void sort(const std::vector<Trash*>& bin)
	{
		for(std::vector<Trash*>::iterator it=bin.begin(); it != bin.end(); ++it)
		{
			if (!sort(*it))
			{
				std::cerr << "Failed to sort item" << std::endl;
			}
		}
	}
};
#endif


#endif /* DESIGNPATTERNS_H_ */
