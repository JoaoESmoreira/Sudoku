#include <iostream>
#include <fstream>


class SUDOKU {

    int m_sudoku[9][9];

    typedef struct _POSITION{
        int x;
        int y;
    } Position;
    
    
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

    bool m_can_put(const int &x, const int &y, const int &value) {

        for (int i = 0; i < 9; ++i) {
            if ((i != y && m_sudoku[x][i] == value) || (m_sudoku[i][y] == value && i != x)) 
                return false;
        }

        int x_cast = x / 3;
        int y_cast = y / 3;

        for (int i = x_cast*3; i < x_cast*3 + 3; ++i) {
            for (int j = y_cast*3; j < y_cast*3 + 3; ++j) {
                if (i != x && j != y && m_sudoku[i][j] == value) 
                    return false;
            }
        }

        return true;
    }

    Position m_void_cell() {
        Position position;

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (m_sudoku[i][j] == 0) {
                    position.x = i;
                    position.y = j;
                    return position;
                }
            }
        }
        position.x = 10;
        position.y = 10;
        return position;
    }

    bool m_solve() {
        Position position = m_void_cell();

        if (position.y == 10)
            return true;

        for (int i = 1; i < 10; ++i) {
            if (m_can_put(position.x, position.y, i)) {
                m_sudoku[position.x][position.y] = i;
                if (m_solve())
                    return true;
                
                m_sudoku[position.x][position.y] = 0;
            }
        }

        return false;
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

    bool solve() {
        return m_solve();
    }

    void print() {
        m_print();
    }

};



int main() {

    SUDOKU s;

    s.print();
    std::cout << s.solve() << "\n";
    s.print();


    return 0;
}