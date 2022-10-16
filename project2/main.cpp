#include <iostream>
#include "func.hpp"
#include "calculator.hpp"
#include <cmath>

using namespace std;

int main()
{
    string str = "";
    string unknown[26];
    while (str != "exit")
    {
        getline(cin, str);
        if (str == "exit")
        {
            break;
        }
        else if (str.find("=") != string::npos) // 定义为赋值语句
        {
            int place = str.find("=");
            char character = str[0];
            string value = str.substr(place + 1);
            unknown[character - 'a'] = value;
        }
        else if (str.find("sqrt") != string::npos)
        {
            string content=extract_content(str,"sqrt");
            // cout << content << endl;
            string result = calculator(content,unknown);
            // cout<<result<<endl;
            double re=stold(result);
            cout << sqrt(re) << endl;
        }
        else
        {
            cout << calculator(str, unknown) << endl;
        }
    }
}