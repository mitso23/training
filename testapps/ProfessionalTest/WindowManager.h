#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include <unistd.h>
#include <algorithm>

extern FILE* fp;

struct Coordinate
{
	Coordinate(int y_, int x_)
		: y(y_)
		, x(x_)
	{

	}

	Coordinate()
	{

	}

	bool Valid() const
	{
		return x != -1 && y != -1;
	}

	int y = -1;
	int x = -1;
};

struct Rectangle
{
	Rectangle(const Coordinate& topLeft, int w, int h)
		: topLeft(topLeft)
		, width(w)
		, height(h)
	{

	}

	Rectangle()
	{

	}

	Coordinate topLeft;
	int width = -1;
	int height = -1;
};

struct GraphicsInfo
{
	int id = -1;
	int next = -1;
	int previous = -1;

	Rectangle rec;
};

struct FrontObject
{
	FrontObject()
	{

	}
	Rectangle rect;
	int id = -1;
};

FrontObject frontObject;
GraphicsInfo displayObjects[10000];

void DrawCoordinateSystem(unsigned int maxY, unsigned int maxX)
{
	printf("\033[%d;%dH",  (0), (0));

	for(unsigned int x=0; x< maxX; ++x)
	{
		std::cout << x << " " ;
	}

	for(unsigned int y=0; y< maxY; ++y)
	{
		printf("\033[%d;%dH",  (y), (0));
		std::cout << y;
	}
}

void DrawLine(unsigned int yOrig, unsigned int xOrig, unsigned count)
{
	printf("\033[%d;%dH",  (yOrig), (xOrig));

	for(unsigned int i=0; i< count; ++i)
	{
		std::cout << "-";
	}
}

void DrawEdge(unsigned int yOrig, unsigned int xOrig, unsigned count, int id)
{
	printf("\033[%d;%dH",  (yOrig), (xOrig));

	std::cout << "-";

	for(unsigned int i=0; i + 2 < count; ++i)
	{
		if (i & 1)
			std::cout << id;
		else
			std::cout << " ";
	}

	std::cout << "-";

}

bool CheckRectangeVisible(const Rectangle& front, const Rectangle& back)
{
	if ((back.topLeft.x >= front.topLeft.x) && ( (back.topLeft.x + back.width) <= (front.topLeft.x + front.width)) )
	{
		if ((back.topLeft.y >= front.topLeft.y) && ( (back.topLeft.y + back.height) <= (front.topLeft.y + front.height)) )
		{
			return false;
		}
	}

	return true;
}

bool CheckRectangleOverlap(const Rectangle& r1, const Rectangle& r2)
{
	//r2 is on the left of r1
	if (r2.topLeft.x >= (r1.topLeft.x + r1.width))
	{
		return false;
	}

	// r2 is on the right of r1
	if (r2.topLeft.x + r2.width <= r2.topLeft.x)
	{
		return false;
	}

	//r2 is above r1
	if (r2.topLeft.y + r2.height <= r1.topLeft.y)
	{
		return false;
	}

	//r2 is below r1
	if (r2.topLeft.y >= r1.topLeft.y + r1.height)
	{
		return false;
	}

	return true;
}

bool isPointInsideRectangle(int y, int x, const Rectangle& rec1)
{
	if (y >= rec1.topLeft.y && y <= rec1.topLeft.y + rec1.height)
	{
		if (x >= rec1.topLeft.x && x <= rec1.topLeft.x + rec1.width)
		{
			return true;
		}
	}

	return false;
}

Rectangle GetOverlapRectangle(const Rectangle& rec1, const Rectangle& rec2)
{
	int width = std::min(rec1.topLeft.x + rec1.width, rec2.topLeft.x + rec2.width) - std::max(rec1.topLeft.x, rec2.topLeft.x);
	int height = std::min(rec1.topLeft.y + rec1.height, rec2.topLeft.y + rec2.height) - std::max(rec1.topLeft.y, rec2.topLeft.y);

	Rectangle result;
	Rectangle opposite;

	if (rec1.topLeft.y >= rec2.topLeft.y)
	{
		result = rec1;
		opposite = rec2;
	}
	else
	{
		result = rec2;
		opposite = rec1;
	}

	if (isPointInsideRectangle(result.topLeft.y, result.topLeft.x, opposite))
	{
		fprintf(fp, "topLeft cornen in rectangle \n");
	}
	else if (isPointInsideRectangle(result.topLeft.y, result.topLeft.x + result.width, opposite))
	{
		fprintf(fp, "topRight corner in rectangle \n");
		result.topLeft.x = result.topLeft.x + result.width - width;
	}
	else if (isPointInsideRectangle(result.topLeft.y + result.height, result.topLeft.x, opposite))
	{
		fprintf(fp, "bottom left corner in rectangle \n");
		result.topLeft.y= result.topLeft.y + result.height - height;
	}
	else if (isPointInsideRectangle(result.topLeft.y + result.height, result.topLeft.x, opposite))
	{
		fprintf(fp, "bottom right corner in rectangle \n");

		result.topLeft.x = result.topLeft.x + result.width - width;
		result.topLeft.y= result.topLeft.y  + result.height - height;
	}

	fprintf(fp, "y: %d x: %d height: %d width: %d\n", result.topLeft.y, result.topLeft.x, result.height, result.width);

	result.width = width;
	result.height = height;

	return result;

}

