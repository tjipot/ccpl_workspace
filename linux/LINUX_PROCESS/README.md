#LINUX_PROCESS_THREAD_SECTION
<strong>不要迷失自己于进程和线程的海洋之中</strong>的前提背景:

* 讲到进程和线程, 绝不能脱离操作系统单独去讲如下的说法: "进程是系统分配资源的最小单位, 线程是CPU调度的最小单位", 这没错, 或是大错特错! 现在的教育方法都是错误了么? 都不能通俗易懂了么?! 

* 计算机的几十年发展历程中, 最早先有进程(那时还没现在的线程概念)的概念, 慢慢地, 为了更高效执行程序的需要(因为OS内部(其实就是内核)为用户创建进程时, 是要执行内核代码的, 也要进行内存的读写操作, 而某些代码的执行却不一定都要消耗那么多CPU等的时间), 操作系统进一步进化, 计算机工作者改善OS逻辑设计, 在进程内部再分化出了线程机制而不是原先的进程机制来执行某些代码(因为执行这些代码并不需要再重新配置一个进程执行所需的所有元素), 故线程的概念出现了; 有了线程概念的明确提出后, 就可以发现原先进程中那个执行流其实也就是现在的线程概念: 一个进程必定包含一个线程.

* 总之, 进程和线程不是独立存在的神秘概念, 它们不能在OS的权限之上来执行, 否则, 就是OS内核BUG了. 以上的所有, 你必须去相信它, 因为它是逻辑, 它不能用眼睛去看见, 它可以被验证, 否则, 你以为你不能感受到引力的存在它就确实不存在了么?! 好了, 开始进程和线程的梳理, Linux万岁, 人类智慧万岁, 抽象万岁, 存在万岁.

##1.进程基本
开门见山: 进程与进程之间的信息的交互(对, 就是这么抽象), 叫<strong><u>进程间通信</u></strong>, 它可以有多种形式, 如下:

* <u>管道(单向)</u>: 进程管道, 有名管道(父子进程间, pipe(int fd[2])), 无名管道(任意进程间, mkfifo创建管道文件, open/read/write, 可能阻塞);
* <u>信号(异步)</u>: 注册信号处理函数, signal(信号编号, 处理函数), sigaction(信号编号, struct sigaction);
* <u>共享内存</u>: 共享同一片内存, 创建或打开(shmget), 映射(标识符->内存地址), 分离(断开连接), 删除(shmctl);
* <u>消息队列(双向)</u>: 邮箱通信, 带类型的收发, 创建或打开(msgget), 发送(msgsnd, 标识符, 消息结构体, 正文长度, flags), 接收(msgrcv), msgctl;
* <u>信号量(互斥与同步)</u>: 分为System V和POSIX的(坑爹的历史演化, 苦了学习的后生):
	* System V: 创建或打开semget, semop(p/v操作), semctl(删除, 赋初值);
	* POSIX: sem_open(创建信号量指针sem_t), sem_wait(p操作, 获取信号量), sem_post(v操作, 释放信号量), sem_close(断开), sem_unlink(删除);

以上5种方式, 你不能理解?! 那是当然, System V和POSIX出来之时, 你都没出生啊小兄弟;

###1.1.进程的背景
1960年代的计算机, 一台机器能跑一个程序就行了, 还谈什么多进程(你不知道你现在的幸福吗)?! 后来, 想跑多进程了, 就需要对不同的进程进行管理(以用好实体计算机). 当然, 一个进程是不能去管别的进程的, 或者, 换个说法, 能管别的进程的进程, 就应该归到操作系统的概念里去啊(我又发现了这个天大的秘密了?! 机灵的我! 这些老师是怎么教书的, 死板如闲鱼!)! 于是, 操作系统就在需求之下发展了起来, 这个看不见的软件的宏大工程就成了我们当下人类先入为主的偏见了(以为操作系统是如此的常见, 以前也必定得有).

###1.2.进程的状态及转换
你要管理进程, 决定让谁去运行, 肯定要有进有出, 有人用CPU就有人等CPU, 于是, 基本的, 进程有三种状态:

* 运行
* 就绪
* 阻塞

