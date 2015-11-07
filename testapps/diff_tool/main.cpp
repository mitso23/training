#include "FileDiff.h"

#include <iostream>
#include <utils/utils.h>
#include <algorithm>

int main(int argc, char* argv[])
{
	FileDiff diff("/home/mitso23/training/resources/text3.diff", "/home/mitso23/training/resources/text3.diff");
	diff.findCommonLines();
}
