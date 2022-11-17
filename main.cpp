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
		int degree; // Степень

		Coeff(int data, int degreeCoeff, Coeff* pNext = nullptr)
		{
			this->number = data;
			this->pNext = pNext;
			this->degree = degreeCoeff;
		}
	};
	Coeff* odds;
	int highestDegree;
 public:

	void PushBack(const int data, const int degreeCoeff)
	{
		Coeff* node = new Coeff(data, degreeCoeff);

		if (odds == nullptr)
		{
			odds = node;
		}
		else
		{
			Coeff* tmp = odds;
			while (tmp->pNext)
			{
				tmp = tmp->pNext;
			}
			tmp->pNext = node;
		}
		highestDegree++;
	}

	Polynomial(int degree = 1)
	{
		if (degree < 1) throw "Error";
		odds = nullptr;

		for (int i = 0; i <= degree; ++i)
		{
			PushBack(1, i);
		}
	}

	~Polynomial()
	{
		delete[] odds;
	}

	void PrintPolynomial()
	{
		Coeff* tmp = odds;
		while (tmp)
		{
			std::cout << tmp->number << "^" << tmp->degree << "   ";
			tmp = tmp->pNext;
		}
	}

};

int main()
{
	Polynomial a = Polynomial(8);
	a.PrintPolynomial();
	return 0;
}