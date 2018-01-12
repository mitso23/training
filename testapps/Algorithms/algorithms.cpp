#include "strings.h"

#include <vector>

#include "Stl/stl.h"

#include "dynamic_programming/coin_changing_problem.h"
#include "sorting/mergeSort.h"
#include "backtracking/labyrinth_wall.h"
#include "combinatronics/permutation.h"
#include "backtracking/collect_max_points_before_hitting_dead_end.h"
#include "recursion/sum_digits.h"
#include "combinatronics/combination_k_out_of_n_items.h"
#include "parsers/matching_brackets.h"
#include "graphs/graph.h"
#include "matrix/communication_stations.h"
#include "backtracking/rat_in_a_maze.h"
#include "recursion/num_ways_to_reach_stairs.h"
#include "backtracking/min_cost_in_matrix.h"
#include "linklist/list.h"
#include "backtracking/N-Queen-Problem.h"
#include "backtracking/HourGlassBacktracking.h"
#include "combinatronics/combination.h"
#include "dynamic_programming/binominal_coefficents.h"
#include "dynamic_programming/paintfence_algorithm.h"
#include "combinatronics/Knapsack.h"
#include "backtracking/fillCanvas.h"
#include "backtracking/WordBreaking.h"
#include "backtracking/longest_path_hurdels.h"
#include "combinatronics/numberofPossibleScores.h"
#include "backtracking/find_path_magic_triangle.h"
#include "backtracking/escape_from_room.h"
#include "backtracking/pattern_matching.h"
#include "dynamic_programming/longest_common_subsequence.h"
#include "backtracking/max_non_parallel_lines.h"
#include "backtracking/max_bins_2d_array.h"
#include "recursion/numers_have_four_digit.h"
#include "graphs/shortest_path_graph_naive.h"
#include "backtracking/find_edge_picture.h"
#include "graphs/shortest_path_warmhole.h"
#include "sorting/warmhole_contest.h"
#include "image_processing/k_means_algorithm.h"
#include "graphs/shortest_path_floyd.h"
#include "trees/tree.h"
#include "trees/check_tree_balanced.h"
#include "graphs/union_find_detect_circle.h"
#include "graphs/graph_mst_prime.h"
#include "graphs/topological_sort.h"
#include "trees/convert_bst_sum_tree.h"
#include "graphs/boggle.h"
#include "graphs/find_articulation_point.h"
#include "trees/find_minimum_height_binary_tree.h"
#include "trees/find_common_anchestor.h"
#include "trees/find_distance_between_two_nodes.h"

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

	std::cout << minCostMatrix(costMatrix, 2, 2, 0) << std::endl;
#endif

#if 0
	unsigned int costMatrix[2][2] = { { 1, 2},
									  { 3, 4},
									};
	std::cout << minCostMatrix(costMatrix, 1, 1, 0) << std::endl;

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

#if 0
	unsigned int data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
			16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
	unsigned int sum = 0;
	//knapsack(data, 0, sizeof(data) / sizeof(data[0]), sum, 32, 0, true);
	//std::cout << "min number of coins: " << minNumCoins << std::endl;
	std::cout << count3({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31}, 27000);
#endif

#if 0
	//std::cout << binomialCoeffBottomUp(5, 2) << std::endl;
	int result[2];
	int data[] = { 1, 2, 3, 4,5};
	for(unsigned int i=0; i< 1; ++i)
	{
		printCombination_rec_2(result, data + i, 0, (sizeof(data)/sizeof(data[0])) - i, 3, 0);
	}
#endif

#if 0
	long unsigned int count = 0;
	int sameColourCount = 0;
	int numberColours = 3;
	int numberPosts = 4;
	countWays(numberColours, 0, numberPosts, sameColourCount, 0, count);
	std::cout << count << std::endl;
	std::cout << countWays(numberPosts, numberColours) << std::endl;
	//std::cout << countWays2(numberPosts, numberColours) << std::endl;
#endif
#if 0
	int data[][4] ={ {  0, 0,  0,  0 },
					 {  0, 0,  1,  0 },
					 {  0, 0,  0,  0 },
					 {  0, 1,  1,  1 },
					 {  0, 0,  1,  0 },
					 {  1, 0,  0,  0 },
					 {  0, 1,  1,  0 },
				   };

	fillCanvas(data, 7, 1, 0, 0);
	printCanvas(data, 7);
