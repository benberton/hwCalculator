#include "calc.h"

Calc::Calc(char* argvIn)
{
    //return true if the tokens are not correct or the parentheses are not balanced
    inFix = argvIn;
    if (!CheckTokens() || !CheckParens())
    {
        cout << "ERROR: Tokens" << endl;
        exit(EXIT_FAILURE);
    }

    MakeValueTbl();
    Parse();
    InFixToPostFix();
}

Calc::~Calc()
{
    delete []valueTbl;
    delete []inFix;
    delete []postFix;
}

bool Calc::CheckTokens()
{
    int i = 0;
    while(inFix[i] != '\0')
    {
        char val = inFix[i];
        if (!IsOperator(val) && !IsChar(val) && !IsDigit(val))
            return false;
        i++;
    }
    return true;
}

bool Calc::IsOperator(char ch)
{
    switch (ch)
    {
        case '+': return true;
        case '-': return true;
        case '*': return true;
        case '/': return true;
        case '(': return true;
        case ')': return true;
    }
    return false;
}

bool Calc::IsChar(char ch)
{
    for (int i = 'A'; i <= 'Z' ; i++)
    {
        if (ch == i)
            return true;
    }
    return false;
}

bool Calc::IsDigit(char ch)
{
    for (int i = '0'; i <= '9'; i++)
    {
        if (ch == i)
            return true;
    }
    return false;
}

void Calc::MakeValueTbl()
{
    valueTbl = new int[26];
    for (int i = 0; i < 26; i++)
        valueTbl[i] = 0;
    valueIdx = 0;
}

void Calc::Parse()
{
    int length = GetLength(inFix);
    char* inFixTemp = new char[length - 2];
    int inFixInd = 0;
    int i = 0;
    while (inFix[i] != '\0')
    {
        if (IsDigit(inFix[i]))
        {
            int start = i;
            i = FindLast(i);
            //puts next available uppercase char in inFix
            inFixTemp[inFixInd] = valueIdx + 'A';
            AddToValueTbl(start,i);
            inFixInd++;
        }else
        {
            inFixTemp[inFixInd] = inFix[i];
            inFixInd++;
        }
        i++;
    }
    inFixTemp[inFixInd] = '\0';
    inFix = inFixTemp;
}

void Calc::AddToValueTbl(int start, int end)
{
    //dynamically creating a new array to store the desired value
    //this is done so that atoi() can be performed
    int length = end - start + 1;
    char* temp = new char[length];
    for (int i = 0; i < length; i++)
    {
        temp[i] = inFix[i + start];
    }
    int total = atoi(temp);
    valueTbl[valueIdx] = total;
    valueIdx++;
    delete []temp;
}

int Calc::FindLast(int cur)
{
    int i = cur;
    while(IsDigit(inFix[i]))
        i++;
    return i - 1;
}

int Calc::GetLength(char* array)
{
    int i = 0;
    while (true)
    {
        if (array[i] == '\0')
            break;
        i++;
    }
    return i;
}

bool Calc::CheckParens()
{
    if (inFix[0] != '(')
        return false;

    stk = new Stack;
    int i = 0;
    while (inFix[i] != '\0')
    {
        if (inFix[i] == '(')
            stk->Push('(');
        if (inFix[i] == ')')
        {
            if (stk->IsEmpty())
                return false;
            stk->Pop();
        }
        i++;
    }

    if (stk->IsEmpty())
    {
        delete stk;
        return true;
    }
    delete stk;
    return false;
}

void Calc::DisplayInFix()
{
    cout  << inFix << endl;
}

void Calc::InFixToPostFix()
{
    postFix = new char[GetLength(inFix)];
    stk = new Stack;
    int postFixInd = 0;
    int i = 0;
    //method discussed in lecture
    while (IsChar(inFix[i]) || IsOperator(inFix[i]))
    {
        char value = inFix[i];
        if (IsChar(value))
        {
            postFix[postFixInd] = value;
            postFixInd++;
        }else if (value == '('){
            stk->Push('(');
        }else if (value == ')')
        {
            while (stk->Peek() != '(')
            {
                postFix[postFixInd] = stk->Peek();
                stk->Pop();
                postFixInd++;
            }
            stk->Pop();
        }else
        {
            stk->Push(value);
        }
        i++;
    }
    postFix[postFixInd] = '\0';
    delete stk;
}

void Calc::DisplayPostFix()
{
    cout << postFix << endl;
}

int Calc::Evaluate()
{
    stk = new Stack;
    int i = 0;
    while (IsChar(postFix[i]) || IsOperator(postFix[i]))
    {
        char value = postFix[i];
        if (IsChar(value))
        {
            stk->Push(value);
        } else
        {
            int num2 = valueTbl[stk->Peek() - 'A'];
            stk->Pop();
            int num1 = valueTbl[stk->Peek() - 'A'];
            stk->Pop();
            //pushes next available uppercase char to stack
            stk->Push(valueIdx + 'A');
            valueTbl[valueIdx] = GetTotal(value,num1,num2);
            valueIdx++;
        }
        i++;
    }

    //most recent total pushed to stack is held at valueIdx - 1
    int total = valueTbl[valueIdx - 1];
    delete stk;
    cout << total << endl;
    return total;
}

int Calc::GetTotal(char operation, int num1, int num2)
{
    switch (operation)
    {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num1 / num2;
    }
    return -1;
}