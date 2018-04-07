#ifndef RED_BLACK_TREE_H_
#define RED_BLACK_TREE_H_

namespace RED_BLACK_TREE
{

enum Color {RED, BLACK};


// What kind of data is this going to return <T>
struct IteratorInterface
{
	virtual IteratorInterface* getPrevious() = 0;
	virtual IteratorInterface* getNext() = 0;
	virtual int  getData() = 0;
};

struct Node
{
    int data = 0;
    bool color = false;
    Node *left, *right, *parent;
    unsigned int numLeftCount = 0;

    // Constructor
    Node(int data)
    {
       this->data = data;
       left = right = parent = NULL;
    }

    Node()
    {
    	this->data = data;
    	left = right = parent = NULL;
    }

    void setData(int data)
    {
    	this->data = data;
    }
};


static Node nodesPool[10000000];
static int nodesPoolCounter = 0;

class RBTree
{

public:
	void insert(const int& data)
	{
		Node* newNode = &nodesPool[nodesPoolCounter++];
		newNode->setData(data);

		if (!m_minNode)
		{
			m_minNode = newNode;
		}

		if (!m_maxNode)
		{
			m_maxNode = newNode;
		}

		m_root = BSTInsert(m_root, newNode);

		fixViolation(m_root, newNode);
	}

	Node* findNode(const int data)
	{
		return findNodeHelper(m_root, data);
	}

	void inorder()
	{
		inorderHelper(m_root);
	}

	void levelOrder()
	{
		levelOrderHelper(m_root);
	}

	void testRotateRight(Node* node)
	{
		rotateRight(m_root, node);
		std::cout << "new root: " << m_root->data << std::endl;
	}

	void testRotateLeft(Node* node)
	{
		rotateLeft(m_root, m_root);
		std::cout << "new root: " << m_root->data << std::endl;
	}

	Node* getRoot()
	{
		return m_root;
	}

	struct Iterator
	{
		Iterator(Node* node, Node* root, Node* minNode, Node* maxNode)
		: m_current(node)
		, m_root(root)
		, m_minNode(minNode)
		, m_maxNode(maxNode)
		{

		}

		Node* getPreviousHelper(Node* node)
		{
			if (!node)
			{
				//std::cout << "null node: " << std::endl;
				return nullptr;
			}

			if (m_current == m_minNode)
			{
				//std::cout << "the end: " << std::endl;
				return nullptr;
			}

			//std::cout << "node: " << node->data <<  " current: " << m_current->data << std::endl;

			if (node->right && node->right->data < m_current->data)
			{
				//std::cout << "right" << std::endl;
				return getPreviousHelper(node->right);
			}

			if (node->left && node->left->data < m_current->data)
			{
				if (node->left->right == nullptr && node->data < m_current->data)
				{
					//std::cout << "found left: " << node->data << std::endl;
					return node;
				}
				else
				{
					//std::cout << "left" << std::endl;
					return getPreviousHelper(node->left);
				}
			}

			if (node->data < m_current->data)
			{
				//std::cout << "found current" << node->data << std::endl;
				return node;
			}

			if (node->parent && node->parent->data < m_current->data)
			{
				//std::cout << "found parent: " << node->parent->data << std::endl;
				return node->parent;
			}

			//std::cout << "parent" << std::endl;
			return getPreviousHelper(node->parent);
		}

		Iterator* getPrevious()
		{
			m_current = getPreviousHelper(m_current);

			if (m_current)
				return new Iterator(m_current, m_root, m_minNode, m_maxNode);

			return nullptr;
		}

		Node* getNextHelper(Node* node)
		{
			if (!node)
			{
				std::cout << "empty: " << std::endl;
				return nullptr;
			}

			//std::cout << " current node: " << node->data << std::endl;

			if (m_current == m_maxNode)
			{
				//std::cout << " the end: " << std::endl;
				return nullptr;
			}

			if (node->left && node->left->data > m_current->data)
			{
				//std::cout << " going left: " << std::endl;
				return getNextHelper(node->left);
			}

			if (node->right && node->right->data >  m_current->data)
			{
				//std::cout << " going right: " << std::endl;
				return getNextHelper(node->right);
			}

			if (node->data > m_current->data)
			{
				//std::cout << "returning current: " << std::endl;
				return node;
			}

			if (node->parent && node->parent->data > m_current->data)
			{
				//std::cout << " returning parent: " << std::endl;
				return node->parent;
			}

			if(node->parent)
			{
				//std::cout << " going to parent: " << node->parent << std::endl;
				return getNextHelper(node->parent);
			}

			//std::cout << " returning null " << std::endl;
			return nullptr;
		}

		Iterator*  getNext()
		{
			m_current = getNextHelper(m_current);

			if (m_current)
			{
				return new Iterator(m_current, m_root, m_minNode, m_maxNode);
			}

			return nullptr;
		}

		unsigned int getData()
		{
			return m_current->data;
		}

	private:
		Node* m_current;
		Node* m_root;
		Node* m_minNode;
		Node* m_maxNode;
	};

	Iterator* GetMaxNode()
	{
		return new Iterator(m_maxNode, m_root, m_minNode, m_maxNode);
	}

