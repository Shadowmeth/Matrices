#ifndef __MATRIX_H
#define __MATRIX_H

#include <stdexcept>
#include <iostream>

class Matrix {
	// think about the private data members...
	// the matrix should store real numbers
	float **array = nullptr;
	int i; // rows
	int j; // columns

	public:
		// include all the necessary checks before performing the operations in the functions
		Matrix(); // a default constructor
		Matrix(int, int); // a parametrized constructor
		Matrix(const Matrix &); // copy constructor
		void seti(int i);
		void setj(int j);
		int geti() const;
		int getj() const;
		void set(int i, int j, float val); // set value at (i, j)
		float get(int i, int j) const; // get value at (i, j)
		Matrix& assign(const Matrix &); // assigns (copies) a Matrix, Returns the same
		Matrix add(const Matrix &); // adds two Matrices and returns the result
		Matrix subtract(const Matrix &); // subtracts two Matrices and returns the result
		Matrix multiply(const Matrix &); // multiplies two Matrcies and returns the result
		Matrix multiplyElement(const Matrix &); // Elementwise multiplies two Matrices and returns
		// the result
		Matrix add(float); // adds a constant to every element
		Matrix multiply(float); // multiplies every element with a constant
		void input(); // takes input in every element of matrix
		void display(); // prints every element
		~Matrix();
};

#endif
