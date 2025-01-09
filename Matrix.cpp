/**
 * @file Matrix.cpp
 * @brief implementation of the matrix class and its operations.
 */

#include "Matrix.hpp"
#include <stdexcept>

namespace rs {

/**
 * @brief default constructor for the matrix class
 * @param r number of rows 
 * @param c number of cols
 */
template <typename T> 
Matrix<T>::Matrix(size_t r, size_t c) : rows(r), cols(c), myVector(r, std::vector<T>(c,0)) {}

/**
 * @brief constructor to initialize a matrix with given values
 * @param values 2D vector representing the matrix elements
 */
template <typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& values) : myVector(values), rows(values.size()), cols(values.empty() ? 0 : values[0].size()) {}

/**
 * getter for rows
 * @brief gets the number of rows
 * @return the number of rows
 */
template <typename T>
size_t Matrix<T>::getRows() const {
    return rows;
}

/**
 * getter for cols
 * @brief gets  the number of columns
 * @return the number of columns
 */
template <typename T>
size_t Matrix<T>::getCols() const {
    return cols;
}

/** indexing operators
 * @brief Access a row in the matrix
 * @param index index of the row to access
 * @return reference to the row vector
 */
template <typename T>
std::vector<T>& Matrix<T>::operator[](size_t index) {
    return myVector[index];
}

/**
 * @brief access a row in the matrix (const version)
 * @param index index of the row to access
 * @return const reference to the row vector
 */
template <typename T>
const std::vector<T>& Matrix<T>::operator[](size_t index) const {
    return myVector[index];
}

/**
 * addiction
 * @brief overload the +operator to add two matrices
 * @param other the matrix to add
 * @return new matrix
 * @throws std::invalid_argument if matrices have different dimensions
 */
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrixs must have the same dimensions");
    }
    Matrix result(rows, cols);
    for (size_t i=0; i<rows; ++i) {
        for(size_t j=0; j<cols; ++j) {
            result[i][j] = myVector[i][j] + other[i][j];
        }
    }
    return result;
}

/**
 * multiplication
 * @brief overloads * operator 
 * @param other the matrix to multiply
 * @return new matrix after operation
 * @throws std::invalid_argument if the number of columns in the first matrix is different from kolumns in second
 */ 
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("The number of columns of the first matrix must be equal to the number of rows of the second matrix.");
    }
    Matrix result(rows, other.cols);
    for (size_t i=0; i<rows; ++i) {
        for (size_t j=0; j<other.cols; ++j) {
            for (size_t k=0; k<cols; ++k) {
                result[i][j] += myVector[i][k] * other[k][j];
            }
        }
    }
    return result;
}

/**
 * substraction
 * @brief overload - operator to subtract two matrices
 * @param other matrix to substract
 * @return new matrix containing the difference
 * @throws std::invalid_argument if dimensions of matrices do not match
 */
template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrixs must have the same dimensions");
    }
    Matrix result(rows, cols);
    for (size_t i =0; i<rows; ++i) {
        for (size_t j=0; j<cols; ++j) {
            result[i][j] = myVector[i][j] - other[i][j];
        }
    }
    return result;
}

/**
 * @brief overload the output stream operator for printing a matrix
 * this operator allows a Matrix object to be printed directly using std::ostream
 * @param out the output stream to which the matrix will be written
 * @param matrix the Matrix object to be printed
 * @return std::ostream& reference to the output stream for chaining.
*/
template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix) {
    for (const auto& row : matrix.myVector) {
        for (const auto& elem : row) {
            out << elem << " ";
        }
        out << std::endl;
    }
    return out;
}

/**
 * transposition
 * @brief computes the transpose of the matrix
 * @return new matrix containing the transpose
 */
template <typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix result(cols, rows);          
    for (size_t i=0; i<rows; ++i) {
        for (size_t j=0; j<cols; ++j) {
            result[j][i] = myVector[i][j];
        }
    } 
    return result;
}

/**
 * scalar multiplication
 * @brief overload scalar value to multiply with
 * @param scalar the scalar value to multiply 
 * @return new matrix containing the result
 */
template <typename T>
Matrix<T> Matrix<T>::operator*(T scalar) const {
    Matrix result(rows, cols);
    for(size_t i=0; i<rows; ++i) {
        for(size_t j=0; j<cols; ++j){
            result[i][j] = myVector[i][j] * scalar;
        }
    }
    return result;
}

/**
 * determinant
 * @brief computes the determinant of the matrix
 * @return the determinant value
 * @throws std::invalid_argument if the matrix is not square
 */
