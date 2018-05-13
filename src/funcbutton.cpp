#include "graphics.hpp"
#include "funcbutton.hpp"
using namespace std;
using namespace genv;

void funcbutton::draw(unsigned int _target)const{
    gout << move_to(x,y) << color(R,G,B) << line(sx,0) << line(0,sy) << line(-sx,0) << line(0,-sy); //keret
    gout << move_to(x+sx/2-gout.twidth(szov)/2,y+(sy/2)+5) << color(R,G,B) << text(szov);

    if(_target == id){
        int cent = 2;
        gout << move_to(x+cent,y+cent) << color(255,0,0) << line(sx-cent*2,0) << line(0,sy-cent*2) << line(-sx+cent*2,0) << line(0,-sy+cent*2);
    }
}

void funcbutton::action(unsigned int posx, unsigned int posy, unsigned int &_target, int _keycode){
    if((posx >= x && posx <= x+sx)&&(posy >= y && posy <= y+sy)){
        f();
        _target = id;
    }
    if(posx == -1 && posy == -1 && _target == id && _keycode == key_space){
        f();
    }
}
