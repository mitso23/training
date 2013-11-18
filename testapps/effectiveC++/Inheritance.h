#ifndef INHERITANCE_H_
#define INHERITANCE_H_

class Base
{
public:
	void mf1()
	{
		std::cout << "Base: mf1() called" << std::endl;
	}

	void mf1(int x)
	{
		std::cout << "Base: mf1(int x) called" << std::endl;
	}
};

class Derived: public Base
{

public:

using Base::mf1;

	//THIS IS HIDING THE NAME IN THE BASE CLASS
	void mf1()
	{
		std::cout << "Derived: mf1() called" << std::endl;
	}

	void mf1(double x)
	{
		std::cout << "Derived: mf1(double x) called" << std::endl;
	}
};

class Airplane
{
public:
	virtual void fly()= 0;
};

//PROVIDE A DEFAULT IMPLEMENTATION SO CLIENTS CAN CALL
void Airplane::fly()
{
	std::cout << "Using the default fly mechanism" << std::endl;
}


class Boing : Airplane
{
public:
	void fly()
	{
		Airplane::fly();

	}
};


//NVI PATTERN, MAKE VIRTUAL PRIVATE
class GameCharacter1
{
public:
	void calculateHealth()
	{
		//pre conditions
		doCalculateHealth();
		//post conditions
	}

private:
	void doCalculateHealth()
	{

	}

};

//USE STRATEGY PATTERN AS ALTERNATIVE TO VIRTUAL FUNCTIONS(C Style)
class GameCharacter;

void calculateHealthValue(const GameCharacter& gameCharacter);

class GameCharacter
{

public:
	typedef void(*HealthCalcFunct)(const GameCharacter& gameCharacter);

	explicit GameCharacter(HealthCalcFunct funct)
	{
		m_healthCalcFunc= funct;
	}

	void calculateHealth()
	{
		m_healthCalcFunc(*this);
	}

private:
	HealthCalcFunct m_healthCalcFunc;
};

//THIS IS THE DIAMOND PROBLEM,
//in IOFILE the class has two copies of FileName
//If we use virtual inheritance IO File will have only one copy
class File
{
public:
	std::string FileName;
};

class InputFile : public File
{

};

class OutputFile : public File
{

};


class IOFile : public InputFile , public OutputFile
{
public:
	IOFile()
	{
		InputFile::FileName= "InputFile";
		OutputFile::FileName= "OutputFile";

		std::cout << "Input: " << InputFile::FileName << std::endl;
		std::cout << "Ouput: " << OutputFile::FileName << std::endl;

		//WE CANT CALL THIS AS THIS IS AMBIGIUS
		//std::cout << "FIle " << File::FileName;
	}
};







#endif /* INHERITANCE_H_ */
