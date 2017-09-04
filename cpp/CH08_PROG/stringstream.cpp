/* @UNIVESRE.COM_20161213_HYe
 * Demonstrates the using of stringstream of CPP.
 * 个人心得: 感觉stringstream对象和string对象没啥区别, 
 * 除了: 是"<<"和">>"操作符的操作对象, 而string类不能这
 * 样, 这点足以说明一个是流类, 一个是内容类, 这足够了. */

#include <iostream>
#include <sstream>
using namespace std;

int main(void){
    
    /* stringstream对象的使用 */
    string line, word;              //Will hold a line and word from input, respectively;
    while(getline(cin, line)){      //Read a line from cin(the standard input) and do per-line processing;
        istringstream stream(line); //Bind line to stream of istringstream type, line is already a string in memory;
        while(stream >> word){      //Read a word from stream: stream->string;
            cout << "Read: " << word << endl;
            break;
        }
        break;
    }
    
    /* stringstream提供的转换和格式化 */
    //Part1: convertion of int to int-string(string of int-like);
    int val1 = 512, val2 = 1024;
    ostringstream format_message;                           //Outstream of string: using operator "<<";
    format_message  << "val1: " << val1 << "\n"
                    << "val2: " << val2 << "\n";            //Convertion happens automatically;
    cout << format_message.str();                           //"val1: 512\nval2: 1024";
    //Part2: convertion of int-string to int;
    istringstream input_istring(format_message.str());      //Instream of string: using operator ">>";
    string dump;
    int new_val1 = 0, new_val2 = 0;
    input_istring >> dump >> new_val1 >> dump >> new_val2;  //Two dumps here, the second readin value "val2" will overwrite the first readin value "val1";
    cout << dump << " " << new_val1 << " "
         << dump << " " << new_val2 << endl;                //"val2: 512 val2: 1024";
    
    return 0;
}