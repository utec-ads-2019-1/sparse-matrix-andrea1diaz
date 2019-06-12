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
	
		unsigned getRowNum() { return rows; }
		void setRowNum(unsigned num) { rows = num; }

		unsigned getColNum() { return columns; }
		void setColNum(unsigned num) { columns = num; }


		HeaderNode<T>* getRow(T index) {
			HeaderNode<T> *tmp = root->getRow();

			while (tmp != nullptr) {
				if (tmp->getIndex() == index) return tmp;
				tmp = tmp->getNext();
			}

			return nullptr;
		}
	

		HeaderNode<T>* getCol(T index) {
			HeaderNode<T> *tmp = root->getColumn();

			while (tmp != nullptr) {
				if (tmp->getIndex() == index) return tmp;
				tmp = tmp->getNext();
			}

			return nullptr;
		}


		bool findElement(T r_index, T c_index, T e_value) {
			HeaderNode<T> *row = getRow(r_index);
			HeaderNode<T> *column = getCol(c_index);

			if (row != nullptr && column != nullptr) {
				ElementNode<T> *tmp = row->getElement();
				
				while (tmp != nullptr) {
					if (tmp->getValue() == e_value && column->getIndex() == c_index )
						return true;
					tmp = tmp->getNext();
				}
				
				return false;	
			}

			return false;
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



    Matrix(unsigned rows, unsigned columns) {
			HeaderNode<T>* row = new HeaderNode<T>(0);
			HeaderNode<T>* column = new HeaderNode<T>(0);

			root->setHeaders(column, row);
			
			addHeaders(row, rows);
			addHeaders(column, columns);
		}


    void set(unsigned row, unsigned column, T value) {
			ElementNode<T> *element = new ElementNode<T>(row, column, value);
			HeaderNode<T> *nrow = root->getRow();
			HeaderNode<T> *ncolumn = root->getColumn();
		}


		void addElement(unsigned row, unsigned column, T value) {
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
