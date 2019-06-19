#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include "headernode.h"

template <typename T>
class Matrix;

template <typename T>
class HeaderNode;

template <typename T>
class ElementNode {
  public:
	 	ElementNode<T>(){ value = 0; column = row = nullptr; down = right = nullptr; }
		ElementNode<T>(HeaderNode<T> *r, HeaderNode<T> *c, T data) { row = r; column = c; value = data; }

		T getValue() { return value; }
		void setValue(T val) { value = val; }

		HeaderNode<T>* getColumn() { return column; }
		void setColumn(HeaderNode<T> *col) { column = col; }

		HeaderNode<T>* getRow() { return row; }
		void setRow(HeaderNode<T> *r) { row = r; }

		ElementNode<T>* getDown() { return down; }
		void setDown(ElementNode<T> *dwn) { down = dwn; }

		ElementNode<T>* getRight() { return right; }
		void setRight(ElementNode<T> *rgt) { right = rgt; }

    friend class Matrix<T>;
		
		~ElementNode() {
			delete down;
			delete right;
			delete column;
			delete row;
		}

	protected:
		T value;
		HeaderNode<T> *column, *row;
		ElementNode<T> *down, *right;
};

#endif
