#include "func.hpp"
#include <sstream>
#include <iomanip>
#include <stack>

using namespace std;

string pre_deal(string str) // pre_deal的作用在于将科学计数法变成普通表示形式，为了方便运算，结尾加上.0000
{
    if (str.find('e') != -1) // 是否使用科学计数法
    {
        int place = str.find_last_of('e');         // place为e在数据中的位置
        string zero_num = (str.substr(place + 1)); // zero_num为科学计数法的指数
        // cout << zero_num << endl;
        string true_num = str.substr(0, place); // true_num为科学计数法的实数部分
        // cout << true_num << endl;
        int z_n = atoi(zero_num.c_str());
        int t_n = atoi(true_num.c_str()); //转换为int类型
        if (z_n > 0)                      //小数点向右移情况
        {
            if (str.find('.') != -1) //是否有小数点
            {
                int p1 = str.find_last_of('.');                                   // p1为小数点所在的位置
                str = true_num.substr(0, p1).insert(p1, true_num.substr(p1 + 1)); // str变成除去小数点之后的实数部分

                if (z_n >= true_num.length() - p1 - 1) // true_num.length() - p1 - 1为小数位数，判断是否要在最后加0
                {
                    // cout << "yes" << endl;
                    for (int i = 0; i < z_n - true_num.length() + p1 + 1; i++) //加0
                    {
                        str = str.insert(str.length(), "0");
                    }
                }
                else
                {
                    str = str.insert(p1 + z_n, ".");
                }
            }
            else //没有小数点
            {
                str = true_num;
                for (int i = 0; i < z_n; i++)
                {
                    str = str.insert(str.length(), "0");
                }
            }
        }
        else //小数点向左移情况
        {
            if (str.find('.') != -1) //存在小数点
            {
                int p1 = str.find_last_of('.');
                str = "0.";
                // cout << in_0 << endl;
                for (int i = 0; i < -z_n - p1; i++)
                {
                    str = str.insert(str.length(), "0");
                }
                // cout << in_0 << endl;
                true_num = true_num.erase(p1, 1); //删去小数点
                str = str.insert(str.length(), true_num);
            }
            else
            {
                str = "0.";
                for (int i = 0; i < -z_n - true_num.length(); i++)
                {
                    str = str.insert(str.length(), "0");
                }
                str = str.insert(str.length(), true_num);
            }
        }
    }

    if (isInt(str))
    {
        str = str.insert(str.length(), ".000000");
    }

    return str;
}

