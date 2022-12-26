#include <iostream>
#include <math.h>
#include <complex>
#include <locale>
#include <iomanip>
#include <complex>
#include <list>
#include <iterator>

template<typename T>
class Polynomial
{
 private:
	template<typename T2>
	class Coeff
	{
	 public:
		T2 number;
		int degree;

		Coeff(T number, int degree)
		{
			this->number = number;
			this->degree = degree;
		}
	};
	std::list<Coeff<T>> odds;
	int numberOfCoeff;
 public:
	Polynomial(const Polynomial<T>& src) = default;
	Polynomial<T>& operator=(const Polynomial<T>& src) = default;
	~Polynomial() = default;

	int GetNumberOfCoeff()
	{
		return numberOfCoeff;
	}

	auto begin()
	{
		return odds.begin();
	}
	auto end()
	{
		return odds.end();
	}

	void Set(const T data, const int degreeCoeff)
	{
		if (data == 0) throw "Coefficient cannot be equal to zero";
		if (degreeCoeff < 0) throw "Degree cannot be less zero";

		for (auto i = begin(); i != end(); ++i)
		{
			if (i->degree == degreeCoeff)
			{
				i->number = data;
				return;
			}
		}
		odds.push_back(Coeff<T>(data, degreeCoeff));
		numberOfCoeff++;
	}

	Polynomial<T>(int degree = 0)
	{
		numberOfCoeff = 0;
		if (degree < 0) throw "Error";

		if (degree == 0) return;

		for (int i = 0; i <= degree; ++i)
		{
			Set(1, i);
		}
	}

