#include <iostream>

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
			std::cout  << listHead->number << "^" <<  degree << " + ";
			PrintInternal(listHead->pNext, degree + 1);
		}
		else
		{
			std::cout  << listHead->number << "^" <<  degree << "";
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
	void Print_rec()
	{
		PrintInternal(odds);
	}

	void push_back_rec(const int data)
	{
		PushBackInternal(odds, data);
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
	Polynomial pln(10);
	pln.push_back_rec(10);
	pln.push_back_rec(1);
	pln.push_back_rec(-20);
	pln.push_back_rec(120);
	pln.Print_rec();
}
