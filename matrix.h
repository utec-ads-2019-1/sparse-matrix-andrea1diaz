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

			this->setRowNum(rows);
			this->setColNum(columns);
		}



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



		ElementNode<T>* getElement(unsigned row, unsigned column) {
			HeaderNode<T> *r = getRow(row);
			HeaderNode<T> *c = getCol(column);

			if (r != nullptr && c != nullptr) {
				ElementNode<T> *tmp = r->getElement();
				
				while (tmp != nullptr) {
					if (tmp->getColumn()->getIndex() == column) return tmp;

					tmp = tmp->getRight();
				}
				
				return nullptr;	
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
					tmp = tmp->getRight();
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



		bool addElement(unsigned row, unsigned column, T value) {
			if (findElement(row, column, value)) return false;

			else {
				ElementNode<T> *element = new ElementNode<T>;

				HeaderNode<T> *r = root->getRow();
				HeaderNode<T> *c = root->getColumn();

				while (r->getIndex() < row) r = r->getNext();
				
				if (r->getElement() == nullptr) r->setElement(element);

				else {
					element->setRight(r->getElement()->getRight());
					r->getElement()->setRight(element);
				}

				while (c->getIndex() < column) c = c->getNext();
				
				if (c->getElement() == nullptr) c->setElement(element);

				else {
					element->setDown(c->getElement()->getDown());
					c->getElement()->setDown(element);
				}

				element->setValue(value);

				return true;
			}	
		}



		bool deleteElement(unsigned row, unsigned column, T value) {
			HeaderNode<T> *r = getRow(row);
			HeaderNode<T> *c = getCol(column);

			if (findElement(row, column, value)) {
				ElementNode<T> *element = getElement(row, column);

				while (r->getIndex() < row) r = r->getNext();
				
				r->getElement()->setRight(element->getRight());

				while (c->getIndex() < column) c = c->getNext();

				c->getElement()->setDown(element->getDown());

				return true;
			}

			else return false;
		}



    void set(unsigned row, unsigned column, T value) {
			if (value == 0) deleteElement(row, column, value);

			else addElement(row, column, value);
		}



    T operator()(unsigned row, unsigned column) {
			ElementNode<T> *element = getElement(row, column);
			
			return element->getValue();
		}
    


		Matrix<T> operator*(T scalar) {
			Matrix<T> *matrix = new Matrix<T>(getRowNum(), getColNum());

			HeaderNode<T> *r = root->getRow();
			ElementNode<T> *element = r->getElement();
		
			while (r != nullptr) {
				while (element != nullptr) {
					T value = element->getValue();
					matrix->addElement(r->getIndex(), element->getColumn()->getIndex(), value * scalar);		
					element = element->getRight();
				}

				r = r->getNext();
			}

			return *matrix;
		}	



    Matrix<T> operator*(Matrix<T> other) const;
    Matrix<T> operator+(Matrix<T> other) const;
    Matrix<T> operator-(Matrix<T> other) const;
    Matrix<T> transpose() const;
    void print() const;

    ~Matrix(){}
};

#endif //SPARSE_MATRIX_MATRIX_H
