##CH01: 有关C语言 ABOUT C
忘掉以前C的似懂而懂概念吧, 全面, 踏实, 新C(SINCE_DEC082016).

####1.1 C的起源
1972年, 贝尔实验室, Dennis Ritch和Ken Thompson(B语言发明者), 为了开发UNIX时, 设计了C.

####1.2 选择C的理由
我认为这三点比较重点:
1.具有通常是汇编语言才有的微调控制能力;
2.可移植性;
3.面向程序员, 及C标准库.

####1.3 C的应用范围
嵌入式系统, UNIX, 计算机游戏, etc.

####1.4 计算机能做什么
围绕CPU来计算: 内存(RAM), 硬盘(用久存储), 及外围设备(如键盘, 触屏等提供人机交互的东西).

####1.5 高级计算机语言和编译器
C是编译型语言, 编译器负责转换文本源码到机器指令, 这中间, 包含预编译(区别于编译), 编译(源码至机器码), 链接(和库函数链接上, 还要加startup code).

####1.6 语言标准
最初是"The C Programming Language(第一版)", 后来是C89(ANSI C或ISO C), 再是C99(C9X), 再是C11(C1X).

####1.7 使用C的7步骤
注意小程序和大项目的一点区别:

1.定义程序目标, 2.设计程序, 3.编写代码, 4.编译, 5.运行, 6.测试和调试, 7.维护和修改代码.

####1.8 编程机制
一步走: 编译;

二步走: 编译+链接;

三步走: 预编译+编译+链接;

(第二步中, 编译生成中间代码(如目标代码的形式, 且只包含自己写的源码的目标代码), 链接把<u>中间代码</u>和<u>其它代码</u>(如库函数代码)合并, 并添加<u>启动代码</u>后生成可执行文件, 整个模式就是模块化管理的概念)

<strong>关于编译器</strong>:

cc编译器没有跟上标准的发展脚步(退出了历史舞台), 其它两种主流是: GNU编译器集合和LLVM项目; GNU编译器集合也称GCC, 其中包含GCC C编译器, 有系统使用cc作为gcc的别名; LLVM项目(是与编译器相关的开源软件集合)也是cc的另一个替代品, 它的C编译器是Clang, 也有系统用cc作为clang的别名.

(p.s. 所有的程序老虎都是虚老虎, 它们都脱离不了编译器的基础, 搞晕你的是编译器的版本, 编个小程序也提供复杂功能的IDE, 等等..)

####1.9 本书的组织结构
略.

####1.10 本书约定
略.

####1.11 小结
C编译器和链接器是一个程序(说成软件的话还是有点浮夸), 记住D&K的范, 早日掌握掌控大型程序的艺术.
