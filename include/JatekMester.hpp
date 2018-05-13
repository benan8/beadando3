#ifndef JATEKMESTER_HPP
#define JATEKMESTER_HPP

#include "widget.hpp"
#include <vector>


class JatekMester
{
    std::vector<std::vector<widget*> > szamok;
    std::vector<std::vector<int>> SolvedBoard;
    public:
        JatekMester();
        bool GenerateSolvedBoard();
        bool FindUnassignedLocation(int &row, int &col);
        bool UsedInRow(int row, int col, int num,bool check);
        bool UsedInCol(int row, int col, int num,bool check);
        bool UsedInBox(int boxStartRow, int boxStartCol, int num,bool check);
        bool isSafe(int row, int col, int num, bool check);
        void start(int id);
        bool checkWin();
};

#endif // JATEKMESTER_HPP
