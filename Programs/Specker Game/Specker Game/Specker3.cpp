#include <iostream>
#include <stdexcept>

class Game
{
	int HEAPS = 0;
	int PLAYERS = 0;
	int heapi = 0;
	int *c;
	Player **p;
	int playeri = 0;

public:
	Game(int heaps, int players);
	~Game();

	void addHeap(int coins) throw(std::logic_error);
	void addPlayer(Player *player) throw(std::logic_error);
	void play(std::ostream &out) throw(std::logic_error);
};

Game::Game(int heaps, int players)
{
	HEAPS = heaps;
	PLAYERS = players;
	p = new Player *[PLAYERS];
	c = new int[HEAPS];
}

Game::~Game()
{
	delete[] c;
	delete[] p;
	HEAPS = 0;
	PLAYERS = 0;
}

void Game::addHeap(int coins) throw(std::logic_error)
{
	if (heapi > HEAPS)
		throw std::logic_error("All Heaps are full!");
	if (coins < 0)
		throw std::logic_error("Coins must be a positive number!");
	else
	{
		c[heapi++] = coins;
	}
}

void Game::addPlayer(Player *player) throw(std::logic_error)
{
	if (playeri >= PLAYERS)
		throw std::logic_error("All players are added!");
	else
	{
		p[playeri++] = player;
	}
}

void Game::play(std::ostream &out) throw(std::logic_error)
{
	if (playeri != PLAYERS and heapi != HEAPS)
		throw std::logic_error("All players and heaps were not added!");
	else
	{
		int i = 0;
		State s(HEAPS, c);
		while (!s.winning())
		{
			out << "State: " << s << std::endl;
			out << *p[i % PLAYERS] << " " << p[i % PLAYERS]->play(s) << std::endl;
			s.next(p[i % PLAYERS]->play(s));
			i++;
		}
		i--;
		out << "State: " << s << std::endl;
		out << *p[i % PLAYERS] << " wins" << std::endl;
	}
}