void ClearRectangle(const Rectangle& rectangle, int id)
{
	const int height = rectangle.height;
	const int width = rectangle.width;

	printf("\033[%d;%dH",  (0), (0));
	fprintf(fp, "clear: id: %d height: %d widht: %d y: %d x: %d", id, height, width, rectangle.topLeft.y, rectangle.topLeft.x);

	printf("\033[%d;%dH",  (rectangle.topLeft.y), (rectangle.topLeft.x));
	for(int j=0; j<= height; ++j)
	{
		for(int i=0; i< width; ++i)
		{
			std::cout << " ";
		}
		printf("\033[%d;%dH",  (rectangle.topLeft.y + j), (rectangle.topLeft.x));
	}

	usleep(100000);
}

void DrawRectangle(const Rectangle& rectangle, int id, bool makeFront= true)
{
	const int height = rectangle.height;
	const int width = rectangle.width;

	fprintf(fp, "draw id: %d height: %d widht: %d y: %d x: %d\n", id, height, width,  rectangle.topLeft.y, rectangle.topLeft.x);

	if (width < 0 || height < 0)
	{
		std::cout << "shit" << std::endl;
		exit(1);
	}

	int count = 0;

	while(count < height)
	{
		if (count == 0)
		{
			DrawLine(rectangle.topLeft.y, rectangle.topLeft.x, width);
		}
		else if (count + 1 == height)
		{
			DrawLine(rectangle.topLeft.y + count, rectangle.topLeft.x, width);
		}
		else
		{
			DrawEdge(rectangle.topLeft.y + count, rectangle.topLeft.x, width, id);
		}

		++count;
	}

	if (makeFront)
	{
		//this is the first object
		if (displayObjects[id].id == -1)
		{
			displayObjects[id].id = id;
			displayObjects[id].rec = rectangle;
			displayObjects[id].previous = frontObject.id;

			displayObjects[frontObject.id].next = id;

			frontObject.id = id;
			frontObject.rect = rectangle;

		}
		//if the object was moved then we need to update this rectangle coordinates
		else if (id == frontObject.id)
		{
			frontObject.rect = rectangle;
			displayObjects[frontObject.id].rec = rectangle;
		}
		//if the front object has changed then we need to update our front to back link list
		else
		{
			// p      c     n    f
			// 1  ->  2 ->  3 -> 4
			// 1  ->  3 ->  4 -> 2

			auto currentPrev = displayObjects[id].previous;
			auto currentNext = displayObjects[id].next;

			if (currentPrev)
			{
				displayObjects[currentPrev].next = currentNext;
			}

			if (currentNext)
			{
				displayObjects[currentNext].previous = currentPrev;
			}

			displayObjects[frontObject.id].previous = currentPrev;
			displayObjects[frontObject.id].next = id;

			displayObjects[id].previous = frontObject.id;
			displayObjects[id].next = -1;
			displayObjects[id].rec = rectangle;


			//update the front one
			frontObject.id = id;
			frontObject.rect = rectangle;

		}
	}

	usleep(100000);
}

void Front(int id)
{
	if (displayObjects[id].id == -1)
	{
		std::cerr << "no such rectangle with id: " << id << std::endl;
		exit(1);
	}

	if (displayObjects[id].id == frontObject.id)
	{
		fprintf(fp, "id: %d is already the front object\n", id);
		return;
	}

	Rectangle rec = displayObjects[id].rec;
	DrawRectangle(rec, id);
}

void Move(int id, int newY, int newX)
{
	if (displayObjects[id].id == -1)
	{
		std::cerr << "no such rectangle with id: " << id << std::endl;
		exit(1);
	}

	fprintf(fp, "move id: %d new y: %d new x: %d \n", id, newY, newX);

	Rectangle srcRec = displayObjects[id].rec;
	Rectangle dstRec = srcRec;

	ClearRectangle(srcRec, id);

	dstRec.topLeft.x = newX;
	dstRec.topLeft.y = newY;

	//Find the first element to draw
	auto current = displayObjects[frontObject.id].id;
	auto previous = displayObjects[frontObject.id].previous;

	while (previous != -1)
	{
		fprintf(fp, "backwards current: %d previous: %d \n", current, previous);
		current = previous;
		previous = displayObjects[current].previous;
	}

	//now draw back to front
	while(current != -1)
	{
		fprintf(fp, "forward: %d\n", current);
		//don;t draw current rectangle as it will be drawn last
		if (current != id)
		{
			bool draw = false;

			Rectangle background = displayObjects[current].rec;
			Rectangle hiddenRecBackGround = GetOverlapRectangle(background, srcRec);

			if (CheckRectangleOverlap(background, srcRec))
			{
				fprintf(fp, "rectangle with id: %d and id: %d overlap \n", current, id);

				if (CheckRectangeVisible(dstRec, hiddenRecBackGround))
				{
					fprintf(fp, "front rectangle with id: %d and back id: %d visible\n", id, current);
					draw = true;
				}
				else
				{
					fprintf(fp, "front rectangle with id: %d and back id: %d not visible\n", id, current);
				}
			}
			else
			{
				fprintf(fp, "rectangle with id: %d and id: %d not overlap\n", current, id);
			}

			if (draw)
			{
				DrawRectangle(hiddenRecBackGround, current, false);
			}
		}
		current = displayObjects[current].next;
	}

	//Draw the last rectangle
	DrawRectangle(dstRec, id, true);
}

void ActiveRectange()
{

}

#endif /* WINDOWMANAGER_H_ */
