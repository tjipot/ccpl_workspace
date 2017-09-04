/* @UNIVESRE.COM_20161219_HYE
 * Observer.h: 观察者模式, 定义对象间的一对多依赖关系, 
 * 当一个对象状态发生改变时, 所有依赖它的对象都得到通知
 * 并被自动更新. */

#ifndef ____Observer__
#define ____Observer__

#include <stdio.h>

class Subject;          //class declaration(not define);

class Observer{         //abstract class;
public:
    virtual ~Observer();
    virtual void Update(Subject* theChangedSubject) = 0;    //pure virtual function;
protected:
    Observer();
};





#endif /* defined(____Observer__) */
