#include <iostream>
#include <string>
using namespace std;

class lexicon {
public:
	lexicon()
	{
		root = nullptr;
	}
	~lexicon();
	void insert(const string &s)
	{

	}
	int lookup(const string &s) const;
	int depth(const string &s) const;
	void replace(const string &s1, const string &s2);
	friend ostream & operator << (ostream &out, const lexicon &l);

private:
	struct word{
		string w;
		int frequency;
		word* right;
		word* left;
	};
	word* root;
	void insertprivate(const string &s) const
	{
		if (root == NULL)
		{
			word* nw = new word;
			nw->w = s;
			nw->left = NULL;
			nw->right = NULL;
			nw->frequency = 1;
			root = nw;
		}
		el 
	}
};