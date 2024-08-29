#ifndef VKDOUBLEBUFFER_H
#define VKDOUBLEBUFFER_H

#include <Vk/VkComponent.h>
#include <Vk/VkPixmap.h>
#include <Xm/Xm.h>
#include <Xm/DrawingA.h>
#include <iostream>

using namespace std;

class VkDoubleBuffer : public VkComponent {

public:
    Dimension _width;
    Dimension _height;  

public:
    Pixmap _canvas;

public:
    VkDoubleBuffer(const char *name, Widget parent);
    ~VkDoubleBuffer();

public:
    virtual void draw();
    virtual void update();
    virtual void resize();

private:
    void swapBuffers();

private:
    void createWidget(const char *name, Widget parent);
    Pixmap createPixmap(Widget widget, int width, int height);
};

#endif // VKDOUBLEBUFFER_H
