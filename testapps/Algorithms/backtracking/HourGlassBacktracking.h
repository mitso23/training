/*
 * HourGlassBacktracking.h
 *
 *  Created on: 7 Jun 2017
 *      Author: mitso23
 */

#ifndef HOURGLASSBACKTRACKING_H_
#define HOURGLASSBACKTRACKING_H_

void calculateNewAandB(unsigned int& A, unsigned int& B, unsigned int time)
{
	if (time >= B)
	{
		B = 0;
	}
	else
	{
		B = B - time;
	}

	if (time >= A)
	{
		A = 0;
	}
	else
	{
		A = A - time;
	}
}

// if A = 4 and B = 7
// if A = 0 and B = 6
// if A = 0 and B = 0
// if A = 1 and B = 0
int runA(unsigned int maxA, unsigned int maxB, unsigned int& A, unsigned int& B)
{
	std::cout << "runA:" << " A: " << A << " B: " << B << std::endl;

	int time = 0;

	if (A == 0)
	{
		A = maxA;
	}

	time = A;

	calculateNewAandB(A, B, time);

	std::cout << "runA:" << " A: " << A << " B: " << B <<  " time: " << time << std::endl;

	return time;
}

// if A = 4 and B = 7
// if A = 0 and B = 6
// if A = 0 and B = 0
// if A = 1 and B = 0
int runB(unsigned int maxA, unsigned int maxB, unsigned int& A, unsigned int& B)
{
	std::cout << "runB:" << " A: " << A << " B: " << B << std::endl;

	int time = 0;

	if (B == 0)
	{
		B = maxB;
	}

	time = B;

	calculateNewAandB(A, B, time);

	std::cout << "runB:" << " A: " << A << " B: " << B << " time: " << time << std::endl;

	return time;
}


// if A = 4 and B = 7
// if A = 0 and B = 6
// if A = 0 and B = 0
// if A = 1 and B = 0
int FlipARunMinDuration(unsigned int maxA, unsigned int maxB, unsigned int& A, unsigned int& B)
{
	std::cout << "FlipARunMinDuration:" << " A: " << A << " B: " << B << std::endl;

	if (A == maxA)
	{
		//std::cout << "can't perform flipA" << std::endl;
		return -1;
	}
	else if (B == 0)
	{
		//std::cout << "B zero no point in making Flip A min duration" << std::endl;
		return -1;
	}

	int time = 0;
	A = maxA - A;

	if (B >= A)
	{
		time = A;
	}
	else
	{
		time = B;
	}

	calculateNewAandB(A, B, time);

	std::cout << "flipA:" << " A: " << A << " B: " << B << " time: " << time << std::endl;

	return time;
}

// if A = 4 and B = 7
// if A = 0 and B = 6
// if A = 0 and B = 0
// if A = 1 and B = 0
int FlipBRunMinDuration(unsigned int maxA, unsigned int maxB, unsigned int& A, unsigned int& B)
{
	std::cout << "FlipBRunMinDuration:" << " A: " << A << " B: " << B << std::endl;

	if (B == maxB)
	{
		return -1;
	}
	else if (A == 0)
	{
		//std::cout << "A zero no point in making Flip A min duration" << std::endl;
		return -1;
	}

	int time = 0;

	B = maxB - B;

	if (B >= A)
	{
		time = A;
	}
	else
	{
		time = B;
	}

	calculateNewAandB(A, B, time);

	std::cout << "flipB:" << " A: " << A << " B: " << B << " time: " << time << std::endl;

	return time;
}

// if A = 4 and B = 7
// if A = 0 and B = 6
// if A = 0 and B = 0
// if A = 1 and B = 0
int FlipBothRunMinDuration(unsigned int maxA, unsigned int maxB, unsigned int& A, unsigned int& B)
{
	std::cout << "FlipBothRunMinDuration:" << " A: " << A << " B: " << B << std::endl;

	int time = -1;
	if (A == 0 && B == 0)
	{
		std::cout << "can't perform flipBoth" << std::endl;
		return -1;
	}

	A = maxA - A;
	B = maxB - B;

	if (B >= A)
	{
		time = A;
	}
	else
	{
		time = B;
	}

	calculateNewAandB(A, B, time);

	std::cout << "flipBoth:" << " A: " << A << " B: " << B << " time: " << time << std::endl;

	return time;
}

bool run(unsigned int maxA, unsigned int maxB, unsigned int A, unsigned int B, int time, int level)
{
	++level;

	std::cout << "--run: " << " A: " << A << " B: " << B << " remaining time: " << time << " level: " << level << std::endl;

	if (time < 0)
	{
		return false;
	}
	else if (time == 0)
	{
		return true;
	}

	unsigned oldA = A;
	unsigned oldB = B;

	int newTime = runA(maxA, maxB, A, B);
	if (newTime != -1)
	{
		if (run(maxA, maxB, A, B, time - newTime, level))
		{
			return true;
		}
		A = oldA;
		B = oldB;
	}

	oldA = A;
	oldB = B;

	newTime = runB(maxA, maxB, A, B);
	if (newTime != -1)
	{
		if (run(maxA, maxB, A, B, time - newTime, level))
		{
			return true;
		}

		A = oldA;
		B = oldB;
	}

	oldA = A;
	oldB = B;

	newTime = FlipARunMinDuration(maxA, maxB, A, B);
	if (newTime != -1)
	{
		if (run(maxA, maxB, A, B, time - newTime, level))
		{
			return true;
		}

		A = oldA;
		B = oldB;
	}

	oldA = A;
	oldB = B;

	newTime = FlipBRunMinDuration(maxA, maxB, A, B);
	if (newTime != -1)
	{
		if (run(maxA, maxB, A, B, time - newTime, level))
		{
			return true;
		}

		A = oldA;
		B = oldB;
	}


	newTime = FlipBothRunMinDuration(maxA, maxB, A, B);
	if (newTime != -1)
	{
		if (run(maxA, maxB, A, B, time - newTime, level))
		{
			return true;
		}
	}

	//std::cout << "---returning: " << " A: " << A << " B: " << B << " level: " << level << " remaining time: " << time << std::endl;
	--level;
	return false;
}


#endif /* HOURGLASSBACKTRACKING_H_ */