更加细分一下, 就有了Linux中进程的七种状态. 当然, 要控制进程, 操作系统就要知道每个进程的状态以便知道如何控制及调度它们. Linux为运行在其中的每个进程(对象)都分配了一个<strong><u>PCB(PROCESS CONTROL BLOCK)</u></strong>数据类型的对象来保存进程的状态. 接下来, 我们看看PCB(PCB其实包含很多内容, 反正我是懒得去记, 只管弄懂). 具体地, Linux系统将PCB存放于<strong>task_struct</strong>的结构体(没错, 就是那个结构体数据类型)中, 这个task_struct包含以下数据:

* 调度数据: 进程状态, 标志, 优先级, 调度策略;
* 时间数据: 创建进程的时间, 用户态运行的时间, 内核态运行的时间等;
* 文件数据: umask掩码, 文件描述符等;
* 内存数据: 进程上下文, 进程标识(进程号);
* 其它数据: 等等.

###1.3.进程控制
进程号, 也就是Linux给该进程PCB的task_struct中的PID赋一个唯一的值, 类型为pid_t, 一个进程的父进程号为PPID, 所在进程组号为PGID.

####1.3.1.PID编程接口

	#include <sys/types.h>
	#include <unistd.h>
	pid_t getpid(void);
	pid_t getppid(pid_t pid);
	pid_t getpgid(pid_t pid);
	
####1.3.2.进程启动(方法1)

在一个程序内部启动一个新进程, 可以用库函数system, 该函数调用/bin/sh来执行command并等待执行结束:

	#include <stdlib.h>
	int system(const char * command);

因为system要启动一个shell, 然后通过shell启动程序, 效率不高, 不推荐使用.

####1.3.3.进程替换(方法2)
进程替换是把当前进程替换为一个新的程序, 使用exec系列函数, 执行exec函数后, 运行中的程序就开始执行由exec指定的新的可执行程序中的代码, PID, PPID与原进程完全一样, 且一般不返回:

	#include <unistd.h>
	int execl(...);
	int execlp(...);
	int execle(...);
	int execv(...);
	int execvp(...);
	int execve(...);//只有这个函数是系统调用(内核提供接口), 其它都是通过它封装的库函数;

####1.3.4.进程复制: fork
以上二方法创建进程都有限制, 用复制进程的方式, 可以在程序中创建一个完全分离的进程, 即fork(系统调用); fork接口复制当前进程, 在进程表中创建一个新的表项, 新进程有自己的数据空间, 环境和文件描述符, 执行的代码也相同, 两个进程几乎相同了;
	
	#include <sys/types.h>
	#include <unistd.h>
	pid_t fork(void); //新进程(子进程)从fork之后的代码开始执行, 子进程返回0, 父进程返回子进程ID;
	
fork得到的子进程是父进程的复制品, 它从父进程继承了整个进程的 地址空间(进程上下文, 进程堆栈, 打开的文件􏰀述符, 信号控制设定, 进程优先级, 进程组号等), 子进程所独有的只有它的进程号, 计时器等, 使用fork代价很大.

使用fork时, 子进程对变量所做的改变并不影响父进程中该变量的值, 因为父子进程各自拥有自己的地址空间.

####1.3.5.进程复制: vfork
在fork之后系统是先执行父进程还是先执行子进程是不确定的, 这取决于内核调度算法. 如果要父子进程之间相互同步, 则要求某种形式的进程间通信, 或使用vfork.

	#include <sys/types.h>
	#include <unistd.h>
	pid_t vfork(void);

系统保证vfork之后让子进程先执行, 且在子进程调用exec或exit之后, 父进程才被调度运行;

在子进程中调用exec或exit之前, 子进程先在父进程的地址空间中运行, 在exec之后子进程才会有自己的进程空间.

####1.3.6.进程挂起
使进程在一定的时间内没有任何动作, 直到指定的时间过去了, 或收到信号了才解除挂起:

	#include <unistd.h>
	unsigned int sleep(unsigned int sec);

注意, 在指定挂起的时长到了之后, 被挂起的进程并不会立即被执行, 系统只是将之切换到就绪态.

####1.3.7.进程等待
进程的等待, 也算是进程间的一种同步, 如果想要父进程等待子进程结束之后再结束, 可以用wait和waitpid:

	#include <sys/types.h>
	#include <sys/wait.h>
	pid_t wait(int * status);
	pid_t waitpid(pid_t pid, int * status, int options);
	
