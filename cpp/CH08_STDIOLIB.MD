##CH8: 标准IO库 STD_IO_LIBRARY
CPP标准IO库定义了如何读写内置数据类型的编程接口, 类类型通常使用标准IO为内置类型定义的操作符和规则进行读写. 一些基本的IO库工具为:

* istream/ostream, 提供输入/输出操作的类型, 当然是会用到系统调用;
* cin/cout/cerr, 读入标准输入(istream对象), 写到标准输出/输出标准错误(ostream对象);
* \>>/<<操作符, 类似重定向的功能;
* getline(), 分别读取istream和string类型的引用形参, 从istream对象中读取单词, 写入到string对象中(其实就是读取输入返回成string对象).

个人心得: 要理解IO流类, 可以从其作用范围的角度去思考: 内存数据(sstream), 磁盘文件(fstream), 输入输出设备(iostream)之间数据的流动, 要不然, 为什么内存到内存的数据不叫什么IO流, 却叫内存共享?!

####8.1 面向对象的标准库
CPP标准库使用了继承来定义一组面向对象的类, 因为通过继承, 可以使不同的派生类都可以继承基类的行为(即接口, 或函数), 使得不同的类对象(宽字符, 控制窗口, 磁盘文件, 内存中的字符串)都可以使用>>等操作符.

IO类型在三个独立的头文件中定义(fstream和sstream派生自iostream):

* iostream定义读写控制窗口的类型,
* fstream定义读写已命名文件的类型,
* sstream定义用于读写存储在内存中string对象的类型.

通过IO类型的继承关联, 可以编写一个函数, 同时应用到三种类型的流上: 控制台iostream, 磁盘文件fstream, 字符串流sstream.

<strong>1.国际字符的支持</strong>: 迄今为止, 所有描述的流类(stream class)读写的都由char类型组成的流, 而对于国际字符(单个字节对超出ASCII的编码不够用), CPP标准库定义了wchar_t的类型来支持它. 每个IO头文件都定义了char和wchar_t类型的类和标准IO对象: iostream也定义了基于流的wchar_t的类, fstream也定义了基于文件流的wchar_t, sstream也定义了基于字串流的wchar_t.

<strong>2.IO对象不可复制和赋值</strong>: 出于某些原因, 标准库类型不允许被复制或赋值(详见类和继承), 所以, 也不能放进vector等容器中, 也不能用作形参或返回类型(除非是指针或引用).

####8.2 条件状态
略.

####8.3 输出缓冲区的管理
略.

####8.4 文件的输入和输出
略.

####8.5 字符串流 Stringstream
一句话点明iostream, fstream和sstream是什么: "fstream和sstream共享相同的基类, 但它们没有其他相互关系. 特别是, stringstream对象不能使用open和close函数, 而fstream对象不允许使用str". 直接这么讲例子不就好了嘛! 这些都是IO, 虽然仅是CPP编程中的一段代码而已. 

谨记: stringstream不是string对象, 而是IO对象(流对象, 表明数据的'流'程).

1.stringstream对象的使用: 见源码文件"stringstream.cpp";

2.stringstream提供的转换和格式化: 见源码文件"stringstream.cpp";

####8.6 小结
略.



























