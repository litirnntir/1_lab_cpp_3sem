#include <iostream>
#include <math.h>
#include <complex>

template<typename T>
class Polynomial
{
 private:
	class Coeff
	{
	 public:
		Coeff* pNext;
		T number;
		int degree;

		Coeff(T number, int degree, Coeff* pNext = nullptr)
		{
			this->number = number;
			this->pNext = pNext;
			this->degree = degree;
		}
	};
	Coeff* odds;
	int numberOfCoeff;
 public:

	int GetNumberOfCoeff()
	{
		return numberOfCoeff;
	}

	void Set(const T data, const int degreeCoeff)
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
			if (degreeCoeff == tmp->degree)
			{
				tmp->number = data;
				return;
			}
			tmp->pNext = node;
		}
		numberOfCoeff++;
	}

	Polynomial<T>(int degree = 0)
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

	Polynomial<T>(const Polynomial<T>& obj)
	{
		numberOfCoeff = obj.numberOfCoeff;
		Coeff* tmp = obj.odds;
		while (tmp)
		{
			Set(tmp->number, tmp->degree);
			tmp = tmp->pNext;
		}
	}

	~Polynomial<T>()
	{
		delete[] odds;
	}

	void PrintPolynomial()
	{
		Coeff* tmp = odds;
		if (numberOfCoeff != 0)
		{
			while (tmp)
			{
				if (tmp->pNext) std::cout << tmp->number << "x^" << tmp->degree << " + ";
				else std::cout << tmp->number << "x^" << tmp->degree << std::endl;
				tmp = tmp->pNext;
			}
		}
		else
		{
			std::cout << "All coefficients is 0" << std::endl;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, Polynomial<T>& obj)
	{
		obj.PrintPolynomial();
		return os;
	}

	T operator[](const int degree)
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

	Polynomial<T> operator*(const T scalar)
	{
		Polynomial<T> result(0);
		Coeff* tmp = odds;
		for (int i = 0; i < numberOfCoeff; ++i)
		{
			result.Set(tmp->number * scalar, tmp->degree);
			tmp = tmp->pNext;
		}
		return result;
	}

	friend Polynomial<T> operator*(const T scalar, const Polynomial<T>& obj)
	{
		Polynomial<T> result(0);
		Coeff* tmp = obj.odds;
		for (int i = 0; i < obj.numberOfCoeff; ++i)
		{
			result.Set(tmp->number * scalar, tmp->degree);
			tmp = tmp->pNext;
		}
		return result;
	}

	T ValueCalculation(T x)
	{
		Coeff* tmp = odds;
		T sum = 0;
		while (tmp)
		{
			sum += tmp->number * (pow(x, tmp->degree));
			tmp = tmp->pNext;
		}

		return sum;
	}

	Polynomial<T> FindIntegral()
	{
		Polynomial<T> integral(0);
		Coeff* tmp = odds;

		while (tmp)
		{
			if ((tmp->number / (tmp->degree + 1)) != 0)
			{
				integral.Set(tmp->number / (tmp->degree + 1), tmp->degree + 1);
			}
			tmp = tmp->pNext;
		}

		return integral;
	}

	Polynomial<T> operator+(Polynomial<T>& obj)
	{
		Polynomial<T> sum(0);
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

	Polynomial<T> operator-(Polynomial<T>& obj)
	{
		Polynomial<T> difference(0);
		Coeff* tmp1 = odds;
		if (obj.numberOfCoeff == 0)
		{
			while (tmp1)
			{
				difference.Set(tmp1->number, tmp1->degree);
				tmp1 = tmp1->pNext;
			}
		}
		else
		{
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
					difference.Set(tmp1->number * -1, tmp1->degree);
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
		}

		return difference;

	};

	Polynomial<T>& operator=(const Polynomial<T>& right)
	{
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

	bool operator==(const Polynomial<T>& right)
	{
		if (this == &right)
		{
			return true;
		}
		if (numberOfCoeff != right.numberOfCoeff)
		{
			return false;
		}
		else
		{
			Coeff* tmp1 = odds;
			while (tmp1)
			{
				Coeff* tmp2 = right.odds;
				bool equal = false;
				while (tmp2)
				{
					if (tmp1->number == tmp2->number && tmp1->degree == tmp2->degree)
					{
						equal = true;
					}
					tmp2 = tmp2->pNext;
				}
				if (!equal)
				{
					return false;
				}
				tmp1 = tmp1->pNext;
			}
		}
		return true;
	}

	bool operator>(Polynomial<T>& right)
	{
		if (this == &right)
		{
			return false;
		}
		if (numberOfCoeff != right.numberOfCoeff)
		{
			return false;
		}
		else
		{
			if (ValueCalculation(1) > right.ValueCalculation(1))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	bool operator<(Polynomial<T>& right)
	{
		if (this == &right)
		{
			return false;
		}
		if (numberOfCoeff != right.numberOfCoeff)
		{
			return false;
		}
		else
		{
			if (ValueCalculation(1) < right.ValueCalculation(1))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
};

template<class T>
class Polynomial<std::complex<T>>
{
 private:
	class Coeff
	{
	 public:
		Coeff* pNext;
		std::complex<T> number;
		int degree;

		Coeff(std::complex<T> number, int degree, Coeff* pNext = nullptr)
		{
			this->number = number;
			this->pNext = pNext;
			this->degree = degree;
		}
	};
	Coeff* odds;
	int numberOfCoeff;
 public:

	int GetNumberOfCoeff()
	{
		return numberOfCoeff;
	}

	void Set(const std::complex<T> data, const int degreeCoeff)
	{
		if (data.imag() == 0 && data.real() == 0) throw "Coefficient cannot be equal to zero";
		if (degreeCoeff < 0) throw "Degree cannot be less zero";
		Coeff* node = new Coeff(data, degreeCoeff);
		if (odds == nullptr)
		{
			odds = node;
		}
		else
		{
			Coeff* tmp = odds;
			if (tmp->pNext != nullptr)
			{
				while (tmp->pNext)
				{
					if (degreeCoeff == tmp->degree)
					{
						tmp->number = data;
						return;
					}
					tmp = tmp->pNext;
				}
			}
			if (degreeCoeff == tmp->degree)
			{
				tmp->number = data;
				return;
			}
			tmp->pNext = node;
		}
		numberOfCoeff++;
	}

	Polynomial<std::complex<T>>(int degree = 0)
	{
		numberOfCoeff = 0;
		if (degree < 0) throw "Error";
		odds = nullptr;

		if (degree == 0) return;

		for (int i = 0; i <= degree; ++i)
		{
			std::complex<T> data = std::complex<T>(1, 1);
			Set(data, i);
		}
	}

	Polynomial<std::complex<T>>(const Polynomial<std::complex<T>>& obj)
	{
		numberOfCoeff = obj.numberOfCoeff;
		Coeff* tmp = obj.odds;
		while (tmp)
		{
			Set(tmp->number, tmp->degree);
			tmp = tmp->pNext;
		}
	}

	~Polynomial<std::complex<T>>()
	{
		delete[] odds;
	}

	void PrintPolynomial()
	{
		Coeff* tmp = odds;
		if (numberOfCoeff != 0)
		{
			while (tmp)
			{
				if (tmp->pNext) std::cout << tmp->number << "x^" << tmp->degree << " + ";
				else std::cout << tmp->number << "x^" << tmp->degree << std::endl;
				tmp = tmp->pNext;
			}
		}
		else
		{
			std::cout << "All coefficients is 0" << std::endl;
		}
	}

	std::complex<T> operator[](const int degree)
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

	Polynomial<std::complex<T>> operator*(const std::complex<T> scalar)
	{
		Polynomial<std::complex<T>> result(0);
		Coeff* tmp = odds;
		for (int i = 0; i < numberOfCoeff; ++i)
		{
			result.Set((std::complex<T>)tmp->number * (std::complex<T>)scalar, tmp->degree);
			tmp = tmp->pNext;
		}
		return result;
	}

	friend Polynomial<std::complex<T>> operator*(const std::complex<T> scalar, const Polynomial<std::complex<T>>& obj)
	{
		Polynomial<std::complex<T>> result(0);
		Coeff* tmp = obj.odds;
		for (int i = 0; i < obj.numberOfCoeff; ++i)
		{
			result.Set(tmp->number * (std::complex<T>)scalar, tmp->degree);
			tmp = tmp->pNext;
		}
		return result;
	}

	std::complex<T> ValueCalculation(std::complex<T> x)
	{
		Coeff* tmp = odds;
		std::complex<T> sum = std::complex<T>(0, 0);
		while (tmp)
		{
			std::complex<T> powX = (std::complex<T>)std::pow(x,  tmp->degree) * (std::complex<T>)tmp->number;
			sum = sum + powX;
			tmp = tmp->pNext;
		}
		return sum;
	}

	Polynomial<std::complex<T>> FindIntegral()
	{
		Polynomial<std::complex<T>> integral(0);
		Coeff* tmp = odds;

		while (tmp)
		{
			std::complex<T>
				a = std::complex<T>(tmp->number.real() / (tmp->degree + 1), tmp->number.imag() / (tmp->degree + 1));
			integral.Set(a, tmp->degree + 1);
			tmp = tmp->pNext;
		}

		return integral;
	}

	Polynomial<std::complex<T>> operator+(Polynomial<std::complex<T>>& obj)
	{
		Polynomial<std::complex<T>> sum(0);
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

	Polynomial<std::complex<T>> operator-(Polynomial<std::complex<T>>& obj)
	{
		Polynomial<std::complex<T>> difference(0);
		Coeff* tmp1 = odds;
		if (obj.numberOfCoeff == 0)
		{
			while (tmp1)
			{
				difference.Set(tmp1->number, tmp1->degree);
				tmp1 = tmp1->pNext;
			}
		}
		else
		{
			while (tmp1)
			{
				Coeff* tmp2 = obj.odds;
				bool found = false;
				while (tmp2 and !found)
				{
					if (tmp1->degree == tmp2->degree)
					{
						if ((tmp1->number - tmp2->number).real() != 0 and (tmp1->number - tmp2->number).imag() != 0)
						{
							difference.Set(tmp1->number - tmp2->number, tmp1->degree);
						}
						found = true;
					}
					tmp2 = tmp2->pNext;
				}
				if (!found)
				{
					std::complex<T> a = std::complex<T>(tmp1->number.real() * -1, tmp1->number.imag() * -1);
					difference.Set(a, tmp1->degree);
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
		}


		return difference;

	};

	Polynomial<std::complex<T>>& operator=(const Polynomial<std::complex<T>>& right)
	{
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

	bool operator==(const Polynomial<std::complex<T>>& right)
	{
		if (this == &right)
		{
			return true;
		}
		if (numberOfCoeff != right.numberOfCoeff)
		{
			return false;
		}
		else
		{
			Coeff* tmp1 = odds;
			while (tmp1)
			{
				Coeff* tmp2 = right.odds;
				bool equal = false;
				while (tmp2)
				{
					if (tmp1->number.real() == tmp2->number.real() && tmp1->number.imag() == tmp2->number.imag()
						&& tmp1->degree == tmp2->degree)
					{
						equal = true;
					}
					tmp2 = tmp2->pNext;
				}
				if (!equal)
				{
					return false;
				}
				tmp1 = tmp1->pNext;
			}
		}
		return true;
	}

	bool operator>(Polynomial<std::complex<T>>& right)
	{
		if (this == &right)
		{
			return false;
		}
		if (numberOfCoeff != right.numberOfCoeff)
		{
			return false;
		}
		else
		{
			if (ValueCalculation(1).real() > right.ValueCalculation(1).real()
				&& ValueCalculation(1).imag() > right.ValueCalculation(1).imag())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	bool operator<(Polynomial<std::complex<T>>& right)
	{
		if (this == &right)
		{
			return false;
		}
		if (numberOfCoeff != right.numberOfCoeff)
		{
			return false;
		}
		else
		{
			std::complex<T> a = std::complex<T>(1, 1);
			if (ValueCalculation(a).real() < right.ValueCalculation(a).real()
				&& ValueCalculation(a).imag() < right.ValueCalculation(1).imag())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
};