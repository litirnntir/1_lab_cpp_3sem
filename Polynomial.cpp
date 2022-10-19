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
			std::cout << "\033[35;40m\033[1m" << listHead->number << "x^" << degree << " + " << "\033[0m";
			PrintInternal(listHead->pNext, degree + 1);
		}
		else
		{
			std::cout << "\033[35;40m\033[1m" << listHead->number << "x^" << degree  << "\033[0m\n";
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
		if (index < 0 || index > highestDegree) throw "Invalid index";
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
		if (highestDegree == 1 || odds->number == 0)
		{
			Polynomial integral(highestDegree);
			return integral;
		}
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