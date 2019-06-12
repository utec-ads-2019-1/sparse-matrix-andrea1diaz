#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include "node.h"
#include "headernode.h"
#include "elementnode.h"

using namespace std;

template <typename T>
class Matrix {
private:
    Node<T> *root;
    unsigned rows, columns;

public:
    Matrix(unsigned rows, unsigned columns) {
			HeaderNode<T>* row = new HeaderNode<T>(0);
			HeaderNode<T>* column = new HeaderNode<T>(0);

			root->setHeaders(column, row);
			
			addHeaders(row, rows);
			addHeaders(column, columns);
		}


		void addHeaders(HeaderNode<T>* node, int n) {
			int i = 1;

			HeaderNode<T>* tmp = node;
			while ( i < n ) {
				HeaderNode<T>* nuevo = new HeaderNode<T>(tmp->getIndex() + 1);
				if (nuevo->getIndex() == (node->getIndex() + 1)) node->setNext(tmp);
				tmp->setNext(nuevo);
				tmp = nuevo;
				i++;
			}
		}


    void set(unsigned row, unsigned column, T value) {
			ElementNode<T> *element = new ElementNode<T>(row, column, value);
			HeaderNode<T> *nrow = root->getRow();
			HeaderNode<T> *ncolumn = root->getColumn();

			if (nrow->getElement() == nullptr) {
				nrow->setElement(element);
			}

			else {
				ElementNode<T> *relement = nrow->getElement();
				
				while ( relement->getRight() != nullptr ) {
					relement = relement->getRight();
				}

				relement->setRight(element); 
			}

			if (ncolumn == nullptr) {
				ncolumn->setElement(element);
			}


		}

    T operator()(unsigned, unsigned) const;
    Matrix<T> operator*(T scalar) const;
    Matrix<T> operator*(Matrix<T> other) const;
    Matrix<T> operator+(Matrix<T> other) const;
    Matrix<T> operator-(Matrix<T> other) const;
    Matrix<T> transpose() const;
    void print() const;

    ~Matrix(){}
};

#endif //SPARSE_MATRIX_MATRIX_H
