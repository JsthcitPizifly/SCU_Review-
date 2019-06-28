#pragma once
#include <iostream>
template <typename T> class HuffNode {
public:
	virtual ~HuffNode() { }
	virtual int weight() = 0;
	virtual bool isLeaf() = 0;
	virtual T val() = 0;
	virtual HuffNode<T> *left() const = 0;
	virtual HuffNode<T> *right() const = 0;
	virtual void setLeft(HuffNode*) = 0;
	virtual void setRight(HuffNode*) = 0;
};

template <typename T> class LeafNode : public HuffNode<T> {
private:
	T it;					//Öµ
	int wgt;				//È¨ÖØ
public :
	LeafNode(const T &val, int freq)
	{
		it = val;
		wgt = freq;
	}
	int weight()
	{
		return wgt;
	}
	T val() 
	{ 
		return it; 
	}
	bool isLeaf()
	{
		return true;
	}
	virtual HuffNode<T> *left() const { return NULL; }
	virtual HuffNode<T> *right() const { return NULL; }
	virtual void setLeft(HuffNode<T>*) {}
	virtual void setRight(HuffNode<T>*) {}

};

template <typename T> class IntlNode : public HuffNode<T> {
private:
	HuffNode<T> *lc;			//left child
	HuffNode<T> *rc;			//right child;
	int wgt;					//weight;
public:
	IntlNode(HuffNode<T> *l, HuffNode<T> *r)
	{
		wgt = l->weight() + r->weight();
		lc = l;
		rc = r;
	}

	int weight()
	{
		return wgt;
	}

	bool isLeaf()
	{
		return false;
	}

	HuffNode<T> *left() const
	{
		return lc;
	}

	HuffNode<T> *right() const
	{
		return rc;
	}

	void setLeft(HuffNode<T> *b)
	{
		lc = b;
	}
	
	void setRight(HuffNode<T> *b)
	{
		rc = b;
	}

	virtual T val() { return -1; }
};

template <typename T> class HuffTree {
private:
	HuffNode<T> *Root;
public:
	HuffTree() = default;
	HuffTree(T &val, int freq)
	{
		Root = new LeafNode<T>(val, freq);
	}
	HuffTree(HuffTree<T> *l, HuffTree<T> *r)
	{
		Root = new IntlNode<T>(l->root(), r->root());
	}

	~HuffTree() {}
	
	HuffNode<T> *root() 
	{ 
		return Root; 
	}

	int weight()
	{
		return Root->weight();
	}
	void print()
	{

	}
};