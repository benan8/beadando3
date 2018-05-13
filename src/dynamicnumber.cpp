#include "graphics.hpp"
#include "widget.hpp"
#include "dynamicnumber.hpp"
#include <sstream>

using namespace genv;
using namespace std;

void dynamicnumber::draw(unsigned int _target)const{
    stringstream s;
    s << szam;
    gout << move_to(x,y) << color(i_R,i_G,i_B) << box(sx,sy);
    gout << move_to(x,y) << color(R,G,B) << line(sx,0) << line(0,sy) << line(-sx,0) << line(0,-sy); //keret
    gout << move_to(x+2,y+(sy/2)+5) << text(s.str());   //tartalom

    gout << move_to(x+sx-gomb_szel,y) << color(R,G,B) << line(0,sy);    //léptetogombok
    gout << move_to(x+sx-gomb_szel,y+sy/2) << line(gomb_szel,0);

    if(_target == id){
        gout << move_to(x+2+gout.twidth(s.str()),y+(sy/2)+5) << color(255,255,255) << line(0,-15); //kurzor vonal
        gout << move_to(x+cent,y+cent) << color(255,0,0) << line(sx-cent*2,0) << line(0,sy-cent*2) << line(-sx+cent*2,0) << line(0,-sy+cent*2);
    }

    gout << move_to(x+sx-2*gomb_szel/3,y+2*sy/5) << color(R,G,B) << text("^");        //nyilacskák belerajzolása
    gout << move_to(x+sx-2*gomb_szel/3,y+4*sy/5) << text("v");
}

void dynamicnumber::action(unsigned int posx, unsigned int posy, unsigned int &_target, int _keycode){
    stringstream s;
    s << szam;
    if((posx >= x && posx <= x+sx)&&(posy >= y && posy <= y+sy)){
        _target = id;
    }
    if(posx == -1 && posy == -1 && _target == id){  //ha o van kiválasztva
        next = (int)szam*10+(int)_keycode-48;   //48 a nulla ascii kódja
        if(_keycode >= 48 && _keycode <= 57 && gout.twidth(s.str()) < sx-cent-8){ //8 egy space mérete pixelben
            set_value(next);
        }else if(_keycode == key_backspace && szam/10 >= 0){
            szam=szam/10;
        }else if(_keycode == key_up && szam < maxim){       //megnyomom a fölfelé nyilat
            szam++;
        }else if(_keycode == key_down && szam > minim){     //megnyomom a lefelé nyilat
            szam--;
        }else if(_keycode == key_pgup && szam+maxim/10 < maxim){
            szam += maxim/10;
        }else if(_keycode == key_pgdn && szam-maxim/10 > minim){
            szam -= maxim/10;
        }else if(_keycode == key_home){
            szam = minim;
        }else if(_keycode == key_end){
            szam = maxim;
        }
    }else if(posx > x+sx-gomb_szel && posx < x+sx && posy > y && posy < y+sy/2 && szam < maxim){     //ha rákattintok a felfelé nyilra
        szam++;
    }else if(posx > x+sx-gomb_szel && posx < x+sx && posy < y+sy && posy > y+sy/2 && szam > minim){     //ha rákattintok a lefelé nyilra
        szam--;
    }
}

void dynamicnumber::set_value(int _szam){
    if(_szam < minim){
        szam = minim;
    }else if(_szam > maxim){
        szam = maxim;
    }else{
        szam = _szam;
    }
}

int dynamicnumber::get_value(){
    return szam;
}

void dynamicnumber::set_tartomany(int also, int felso){
    if(also < felso){
        minim = also;
        maxim = felso;
        if(szam > felso)szam = felso;
        else if(szam < also)szam = also;
    }
}


