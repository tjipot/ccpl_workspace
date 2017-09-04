#Shell笔记
######@SINCE NOV22, 2016 @HYE
通俗理解shell: 什么是核? 是系统内核, shell作为核的壳, 提供了界面, 让用户输入命令, 它交付这些命令到系统内核或系统库, 执行这些命令(如, 内核提供的函数接口);

>联想: 词法分析器. 编译器中的词法分析器也是一个软件, 也是建立在计算机(软件)体系上的一个软件, 一个软件接套一个软件, 像套娃吗?! 还是像一套精密的齿轮系统?!

正式上讲, shell是一种命令解析器(注意, 它与以前程序员用的终端的关联度极大(tty: TeleTYpewriter)), 它将用户输入的命令转换为计算机能够运行的相应的程序.

shell是运行其他应用程序的接口(常说的从命令行运行程序就是这么来的), 用户登录系统后, 可以向shell程序键入命令(用户登录时一般会启动一个终端, shell程序运行在终端中), 由终端处理已输入的命令的系统调用或库调用, 或将系统的控制权(p.s.学术辞藻)交由用户输入的要执行的程序.

Shell的用户输入通常来自于终端(交互式shell), 有时则来自于文件(shell脚本), 这两种方式其实都在调用shell的内在解释器模块(要不shell程序语句怎么执行).

shell和编程语言的编译器类似, 都是"看不见"却在后台发挥作用的东西.


##1.Shell基本
###1.1 Shell种类
这一段是有关历史的叙述了: 70/80年代的程序员根据各自喜好和理念, 做出了不同的shell, 如: Bourne shell("/bin/sh"), Bourne-again shell("/bin/bash"), C shell("/bin/csh"), Korn shell("/bin/ksh");
###1.2 Shell脚本
两种方法可以去使用shell(依我看, 说成感受shell更有人情味):

1.通过终端输入命令交由shell解释执行并返回结果,

2.从终端执行".sh"shell文件(告诉终端去把整个文件里面的代码执行了);


##2.Shell语法

shell脚本的第一行必须是如下格式: "#!/bin/sh", 符号#!用来指定该脚本的解析程序, 一般是"/bin/sh"; 当编辑好脚本后, 如果要执行这个脚本, 还必须使其具有可执行权限(一种Unix系统的概念, 一般地, ".sh"文本文件创建后, 默认是无可执行权限的, 即无"x"): chmod +x filename;

###2.1 注释
用#号, 表示注释一整行.

###2.2 退出码
退出指令为: exit, shell解释器在执行到exit所在这一行后, 就会退出剩余shell脚本的执行(脚本也是按行执行的), exit 0表示退出, 状态为成功(shell规定0表示成功); 

###2.3 变量/默认变量
####2.3.1 变量
变量由字符串组成, 不需要预先声明, 赋值不需要"$"号, 引用需要在之前加"$";
<pre><code>￼var="Hello" #"="号两边不能有空格;￼echo "var is: $var"</code></pre>

####2.3.1默认变量

$*: 所有命令行参数值, 在各个参数值之间留有空格;

$#: 传入脚本的命令行参数个数;

$0: 命令本身("./文件名.sh");

$1: 第一个命令行参数;$2:第二个命令行参数;
<pre><code>￼#!/bin/sh￼echo "Number of args is:$#"￼echo "Value of all args is: $*"￼echo "Value of arg0 is: $0"￼echo "Value of arg1 is: $1"￼echo "value of arg2 is: $2"
</code></pre>

以上仅部分参数.

###2.4流程控制语句: if, for, while/until, case, break/continue

####2.4.1 if 语句
<pre><code>var1=1
var2=2
if [ $var1 -eq $var2 ];then
	echo "var1 equal to var2"
else
	echo "var1 not equal to var2"
fi</code></pre>

####2.4.2 for 语句
<pre><code>#for语句: for in do done;
for day in Sun Mon Tue Wed Thu Fri Sat
do
	echo $day
done

#for语句: echo当前文件夹下的所有文件;
for file in *
do
	echo $file
done

#for loop: generate ".o" file, terminal command included;
for file in $(ls *.c)
do
	gcc $file -c
done
</code></pre>

####2.4.3 while/until 语句

<pre><code>#while/until statement: while/until do done;
echo "Enter password"
read password
while [ $password != 123456 ]; do
	echo "Pwd not right, try again."
	read password
done
echo "Password right."
</code></pre>


####2.4.4 case 语句

<pre><code>case statement: case in pattern statement;
echo "Is it morning?!"
read answer
case $answer in
	Yes | YES | yes | y) echo "Good Morning!";;
	No  | NO  | no  | n) echo "Best Wishes!";;
	*) echo "Answer Not In Right Format!";;
esac
</code></pre>

####2.4.5 break/continue 语句

<pre><code>#break/continue: left for blank;
</code></pre>

###2.5 函数/参数/返回值/参数扩展
####2.5.1 函数
<pre><code>#functions in shell: function_name(){#statements};
fun_var="Global Variable"
foo()
{
	local fun_var="Local Variable"
	echo $fun_var
}
echo "Script Starting.."
foo
echo "Script Ended."
</code></pre>

####2.5.2 函数参数/返回值

<pre><code>#Function parameter & return value;
foo(){
	echo "Is your name $*"
	read answer
	case "$answer" in
		y|yes) return 1;;
		n|no)  return 0;;
	esac
}
foo $1				#传入第一个参数给foo()中的"$*"
if [ $? -eq 1 ] 	#"$?"表示上一个命令的返回值
then
	echo "Hello $1"
else
	echo "Never Mind"
fi</code></pre>


####2.5.3 参数扩展

参数扩展可以理解为参数格式化替换, 常用的参数扩展有:<table>
	<tr>
		<td>操作符</td><td>操作示例</td><td>作用解释</td></tr>
	<tr>
		<td>#</td><td>$(#param)</td><td>给出param的长度</td></tr>
	<tr>
		<td>:-</td><td>$(param:-default)</td><td>如果param为空, 则把它替换成default的值</td></tr>
	<tr>
		<td>#</td><td>$(param#word)</td><td>从param的<strong>头部</strong>开始删除与word匹配的<strong>最短部分</strong>, 返回剩余部分</td></tr>
	<tr>
		<td>##</td><td>$(param##word)</td><td>从param的<strong>头部</strong>开始删除与word匹配的<strong>最长部分</strong>, 返回剩余部分</td></tr>
	<tr>
		<td>%</td><td>$(param%word)</td><td>从param的<strong>尾部</strong>开始删除与word匹配的<strong>最短部分</strong>, 返回剩余部分</td></tr>
	<tr>
		<td>%%</td><td>$(param%%word)</td><td>从param的<strong>尾部</strong>开始删除与word匹配的<strong>最长部分</strong>, 返回剩余部分</td></tr>
</table><pre><code>￼unset foo￼￼echo ${foo:-default}	# default

foo=SHELL￼￼echo ${foo:-default}	# SHELL￼
foo=/usr/test/test/hello￼￼echo ${foo#*test/}	# test/hello￼￼echo ${foo##*test/}	# hello

foo=/usr/hello/test/test￼￼echo ${foo%/test*}	# /usr/hello/test￼￼echo ${foo%%/test*}	# /usr/hello
</code></pre>
    

