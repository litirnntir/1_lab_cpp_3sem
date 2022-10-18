#include <iostream>
#include <math.h>

class Polynomial
{
 private:
	class Coeff
	{
	 public:
		Coeff* pNext; // указатель на следующий элемент
		int number; // Коеффициент

		Coeff(int data, Coeff* pNext = nullptr)
		{
			this->number = data;
			this->pNext = pNext;
		}
	};
	Coeff* odds;
	int highestDegree;

	void PrintInternal(Coeff* listHead, int degree = 1)
	{
		if (listHead->pNext != nullptr)
		{
			std::cout << listHead->number << "x^" << degree << " + ";
			PrintInternal(listHead->pNext, degree + 1);
		}
		else
		{
			std::cout << listHead->number << "x^" << degree << "\n";
		}
	}

	void PushBackInternal(Coeff*& listHead, int data)
	{
		if (odds == nullptr)
		{
			Coeff* tmp = new Coeff(data, nullptr);
			odds = tmp;
			return;
		}
		if (listHead->pNext != nullptr)
		{
			PushBackInternal(listHead->pNext, data);
		}
		else
		{
			Coeff* tmp = new Coeff(data, nullptr);
			listHead->pNext = tmp;
		}

	}

 public:

	int operator[](const int index)
	{
		if (index < 0 || index > highestDegree) throw "Invalid index";
		int counter = 0;
		Coeff* current = this->odds;
		while (current != nullptr)
		{
			if (counter == index)
			{
				return current->number;
			}
			current = current->pNext;
			counter++;
		}
		return 0;
	}

	void multiplicationPolynomial(int factor)
	{
		Coeff* tmp = odds;
		for (int i = 0; i < highestDegree; ++i)
		{
			this->setCoeff(i, tmp->number * factor);
			tmp = tmp->pNext;
		}
	}

	void setCoeff(int index, int coeff)
	{
		if (index < 0) throw "Invalid index";
		if (index > highestDegree)
		{
			for (int i = 0; i < abs(highestDegree - index); ++i)
			{
				this->pushBackElem(coeff);
			}
		}
		else
		{
			int counter = 0;
			Coeff* current = this->odds;
			while (current != nullptr)
			{
				if (counter == index)
				{
					current->number = coeff;
				}
				current = current->pNext;
				counter++;
			}
		}
	}

	void printCoeff()
	{
		PrintInternal(odds);
	}

	void pushBackElem(const int data)
	{
		PushBackInternal(odds, data);
	}

	// 0 0 0 0 0
	// 3 2 0 0 0 0 0
	static Polynomial additionPolynomials(Polynomial firstP, Polynomial secondP)
	{
		if (firstP.highestDegree > secondP.highestDegree)
		{
			Polynomial sum(firstP.highestDegree);

			for (int i = 0; i < secondP.highestDegree; ++i)
			{
				sum.setCoeff(i, firstP[i] + secondP[i]);
			}
			for (int i = secondP.highestDegree; i < firstP.highestDegree; ++i)
			{
				sum.setCoeff(i, firstP[i]);
			}
			return sum;
		}
		else
		{
			Polynomial sum(secondP.highestDegree);

			for (int i = 0; i < firstP.highestDegree; ++i)
			{
				sum.setCoeff(i, firstP[i] + secondP[i]);
			}
			for (int i = firstP.highestDegree; i < secondP.highestDegree; ++i)
			{
				sum.setCoeff(i, secondP[i]);
			}
			return sum;
		}
	}

	static Polynomial subtractionPolynomials(Polynomial firstP, Polynomial secondP)
	{
		if (firstP.highestDegree > secondP.highestDegree)
		{
			Polynomial sum(firstP.highestDegree);

			for (int i = 0; i < secondP.highestDegree; ++i)
			{
				sum.setCoeff(i, firstP[i] - secondP[i]);
			}
			for (int i = secondP.highestDegree; i < firstP.highestDegree; ++i)
			{
				sum.setCoeff(i, firstP[i]);
			}
			return sum;
		}
		else
		{
			Polynomial sum(secondP.highestDegree);

			for (int i = 0; i < firstP.highestDegree; ++i)
			{
				sum.setCoeff(i, firstP[i] - secondP[i]);
			}
			for (int i = firstP.highestDegree; i < secondP.highestDegree; ++i)
			{
				sum.setCoeff(i, secondP[i]);
			}
			return sum;
		}
	}

