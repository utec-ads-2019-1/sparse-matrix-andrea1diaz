#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include "elementnode.h"

template <typename T>
class Matrix;

template <typename T>
class ElementNode;

template <typename T>
class HeaderNode {
	public:
		HeaderNode() { index = 0; next = nullptr; down = nullptr; }
		HeaderNode(T ind) { index = ind; next = nullptr; down = nullptr; }

		T getIndex() { return index; }
		void setIndex(T ind) { index = ind; } 

		HeaderNode<T>* getNext() { return next; }
		void setNext(HeaderNode<T> *nuevo) { next = nuevo; }

		ElementNode<T>* getElement() { return down; }
		void setElement(ElementNode<T> *nuevo) { down = nuevo; }


    friend class Matrix<T>;

	protected:
		T index;
		HeaderNode<T> *next;
		ElementNode<T> *down;

};

#endif
