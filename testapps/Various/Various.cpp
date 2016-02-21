#include <stdio.h>
#include <stdlib.h>


//Two convert a two dimensional array into single one we use this formula Y*10 + X
//where X,Y is the pixel coordinates

unsigned pImage[100];

//We assume that each square box is a single pixel of one byte size
unsigned calculateArea(unsigned char *pImage, unsigned int size)
{
	unsigned counter= 0;
	for(unsigned int i=0; i< 100; ++i)
	{
		if (pImage[i] != 0)
		{
			++counter;
		}
	}

	return counter;
}

int main(int argc, char* argv[])
{
	//The selected coordinates are random and don't correspond to the image provided
    pImage[12]= 1;
    pImage[13]= 2;
    pImage[17]= 4;

    calculateArea((unsigned char*)pImage, 100);

}
