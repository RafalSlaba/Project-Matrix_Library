#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <stdexcept>

namespace rs {

template <typename T>    
class Matrix {
    private:
        std::vector<std::vector<T>> myVector;
        size_t rows;
        size_t cols;

    public:
        //default constructor
        Matrix(size_t r=0, size_t c=0);
        //constructor to initialize data
        Matrix(const std::vector<std::vector<T>>& values);

        //getter for rows
        size_t getRows() const;
        //getter for cols
        size_t getCols() const;

        //indexing operator
        std::vector<T>& operator[](size_t index);
        const std::vector<T>& operator[](size_t index) const;
        //operator overload + 
        Matrix<T> operator+(const Matrix& other) const;
        //operator overload *
        Matrix<T> operator*(const Matrix& other) const;        
        //operator overload - 
        Matrix<T> operator-(const Matrix& other) const;
        //operator overload << (for streaming output)
        template <typename D>
        friend std::ostream& operator<<(std::ostream& out, const Matrix<D>& matrix);
        //operator overloading for scalar multiplication
        Matrix operator*(T scalar) const;

        //method for transposition
        Matrix<T> transpose() const;
        //method for determinant
        T determinant() const; 
        //method for reading the cell
        T getCell(size_t row, size_t col) const;
        //cols and rows operations
        void addRow(const std::vector<T>& row);
        void addColumn(const std::vector<T>& column);
        void removeRow(size_t rowIndex);
        void removeColumn(size_t colIndex);
        //reading selected row or col
        std::vector<T> getRow(size_t rowIndex) const;
        std::vector<T> getColumn(size_t colIndex) const;
        
        //function to load matrix
        void loadMatrix();
};

}
#endif 