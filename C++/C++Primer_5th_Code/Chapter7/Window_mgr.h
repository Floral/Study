#ifndef WINDOW_MGR
#define WINDOW_MGR
#include<iostream>
#include<vector>
#include"Screen.h"

class Window_mgr
{
private:
    std::vector<Screen> screens{Screen(24,80,' ')};

public:
    Window_mgr(/* args */);
    ~Window_mgr();
    using ScreenIndex = std::vector<Screen>::size_type;
    void clear(ScreenIndex);

};

void Window_mgr::clear(ScreenIndex i)
{
    Screen &s=screens[i];
    s.contents = string(s.height * s.width,' ');
}

#endif