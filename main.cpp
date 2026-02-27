#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <math.h>

bool Contains(std::vector<char> &list, const char &c);
int IndexOf(std::vector<char> &list, const char &c);
int GetOperatorValue(const char &op);
double Calculate(const std::string &first, const std::string &second, const char &op);


int main()
{
    std::cout << "Type your equation: ";
    std::string input = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
    // getline(std::cin, input);
    std::vector<std::string> equation;
    std::string temp;
    std::vector<char> opList = { '+', '-', '/', '*', '^', '(', ')'};
    for (const char ch : input)
    {
        if (ch == ' ')
            continue;
        if (Contains(opList, ch))
        {
            if (!temp.empty())
                equation.push_back(temp);
            equation.push_back(std::string(1, ch));
            temp.clear();
        }
        else
        {
            temp += ch;
        }
       
    }
    if (!temp.empty())
        equation.push_back(temp);   
    std::cout << "Equation: ";
    for (const std::string &str : equation)
    {
        std::cout << str << ", ";
    }
    std::cout << std::endl;
    std::stack<char> operators;
    std::vector<std::string> output;
    for (const std::string str : equation)
    {
        // std::cout << str << " ";
        if (Contains(opList, str[0]))
        {
            char op = str[0];
            if (operators.empty())
            {
                operators.push(op);
                continue;
            }
            if (op == '(')
            {
                operators.push(op);
                continue;
            }
            if (op == ')')
            {
                while (operators.top() != '(')
                {
                    output.push_back(std::string(1, operators.top()));
                    operators.pop();
                }
                operators.pop();
                continue;
            }
            while (GetOperatorValue(op) <= GetOperatorValue(operators.top()) && GetOperatorValue(operators.top()) != 4)
            {
                output.push_back(std::string(1, operators.top()));
                operators.pop();
                if (operators.empty()) break;
            }
            operators.push(op);
        }
        else
        {
            
            output.push_back(str);
        }
    }

    // 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3

    while (!operators.empty())
    {
        output.push_back(std::string(1, operators.top()));
        operators.pop();
    }

    std::cout << std::endl;

    std::cout << "I LOVE POLAND: ";
    for (const std::string &s : output)
    {
        std::cout << s << ", ";
    }
    std::cout << std::endl;

    for (int i = 2; i < output.size(); i++)
    {
        if (Contains(opList, output[i][0]))
        {
            std::string replacement = std::to_string(Calculate(output[i - 2], output[i - 1], output[i][0]));
            output.erase(output.begin() + i - 2, output.begin() + i + 1);
            output.insert(output.begin() + i - 2, replacement);
            i = 2;
            std::cout << "Replacing: ";
            for (const std::string &s : output)
            {
                std::cout << s << " ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "I LOVE POLAND 2: " << output[0] << std::endl;
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

double Calculate(const std::string &first, const std::string &second, const char &op)
{
    std::cout << "Calculating: " << first << " " << second << std::endl;
    switch (op)
    {
        case '+':
            return std::stod(first) + std::stod(second); 
        case '-':
            return std::stod(first) - std::stod(second); 
        case '/':
            return std::stod(first) / std::stod(second); 
        case '*':
            return std::stod(first) * std::stod(second); 
        case '^':
            return pow(std::stod(first), std::stod(second)); 
        default:
            break;
    }
    return -1.0;
}