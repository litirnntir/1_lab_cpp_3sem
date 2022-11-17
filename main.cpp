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
	void PushBack(const int data, const int degreeUpdate)
	{
	}

	Polynomial(int degree = 1)
	{
		if (degree < 1) throw "Error";
		highestDegree = degree;
		odds = nullptr;

		for (int i = 0; i < highestDegree; ++i)
		{
			this->PushBack(1, i);
		}
	}

	~Polynomial()
	{
		delete[] odds;
	}

};

int main()
{
	Polynomial a = Polynomial(5);
	return 0;
}