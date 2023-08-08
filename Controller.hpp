#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include <Message.hpp>

typedef struct ControllerType
{
    double x;  //x軸
    double y;  //y軸 
    bool l;    //左回転モード
    bool r;    //右回転モード
    bool a, b, c; //ボタン
} controller_t;

//  create message
typedef sb::Message<controller_t> Controller;

#endif

