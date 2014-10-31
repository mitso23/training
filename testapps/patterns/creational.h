/*
 * creatonal.h
 *
 *  Created on: Sep 5, 2013
 *      Author: dimitrios
 */

#ifndef CREATONAL_H_
#define CREATONAL_H_

////////////////////////////////////////////////////FACTORY CLASSES/////////////////////////////////////////
typedef enum
{
	DIRECTION_NORTH,
	DIRECTION_SOUTH,
	DIRECTION_WEST,
	DIRECTION_EAST,

}direction_t;

class MapSite
{
public:

	MapSite()
	{

	}

	virtual void enter()= 0;

	virtual ~MapSite()
	{

	}

};

class Door: public MapSite
{
public:
	void enter()
	{
		std::cout << "entering the door" << std::endl;
	}

	bool isOpen()
	{
		return true;
	}

	virtual Door* clone()
	{
		return new Door();
	}
};

class Wall : public MapSite
{
public:
	void enter()
	{
		std::cout << "entering the wall: " << std::endl;
	}

	virtual Wall* clone()
	{
		return new Wall();
	}
};


class BombedWall : public Wall
{

public:

	BombedWall():
		m_hasBombe(false)
	{

	}

	void destroyWalls()
	{

	}

	virtual Wall* clone()
	{
		return new BombedWall(*this);
	}

	bool hasBombe() const
	{
		return m_hasBombe;
	}

	BombedWall(const BombedWall& other):
		Wall()
	{
		this->m_hasBombe= other.hasBombe();
	}

private:
	bool m_hasBombe;
};

class Room: public MapSite
{

public:
	Room(int number):
		m_roomNumber(number)
	{
		for (int i=0; i< 4; i++)
		{
			m_sites[i]= NULL;
		}
	}

	Room(const Room& other)
	{
		this->m_roomNumber= other.m_roomNumber;
	}

	void enter()
	{
		std::cout << "entering the room" << std::endl;
	}

	void setSide(direction_t direction, MapSite* side)
	{
		m_sites[direction]= side;
	}

	MapSite* getSide(direction_t direction)
	{
		return m_sites[direction];
	}

	virtual Room* clone()
	{
		return new Room(*this);
	}


private:
	MapSite* m_sites[4];
	int m_roomNumber;
};

class Maze
{
public:
	Maze()
	{

	}

	void addRoom(Room* room)
	{

	}

	Room* getRoom(int roomNumber);
};

//////////////////////////////////Abstract Factory //////////////////////////////////////////////////////
class MazeFactory
{

public:

	MazeFactory()
	{

	}

	virtual Maze* createMaze()
	{
		return new Maze();
	}

	virtual Wall* createWall()
	{
		return new Wall();
	}

	virtual Door* createDoor()
	{
		return new Door();
	}

	virtual Room* createRoom(int roomNumber)
	{
		return new Room(roomNumber);
	}

	virtual ~MazeFactory()
	{

	}
};


class EnchanteMazeFactory : public MazeFactory
{
	virtual Wall* createWall()
	{
		return new BombedWall();
	}
};

class MazeGame
{
public:

	Maze* createMaze(MazeFactory& factory)
	{

		Maze* maze= factory.createMaze();

		Wall* wall1= factory.createWall();
		Wall* wall2= factory.createWall();;
		Wall* wall3= factory.createWall();;
		Door* door= factory.createDoor();

		Room* room= new Room(0);
		room->setSide(DIRECTION_EAST, wall1);
		room->setSide(DIRECTION_WEST, wall2);
		room->setSide(DIRECTION_NORTH, wall3);
		room->setSide(DIRECTION_SOUTH, door);

		maze->addRoom(room);

		return maze;
	}
};


/////////////////////////////////////////BUILDER PATTERN /////////////////////////////////////////////////

class MazeBuilder
{

public:
	virtual void buildMaze()
	{

	}

	virtual void buildRoom(int room)
	{

	}

	virtual void buildDoor(int room1, int room2)
	{

	}

	MazeBuilder()
	{

	}

	virtual ~MazeBuilder()
	{

	}

};

