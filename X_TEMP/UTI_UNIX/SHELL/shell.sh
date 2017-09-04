#!/bin/sh

# echo "Hello, World!"
# # exit 0
# echo "Hello, World! Again!"

# var="Hello"	#No blank permitted around "="
# echo "var is $var"
# # read var
# echo "Your input is $var"

# num=2
# echo "This is ${num}nd"


# Some default variables in shell;
# 
# echo "num of args is:$#"
# echo "value of all args is:$*"
# echo "value of arg0 is:$0"
# echo "value of arg1 is:$1"
# echo "value of arg2 is:$2"
# echo "value of arg3 is:$3"

# if statement:;
# 
# var1=1
# var2=2
# if [ $var1 -eq $var2 ];then
# 	echo "var1 equal to var2"
# else
# 	echo "var1 not equal to var2"
# fi

# for语句: for in do done;
# for day in Sun Mon Tue Wed Thu Fri Sat
# do
# 	echo $day
# done
# 
# for语句: echo当前文件夹下的所有文件;
# for file in *
# do
# 	echo $file
# done
# 
# for loop: generate ".o" file, terminal command included;
# for file in $(ls *.c)
# do
# 	gcc $file -c
# done

# while/until statement: while/until do done;
# echo "Enter password"
# read password
# while [ $password != 123456 ]; do
# 	echo "Pwd not right, try again."
# 	read password
# done
# echo "Password right."

# case statement: case in pattern statement;
# echo "Is it morning?!"
# read answer
# case $answer in
# 	Yes | YES | yes | y) echo "Good Morning!";;
# 	No  | NO  | no  | n) echo "Best Wishes!";;
# 	*) echo "Answer Not In Right Format!";;
# esac

# break/continue: left for blank;

# functions in shell: function_name(){#statements};
# fun_var="Global Variable"
# foo()
# {
# 	local fun_var="Local Variable"
# 	echo $fun_var
# }
# echo "Script Starting.."
# foo
# echo "Script Ended."

# Function parameter & return value;
# 
# foo(){
# 	echo "Is your name $*"
# 	read answer
# 	case "$answer" in
# 		y|yes) return 1;;
# 		n|no)  return 0;;
# 	esac
# }
# foo $1 # 传入第一个参数给foo()中的"$*"
# if [ $? -eq 1 ]
# then
# 	echo "Hello $1"
# else
# 	echo "Never Mind"
# fi








