#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include "headernode.h"

template <typename T>
class Matrix;

template <typename T>
class ElementNode {
  public:
		typedef typename T::header header;
	 	ElementNode<T>(){ value = 0; column = row = down = right = nullptr; }
		ElementNode<T>(header *r, header *c, T data) { row = r; column = c; value = data; }

		T getValue() { return value; }
		void setValue(T val) { value = val; }
		header* getColumn() { return column; }
		void setColumn(header *col) { column = col; }

		header* getRow() { return row; }
		void setRow(header *r) { row = r; }

		ElementNode<T>* getDown() { return down; }
		void setDown(ElementNode<T> *dwn) { down = dwn; }

		ElementNode<T>* getRight() { return right; }
		void setRight(ElementNode<T> *rgt) { right = rgt; }

    friend class Matrix<T>;

	protected:
		T value;
		header *column, *row;
		ElementNode<T> *down, *right;
};

#endif
