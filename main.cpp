#include <iostream>
#include <math.h>

class Polynomial
{
 private:
	class Coeff
	{
	 public:
		Coeff* pNext; // указатель на следующий элемент
		double number; // Коеффициент
		int degree; // Степень

		Coeff(double data, int degreeCoeff, Coeff* pNext = nullptr)
		{
			this->number = data;
			this->pNext = pNext;
			this->degree = degreeCoeff;
		}
	};
	Coeff* odds;
	int numberOfCoeff;
 public:

	void AddCoeff(const double data, const int degreeCoeff)
	{
		if (data == 0) throw "Coefficient cannot be equal to zero";
		if (degreeCoeff < 0) throw "Degree cannot be less zero";
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
				if (degreeCoeff == tmp->degree)
				{
					tmp->number = data;
					return;
				}
				tmp = tmp->pNext;
			}
			tmp->pNext = node;
		}
		numberOfCoeff++;
	}

	Polynomial(int degree = 0)
	{
		numberOfCoeff = 0;
		if (degree < 0) throw "Error";
		odds = nullptr;

		if (degree == 0) return;

		for (int i = 0; i <= degree; ++i)
		{
			AddCoeff(1, i);
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
			if (tmp->pNext) std::cout << tmp->number << "x^" << tmp->degree << " + ";
			else std::cout << tmp->number << "x^" << tmp->degree << std::endl;
			tmp = tmp->pNext;
		}
	}

	double operator[](const int degree)
	{
		Coeff* tmp = this->odds;
		while (tmp != nullptr)
		{
			if (degree == tmp->degree)
			{
				return tmp->number;
			}
			tmp = tmp->pNext;
		}
		return 0;
	}

	friend std::ostream& operator<<(std::ostream& os, Polynomial& obj)
	{
		obj.PrintPolynomial();
		return os;
	}

	Polynomial operator*(double scalar)
	{
		Polynomial result(0);
		Coeff* tmp = odds;
		for (int i = 0; i < numberOfCoeff; ++i)
		{
			result.AddCoeff(tmp->number * scalar, tmp->degree);
			tmp = tmp->pNext;
		}
		return result;
	}

	double ValueCalculation(double x)
	{
		Coeff* tmp = odds;
		double sum = 0;
		for (int i = 0; i < numberOfCoeff; ++i)
		{
			sum += pow((odds->number * x), i + 1);
		}

		return sum;
	}

	Polynomial FindIntegral()
	{
		Polynomial integral(0);
		Coeff* tmp = odds;

		while (tmp)
		{
			integral.AddCoeff(tmp->number/(tmp->degree + 1), tmp->degree + 1);
			tmp = tmp->pNext;
		}

		return integral;
	}

};

int main()
{
	Polynomial a = Polynomial(8);
	Polynomial b = Polynomial(5);
	std::cout << b;
	Polynomial c = b.FindIntegral();
	std::cout << c;
	return 0;
}