#ifndef __TSTACK_H___
#define __TSTACK_H___

#include <string>
#include <stack>

using namespace std;

class TStack
{
	string inFix;	// инфиксная форма
	string postFix; // постфиксная форма

	bool CheckOperationsAndOperands();  // проверка на соотношение операций и операнд
	bool CheckParenthesis();            // проверка на соотношение скобок
	bool IsNumber(char v);              // проверка на число
	bool IsOperator(char v);			// проверка на оператор
	void SplitString(string& str);      // разделение элементов строки пробелами
	int Priority(char a, char b);       // приоритеты операций между двумя операндами

public:
	string ToPostfix();					// перевод в постфиксную форму
	double Calculate();
	string GetInfix();                  // получить инфиксное выражение
	string GetPostfix();				// получить постфиксное выражение

	TStack(string tmp = "");            // конструктор
	TStack(TStack& v);					// конструктор копирования
};

#endif