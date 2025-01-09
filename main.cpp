/**
 * @file main.cpp
 * @brief The main program that allows you to perform operations on matrices using the Matrix class.
 * 
 * The program allows the user to create matrices and perform operations 
 */

#include "Matrix.cpp"
#include <iostream>

/**
 * @brief main function of program
 * Option to select matrix operations and perform them in an interactive manner.
 */
int main() {
    rs::Matrix<double> A, B;
    std::cout << "Build first matrix:\n";
    A.loadMatrix();

    std::cout << "Build second matrix:\n";
    B.loadMatrix();

    bool done = false;
    do {
        std::cout << "choose operation:\n"
                  << "1. Addition\n"
                  << "2. Subtraction\n"
                  << "3. Multiplication\n"
                  << "4. Transposition\n"
                  << "5. Scalar multiplication\n"
                  << "6. Determinant\n"
                  << "7. Row addition\n"
                  << "8. Col addition\n"
                  << "9. Deleting a row\n"
                  << "10. Deleting a col\n"
                  << "11. Reading a row\n"
                  << "12. Reading a col\n"
                  << "13. Reading a cell\n";

        int choice;
        std::cin >> choice;

        switch (choice)
        {
            case 1: {
                rs::Matrix<double> C = A + B;
                std::cout << "Addition result:\n" << C;
                done = true;
                break;
            }
            case 2: {
                rs::Matrix<double> C = A - B;
                std::cout << "Subtraction result:\n" << C;
                done = true;
                break;
            }
            case 3: {
                rs::Matrix<double> C = A * B;
                std::cout << "Multiplication result:\n" << C;
                done = true;
                break;
            }
            case 4: {
                rs::Matrix<double> C = A.transpose();
                std::cout << "Transposition result:\n" << C;
                done = true;
                break;
            }
            case 5: {
                double scalar;
                std::cout<<"enter a scalar:";
                std::cin >> scalar;
                rs::Matrix C = A * scalar;
                std::cout << "Result of multiplication by " << scalar << ":\n" << C;
                break;
            }
            case 6: {
                try{
                    double determinant = A.determinant();
                    std::cout << "Determinant of matrix A:" << determinant << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "error: " << e.what() << std::endl;
                }    
                break;
            }
            case 7: {  
                std::vector<double> row(A.getCols());
                std::cout <<"Enter row elements to add:\n";
                for (auto& elem : row) {
                    std::cin>>elem;
                } 
                A.addRow(row);
                std::cout << "The row has been added. New matrix:\n" << A;
                break;
            }
            case 8: {   
                std::vector<double> column(A.getRows());
                std::cout<<"Enter col elements to add:\n";
                for (auto& elem : column) {
                    std::cin >> elem;
                }
                A.addColumn(column);
                std::cout << "The column has been added. New matrix:\n" << A;
                break;
            }
            case 9: {   
                size_t rowIndex;
                std::cout << "Enter a row index to remove: ";
                std::cin >> rowIndex;
                try {
                    A.removeRow(rowIndex);
                    std::cout << "The row has been removed. New matrix:\n" << A;
                }
                catch (const std::exception& e) {
                    std::cerr << "error: " << e.what() << std::endl;
                }
                break;
            }
            case 10: {
                size_t colIndex;
                std::cout << "Enter a col index to remove: ";
                std::cin >> colIndex;
                try{
                    A.removeColumn(colIndex);
                    std::cout <<"The column has been removed. New matrix:\n" << A;
                }
                catch (const std::exception& e) {
                    std::cerr << "error: " << e.what() << std::endl;
                }
                break;
            }
            case 11: {      
                size_t rowIndex;
                std::cout << "Enter a row index for reading: ";
                std::cin >> rowIndex;
                try{
                    std::vector<double> row = A.getRow(rowIndex);
                    std::cout << "row " << rowIndex << ": ";
                    for (const auto& elem : row) {
                        std::cout << elem << " ";
                    } 
                    std::cout << std::endl;
                }
                catch (const std::exception& e) {
                    std::cerr << "error: " << e.what() << std::endl;
                }
                break;
            }
            case 12: {     
            size_t colIndex;
            std::cout << "Enter a col index for reading: ";
            std::cin >> colIndex;
            try {
                std::vector<double> column = A.getColumn(colIndex);
                std::cout << "col " << colIndex << ": ";
                for (const auto& elem : column) {
                    std::cout << elem << " ";
                }
                std::cout << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "error: " << e.what() << std::endl;
            }
            break;
            }
            case 13: {      
                size_t rowIndex, colIndex;
                std::cout << "Enter a row index: ";
                std::cin >> rowIndex;
                std::cout << "Enter a col index: ";
                std::cin >> colIndex;
                try {
                    double value = A.getCell(rowIndex, colIndex);
                    std::cout << "number in the cell (" << rowIndex << ", "<<colIndex << "): " << value << std::endl;
                }
                catch (const std::exception& e) {
                    std::cerr << "error: " << e.what() << std::endl;
                }
                break;
            }
            default:
            {
                std::cout << "unknow operation." << std::endl;
                break;
            }
        }
    }
    while (!done);

    return 0;

}