####1.3.8.进程退出
在Linux中, exit为库函数, 而_exit为系统函数, 调用了它俩, 进程就会结束运行:

	#include <stdlib.h>
	void exit(int value);
	#include <unistd.h>
	void _exit(int value);

如果想要在退出时做点什么, 可以用atexit注册退出处理函数:

	#include <stdlib.h>
	int atexit(void (* function)(void));

###1.4.僵尸进程
子进程已经结束运行, 但仍然存在于系统中, 因为子进程的退出码还会保存在PCB中, 以备父进程的wait调用, 这时的子进程成为僵尸进程(或死进程).

僵尸进程占用系统资源, 而不发挥什么作用, 不好.

###1.5.孤儿进程
Orphan Process, 一进程的父进程运行结束了, 但其还未运行结束.

###1.6.守护进程
Daemon Process, 一种特殊的孤儿进程, 脱离于终端在后台运行.

<br/>
<br/>
<br/>

##2.线程基本
线程是进程内部的一条执行线路, 可以对应为代码中的某个函数; 进程可以同时运行多个线程, 相比于多进程形式的并发操作, 多线程有更高效率; 对CPU来说, CPU总是无时不刻地在执行一些代码(哪怕是idle的代码), 这些代码都可以被视为线程, 只不过, 是哪一个进程的线程?!(归谁管?! 我真机智, 居然发现这个重大秘密)

* <u>进程创建</u>的开销: 1.新的内存空间, 2.一些数据表, 维护代码段, 数据段, 堆栈端;
* <u>进程切换</u>的开销: 保存当前进程的CPU环境个, 载入新进程的CPU环境;

* <u>线程创建</u>的开销: 程序计数器, 一组寄存器和栈的值要处理; 进程地址空间(如代码,全局变量,描述符,信号处理函数)是<u>共享</u>的, 不需要通过IPC系统调用来实现通信;
* <u>线程切换</u>的开销: 操作少量寄存器的内存(不需要切换整个进程的环境);

进程的<u>内存结构</u>(自低地址向高地址): 代码区, 数据区, BSS区, 堆区, 栈(栈A(线程A), 栈B(线程B));

(注: BSS段, 即Block Started by Symbol, 是未初始化的数据区(段), 存放程序中的全局变量和静态变量, 可用"size a.out"查看段大小)

###2.1.编程操作

####2.1.1.线程号
思路: OS要管理和调度线程, 当然要某种东西来标记线程, 在Linux中, 这东西就是pthread_t, 即线程号(理解为POSIX的thread type, 线程号只在某个进程中是唯一的); 需注意, linux可创建的线程数是有限的, 而且线程栈的空间也是有限的;

####2.1.2.编程接口
Linux下的多线程程序, 需头文件<pthread.h>, 链接时要用到库"libpthread.a/-lpthread";

* 线程创建: "int pthread_create(pthread_t \*thread, const pthread_attr_t \*attr, void \*(\*start_routine)(void \*), void \*arg);";
* 线程阻塞: 在主线程中, 使主线程等待子线程: "int pthread_join(pthread_t thread, void **retval);";
* 线程分离: 不想让主进程阻塞等待, 就detach一个线程, 使成为一个独立线程: "int pthread_detach(pthread_t thread);";
* 线程退出: 使调用线程退出: "void pthread_exit(void *retval);", 参数不要指向局部变量;
* 线程取消: 取消一个正在执行的线程, 只会发送信号给目标线程, 并不会等待目标线程执行完毕才返回: int pthread_cancel(pthread_t thread)";

	一个线程的取消行为可以有三点参考: 1.线程的取消状态, 2.线程的取消类型, 3.线程的取消点;
	* 线程的取消状态默认是可被取消的, 可通过```int pthread_setcancelstate(int state, int *old_state)```函数设置;
	* 如果线程可取消, 就进入第二层次的控制(取消类型): ```int pthread_setcanceltype(int type, int *oldtype)```, 决定是立即取消还是到取消点再取消;
	* 默认取消类型是到取消点再取消的(有一系列的取消点函数的), pthread_testcancel可以手动设置取消点: ```void pthread_testcancel(void)```;

* 线程退出清理(和进程类似): 线程退出时要调用的函数, 清理函数存放在栈中, 执行顺序和注册顺序相反(先进后出, 需配对使用):
	* ```void pthread_cleanup_push(void(*routine)(void*), void *arg)```, 注册清理函数(压栈);
	* ```void pthread_cleanup_pop(int execute)```, 删除清理函数(出栈);
