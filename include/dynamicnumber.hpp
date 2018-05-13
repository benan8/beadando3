#ifndef DYNAMICNUMBER_HPP_INCLUDED
#define DYNAMICNUMBER_HPP_INCLUDED

#include <sstream>
#include "widget.hpp"

class dynamicnumber : public widget{
protected:
    int szam;
    int minim;
    int maxim;
    int next;


    int cent = 2; //kijel�l�skor megjelen� piros keret max m�rettol val� t�vols�ga pixelben. min�l nagyobb a sz�m ann�l kisebb a keret
    int gomb_szel = 30; //l�ptetogombok sz�less�ge pixelben
public:
    dynamicnumber(int _x, int _y, int _sx, int _sy, double _szam, int _minim, int _maxim, int _id) : widget(_x,_y,_sx,_sy,_id),szam(_szam),minim(_minim),maxim(_maxim){};

    void draw(unsigned int _target)const;

    void action(unsigned int posx, unsigned int posy, unsigned int &_target, int _keycode);

    void set_value(int _szam);
    std::string get_type(){return "dynNum";}
    int get_value();


    void set_tartomany(int also, int felso);
};


#endif // DYNAMICNUMBER_HPP_INCLUDED
