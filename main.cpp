#include <iostream>
#include <string>
#include <stack>
#include <vector>

bool Contains(std::vector<char> &list, const char &c);
int IndexOf(std::vector<char> &list, const char &c);
int GetOperatorValue(const char &op);


int main()
{
    std::cout << "Type your equation: ";
    std::string input;
    getline(std::cin, input);
    std::stack<char> operators;
    std::string output;
    std::vector<char> opList = { '+', '-', '%', '*', '^'};
    for (const char ch : input)
    {
        if (ch == ' ') continue;
        if (Contains(opList, ch))
        {
            if (operators.empty())
            {
                operators.push(ch);
                continue;
            }
            while (GetOperatorValue(ch) <= GetOperatorValue(operators.top()))
            {
                output += operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
        else
        {
            output += ch;
        }
    }

    // std::cout << "I LOVE POLAND: " << 
    return 0;
}

bool Contains(std::vector<char> &list, const char &c)
{
    for (const char ch : list)
    {
        if (ch == c) return true;
    }
    return false;
}

int IndexOf(std::vector<char> &list, const char &c)
{
    int index = 0;
    for (const char ch : list)
    {
        if (ch == c) return index;
        index++;
    }
    return -1;
}

int GetOperatorValue(const char &op)
{
    switch (op)
    {
        case '+':
        case '−':
        case '-':
            return 2;
        case '÷':
        case '×':
        case '%':
        case '*':
            return 3;   
        case '^':
            return 4;
        default:
            break;
    }
    return -1;
}