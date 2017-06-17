/*
 * communication_stations.h
 *
 *  Created on: 29 Apr 2017
 *      Author: mitso23
 */
#ifndef COMMUNICATION_STATIONS_H_
#define COMMUNICATION_STATIONS_H_


#define MAX_SIZE 9

int CityMap[MAX_SIZE][MAX_SIZE] =
				{
					{ 1, 0, 0, 0, 0, 0, 0, 0, 1 },

					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },

					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },

					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },

					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },

					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },

					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },

					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },

					{ 1, 0, 0, 0, 0, 0, 0, 0, 1 },

				};

unsigned int minDistancebetweenStations = 0xFF;

unsigned int gBase1Y = 0;
unsigned int gBase1X = 0;

unsigned int gBase2Y = 0;
unsigned int gBase2X = 0;

unsigned int gR1 = 0;
unsigned int gR2 = 0;

unsigned calculateDistance(unsigned int Y1, unsigned int X1, unsigned int Y2, unsigned int X2)
{
	return (Y1-Y2)*(Y1-Y2) + (X1 - X2)*(X1-X2);
}

bool isPointWithinRadius(unsigned int Y1, unsigned X1, unsigned int BaseY, unsigned int BaseX, unsigned int Radius)
{
	int diff = Radius*Radius - calculateDistance(Y1, X1, BaseY, BaseX);

	if (diff >=0)
	{
		return true;
	}

	return false ;
}

int checkIfPositioningBaseStationsIsPossible(unsigned int Base1Y, unsigned int Base1X,
								 	 	 	 unsigned int Base2Y, unsigned int Base2X,
								 	 	 	 unsigned R1, unsigned R2, unsigned mapSize)
{

	//std::cout << "B1Y: " << Base1Y << " B1X: " << Base1X << " B2Y: " << Base2Y << " B2X: " << Base2X << " R2: " << R2  << " R1: " << R1 << std::endl;

	bool bothCommunicate = false;

	for(unsigned int j=0; j< mapSize; ++j)
	{
		for(unsigned int i=0; i< mapSize; ++i)
		{
			if (CityMap[j][i] == 1)
			{
				bool base1range = isPointWithinRadius(j, i, Base1Y, Base1X, R1);
				bool base2range = isPointWithinRadius(j, i, Base2Y, Base2X, R2);

				if (!base1range && !base2range)
				{
					return -1;
				}
				else if (base1range && base2range)
				{
					bothCommunicate = true;
				}
				else
				{
					continue;
				}


			}
			else if (CityMap[j][i] == 2)
			{

				bool base1range = isPointWithinRadius(j, i, Base1Y, Base1X, R1);
				bool base2range = isPointWithinRadius(j, i, Base2Y, Base2X, R2);

				if (base1range || base2range)
				{
					return -1;
				}
				else
				{
					continue;
				}

			}
		}
	}

	if (bothCommunicate)
	{
		return calculateDistance(Base1Y, Base1X, Base2Y, Base2X);
	}

	return -1;

}

void tryBase1(unsigned int r2, unsigned int r1, unsigned int mapSize, unsigned int Base2Y, unsigned int Base2X)
{
	if (Base2Y == mapSize - 1 && Base2X == mapSize - 1)
	{
		return ;
	}

	unsigned startBase1Y = 0;
	unsigned startBase1X = 0;

	if (Base2X == mapSize - 1)
	{
		startBase1Y = Base2Y + 1;
		startBase1X = 0;
	}
	else
	{
		startBase1Y = Base2Y;
		startBase1X = Base2X + 1;

	}

	for (unsigned int j = startBase1Y; j < mapSize; ++j)
	{
		for (unsigned int i = startBase1X; i < mapSize; ++i)
		{
			if (CityMap[j][i] == 0)
			{
				int distance = checkIfPositioningBaseStationsIsPossible(j, i, Base2Y, Base2X, r1, r2, mapSize);

				if (distance > 0 && (unsigned)distance < minDistancebetweenStations)
				{
					minDistancebetweenStations = distance;
					gBase1Y = j;
					gBase1X = i;
					gBase2Y = Base2Y;
					gBase2X = Base2X;

					gR1 = r1;
					gR2 = r2;
				}
			}
		}
	}
}

void tryBase2(unsigned int r2, unsigned int r1, unsigned int mapSize)
{
	for(unsigned int j=0; j< mapSize; ++j)
	{
		for (unsigned int i=0; i< mapSize; ++i)
		{
			if (CityMap[j][i] == 0)
			{
				tryBase1(r2, r1, mapSize, j, i);
			}
		}
	}
}

void tryAllCombinations(unsigned int mapSize)
{
	for (unsigned int r2= 1; r2< mapSize; ++r2)
	{
		for (unsigned int r1 = 1; r1 < mapSize; ++r1)
		{
			tryBase2(r2, r1, mapSize);

		}
	}

	std::cout << "min distance: " << minDistancebetweenStations << " Station 1, Y: " <<
			gBase1Y << " X: " << gBase1X <<
			" Station2 Y: "<< gBase2Y << " X: " << gBase2X <<
			" R1: " << gR1 << " R2: " << gR2 << std::endl;
}




#endif
