#include "graphics.hpp"
#include "widget.hpp"

using namespace genv;
using namespace std;

void widget::setrgb(char _R, char _G, char _B)
{
    if(_R >= 0 && _R <= 255)R=_R;
    else if(_R < 0)R=0;
    else if(_R > 255)R=255;

    if(_G >= 0 && _G <= 255)G=_G;
    else if(_G < 0)G=0;
    else if(_G > 255)G=255;

    if(_B >= 0 && _B <= 255)B=_B;
    else if(_B < 0)B=0;
    else if(_B > 255)B=255;
}

void widget::change_color(char _R, char _G, char _B/*,unsigned _target*/)
{
    /*if (_target == id)
    {*/
        i_R = _R;
        i_G = _G;
        i_B = _B;
    //}
}