class StandardMazeBuilder : MazeBuilder
{

public:
	StandardMazeBuilder() :
			MazeBuilder(), m_currentMaze(NULL)
	{

	}

	virtual void buildMaze()
	{
		m_currentMaze= new Maze();
	}

	virtual void buildRoom(int roomNumber)
	{

		Room* room = new Room(roomNumber);

		room->setSide(DIRECTION_EAST, new Wall);
		room->setSide(DIRECTION_WEST, new Wall);
		room->setSide(DIRECTION_NORTH, new Wall);
		room->setSide(DIRECTION_SOUTH, new Wall);

		if(m_currentMaze)
			m_currentMaze->addRoom(room);
	}

	virtual void buildDoor(int room1, int room2)
	{

#if 0
		Room* r1 = m_currentMaze->RoomNo(n1);
		Room* r2 = m_currentMaze->RoomNo(n2);
		Door* d = new Door(r1, r2);
#endif
	}

	Maze* getMaze()
	{
		return m_currentMaze;
	}

private:
	Maze* m_currentMaze;
};

class MazeGame2
{
public:

	void createMaze(StandardMazeBuilder& builder)
	{
		builder.buildMaze();

		builder.buildRoom(0);
		builder.buildRoom(1);

		builder.buildDoor(0, 1);

	}
};

/////////////////////////////////////FACTORY PATTERN/////////////////////////////////////////////////////

class MazeGame3
{
public:
	virtual Maze* makeMaze()
	{
		return new Maze();
	}

	virtual Wall* makeWall()
	{
		return new Wall;
	}

	virtual Room* makeRoom(int roomNumber)
	{
		return new Room(roomNumber);
	}

	virtual Door* makeDoor(Room* room1, Room* room2)
	{
		return new Door();
	}

	Maze* createMaze()
	{
		Maze* maze= makeMaze();

		Room* room1= makeRoom(1);
		Room* room2= makeRoom(2);

		maze->addRoom(room1);
		maze->addRoom(room2);

		room1->setSide(DIRECTION_EAST, makeWall());
		room1->setSide(DIRECTION_WEST, makeWall());
		room1->setSide(DIRECTION_NORTH, makeWall());

		return maze;
	}

	MazeGame3()
	{

	}

	virtual ~MazeGame3()
	{

	}
};

class EnchantedMazeGame3 : public MazeGame3
{
public:
	virtual Wall* makeWall()
	{
		return new BombedWall();
	}

	EnchantedMazeGame3()
	{

	}

	~EnchantedMazeGame3()
	{

	}

};

////////////////////////////////////Prototype pattern ///////////////////////////////////////////////////

class MazeGamePrototypeFactory
{
public:
	MazeGamePrototypeFactory(Wall* wall, Door* door, Room* room) :
		m_wall(wall),
		m_door(door),
		m_room(room),
		m_maze(NULL)
	{

	}

	Maze* makeMaze()
	{
		m_maze= new Maze();
		return m_maze;
	}

	Wall* makeWall()
	{
		return m_wall->clone();
	}

	Door* makeDoor()
	{
		return m_door->clone();
	}

	Room* makeRoom()
	{
		return m_room->clone();
	}

private:
		Wall* m_wall;
		Door* m_door;
		Room* m_room;
		Maze* m_maze;
};

class MazeGame4
{

public:
	Maze* createMaze(MazeGamePrototypeFactory& prototype)
	{
		Maze* maze= prototype.makeMaze();
		Room* room= prototype.makeRoom();

		maze->addRoom(room);

		return maze;
	}
};

////////////////////////////////////////Singleton Pattern ////////////////////////////////////////////////

class MazeGameSingleton
{
public:

	static MazeGameSingleton* getInstanse()
	{
		if (m_instance == NULL)
		{
			return m_instance= new MazeGameSingleton();
		}
		else
		{
			return m_instance;
		}
	}

protected:
	MazeGameSingleton()
	{

	}
private:
	static MazeGameSingleton* m_instance;
};

MazeGameSingleton* MazeGameSingleton::m_instance= NULL;







#endif /* CREATONAL_H_ */
