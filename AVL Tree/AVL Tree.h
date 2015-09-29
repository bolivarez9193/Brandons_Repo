#include <iostream>
using namespace std;

class avlTree
{
private:
	class node
	{
	public:
		int data;
		node * left;
		node * right;
		int height;
		node(int x)
		{
			data=x;
			left=NULL;
			right=NULL;
			height = 0;
		}
	};

	node * root;
	void leftRotation(node * &r)
	{
		node * a = r;
		node * b = a->right;
		node * bl = b->left;

		r = b;
		b->left = a;
		a->right = bl;

		//update heights
		a->height = 1 + max(getHeight(a->left), getHeight(a->right));
		b->height = 1 + max(getHeight(a->left), getHeight(a->right));
	}
	void rightRotation(node * &r)
	{
		node * a = r;
		node * b = a->left;
		node * br = b->right;

		r = b;
		b->right = a;
		a->left = br;

		//update heights
		a->height = 1 + max(getHeight(a->left), getHeight(a->right));
		b->height = 1 + max(getHeight(a->left), getHeight(a->right));
	}
	void rightLeftRotation(node * &r)
	{
		rightRotation(r->right);
		leftRotation(r);
	}
	void leftRightRotation(node * &r)
	{
		leftRotation(r->left);
		rightRotation(r);
	}
	int getHeight(node * r)
	{
		if(r == NULL)
			return -1;
		else
			return r -> height;
	}
	void performRotation(node * &r)
	{
		// left imbalance
		if(getHeight(r->right) > getHeight(r->left) + 1)
		{
			if ( getHeight(r->right->right) > getHeight(r->right->left))
			{
				leftRotation(r);
			}
			else
			{
				rightLeftRotation(r);
			}
		}
		//right imbalance
		if(getHeight(r->left) > getHeight(r->right) + 1)
		{
			if (getHeight(r->left->left) > getHeight(r->left->right))
			{
				rightRotation(r);
			}
			else
			{
				leftRightRotation(r);
			}
		}
	}
	//insert x into tree rooted at r
	void insert(node * &r, int x)
	{
		if( r==NULL )
		{
			r = new node(x);
		}
		else
		{
			if( x < r->data )
			{
				insert(r->left, x);
				performRotation(r);
			}
			else
			{
				insert(r->right, x);
				performRotation(r);
			}

			//update height of r
			r-> height = max(getHeight(r->left), getHeight(r->right)) + 1;
		}
	}

	//in-order traversal of the tree
	void display(node * r)
	{
		if( r==NULL )
		{
			//ha ha! nothing to display! do nothing!!!!
		}
		else
		{
			display(r->left);
			cout << r->data << endl;
			display(r->right);
		}
	}

	int numLeaves( node * r )
	{
		if( r==NULL )
		{
			return 0;
		}
		else if( r->right == NULL && r->left == NULL ) //it's a leaf!
		{
			return 1;
		}
		else
		{
			return numLeaves(r->left) + numLeaves(r->right);
		}
	}

	//return height of tree rooted at r
	//int getHeight(node * r)
	//{
	
	//}

public:
	avlTree()
	{
		root = NULL;
	}

	void insert(int x)
	{
		insert(root, x);
	}

	int numLeaves()
	{
		return numLeaves(root);
	}

	void display()
	{
		display(root);
	}
	int height()
	{
		return getHeight(root);
	}

};