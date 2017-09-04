/* @UNIVESRE.COM @NOV10,2016 @HYE @Q91FILE
 * Demonstrates the mechanism of self-defined String class, including the implementation
 * of String's constructor, destructor, copy constructor and assignment operator overload.
 * 需要指出的是, 在源码解析的过程中, CPP编译器如果遇到了上述情形, 如对一个String对象进行"="号赋值, 那
 * 么, 编译器会自动调用自定义的赋值操作符重载函数(否则就用默认的), 这不是法律规则, 这是CPP的规则和工作
 * 机理. 
 */
#include <iostream>
using namespace std;

class String{
private:
	char *m_str;//String对象的数据成员: 首字符的起始地址;
	int   m_len;  //String对象的长度(即占用字节数, 应包含'\0'作为字符串终止符);
public:
	String(const char *str = NULL);	//String 构造函数;
	String(const String &otherStr); //String 复制构造函数;
	String& operator=(const String& otherStr);	//String 赋值操作符重载函数;
	~String();	//String 析构函数
	friend ostream& operator<<(ostream& stream, const String& str);	//String 输出操作符重载友元函数;
	char& operator[](unsigned int index){	//String 下标操作符重载函数, 用于左值;
		static char c = '\0';
		if(index >= m_len){
			cout << "Index Out Of Range!" << endl;
			return c;
		}else{
			cout << "Not const" << endl;
			return m_str[index];
		}
	}
	const char& operator[](unsigned int index) const{	//String 下标操作符重载函数, 用于右值;
		static char c = '\0';
		if(index > m_len){
			cout << "Index Out Of Range!" << endl;
		}else{
			cout << "In const" << endl;
			return m_str[index];
		}
	}
	void display(){	//sizeof()和strlen(m_str)是字符串个数, 而m_len则是占用字节数(包括'\0');
		cout << m_str << " sizeof(m_str): " << strlen(m_str) << ", m_len: " << m_len << endl;
	}
};

/* Outer Of Class */
String::String(const char *str){ //类内声明, 类外定义: constructor;
	if(NULL == str){ //没有内容的字符串也有占用空间, 占用空间为1, 内容为终止符"\0";
		m_len = 1;
		m_str = new char[m_len];
		*m_str = '\0';
	}else{
		m_len = strlen(str) + 1; //strlen为字符串的个数, 不包含"\0";
		m_str = new char[m_len];
		strcpy(m_str, str);
	}
}

String::String(const String &otherStr){ //类内声明, 类外定义: copy constructor;
	m_len = otherStr.m_len;
	strcpy(m_str, otherStr.m_str);
}

String& String::operator=(const String& otherStr){ //类内声明, 类外定义: assignment overload;
	if(m_str != otherStr.m_str){// s1 = s1
		delete []m_str; // s1 = s1
		m_str = NULL;
		// m_str = new char[strlen(otherString.m_str)+1];
		m_len = otherStr.m_len;
		strcpy(m_str, otherStr.m_str);
	}
	return *this; //返回String&, "&"代表对象实体, 而不是地址值;
}

String::~String(){ //类内声明, 类外定义: destructor;
	delete []m_str;
	m_str = NULL;
}

/* Helper Function */
char func(const String& str){
	char c = str[6]; //字符串结束符是8个0(0000 0000), 并且不是能显示的字符(即不是普通意义上的能看得见的字符)
	return c;
}

int main(void){

	String s1("Hello!");
	// s1.display();
	String s2("Bad");

	char a = s1[1];
	// cout << "char a: '" << a << "', s1[6]: " << s1[6] << endl;
	// s1[0] = s2[1];
	// s1[0] = 'a';
	cout << "s1[0] " << s1[0] << endl;
	// cout << func(s1) << endl;

	return 0;
}