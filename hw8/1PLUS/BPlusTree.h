/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <list>
#include <iostream>
#include <cmath>
#include <algorithm>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree;

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; }

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>;
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

///////Students commendts//////////
/*
The protptype of this B+ tree is heavily reference to the ds_set
several basic functions are very similar to
the sample code
*/

template <class T>
 class BPlusTree
{
public:
		//this is simlar to the sample code-> ds_set
		//constctor, copy functions
		BPlusTree(){ root = NULL; size = 0; H =1;}
		BPlusTree(int asize);
		BPlusTree(const BPlusTree<T>& old) : H(old.H), size(old.size){
			root = this->copy(old.root, NULL);}
		BPlusTree& operator=(const BPlusTree<T>& old) {
		    if (&old != this) {
			    this->destroy_tree(root);
			    root = this->copy(old.root, old.root->parent);
					H = old.H;
		      size = old.size;
		    }

		    return *this;
	  	}
		//destructor of the B+tree
		~BPlusTree(){this->destroy_tree(root); root = NULL;}

		//the finding function, return the treenode
			BPlusTreeNode<T>* find(const T& value){return find(value, root);}

		//the insert function, insert the key into the tree
			bool insert(const T& value){return insert(value, root);}

		//pritting functions, similar to ds_set
			void print_sideways(std::ostream& ostr){print_sideways(ostr, root, 0);}
			void print_BFS(std::ostream& ostr){print_BFS(ostr, root);}
			void print_BFS_pretty(std::ofstream& ostr){print_BFS_pretty(ostr, root);};
private:
	BPlusTreeNode<T>* root;
	int H;
	int size;

//several functions are upptted in the Private
//similar coding style with ds_set
	BPlusTreeNode<T>* copy(BPlusTreeNode<T>* root_old, BPlusTreeNode<T>* parent);

	//the destorutor function
	void destroy_tree(BPlusTreeNode<T>* p);

	//the treenode finding function
	BPlusTreeNode<T>* find(const T& value, BPlusTreeNode<T>* p);

	//inserting function, put a value into the tree
	bool insert(const T& value, BPlusTreeNode<T>*& p);

	//the helper function which help us splitting
	//the those nodes
	void split_node(BPlusTreeNode<T>*& in_node, int is_root, BPlusTreeNode<T>*& p);
	//prtting functions
	void print_sideways(std::ostream& ostr, const BPlusTreeNode<T>* p, int depth);
	void print_BFS(std::ostream& ostr, BPlusTreeNode<T>* p);
	void print_BFS_pretty(std::ostream& ostr, BPlusTreeNode<T>* p);
};

//default consructor
template <class T>
	BPlusTree<T>::BPlusTree(int asize)
{
	size = asize-1;
	//since the given number is the max size, we will use size-1 for the actual size
	//for convience
	root = new BPlusTreeNode<T>;

	H = 1;
}

//copy function
template <class T>
		BPlusTreeNode<T>* BPlusTree<T>::copy(BPlusTreeNode<T>* root_old, BPlusTreeNode<T>* parent)
{
	if(root_old == NULL)
	{
		return NULL;
	}
//copying every elements of the old tree into the new trees
	BPlusTreeNode<T>* answer = new BPlusTreeNode<T>;
	answer->parent = root_old->parent;
	answer->keys = root_old->keys;
	answer->children = root_old->children;

//we can seen every children as an subtree
//every things in the sub tree also need to be copied
//recurtion
	for(unsigned int i =0; i< answer->children.size()
			&& !answer->is_leaf(); i++)
	{
		copy(answer->children[i], answer);
	}

	return answer;
}

//the destorutor of the b+ tree
template <class T>	void
	BPlusTree<T>::destroy_tree(BPlusTreeNode<T>* p)
{
	if(!p)
		return;
	if(!p->is_leaf())
	{	// recursing every subtree to make sure the tree is clear
		for(unsigned int i =0; i<p->children.size(); i++)
		{
			destroy_tree(p->children[i]);
		}
	}
	delete p;
	p = NULL;
}

