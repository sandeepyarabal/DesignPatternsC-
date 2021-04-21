#include <iostream>

using namespace std;

class WindowImp
{
public:
    virtual void DevDrawText() = 0;

private:


};

class XwindowImp : public WindowImp
{
public:
    void DevDrawText()
    {
        cout << "DevDrawText" << "\n";
    }
};

class PMwindowImp : public WindowImp
{

};


class window
{
public:
   
    virtual void DrawRect() = 0;

protected:

private:

    WindowImp* _WindowImp;
  
};

class IconWindow:public window
{
public:
    void DrawRect()
    {
        WindowImp* _windowImp;
        _windowImp = new XwindowImp();

        _windowImp->DevDrawText();

        cout << "DrawBorder" << "\n";
       
    }

   
};

class TransientWindow :public window
{
public:
    void DrawCloseBox()
    {
        cout << "DrawCloseBox" << "\n";
       
    }

};



int main()
{
    window* win = new IconWindow();
    win->DrawRect();
   
   
    std::cout << "Hello World!\n";
}