	int valueCalculation(int x)
	{
		Coeff* tmp = odds;
		int sum = 0;
		for (int i = 0; i < highestDegree; ++i)
		{
			sum += pow((odds->number * x), i + 1);
		}

		return sum;
	}

	Polynomial findIntegral()
	{
		Polynomial integral(highestDegree + 1);
		Coeff* tmp = odds;
		Coeff* tmpNew = integral.odds->pNext;

		for (int i = 1; i < highestDegree + 1; ++i)
		{
			tmpNew->number = pow(tmp->number, (i)) / (i + 1);
			tmpNew = tmpNew->pNext;
			tmp = tmp->pNext;
		}

		return integral;
	}

	Polynomial(int degree = 1)
	{
		if (degree < 1) throw "Error";
		highestDegree = degree;
		odds = nullptr;

		for (int i = 0; i < degree; ++i)
		{
			this->PushBackInternal(odds, 0);
		}
	}
};

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

			std::cout << "\033[33;40m\033[1m" << "Menu:\n"
												 "1 - List of polynomials\n"
												 "2 - Create polynomial\n"
												 "3 - Get coefficient\n"
												 "4 - Set coefficient\n"
												 "5 - Polynomial addition and subtraction operators;;\n"
												 "6 - Multiplication operator that performs scalar product of vectors;\n"
												 "7 - Operator of multiplication of a polynomial by a scalar\n"
												 "9 - Calculation of polynomial value at a given value of x.\n"
												 "10 - Find the integral of a polynomial.\n"
												 "11 - Exit\n" << "\033[0m\n";

			while (!right_choose)
			{
				fflush(stdin);
				scanf("%c", &choose);
				if (isdigit(choose))
				{
					int digit = atoi(&choose);
					if (digit > 3)
					{
						throw "Incorrect number";
					}
					else
					{
						right_choose = true;
					}
				}
				else throw "Enter the number\n";
			}

			switch (choose)
			{
			case '1':
			{
				for (int i = 0; i < SIZE; ++i)
				{
					std::cout << i << ".";
					polynomials[i].printCoeff();
				}
			}
				break;
			case '2':
			{
				int degree;
				int indexPolynomial;
				int chooseInput;

				std::cout << "\033[33;40m\033[1m" << "in which cell (1-10) to write?\n" << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &indexPolynomial);

				if (indexPolynomial < 0 || indexPolynomial > 10) throw "Invalid index";

				std::cout << "\033[33;40m\033[1m" << "Enter the maximum degree of the polynomial\n" << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &degree);

				std::cout << "\033[33;40m\033[1m" << "1.Manual input\n"
													 "2. Zero polynomial\n" << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &chooseInput);

				if (chooseInput == 1)
				{
					int element;
					polynomials[indexPolynomial] = Polynomial(degree);
					for (int i = 0; i < degree; ++i)
					{
						std::cout << "\033[33;40m\033[1m" << "Enter element with indexPolynomial " << i << ":"
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

				std::cout << "\033[33;40m\033[1m" << "in which cell (1-10) to read?\n" << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &indexPolynomial);

				if (indexPolynomial < 0 || indexPolynomial > 10) throw "Invalid index";

				std::cout << "\033[33;40m\033[1m" << "Enter the degree at which to read the coefficient\n"
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

				std::cout << "\033[33;40m\033[1m" << "in which cell (1-10) to write?\n" << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &indexPolynomial);

				if (indexPolynomial < 0 || indexPolynomial > 10) throw "Invalid index";

				std::cout << "\033[33;40m\033[1m" << "Enter the degree at which to change the coefficient\n"
						  << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &degree);

				std::cout << "\033[33;40m\033[1m" << "Enter the  coefficient\n" << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &coeff);

				polynomials[indexPolynomial].setCoeff(degree, coeff);
				polynomials[indexPolynomial].printCoeff();

				break;
			}
			case '5':
			{
				int degree;
				int indexPolynomial;
				int choose;

				std::cout << "\033[33;40m\033[1m" << "1. adding\n"
													 "2. subtraction\n" << "\033[0m\n";
				fflush(stdin);
				scanf("%d", &choose);

				if (choose == 1)
				{

				}
				if (choose == 2)
				{

				}
			}
			case '6':
			{

			}
			case '7':
			{

			}
			case '8':
			{

			}
			case '9':
			{

			}
			case '10':
			{

			}
			case '11':
			{

			}
			}
		}
	}
	catch (const char* e)
	{
		std::cout << "\033[31;40m\033[1m" << (e) << "\033[0m\n";
	}
}
