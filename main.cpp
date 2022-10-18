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

	void PrintInternal(Coeff* listHead, int degree=1)
	{
		if (listHead->pNext != nullptr)
		{
			std::cout  << listHead->number << "x^" <<  degree << " + ";
			PrintInternal(listHead->pNext, degree + 1);
		}
		else
		{
			std::cout  << listHead->number << "^" <<  degree << "\n";
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
		Coeff *current = this->odds;
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
		if (index < 0 || index > highestDegree) throw "Invalid index";
		int counter = 0;
		Coeff *current = this->odds;
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

	void PrintCoeff()
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

	Polynomial(int degree=1)
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
		Polynomial first(3);
		first.setCoeff(0, 1);
		first.setCoeff(1, 1);
		first.setCoeff(2, 1);
		first.PrintCoeff();
		Polynomial second(3);
		second.setCoeff(0, 21);
		second.setCoeff(1, 22);
		second.setCoeff(2, 255);
		second.PrintCoeff();
		Polynomial third = Polynomial::subtractionPolynomials(first, second);
		third.PrintCoeff();
		third.multiplicationPolynomial(10);
		third.PrintCoeff();

		std::cout << first.valueCalculation(1);
	}
	catch (const char* e)
	{
		std::cout << "\033[31;40m\033[1m" << (e) << "\033[0m\n";
	}
}