//NOTICING: p usually is the root of the tree that we tranna find
template <class T>	BPlusTreeNode<T>*
BPlusTree<T>::find(const T& value, BPlusTreeNode<T>* p)
{	// if null, return null
	if(p->keys.size()==0)
	{	return NULL;}

	//keep going down until it hit an leaf
	while(!p->is_leaf())
	{
		//higher  marking for the next level we need to go to
		int higher = p->keys.size();

		for(unsigned int i =0; i< p->keys.size(); i++)
		{

			 if(p->keys[i] > value)
			{
				higher = i;
				break;

			}
		}

		p = p->children[higher];
	}


	return p;

}

// P is the root of the BPlusTree;
//inserting functionfor the tree
//1.find the plzce to insert
//2. insert it into the treee
//3. split the nodes to make the tree
//		evenly distribute
template <class T>	bool
	BPlusTree<T>::insert(const T& value, BPlusTreeNode<T>*& p)
	{	//if is a NULL tree, directly put it in the tree
		if(p->keys.size()==0)
		{

			root->keys.push_back(value);
			return true;
		}
		//find the place that we need to insert the node
		BPlusTreeNode<T>* in_node = find(value);

			//directly insert the value into the tree
			//judge is the flag that prevent last node is the place
			//we need to insert it
			bool judge = false;

			for(unsigned int i = 0; i<in_node->keys.size(); i++)
			{				T a = in_node->keys[i];
				if(value<a)
				{
				in_node->keys.insert(in_node->keys.begin()+i, value);
				judge = true;
				break;
				}
			}

			if(judge == false)
			{
				in_node->keys.push_back(value);
			}

			//split the over_lenth ndoes if neccassry
			if(in_node->keys.size()>size)
				split_node(in_node, 0,p);

			return true;


	}

