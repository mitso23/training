/*
 * amazon.cpp
 *
 *  Created on: 12 Nov 2017
 *      Author: mitso23
 */
#include "easy.h"
#include <iostream>

int main(int argc, char* argv[])
{

#if 0
	int arr[] = { 1, 4, -2 , 3 };
	//std::cout << "max profit: " << calculate_max_profit_stock_sell(arr, 4) << std::endl;
	checkIfTwoElementsAddToSum(arr, 4, -10);
#endif

	//runLengthEncoding("aaabbcc");

	DoubleList list;
	list.insertItem(1);
	list.insertItem(2);
	list.insertItem(3);
	list.insertItem(4);

	list.iterateItemsForward();
	std::cout << std::endl;

	rotateDoubleLinkList(list, 2);

	list.iterateItemsForward();

}

