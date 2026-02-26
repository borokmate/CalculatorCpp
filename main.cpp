#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <math.h>

bool Contains(std::vector<char> &list, const char &c);
int IndexOf(std::vector<char> &list, const char &c);
int GetOperatorValue(const char &op);
int Calculate(const char &first, const char &second, const char &op);


int main()
{
    std::cout << "Type your equation: ";
    std::string input;
    getline(std::cin, input);
    std::stack<char> operators;
    std::string output;
    std::vector<char> opList = { '+', '-', '/', '*', '^', '(', ')'};
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
            if (ch == '(')
            {
                operators.push(ch);
                continue;
            }
            if (ch == ')')
            {
                while (operators.top() != '(')
                {
                    output += operators.top();
                    operators.pop();
                }
                operators.pop();
                continue;
            }
            while (GetOperatorValue(ch) <= GetOperatorValue(operators.top()) && GetOperatorValue(operators.top()) != 4)
            {
                std::cout << "Current: " << ch << "\nPops: " << operators.top() << std::endl;
                output += operators.top();
                operators.pop();
                if (operators.empty()) break;
            }
            operators.push(ch);
        }
        else
        {
            output += ch;
        }
    }

    // 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3

    while (!operators.empty())
    {
        output += operators.top();
        operators.pop();
    }

    std::cout << "I LOVE POLAND: " << output << std::endl;

    for (int i = 2; i < output.length(); i++)
    {
        if (Contains(opList, output[i]))
        {
            output.replace(i - 2, i, std::to_string(Calculate(output[i - 2], output[i - 1], output[i])));
            std::cout << "buh?: " << output << std::endl;
            i = 2;
        }
    }
    std::cout << "I LOVE POLAND 2: " << output << std::endl;
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
        case '-':
            return 2;
        case '/':
        case '*':
            return 3;
        case '^':
            return 4;
        default:
            break;
    }
    return -1;
}

int Calculate(const std::string &first, const std::string &second, const char &op)
{
    switch (op)
    {
        case '+':
            
            return std::stoi(first) + std::stoi(second); 
        case '-':
            return std::stoi(first) - std::stoi(second); 
        case '/':
            return std::stoi(first) / std::stoi(second); 
        case '*':
            return std::stoi(first) * std::stoi(second); 
        case '^':
            return pow(std::stoi(first), std::stoi(second)); 
        default:
            break;
    }
}