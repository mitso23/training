#include <vector>
#include "Stl/stl.h"

#include "dynamic_programming/coin_changing_problem.h"
#include "sorting/mergeSort.h"
#include "backtracking/labyrinth_wall.h"
#include "combinatronics/permutation.h"
#include "backtracking/collect_max_points_before_hitting_dead_end.h"
#include "recursion/sum_digits.h"
//#include "combinatronics/combination_k_out_of_n_items.h"
#include "trees/tree.h"
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
#include "trees/bottom_view_tree.h"
#include "hash/hash.h"
#include "trees/check_binary_tree_subtree_another.h"
#if 0
#include "trees/construct_tree_from_preorder_inorder_traversal.h"
#include "trees/remove_nodes_on_root_leaf_less_distance_k.h"
#endif
#include "trees/reverse_alternate_levels.h"
#include "heap/binary_heap.h"
#include "heap/k_largest_elements.h"
#include "heap/sort_almost_sorted_array.h"
#include "sorting/quicksort.h"
#include "sorting/find_element_sorted_rotated.h"
#include "trees/red_black_tree.h"
#include "trees/check_binary_tree_bst.h"
#include "linklist/mergesort.h"
#include "linklist/remove_duplicate.h"
#include "trees/k_smallest_element_bst.h"
#include "trees/sorted_array_to_bst.h"
#include "sorting/insertion_sort.h"
#include "arrays/generate_combinations_two_sorted_arrays.h"
#include "arrays/sort_array_zero_one_three.h"
#include "arrays/reverse_array_special_characters.h"
#include "arrays/count_triplets_sum_smaller_value.h"
#include "arrays/longest_sub_array_cont_seq.h"
#include "arrays/longest_sequence_array.h"
#include "graphs/find_all_possible_islands.h"
#include "strings/all_possible_palindromic_partition.h"
#include "arrays/print_array_spiral.h"
#include "trees/segment_tree.h"

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

#if 0
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
#endif
#if 0
	 Hash h(10);
	 h.addItem(1, 123);
	 int res = -1;
	 h.findValue(1, res);
	 std::cout << "value: " << res << std::endl;
#endif

#if 0
	Tree tree;
	tree.AddData(50);
	tree.AddData(30);
	tree.AddData(60);
	tree.AddData(20);
	tree.AddData(40);
	tree.AddData(1);
	tree.AddData(70);

	tree.PrintData();

	printBottomView(tree.m_root);
#endif
#if 0
	Tree tree1;
	tree1.AddData(50);
	tree1.AddData(30);
	tree1.AddData(60);
	tree1.AddData(20);
	tree1.AddData(40);
	tree1.AddData(1);
	tree1.AddData(70);
	tree1.PrintData();


	TreeIterator treeIter1(tree1.m_root);
	int result1;
	bool success1 = treeIter1.getNext(result1);

	Tree tree2;
	tree2.AddData(30);
	tree2.AddData(20);
	tree2.AddData(40);
	tree2.AddData(1);
	tree2.PrintData();

	int result2;
	TreeIterator treeIter2(tree2.m_root);
	bool success2 = treeIter2.getNext(result2);

	bool found = false;
	while(success1 && success2)
	{
		std::cout << "result1: " << result1 << " result2: " << result2 << std::endl;

		if (!found && result1 == result2)
		{
			found = true;
			success1 = treeIter1.getNext(result1);
			success2 = treeIter2.getNext(result2);
			std::cout << "found matching root: " << success1 << std::endl;
		}
		else if (found)
		{
			success1 = treeIter1.getNext(result1);
			success2 = treeIter2.getNext(result2);

			if (!success2)
			{
				std::cout << "subtree: " << std::endl;
			}
			else if (!(success1 && success2 && result1 == result2))
			{
				std::cout << "not a subtree" << std::endl;
				return 0;
			}
		}
		else
		{
			success1 = treeIter1.getNext(result1);
		}
	}
#endif

#if 0
	auto res = find_square_root(34567012, 10);
	std::cout << res << " res: " << " res*res: " << res*res << std::endl;
#endif

#if 0
	char* pre = "abcdefhg";
	char* inord = "dcfebahg";

	printPreorder(createTree(inord, pre, 0, strlen(inord)));
