#pragma once
#include <iostream>
using namespace std;

template<class T>
class Tree {
private:
	template<class T>
	struct Elem {
		T* obj;
		Elem<T> *left, *right;
		Elem(T* _obj = nullptr) : obj(_obj), left(nullptr), right(nullptr) {}
	};
	int count = 0;
	Elem<T>* root;
	void memfree(Elem<T>*&);
public:
	Tree() { root = nullptr; }
	Tree(T* _obj) : root(new Elem<T>(_obj)) {}
	~Tree() { memfree(root); root = nullptr; }
	void Insert(Elem<T>*&, T* _obj);
	void Push(T* _obj);
	//void Sort(Elem<T>*&);
};


template <class T>
void Tree<T>::memfree(Elem<T>*& t) {
	if (t->left)
		memfree(t->left);
	if (t->right)
		memfree(t->right);
	delete t;
}

template <class T>
void Tree<T>::Insert(Elem<T>*& t, T* _obj) {
	if (!t) {
		t = new Elem<T>(_obj);
	}
	else {
		if (*t->obj > *_obj) 
			Insert(t->left, _obj);
		else
			Insert(t->right, _obj);
	}
}

template <class T>
void Tree<T>::Push(T* _obj) {
	if (!root) {
		root = new Elem<T>(_obj);
	}
	else {
		if (*root->obj > *_obj)
			Insert(root->left, _obj);
		else
			Insert(root->right, _obj);
	}
}

//template <class T>
//void Tree<T>::Sort(Elem<T>*& t) {
//	if (t->left != nullptr)
//		Sort(t->left);
//	else if (t->right != nullptr)
//		Sort(t->right);
//	else
//}