//this is the node spliitibng function
//we we discuss the possible inserting places in
// four situation to prevent corner cases
// 1. it's an leaf and a root
// 2. it's a not either a leaf or a  root
// 3. it's a leaf, but not a root
// 4. it's a root but not a leaf
	template <class T>	void
		BPlusTree<T>::split_node(BPlusTreeNode<T>*& in_node, int is_root, BPlusTreeNode<T>*& p)
		{
		// until the size is qualify, we will keep addingg it
		while(in_node !=  NULL && in_node->keys.size()  > size )
	{

			int total_key = in_node->keys.size();
			int bound = total_key/2;

			//Case 1
			if(in_node->is_leaf() && in_node->parent != NULL)
			{
				//create two new nodes for seperations
				// set up connection accordingly
				BPlusTreeNode<T>* left = new BPlusTreeNode<T>;
				BPlusTreeNode<T>* right = new BPlusTreeNode<T>;
				left->parent = in_node->parent;
				right->parent = in_node->parent;

				//pushing keys into left and right node
				for(unsigned int i =0; i<bound; i++)
					left->keys.push_back(in_node->keys[i]);
				for(unsigned int j = bound; j<total_key; j++)
					right->keys.push_back(in_node->keys[j]);

				//find the right place to insert marking value(path value)
				//judge is the flag to prevent corner cases
				bool judge = false;
				for(unsigned int k = 0; k	<	in_node->parent->keys.size(); k++)
				{
					if(right->keys[0]  < in_node->parent->keys[k])
					{
						in_node->parent->keys.insert(in_node->parent->keys.begin()+k,
																					right->keys[0]);
						judge = true;
						break;
					}
				}
				if(judge == false)
				{
					in_node->parent->keys.push_back(right->keys[0]);
				}
				//insert the two node we just created into the cildreans
				typename std::vector<BPlusTreeNode<T>* >::iterator itr;
				itr = std::find(in_node->parent->children.begin(),
												in_node->parent->children.end(), in_node);
				itr = in_node->parent->children.erase(itr);
				itr =	in_node->parent->children.insert(itr, left);
				++itr;
				in_node->parent->children.insert(itr, right);

				//delete current node to prevent memory leak
				//go to nest node
				delete in_node;
				in_node = right->parent;

			}

			//case 2
			else	if( !in_node->is_leaf() && in_node->parent)
			{
				//create two new nodes and new root node for seperations
				// set up connection accordingly
				BPlusTreeNode<T>* PARENT = in_node->parent;
				BPlusTreeNode<T>* left = new BPlusTreeNode<T>;
				BPlusTreeNode<T>* right = new BPlusTreeNode<T>;
				left->parent = in_node->parent;
				right->parent = in_node->parent;
				//pushing keys into left and right node
				for(unsigned int i =0; i<bound; i++)
					left->keys.push_back(in_node->keys[i]);
				for(unsigned int j = bound+1; j<total_key; j++)
					right->keys.push_back(in_node->keys[j]);

				// insert passing the plited key into the parents's key
				bool judge = false;
				for(unsigned int k = 0; k	<	in_node->parent->keys.size(); k++)
				{
					if(right->keys[0]  < in_node->parent->keys[k])
					{
						in_node->parent->keys.insert(in_node->parent->keys.begin()+k, in_node->keys[bound]);
						judge = true;
						break;
					}
				}

				if(judge == false)
				{
					in_node->parent->keys.push_back(in_node->keys[bound]);
				}

				//make sure the chuildren nodes and the parents node
				//are linked
				for(unsigned int i =0; i< in_node->children.size(); i++)
				{
					if(i< in_node->children.size()/2)
						{left->children.push_back(in_node->children[i]);
						in_node->children[i]->parent = left;}
					else
						{
							right->children.push_back(in_node->children[i]);
							in_node->children[i]->parent = right;
						}
				}
								//insert the two node we just created into the cildreans
				typename std::vector<BPlusTreeNode<T>* >::iterator itr;
				itr = std::find(in_node->parent->children.begin(), in_node->parent->children.end(), in_node);
				itr = in_node->parent->children.erase(itr);
				itr =	in_node->parent->children.insert(itr, left);
				++itr;
				in_node->parent->children.insert(itr, right);

				//delete current node to prevent memory leak
				//go to nest node
				delete in_node;
				in_node = PARENT;
				continue;
			}
			//Case 3
			else if(in_node->is_leaf() && !in_node->parent)
			{
				//create two new nodes and new root node for seperations
				// set up connection accordingly
				BPlusTreeNode<T>* PARENT = new BPlusTreeNode<T>;
				in_node->parent = PARENT;
				PARENT->children.push_back(in_node);
				BPlusTreeNode<T>* left = new BPlusTreeNode<T>;
				BPlusTreeNode<T>* right = new BPlusTreeNode<T>;
				left->parent = in_node->parent;
				right->parent = in_node->parent;

			//pushing keys into left and right node
				for(unsigned int i =0; i<bound; i++)
					left->keys.push_back(in_node->keys[i]);
				for(unsigned int j = bound; j<total_key; j++)
					right->keys.push_back(in_node->keys[j]);

				PARENT->keys.insert(PARENT->keys.begin(), right->keys[0]);
				//make sure the children nodes and the parents node
				//are linked
				for(unsigned int i =0; i< in_node->children.size(); i++)
				{
					if(i< in_node->children.size()/2)
						{left->children.push_back(in_node->children[i]);
						in_node->children[i]->parent = left;}
					else
						{
							right->children.push_back(in_node->children[i]);
							in_node->children[i]->parent = right;
						}
				}
				//insert the two node we just created into the cildreans
				typename std::vector<BPlusTreeNode<T>* >::iterator itr;
				itr = std::find(in_node->parent->children.begin(), in_node->parent->children.end(), in_node);
				itr = in_node->parent->children.erase(itr);
				itr =	in_node->parent->children.insert(itr, left);
				++itr;
				in_node->parent->children.insert(itr, right);
				//delete current node to prevent memory leak
				//go to nest node
				//changing the root of the origin object
				delete in_node;

				in_node = PARENT;
				root = PARENT;
				continue;

			}
			//Case 4
			else if(!in_node->is_leaf() && !in_node->parent)
			{
				//create two new nodes and new root node for seperations
				// set up connection accordingly
				BPlusTreeNode<T>* PARENT = new BPlusTreeNode<T>;
				in_node->parent = PARENT;
				PARENT->children.push_back(in_node);
				BPlusTreeNode<T>* left = new BPlusTreeNode<T>;
				BPlusTreeNode<T>* right = new BPlusTreeNode<T>;
				left->parent = in_node->parent;
				right->parent = in_node->parent;

				//pushing keys into left and right node
				for(unsigned int i =0; i<bound; i++)
					left->keys.push_back(in_node->keys[i]);
				for(unsigned int j = bound+1; j<total_key; j++)
					right->keys.push_back(in_node->keys[j]);

				PARENT->keys.insert(PARENT->keys.begin(), in_node->keys[bound]);


				//make sure the children nodes and the parents node
				//are linked
				for(unsigned int i =0; i< in_node->children.size(); i++)
				{
					if(i< in_node->children.size()/2)
						{left->children.push_back(in_node->children[i]);
						in_node->children[i]->parent = left;}
					else
						{
							right->children.push_back(in_node->children[i]);
							in_node->children[i]->parent = right;
						}
				}
				//insert the two node we just created into the cildreans
				typename std::vector<BPlusTreeNode<T>* >::iterator itr;
				itr = std::find(in_node->parent->children.begin(), in_node->parent->children.end(), in_node);
				itr = in_node->parent->children.erase(itr);
				itr =	in_node->parent->children.insert(itr, left);
				++itr;
				in_node->parent->children.insert(itr, right);

				//delete current node to prevent memory leak
				//go to nest node
				//changing the root of the origin object
				delete in_node;

				in_node = PARENT;
				root = PARENT;
				continue;

			}
		}


}

