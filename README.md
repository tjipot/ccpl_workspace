# ccpl_workspace

#C_CPP_LINUX
孜孜不倦: 为了开发一个新的操作系统, 有了C, 然后有了UNIX; 为了使C有OOP的特性, 有了CPP: 这个世界, 千丝万缕, 这就是文化.

Talk is cheap, show me the code. --Linus

##LINUX_PART
依功能方面的考量, 这Linux笔记主要分两部分: 本地和网络, 分别代表本地系统和网络通信两块.

* 本地部分: 分文件, 和进程(包括进程间通信和线程);
* 网络部分: 主要是TCP和UDP的通信, 通过这两个概念的代码, 一窥网络编程的实现.


###FILE OPERATION
####\<sys/stat.h>
File Statues: a lib about file status under System V protocal, often used by command `ls -al`;

####\<sys/types.h>
Unix/Linux系统的基本系统数据类型的头文件, 含有`size_t, time_t, pid_t`等类型, 是linux编程中经常用到的头文件.




###PROCESS_SECTION
注: 进程PROCESS和线程THREAD的部分.



####TCP网络编程

#####I/O复用
I/O复用的背景意义: 不能让计算机等待一个用户输入的同时, 也把其它的输入(如Socket输入), 也屏蔽了.

Linux的5种I/O模式: 阻塞式I/O, 非阻塞式I/O, I/O复用(select和poll), 信号驱动I/O(SIGIO), 异步I/O(POSIX的aio_系列函数).


I/O复用场景: 
* 1.当需要处理多个描述符(如交互输入和网络套接字)时, 必须I/O复用;
* 2.要同时处理套接字监听和处理已连接套接字时;
* 3.一个服务器既要处理TCP, 又要处理UDP时;

#####select函数
select函数告诉内核等待一个集合中的某个或多个事件发生或某段时间后唤醒该进程;

<pre><code>int select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds, struct timeval *restrict timeout); //参数: 最大fd+1, 是否可读的fd集合, 是否可写的fd集合, 是否发生异常的fd集合, 等待时间(为0时称为轮询(polling));</code></pre>

#####shutdown函数
shutdown函数可以只关闭一个方向上的数据连接功能(防止数据未收到就关闭).
<pre><code>int shutdown(int socket, int how); //shut down part of a full-duplex connection, sys/socket.h
</code></pre>




##C_CPP_语言

####CPP: 必须使用初始化列表进行初始化的数据类型:
1. const成员,
2. 引用成员,
3. 无默认构造函数的内嵌对象成员;

######常用函数解释:
<pre><code>char * stpcpy(char *dst, const char *src); //string.h</code></pre>
<pre><code>void * memcpy(void *restrict dst, const void *restrict src, size_t n); //string.h</code></pre>

######"."和"->"的区别:
"->"使用在指针的后面, 指向指针所指实体实体对象的内部对象;
"."使用在实体对象后面, 指向实体对象的内部对象;

######restrict关键字:
该关键字修饰指针, 用了restrict, 等于告诉编译器该指针修饰的内存对象内容必须由该指针来修改, 其它任何指针或变量不能参与修改(编译器可以以此特性进行优化);

######有关指针:
<pre><code>const char * msg; //msg:string类型, *msg:char类型, &msg:const char ** 类型;</code></pre>



