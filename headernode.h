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
		HeaderNode() { index = -1; next = nullptr; down = nullptr; }
		HeaderNode(T ind) { index = ind; next = nullptr; down = nullptr; }
		HeaderNode(HeaderNode<T> *nuevo) {
			this->index = nuevo->getIndex();
			this->next = nuevo->getNext();
			this->down = nuevo->getElement();
		}
		
		T getIndex() { if(index != -1) return index; else return -1; }
		void setIndex(T ind) { index = ind; } 

		HeaderNode<T>* getNext() { return next; }
		void setNext(HeaderNode<T> *nuevo) { next = nuevo; }

		ElementNode<T>* getElement() { return down; }
		void setElement(ElementNode<T> *nuevo) { down = nuevo; }

		HeaderNode<T>* operator=(HeaderNode<T> *newHeader) {
			this->setIndex(newHeader->getIndex());
			this->setNext(newHeader->getNext());
			this->setElement(newHeader->getElement());

			return this;
		}

    friend class Matrix<T>;

		~HeaderNode() {
			delete next;
			delete down;
		}

	protected:
		T index;
		HeaderNode<T> *next;
		ElementNode<T> *down;

};

#endif
