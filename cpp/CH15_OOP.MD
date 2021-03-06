##CH15: 面向对象编程 OOP
继续<u>继承</u>和<u>动态绑定</u>的讨论: <strong><u>继承</u></strong>, <strong><u>动态绑定(多态)</u></strong>, <strong><u>数据抽象(封装)</u></strong>一起, 是OOP的基础; 

<u>继承</u>, 使一个类与其它类相似但又不相同;

<u>动态绑定</u>, 使一个程序能够<u>忽略</u>相似类类型(对象)之间的区别, 使编译器决定在运行时是使用基类的函数还是派生类的函数.

(编写<u>自己的</u>面向对象类型或泛型类型, 需要有对CPP基本原理的充分理解并且很好地掌握怎样定义更<u>基本的类</u>: 现阶段, 只要知道怎么使用得好即可)

####15.1 OOP概述
CPP中, 多态性(polymorphism)仅用于<u>通过继承而相关联的</u>类型的引用或指针.

1.继承: 基类, 派生类, 继承层次, virtual函数(是基类期待派生类重新定义的);

2.动态绑定: 使程序使用继承层次中任意类型的对象, 而无须关心对象的具体类型(无须区分函数是在基类还是派生类中定义的);

####15.2 基类和派生类
略.

#####15.2.1 定义基类
1.基类成员函数
2.访问控制和继承.
#####15.2.2 protected成员
略.

#####15.2.3 派生类
1.派生类的定义
2.派生类和虚函数
3.派生类对象包含基类对象作为子对象
4.派生类中的函数可以使用基类成员
5.用作基类的类必须是已定义的
6.用派生类作基类
7.派生类的声明

#####15.2.4 virtual与其它成员函数
略.

#####15.2.5 公用,私有和受保护继承
略.

#####15.2.6 友元关系和继承
略.

#####15.2.7 继承与静态成员
略.

####15.3 转换与继承
理解了基类类型和派生类类型之间的转换, 就理解了OOP在C++中的工作机制.

可以将<u>派生类对象的引用(或指针)</u>转换为<u>基类子对象的引用(或指针)</u>, 即: 基类引用(或指针) = 派生类引用(或指针), 左值 = 右值; 反之则不行.

还有, 严格地说, 没有从<u>派生类型对象</u>到<u>基类类型对象</u>的直接转换, 只有派生对象(的基类部分)对基类对象进行的初始化或赋值.

####15.4 构造函数与复制控制
前提背景: 每个 派生类对象 都由派生类中定义的非static成员 加上 一个或多个基类子对象 构成, 这一事实, 影响着派生类对象的<u>构造</u>, <u>复制</u>, <u>赋值</u>和<u>撤销</u>; 当构造, 复制, 赋值和撤销派生类型对象时, 也会构造, 复制, 赋值和撤销派生类型对象.

<u>构造函数</u>和<u>复制控制成员</u>(及复制,赋值,撤销)不能继承, 每个类需自己定义它们; 如果类不定义自己的默认构造函数和复制控制成员, 就将使用<u>合成版本</u>.

####15.5 继承情况下的类作用域
每个类都保持着自己的作用域, 在继承的情况下, 派生类的作用域<u>嵌套</u>在基类的作用域中, 即: 派生类作用域的外围是基类作用域; 正是这种类作用域的嵌套层次使派生类成员能够直接访问基类的成员(好像是派生类成员自己的一样).

####15.6 纯虚函数
纯虚函数(pure virtual function)是在函数声明时在形参表后面加上"=0"的函数, 纯虚函数为后代类型提供了可覆盖的接口, 但在这个版本的类中决不会调用, 即用户不能创建Disc_item类型的对象;

含有(或继承)一个或一个以上纯虚函数的类是<u>抽象类(abstract class)</u                                                                                                                                                      >, 此类除了作为其派生类对象的组成部分, 不能创建对象.

####15.7 容器与继承
如果我们希望一个容器保存一些有继承关系的对象(基类对象或派生类对象)怎么办?! 如在multiset中保存基类类型(Item_base)的对象, 那么, 将Bulk_item(Item_base的派生类)放入容器中, 只能保存Bulk_item的基类部分(派生类被"切掉");

如果强制转换类型(基类类型转换为派生类类型), 那么, 这个强转来的派生类对象的派生部分是未初始化的;

唯一可行的好像就是指针了, 但是也需要在使用时管理对象和指针: 要确保容器存在, 被指向的对象也存在; 容器消失, 对象也被释放;

<u>句柄类</u>是一个更好更通用的解决方案.

####15.8 句柄类与继承
15.7节的情况, 是说CPP虽是OOP的, 但在那时却不能用对象, 而只能用指针或引用;

解决上述问题的通用技术是定义<u>包装(cover)</u>类或<u>句柄(handle)</u>类: 句柄类存储和管理基类指针;

用户通过句柄类访问继承层次的操作, 因为句柄类使用指针执行操作, 而<u>虚成员</u>的行为将在运行时根据句柄实际绑定的对象类型而变化.

####15.9 文本查询示例(再谈)
略.

####15.10 小结
<u>继承</u>使新类与基类共享行为但重新定义必要的行为;

<u>动态绑定</u>使程序能够在运行时根据对象的动态类型确定运行<u>函数的哪个版本</u>;

CPP程序定义继承层次接口的<u>句柄类</u>很常见, 句柄类分配并管理指向<u>继承层次中</u>对象的指针, 使用户代码在无须处理指针的情况下获得动态行为(见15.7, 句柄类类似是一个Helper Function).