	Iterator* GetMinNode()
	{
		return new Iterator(m_minNode, m_root, m_minNode, m_maxNode);
	}

private:
	/* A utility function to insert a new node with given key
	   in BST */
	Node* BSTInsert(Node* root, Node *pt)
	{
	    /* If the tree is empty, return a new node */
	    if (root == NULL)
	       return pt;

	    /* Otherwise, recur down the tree */
	    if (pt->data < root->data)
	    {
	        root->left  = BSTInsert(root->left, pt);
	        root->left->parent = root;
	        root->numLeftCount+=1;

	        if (!m_minNode || m_minNode->data > root->left->data)
	        {
	        	m_minNode = root->left;
	        }

	    }
	    else if (pt->data > root->data)
	    {
	        root->right = BSTInsert(root->right, pt);
	        root->right->parent = root;

	        if (!m_maxNode || m_maxNode->data < root->right->data)
	        {
	        	m_maxNode = root->right;
	        }
	    }

	    /* return the (unchanged) node pointer */
	    return root;
	}

	void fixViolation(Node *&root, Node *pt)
	{
		 Node *parent_pt = NULL;
		 Node *grand_parent_pt = NULL;
		 Node *uncle_pt = NULL;

		 while((pt != root) && (pt->color != BLACK) && pt->parent->color == RED)
		 {
			 // to have a violation we need to have parent_pt and grand_parent_pt
			 parent_pt = pt->parent;
			 grand_parent_pt = parent_pt->parent;

			 //uncle_pt can be NULL
			 uncle_pt = grand_parent_pt->right;

			 //PARENT AND GRANDPARENT ARE ON THE LEFT SIDE
			 if (parent_pt->parent = grand_parent_pt)
			 {
				 //uncle is RED, only recoloring is required
				 if ((uncle_pt != NULL && uncle_pt->color == RED))
				 {
					 uncle_pt->color = BLACK;
					 parent_pt->color = BLACK;
					 grand_parent_pt->color = RED;
					 pt = grand_parent_pt;

				 }
				 else
				 {
					 if (pt == pt->parent->left)
					 {
						 rotateRight(m_root, grand_parent_pt);
						 std::swap(parent_pt->color, grand_parent_pt->color);
						 pt = parent_pt;
					 }
					 else
					 {
						 rotateLeft(m_root, parent_pt);
						 pt = parent_pt;
						 parent_pt = pt->parent;
					 }
				 }
			 }
			 else
			 {
				 Node *uncle_pt = grand_parent_pt->left;

				/*  Case : 1
				 The uncle of pt is also red
				 Only Recoloring required */
				if ((uncle_pt != NULL) && (uncle_pt->color == RED))
				{
					grand_parent_pt->color = RED;
					parent_pt->color = BLACK;
					uncle_pt->color = BLACK;
					pt = grand_parent_pt;
				}
				else
				{
					/* Case : 2
					 pt is left child of its parent
					 Right-rotation required */
					if (pt == parent_pt->left)
					{
						rotateRight(root, parent_pt);
						pt = parent_pt;
						parent_pt = pt->parent;
					}

					/* Case : 3
					 pt is right child of its parent
					 Left-rotation required */
					rotateLeft(root, grand_parent_pt);
					swap(parent_pt->color, grand_parent_pt->color);
					pt = parent_pt;
				}
			}
		 }

		 root->color = BLACK;
	}

	Node* findNodeHelper(Node* node, int data)
	{
		if (!node)
		{
			return nullptr;
		}

		if (node->data == data)
		{
			return node;
		}
		else if (data < node->data)
		{
			return findNodeHelper(node->left, data);
		}
		else
		{
			return findNodeHelper(node->right, data);
		}
	}

	// A recursive function to do level order traversal
	void inorderHelper(Node *root)
	{
		if (root == NULL)
			return;

		inorderHelper(root->left);
		cout << "data: " << root->data << " left count " << root->numLeftCount << std::endl;
		inorderHelper(root->right);
	}

	// Utility function to do level order traversal
	void levelOrderHelper(Node *root)
	{
		if (root == NULL)
			return;

		std::queue<Node *> q;
		q.push(root);

		while (!q.empty())
		{
			Node *temp = q.front();
			cout << temp->data << "  ";
			q.pop();

			if (temp->left != NULL)
				q.push(temp->left);

			if (temp->right != NULL)
				q.push(temp->right);
		}
	}

	/// Example where g -> pt
	///
	///        g  -->pt            p
	///     p    u       --->   x     g
	///   x   p_r                 p_r   u
	///
	void rotateRight(Node *&root, Node* pt)
	{
		Node *pt_left = pt->left;

		pt->left = pt_left->right;

		if (pt->left != NULL)
		{
			pt->left->parent = pt;
		}

		pt_left->parent = pt->parent;

		if (pt->parent == NULL)
		{
			root = pt_left;
		}
		else if (pt == pt->parent->left)
		{
			pt->parent->left = pt_left;
		}
		else
		{
			pt->parent->right = pt_left;
		}

		pt_left->right = pt;
		pt->parent = pt_left;
	}

	///         pt
	///   p_l       p_r
	///
	void rotateLeft(Node *& root, Node *pt)
	{
		Node* newRoot = pt->right;

		pt->right = newRoot->left;
		if (pt->right)
		{
			pt->right->parent = pt;
		}

		newRoot->parent = pt->parent;

		if (pt->parent == NULL)
		{
			root = newRoot;
		}
		else if (pt == pt->parent->left)
		{
			pt->parent->left = newRoot;
		}
		else
		{
			pt->parent->right = newRoot;
		}

		newRoot->left = pt;
		pt->parent = newRoot;
	}

private:
	Node* m_root = nullptr;
	Node* m_minNode = nullptr;
	Node* m_maxNode = nullptr;
};


}
#endif /* RED_BLACK_TREE_H_ */
