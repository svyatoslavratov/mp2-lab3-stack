#include "Stack.h"

#include <vector>
#include <iostream>

using namespace std;

TStack::TStack(string tmp)
	: inFix(tmp), postFix("") {}

TStack::TStack(TStack& v)
	:inFix(v.inFix), postFix(v.postFix) {}

bool TStack::CheckOperationsAndOperands()
{
	for (int i = 0; i < inFix.size(); i++)
	{
		if (!IsNumber(inFix[i]) && !IsOperator(inFix[i]))
		{
			return false;
		}
	}

	int Operands = 0;
	int Operations = 0;

	for (int i = 0; i < inFix.size(); i++)
	{
		if (inFix[i] == '(' || inFix[i] == ')')
		{
			i++;
			if (i == inFix.size())
			{
				break;
			}
		}

		if (inFix[i] == '-' || inFix[i] == '+' || inFix[i] == '/' || inFix[i] == '*' || inFix[i] == '^')
		{
			Operations++;
		}

		if (!IsOperator(inFix[i]))
		{
			while (!IsOperator(inFix[i]))
			{
				i++;
				if (i == inFix.size())
				{
					break;
				}
			}
			i--;
			Operands++;
		}
	}

	if (Operands == Operations + 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool TStack::CheckParenthesis()
{
	int LeftParenthesis = 0;
	int	RightParenthesis = 0;

	for (int i = 0; i < inFix.size(); i++)
	{
		if (inFix[i] == '(')
		{
			LeftParenthesis++;
		}
		else if (inFix[i] == ')')
		{
			RightParenthesis++;
		}
			

		if (RightParenthesis > LeftParenthesis)
		{
			throw exception();
		}
	}
	if (LeftParenthesis == RightParenthesis)
	{
		return true;
	}
	else {
		return false;
	}
}

bool TStack::IsNumber(char v)
{
	if (int(v) >= 48 && int(v) <= 57)
	{
		return true;
	}

	return false;
}

bool TStack::IsOperator(char v)
{
	if (v == '~' || v == '-' || v == '+' || v == '/' || v == '*' || v == '^' || v == '(' || v == ')')
	{
		return true;
	}
	else {
		return false;
	}
}

void TStack::SplitString(string& str)
{
	if (str.empty())
	{
		return;
	}

	if (str.back() != ' ')
	{
		str += ' ';
	}
}

int TStack::Priority(char a, char b)
{
	if (a == '~')
	{
		return 1;
	}

	if (b == '~')
	{
		return -1;
	}

	if ((a == '*' || a == '/') && (b == '+' || b == '-'))
	{
		return 1;
	}

	if ((a == '+' || a == '-') && (b == '*' || b == '/'))
	{
		return -1;
	}

	if ((a == '*' || a == '/') && (b == '*' || b == '/') || (a == '+' || a == '-') && (b == '+' || b == '-'))
	{
		return 0;
	}

	if (b == '^' && a != '~')
	{
		return -1;
	}

	if (a == '^' && b != '~')
	{
		return 1;
	}

	throw exception("priority error");
}

string TStack::ToPostfix()
{
	if (!CheckParenthesis())
	{
		throw exception("error");
	}


	for (int j = 0; j < inFix.size(); j++)
	{
		if (inFix[0] == '-')
		{
			inFix[0] = '~';
		}

		if (inFix[j] == '-' && (inFix[j - 1] == '(' || inFix[j - 1] == '~'))
		{
			inFix[j] = '~';
		}
	}

	int count = -1;
	stack<char> Set;

	for (int i = 0; i < inFix.size(); i++)
	{
		if (IsOperator(inFix[i]))
		{
			if ((Set.empty() || inFix[i] == '(') && inFix[i] != '~')
			{
				if (inFix[i] != '(')
				{
					SplitString(postFix);
				}

				Set.push(inFix[i]);
				count++;
				continue;
			}
			else if ((Set.empty() || Set.top() == '~') && inFix[i] == '~')
			{
				Set.push(inFix[i]);
				count++;
				continue;
			}
			else if (inFix[i] == ')')
			{
				while (Set.top() != '(')
				{
					SplitString(postFix);
					postFix += Set.top();
					Set.pop();
					count--;
				}
				Set.pop();
				count--;
			}
			else if ((Set.top()) == '(' || Priority(inFix[i], Set.top()) == 1)
			{
				Set.push(inFix[i]);
				SplitString(postFix);
				count++;
			}
			else if (Priority(inFix[i], Set.top()) == -1)
			{
				SplitString(postFix);
				while (!(Set.empty()))
				{
					if (Set.top() == '(')
					{
						break;
					}

					postFix += Set.top();
					Set.pop();
					SplitString(postFix);
					count--;
				}
				Set.push(inFix[i]);
				count++;
			}
			else if (Priority(inFix[i], Set.top()) == 0)
			{
				SplitString(postFix);
				postFix += Set.top();
				Set.pop();
				Set.push(inFix[i]);
				SplitString(postFix);
			}
		}
		else {
			postFix += inFix[i];
		}
			
		if (i == inFix.size() - 1)
		{
			for (count; count >= 0; count--)
			{
				SplitString(postFix);
				postFix += Set.top();
				Set.pop();
			}
		}
	}
	return postFix;
}

double TStack::Calculate()
{
	if (!CheckOperationsAndOperands() || postFix == "")
	{
		throw exception("error");
	}

	stack<double> Result;
	string str;

	for (int i = 0; i < postFix.size(); i++)
	{
		if (postFix[i] == ' ')
		{
			continue;
		}

		if (!IsOperator(postFix[i]))
		{
			while (postFix[i] != ' ')
			{
				str += postFix[i];
				i++;
			}
			Result.push(atof(str.c_str()));
			str = "";
		}
		else
		{
			if (postFix[i] == '~')
			{
				double a = Result.top();
				Result.pop();
				Result.push(-a);
				continue;
			}

			double a = Result.top();
			Result.pop();

			double b = Result.top();
			Result.pop();

			if (postFix[i] == '+')
			{
				Result.push(b + a);
			}
				
			else if (postFix[i] == '-')
			{
				Result.push(b - a);
			}
			else if (postFix[i] == '*')
			{
				Result.push(b * a);
			}
			else if (postFix[i] == '/')
			{
				if (a == 0.0)
				{
					throw exception("error");
				}
				Result.push(b / a);
			}
			else if (postFix[i] == '^')
			{
				Result.push(pow(b, a));
			}
		}
	}

	return Result.top();
}

string TStack::GetInfix()
{
	return inFix;
}

string TStack::GetPostfix()
{
	return postFix;
}
