/*
 * ipctest.cpp
 *
 *  Created on: Aug 4, 2013
 *      Author: dimitrios
 */

#include<libipc/ipc.h>
#include<libbase/logger.h>

#include<iostream>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdio.h>
#include<sys/types.h>
#include"creational.h"
#include"structural.h"
#include"behavioral.h"

#include<vector>
#include<queue>

int main(int argc, char* argv[])
{

#if 1
	//Creational patterns
	{
		///Abstract Factory
		MazeGame game;
		EnchanteMazeFactory factory;
		Maze* maze = game.createMaze(factory);

		///Build
		MazeGame2 game2;
		StandardMazeBuilder builder;

		game2.createMaze(builder);
		Maze* maze2 = builder.getMaze();

		//Factory
		EnchantedMazeGame3 game3;
		Maze* maze3 = game3.createMaze();

		//Prototype
		MazeGame4 game4;
		MazeGamePrototypeFactory prototype(new BombedWall(), new Door(),
				new Room(1));
		Maze* maze4 = game4.createMaze(prototype);

		//Singleton
		MazeGameSingleton* minstance = MazeGameSingleton::getInstanse();
	}


	//structural patterns
	{
		//bridge pattern
		WindowImpl* Ximpl= new XWindow();
		Window* window= new IconWindow(Ximpl);

		//composite pattern
		Equipment* engine= new Engine();
		Equipment* sensor= new Sensor();
		dynamic_cast<Composite*>(engine)->add(sensor);

		//Decorator pattern
		VisualComponent* component= new GraphicView();
		VisualComponent* scrollDecorator= new ScrollDecorator(component);
		VisualComponent* borderDecorator= new BorderDecorator(scrollDecorator);
		borderDecorator->draw();

#if 0
		//Proxy pattern
		ImagePtr image("/tmp/image.jpeg");
		image->getHeight();
		image->getWidth();
#endif

	}

	//behavioral patterns
	{

		//Chain of responsibility
#if 0
		Application* application = new Application(APPLICATION_TOPIC);
		Dialog* dialog = new Dialog(application, PRINT_TOPIC);
		Button* button = new Button(dialog, PAPER_ORIENTATION_TOPIC);
#endif

		//Command Pattern
		Document* document= new Document();
		Command* command= new PasteCommand(document);
		MenuItem* menuItem= new MenuItem(command);
		menuItem->onButtonClick();

		//Iterator pattern
		ListContainer* list= new ListContainer();
		Iterator* iter= list->createIterator();

		list->push(1);
		list->push(2);
		list->push(3);

		for(iter->first(); !iter->isDone(); iter->next())
		{
			std::cout << iter->getCurrentItenm() <<std::endl;
		}

		//Memento
		Originator* orig= new Originator();
		//create a copy of the current state
		Memento* oldState= orig->CreateMemento();
		//change the state
		orig->ChangeState();
		//restore the old state
		orig->SetMemento(oldState);


		//Template method
		//Renderer* render= new Renderer();
		//render->display();

		PriceVisitor priceVisitor;
		Equipments* equipment= new Brake(&priceVisitor);
		equipment->displayPrice();

		}
#endif

}
