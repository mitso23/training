#include "various.h"
#include "strings.h"

#include <vector>
#include <utils/utils.h>
#include "sorting.h"
#include "stl.h"

#include "coin_changing_problem.h"
#include "mergeSort.h"
#include "labyrinth_wall.h"
#include "permutation.h"
#include "collect_max_points_before_hitting_dead_end.h"
#include "sum_digits.h"
#include "combination_k_out_of_n_items.h"
#include "matching_brackets.h"
#include "graph.h"
#include "communication_stations.h"
#include "shortest_path.h"
#include "rat_in_a_maze.h"
#include "num_ways_to_reach_stairs.h"
#include "min_cost_in_matrix.h"
#include "list.h"
#include "N-Queen-Problem.h"
#include "HourGlassBacktracking.h"
#include "combination.h"

int main(int argc, char* argv[])
{
	//print_pyramid(7);
	//print_mutation("Dimitrios Symonidis");
	//std::cout << checkAllCharactersUnique("abcd") << std::endl;
	//std::cout << checkAllCharactersUnique("Dimitrios") << std::endl;
	//removeAllDuplicates(std::string("Dimitrios"));

#if 0
	BigInt b1("26");
	BigInt b2("995");

	std::cout << b1 + b2 << std::endl;
#endif

	//std::cout << power(2, 8) << std::endl;

	//std::vector<unsigned> x= { 1, 2 ,3 ,4 ,5, 1 ,1 ,1 ,1 ,1 ,1 , 1, 1 , 2, 2, 2, 3, 4, 5, 5};
	//knapsack(x, 9);
	//combinationStrings("abcde");
	//checkIfRotated("abcde", "eabcd");
	//std::vector <int> x = { 1, 1, 2, 2 , 3};
	//removeDuplicateFromSortedArray(x);
	//print_cont(x);

#if 0
	std::vector<int> x1= { 1, 2 , 3 };
	std::vector<int> x2= { 4, 5, 6 };
	std::vector<int> result;

	mergeSortedArrays(x1, x2, result);
	print_cont(result);
#endif
#if 0
	std::vector<unsigned> x1= { 1, 3, 7, 2 , 1, 5 , 6, 2, 9 };
	pairOfNumbersSumToGivenN(x1, 10);
#endif

	//auto result= checkPattern("/home/mitso23/skatttas", "/home/mitso23/skat*a");
	//auto result= checkPattern2("abkkjkjcdefg", "ab*cdefg");
	//auto result= checkPattern2("ab", "ab*");
	//auto result= checkPattern2("abcccccc", "ab*c");
	//auto result= checkPattern2("abccccccccd", "ab*c");
	//auto result= checkPattern2("a", "*a");
	//auto result= checkPattern2("abc", "ab*c");
	//auto result= checkPattern2("a", "*a");
	//auto result= checkPattern2("a", "*");
	//auto result= checkPattern2("abcdefg", "a*cd*fg");
	//auto result= checkPattern2("abcdefg", "a*cd*fg*");
	//auto result= checkPattern2("abcdefg", "a*cd*fkg");
	//auto result= checkPattern2("abcdefg", "a*cd*fgl");

	//unsigned x[] = { 4, 3, 1};
	//std::cout << calculateMinNumberCoins(x, sizeof(x)/sizeof(x[0]), 10);
	//std::cout << count3({2,3,4}, 60000) << std::endl;;
#if 0
	unsigned x[] = { 2, 1, 4, 3, 9, 4 , 8 , 1, 11 , 12 , 15 };
	mergeSort(x, 0, sizeof(x)/sizeof(unsigned));

	for (unsigned int i=0; i<  sizeof(x)/sizeof(unsigned); ++i)
	{
		std::cout << x[i] << std::endl;
	}
#endif

	const unsigned lab[][10] = {
							{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
							{ '#', '*', '#', '#', ' ', ' ', ' ', ' ', '#', '#'},
							{ '#', ' ', ' ', '#', ' ', '#', '#', ' ', ' ', '#'},
							{ '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '#'},
							{ '#', '#', ' ', ' ', '#', '#', ' ', ' ', ' ', '#'},
							{ ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
							{ ' ', '#', '#', ' ', ' ', '#', '#', '#', ' ', '#'},
							{ ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', '#'},
							{ '#', ' ', '#', '#', '#', '#', '#', '#', ' ', ' '},
						  };
	//findExit(lab, 9, {8, 9}, { 8, 1 });
	//Solve(0, 0);
#if 0
	char str[] = "abc";
	std::deque<char> d;
	permutate2(str, strlen(str), 0, d);
#endif
	//printf("%s", rotate(str, ));
	///move(0, 0, true, 0);
	//std::cout << MaxCount << std::endl;
	//std::cout << maxCoinsRec(arr, 0, 0, 1) << std::endl;
	//std::cout << sum_digits_unti_sum_one_digit(1239) << std::endl;

	//std::vector<int> x = {1, 2, 3, 4, 5, 6 , 7 , 8, 9 };
	//printCombination(x, 0, 4);
	//std::cout << match("{(3])()[}") << std::endl;

#if 0
	Graph g(7);
	g.AddEdge(0, 1);
	g.AddEdge(0, 2);
	g.AddEdge(1, 3);
	g.AddEdge(1, 4);
	g.AddEdge(2, 5);
	g.AddEdge(2, 6);

	//Add some loops
	g.AddEdge(6, 0);
	g.AddEdge(2, 1);
	g.AddEdge(2, 6);
	g.AddEdge(5, 6);

	//g.traverseGraphDfs(0);
	std::queue<int> q;
	g.traverseGraphBfs(0, q);
#endif

	//tryAllCombinations(9);
	//dijkstra(graph, 2);




#if 1
	int arr[6][6] = {

				{ 1, 1, 1, 1, 1, 1 },
				{ 0, 1, 0, 1, 0, 1 },
				{ 1, 1, 1, 1, 1, 1 },
				{ 0, 1, 0, 1, 0, 1 },
				{ 1, 1, 1, 1, 1, 1 },
				{ 0, 1, 0, 1, 0, 1 }

					};
#endif

#if 0
	int arr[6][6] = {

					{ 1, 1, 1, 1, 1, 1 },
					{ 1, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 1 },
					{ 1, 1, 1, 1, 1, 1 }

						};
#endif

#if 0
	//RDDDDRRUUUURRDDDDD
	auto res = printPath(arr, 6);
	for(auto item: res)
	{
		std::cout << item << std::endl;
	}
#endif

#if 0
	std::cout << stepDynamicProg(3) << std::endl;
	std::cout << stepNaive(3) << std::endl;


	std::cout << stepDynamicProg(100) << std::endl;
	std::cout << stepNaive(100) << std::endl;
#endif
#if 0
	unsigned int costMatrix[3][3] = { { 1, 1, 8 },
									  { 2, 3 ,1 },
									  { 4, 5, 1 }
								  };

	std::cout << minCostMatrix(costMatrix, 2, 2) << std::endl;
#endif

#if 0
	push_back(1);
	push_back(2);
	push_back(3);

	remove_back();
	printList();
#endif

#if 0
	int arr2[] = { 1, 2, 3};
	std::vector<int> d = { 1, 2 ,3 };
	//printCombination(d, 0, 2);
	printCombinations2(arr2, 3);
#endif

	//unsigned int board[8][8];
	//memset(board, 0, sizeof(board));

	//unsigned int board[2][2] = { { 0,0 }, { 0, 0} };
	//positionNQueens(0, 0, board, 0);
#if 0
	unsigned int A= 4;
	unsigned int B= 7;

	std::cout << std::boolalpha << run(4, 7, A, B, 5, 0) << std::endl;
#endif
	//char str[] = "1234";
	//permutate(str, 4, 0);

	//int arrr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
	//combination_sum(arrr, 9, 9);

	//Solve(0, 0);

	unsigned int data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
			16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
	unsigned int sum = 0;
	//knapsack(data, 0, sizeof(data) / sizeof(data[0]), sum, 32, 0, true);
	//std::cout << "min number of coins: " << minNumCoins << std::endl;
	std::cout << count3({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31}, 27000);


}
