#include "graphics.hpp"
#include <iostream>
#include <vector>

#include "dynamiclist.hpp"

using namespace genv;
using namespace std;

void dynamiclist::draw(unsigned int _target)const{
    gout << move_to(x,y) << color(R,G,B) << line(sx,0) << line(0,sy) << line(-sx,0) << line(0,-sy);

    unsigned loc_kifer = kifer;
    if(loc_kifer > tartalom.size())loc_kifer = tartalom.size();
    for(unsigned int i=scroll;i < scroll+loc_kifer;i++){
        unsigned int j = i-scroll;
        if(i == target_element){
            gout << move_to(x+cent,y+cent+j*sor_mag) << color(55,55,55) << box(sx-cent*2,sor_mag-cent);
            gout << move_to(x+cent,y+cent+j*sor_mag) << color(255,0,0) << line(sx-cent*2,0) << line(0,sor_mag-cent) << line(-sx+cent*2,0) << line(0,-sor_mag+cent);
        }
        gout << move_to(x+4,y+(j+1)*sor_mag-sor_mag/5) << color(R,G,B) << text(tartalom[i]);
    }

    if(_target == id){
        gout << move_to(x+cent,y+cent) << color(255,0,0) << line(sx-cent*2,0) << line(0,sy-cent*2) << line(-sx+cent*2,0) << line(0,-sy+cent*2);
    }
}

void dynamiclist::action(unsigned int posx, unsigned int posy, unsigned int &_target, int _keycode){
    if((posx >= x && posx <= x+sx)&&(posy >= y && posy <= y+sy)){
        _target = id;
        unsigned loc_kifer = kifer;
        if(loc_kifer > tartalom.size())loc_kifer = tartalom.size();
        if(posy-y-cent > 0 && posy-y-cent < loc_kifer*sor_mag){
            target_element = ((int)(posy-y-cent)/sor_mag)+scroll;
        }
    }else if(posx == -1 && posy == -1 && _target == id){
        if(_keycode == key_up && target_element > 0){
            target_element--;
            scroll_after_target();
        }else if(_keycode == key_down && target_element < tartalom.size()-1){
            target_element++;
            scroll_after_target();
        }else if(_keycode == -btn_wheelup){
            scroll_up();
        }else if(_keycode == -btn_wheeldown){
            scroll_down();
        }
    }
}

 void dynamiclist::add_element(std::string _elem){
    tartalom.push_back(_elem);
    target_element = tartalom.size()-1;
    if(target_element >= kifer+scroll){
        scroll = tartalom.size()-kifer;
    }
}

void dynamiclist::scroll_up(){
    if(scroll > 0)scroll--;
}

void dynamiclist::scroll_down(){
    if(0 < (int)(tartalom.size()-kifer-scroll))scroll++;
}

std::string dynamiclist::get_target(){
    if(tartalom.size()>0)return tartalom[target_element];
    else return "";
}

std::string dynamiclist::get_number(unsigned int _target){
    if(tartalom.size() > 0 && _target >= 0 && _target <= tartalom.size()-1)return tartalom[_target];
    else return "";
}

void dynamiclist::delete_target(){
    if(tartalom.size() > 0){
        for(unsigned int i=target_element+1;i < tartalom.size();i++){
            tartalom[i-1] = tartalom[i];
        }
        tartalom.pop_back();
        if(target_element > 0)target_element--;
    }
}

void dynamiclist::delete_number(unsigned int _target){
    if(tartalom.size() > 0 && _target >= 0 && _target <= tartalom.size()-1){
        for(unsigned int i=_target+1;i < tartalom.size();i++){
            tartalom[i-1] = tartalom[i];
        }
        tartalom.pop_back();
        if(target_element > 0)target_element--;
    }
}

int dynamiclist::get_size(){
    return tartalom.size();
}
