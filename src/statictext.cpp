#include "graphics.hpp"
#include "widget.hpp"
#include "statictext.hpp"

using namespace genv;
using namespace std;

void statictext::draw(unsigned int _target)const{
    //gout << move_to(x,y) << color(R,G,B) << line(sx,0) << line(0,sy) << line(-sx,0) << line(0,-sy); //keret
    gout << move_to(x+2,y+(sy/2)+5) << color(R,G,B) << text(szov);
}

void statictext::action(unsigned int posx, unsigned int posy, unsigned int &_target, int _keycode){
}

void statictext::change_text(string _text){
    szov = _text;
}
