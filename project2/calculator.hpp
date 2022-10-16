#include <string>
#include <iostream>
#include <stack>
#include "func.hpp"

using namespace std;

string calculator(string str,string unknown[]);

int priority(char ope);

void calculate(stack<char> &ope, stack<string> &num);