#include <iostream>
#include <string>

#include "Stack.h"

int main()
{
	std::string userExp;
	std::cout << "Enter your expession: " << std::endl;
	std::cin >> userExp;

	try
	{
		TStack postfix(userExp);
		std::cout << "Arithmetical expression: " << postfix.GetInfix() << std::endl;
		postfix.ToPostfix();
		std::cout << "Postfix form: " << postfix.GetPostfix() << std::endl;
		std::cout << "Result: " << postfix.Calculate() << std::endl;
	}
	catch (const char* n) { std::cout << n << std::endl; }

	system("pause");
	return 0;
}