#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

class ChessBoardArray
{
protected:
	int *data;
	unsigned SIZE, BASE;
	class Row
	{
		ChessBoardArray &cba;
		int row;

	public:
		Row(ChessBoardArray &a, int i) : cba(a), row(i) {}
		int &operator[](int i) const
		{
			return cba.select(row, i);
		}
	};

	class ConstRow
	{
	public:
		ConstRow(const ChessBoardArray &a, int i) : cba(a), row(i) {}
		int operator[](int i) const
		{
			return cba.select(row, i);
		}

	private:
		const ChessBoardArray &cba;
		int row;
	};
	unsigned int loc(int i, int j) const throw(out_of_range)
	{
		int di = i - BASE;
		int dj = j - BASE;
		int c = (di * SIZE + dj) / 2;
		if (di < 0 or dj < 0 or di >= SIZE or di >= SIZE or (di + dj) % 2 != 0)
			throw out_of_range("invalid index");
		return c;
	}

public:
	ChessBoardArray(unsigned size = 0, unsigned base = 0) : data(new int[(size * size) - (size * size) / 2]), SIZE(size), BASE(base)
	{
		for (unsigned i = 0; i < (SIZE * SIZE) - (SIZE * SIZE) / 2; ++i)
		{
			data[i] = 0;
		}
	}
	ChessBoardArray(const ChessBoardArray &a)
	{
		data = new int[(a.SIZE) * (a.SIZE) - (a.SIZE) * (a.SIZE) / 2];
		BASE = a.BASE;
		SIZE = a.SIZE;
		for (unsigned i = 0; i < (SIZE * SIZE) - (SIZE * SIZE) / 2; ++i)
		{
			data[i] = a.data[i];
		}
	}
	~ChessBoardArray()
	{
		delete[] data;
	}
	ChessBoardArray &operator=(const ChessBoardArray &a)
	{
		delete[] data;
		BASE = a.BASE;
		SIZE = a.SIZE;
		data = new int[(SIZE * SIZE) - (SIZE * SIZE) / 2];
		for (unsigned i = 0; i < (SIZE * SIZE) - (SIZE * SIZE) / 2; ++i)
		{
			data[i] = a.data[i];
		}
		return *this;
	}
	int &select(int i, int j)
	{
		return data[loc(i, j)];
	}
	int select(int i, int j) const
	{
		return data[loc(i, j)];
	}
	const Row operator[](int i)
	{
		return Row(*this, i);
	}
	const ConstRow operator[](int i) const
	{
		return ConstRow(*this, i);
	}

	friend ostream &operator<<(ostream &out, const ChessBoardArray &a)
	{
		unsigned int c = 0, k = 0;
		out << setw(4);
		for (unsigned i = 0; i < a.SIZE; ++i)
		{
			for (unsigned j = 0; j < a.SIZE; ++j)
			{
				if ((i + j) % 2 != 0)
				{
					out << "0" << setw(4);
					c++;
				}
				else
				{
					out << a.data[k++] << setw(4);
					c++;
				}
				if (c == a.SIZE)
				{
					out << endl;
					c = 0;
				}
			}
		}
		return out;
	}
};

int main()
{
	ChessBoardArray a(25, 1);
	a[1][1] = 1;
	a[1][3] = 2;
	a[2][2] = 3;
	a[3][1] = 4;
	a[3][3] = 5;
	cout << a;
	int x;
	cin >> x;
}