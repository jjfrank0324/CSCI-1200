/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <math.h>
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
template <class T>
 class BPlusTree
{
public:
		BPlusTree(){ root = NULL; size = 0; H =1;}
		BPlusTree(int asize);
		BPlusTree(const BPlusTree<T>& old) : H(old.H), size(old.size){
			root = this->copy_tree(old.root, NULL);}
		BPlusTree& operator=(const BPlusTree<T>& old) {
		    if (&old != this) {
			    this->destroy_tree(root);
			    root = this->copy_tree(old.root, old.root->parent);
					H = old.H;
		      size = old.size;
		    }

		    return *this;
	  	}
		~BPlusTree(){this->destroy_tree(root); root = NULL;}


			BPlusTreeNode<T>* find(const T& value){return find(value, root);}
			bool insert(const T& value){return insert(value, root);}
private:
	BPlusTreeNode<T>* root;
	int H;
	int size;


	BPlusTreeNode<T>* copy(BPlusTreeNode<T>* root_old, BPlusTreeNode<T>* parent);
	void destroy_tree(BPlusTreeNode<T>* p);
	BPlusTreeNode<T>* find(const T& value, BPlusTreeNode<T>* p);
	bool insert(const T& value, BPlusTreeNode<T>* p);
	void split_node(BPlusTreeNode<T>*& in_node, BPlusTreeNode<T>*& p);
};

template <class T>
	BPlusTree<T>::BPlusTree(int asize)
{
	size = asize-1;
	//since the given number is the max size, we will use size-1 for the actual size
	//for convience
	root = new BPlusTreeNode<T>;
	H = 1;
}

template <class T>
	BPlusTree<T>::BPlusTree(const BPlusTree<T>& old)
{
	size = asize-1;
	//since the given number is the max size, we will use size-1 for the actual size
	//for convience
	root = new BPlusTreeNode<T>;
	H = 1;
}

template <class T>
		BPlusTreeNode<T>* BPlusTree<T>::copy(BPlusTreeNode<T>* root_old, BPlusTreeNode<T>* parent)
{
	if(old->root == NULL)
	{
		return NULL;
	}

	BPlusTreeNode<T>* answer = new BPlusTreeNode<T>;
	asnwer->parent = root_old->parent;
	answer->keys = root_old;
	answer->children = root_old->children;
	for(unsigned int i =0; i< answer->children.size()
			&& !answer.is_leaf(); i++)
	{
		copy(answer->children[i], answer);
	}

	return amswer;
}


template <class T>	void
	BPlusTree<T>::destroy_tree(BPlusTreeNode<T>* p)
{
	if(!p)
		return;
	if(!p->is_leaf())
	{
		for(unsigned int i =0; i<p->children.size(); i++)
		{
			destroy_tree(p->children[i]);
		}
	}
	delete p;
	p = NULL;
}

//marking: p usually uis the root of the tree that we tranna find
template <class T>	BPlusTreeNode<T>*
BPlusTree<T>::find(const T& value, BPlusTreeNode<T>* p)
{
	if(!p)
	{return NULL;}

	while(!p->is_leaf())
	{	int higher = 0;

		for(unsigned int i =0; i< p->keys.size(); i++)
		{
			if(p->keys[i] > value)
			{
				higher = i+1;
			}
		}

		p = p->children[higher];
	}

	return p;

}

