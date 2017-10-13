//eval_pre_post_.cpp
//Sakhrani:Kabir:A00376745:csc34141
//Submission 08: Evaluating Prefix and Postfix Expressions

/*
The whole program works correctly to my knowledge, expcept for some
error checking.
*/

#include <iostream> //this is where cout, endl and cin.ignore() live
#include <string> //this is where getline() and to_string() live
#include <cstdlib> //this is where atoi() lives
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

#include "utilities.h"
using Scobey::DisplayOpeningScreen;
using Scobey::Pause;

void DisplayUsage();
/**<
Displays a brief program usage description on the standard output.
@pre None
@post A program usage description has been displayed, with a pause
at the end for the user to press Enter to continue.
*/

int postfixOrPrefixCalculated
(
string expression          //in
);
/**<
Performs the calculation based on the input expresson.
@param result The final result.
@pre
- expression has been input and ready for manipulation
@post
- Returns a value which is the result from the expression
*/


void ErrorCheckingDone
(
string expression         //in
);
/**<
Checks for errors in the input expression
@param expression The expression to be calculated
@param result The final result.
@pre
- expression has been input and ready for manipulation.
@post
- The program continues or exits and reports an error if there is one.
*/

void Format
(
string formattedExpression,    //in
int result                    //in
);
/**<
Formats the input for a specified output.
@param formattedExpression String with spaces between characters
@param result The final result.
@pre
- formattedExpression has been declared and ready for manipulation.
- result can be used for manipulation
@post
- The final output has been output.
*/

int main(int argc, char* argv[])
{
    //Displayed if there are no command-line parameters besides program name.
    if (argc == 1)
    {
        Scobey::DisplayOpeningScreen("Sakhrani:Kabir:A00376745:csc34141",
            "Submission 08: Evaluating Prefix and Postfix Expressions");
        DisplayUsage();
        return EXIT_SUCCESS;
    }
    else
    {
        //Declared/Initialized Variables
        int result;
        string const operators = "+-*/";
        string expression;
        string formattedExpression;

        //Creates the expression
        for (int i = 1; i < argc; i += 1)
        {
            expression += string(argv[i]);
            if (i == argc - 1)
            {
                formattedExpression += string(argv[i]);
            }
            else
            {
                formattedExpression += string(argv[i]) + " ";
            }
            
        }
        //Checks whether the expression is postfix or prefix
        size_t found = operators.find(expression.at(0));
        //Code for postfix expression
        if (found == string::npos)
        {
            ErrorCheckingDone(expression);
            result = postfixOrPrefixCalculated(expression);
            Format(formattedExpression, result);
        }
        //Code for prefix expression
        else
        {
            ErrorCheckingDone(expression);
            reverse(expression.begin(), expression.end());
            result = postfixOrPrefixCalculated(expression);
            Format(formattedExpression, result);
        }
        Pause();
    }
}


void DisplayUsage()
{
    cout << "This program evaluates any valid prefix or postfix "
        "expression which\ncontains positive integer operands and the "
        "operators +, -, * and/or /.\nThe expression to be evaluated "
        "must be entered on the command line.\nA single positive integer "
        "also evaluates as itself."

        "\n\nTypical usage examples:"
        "\n> eval_pre_post + * 2 3 4"
        "\n+ * 2 3 4 = 10"
        "\n> eval_pre_post 2 3 4 + *"
        "\n2 3 4 + * = 14"

        "\n\nThe following errors are recognized and reported:"
        "\n\nFor prefix expressions:"
        "\nError: End of prefix expression reached unexpectedly."
        "\nError: Bad operator ? encountered evaluating prefix expression."
        "\nError: Extraneous characters found after valid prefix expression."
        "\n\nFor postfix expressions:"
        "\nError: End of postfix expression reached unexpectedly."
        "\nError: Bad operator ? encountered evaluating postfix expression."
        "\nError: Not enough operands for postfix operator ?."
        "\nError: Found too many operands when evaluating postfix expression."
        "\n";
    Pause();
}

