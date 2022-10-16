#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

struct struc_add;

struct struc_minus;

string pre_deal(string str);

bool isInt(string str);

string add(string str1,string str2);

string minu(string str1,string str2);

string mul(string str1,string str2);

string divide(string str1,string str2);

string after_deal(string str);

string extract_content(string str,string function);

struc_add calculate_add_demical(string major_demical, int major_bit, string another_demical, int another_bit, int para);

struc_add calculater_add_int(string major_int, string another_int, int para);

struc_minus calculate_minus_demical(string major_demical, int major_bit, string another_demical, int another_bit, int para);

struc_minus calculater_minus_int(string major_int, string another_int, int para);

