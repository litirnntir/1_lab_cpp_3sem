#include <iostream>
#include <math.h>
#include "Polynomial.cpp"

int main()
{
	try
	{
		bool exit = false;
		const int SIZE = 10;
		Polynomial polynomials[SIZE];

		while (!exit)
		{
			char choose;
			bool right_choose = false;

			std::cout << "\033[35;40m\033[1m" << "Menu:\n"
												 "1 - List of polynomials\n"
												 "2 - Create polynomial\n"
												 "3 - Get coefficient\n"
												 "4 - Set coefficient\n"
												 "5 - Polynomial addition and subtraction operators;;\n"
												 "6 - Operator of multiplication of a polynomial by a scalar\n"
												 "7 - Calculation of polynomial value at a given value of x.\n"
												 "8 - Find the integral of a polynomial.\n"
												 "9 - Exit\n" << "\033[0m\n";

			while (!right_choose)
			{
				fflush(stdin);
				scanf("%c", &choose);
				if (isdigit(choose))
				{
					int digit = atoi(&choose);
					if (digit > 11)
					{
						std::cout << "Incorrect number";
					}
					else
					{
						right_choose = true;
					}
				}
				else std::cout << "Enter the number\n";
			}

			switch (choose)
			{
			case '1':
			{
				for (int i = 0; i < SIZE; ++i)
				{
					std::cout << "\033[35;40m\033[1m" << i << "." << "\033[0m";
					polynomials[i].printCoeff();
				}
				std::cout <<"\n\n";
			}
				break;
			case '2':
			{
				int degree;
				int indexPolynomial;
				int chooseInput;

				std::cout << "\033[35;40m\033[1m" << "in which cell (1-10) to write?\n" << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &indexPolynomial);

				if (indexPolynomial < 0 || indexPolynomial > 10) throw "Invalid index";

				std::cout << "\033[35;40m\033[1m" << "Enter the maximum degree of the polynomial\n" << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &degree);

				std::cout << "\033[35;40m\033[1m" << "1.Manual input\n"
													 "2. Zero polynomial\n" << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &chooseInput);

				if (chooseInput == 1)
				{
					int element;
					polynomials[indexPolynomial] = Polynomial(degree);
					for (int i = 0; i < degree; ++i)
					{
						std::cout << "\033[35;40m\033[1m" << "Enter element with indexPolynomial " << i << ":"
								  << "\033[0m\n";
						fflush(stdin);
						scanf("%d", &element);
						polynomials[indexPolynomial].setCoeff(i, element);
					}
				}
				else if (chooseInput == 2)
				{
					polynomials[indexPolynomial] = Polynomial(degree);
				}
				else throw "Invalid number";

				polynomials[indexPolynomial].printCoeff();
				break;
			}
			case '3':
			{
				int degree;
				int indexPolynomial;

				std::cout << "\033[35;40m\033[1m" << "in which cell (1-10) to read?\n" << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &indexPolynomial);

				if (indexPolynomial < 0 || indexPolynomial > 10) throw "Invalid index";

				std::cout << "\033[35;40m\033[1m" << "Enter the degree at which to read the coefficient\n"
						  << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &degree);

				int coeff = polynomials[indexPolynomial][degree];

				std::cout << "coefficient with degree " << degree << ": " << coeff;

			}
				break;
			case '4':
			{
				int degree;
				int indexPolynomial;
				int coeff;

				std::cout << "\033[35;40\033[1m" << "in which cell (1-10) to write?\n" << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &indexPolynomial);

				if (indexPolynomial < 0 || indexPolynomial > 10) throw "Invalid index";

				std::cout << "\033[35;40m\033[1m" << "Enter the degree at which to change the coefficient\n"
						  << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &degree);

				std::cout << "\033[35;40m\033[1m" << "Enter the coefficient\n" << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &coeff);

				polynomials[indexPolynomial].setCoeff(degree - 1, coeff);
				polynomials[indexPolynomial].printCoeff();

				break;
			}
			case '5':
			{
				int first;
				int second;
				int third;
				int choose;

				std::cout << "\033[35;40m\033[1m" << "1. adding\n"
													 "2. subtraction\n" << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &choose);

				if (choose == 1)
				{
					std::cout << "\033[35;40m\033[1m" << "First polynomial (1-10):" << "\033[0m\n";

					fflush(stdin);
					scanf("%d", &first);

					std::cout << "\033[35;40m\033[1m" << "Second polynomial (1-10):" << "\033[0m\n";

					fflush(stdin);
					scanf("%d", &second);

					std::cout << "\033[35;40m\033[1m" << "Third polynomial (1-10):" << "\033[0m\n";

					fflush(stdin);
					scanf("%d", &third);

					polynomials[third] = Polynomial::additionPolynomials(polynomials[first], polynomials[second]);
					polynomials[first].printCoeff();
					std::cout << "\033[35;40m\033[1m" << "+++++++\n" << "\033[0m\n";
					polynomials[second].printCoeff();
					std::cout << "\033[35;40m\033[1m" << "=======\n" << "\033[0m\n";
					polynomials[third].printCoeff();
					break;
				}
				else if (choose == 2)
				{
					std::cout << "\033[35;40m\033[1m" << "First polynomial (1-10):" << "\033[0m\n";

					fflush(stdin);
					scanf("%d", &first);

					std::cout << "\033[35;40m\033[1m" << "Second polynomial (1-10):" << "\033[0m\n";

					fflush(stdin);
					scanf("%d", &second);

					std::cout << "\033[35;40m\033[1m" << "Third polynomial (1-10):" << "\033[0m\n";

					fflush(stdin);
					scanf("%d", &third);

					polynomials[third] = Polynomial::subtractionPolynomials(polynomials[first], polynomials[second]);
					polynomials[first].printCoeff();
					std::cout << "--------\n";
					polynomials[second].printCoeff();
					std::cout << "=======\n";
					polynomials[third].printCoeff();
					break;
				}
				else throw "Invalid number";
			}
			case '6':
			{
				int choose;
				int factor;

				std::cout << "\033[35;40m\033[1m" << "Polynomial (1-10):" << "\033[0m\n";

				fflush(stdin);
				scanf("%d", &choose);

				std::cout << "\033[35;40m\033[1m" << "Factor:" << "\033[0m\n";

				fflush(stdin);
				scanf("%d", &factor);

				polynomials[choose].multiplicationPolynomial(factor);
				polynomials[choose].printCoeff();
				break;
			}
			case '7':
			{
				int choose;
				int x;

				std::cout << "\033[35;40m\033[1m" << "Polynomial (1-10):" << "\033[0m\n";

				fflush(stdin);
				scanf("%d", &choose);

				std::cout << "\033[35;40m\033[1m" << "x:" << "\033[0m\n";

				fflush(stdin);
				scanf("%d", &x);

				std::cout << "\033[37;40m\033[1m" << "Value:" << polynomials[choose].valueCalculation(x) << "x:" << "\033[0m\n\n";
				break;
			}
			case '8':
			{
				int first;
				int second;

				std::cout << "\033[35;40m\033[1m" << "Enter the polynomial from which to take the integral (1-10)"
						  << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &first);

				std::cout << "\033[35;40m\033[1m" << "Enter the polynomial where to write the integral (1-10)"
						  << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &first);

				polynomials[second] = polynomials[first].findIntegral();
				polynomials[first].printCoeff();
				polynomials[second].printCoeff();
				break;
			}
			case '9':
			{
				exit = true;
				break;
			}
			}
		}
	}
	catch (const char* e)
	{
		std::cout << "\033[31;40m\033[1m" << (e) << "\033[0m\n";
	}
}
