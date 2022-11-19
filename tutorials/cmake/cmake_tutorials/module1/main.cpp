#include <iostream>

#include "addition.hpp"
#include "soustraction.hpp"
#include "printer.hpp"

int main(){

	float first_no{}, second_no{}, result_add{}, result_minus{};

	std::cout<<"Enter first number? >> ";
	std::cin>>first_no;

	std::cout<<"Enter second number? >> ";
	std::cin>>second_no;

	result_add = addition(first_no, second_no);
	result_minus = soustraction(first_no, second_no);

	printResult("Addition", result_add);
	printResult("Soustraction", result_minus);

	return 0;
}
