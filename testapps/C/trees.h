#ifndef TREES_H
#define TREES_H

typedef struct _Node
{
	struct _Node* leftChild;
	struct _Node* rightChild;
	unsigned int data;

}Tree_Node;

void addNode(Tree_Node** root, unsigned int data)
{
	//The user could make sure that root is not null to avoid the penalty of checking this value
	if (*root == NULL)
	{
		*root= (Tree_Node*)malloc(sizeof(Tree_Node));
		(*root)->data= data;
		return;
	}
	else
	{
		Tree_Node* current= *root;

		while(current)
		{
			Tree_Node** ppsChild= NULL;

			if (current->data == data)
			{
				current->data = data;
				return;
			}
			else if (data < current->data)
			{
				ppsChild= &current->rightChild;
			}
			else
			{
				ppsChild= &current->leftChild;
			}

			if (*ppsChild)
			{
				current= *ppsChild;
				continue;
			}

			Tree_Node* temp = (Tree_Node*) malloc(sizeof(Tree_Node));
			*ppsChild = temp;
			(*ppsChild)->data = data;
			return;
		}
	}
}

void printTreeInorder(Tree_Node* root)
{
	if(root == NULL)
	{
		return;
	}

	printTreeInorder(root->leftChild);
	printf("value: %d\n", root->data);
	printTreeInorder(root->rightChild);
}

void printPreorder(Tree_Node* root)
{
	if(root == NULL)
	{
		return;
	}

	printf("%d\n", root->data);
	printPreorder(root->leftChild);
	printPreorder(root->rightChild);
}

void printPostOrder(Tree_Node* root)
{
	if (root == NULL)
		return;

	printPostOrder(root->leftChild);
	printPostOrder(root->rightChild);
	printf("%d\n", root->data);

}

void findNSmallestNumber(Tree_Node* root, int k)
{
	if(root == NULL)
	{
		return;
	}

	findNSmallestNumber(root->rightChild, k);
	--k;

	if( k == 0)
	{
		printf("The smallest number is %d",root->data);
		return;
	}

	findNSmallestNumber(root->leftChild, k);
}

void findCommonAnchestorTwoNodes(Tree_Node* root, Tree_Node* node1, Tree_Node* node2)
{
	if (root == NULL) return;

	if((node1->data >= root->data && node2->data <= root->data ) || (node1->data <= root->data  && node2->data >= root->data ))
	{
		printf("Common anchestor is %d\n", root->data);
		return;
	}
	else if (node1->data > root->data  && node2->data > root->data )
	{
		findCommonAnchestorTwoNodes(root->leftChild, node1, node2);
	}
	else
	{
		findCommonAnchestorTwoNodes(root->rightChild, node1, node2);
	}
}

#endif /* TREES_H_ */
