void __swap(int& s, int& d)
{
	int temp = s;
	s = d;
	d = temp;
}

void rotate_cw(int M, int object[4][4], int count)
{

	if (count % 4 == 1)
	{
		int startI = 0;
		int endJ =  M - 1;

		while(startI < endJ)
		{
			for(int j= startI; j< endJ; ++j)
			{
				//90 degrees rotation
				int temp = object[startI][j];
				int srcI = startI;
				int srcJ = j;

				//std::cout << "starting from i: " << srcI << " j: " << srcJ << std::endl;

				for (int counter = 0; counter< 4; ++counter)
				{
					int dstI = 0;
					int dstJ = 0;

					dstI = srcJ;
					dstJ = (M-1) - srcI;

					//std::cout << "copying " << temp << " to: " << object[dstI][dstJ] << std::endl;

					__swap(temp, object[dstI][dstJ]);
					srcI = dstI;
					srcJ = dstJ;
				}


				//std::cout << "finished one block" << std::endl;
			}

			//std::cout << "finished one side: " << std::endl;

			++startI;
			--endJ;
		}
	}
	else if (count % 4 == 2)
	{
		for (int i=0; i< M / 2; ++i)
		{
			for(int j=0; j< M; ++j)
			{
				//std::cout << "i: " << i << " j: " << j << std::endl;
				int dstI = (M - 1) - i;
				int dstJ = (M - 1) - j;

				//std::cout << "copying " << object[i][j] << " to: " << object[dstI][dstJ] << std::endl;
				__swap(object[i][j], object[dstI][dstJ]);
			}

			std::cout << "finished one side" << std::endl;
		}
	}
	else if (count % 4 == 3)
	{
		int startI = 0;
		int endJ =  M - 1;

		while(startI < endJ)
		{
			for(int j= startI; j< endJ; ++j)
			{
				//90 degrees rotation
				int temp = object[startI][j];
				int srcI = startI;
				int srcJ = j;

				for (int counter = 0; counter< 4; ++counter)
				{
					int dstI = M - 1 - srcJ;
					int dstJ = srcI;

					//std::cout << "starting from i: " << srcI << " j: " << srcJ <<  " dstI: " << dstI << " dstJ: " << dstJ <<std::endl;
					//std::cout << "copying " << temp << " to: " << object[dstI][dstJ] << std::endl;

					__swap(temp, object[dstI][dstJ]);
					srcI = dstI;
					srcJ = dstJ;
				}


				//std::cout << "finished one block" << std::endl;
			}

			//std::cout << "finished one side: " << std::endl;

			++startI;
			--endJ;
		}
	}
}

void flip(int M, int object[4][4], int vh)
{
	// up and down
	if (vh == 0)
	{
		int startI = 0;
		int startJ = 0;

		int endI = M - 1;
		int endJ = 0;

		while(startI < endI)
		{
			for(int count = 0; count < M; ++count)
			{
				//std::cout << "swapping i: " << startI << " j: " << count << " with i: " << endI <<  " j: " << count << std::endl;
				__swap(object[startI][count], object[endI][count]);
			}

			++startI;
			--endI;
		}
	}
	else
	{
		for (int i=0; i< M; ++i)
		{
			for (int j=0; j< M/2; ++j)
			{
				__swap(object[i][j], object[i][M - j - 1]);
			}
		}
	}
}


struct Object
{
	int x;
	int y;

	int width;
	int height;
};

struct Board
{
	int width;
	int height;

	int board[10][10];
};

static Object srcObject;
static Object dstObject;
static Board  b;

bool CheckIfObjectOverlap(const Object& srcObject, const Object& dstObject)
{
	if ((dstObject.x >= srcObject.x + srcObject.width) ||
		(dstObject.y <= srcObject.y - srcObject.height) ||
		(dstObject.x + dstObject.width <= srcObject.x) ||
		(dstObject.y - dstObject.height) >=srcObject.y)
	{
		std::cout << "Object don't overlap" << std::endl;
		return false;
	}

	std::cout << "Object overlap" << std::endl;
	return true;
}

