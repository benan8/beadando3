#ifndef FUNCBUTTON_HPP_INCLUDED
#define FUNCBUTTON_HPP_INCLUDED

#include "widget.hpp"

#include <functional>

class funcbutton : public widget {
    std::function<void()> f;
    std::string szov;
public:
    funcbutton(int _x, int _y, int _sx, int _sy, std::string _szov, int _id, std::function<void()> _fv) : widget(_x,_y,_sx,_sy,_id),szov(_szov),f(_fv){
        //f = _fv;
    }
    void draw(unsigned int _target)const;

    void action(unsigned int posx, unsigned int posy, unsigned int &_target, int _keycode);
};

#endif // FUNCBUTTON_HPP_INCLUDED
