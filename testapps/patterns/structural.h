/*
 * behavioral.h
 *
 *  Created on: Sep 5, 2013
 *      Author: dimitrios
 */

#ifndef BEHAVIORAL_H_
#define BEHAVIORAL_H_
#include<list>

///////////////////////////////////////ADAPTER//////////////////////////////////////////////////////////////////
class Point;
class Manipulator;
class Coord;

class Shape
{
public:
	Shape();
	virtual void BoundingBox(Point& bottomLeft, Point& topRight) const;
	virtual Manipulator* CreateManipulator() const;
	virtual ~Shape()
	{

	}
};

class TextView
{
public:
	TextView();
	void GetOrigin(Coord& x, Coord& y) const;
	void GetExtent(Coord& width, Coord& height) const;
	virtual bool IsEmpty() const;
	virtual ~TextView() {};
};

//adapts the TextView to be compatible with a shape class
class TextShape: public Shape, private TextView
{
public:
	TextShape();
	virtual void BoundingBox(Point& bottomLeft, Point& topRight) const;
	virtual bool IsEmpty() const;
	virtual Manipulator* CreateManipulator() const;
};

/////////////////////////////////BRIDGE///////////////////////////////////////////////////////////////////

class WindowImpl
{
public:
	virtual void devDrawText()= 0;

	virtual void devDrawRect()= 0;

	virtual ~WindowImpl()
	{
	};
};

class XWindow : public WindowImpl
{
public:
	void devDrawText()
	{

	}

	void devDrawRect()
	{

	}

	virtual ~XWindow()
	{

	};
};

class  Window
{
public:

	Window(WindowImpl* windowImpl):
		m_windowImpl(windowImpl)
	{

	}

	virtual void drawText()= 0;

	virtual void drawRect()= 0;

	virtual ~Window()
	{

	}

protected:
	WindowImpl* m_windowImpl;

};

class IconWindow: public Window
{
public:
	IconWindow(WindowImpl* windowImpl) :
			Window(windowImpl)
	{

	}
	void drawText()
	{
		m_windowImpl->devDrawText();
	}

	void drawRect()
	{
		m_windowImpl->devDrawRect();
	}

};

///////////////////////////////////Composite//////////////////////////////////////////////////////////////


class Equipment
{

public:
	virtual double power()= 0;

	virtual double price()= 0;

	virtual ~Equipment() { };
};

class Composite: public Equipment
{
public:
	virtual double power()= 0;

	virtual double price()= 0;

	virtual ~Composite() { } ;

	virtual void add(const Equipment* child)= 0;

	virtual void remove(const Equipment* child)= 0;

	virtual  const Equipment* getChild(int n)= 0;

};

class Engine: public Composite
{
public:
	double power()
	{
		return 3500.0;
	}

	double price()
	{
		return 3000;
	}

	virtual ~Engine(){};

	void add(const Equipment* child)
	{
		children.push_back(child);
	}

	void remove(const Equipment* child)
	{
		children.remove(child);
	}

	const Equipment* getChild(int n)
	{
		if (!children.empty())
		{
			return children.front();
		}
		else
		{
			return NULL;
		}

	}

private:
	std::list<const Equipment* > children;
};

class Sensor: public Equipment
{
public:
	double power()
	{
		return 3500.0;
	}

	double price()
	{
		return 3000;
	}

	virtual ~Sensor(){};

};

////////////////////////////////////////Decorator///////////////////////////////////////////////////////////

class VisualComponent
{

public:
	VisualComponent()
	{

	}

	virtual void draw()= 0;

	virtual void resize()= 0;

	virtual ~VisualComponent() { };

};

class GraphicView : public VisualComponent
{

public:
	GraphicView()
	{

	}

	virtual void draw()
	{
		//draw something
	}

	virtual void resize()
	{
		//resize it
	}

	virtual ~GraphicView() { };

};


class Decorator: public VisualComponent
{

public:
	Decorator(VisualComponent* component):
		m_component(component)
	{

	}

	virtual void draw()
	{
		m_component->draw();

		std::cout << "Drawing the graphic" << std::endl;
	}

	virtual void resize()
	{
		m_component->resize();
	}

private:
		VisualComponent* m_component;

};

class ScrollDecorator: public Decorator
{
public:
	ScrollDecorator(VisualComponent* component):
		Decorator(component)
	{

	}

	virtual void draw()
	{
		//adding some extra decoration here for scrolling
		//and then calling the parent
		Decorator::draw();

		std::cout << "adding scrolling " << std::endl;

	}

	virtual void resize()
	{
		//adding some scrolling specific resize operation
		//and then call the parent one
		Decorator::draw();
	}

};

class BorderDecorator: public Decorator
{
public:
	BorderDecorator(VisualComponent* component):
		Decorator(component)
	{

	}

	virtual void draw()
	{
		//adding some extra decoration here for scrolling
		//and then calling the parent
		Decorator::draw();

		std::cout << "adding border " << std::endl;
	}

	virtual void resize()
	{
		//adding some scrolling specific resize operation
		//and then call the parent one
		Decorator::draw();
	}

};

////////////////////////////////////Proxy pattern/////////////////////////////////////////////////////////

class Image
{
public:

	int getWidth()
	{
		return 12;
	}

	int getHeight()
	{
		return 10;
	}
};

class ImagePtr
{
public:
	ImagePtr(const char* imageFile) :
			m_imageFile(imageFile), m_image(NULL)
	{

	}
	virtual ~ImagePtr()
	{
		delete m_imageFile;
	}
	virtual Image* operator->()
	{
		return LoadImage();
	}
	virtual Image& operator*()
	{
		return *LoadImage();
	}
private:
	Image* LoadImage()
	{
		if (m_image == NULL)
		{
			//create the Image and return it;
			return NULL;
		}
		else
		{
			return m_image;
		}
	}
private:
	Image* m_image;
	const char* m_imageFile;
};


#endif /* BEHAVIORAL_H_ */