int postfixOrPrefixCalculated
(
string expression            //in
)
{
    stack<int> calculate;
    int right, left;
    for (int i = 0; i < expression.size(); i++)
    {
        //Pushes a number back to the stack
        if (isdigit(expression.at(i)))
        {
            calculate.push(expression.at(i) - '0');
        }
        //Removes the top two values from the stack
        //Then performs a calculation and the answer is pushed back
        else
        {
            left = calculate.top();
            calculate.pop();
            right = calculate.top();
            calculate.pop();
            if (expression.at(i) == '+')
            {
                calculate.push(left + right);
            }
            if (expression.at(i) == '*')
            {
                calculate.push(left * right);
            }
            if (expression.at(i) == '/')
            {
                calculate.push(right / left);
            }
            if (expression.at(i) == '-')
            {
                calculate.push(right - left);
            }
        }
    }
    return calculate.top();
}

void ErrorCheckingDone
(
string expression           //in
)
{
    //Declared/Initialized Variables
    string const onlyUsableSymbols = "0123456789+-*/";
    string const operators = "+-*/";
    string const operands = "0123456789";
    int operandCount = 0;
    int operatorCount = 0;
    int noUsableSymbolsCount = 0;
    char badSymbol;
    size_t found = operators.find(expression.at(0));
    if (found == string::npos)
    {
        //Error Checking for Postfix expression
        for (int x = 0; x < expression.length(); x++)
        {
            size_t operatorFind;
            size_t noUsableSymbolsFind;
            noUsableSymbolsFind = onlyUsableSymbols.find(expression.at(x));
            if (noUsableSymbolsFind == string::npos)
            {
                badSymbol = expression.at(x);
                noUsableSymbolsCount += 1;
                break;
            }
            operatorFind = operators.find(expression.at(x));
            if (operatorFind == string::npos)
            {

                operandCount += 1;
            }
            else
            {
                operatorCount += 1;
            }
        }
        //Output if there is a bad operator
        if (noUsableSymbolsCount >= 1)
        {
            cout << "Error: Bad operator " << badSymbol << " encountered"
                 << " evaluating postfix expression.\nProgram is now "
                 << "terminating." << endl;
            Pause();
            exit(0);
        }
        //Output if there are too many operands
        if (operandCount - operatorCount > 1)
        {
            cout << "Error: Found too many operands when evaluating "
                 << "postfix expression.\nProgram is now terminating."
                 << endl;
            Pause();
            exit(0);
        }
    }
    else
    {
        //Error Checking for Prefix expression
        for (int x = 0; x < expression.length(); x++)
        {
            size_t operatorFind;
            size_t noUsableSymbolsFind;
            noUsableSymbolsFind = onlyUsableSymbols.find(expression.at(x));
            if (noUsableSymbolsFind == string::npos)
            {
                badSymbol = expression.at(x);
                noUsableSymbolsCount += 1;
                break;
            }
            operatorFind = operators.find(expression.at(x));
            if (operatorFind == string::npos)
            {

                operandCount += 1;
            }
            else
            {
                operatorCount += 1;
            }
        }
        //Output if there is a bad operator
        if (noUsableSymbolsCount >= 1)
        {
            cout << "Error: Bad operator " << badSymbol << " encountered"
                 << " evaluating prefix expression.\nProgram is now "
                 << "terminating." << endl;
            Pause();
            exit(0);
        }
        //Ouput if the end of the expression is reached
        if (operandCount <= operatorCount)
        {
            cout << "Error: End of prefix expression reached"
                 << " unexpectedly.\nProgram is now terminating." << endl;
            Pause();
            exit(0);
        }
    }
}

void Format
(
string formattedExpression,        //in
int result                         //in
)
{
    //The final output
    cout << formattedExpression << " = " << result << endl;
}