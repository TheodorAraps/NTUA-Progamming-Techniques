#include <iostream>
using namespace std;

class Polynomial
{
protected:
	class Term
	{
	protected:
		int exponent;
		int coefficient;
		Term *next;
		Term(int exp, int coeff, Term *n) : exponent(exp), coefficient(coeff), next(n) {}
		friend class Polynomial;
	public:
		int getexp() const
		{
			return exponent;
		}
		int getcoeff() const
		{
			return coefficient;
		}
		Term *getnext() const
		{
			return next;
		}
	};

private:
	Term *head, *tail;

public:
	Polynomial()
	{
		head = NULL;
		tail = NULL;
	}
	Polynomial(const Polynomial &p)
	{
		head = NULL;
		tail = NULL;
		Term *temp = p.head;
		while (temp != NULL)
		{
			addTerm(temp->getexp(), temp->getcoeff());
			temp = temp->getnext();
		}
	}
	~Polynomial()
	{
		delete head;
		delete tail;
	}
	Polynomial &operator=(const Polynomial &p)
	{
		Polynomial P;
		P.head = p.head;
		P.tail = p.tail;
		return P;
	}
	void addTerm(int expon, int coeff)
	{
		if (head == NULL)
		{
			Term *temp = new Term(expon, coeff, NULL);
			head = temp;
			tail = temp;
		}
		else
		{
			Term *add = head;
			while (add->getexp() > expon and add->getnext() != NULL)
			{
				add = add->getnext();
			}
			if (add->getnext() == NULL and expon < add->getexp())
			{
				Term *temp = new Term(expon, coeff, NULL);
				tail->getnext() = temp;
				tail = temp;
			}
			else if (add->getexp() != expon)
			{
				if (add == head)
				{
					Term *temp = new Term(expon, coeff, NULL);
					temp->getnext() = add;
					head = temp;
				}
				else
				{
					Term *temp = new Term(expon, coeff, NULL);
					temp->getnext() = add->getnext();
					add->getnext() = temp;
				}
			}
			else
			{
				add->getcoeff() += coeff;
				if (add->getcoeff() == 0)
				{
					if (add == head)
					{
						head = head->getnext();
						delete add;
					}
					else
					{
						Term *d = head;
						while (d->getnext() != add)
						{
							d = d->getnext();
						}
						d = add->getnext();
						add->getnext() = NULL;
						delete add;
					}
				}
			}
		}
	}
	double evaluate(double x)
	{
		double sum = 0;
		Term *temp = head;
		while (temp != NULL)
		{
			double s = 1;
			for (int i = 0; i < temp->getexp(); i++)
			{
				s *= x;
			}
			s = (temp->getcoeff) * s;
			sum += s;
			temp = temp->next;
		}
		return sum;
	}

	friend Polynomial operator+(const Polynomial &p, const Polynomial &q)
	{
		Polynomial P;
		Term *temp1 = p.head;
		Term *temp2 = q.head;
		while (temp1 != NULL or temp2 != NULL)
		{
			if (temp1->getexp() == temp2->getexp())
			{
				P.addTerm(temp1->getexp(), temp1->getcoeff() + temp2->getcoeff());
				temp1 = temp1->getnext();
				temp2 = temp2->getnext();
				continue;
			}
			else if (temp1->getexp() > temp2->getexponent())
			{
				P.addTerm(temp1->getexp(), temp1->getcoeff());
				temp1 = temp1->next;
				continue;
			}
			else
			{
				P.addTerm(temp2->exponent, temp2->coefficient);
				temp2 = temp2->next;
				continue;
			}
		}
		return P;
	}

	friend Polynomial operator*(const Polynomial &p, const Polynomial &q)
	{
		Polynomial P;
		Term *temp1 = p.head;
		Term *temp2;
		while (temp1 != NULL)
		{
			temp2 = q.head;
			while (temp2 != NULL)
			{
				P.addTerm((temp1->exponent) + (temp2->exponent), (temp1->coefficient) * (temp2->coefficient));
				temp2 = temp2->next;
			}
			temp1 = temp1->next;
		}
		return P;
	}

	friend ostream &operator<<(ostream &out, const Polynomial &p)
	{
		Term *temp = p.head;
		if (temp->coefficient == 0 and temp->next == NULL)
		{
			out << "0";
			return out;
		}
		if (temp->coefficient == -1)
		{
			out << "- ";
			if (temp->exponent == 0)
			{
				out << "1";
			}
		}
		if (temp->coefficient < -1)
		{
			out << "- " << (-1) * (temp->coefficient);
		}
		if (temp->coefficient > 1)
		{
			out << temp->coefficient;
		}
		if (temp->exponent == 1)
		{
			out << "x";
		}
		if (temp->exponent != 0 and temp->exponent != 1)
		{
			out << "x^" << temp->exponent;
		}
		temp = temp->next;
		while (temp != NULL)
		{
			if (temp->coefficient != 0)
			{
				if (temp->coefficient == -1)
				{
					out << " - ";
					if (temp->exponent == 0)
					{
						out << "1";
					}
				}
				if (temp->coefficient < -1)
				{
					out << " - " << (-1) * (temp->coefficient);
				}
				if (temp->coefficient > 1)
				{
					out << " + " << temp->coefficient;
				}
				if (temp->coefficient == 1)
				{
					out << " + ";
					if (temp->exponent == 0)
					{
						out << "1";
					}
				}
				if (temp->exponent == 1)
				{
					out << "x";
				}
				if (temp->exponent != 0 and temp->exponent != 1)
				{
					out << "x^" << temp->exponent;
				}
			}
			temp = temp->next;
		}
		return out;
	}
};

int main()
{
	Polynomial p;
	p.addTerm(1, 1);
	p.addTerm(0, -1);
	Polynomial q(p);
	q.addTerm(0, 2);
	cout << "P(x) = " << p << endl;
	cout << "P(1) = " << p.evaluate(1) << endl;
	cout << "Q(x) = " << q << endl;
	cout << "Q(1) = " << q.evaluate(1) << endl;
	cout << "(P+Q)(x) = " << p + q << endl;
	cout << "(P*Q)(x) = " << p * q << endl;
	return 0;
}