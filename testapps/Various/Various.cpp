#include <iostream>
#include <functional>
#include <utils/Noisy.h>

int main(int argc, char* argv[])
{
	Noisy n3= Noisy() + Noisy() + Noisy();
	n3.setData(0);

}
