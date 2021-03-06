##CH16: 模板/泛型编程 TEMPLATE/GENERIC
<u>泛型编程</u>: 以<u>独立于任何特定类型</u>的方式<u>编写代码</u>;

泛型程序使用方法: 在程序模板中<u>提供</u>具体程序实例所操作的<u>类型</u>或<u>值</u>, 即某种容器的定义是单一的, 但是这一种容器实例间的区别是<u>所包含的元素类型</u>;

泛型编程的例子: 标准库容器, 迭代器和算法;

<u>模板是泛型编程的基础</u>(本章讲解<u>如何定义</u>自己的模板类和模板函数);

<u>函数模板</u>和<u>类模板</u>: 使能够编写<strong><u>独立于具体类型</u></strong>的泛型函数和泛型类;

关于<u>多态性</u>: 面向对象->运行时多态性, 泛型编程->编译时/参数式多态性.

####16.1 模板定义
模板好像是函数重载: 模板参数不一样, 就是不一样的模板类型;

概念: template关键字, 模板形参表, 模板形参, 模板实参, 实例化, inline函数模板: "template \<typename T> inline T min(const T&, const T&);";

类模板: "template \<class Type> class Queue{ ... };";

注: typename与class含义相同, 原因是typename是作为CPP的组成部分加到CPP中的, 所以, 旧的程序更有可能只使用class关键字.

####16.2 实例化
实例化指, 产生模板特定类型实例的过程(由编译器产生), 如: "Queue\<string> qs;";

####16.3 模板编译模型
当编译器看到<u>模板定义</u>时, 它不立即产生代码; 只有代码中用到模板时(调用模板函数或定义模板类对象), 编译器才产生<u>特定类型</u>的模板实例;

<u>一般情况</u>下, 调用函数时, 编译器只需看到函数的声明; 定义类类型对象时, 类定义需可用, 而成员函数的定义不是必须要存在的; 故, 类定义和函数声明放<u>头文件</u>中, 普通函数和类成员函数的定义放<u>源文件</u>中;                                                                                                          

<u>模板</u>则不同: 要进行实例化, 编译器必须能访问定义模板的源代码, 即, 调用函数模板或类模板的成员函数时, 编译器需要函数定义, 需要那些<u>通常放在源文件中的代码</u>(这和一般情况不同);

标准CPP为<u>编译模板代码</u>提供了两种模型: <u>1.包含编译模型</u>(所有编译器支持), <u>2.分别编译模型</u>(部分编译器支持); 它们相同之处为类定义和函数声明放在头文件中, 而函数定义和成员定义放在源文件中; 不同之处在于编译器怎样使用来自源文件的定义.

####16.4 类模板成员
怎样实现Queue类模板: 略.

####16.5 一个泛型句柄类
实现<u>泛型句柄类</u>(generic handle class), 提供管理使用计数和基础对象的操作: 略.

####16.6 模板特化
<u>模板特化</u>(template specialization)是某类模板的一个或多个形参的实际类型或实际值是指定的; 

为什么需要模板特化: 1.compare函数模板如果用两个"const char *"实参调用模板, 则将比较地址值, 2.特化比通用模板实例化的函数更有效率.

####16.7 重载与函数模板
有相同名字但形参数目或类型不同的多个函数模板, 或与函数模板有相同名字的普通函数, 都是<u>函数模板重载</u>;

声明一组<u>重载的函数模板</u>不保证可以成功调用他们, 因为重载的函数模板可能有二义性.

####16.8 小结
<u>模板</u>(记牢: 只有函数模板和类模板)是CPP与众不同的特性, 是标准库的基础;

<u>函数模板</u>是建立算法库的基础, <u>类模板</u>是建立标准库容器和迭代器类型的基础;

<u>编译模板</u>需要编程环境的支持, 语言为实例化模板定义了两个主要策略: <u>1.包含模型</u>(编译器必须看到所有模板的定义), <u>2.分别编译模型</u>(编译器会为程序员跟踪相关模板的定义);

<u>显式模板实参</u>会固定一个或多个模板形参的类型或值, 使得程序员能够设计无须从对应的实参推断模板类型的函数, 也能使程序员能够对实参进行转换(如无法确定返回值进而对形参进行显式类型强转的例子: "sum(static_cast\<int>(s), i);");

<u>模板特化</u>定义了模板的不同版本, 将一个或多个形参绑定到特定的类型或特定值上; 对于默认模板不适用的类型, 特化非常有用.

######P.S.
以上所有概念, 都是CPP语言的特点之一, 其它语言可能没有或不设计成如此, 但这些概念, 终归是宇宙的一部分.

