#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
{
	Matrix mat1(2, 3);
	
	mat1.input();
	mat1.display();
	
	Matrix mat2(3, 2);

	mat2.input();
	mat2.display();

	Matrix res = mat1.multiply(mat2);
	std::cout << "result properly returned\n";
	res.display();

}