// P is the root of the BPlusTree;
template <class T>	bool
	BPlusTree<T>::insert(const T& value, BPlusTreeNode<T>* p)
{
	if(p == NULL)
	{
		root = new BPlusTreeNode<T>;
		root->keys.push_back(value);
		return true;
	}

	BPlusTreeNode<T>* in_node = find(value, p);

	bool judge = false;
	for(unsigned int i = 0; i<in_node->keys.size(); i++)
	{
		if(value<in_node->keys[i])
		{
		in_node->keys.insert(in_node->keys.begin()+i, value);
		judge = true;
		break;
		}
	}

	if(judge == false)
	{
		in_node->keys.push_back();
	}

	split_node(in_node, p);
	return true;
}
template <class T>	void
	BPlusTree<T>::split_node(BPlusTreeNode<T>*& in_node, BPlusTreeNode<T>*& p)
{
	std::cout<<"it enter hereWWWWWWWWWW"<<std::endl
	while(in_node->keys.size() > size )
	{ std::cout<<"it enter hereWWWWWWWWWW"<<std::endl
	// 	int total_key = in_node->keys.size();
	// 	int bound = floor(total_key/2);
	//
	// 	if(in_node->parent == NULL)
	// 	{
	// 		BPlusTreeNode<T>* NEW_root = new BPlusTreeNode<T>
	// 	}
	//
	// 	in_node = in_node->parent;
	// }


		if(in_node->is_leaf())
		{
			BPlusTreeNode<T>* left = new BPlusTreeNode<T>;
			BPlusTreeNode<T>* right = new BPlusTreeNode<T>;

			for(unsigned int i =0; i<bound; i++)
				left->keys.push_back(in_node->keys[i]);
			for(unsigned int j = bound; j<total_key; j++)
				right->keys.push_back(in_node->keys[j]);

			// to find the proper place to add the node
			for(unsigned int k = 0; k	<	in_node->parent.size(); k++)
			{
				bool judge = false;
				if(right->keys[0]  < in_node->parent->keys[k])
				{
					in_node->parent->keys.insert(in_node->parent->keys.begin()+k, right->keys[0]);
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
			itr = std::find(in_node->parent->children.begin(), in_node->parent->children.end(), in_node);
			itr = in_node->parent->children.erase(itr);
			itr =	in_node->parent->children.insert(itr, left);
			++itr;
			in_node->parent->children.insert(itr, right);




		}






		else	if( !in_node->is_leaf() && in_node->parent)
		{
			BPlusTreeNode<T>* PARENT = in_node->parent;

			BPlusTreeNode<T>* left = new BPlusTreeNode<T>;
			BPlusTreeNode<T>* right = new BPlusTreeNode<T>;
			left->parent = in_node->parent;
			right->parent = in_node->parent;

			for(unsigned int i =0; i<bound; i++)
				left->keys.push_back(in_node->keys[i]);
			for(unsigned int j = bound+1; j<total_key; j++)
				right->keys.push_back(in_node->keys[j]);

			// insert passing the plited key into the parents's key
			for(unsigned int k = 0; k	<	in_node->parent->keys.size(); k++)
			{
				bool judge = false;
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
					{left->children.push_back(in_node->children.size());
					in_node->children[i]->parent = left;}
				else
					{
						right->children.push_back(in_node->children.size());
						in_node->children[i]->parent = right;
					}
			}

			typename std::vector<BPlusTreeNode<T>* >::iterator itr;
			itr = std::find(in_node->parent->children.begin(), in_node->parent->children.end(), in_node);
			itr = in_node->parent->children.erase(itr);
			itr =	in_node->parent->children.insert(itr, left);
			++itr;
			in_node->parent->children.insert(itr, right);

			delete in_node;
			in_node = PARENT;
			continue;
		}




		in_node = in_node->parent;
	}




}














if(in_node->keys.size() >= size)
{
	std::cout<<"it should splitafFFFFF"<<std::endl;
	int pos = floor(in_node->keys.size()/2);
	if(!in_node->parent)
	{
		BPlusTreeNode<T>* roott = new BPlusTreeNode<T>;
		roott->keys.push_back(in_node->keys[pos]);
		BPlusTreeNode<T>* tmp1 = new BPlusTreeNode<T>;

		for(int n=0; n<pos; n++)
		{
			tmp1->keys.push_back(in_node->keys[n]);
			in_node->keys.erase(in_node->keys.begin());
		}
		if(is_root)
		{
			for(int n=0; n<= pos; n++)
			{
				in_node->children[0]->parent = tmp1;
				tmp1->children.push_back(in_node->children[0]);
				in_node->children.erase(in_node->children.begin());
			}
			in_node->keys.erase(in_node->keys.begin());
		}
		roott->children.push_back(tmp1);
		roott->children.push_back(in_node);
		tmp1->parent = roott;
		in_node->parent = roott;
		p = roott;
		return;
	}
	else
	{
		BPlusTreeNode<T>* tmp= in_node->parent;
		for( unsigned int i =0; i<tmp->keys.size(); i++)
		{
			if(in_node->keys[pos]<tmp->keys[i])
			{
				tmp->keys.insert(tmp->keys.begin()+i,in_node->keys[pos]);
				BPlusTreeNode<T>* temp1 = new BPlusTreeNode<T>;
				for(int n=0; n<pos; n++)
				{
					temp1->keys.push_back(in_node->keys[0]);//
					in_node->keys.erase(in_node->keys.begin());
				}
				if(is_root == 1)
				{
					for(int n=0; n<=pos; n++)
					{
						in_node->children[0]->parent = temp1;
						temp1->children.push_back(in_node->children[0]);
						in_node->children.erase(in_node->children.begin());
					}
					in_node->keys.erase(in_node->keys.begin());
				}
				temp1->parent = in_node->parent;
				tmp->children.insert(tmp->children.begin()+i, temp1);
				break;
			}
			else if(i==tmp->keys.size()-1)
			{
				tmp->keys.push_back(in_node->keys[pos]);
				BPlusTreeNode<T>* tmp1 = new BPlusTreeNode<T>;
				for(int n =0; n<pos; n++)
				{
					tmp1->keys.push_back(in_node->keys[n]);
					in_node->keys.erase(in_node->keys.begin());
				}
				if(is_root == 1)
				{
					for(int n=0; n<=pos; n++)
					{
						in_node->children[0]->parent = tmp1;
						tmp1->children.push_back(in_node->children[0]);
						in_node->children.erase(in_node->children.begin());
					}
					in_node->keys.erase(in_node->keys.begin());
				}
				tmp1->parent = in_node->parent;
				tmp->children.insert(tmp->children.begin()+1, tmp1);
				break;
			}
			}
			split_node(in_node, 1, p);
		}
	}
	else
		return;
}


#endif