//similar to the ds_set pritting function
template <class T>	void
		BPlusTree<T>::print_sideways(std::ostream& ostr, const BPlusTreeNode<T>* p, int depth)
{
	if(p->keys.size()== 0)
	{
		ostr<< "Tree is empty."<<"\n";
		return;
	}
	if(p)
	{	//the spliting marks for the tree
		unsigned int split =(p->children.size()/ 2 );
		for(unsigned int i = 0; i< split; i++)
			print_sideways(ostr, p->children[i], depth+1);
		for(unsigned int i =0; i<depth; i++)
			ostr<<"\t";

		for(unsigned int i =0; i< p->keys.size(); i++)
		{
			if( i == p->keys.size()-1)
				ostr<< p->keys[i];
			else
				ostr<< p->keys[i] << ",";
		}

		ostr<<"\n";
		for(unsigned int i = split; i< p->children.size(); i++)
		print_sideways(ostr, p->children[i], depth+1);


		return;
	}
	return;
}


//prrtting the tree in BFS order
template <class T>	void
		BPlusTree<T>::print_BFS(std::ostream& ostr, BPlusTreeNode<T>* p)
{
	if(p->keys.size()== 0)
	{
		ostr<< "Tree is empty."<<"\n";
		return;
	}

	//create two vector to store all the vector into the function
	std::vector<BPlusTreeNode<T>*> lv1;
	std::vector<BPlusTreeNode<T>*> lv2;
	lv1.push_back(p);

	//we will print it level by level
	// till the last level have not nodes
	while(lv1.size()!= 0)
	{
		for(unsigned int i =0; i< lv1.size(); i++)
		{
			for(unsigned int j=0; j<lv1[i]->keys.size(); j++)
			{
				if(j == lv1[i]->keys.size()-1 )
					ostr << lv1[i]->keys[j];
				else
					ostr << lv1[i]->keys[j]<<",";
			}
			if(!lv1[i]->is_leaf())
			{
				for(unsigned int k = 0; k< lv1[i]->children.size(); k++)
					lv2.push_back(lv1[i]->children[k]);
			}
			if(i != lv1.size()-1)
				ostr<<"\t";
		}
		ostr<<"\n";
		lv1 = lv2;
		lv2.clear();
	}

}



template <class T>	void
		BPlusTree<T>::print_BFS_pretty(std::ostream& ostr, BPlusTreeNode<T>* p)
{
	if(p->keys.size()== 0)
	{
		ostr<< "Tree is empty."<<"\n";
		return;
	}

	//create two vector to store all the vector into the function
	std::vector<BPlusTreeNode<T>*> lv1;
	std::vector<BPlusTreeNode<T>*> lv2;
	lv1.push_back(p);

	//we will print it level by level
	// till the last level have not nodes
	while(lv1.size()!= 0)
	{
		for(unsigned int i =0; i< lv1.size(); i++)
		{
			for(unsigned int j=0; j<lv1[i]->keys.size(); j++)
			{
				if(j == lv1[i]->keys.size()-1 )
					ostr << lv1[i]->keys[j];
				else
					ostr << lv1[i]->keys[j]<<"|";
			}
			if(!lv1[i]->is_leaf())
			{
				for(unsigned int k = 0; k< lv1[i]->children.size(); k++)
					lv2.push_back(lv1[i]->children[k]);
			}
			if(i != lv1.size()-1)
				ostr<<"~";
		}
		ostr<<"\n"<<"____________________________________"<<"\n";
		lv1 = lv2;
		lv2.clear();
	}

}
#endif
