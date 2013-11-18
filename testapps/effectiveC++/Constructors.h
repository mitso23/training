/*
 * Constructors.h
 *
 *  Created on: Oct 23, 2013
 *      Author: dimitrios
 */

#ifndef CONSTRUCTORS_H_
#define CONSTRUCTORS_H_


#include<iostream>
#include<stdio.h>
#include<string.h>
#include<vector>


class GamePlayer
{
public:
	enum { NUM_TURNS= 5 };
	static const int NumPlayers= 5;
	static int numGames;
	int arr[NumPlayers];
	int arr2[NUM_TURNS];
};

int GamePlayer::numGames= 0;


class Rational
{
	int x;
	int y;

public:
	Rational()
	{
		this->x= 0;
		this->y= 0;

		std::cout << "Constructor called " << std::endl;
	}

	Rational(int x, int y)
	{
		this->x= x;
		this->y= y;
	}

	//return const to avoid a+b= c;
	friend const Rational operator+(const Rational& lhs, const Rational& rhs)
	{
		return Rational(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	void print() const
	{
		std::cout << "X: " << x << " Y: " << y << std::endl;
	}

};

class TextBlock
{
public:

	TextBlock(std::string& name) :
		rational(1,2), 				//Normally it calls the default constructor rational()
		m_name(name)
	{
		std::cout << "Text book constructor called " << std::endl;
	}

	const char& operator[](std::size_t position) const
	{
		return text[position];
	}

	char& operator[](std::size_t position)
	{
		//MAGIC CAST
		return const_cast<char&>(static_cast<const TextBlock&>(*this)[position]);
	}

private:
	std::string text;
	Rational rational;
	std::string& m_name; 	//can't do assignment operation tb1=tb2 with default copy constructor
};

//non copyable lock
class Lock
{
public:
	Lock()
	{

	}

	~Lock()				//Destructors can not propagate exceptions
	{
		try
		{

		}
		catch(std::exception& e)
		{
			//log the error
		}

	}

private:
	Lock(const Lock& rhs);					//copy constructor
	Lock& operator=(const Lock& rhs);		//assignment
};


class Widget
{
public:
	Widget() :
			m_ptr(NULL)
	{

	}

	Widget(const Widget& rhs):
		m_ptr(NULL)
	{

	}

	Widget& operator=(const Widget& rhs)
	{
		//self assignment
		if (this == &rhs)
		{
			return *this;
		}

		try
		{
			int* copyPtr = new int;

			if (m_ptr)
			{
				delete m_ptr;
			}

			m_ptr = copyPtr;
			memcpy((void*) m_ptr, (void*) rhs.m_ptr, sizeof(int));
		}
		catch (std::exception& e)//provide strong guarantee if allocation fails return the same
		{							//object
			return *this;
		}

		return *this;
	}

private:
	int* m_ptr;
};

class TableViewWidget : public Widget
{

public:
	TableViewWidget() :
		m_index(0)
	{

	}

	//copy first the base component
	TableViewWidget(const TableViewWidget& rhs):
		Widget(*(Widget*)this)
	{
		this->m_index= rhs.m_index;
	}

	//copy first the base component
	TableViewWidget& operator=(const TableViewWidget& rhs)
	{
		Widget::operator =(rhs);

		this->m_index= rhs.m_index;

		return *this;
	}

private:
	int m_index;

};








#endif /* CONSTRUCTORS_H_ */
