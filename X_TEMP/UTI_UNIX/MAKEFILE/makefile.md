#MAKEFILE笔记
######@Nov 23, 2016 @HYE

##Makefile的存在逻辑
程序员写的代码并不是程序, 是源代码, 而源代码要编译过之后, 才是可运行的程序. 对于大型的项目来说, 仅在改动一个源码文件(可能是".h"文件, 也可能是".c"文件)后就去编译整个项目, 是划不来的. 为了解决这些"不合人情"的现状, make工具就有了存在的必要性了.

通过在makefile文件(make工具必需的文件)中制定编译的规则, make工具会知道如何编译一个工程, 如何链接文件, 如何生成我们想要的文件.

makefile文件一般放在与项目的源文件相同的目录中.

##Makefile示例
makefile文件由一系列规则组成, 每个规则分成三部分: `目标, 依赖, 命令`.

如下示例:
<pre><code># 目标:依赖1, ..., 依赖n
	# 命令
target:main.o arrayUtil.o base64.o
	gcc main.o arrayUtil.o base64.o -o target

main.o:main.c arrayUtil.h base64.h common.h
	gcc main.c -c -o main.o
	
arrayUtil.o:arrayUtil.c arrayUtil.h
	gcc arrayUtil.c -c -o arrayUtil.o
	
base64.o:base64.c base64.h
	gcc base64.c -c -o base64.o
</code></pre>

###最终目标
makefile中只有一个最终目标, 其它目标都是这个目标的依赖子目标, 一般地, 第一条规则中的目标为最终目标, 这个可以通过`make 具体目标名`来改变, 如`make target`将把`target`作为最终目标.

默认地, make命令会在当前目录下寻找名字为makefile或Makefile的make规则文件, 也可用如下格式来指定编译规则的文件: `make -f 文件名`

###伪目标
只有`目标, 命令`, 没有`依赖`的规则的目标是一个伪目标(phony target), 常用的clean目标就是一个伪目标(清除编译生成的中间文件):
<pre><code>clean:
	rm *.o -rf
</code></pre> 


##Makefile变量

使用自定义变量, 以提高效率. 下例:
<pre><code>OBJECTS=main.o  arrayUtil.o  base64.o
TARGET=tatget
$(TARGET):$(OBJECTS)
	gcc $(OBJECTS) -o $(TARGET)
</code></pre>
即为:
<pre><code>OBJECTS=main.o arrayUtil.o base64.o
TARGET=tatget
target:main.o arrayUtil.o base64.o
	gcc main.o arrayUtil.o base64.o -o target
</code></pre>

以上是自定义变量的示例, makefile中, 还有系统默认的自动化变量(同shell解释器一样, 都有默认变量; 其实, 这些都是make工具的发明者规定的, 他们把这些规则编定进了make工具的解释器中去了, 所以, 程序员是制定世界规则的人吗?! 哈哈), 如: `$@`代表目标, `$^`代表所有的依赖文件, `$<`代表第一个依赖文件. 因此, 上一个例子更可以简写为:

<pre><code>$(TARGET):$(OBJECTS)
	gcc   $^    -o  $@
#   gcc 所有依赖 -o  目标
</code></pre>

###Makefile Tips
makefile文件中, 井号"#"之后的行内容被注释了;

在命令前使用符号"@", 会取消命令的回显(不会输出显示了).


_一点心得: 变量的使节省了重复的操作, 虽然一时看着不习惯, 但适应之后, 效率会提升的. 二点心得: 应该感谢上帝的安排(此处上帝不是指基督上帝, 此上帝可以理解成变量X, 泛指宇宙本身中人类未发现的东西, 而基督上帝, 本身也属于未发现东西之列), 让物理/电路特性能够与人类的说不清从何而来的认知结合, 大幅度提升人类的Vision(视界), 这个世界从一堆沙子中来, 又浓缩于一粒沙子中: 程序员的, 一沙一世界._
