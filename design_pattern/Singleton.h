/* @UNIVESRE.COM_20161219_HYe
 * Singleton.h
 * 单件模式: 保证该类只有一个实例, 并且提供一个访问它的全局访问点. */

class Singleton{
public:
    static Singleton* Instance();   //任何地方都可访问;
protected:
    Singleton();                    //类体系内可访问: 试图直接实例化Singleton将得到一个编译时的错误, 结合Instance(), 就保证了仅有一个实例可以被创建(_instance指针);
private:
    static Singleton* _instance;    //本类可访问: Singleton()或Instance();
};