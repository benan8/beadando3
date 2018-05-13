#ifndef STATICTEXT_HPP_INCLUDED
#define STATICTEXT_HPP_INCLUDED

#include "widget.hpp"
#include <cstdlib>

class statictext : public widget{
protected:
    std::string szov;

public:
    statictext(int _x, int _y, int _sx, int _sy, std::string _szov) : widget(_x,_y,_sx,_sy,-1),szov(_szov){};

    void draw(unsigned int _target)const;

    void action(unsigned int posx, unsigned int posy, unsigned int &_target, int _keycode);

    void change_text(std::string _text);

    std::string get_text(){
        return szov;
    }
    std::string get_type(){return "static";}
    int get_value(){
        return atoi(szov.c_str());
    }
};

#endif // STATICTEXT_HPP_INCLUDED
