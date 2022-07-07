#include <iostream>
#include <fstream>


class SUDOKU {

    int m_sudoku[9][9];
    
    
    bool m_read(const char *filename) { 

        std::ifstream file(filename);

        if (!file.is_open())
            return false;


        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                file >> m_sudoku[i][j];
            }
        }
        return true;
    }

    void m_print() {

        for (int i = 0; i < 9; ++i) {
            if (i % 3 == 0)
                std::cout << "+-------+-------+-------+\n";
            for (int j = 0; j < 9; ++j) {
                if (j % 3 == 0)
                    std::cout << "| ";
                std::cout << m_sudoku[i][j] << " ";
            }
            std::cout << "|\n";
        }
        std::cout << "+-------+-------+-------+\n";
    }

public:

    SUDOKU() {
        if (!m_read("input.txt")) {
            std::cout << "ERROR TO READ THE FILE\n";
            exit(1);
        }
    }

    SUDOKU(const char *filename) {
        if (!m_read(filename))
            std::cout << "ERROR TO READ THE FILE\n";
    }

    void print() {
        m_print();
    }

};



int main() {

    SUDOKU s;

    s.print();


    return 0;
}