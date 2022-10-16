#include "func.hpp"
#include "calculator.hpp"
#include <iostream>
#include <string>
#include <stack>

using namespace std;

string calculator(string str, string unknown[])
{                                         // str为四则表达式
    string::iterator input = str.begin(); // input为输入迭代器，用于读取输入
    stack<char> ope;
    stack<string> num; //创建两个栈，ope用于存放操作符，num用于存放数字

    string value = "";
    while (input != str.end())
    {
        if (*input == '+' || *input == '-' || *input == '*' || *input == '/' || *input == '(' || *input == ')') //检测是否是运算符
        {
            value = "";
            if (*input == '(' || ope.empty())
            {
                ope.push(*input);
            }
            else if (*input == ')')
            {
                while (ope.top() != '(')
                {
                    calculate(ope, num);
                }
                ope.pop();
            }
            else if (priority(ope.top()) >= priority(*input))
            {
                // cout << ope.top () << endl;
                while (ope.top() != '(')
                {
                    calculate(ope, num);
                    if (ope.empty() || priority(ope.top()) < priority(*input))
                    {
                        break;
                    }
                }
                ope.push(*input);
            }
            else
            {
                ope.push(*input);
            }
        }
        else
        {
            if (*input >= '0' && *input <= '9' || *input == '.')
            {
                if (value != "")
                {
                    num.pop();
                }
                value = value + *input;
                // if (num.empty())
                // {
                //     if (!ope.empty())
                //     {
                //         if (ope.top() == '-')
                //         {
                //             value = "-" + value;
                //             ope.pop();
                //         }
                //     }
                // }
                num.push(value);
            }
            else
            {
                string new_in = unknown[*input - 'a'];
                if (value != "")
                {
                    num.pop();
                }
                value = value + new_in;
                num.push(value);
            }
        }
        input++;
    }

    // cout << "begin cal" << endl;
    while (!ope.empty())
    {
        calculate(ope, num);
    }
    // cout << "end cal" << endl;

    // cout << num.top() << endl;
    return num.top();
}

int priority(char ope)
{
    if (ope == '(')
    {
        return 0;
    }
    else if (ope == '+' || ope == '-')
    {
        return 1;
    }
    else if (ope == '*' || ope == '/')
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

void calculate(stack<char> &ope, stack<string> &num)
{
    string num2;
    string num1;

    if (ope.top() == '-')
    {
        num1 = num.top();
        num.pop();
        ope.pop();
        if (!num.empty())
        {
            if (ope.empty() || num.size() == ope.size())
            {
                ope.push('+');
            }
        }
        num1 = "-" + num1;
        num.push(num1);
    }
    else
    {
        num2 = num.top();
        num.pop();
        num1 = num.top();
        num.pop();

        // cout << num1 << endl;
        // cout << num2 << endl;

        if (ope.top() == '+')
        {
            // cout << num1 << endl;
            // cout << num2 << endl;
            // cout << add(num1, num2) << endl;
            if (num1.find("-") == string::npos && num2.find("-") == string::npos)
            {
                // cout << 1 << endl;
                num.push(add(num1, num2));
            }
            else if (num1.find("-") != string::npos && num2.find("-") != string::npos)
            {
                num1.erase(0, 1);
                num2.erase(0, 1);
                // cout << 2 << endl;
                num.push("-" + add(num1, num2));
            }
            else
            {
                if (num1.find("-") != string::npos)
                {
                    num1.erase(0, 1);
                    // cout << 3 << endl;
                    num.push(minu(num2, num1));
                }
                else
                {
                    num2.erase(0, 1);
                    // cout << 4 << endl;
                    num.push(minu(num1, num2));
                }
            }
            // cout << num.top() << endl;
        }
        else if (ope.top() == '*')
        {
            num.push(mul(num1, num2));
        }
        else if (ope.top() == '/')
        {
            num.push(divide(num1, num2));
        }

        ope.pop();
    }
    // cout << num.top() << endl;
}

// int main(){
//     string str="";
//     while(str!="exit"){
//         getline(cin,str);
//         calculator(str);
//     }
// }