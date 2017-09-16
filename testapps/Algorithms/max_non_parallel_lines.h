/*
 * max_non_parallel_lines.h
 *
 *  Created on: 13 Aug 2017
 *      Author: mitso23
 */

#ifndef MAX_NON_PARALLEL_LINES_H_
#define MAX_NON_PARALLEL_LINES_H_

struct LineCoord
{
	int x;
	int y;
};

struct LineAngle
{
	float angle;
	bool vertical;
};

#define MAX_NUMBER_LINES 4

LineCoord arrLines[MAX_NUMBER_LINES];
LineAngle arrAngles[MAX_NUMBER_LINES *2];

unsigned int arrAnglesPos = 0;

bool checkIfParallelOtherLine(LineAngle angle)
{
	for(unsigned int i=0; i< arrAnglesPos; ++i)
	{
		if ((!angle.vertical && !arrAngles[i].vertical) && (angle.angle == arrAngles[i].angle))
		{
			return true;
		}
		else if (angle.vertical == 1 && (angle.vertical == arrAngles[i].vertical))
		{
			return true;
		}
	}

	return false;
}

void findMaxNumberLines()
{
	unsigned int start = 0;

	for(unsigned int j= start; j< MAX_NUMBER_LINES; ++j)
	{
		for(unsigned int i=j + 1; i < MAX_NUMBER_LINES; ++i)
		{
			LineAngle angle;
			memset(&angle, 0, sizeof(angle));
			if ((arrLines[i].x - arrLines[j].x) == 0)
			{
				angle.vertical = true;
			}
			else
			{
				angle.angle = (arrLines[i].y - arrLines[j].y)/(arrLines[i].x - arrLines[j].x);
			}

			std::cout << "j: " << j << " i: " << i << " vertical: " << angle.vertical << " angle: " << angle.angle << std::endl;

			if (!checkIfParallelOtherLine(angle))
			{
				std::cout << " not parallel" << std::endl;
				arrAngles[arrAnglesPos++] = angle;
			}
			else
			{
				std::cout << " parallel " << std::endl;
			}
		}
	}
}



#endif /* MAX_NON_PARALLEL_LINES_H_ */
