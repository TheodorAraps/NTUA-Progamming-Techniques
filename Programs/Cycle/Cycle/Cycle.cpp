#include <iostream>
#include <vector>
using namespace std;

class Graph
{
public:
	Graph(int V) : v(V), adj(V, vector<bool>(V)) {}
	~Graph();
	void addEdge(int u, int v)
	{
		adj[u][v] = true;
	}
	bool cycle(vector<int> &path) const
	{
		int p[1000000], q = 0;
		for (int i = 0; i < v; i++)
		{
			for (int j = 0; j < v; j++)
			{
				if (adj[i][j])
				{
					for (int k = 0; k < v; k++)
					{
						if (adj[k][i])
						{
							p[0] = i;
							int f = j, g = 0, l = 1;
							while (f != k and g != i)
							{
								for (g = 0; g < v g++)
								{
									if (adj[f][g])
									{
										f = g;
										p[l++] = g;
										break;

									}
								}
								if (g == v)break;
								for (g = 0; g < l; g++)
								{
									path[q++];
								}
							}
						}
					}
				}
			}
		}
	}

private:
	int v;
	vector<vector<bool>> adj;
};