#endif
#if 0
	const char sentence[] = "IamGreek";
	char* dict[100000];

	ifstream f("/usr/share/dict/words");
	unsigned int i=0;
	while(f)
	{
		std::string skata;
		f >> skata;
		dict[i] = static_cast<char*>(malloc(sizeof(char)*(skata.size() + 1)));
		strcpy(dict[i++], skata.c_str());
	}

	printAllWords_rec(sentence, (const char**)dict, i, 0, 0, 0);
#endif

#if 0
	int path[Y_MAX][X_MAX] = { { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
							   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
							   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
							 };
#endif

#if 1
	int path[Y_MAX][X_MAX] = { { 1, 1, 1 },
							   { 1, 1, 1 },
							   { 1, 1, 1 }
							 };
#endif
#if 0
	int currentLength = 0;
	memset(visitedPath, false, sizeof(visitedPath));
	findLongestPath(path, 0, 0, 0, currentLength, 2, 2);

	std::cout << "num time called: " << numberRecursionCalled << std::endl;
	std::cout << "length: " << maxLength << std::endl;
#endif

#if 0
	unsigned int scores[] = {1, 1, 1, 1, 2};
	std::cout << calculatePossibilities(5, scores);
#endif

#if 0
	unsigned steps;
	NumberSteps(100, 1, 1, steps);

	std::cout << minSteps << std::endl;
#endif

#if 0
	srcDstVisited[0].srcDst.src = 1;
	srcDstVisited[0].srcDst.dst = 6;

	srcDstVisited[1].srcDst.src = 3;
	srcDstVisited[1].srcDst.dst = 4;

	srcDstVisited[2].srcDst.src = 5;
	srcDstVisited[2].srcDst.dst = 2;

	unsigned count = 1;
	FindMinTimeEscape(0, 0, count, 0, 3);

	std::cout << "total count: " << maxCount << std::endl;
#endif

#if 0
	char str[] = "KKaaabbbaaaccaaaddccddaaabbbaaaccaaaddccddaaabbbaaaccaaaddccddaaabbbaaaccaaaddccddKS";
	char pattern[] = "KabacadcdabacadcdabacadcdabacadcdK";
	bool result = pattern_match(str, 0, pattern, 0);
	std::cout << "result: " << std::boolalpha << result << std::endl;
#endif

#if 0
	char str1[] = "ABCDGH";
	char str2[] = "AEDFHR";

	std::cout << longestCommonSubSequence(str1, str2) << std::endl;
#endif

#if 0
	arrLines[0].x = -2;
	arrLines[0].y = -3;

	arrLines[1].x = -2;
	arrLines[1].y = 3;

	arrLines[2].x = 2;
	arrLines[2].y = 3;

	arrLines[3].x = 2;
	arrLines[3].y = -3;

	findMaxNumberLines();

	std::cout << arrAnglesPos << std::endl;
#endif
#if 0
	memset(binCoordinates, 0, sizeof(binCoordinates));
	memset(BinArray, 0, sizeof(BinArray));

	maxBinsArray(0, 0, 9, 3, 0, 0);

	std::cout << "max bin count: " << maxBinCount << std::endl;
#endif

#if 0
	std::cout << numbers_contain_digits(183781273, 100000000) << std::endl;
	//std::cout << countNumbersWith4(183781273) << std::endl;
#endif

#if 0
	fillGraph();
	auto currentDistance = 0;
	for(unsigned int src= 0; src < 4; ++src)
	{
		for(unsigned int dst=0; dst < 4; ++dst)
		{
			FindShortestDestination(src, dst, 4, currentDistance);
			std::cout << "min distance from: " << src << " to: " << dst << " is: " << MinDistancePath << std::endl;
			MinDistancePath = 0xFFFF;
		}
	}
#endif

#if 0
	int startY = -1;
	int startX = -1;
	int count = 0;

	findFirstEdge(startY, startX, MAX_PICTURE_SIZE);
	std::cout << "startY: " << startY << " startX: " << startX << std::endl;
	findEdge(startY, startX, MAX_PICTURE_SIZE, count, startY, startX);
#endif

#if 0
	Coordinate a;
	a.x = 1;
	a.y = 1;

	Coordinate b;
	b.x = 2;
	b.y = 2;

	Coordinate c;
	c.x = 3;
	c.y = 3;

	Coordinate d;
	d.x = 4;
	d.y = 4;

	Coordinates[0] = a;
	Coordinates[1] = b;
	Coordinates[2] = c;
	Coordinates[3] = d;

	// a->b
	wormHoldeMap[0][1] = 1;
	wormHoldeMap[1][0] = 1;

	// b->c
	wormHoldeMap[1][2] = 1;
	wormHoldeMap[2][1] = 1;

	// b->d
	wormHoldeMap[1][3] = 1;
	wormHoldeMap[3][1] = 1;

	// c->d
	wormHoldeMap[2][3] = 1;
	wormHoldeMap[3][2] = 1;

	// a->d
	wormHoldeMap[0][3] = 1;
	wormHoldeMap[3][0] = 1;

	findMinDistance(0, 3, 0);

	std::cout << "min distance: " << minPathDistance << std::endl;
#endif

#if 0
	//std::cout << shortestDuration() << std::endl;
	std::vector<int> v = { 1, 4, 4, 4, 5 ,12};
	auto start = ::lower_bound(v.begin(), v.end(), 4);
	auto end = ::upper_bound(v.begin(), v.end(), 4);

	v.erase(remove_duplicates(v.begin(), v.end()), v.end());

	for(auto item: v)
		std::cout << item << std::endl;
#endif

#if 0
	KMeansCoordinate groups[2];
	groups[0].data = 9;
	groups[0].x = 0;
	groups[0].y = 0;

	groups[1].data = 10;
	groups[1].x = 1;
	groups[1].y = 3;

	groups[2].data = 12;
	groups[2].x = 0;
	groups[2].y = 4;

	partition(groups, 3);
	printGroups(3);
#endif

#if 0
	Graph graph(9);
	graph.AddEdge(0, std::make_pair(1, 4));
	graph.AddEdge(1, std::make_pair(0, 4));

	graph.AddEdge(0, std::make_pair(7, 8));
	graph.AddEdge(7, std::make_pair(0, 8));

	graph.AddEdge(1, std::make_pair(7, 11));
	graph.AddEdge(7, std::make_pair(1, 11));

	graph.AddEdge(1, std::make_pair(2, 8));
	graph.AddEdge(2, std::make_pair(1, 8));

	graph.AddEdge(2, std::make_pair(8, 2));
	graph.AddEdge(8, std::make_pair(2, 2));

	graph.AddEdge(2, std::make_pair(5, 4));
	graph.AddEdge(5, std::make_pair(2, 4));

	graph.AddEdge(2, std::make_pair(3, 7));
	graph.AddEdge(3, std::make_pair(2, 7));

	graph.AddEdge(8, std::make_pair(7, 7));
	graph.AddEdge(7, std::make_pair(8, 7));

	graph.AddEdge(7, std::make_pair(6, 1));
	graph.AddEdge(6, std::make_pair(7, 1));


	graph.AddEdge(5, std::make_pair(6, 2));
	graph.AddEdge(6, std::make_pair(5, 2));

	graph.AddEdge(8, std::make_pair(6, 6));
	graph.AddEdge(6, std::make_pair(8, 6));

	graph.AddEdge(3, std::make_pair(4, 9));
	graph.AddEdge(4, std::make_pair(3, 9));

	graph.AddEdge(3, std::make_pair(5, 14));
	graph.AddEdge(5, std::make_pair(3, 14));

	graph.AddEdge(4, std::make_pair(5, 10));
	graph.AddEdge(5, std::make_pair(4, 10));

	graph.calculateMinDistanceDijkta();
#endif

#if 0
	auto min = std::numeric_limits<int>::max();

	for(unsigned int src= 0; src< 4; ++src)
	{
		for(unsigned int dst=0; dst< 4; ++dst)
		{
			for(unsigned int k=0; k< 4; ++k)
			{
				auto value = calculateMinDistance(src, dst, k);

				if (value < min)
				{
					min = value;
				}
			}

			std::cout << "src: " << src << " dst: " << dst << " min: " << min << std::endl;
			min = std::numeric_limits<int>::max();
		}
	}

	std::cout << min << std::endl;
#endif

#if 0
	Tree tree;
	tree.AddData(30);

	tree.AddData(15);
	tree.AddData(41);

	tree.AddData(16);
	tree.AddData(17);

	tree.AddData(40);
	tree.AddData(42);

	std::cout << CheckTreeBalanced(tree.m_root);
#endif


#if 0
	tree.AddData(40);
	tree.AddData(50);
	tree.AddData(51);
	tree.AddData(52);
	tree.AddData(53);

	tree.AddData(13);
	tree.AddData(21);
	tree.AddData(12);
	tree.AddData(11);
	tree.AddData(10);


#endif

#if 0
	Graph graph(3);
	graph.AddEdge(0, std::make_pair(1, 1));
	graph.AddEdge(1, std::make_pair(2, 1));
	graph.AddEdge(2, std::make_pair(0, 1));

	std::cout << CheckIfLoopGraph(&graph) << std::endl;
#endif

#if 0
	Graph graph(4);

	graph.AddEdge(0, std::make_pair(1, 4));
	graph.AddEdge(1, std::make_pair(0, 4));

	graph.AddEdge(1, std::make_pair(2, 2));
	graph.AddEdge(2, std::make_pair(1, 2));


	graph.AddEdge(2, std::make_pair(0, 1));
	graph.AddEdge(0, std::make_pair(2, 1));

	graph.AddEdge(1, std::make_pair(3, 5));
	graph.AddEdge(3, std::make_pair(1, 5));

	graph.AddEdge(0, std::make_pair(3, 7));
	graph.AddEdge(3, std::make_pair(0, 7));

	calculateMstTree(&graph);
#endif

#if 0
	  int __graph[5][5] = {{0, 2, 0, 6, 0},
	                      {2, 0, 3, 8, 5},
	                      {0, 3, 0, 0, 7},
	                      {6, 8, 0, 0, 9},
	                      {0, 5, 7, 9, 0},
	                     };

	  Graph graph(&__graph[0][0], 5, 5);
	  //graph.traverseGraphDfs(0);
	  calculateMstTree(&graph);
#endif

#if 0
	 Graph graph(6);

	 graph.AddEdge(0, std::make_pair(1, 4));
	 graph.AddEdge(1, std::make_pair(2, 4));
	 graph.AddEdge(1, std::make_pair(3, 4));
	 graph.AddEdge(0, std::make_pair(4, 4));
	 graph.AddEdge(5, std::make_pair(4, 4));

	 topological_sort(&graph, 0);
#endif

#if 0

	 Tree tree;
	 tree.AddData(10);

	 tree.AddData(5);
	 tree.AddData(4);
	 tree.AddData(6);

	 tree.AddData(15);
	 tree.AddData(14);
	 tree.AddData(16);

	 tree.PrintData();

	 convert_bst_sum_tree(tree.m_root);
	 tree.iterateItems([](int data){ std::cout << data << std::endl;});

#endif
#if 0
	 char* dictionary[100000];

	 ifstream f("/usr/share/dict/words");
	 unsigned int i = 0;

	 while(f >> (dictionary[i++] = (char*)malloc(sizeof(char)*100)));
	 std::sort(dictionary, dictionary + i);

	 //for(unsigned int j=0; j< i; ++j)
		 //std::cout << dictionary[j] << std::endl;

	 char boggle[3][3]   = {{'g','i','z'},
	                        {'u','e','k'},
	                        {'q','s','e'}};

	 std::string str;
	 boggleTreeRoot = new BoggleTree();
	dictionaryToBoggleTree(dictionary, i);

#if 0
	 std::cout << "slow" <<std::endl;
	 find_all_possible_words_boggle(dictionary, 99000, boggle, 0, 0, str, true);
#endif
	 std::cout << "fast" <<std::endl;
	 find_all_possible_words_boggle(dictionary, 99000, boggle, 0, 0, str, false);


	 //std::cout << checkWordExists("beautiful", boggleTreeRoot);
	 //std::deque<char> d;
	 //printBoggleDictionary(boggleTreeRoot, d);
	 //my_binary_search("quiz", dictionary, i, true);
#endif

#if 0
	 MyGraph2 graph;
	 graph.AddEdge(0, 1);
	 graph.AddEdge(1, 0);

	 graph.AddEdge(1, 2);
	 graph.AddEdge(2, 1);

	 graph.AddEdge(0, 2);
	 graph.AddEdge(2, 0);

	 graph.AddEdge(2, 4);
	 graph.AddEdge(4, 2);

	 graph.AddEdge(1, 3);
	 graph.AddEdge(3, 1);

	 graph.AddEdge(0, 3);
	 graph.AddEdge(3, 0);

	 graph.AddEdge(4, 1);
	 graph.AddEdge(1, 4);

	 graph.Dfs(0);
#endif

	 Tree tree;
	 tree.AddData(50);
	 tree.AddData(30);
	 tree.AddData(60);
	 tree.AddData(20);
	 tree.AddData(40);
	 tree.AddData(1);
	 tree.AddData(70);

	 tree.PrintData();
	 auto res = findCommonAnchestor(tree.m_root, 20, 30);

	 std::cout << "distance: " << res->m_data <<  std::endl;

}