bool isInt(string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        int tmp = (int)str[i];
        if (tmp >= 48 && tmp <= 57)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

struct struc_add
{
    string result;
    string para;
};

string add(string str1, string str2)
{
    string num1 = pre_deal(str1);
    string num2 = pre_deal(str2);
    int place1 = num1.find('.');
    // cout << place1 << endl;
    int place2 = num2.find('.');
    // cout << place2 << endl;
    int bit1 = num1.length() - place1 - 1;
    int bit2 = num2.length() - place2 - 1;
    // cout << bit1 << endl;
    string result1;
    string result2;
    string para = "0";
    string major_int, another_int;
    string major_demical, another_demical;

    if (bit1 > bit2)
    {
        major_demical = num2.substr(place2 + 1);
        another_demical = num1.substr(place1 + 1);
        struc_add struc;
        struc = calculate_add_demical(major_demical, bit2, another_demical, bit1, para[0] - '0');
        result2 = struc.result;
        para = struc.para;
    }
    else
    {
        major_demical = num1.substr(place1 + 1);
        another_demical = num2.substr(place2 + 1);
        struc_add struc;
        struc = calculate_add_demical(major_demical, bit1, another_demical, bit2, para[0] - '0');
        result2 = struc.result;
        para = struc.para;
    }

    if (place1 > place2)
    {
        major_int = num2.substr(0, place2);
        another_int = num1.substr(0, place1);
        struc_add struc;
        struc = calculater_add_int(major_int, another_int, para[0] - '0');
        result1 = struc.result;
        para = struc.para;
    }
    else
    {
        major_int = num1.substr(0, place1);
        another_int = num2.substr(0, place2);
        struc_add struc;
        struc = calculater_add_int(major_int, another_int, para[0] - '0');
        result1 = struc.result;
        para = struc.para;
    }

    // cout << "major int: " << major_int << endl;
    // cout << "another int: " << another_int << endl;
    // cout << "result1: " << result1 << endl;

    // cout << "major demical: " << major_demical << endl;
    // cout << "another demical: " << another_demical << endl;

    string result = result1 + "." + result2;

    return after_deal(result);
}

struc_add calculate_add_demical(string major_demical, int major_bit, string another_demical, int another_bit, int para)
{
    string result = "";
    for (int i = major_demical.length() - 1; i >= 0; i--)
    {
        result = to_string((major_demical[i] + another_demical[i] + para - '0' - '0') % 10) + result;
        para = (major_demical[i] + another_demical[i] + para - '0' - '0') / 10;
    }
    for (int i = major_bit; i < another_bit; i++)
    {
        result = result + another_demical[i];
    }

    struc_add struc;
    struc.result = result;
    struc.para = to_string(para);
    return struc;
}

struc_add calculater_add_int(string major_int, string another_int, int para)
{
    string result = "";
    for (int i = 0; i < major_int.length(); i++)
    {
        // cout << para <<endl;
        result = to_string((major_int[major_int.length() - 1 - i] + another_int[another_int.length() - 1 - i] + para - '0' - '0') % 10) + result;
        para = (major_int[major_int.length() - 1 - i] + another_int[another_int.length() - 1 - i] + para - '0' - '0') / 10;
        // cout << major_int[major_int.length() - 1 - i] - '0' << endl;
        // cout << another_int[another_int.length() - 1 - i] - '0' << endl;
        // cout << "i = " << i << ", para = " << para << endl;

        // cout << "result: " << result << endl;
    }
    for (int i = another_int.length() - major_int.length() - 1; i >= 0; i--)
    {
        result = to_string((another_int[i] - '0' + para) % 10) + result;
        para = (another_int[i] - '0' + para) / 10;
        // cout << "i = " << i << ", para = " << para << endl;
    }
    // cout << "result: " << result << endl;
    if (para > 0)
    {
        result = to_string(para) + result;
    }
    struc_add struc;
    struc.result = result;
    struc.para = to_string(para);
    return struc;
}

struct struc_minus
{
    string result;
    string para;
};

string minu(string str1, string str2)
{
    string num1 = pre_deal(str1);
    string num2 = pre_deal(str2);
    int place1 = num1.find('.');
    // cout << place1 << endl;
    int place2 = num2.find('.');
    // cout << place2 << endl;
    int bit1 = num1.length() - place1 - 1;
    int bit2 = num2.length() - place2 - 1;
    // cout << bit1 << endl;
    string result1;
    string result2;
    string para = "0";
    string major_int, another_int;
    string major_demical, another_demical;

    bool swap = false;

    if (place1 < place2)
    {
        string num3 = num1;
        num1 = num2;
        num2 = num3;
        int place3 = place1;
        place1 = place2;
        place2 = place3;
        int bit3 = bit1;
        bit1 = bit2;
        bit2 = bit3;
        swap = true;
        // cout << num1 <<endl;
        // cout << num2 <<endl;
        // cout << num3 <<endl;
    }
    

    if (bit1 > bit2)
    {
        major_demical = num1.substr(place1 + 1);
        another_demical = num2.substr(place2 + 1);
        // cout << "major_demical" << major_demical << endl;
        // cout << "another_demical" << another_demical << endl;
        for (int i = bit2; i < bit1; i++)
        {
            another_demical = another_demical + "0";
        }
        struc_minus struc;
        struc = calculate_minus_demical(major_demical, bit2, another_demical, bit1, para[0] - '0');
        result2 = struc.result;
        para = struc.para;
    }
    else
    {

        major_demical = num1.substr(place1 + 1);
        another_demical = num2.substr(place2 + 1);
        // cout << "major_demical: " << major_demical << endl;
        // cout << "another_demical: " << another_demical << endl;
        for (int i = bit1; i < bit2; i++)
        {
            major_demical = major_demical + "0";
        }
        struc_minus struc;
        struc = calculate_minus_demical(major_demical, bit1, another_demical, bit2, para[0] - '0');
        result2 = struc.result;
        para = struc.para;
    }

    if (place1 > place2)
    {
        major_int = num1.substr(0, place1);
        another_int = num2.substr(0, place2);
        // cout << "major_int: " << major_int << endl;
        // cout << "another_int: " << another_int << endl;
        struc_minus struc;
        struc = calculater_minus_int(major_int, another_int, para[0] - '0');
        result1 = struc.result;
        para = struc.para;
    }
    else
    {
        major_int = num1.substr(0, place1);
        another_int = num2.substr(0, place2);
        struc_minus struc;
        struc = calculater_minus_int(major_int, another_int, para[0] - '0');
        result1 = struc.result;
        para = struc.para;
    }

    // cout << "major int: " << major_int << endl;
    // cout << "another int: " << another_int << endl;
    // cout << "result1: " << result1 << endl;

    // cout << "major demical: " << major_demical << endl;
    // cout << "another demical: " << another_demical << endl;

    string result = result1 + "." + result2;
    // cout << "result: " << result << endl;

    if (para == "-1" && place1 <= place2)
    {
        result = to_string(stold(result) - 10);
    }
    if(swap)
    {
        result="-"+result;
    }

    return after_deal(result);
}

struc_minus calculate_minus_demical(string major_demical, int major_bit, string another_demical, int another_bit, int para)
{
    string result = "";
    for (int i = major_demical.length() - 1; i >= 0; i--) // 小数末位向前
    {
        if (major_demical[i] - another_demical[i] + para < 0)
        {
            result = to_string((major_demical[i] - another_demical[i] + para + 10)) + result;
            para = -1;
        }
        else
        {
            result = to_string((major_demical[i] - another_demical[i] + para)) + result;
            para = 0;
        }
    }

    struc_minus struc;
    struc.result = result;
    struc.para = to_string(para);
    return struc;
}

struc_minus calculater_minus_int(string major_int, string another_int, int para)
{
    string result = "";
    for (int i = 0; i < another_int.length(); i++)
    {
        // cout << para <<endl;
        if ((major_int[major_int.length() - 1 - i] - another_int[another_int.length() - 1 - i] + para < 0))
        {
            result = to_string((major_int[major_int.length() - 1 - i] - another_int[another_int.length() - 1 - i] + para + 10)) + result;
            para = -1;
            // cout << "result: "<<result <<endl;
        }
        else
        {
            result = to_string((major_int[major_int.length() - 1 - i] - another_int[another_int.length() - 1 - i] + para)) + result;
            para = 0;
            // cout << "result: "<<result <<endl;
        }
        // cout << major_int[major_int.length() - 1 - i] - '0' << endl;
        // cout << another_int[another_int.length() - 1 - i] - '0' << endl;
        // cout << "i = " << i << ", para = " << para << endl;

        // cout << "result: " << result << endl;
    }
    for (int i = major_int.length() - another_int.length() - 1; i >= 0; i--)
    {
        if ((major_int[i] - '0' + para) < 0)
        {
            result = to_string((major_int[i] - '0' + para + 10)) + result;
            para = -1;
        }
        else
        {
            result = to_string((major_int[i] - '0' + para)) + result;
            para = 0;
        }
        // cout << "i = " << i << ", para = " << para << endl;
    }
    // cout << "result: " << result << endl;

    struc_minus struc;
    struc.result = result;
    struc.para = to_string(para);
    // cout << result<<endl;
    return struc;
}

string mul(string str1, string str2)
{
    string in_0 = pre_deal(str1);
    string in_1 = pre_deal(str2);
    int len_1 = in_0.length();
    int len_2 = in_1.length();

    int *num1 = (int *)malloc(len_1 * sizeof(len_1));
    int *num2 = (int *)malloc(len_2 * sizeof(len_2));
    int *result = (int *)malloc((len_1 + len_2) * sizeof(len_1 + len_2));

    // cout << sizeof(result) <<endl;

    memset(num1, 0, len_1 * sizeof(len_1));
    memset(num2, 0, len_2 * sizeof(len_2));
    memset(result, 0, (len_1 + len_2) * sizeof(len_1 + len_2));

    // cout << in_0 << endl;

    int bit1 = 0;
    int bit2 = 0;
    for (int i = len_1 - 1, j = 0; i >= 0; i--, j++)
    {
        if (in_0[j] == '.')
        {
            bit1 = len_1 - 1 - j;
        }
        else
        {
            int t = i - 1;
            if (bit1 != 0)
            {
                t = i;
            }
            num1[t] = in_0[j] - '0';
        }
    }

    // cout << bit1 << endl;

    for (int i = len_2 - 1, j = 0; i >= 0; i--, j++)
    {
        if (in_1[j] == '.')
        {
            bit2 = len_2 - 1 - j;
        }
        else
        {
            int t = i - 1;
            if (bit2 != 0)
            {
                t = i;
            }
            num2[t] = in_1[j] - '0';
        }
    }

    // cout << in_0 << endl;
    // for (int i=0;i<sizeof(num1);i++){
    //     cout << num1[i];
    // }
    // cout << endl;
    // cout << in_1 << endl;
    // for (int i=0;i<sizeof(num2);i++){
    //     cout << num2[i];
    // }
    // cout << endl;

    for (int i = 0; i < len_1 - 1; i++)
    {
        for (int j = 0; j < len_2 - 1; j++)
        {
            result[i + j] += num1[i] * num2[j];
        }
    }

    // cout << result[1] <<endl;

    for (int i = 0; i < len_1 + len_2; i++)
    {
        if (result[i] > 0)
        {
            result[i + 1] += result[i] / 10;
        }

        result[i] = result[i] % 10;
    }

    int index = 0;
    string fi = "";
    for (int i = len_1 + len_2 - 1; i >= 0; i--)
    {
        if (result[i] != 0)
        {
            index = i;
            break;
        }
    }

    for (int i = index; i >= 0; i--)
    {
        fi += to_string(result[i]);
    }

    // cout << fi << endl;

    int sen2 = 0;
    int len_fi = fi.length();
    int bit = 0;

    // cout << bit1 +bit2 << endl;
    // cout << fi.length() << endl;

    for (int i = 0; i < fi.length(); i++)
    {
        if (sen2 == 0 && i < bit1 + bit2)
        {

            if (fi.substr(fi.length() - 1 - i, 1) != "0")
            {
                // cout << fi.substr(fi.length() - 1 - i, 1) << endl;

                sen2 = 1;
            }
            else
            {
                bit = i;
            }
        }
        if (i == bit1 + bit2)
        {
            break;
        }
    }

    fi = fi.erase(fi.length() - bit - 1);

    // cout << fi.length() << endl;
    // cout << sen2 << endl;

    if (sen2 == 1)
    {
        while (len_fi - bit1 - bit2 < 1)
        {
            fi.insert(0, "0");
            len_fi += 1;
        }
        fi = fi.insert(len_fi - bit1 - bit2, ".");
    }

    free(num1);
    free(num2);
    num1 = NULL;
    num2 = NULL;

    return fi;
}

string divide(string str1, string str2)
{
    double a = stold(str1);
    double b = stold(str2);
    return after_deal(to_string(a / b));
}

string after_deal(string str) // after_deal用于除去小数位数
{
    for (int i = str.length() - 1; i >= 0; i--)
    {
        if (str.substr(i) == "0")
        {
            str.erase(i);
        }
        else if (str.substr(i) == ".")
        {
            str.erase(i);
            break;
        }
        else
        {
            break;
        }
    }
    for (int i = 0; i < str.length(); i++)
    {
        if (str.substr(i, i + 1) == "0")
        {
            str.erase(i, i + 1);
        }
        else
        {
            break;
        }
    }
    return str;
}

string extract_content(string str, string function)
{
    int place = str.find(function);
    // cout << place << endl;
    stack<char> par;
    par.push('(');
    bool sentence = false;
    string content = "";
    for (int i = place; i < str.length(); i++)
    {
        if (!sentence && str[i] == '(')
        {
            sentence = true;
        }
        else if (str[i] == '(')
        {
            par.push('(');
        }
        else if (str[i] == ')')
        {
            par.pop();
        }

        if (!par.empty() && sentence)
        {
            content = content + str[i];
        }
        else if (par.empty())
        {
            break;
        }
    }
    content.erase(0, 1);
    return content;
}