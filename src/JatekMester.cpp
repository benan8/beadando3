#include "JatekMester.hpp"
#include "graphics.hpp"
#include "dynamicnumber.hpp"
#include "statictext.hpp"
#include <string>

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace genv;

const int XX = 1000;
const int YY = 600;

JatekMester::JatekMester()
{
    gout.open(XX,YY);

    srand(time(0));
    SolvedBoard = {{rand() % 9 + 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, rand() % 9 + 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, rand() % 9 + 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, rand() % 9 + 1}
    };
    GenerateSolvedBoard();
    for (unsigned i = 0; i < 25; i++)
        SolvedBoard[rand() % 9][rand() % 9] = 0;
    int id = 0;
    //widget * text = new statictext(600,10,100,100,"Uj jatek F5");
    for (int i = 0; i < 9; i++)
    {
        std::vector<widget*> szam;
        for (int j = 0; j < 9; j++)
        {
            if (SolvedBoard[j][i] == 0)
                szam.push_back(new dynamicnumber(j*58+25,i*58+25,50,50,SolvedBoard[j][i],1,9,++id));
            else
                szam.push_back(new statictext(j*58+25,i*58+25,50,50,std::to_string(SolvedBoard[j][i])));
            //std::cout << id << std::endl;
        }
        szamok.push_back(szam);
        szam.clear();
    }
    start(id);
}

void JatekMester::start(int id)
{
    unsigned int target = 0;
    for (unsigned i = 0; i < szamok.size(); i++)
        for (unsigned j = 0; j < szamok[0].size(); j++)
            szamok[i][j]->draw(target);
        //text->draw(target);
    gout.refresh();
    event ev;

//    unsigned int target=0;
    bool bal_klikk = false;
    unsigned int posx=0,posy=0;
    int keycode =0;

    while (gin >> ev && ev.keycode != key_escape)
    {

        if(ev.pos_x)posx=ev.pos_x;
        if(ev.pos_y)posy=ev.pos_y;
        if(ev.button==btn_left)bal_klikk=true;
        if(ev.keycode == key_tab && id!=0) target = ++target%id;
        if(ev.keycode)keycode = ev.keycode;
        else if(ev.button)keycode = ev.button;
        if(bal_klikk==true)
        {
            for(unsigned int i=0; i<szamok.size(); i++)
                for (unsigned j = 0; j < szamok[0].size(); j++)
                    szamok[i][j]->action(posx,posy,target,keycode);

            bal_klikk=false;
            keycode = 0;
        }

        if(keycode)
        {
            for(unsigned int i=0; i<szamok.size(); i++)
            {
                for (unsigned j = 0; j < szamok[0].size(); j++)
                {
                    szamok[i][j]->action(-1,-1,target,keycode);
                    SolvedBoard[i][j] = szamok[i][j]->get_value();
                    if (!isSafe(i, j, szamok[i][j]->get_value(),true) && szamok[i][j]->get_type() !="static" && szamok[i][j]->get_value() != 0)
                    {
                        szamok[i][j]->change_color(255,0,0/*,target*/);
//                        std::cout << szamok[i][j]->get_value() << ' ';
                        //szamok[i][j]->setrgb(255,0,0);
                    }
                    else
                    {
//                        std::cout << "S ";
                        szamok[i][j]->change_color(55,55,55/*,target*/);
                    }


                }
//                std::cout << std::endl;
            }
            keycode = 0;
            if(checkWin()){
                std::cout << "Nyert" << std::endl;
            }
        }
        for (unsigned i = 0; i < szamok.size(); i++)
            for (unsigned j = 0; j < szamok[0].size(); j++)
                szamok[i][j]->draw(target);
        gout << refresh;
        gout << move_to(0,0) << color(0,0,0) << box_to(XX-1,YY-1);
        keycode = 0;
//        for(unsigned int i=0; i<SolvedBoard.size(); i++)
//        {
//            for (unsigned j = 0; j < SolvedBoard[0].size(); j++)
//            {
//
//                std::cout << SolvedBoard[i][j] << ' ';
//            }
//            std::cout << std::endl;
//        }
//        std::cout << std::endl << std::endl;
    }
}

bool JatekMester::GenerateSolvedBoard()
{
    int row, col;
    if (!FindUnassignedLocation(row, col))
        return true;
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(row, col, num,false))
        {
            SolvedBoard[row][col] = num;

            if (GenerateSolvedBoard())
                return true;
            SolvedBoard[row][col] = 0;
        }
    }
    return false;
}

bool JatekMester::FindUnassignedLocation(int &row, int &col)
{
    for (row = 0; row < (int)SolvedBoard.size(); row++)
        for (col = 0; col < (int)SolvedBoard[0].size(); col++)
            if (SolvedBoard[row][col] == 0)
                return true;
    return false;
}

bool JatekMester::UsedInRow(int row, int _col, int num,bool check)
{
    for (int col = 0; col < (int)SolvedBoard.size(); col++)
        if (SolvedBoard[row][col] == num && col != _col)
            return true;
    return false;
}

bool JatekMester::UsedInCol(int _row, int col, int num,bool check)
{
    for (int row = 0; row < (int)SolvedBoard.size(); row++)
        if (SolvedBoard[row][col] == num  && row != _row)
            return true;
    return false;
}

bool JatekMester::UsedInBox(int _row, int _col, int num,bool check)
{
    int boxStartRow = _row - _row%3;
    int boxStartCol = _col - _col%3;
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (SolvedBoard[row+boxStartRow][col+boxStartCol] == num  && (row+boxStartRow != _row && col+boxStartCol != _col))
                return true;
    return false;
}

bool JatekMester::isSafe(int row, int col, int num, bool check)
{
    return !UsedInRow(row, col, num, check) &&
           !UsedInCol(row, col, num, check) &&
           !UsedInBox(row, col, num, check);
}

bool JatekMester::checkWin()
{
    for (std::vector<int> & a : SolvedBoard)
        for (int & b : a)
            if (b == 0) return false;
     for (unsigned i = 0; i < SolvedBoard.size(); i++)
            for (unsigned j = 0; j < SolvedBoard[0].size(); j++)
                if (!isSafe(i, j, szamok[i][j]->get_value(),true))
                    return false;
    return true;
}

