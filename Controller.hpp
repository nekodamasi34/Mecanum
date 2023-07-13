#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <Message.hpp>

typedef struct ControllerType
{
    double x;  //x軸
    double y;  //y軸 
    bool l;    //左回転モード
    bool r;    //右回転モード
} controller_t;

//  create message
typedef sb::Message<controller_t> Controller;

#endif

