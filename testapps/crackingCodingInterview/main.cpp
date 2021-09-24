#include "ArraysStrings.h"
#include "Trees.h"
#include "LinkList.h"
#include "Graphs.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <list>
#include <unordered_map>
#include <deque>
#include <memory>

using namespace std;

#include <iostream>
#include <deque>
using namespace std;

template <typename T, typename... Args>
std::unique_ptr<T> my_make_unique_ptr(Args&&... args)
{
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main(int argc, char* argv[])
{

#if 0
	for(unsigned int i=0; i< 1000000; ++i)
	{
		char str[100] = "  My name is  Dimitros   Symonidis  \0          ";
		ReplaceSpaceString(str, sizeof(str));
		//std::replace(str, str + 100, ' ', '%');
	}
#endif

	//char data[] = "aaabcccccaaa";
	//char data[] = "a";
	//char data[] = "aaaaaaaaa";
	//char data[] = "abcdefghccccccccc";
	//auto encPos = EncodeString(data);
	//std::cout << std::string(data + encPos, data + strlen(data)) << std::endl;
	//std::cout << std::hex << std::numeric_limits<int>::max() << std::endl;
	//std::cout << std::hex << std::numeric_limits<int>::min() << std::endl;

	//char data[] = "aaabbcccd";
	//char data[] = "aaa";
	//auto offset = RemoveDuplicates(data);
	//std::cout << std::string(data, data + offset) << std::endl;

	//unsigned int data[] = {3,8,7,3,9,1,5,8};
	//std::cout << findMaxStock(data, sizeof(data)/sizeof(unsigned)) << std::endl;

#if 0
	char data[] = {'(', '[', '{', '}', ']', ')'};
	Stack<sizeof(data)> st;
	std::cout << CheckProperString<sizeof(data)>(data, 0, sizeof(data), st) << std::endl;
#endif

#if 0
	{
		//ABBBA -> AA
		char data[] = "ABCCCCBBA";
		RemoveThreeConsecutiveChars(data);

		std::cout << data << std::endl;
	}

	{
		//B
		char data[] = "AAAAABBBBD";
		RemoveThreeConsecutiveChars(data);

		std::cout << data << std::endl;
	}

	{
		//ABC
		char data[] = "ABC";
		RemoveThreeConsecutiveChars(data);

		std::cout << data << std::endl;
	}

	{
		//BBBC --> C
		char data[] = "AAABBBC";
		RemoveThreeConsecutiveChars(data);

		std::cout << data << std::endl;
	}
#endif

#if 0
	Tree::Employee emp;
	emp.AddEmployee(2, 1);
	emp.AddEmployee(3, 1);
	emp.AddEmployee(4, 1);

	emp.AddEmployee(5, 3);
	emp.AddEmployee(6, 3);
	emp.AddEmployee(7, 3);

	emp.AddEmployee(9, 5);
	emp.AddEmployee(10, 5);

	emp.DisplayEmployee(1);
#endif

#if 0
	using namespace LinkList;
	int arr[] = {1, 2, 3, 4, 5, 6 };

	Node<int>* head = nullptr;
	CreateSingleList(arr, sizeof(arr)/sizeof(int), head);
	RemoveMiddleElement(head);
	DisplaySingleList(*head);
#endif

#if 0
	using namespace LinkList;
	Node<int> pool1[4];
	Node<int> pool2[4];

	Node<int>* head1 = &pool1[0];
	head1->next = &pool1[1];
	head1->next->next = &pool1[2];
	head1->next->next->next = &pool1[3];

	Node<int>* head2 = &pool2[0];
	head2->next = &pool2[1];
	head2->next->next = &pool2[2];
	head2->next->next->next = &pool2[3];
	head2->next->next->next->next = &pool1[2];

	std::cout << ReturnIntersectionPoint(head1, head2);
#endif

#if 0
	int arr[] = {8, 1, 3, 5, 6, 7, 9, 10};
	//int arr[] = {2, 1, 4, 3};
	//int arr[] = {1, 2, 3, 4};
	//int arr[] = {4,3,2,1};
	sort(arr, 0, 7);

	for(unsigned int i=0; i< sizeof(arr)/sizeof(int); ++i)
	{
		std::cout << arr[i] << std::endl;
	}
#endif

#if 0
	using namespace LinkList;
	int arr[] = {1, 2, 2, 1 };

	Node<int>* head = nullptr;
	CreateSingleList(arr, sizeof(arr)/sizeof(int), head);
	CheckIfLinkListPalindrome(head, sizeof(arr)/sizeof(arr[0]));
#endif

#if 0
	char word[][10] = {"abc", "bca", "dae", "dfg"};
	char output[2][10];
	findNumberOfWords(word, 4, 3, output);

	for(unsigned int i=0; i< 4; ++i)
	{
		std::cout << output[i] << std::endl;
	}
#endif

#if 0
	Graph<7> g;
	g.Add(0, 1, 10);
	g.Add(0, 2, 20);

	g.Add(1, 3, 30);
	g.Add(1, 4, 40);

	g.Add(2, 5, 50);
	g.Add(2, 6, 60);

	std::cout << std::boolalpha << g.CheckPath(2, 3);
#endif

#if 0
	int sorted[] = {0, 1, 2, 3, 4, 5, 6};
	Tree::BinNode* root = nullptr;
	Tree::CreateBinaryTree(sorted, 0, sizeof(sorted)/sizeof(sorted[0]) - 1, root);
	PrintBinaryTree(root);
	//std::cout << CheckTreeBalanced(root) << std::endl;
	//std::cout <<  Tree::CheckTreeBinarySearch(root, 100, -1) << std::endl;
	Tree::FindCommonAncestor(root, root->left->right, root->right->right);
#endif

#if 0
	Graph2<5> graph;
	graph.AddNode('a');
	graph.AddNode('b');
	graph.AddNode('c');
	graph.AddNode('d');
	graph.AddNode('e');

	graph.AddEdge(0, 1);
	graph.AddEdge(0, 2);
	graph.AddEdge(2, 3);
	graph.AddEdge(2, 4);
	graph.AddEdge(3, 4);

	graph.TopologicalSort(0);
#endif

	#if 0
	Tree::BinNode* root = new Tree::BinNode(5);
	root->left = new Tree::BinNode(3);
	root->right = new Tree::BinNode(7);
	root->right->right = new Tree::BinNode(8);
	root->right->left = new Tree::BinNode(9);
	//root->right->left = new Tree::BinNode(9);

	Tree::BinNode* root2 = new Tree::BinNode(7);
	root2->right = new Tree::BinNode(8);
	root2->left = new Tree::BinNode(9);

	std::cout << Tree::CheckSubTree(root, root2) << std::endl;
	#endif

	auto ptr = my_make_unique_ptr<int>(1);
	std::shared_ptr<int> sp(std::move(ptr));
	std::weak_ptr<int> wp(sp);


	std::cout << *wp.lock() << std::endl;
}


