/*
*	AVL tree, generic, can be modified for implementing std::map
*	Date Created - 22/02/2015
*	Date Modified- 12/06/2015
*	Author - Harmandeep Singh (harmandeep3091@gmail.com, harman786@yahoo.co.in)
*	Please report bugs at the above mentioned emailid, Thanks
*/

#include<cstdio>
#include<iostream>
using namespace std;
template<class T>
class AVL
{
	class node
	{
		public:
			T data;
			node* left, *right;
			int height;
	};
	node* root;
	node* newnode(T data)
	{
		node* temp = new node;
		temp->data = data;
		temp->left = temp->right = NULL;
		temp->height = 1;
		return temp;
	}
	node* l_rotate(node* X)
	{
		cout<<"l_rotate "<<X->data<<endl;
		node* W = X->left;
		X->left = W->right;
		W->right = X;
		X->height = max(height(X->left), height(X->right))+1;
		W->height = max(height(W->left), height(W->right))+1;
		return W;
	}
	node* lr_rotate(node* X)
	{
		cout<<"lr_rotate "<<X->data<<endl;
		node* W = X->left;
		node* Z = W->right;
		W->right = Z->left;
		X->left = Z->right;
		Z->left = W;
		Z->right = X;
		X->height = max(height(X->left), height(X->right))+1;
		W->height = max(height(W->left), height(W->right))+1;
		Z->height = max(height(X), height(Z))+1;
		return Z;
	}
	node* r_rotate(node* X)
	{
		cout<<"r_rotate "<<X->data<<endl;
		node* Z = X->right;
		X->right = Z->left;
		Z->left = X;
		X->height = max(height(X->left), height(X->right))+1;
		Z->height = max(height(Z->right), height(X))+1;
		return Z;
	}
	node* rl_rotate(node* X)
	{
		cout<<"rl_rotate "<<X->data<<endl;
		node* Y = X->right;
		node* Z = Y->left;
		Y->left = Z->right;
		X->left = Z->left;
		Z->left = X;
		Z->right = Y;
		X->height = max(height(X->left), height(X->right))+1;
		Y->height = max(height(Y->left), height(Y->right))+1;
		Z->height = max(height(Y), height(Z))+1;
		return Z;
	}
	void _insert(node** ptr, T data)
	{
		if(*ptr)
		{
			T val = (*ptr)->data;
			if(data<val)
			{
				_insert(&((*ptr)->left), data);
				if(height((*ptr)->left)-height((*ptr)->right)>=2)
				{
					if(data < (*ptr)->left->data)	//LL rotation
						*ptr = l_rotate(*ptr);
					else							//LR rotation
						*ptr = lr_rotate(*ptr);
				}
			}
			else
			{
				_insert(&((*ptr)->right), data);
				if(height((*ptr)->right)-height((*ptr)->left)>=2)
				{
					if(data >= (*ptr)->right->data)	//RR rotation
						*ptr = r_rotate(*ptr);
					else							//RL rotation
						*ptr = rl_rotate(*ptr);
				}
			}
			(*ptr)->height = 1 + max(height((*ptr)->left), height((*ptr)->right));
		}
		else
		{
			*ptr = newnode(data);
		}
	}
	void _inorder(node* root)
	{
		if(!root)
			return;
		_inorder(root->left);
		cout<<root->data<<"|"<<root->height<<" ";
		_inorder(root->right);
	}
	void _preorder(node* root)
	{
		if(!root)
			return;
		cout<<root->data<<"|"<<root->height<<" ";
		_preorder(root->left);
		_preorder(root->right);
	}
	node* _search(node* temp, T data)
	{
		if(!temp)
			return NULL;
		if(temp->data == data)
			return temp;
		else if(data < temp->data)
			return _search(temp->left, data);
		else
			return _search(temp->right, data);
	}
	void _delete(node** ptr, node* del_node)
	{
		if((*ptr)==del_node)
		{
			if(del_node->left && del_node->right)
			{
				node* temp = del_node->right;
				while(temp->left)
					temp=temp->left;
				_delete(&((*ptr)->right), temp);
				temp->left = (*ptr)->left;
				temp->right = (*ptr)->right;
				*ptr = temp;
				if(height((*ptr)->left) - height((*ptr)->right) >=2 )			//In this case we are doing the rotation at this level becuase after getting the 
				{																// rightmost largest element, and deleting the del_node, the tree with ptr as root, may not be balanced	
					if(height((*ptr)->left->left) - height((*ptr)->left->right) <0)// Eg tree - 50, 25, 62, 12, 37, in this if we delete 50, we will replace it with 67 and the do rotation
						*ptr = lr_rotate(*ptr);									// at 67 node.
					else
						*ptr = l_rotate(*ptr);
				}
				else if(height((*ptr)->left) - height((*ptr)->right) <-1)
				{
					if(height((*ptr)->right->right) - height((*ptr)->right->left) <0)
						*ptr = rl_rotate(*ptr);
					else
						*ptr = r_rotate(*ptr);
				}
				(*ptr)->height = max(height((*ptr)->left), height((*ptr)->right))+1;	
			}
			else if(del_node->left || del_node->right)
			{
				if(del_node->left)
					*ptr = del_node->left;
				else
					*ptr = del_node->right;
				(*ptr)->height = max(height((*ptr)->left), height((*ptr)->right))+1;
			}
			else
				*ptr = NULL;
		}
		else
		{
			if(del_node->data < (*ptr)->data)
				_delete(&((*ptr)->left), del_node);
			else
				_delete(&((*ptr)->right), del_node);
			if(height((*ptr)->left) - height((*ptr)->right) >=2 )	//if left subtree has more elements
			{
				//cout<<height((*ptr)->left) - height((*ptr)->right)<<endl;
				if(height((*ptr)->left->left) - height((*ptr)->left->right) <0)
					*ptr = lr_rotate(*ptr);
				else
					*ptr = l_rotate(*ptr);
			}
			else if(height((*ptr)->left) - height((*ptr)->right) <-1)
			{
				if(height((*ptr)->right->right) - height((*ptr)->right->left) <0)
					*ptr = rl_rotate(*ptr);
				else
					*ptr = r_rotate(*ptr);
			}
			(*ptr)->height = max(height((*ptr)->left), height((*ptr)->right))+1;	
		}
	}
	public:
		int max(int a, int b)
		{
			if(a<b)
				return b;
			return a;
		}
		int height(node* temp)
		{
			if(!temp)
				return 0;
			return temp->height;
		}
		AVL()
		{
			root = NULL;
		}
		void insert(T data)
		{
			_insert(&root, data);
		}
		void inorder()
		{
			_inorder(root);
			cout<<endl;
		}
		void preorder()
		{
			_preorder(root);
			cout<<endl;
		}
		bool search(T data)
		{
			if(_search(root, data)!=NULL)
				return true;
			return false;
		}
		void deleteNode(T data)
		{
			//cout<<data<<"---->"<<endl;
			node* temp = _search(root, data); 
			if(temp!=NULL)
			{
				_delete(&root, temp);
				delete temp;
			}
		}
};
main()
{
	AVL<int> a;
	a.insert(100);
	a.insert(50);
	a.insert(200);
	a.insert(25);
	a.insert(75);
	a.insert(150);
	a.insert(250);
	a.insert(12);
	a.insert(37);
	a.insert(62);
	a.insert(87);
	a.insert(125);
	a.insert(175);
	a.insert(93);
	a.insert(112);
	a.inorder();
	a.deleteNode(112);
	a.inorder();
	a.deleteNode(200);
	a.inorder();
	a.deleteNode(150);
	a.inorder();
	a.deleteNode(50);
	a.inorder();
	a.deleteNode(100);
	a.inorder();
}
