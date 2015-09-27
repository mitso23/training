#include "FileDiff.h"

#include <iostream>
#include <utils/utils.h>
#include <algorithm>

int main(int argc, char* argv[])
{
	FileDiff diff("/home/mitso23/training/resources/text1_diff.c", "/home/mitso23/training/resources/text2_diff.c");
	diff.outputDiffToDisk();
}