* 线程属性初始化: 用于设置在pthread_create时传入的属性变量, ```int pthread_attr_init(pthread_attr_t *attr)```(具体使用, 请查阅资料);
* 线程属性变量清理: 清理和回收线程属性变量, 回收之后, 除非重新被初始化, 否则被再次使用: ```int pthread_attr_destroy(pthread_attr_t *attr)```;

###2.2.线程间通信: 信号量
POSIX线程间通信接口进行线程间同步: 一个线程在进入临界代码时先独占信号量, 使用完后释放信号量(线程/进程都如此); 接口有如: ```sem_init, sem_wait, sem_post, sem_destory```;

###2.3.线程间通信: 互斥量
互斥量也可称做互斥锁(mutex), 用于保证程序对某些数据的互斥访问, 使用场景与二值信号量类似; 可以把互斥锁理解为计算机概念中的一种逻辑锁, 有两种状态: 上锁和解锁; 使用时, 进入临界代码区前, 锁住一个互斥锁变量, 退出临界代码区时, 解开锁; 这又是一个抽象概念, 它实质上是POSIX标准下的一种变量(由POSIX提供API);

<strong>2.3.1.编程接口</strong>

* 静态分配互斥锁: ```pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;```
* 动态分配互斥锁:

	```
	#include <pthread.h>
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, const pthread_mutexattr_t *attr); //属性参数一般为NULL(默认属性)
	```
默认状态下, 互斥锁变量是在解锁状态的;

* 销毁互斥锁: 在不需要使用互斥锁时, 要销毁互斥锁, 其实就是调用POSIX协议提供的API, 清理互斥锁变量, 类似指针的清理;
	
	```
	int pthread_mutex_destroy(pthread_mutex_t *mutex);
	```
* 上锁互斥锁(阻塞): 若该互斥锁已经上锁, 则该线程阻塞到解锁(然而, 要区分此时OS并不会被阻塞住, OS有一套自己的机制, 如分时, 来破此局);
	
	```
	int pthread_mutex_lock(pthread_mutex_t *mutex);
	```
	
* 上锁互斥锁(非阻塞): 若该互斥锁已上锁, 函数立即返回;

	```
	int pthread_mutex_trylock(pthread_mutex_t *mutex);
	```
* 解锁互斥锁: 返回值: 成功0/失败!0;
	
	```
	int pthread_mutex_unlock(pthread_mutex_t * mutex);
	```

###2.4.线程的条件变量
对于某个共享数据, 如果有以下情形: 程序代码正在等待这个共享数据的某个期望条件出现, 在不停地上锁和解锁检测期望条件是否出现了.., 那么应该用一种新的办法来解决这个场景了, 因为人为地规定间隔一定时间(如1秒钟)去检测期望条件并不是那么合理的.

POSIX```条件变量```可以让正在等待期望条件的线程进入睡眠状态, 而等期望条件出现了, 去唤醒该线程(如同很多个其它情形一样, 这个机制也是OS提供的功能之一, 而不是这个条件变量本身的功能, 撇开爱情谈论婚嫁不好, 这里补充强调一下);

<strong>2.4.1.编程接口</strong>

* ```静态初始化```条件变量: ```pthread_cond_t cond = PTHREAD_COND_INITIALIZER```;

* ```动态初始化```条件变量: ```int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr)```;


* ```销毁```条件变量: ```int pthread_cond_destory(pthread_cond_t *cond)```;

* ```条件变量和互斥锁关联```: 把锁住的互斥量传给函数, 函数把线程放到等待条件的线程列表上, 对互斥量解锁, 然后线程进入睡眠; 当条件发生后, 函数返回, 同时将互斥量再次锁住(OS提供的功能);
	
	```
	int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
	```
* 条件变量的```信号发送```: 当条件满足是, 需要发送信号并唤醒至少一个相关线程, 对应的```pthread_cond_wait()```将失效:
	```
	int pthread_cond_signal(pthread_cond_t *cond)
	```

* 条件变量的```信号广播```: 给所有满足等待条件的线程发送信号: ```int pthread_cond_broadcast(pthread_cond_t *cond)```;


















