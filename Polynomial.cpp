#include <iostream>
#include <math.h>

class Polynomial
{
 private:
	class Coeff
	{
	 public:
		Coeff* pNext;
		double number;
		int degree;

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

	void Set(const double data, const int degreeCoeff)
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
			Set(1, i);
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

	friend std::ostream& operator<<(std::ostream& os, Polynomial& obj)
	{
		obj.PrintPolynomial();
		return os;
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

	Polynomial operator*(const double scalar)
	{
		Polynomial result(0);
		Coeff* tmp = odds;
		for (int i = 0; i < numberOfCoeff; ++i)
		{
			result.Set(tmp->number * scalar, tmp->degree);
			tmp = tmp->pNext;
		}
		return result;
	}

	friend Polynomial operator*(const double scalar, const Polynomial& obj)
	{
		Polynomial result(0);
		Coeff* tmp = obj.odds;
		for (int i = 0; i < obj.numberOfCoeff; ++i)
		{
			result.Set(tmp->number * scalar, tmp->degree);
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
			integral.Set(tmp->number / (tmp->degree + 1), tmp->degree + 1);
			tmp = tmp->pNext;
		}

		return integral;
	}

	Polynomial operator+(Polynomial& obj)
	{
		Polynomial sum(0);
		Coeff* tmp1 = odds;
		while (tmp1)
		{
			Coeff* tmp2 = obj.odds;
			bool found = false;
			while (tmp2 and !found)
			{
				if (tmp1->degree == tmp2->degree)
				{
					sum.Set(tmp1->number + tmp2->number, tmp1->degree);
					found = true;
				}
				tmp2 = tmp2->pNext;
			}
			if (!found)
			{
				sum.Set(tmp1->number, tmp1->degree);
			}
			tmp1 = tmp1->pNext;
		}
		Coeff* tmp2 = obj.odds;
		while (tmp2)
		{
			tmp1 = sum.odds;
			bool found = false;
			while (tmp1 and !found)
			{
				if (tmp2->degree == tmp1->degree)
				{
					found = true;
				}
				tmp1 = tmp1->pNext;
			}
			if (!found)
			{
				sum.Set(tmp2->number, tmp2->degree);
			}
			tmp2 = tmp2->pNext;
		}

		return sum;

	};

	Polynomial operator-(Polynomial& obj)
	{
		Polynomial difference(0);
		Coeff* tmp1 = odds;
		while (tmp1)
		{
			Coeff* tmp2 = obj.odds;
			bool found = false;
			while (tmp2 and !found)
			{
				if (tmp1->degree == tmp2->degree)
				{
					if (tmp1->number - tmp2->number != 0)
					{
						difference.Set(tmp1->number - tmp2->number, tmp1->degree);
					}
					found = true;
				}
				tmp2 = tmp2->pNext;
			}
			if (!found)
			{
				difference.Set(tmp1->number, tmp1->degree);
			}
			tmp1 = tmp1->pNext;
		}

		Coeff* tmp2 = obj.odds;
		while (tmp2)
		{
			tmp1 = odds;
			bool found = false;
			while (tmp1 and !found)
			{
				if (tmp2->degree == tmp1->degree)
				{
					found = true;
				}
				tmp1 = tmp1->pNext;
			}
			if (!found)
			{
				difference.Set(tmp2->number, tmp2->degree);
			}
			tmp2 = tmp2->pNext;
		}

		return difference;

	};

	Polynomial& operator=(const Polynomial& right)
	{
		//проверка на самоприсваивание
		if (this == &right)
		{
			return *this;
		}
		delete[] odds;
		numberOfCoeff = right.numberOfCoeff;
		Coeff* tmp = right.odds;
		while (tmp)
		{
			Set(tmp->number, tmp->degree);
			tmp = tmp->pNext;
		}
		return *this;
	}
};