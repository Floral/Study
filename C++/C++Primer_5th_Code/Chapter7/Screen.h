#ifndef SCREEN
#define SCREEN
#include<string>
#include<iostream>
#include"Window_mgr.h"

using std::cin; using std::cout; using std::endl;
using std::string;

class Screen{
    friend class Window_mgr;
public:
    typedef std::string::size_type pos;
    Screen() = default;
    Screen(pos ht, pos wd):height(ht),width(wd),contents(ht*wd, ' '){}
    Screen(pos ht, pos wd, char c):height(ht),width(wd),contents(ht*wd,c){}
    {
        return contents[cursor];
    }
    inline char get(pos ht, pos wd) const;
    
    pos size() const;
    
    Screen &move(pos r, pos c);
    Screen &set(char);
    Screen &set(pos, pos, char);
    Screen &display(std::ostream &os)
    {do_display(os); return *this;}
    const Screen &display(std::ostream &os) const
    {do_display(os); return *this;}

private:
    pos cursor = 0;
    pos height = 0,width = 0;
    std::string contents;

    void do_display(std::ostream &os) const;
 };

inline
Screen &Screen::move(pos r,pos c)
{
    pos row = r*width;
    cursor = row+c;
    return *this;
}

char Screen::get(pos r, pos c) const
{
    pos row = r*width;
    return contents[row+c];
}

Screen::pos Screen::size() const {return height * width;}

inline Screen &Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}
inline Screen &Screen::set(pos r, pos col, char ch)
{
    contents[r*width+col] = ch;
    return *this;
}
void Screen::do_display(std::ostream &os) const
{
    for (size_t r = 0; r < height; ++r)
    {
        for (size_t c = 0; c < width; ++c)
        {
            os<<contents[r*width+c];
        }
        os<<'\n';
    }
}
#endif