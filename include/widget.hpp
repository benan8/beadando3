#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED

#include <string>

class widget{
protected:
    unsigned int x,y;    //pozicio
    unsigned int sx,sy;  //méret

    char R,G,B;
     char i_R = 55, i_G = 55, i_B = 55;

    int id;

public:
    widget(int _x, int _y, int _sx, int _sy, unsigned int _id):x(_x),y(_y),sx(_sx), sy(_sy), id(_id){
        R=255;
        G=255;
        B=255;
    };

    virtual void draw(unsigned int _target)const = 0;

    virtual void action(unsigned int posx, unsigned int posy, unsigned int &_target, int _keycode) = 0;

    virtual int get_value() = 0;
    virtual std::string get_type() = 0;

    void setrgb(char _R, char _G, char _B);
    void change_color(char _R, char _G, char _B/*, unsigned _target*/);


};

#endif // WIDGET_HPP_INCLUDED
