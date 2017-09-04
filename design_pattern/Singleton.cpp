/* @UNIVESRE.COM_20161219_HYe
 * Singleton.cpp
 * 单件模式: 保证该类只有一个实例, 并且提供一个访问它的全局访问点. */

#include "Singleton.h"

Singleton* Singleton::_instance = 0;    //初始化地址为0, 即NULL;

Singleton* Singleton::Instance(){       //客户仅通过Instance()访问此单件类;
    if(_instance == 0){
        _instance = new Singleton;      //如果_instance还没指向任何一个对象, 则新建一个对象;
    }
    return _instance;                   //返回_instance, 无论是刚创建的还是原来已有的;
}