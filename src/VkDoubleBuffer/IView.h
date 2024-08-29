#ifndef IView_H
#define IView_H

#include <Xm/Xm.h>
#include "VkDoubleBuffer.h"

using namespace std;

class IView : public VkDoubleBuffer {

public:
    IView(const char *name, Widget parent);
    ~IView();
    
public:
    void draw();

private:
    int _visualState; 

private:
    Pixmap _vaPixmap;
    Pixmap _sgiPixmap;
};

#endif // IView_H