void initObject(int size, int object[4][4])
{
	srcObject.x = 0;
	srcObject.y = b.height;
	srcObject.height = size;
	srcObject.width = size;

	dstObject = srcObject;

	int yy = 0;
	for(int y=b.height; y>=(b.height - size); --y)
	{
		for (int x= 0; x<= size; ++x)
		{
			b.board[y][x] = object[yy][x];
		}

		++yy;
	}
}

void initBoard(int size, int board[10][10])
{
	b.height = size;
	b.width = size;

	for(int i=0; i< size; ++i)
	{
		for (int j=0; j< size; ++j)
		{
			b.board[i][j] = board[i][j];
		}
	}
}

void Fill(const Object& rec)
{
	for(int y = rec.y; y > (rec.y - rec.height); --y)
	{
		for (int x = rec.x; x < rec.x + rec.width; ++x)
		{
			b.board[y][x] = 0;
		}
	}
}

void Copy(const Object& src, const Object& dst)
{
	for(int j=0; j< src.height; ++j)
	{
		for(int i=0; i< src.width; ++i)
		{
			int srcX = src.x + i;
			int srcY = src.y - j;

			int dstX = dst.x + i;
			int dstY = dst.y - j;

			if (dstY < 0 || dstX >= b.width )
			{
				std::cout << "x: " << dstX << " y: " << dstY << " out of bounds " << std::endl;
				continue;
			}
			else
			{
				std::cout << "copying y: " << srcY << " x: " << srcX << " to y: " << dstY << " x: " << dstX << std::endl;
				b.board[dstY][dstX] = b.board[srcY][srcX];
			}
		}
	}
}

void printBoard()
{
	for(int y=b.height; y>0; --y)
	{
		for (int x= 0; x< b.width; ++x)
		{
			std::cout << b.board[y][x] << " ";
		}

		std::cout << std::endl;
	}
}

// 0 0 0 1 0 0
// 0 1 0 0 0 0
// 0 1 0 1 0 0