#endif
#if 0
	Tree tree1;
	tree1.AddData(50);

	tree1.AddData(30);

	tree1.AddData(25);
	tree1.AddData(20);
	tree1.AddData(26);


	tree1.AddData(35);
	tree1.AddData(34);
	tree1.AddData(36);

	tree1.AddData(60);

	tree1.AddData(65);
	tree1.AddData(64);
	tree1.AddData(66);

	tree1.AddData(55);
	tree1.AddData(54);
	tree1.AddData(56);


	tree1.PrintData();

	//remove_nodes_less_given_distance(&tree1.m_root, nullptr, false, 1, 10);
	MyNodeInfo* __arr[10];
	std::queue<MyNodeInfo> q;
	auto size = 0U;
	reverseAlternateLevels(tree1.m_root, nullptr, 0, __arr, 0, size, q);

	auto l = [](int data) { std::cout << "data: " << data << std::endl; };
	tree1.iterateItems(l);
#endif

#if 0
	Heap p(10);
	p.insertItem(10);
	p.insertItem(4);
	p.insertItem(9);
	p.insertItem(2);
	p.insertItem(5);
	p.insertItem(11);
	p.sortHeap();
	p.printHeap();
#endif

#if 0
	int data[] = { 1, 7, 8, 10, 13, 5, 6, 100 };
	printKLargestElementsArray(data, sizeof(data)/sizeof(data[0]), 3);
#endif

#if 0
	int data[] = { 1, 3, 4 , 1 , 6};
	sort_almost_sorted_array(data, sizeof(data)/sizeof(data[0]), 2);
#endif

#if 0
	unsigned int data[] = {2, 1, 3, 10, 4, 9,5};
	mergeSort2(data,0, 6);

	for(unsigned int i=0; i< sizeof(data)/sizeof(data[0]); ++i)
	{
		std::cout << data[i] << std::endl;
	}
#endif

#if 0
	int data[] = {2, 1, 3, 4, 6, 7, 5, 9};
	quicksort(data, sizeof(data)/sizeof(data[0]));

	for(unsigned int i=0; i< sizeof(data)/sizeof(data[0]); ++i)
	{
		std::cout << data[i] << std::endl;
	}
#endif
#if 0
	int data[] = { 7,8,9,1,2,3,4,5,6 };
	find_element(data, sizeof(data)/sizeof(data[0]), 1);
#endif

#if 0
	Tree tree1;
	tree1.AddData(50);
	tree1.AddData(80);
	tree1.AddData(85);
	tree1.AddData(70);
	tree1.AddData(65);
	tree1.AddData(60);
	tree1.AddData(75);
	tree1.AddData(76);

	tree1.AddData(30);
	tree1.AddData(35);

	tree1.AddData(25);

	tree1.PrintData();

	auto current = tree1.GetMaxNode();

	while(current != nullptr)
	{
		std::cout << current->getData()<< std::endl;
		current = current->getPrevious();
	}
#endif

#if 0
	Tree tree1;
	tree1.AddData(50);
	tree1.AddData(80);
	tree1.AddData(85);
	tree1.AddData(70);
	tree1.AddData(65);
	tree1.AddData(60);
	tree1.AddData(75);
	tree1.AddData(76);

	tree1.AddData(30);
	tree1.AddData(35);

	tree1.AddData(25);

	tree1.PrintData();
	std::cout << checkBinaryTreeBst(tree1.m_root) << std::endl;
#endif

#if 0
	Tree tree1;
	tree1.AddData(11);
	tree1.AddData(5);
	tree1.AddData(14);

	tree1.PrintData();
	RotateLeft(tree1.m_root->m_left);
	tree1.PrintData();
#endif

#if 0
	RED_BLACK_TREE::RBTree tree;

	tree.insert(40);
	tree.insert(30);
	tree.insert(60);
	tree.insert(20);
	tree.insert(35);
	tree.insert(50);
	tree.insert(70);
	tree.insert(45);
	tree.insert(55);
	tree.insert(54);
	tree.insert(56);


	cout << "Inoder Traversal of Created Tree\n";
	tree.inorder();

	cout << "\n\nLevel Order Traversal of Created Tree\n";
	tree.levelOrder();
#endif

#if 0
	auto iter2 = tree.GetMaxNode();

	while(iter2 != nullptr)
	{
		std::cout << "max element: " << iter2->getData() << std::endl;
		iter2 = iter2->getPrevious();
	}
#endif

#if 0

	auto iter1 = tree.GetMinNode();

	while(iter1 != nullptr)
	{
		std::cout << " element: " << iter1->getData() << std::endl;
		iter1 = iter1->getNext();
	}

	std::cout << "found node: " << tree.findNode(56)->data << std::endl;
#endif

#if 0
	Node* head = nullptr;
	Node* a = nullptr;
	Node* b = nullptr;

	push_back(&head, 1);
	push_back(&head, 2);
	push_back(&head, 3);
	push_back(&head, 3);
	push_back(&head, 3);
	push_back(&head, 0);
	push_back(&head, 4);
	push_back(&head, 10);
	push_back(&head, 6);
	push_back(&head, 9);

	printList(head);

	MergeSortList(&head);
	std::cout << "sorted list is " << std::endl;
	printList(head);

	std::cout << "sorted unique list is " << std::endl;
	removeDuplicate(head);
	printList(head);