template  <typename T>
T Matrix<T>::determinant() const {
    if (rows != cols) {
        throw std::invalid_argument("The determinant can only be calculated for a square matrix.");
    }
    if (rows == 1) return myVector[0][0];   

    if (rows == 2) {                    
        return myVector[0][0] * myVector[1][1] - myVector[0][1] * myVector[1][0];
    }
    T det = 0;
    for (size_t col=0; col<cols; ++col) {
        Matrix<T> subMatrix(rows -1, cols -1);
        for (size_t i = 1; i < rows; ++i) {
            size_t subColIndex = 0;
            for (size_t j=0; j<cols; ++j) {
                if (j==col) continue;
                subMatrix[i - 1][subColIndex++] = myVector[i][j];
            }
        }
        det += (col % 2 == 0 ? 1 : -1) * myVector[0][col] * subMatrix.determinant();
    }
    return det;
}

/**
 * @brief adds a row to the matrix
 * @param row the row to add
 * @throws std::invalid_argument if the row size does not match the number of cols
 */
template <typename T>
void Matrix<T>::addRow(const std::vector<T>& row) {
    if (row.size() != cols) {
        throw std::invalid_argument("row length does not match number of columns");
    }
    myVector.push_back(row);
    ++rows;
}

/**
 * @brief adds new column to the matrix
 * the size of the input column must match the number of rows in the matrix
 * @param column vector containing the elements of the column to be edded
 * @throws std::invalid_argument if the size of thecolumn does not match the number of rows.
 */
template <typename T>
void Matrix<T>::addColumn(const std::vector<T>& column) {
    if (column.size() != rows) {
        throw std::invalid_argument("column length does not match number of rows");
    }
    for (size_t i=0; i<rows; ++i) {
        myVector[i].push_back(column[i]);
    }
    ++cols;
}

/**
 * @brief removes a specified row from the matrix
 * @param rowIndex the zero-based index of the row to be removed
 * @throws std::out_of_range if the provided row index is bigger than number of rows in the matirx
 */
template <typename T>
void Matrix<T>::removeRow(size_t rowIndex) {
    if (rowIndex >= rows) {
        throw std::out_of_range("Row index out of range");
    }
    myVector.erase(myVector.begin() + rowIndex);
    --rows;
}

/**
 * @brief removes a specified column from the matrix
 * this function removes the column at the specified index from matrix
 * @param colIndex the zero-based index of the column to be removed
 * @throws std::out_of_range if provided column index is bigger than number of columns in matrix
 */
template <typename T>
void Matrix<T>::removeColumn(size_t colIndex) {
    if (colIndex >= cols) {
        throw std::out_of_range("Column index out of range");
    }
    for (auto& row : myVector) {
        row.erase(row.begin() + colIndex);
    }
    --cols;
}

/**
 * @brief retrieves a specific row from the matrix
 * @param rowIndex the zero-based index of the row to retrieve
 * @return vector containing the elements of the specified row.
 * @throws std::out_of_range if the provided row index is greater than number rows in matrix
 */
template <typename T>
std::vector<T> Matrix<T>::getRow(size_t rowIndex) const {
    if (rowIndex >= rows) {
        throw std::out_of_range("Row index out of range");
    }
    return myVector[rowIndex];
}
/**
 * @brief retrieves a specific col from the matrix
 * @param colIndex the zero-based index of the column to retrieve
 * @return vector containing the elements of the specified column.
 * @throws std::out_of_range if the provided col index is greater than number cols in matrix
 */
template <typename T>
std::vector<T> Matrix<T>::getColumn(size_t colIndex) const {
    if (colIndex >= cols) {
        throw std::out_of_range("Column index out of range");
    }
    std::vector<T> column(rows);
    for (size_t i=0; i<rows; ++i){
        column[i] = myVector[i][colIndex];
    }
    return column;
}

/**
 * @brief Retrieves the value of a specific cell in the matrix
 * @param row The zero-based index of the row of the desired cell
 * @param col The zero-based index of the column of the desired cell
 * @return The value at the specified cell in the matrix
 * @throws std::out_of_range If the provided row or column index is out of the matrix's bounds.
 */
template <typename T>
T Matrix<T>::getCell(size_t row, size_t col) const {
    if (row >= rows || col >= cols) {
        throw std::out_of_range("Index out of range of matrix");
    }
    return myVector[row][col];
} 

/**
 * @brief Reads and initializes the matrix with user input. 
 * Prompts the user to specify the number of rows and columns, 
 * then populates the matrix by accepting input for each element row by row.
 */
template <typename T>
void Matrix<T>::loadMatrix() {
    std::cout << "enter number of row: ";
    std::cin >> rows;
    std::cout << "enter number of column: ";
    std::cin >> cols;
    myVector.resize(rows, std::vector<T>(cols));
    std::cout << "Enter element of matrix (row by row): ";
    for (size_t i=0; i<rows; ++i) {
        for (size_t j=0; j<cols; ++j) {
            std::cin >> myVector[i][j];
        }
    }
}

}