	void PrintPolynomial()
	{

		if (numberOfCoeff != 0)
		{
			for (auto i = begin(); i != end(); ++i)
			{
				if (i != std::prev(end())) std::cout << i->number << "x^" << i->degree << " + ";
				else std::cout << i->number << "x^" << i->degree << std::endl;
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
		for (auto i = begin(); i != end(); ++i)
		{
			if (i->degree == degree) return i->number;
		}
		return 0;
	}

	Polynomial<T> operator*(const T scalar)
	{
		Polynomial<T> result(0);
		for (auto i = begin(); i != end(); ++i)
		{
			result.Set(i->number * scalar, i->degree);
		}
		return result;
	}

	friend Polynomial<T> operator*(const T scalar, const Polynomial<T>& obj)
	{
		Polynomial<T> result(0);
		for (auto i = obj.begin(); i != obj.end(); ++i)
		{
			result.Set(i->number * scalar, i->degree);
		}
		return result;
	}

	T ValueCalculation(T x)
	{
		T sum = 0;
		for (auto i = begin(); i != end(); ++i)
		{
			sum += i->number * (pow(x, i->degree));
		}
		return sum;
	}

	Polynomial<T> FindIntegral()
	{
		Polynomial<T> integral(0);
		for (auto i = begin(); i != end(); ++i)
		{
			if ((i->number / (i->degree + 1)) != 0)
			{
				integral.Set(i->number / (i->degree + 1), i->degree + 1);
			}
		}
		return integral;
	}

	Polynomial<T> operator+(Polynomial<T>& obj)
	{
		Polynomial<T> sum(0);

		for (auto i = begin(); i != end(); ++i)
		{
			bool found = false;
			auto j = obj.begin();
			while ((j != obj.end()) && !found)
			{
				if (i->degree == j->degree)
				{
					sum.Set(i->number + j->number, i->degree);
					found = true;
				}
				j++;
			}
			if (!found)
			{
				sum.Set(i->number, i->degree);
			}
		}

		for (auto j = obj.begin(); j != obj.end(); ++j)
		{
			auto i = sum.begin();
			bool found = false;
			while ((i != sum.end()) && !found)
			{
				if (j->degree == i->degree)
				{
					found = true;
				}
				i++;
			}
			if (!found)
			{
				sum.Set(j->number, j->degree);
			}
		}

		return sum;

	};

	Polynomial<T> operator-(Polynomial<T>& obj)
	{
		Polynomial<T> difference(0);

		for (auto i = begin(); i != end(); ++i)
		{
			bool found = false;
			auto j = obj.begin();
			while ((j != obj.end()) && !found)
			{
				if (i->degree == j->degree)
				{
					if (i->number - j->number != 0)
					{
						difference.Set(i->number - j->number, i->degree);
					}
					found = true;
				}
				j++;
			}
			if (!found)
			{
				difference.Set(i->number * -1, i->degree);
			}
		}

		for (auto j = obj.begin(); j != obj.end(); ++j)
		{
			auto i = this->begin();
			bool found = false;
			while ((i != difference.end()) && !found)
			{
				if (j->degree == i->degree)
				{
					found = true;
				}
				i++;
			}
			if (!found)
			{
				difference.Set(j->number, j->degree);
			}
		}

		return difference;
	}

	bool operator==(Polynomial<T>& right)
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
			for (auto i = begin(); i != end(); ++i)
			{
				bool equal = false;
				for (auto j = right.begin(); i != right.end(); ++i)
				{
					if (i->number == j->number && i->degree == j->degree)
					{
						equal = true;
					}
					j++;
				}
				if (!equal)
				{
					return false;
				}
				i++;
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
	template<typename T2>
	class Coeff
	{
	 public:
		std::complex<T2> number;
		int degree;

		Coeff(std::complex<T> number, int degree)
		{
			this->number = number;
			this->degree = degree;
		}
	};
	std::list<Coeff<T>> odds;
	int numberOfCoeff;
 public:

	Polynomial(const Polynomial<std::complex<T>>& src) = default;
	Polynomial<std::complex<T>>& operator=(const Polynomial<std::complex<T>>& src) = default;
	~Polynomial() = default;

	int GetNumberOfCoeff()
	{
		return numberOfCoeff;
	}

	auto begin()
	{
		return odds.begin();
	}
	auto end()
	{
		return odds.end();
	}

	void Set(const std::complex<T> data, const int degreeCoeff)
	{
		if (data.real() == 0 && data.imag() == 0) throw "Coefficient cannot be equal to zero";
		if (degreeCoeff < 0) throw "Degree cannot be less zero";

		for (auto i = begin(); i != end(); ++i)
		{
			if (i->degree == degreeCoeff)
			{
				i->number = data;
				return;
			}
		}
		odds.push_back(Coeff<T>(data, degreeCoeff));
		numberOfCoeff++;
	}

	Polynomial<std::complex<T>>(int degree = 0)
	{
		numberOfCoeff = 0;
		if (degree < 0) throw "Error";

		if (degree == 0) return;

		for (int i = 0; i <= degree; ++i)
		{
			std::complex<T> data = std::complex<T>(1, 1);
			Set(data, i);
		}
	}

	void PrintPolynomial()
	{

		if (numberOfCoeff != 0)
		{
			for (auto i = begin(); i != end(); ++i)
			{
				if (i != std::prev(end())) std::cout << i->number << "x^" << i->degree << " + ";
				else std::cout << i->number << "x^" << i->degree << std::endl;
			}
		}

		else
		{
			std::cout << "All coefficients is 0" << std::endl;
		}
	}

	std::complex<T> operator[](const int degree)
	{
		for (auto i = begin(); i != end(); ++i)
		{
			if (i->degree == degree) return i->number;
		}
		return 0;
	}

	Polynomial<std::complex<T>> operator*(std::complex<T> scalar)
	{
		Polynomial<std::complex<T>> result(0);
		for (auto i = begin(); i != end(); ++i)
		{
			result.Set((std::complex<T>)i->number * (std::complex<T>)scalar, i->degree);
		}
		return result;
	}

	friend Polynomial<std::complex<T>> operator*(std::complex<T> scalar, Polynomial<std::complex<T>>& obj)
	{
		Polynomial<std::complex<T>> result(0);
		for (auto i = obj.begin(); i != obj.end(); ++i)
		{
			result.Set((std::complex<T>)i->number * (std::complex<T>)scalar, i->degree);
		}
		return result;
	}

	std::complex<T> ValueCalculation(std::complex<T> x)
	{
		std::complex<T> sum = std::complex<T>(0, 0);
		for (auto i = begin(); i != end(); ++i)
		{
			std::complex<T> powX = (std::complex<T>)std::pow(x, i->degree) * (std::complex<T>)i->number;
			sum = sum + powX;
		}
		return sum;
	}

	Polynomial<std::complex<T>> FindIntegral()
	{
		Polynomial<std::complex<T>> integral(0);
		for (auto i = begin(); i != end(); ++i)
		{
			std::complex<T> a = std::complex<T>(i->number.real() / (i->degree + 1), i->number.imag() / (i->degree + 1));
			integral.Set(a, i->degree + 1);
		}
		return integral;
	}

	Polynomial<std::complex<T>> operator+(Polynomial<std::complex<T>>& obj)
	{
		Polynomial<std::complex<T>> sum(0);

		for (auto i = begin(); i != end(); ++i)
		{
			bool found = false;
			auto j = obj.begin();
			while ((j != obj.end()) && !found)
			{
				if (i->degree == j->degree)
				{
					sum.Set(i->number + j->number, i->degree);
					found = true;
				}
				j++;
			}
			if (!found)
			{
				sum.Set(i->number, i->degree);
			}
		}

		for (auto j = obj.begin(); j != obj.end(); ++j)
		{
			auto i = sum.begin();
			bool found = false;
			while ((i != sum.end()) && !found)
			{
				if (j->degree == i->degree)
				{
					found = true;
				}
				i++;
			}
			if (!found)
			{
				sum.Set(j->number, j->degree);
			}
		}

		return sum;

	};

	Polynomial<std::complex<T>> operator-(Polynomial<std::complex<T>>& obj)
	{
		Polynomial<std::complex<T>> difference(0);

		for (auto i = begin(); i != end(); ++i)
		{
			bool found = false;
			auto j = obj.begin();
			while ((j != obj.end()) && !found)
			{
				if (i->degree == j->degree)
				{
					if ((i->number - j->number).real() != 0 and (i->number - j->number).imag() != 0)
					{
						difference.Set(i->number - j->number, i->degree);
					}
					found = true;
				}
				j++;
			}
			if (!found)
			{
				std::complex<T> a = std::complex<T>(i->number.real() * -1, i->number.imag() * -1);
				difference.Set(a, i->degree);
			}
		}

		for (auto j = obj.begin(); j != obj.end(); ++j)
		{
			auto i = this->begin();
			bool found = false;
			while ((i != difference.end()) && !found)
			{
				if (j->degree == i->degree)
				{
					found = true;
				}
				i++;
			}
			if (!found)
			{
				difference.Set(j->number, j->degree);
			}
		}

		return difference;
	}

	bool operator==(Polynomial<std::complex<T>>& right)
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
			for (auto i = begin(); i != end(); ++i)
			{
				bool equal = false;
				for (auto j = right.begin(); i != right.end(); ++i)
				{
					if (i->number.real() == j->number.real() && i->number.imag() == j->number.imag()
						&& i->degree == j->degree)
					{
						equal = true;
					}
					j++;
				}
				if (!equal)
				{
					return false;
				}
				i++;
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