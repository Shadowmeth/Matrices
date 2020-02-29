#include "Matrix.h"

Matrix::Matrix(int r, int c) : i{r}, j{c}
{

    if (i < 0 || j < 0) {
        throw std::invalid_argument("Rows/Columns can't be negative."); // No need to allocate mem
    }

    array = new float*[i]; // allocate an array of i rows

    for (int count = 0; count < i; count++)
    {
        array[count] = new float[j]; // for every row allocate j columns
    }
}

void Matrix::setj(int j)
{
    this->j = j;
}

void Matrix::seti(int i)
{
    this->i = i;
}

int Matrix::geti() const
{
    return i;
}

int Matrix::getj() const
{
    return j;
}

void Matrix::set(int i, int j, float val)
{
    if (i < 0 || j < 0) {
        throw std::invalid_argument("Rows/Columns can't be negative");
    }

    array[i][j] = val;
}

float Matrix::get(int i, int j) const
{

    if (i < 0 || j < 0) {
        throw std::invalid_argument("Rows/Columns can't be negative.");
    }

    return array[i][j];
}
Matrix::Matrix(const Matrix &copyMatrix): i{copyMatrix.geti()}, j{copyMatrix.getj()}
{
    if (i < 0 || j < 0) {
        throw std::invalid_argument("Rows/Columns can't be negative."); // No need to allocate mem
    }

    array = new float*[i]; // allocate an array of i rows

    for (int count = 0; count < i; count++)
    {
        array[count] = new float[j]; // for every row allocate j columns
    }

    // copy values
    for (int rows = 0; rows < i; rows++)
        for (int cols = 0; cols < j; cols++)
            array[rows][cols] = copyMatrix.get(rows, cols);
}

Matrix& Matrix::assign(const Matrix &mat)
{

    // note that we are re allocating memory here even if the order of *this and mat is same
    // if performance is a concern reallocate memory only if the order doesn't match in the first place

    if (array != nullptr) {
        for (int count = 0; count < i; count++) {
            delete [] array[count]; // release columns
        }
        delete[] array; // release rows
    }

    seti(mat.geti());
    setj(mat.getj());

    array = new float*[i]; // allocate an array of i rows

    for (int count = 0; count < i; count++)
    {
        array[count] = new float[j]; // for every row allocate j columns
    }

    // copy values
    for (int rows = 0; rows < i; rows++)
        for (int cols = 0; cols < j; cols++)
            array[rows][cols] = mat.get(rows, cols);

    return *this; 
}

 Matrix Matrix::add(const Matrix &addMat)
 {
     // first ensure the order is same
     if (i != addMat.geti() || j != addMat.getj())
        throw std::logic_error("Order of both matrices to be added should be same.");

    Matrix result(i, j);
    float sum;
    for (int rows = 0; rows < i; rows++)
        for (int cols = 0; cols < j; cols++) {
            sum = get(rows, cols) + addMat.get(rows, cols);
            result.set(rows, cols, sum);
        }

    return result;
 }

 Matrix Matrix::subtract(const Matrix &subMat)
 {
     // first ensure the order is same
    if (i != subMat.geti() || j != subMat.getj()) {
        throw std::logic_error("Order of both matrices to be subtracted should be same.");
    }

    Matrix result(i, j);
    float diff;
    for (int rows = 0; rows < i; rows++)
        for (int cols = 0; cols < j; cols++) {
            diff = get(rows, cols) - subMat.get(rows, cols);
            result.set(rows, cols, diff);
        }

    return result;
 }
    
Matrix Matrix::multiply(const Matrix &multMat)
{
    if (getj() != multMat.geti()) // columns of 1st matrix should be equal to rows of 2nd matrix   
        throw std::logic_error("Columns of 1st matrix should be equal to rows of 2nd matrix");

    // the result matrix will have same number of rows as 1st matrix, and the same number of columns
    // as the 2nd matrix
    Matrix result(i, multMat.getj());
    float product;
    for (int rows = 0; rows < i; rows++) {
        for (int cols = 0; cols < result.getj(); cols++) {
            product = 0.0f;
            for (int k = 0; k < j; k++)
                product = product + get(rows, k) * multMat.get(k, cols);

            result.set(rows, cols, product);
        }
    }

    return result;
}
Matrix Matrix::multiplyElement(const Matrix &multMat)

{
    // first ensure the order is same
    if (i != multMat.geti() || j != multMat.getj()) {
        throw std::logic_error("Order of both matrices to be multiplied elementwise should be same.");
    }

    Matrix result(i, j);
    float product;
    for (int rows = 0; rows < j; rows++) {
        for (int cols = 0; cols < i; cols++) {
                product = get(rows, cols) * multMat.get(rows, cols);
            result.set(rows, cols, product);
            }
        }

    return result;
}

Matrix Matrix::add(float val)
{
    Matrix result(i, j);
    for (int rows = 0; rows < i; rows++)
        for (int cols = 0; cols < j; cols++) {
            result.set(rows, cols, get(rows, cols) + val);
        }

    return result;
}

Matrix Matrix::multiply(float val)
{
    Matrix result(i, j);
    for (int rows = 0; rows < i; rows++)
        for (int cols = 0; cols < j; cols++)
           result.set(rows, cols, get(rows, cols) * val);

    return result;
}

void Matrix::input()
{
    float input;
    for (int rows = 0; rows < i; rows++)
        for (int cols = 0; cols < j; cols++) {
            std::cout << "Enter matrix[" << rows + 1 << ']' << '[' << cols + 1 << "]: ";
            std::cin >> input;
            array[rows][cols] = input;
        }

}

void Matrix::display() 
{
    std::cout << '\n';
    for (int rows = 0; rows < i; rows++) {
        std::cout << '[';
            for (int cols = 0; cols < j; cols++) {
                std::cout << ' ' << array[rows][cols];
            }
        std::cout << "]\n";
    }
    
    std::cout << '\n';
}

Matrix::~Matrix()
{
    for (int count = 0; count < i; count++)
    {
        delete[] array[count]; // release columns
    }

    delete[] array; // release rows
    array = nullptr;
}