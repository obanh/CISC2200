//Oscar Banh
//November 11, 2018 resubmit

#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
using namespace std;

using ValueType = int;

/**
 * @class IllegalExprException
 * Exception class thrown by illegal infix expression
 */
class IllegalExprException : public exception
{
};


ValueType processExpression(const string& expr) throw (IllegalExprException);
bool isValidResponse(char response); //done
bool isYesResponse(char response); //done
int precedence(char op); //done
void provideHelpIfNecessary(void); //done
void execute(stack<ValueType>& valstack, stack<char>& opStack)
    throw (IllegalExprException); //done
ValueType doOperation(ValueType operandL, char operation, ValueType operandR)
    throw (IllegalExprException); //done


int main(void)
{
    provideHelpIfNecessary();

    while (true) {
	cout << "Expression? " ;
	string expr;                    // holds the supposed expression
	getline(cin, expr);
	if (expr.length() == 0)
	    break;
	try {
	    ValueType result = processExpression(expr);
	    cout << result << endl;
	} catch (exception& ex) {
	    cerr << ex.what() << endl;
	}
    } // end while
    cout << endl;
} // end main

void provideHelpIfNecessary(void)
{
    cout << "Do you need help (Y/N)? ";
    char response;
    cin >> response;
    isValidResponse(response);

} // end provideHelpIfNecessary

ValueType processExpression(const string& expr) throw (IllegalExprException)
{
    stack<ValueType>valStack;
    stack<char>opStack;
    for (int i = 0; i < expr.length(); i++)
    {
        switch (expr[i])
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                valStack.push(expr[i] - 48); //need to keep -48 or else it breaks the program
                break;
            case '(':
                opStack.push('(');
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                if (opStack.empty())
                    opStack.push(expr[i]);
                else if (precedence(expr[i]) > precedence(opStack.top()))
                    opStack.push(expr[i]);
                else
                {
                    while (!opStack.empty() && precedence(expr[i]) <= precedence(opStack.top()))
                    {
                        execute(valStack, opStack);
                    }
                    opStack.push(expr[i]);
                }
                break;
            case ')':
                while (opStack.top() != '(')
                {
                    execute(valStack, opStack);
                }
                opStack.pop();
                break;
        }
    }
    while (!opStack.empty())
    {
        execute(valStack, opStack);
    }
    ValueType answer = valStack.top();
    return answer;
} // end processExpression

bool isValidResponse(char response)
{
    if (response == 'Y' || response == 'y' || response == 'N' || response == 'n')
    {
        isYesResponse(response);
    }
    else
    {
        cout << "Response must be 'Y' or 'N'." << endl;
        provideHelpIfNecessary();
    }
    return true;
} // end isValidResponse

bool isYesResponse(char response)
{
    if (response == 'Y' || response == 'y')
    {
        cout << "Enter an infix expression at the prompt." << endl;
        cout << "The program will tell you its value." << endl;
        cout << "To stop the program, just hit \"return\" at the prompt." << endl;
        cin.clear();
        cin.sync();
        return true;
    }
    else
        exit(EXIT_SUCCESS);
} // end isYesResponse

int precedence(char op)
{
    if (op == '(' || op == ')')
        return 1;
    else if (op == '+' || op == '-')
        return 2;
    else if (op == '*' || op == '/')
        return 3;
    else if (op == '^')
        return 4;
    else
        return -1;
} // end precedence

void execute(stack<ValueType>& valStack, stack<char>& opStack)
    throw (IllegalExprException)
{
    ValueType operand2 = valStack.top();
    valStack.pop();
    ValueType operand1 = valStack.top();
    valStack.pop();
    char op = opStack.top();
    opStack.pop();
    ValueType result = doOperation(operand1, op, operand2);
    valStack.push(result);
} // end execute

ValueType doOperation(ValueType operandL, char operation, ValueType operandR)
    throw (IllegalExprException)
{
    if (operation == '+')
        return operandL + operandR;
    else if (operation == '-')
        return operandL - operandR;
    else if (operation == '*')
        return operandL * operandR;
    else if (operation == '/')
        return operandL / operandR;
    else
        return operandL ^ operandR;
} // end doOperation
