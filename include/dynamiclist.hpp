#ifndef DYNAMICLIST_HPP_INCLUDED
#define DYNAMICLIST_HPP_INCLUDED

#include "widget.hpp"

class dynamiclist : public widget {
protected:
    std::vector<std::string> tartalom;
    unsigned int target_element=0;
    int sor_mag;    //egy sor magass�ga
    unsigned int scroll=0;
    unsigned int kifer; //h�ny sor f�rjen az ablakba

    int cent = 2;   //a kijel�l�st jelzo piros keretnek, az ablak keret sz�ltol val� t�vols�ga pixelben

    void scroll_after_target(){     //ha a nyilakkal l�pkedek az ablakban mindig l�that� legyen a kijel�lt elem
        if(target_element >= kifer+scroll){     //a kijel�lt elem ha kimegy az ablakb�l ut�nag�rget�nk
            scroll=target_element-kifer+1;
        }else if(target_element < scroll){
            scroll = target_element;
        }
    }
public:
    dynamiclist(int _x, int _y, int _sx, int _sy, int _kifer, std::vector<std::string> _tartalom, int _id) : widget(_x,_y,_sx,_sy,_id), kifer(_kifer),tartalom(_tartalom){
        sor_mag = sy/kifer;
    }

    void draw(unsigned int _target)const;

    void action(unsigned int posx, unsigned int posy, unsigned int &_target, int _keycode);

    void add_element(std::string _elem);

    void scroll_up();

    void scroll_down();

    std::string get_target();

    std::string get_number(unsigned int _target);

    void delete_target();

    void delete_number(unsigned int _target);

    int get_size();
};

#endif // DYNAMICLIST_HPP_INCLUDED
