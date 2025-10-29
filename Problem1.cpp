#include <iostream>
#include <string>
#include <stack>
using namespace std;

string isBalanced(string s) {
    stack<char> brackets;
    //Adding all the opening brackets to a stack then removing them if the next closing bracket in the string matches
    for (char& c : s) {
        if (c == '[' || c == '{' || c == '(')
            brackets.push(c);
        else {
            //If we find a closing bracket that doesn't match the opening bracket at the top of the stack it means the order of the brackets is wrong
            if (brackets.empty() || abs(brackets.top() - c) > 2) return "Not Balanced";
            else brackets.pop();
        }
    }
    //If the string is empty at the end it means all the brackets are balanced otherwise it's not balanced
    if (brackets.empty()) return "Balanced";
    return "Not Balanced";
}

int main()
{
    //I've made the solution into a standalone program so I can check it works correctly
    string input;
    cin >> input;
    cout << isBalanced(input);

    return 0;
}