#endif

#if 0
	RED_BLACK_TREE::RBTree tree;
	tree.insert(20);
	tree.insert(8);
	tree.insert(22);
	tree.insert(4);
	tree.insert(12);
	tree.insert(10);
	tree.insert(14);
	tree.inorder();

	std::cout << "kth smallest element: " << find_k_smallest_element(tree.getRoot(), 7);

#endif

#if 0
	int data[] = { 1, 7, 3, 8, 9, 4, 6 };
	Heap heap(100, data, 7sizeof(data)/sizeof(data[0]));
	std::cout << "3 smallest: " << heap.getKthSmallestElement(3) << std::endl;
#endif

#if 0
	int data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	RED_BLACK_TREE::RBTree tree;
	sortedArrayToTree(data, 0, 9, &tree);
	tree.levelOrder();
#endif

#if 0
	unsigned const DATA_SIZE = 100;
	int* data = new int[DATA_SIZE];
	RED_BLACK_TREE::RBTree tree;
	std::map<int, int> map;
	Node* head = nullptr;
	Node* tail = nullptr;


	for(unsigned int i=0; i< DATA_SIZE; ++i)
	{
		data[i] = i;
		//tree.insert(i);
		//map[i] = i;

		push_front(&head, DATA_SIZE - i);
		tail = (tail == nullptr ? head : tail);
	}
	push_front(&head, 1);

	for(unsigned int i=0; i< DATA_SIZE; ++i)
	{
		data[i] = random() % DATA_SIZE;
		//tree.insert(data[i]);
		//map[i] = i;

		push_front(&head, data[i]);
		tail = (tail == nullptr ? head : tail);
	}

	//printList(head);
	//insertion_sort_list(&head, tail);
	MergeSortList(&head);
	//printList(head);
	//insertion_sort(data, DATA_SIZE);
	quicksort(data, DATA_SIZE);
	for(unsigned int i=0; i< DATA_SIZE; ++i)
	{
		std::cout << data[i] << std::endl;
	}
	//std::sort(data, data + DATA_SIZE);

	//tree.inorder();
#endif

#if 0
	unsigned int arr1[] = { 10, 15, 25};
	unsigned int arr2[] = { 1, 5, 20, 30};

	generatCombination(arr1, sizeof(arr1)/sizeof(arr1[0]), arr2, sizeof(arr2)/sizeof(arr2[0]));
#endif
#if 0
	//int inputData[] = { 0,0, 2, 2, 1, 0, 0, 2, 1, 2, 0, 1};
	int inputData[] = {2,1};
	sortArrayOneTwoThree(inputData, sizeof(inputData)/sizeof(inputData[0]));
	for(auto i = 0U; i<  sizeof(inputData)/sizeof(inputData[0]); ++i)
	{
		std::cout << inputData[i] << std::endl;
	}
#endif
#if 0
	char d[] = "ab$c";
	reverse_array_special_character(d);
	printf("%s", d);
#endif

#if 0
	//int ss[] = {14, 12, 11, 20};
	int ss[] = { 1, 2, 3 , 4};
	longest_cont_sub_array(ss, 4);
#endif

#if 0
	int ss[] = { 10, 11, 1, 2, 3, 4, 7, 8, 9, 12, 13};
	longest_sequence_array_2(ss, sizeof(ss)/sizeof(ss[0]));
#endif

#if 0
unsigned int mat[5][5] = {
							{1, 1, 0, 0, 0},
							{0, 1, 0, 0, 1},
							{1, 0, 0, 1, 1},
							{0, 0, 0, 0, 0},
							{1, 0, 1, 0, 1}
						 };

std::cout << "max islands: " << find_all_possible_islands(mat);
#endif

#if 0
char ptr[] = "Geeks";
std::vector<std::string> data;

allPossiblePallindromicPartitions(ptr, 0, data);
#endif

#if 0
int a[R][C] =
{
		{1,  2,  3,  4,  5,  6},
        {7,  8,  9,  10, 11, 12},
        {13, 14, 15, 16, 17, 18}
};

spiralPrint(a);
#endif

int input[] = { 1, 2, 3, 4 };
int segmentTree[sizeof(input)/sizeof(input[0]) * 2];
createSegmentTree(segmentTree, 0, input, 0, 3);

std::queue<int> q;
traverseSegmentTree(segmentTree, sizeof(input)/sizeof(input[0]) * 2, 0, q);

}