//dir: UP(0), DOWN(1), RIGHT(2), LEFT(3)
void move(int dir, int count)
{
	//right
	if (dir == 2)
	{
		//find the left corner and check if it can be moved left
		int minMoveRight = b.width;

		for(int y= srcObject.y; y >(srcObject.y - srcObject.height); --y)
		{
			int currentMoveRight = 0;
			bool stop = false;

			int startX = srcObject.x + srcObject.width - 1;
			int value = b.board[y][startX];

			std::cout << "y: " << y << " startX: " << startX << " value: " << value << std::endl;

			for(int k= 1; k<= count; ++k)
			{
				if (value == 1 && ((startX + k) >= b.width))
				{
					stop = true;
					std::cout << "out of bounds " << startX + k << std::endl;
					break;
				}
				else if (value == 1 && b.board[y][startX + k] != 0)
				{
					stop = true;
					std::cout << " can't move one to obstacle " << b.board[y][startX + k] << std::endl;
					break;
				}
				else
				{
					std::cout << " can move left from x: " << startX << " y: " << y << std::endl;
					++currentMoveRight;
				}
			}

			if (currentMoveRight < minMoveRight)
			{
				std::cout << "current Move left " << currentMoveRight << " is less: " << minMoveRight << std::endl;
				minMoveRight = currentMoveRight;
			}

			if (stop)
			{
				break;
			}
		}

		dstObject.x+= minMoveRight;
	}
	//left
	else if (dir == 3)
	{
		int minMoveLeft = 0;

		for(int y= srcObject.y; y >=0; --y)
		{
			int currentMoveLeft = 0;
			bool stop = false;
			int startX = srcObject.x;
			int value = b.board[y][startX];

			std::cout << "y: " << y << " startX: " << startX << " value: " << value << std::endl;

			for(int k=1; k<= count; ++k)
			{
				if (value == 1 && ((startX - k) < 0))
				{
					stop = true;
					std::cout << "out of bounds " << startX - k << std::endl;
					break;
				}
				else if (value == 1 && b.board[y][startX - k] != 0)
				{
					stop = true;
					std::cout << " can't move one to obstacle " << b.board[y][startX - k] << std::endl;
					break;
				}
				else
				{
					std::cout << " can move left from x: " << startX << " y: " << y << std::endl;
					++currentMoveLeft;
				}
			}

			if (stop)
			{
				break;
			}

			if (currentMoveLeft < minMoveLeft)
			{
				std::cout << "current Move left " << currentMoveLeft << " is less: " << minMoveLeft << std::endl;
				minMoveLeft = currentMoveLeft;
			}
		}

		dstObject.x+= minMoveLeft;
	}
	//UP
	else if (dir == 0)
	{

		// 0 0 0 1 0 0
		// 0 1 0 0 0 0
		// 0 1 0 1 0 0

		int minMoveUp = 0;

		for(int x= srcObject.x; x < srcObject.x + srcObject.width; ++x)
		{
			int currentMoveUp = 0;
			bool stop = false;
			int startY = srcObject.y;
			int value = b.board[startY][x];

			std::cout << "y: " << startY << " x: " << x << " value: " << value << std::endl;

			for(int k=1; k<= count; ++k)
			{
				if (value == 1 && ((startY + k) > srcObject.y + srcObject.height))
				{
					stop = true;
					std::cout << "out of bounds " << startY + k << std::endl;
					break;
				}
				else if (value == 1 && b.board[startY+k][x] != 0)
				{
					stop = true;
					std::cout << " can't move one to obstacle " << b.board[startY + k][x] << std::endl;
					break;
				}
				else
				{
					std::cout << " can move up x: " << x << " y: " << startY << std::endl;
					++currentMoveUp;
				}
			}

			if (stop)
			{
				break;
			}

			if (currentMoveUp < minMoveUp)
			{
				std::cout << "current Move up " << currentMoveUp << " is less: " << minMoveUp << std::endl;
				minMoveUp = currentMoveUp;
			}

		}
	}
	//Down
	else if (dir == 1)
	{

		// 0 0 0 1 0 0
		// 0 1 0 0 0 0
		// 0 1 0 1 0 0

		int minMoveDown = 0;

		for(int x= srcObject.x; x < srcObject.x + srcObject.width; ++x)
		{
			int currentMoveDown = 0;
			bool stop = false;
			int startY = srcObject.y - srcObject.height;
			int value = b.board[startY][x];

			std::cout << "y: " << startY << " x: " << x << " value: " << value << std::endl;

			for(int k=1; k<= count; ++k)
			{
				if (value == 1 && ((startY - k) < 0))
				{
					stop = true;
					std::cout << "out of bounds " << startY - k << std::endl;
					break;
				}
				else if (value == 1 && b.board[startY-k][x] != 0)
				{
					stop = true;
					std::cout << " can't move one to obstacle " << b.board[startY - k][x] << std::endl;
					break;
				}
				else
				{
					std::cout << " can move down x: " << x << " y: " << startY << std::endl;
					++currentMoveDown;
				}
			}

			if (stop)
			{
				break;
			}


			if (currentMoveDown < minMoveDown)
			{
				std::cout << "current Move down " << currentMoveDown << " is less: " << minMoveDown << std::endl;
				minMoveDown = currentMoveDown;
			}

		}
	}

	if (CheckIfObjectOverlap(srcObject, dstObject))
	{
		std::cout << "Objects overlap: " << std::endl;
	}
	else
	{
		Copy(srcObject, dstObject);
		Fill(srcObject);
	}


}

void getBoard(int board[10][10])
{

}
