#include <iostream>
#include <stdexcept>

#pragma warning( disable : 4290 )

class Move
{
	int sourceh = 0;
	int targeth = 0;
	int sourcec = 0;
	int targetc = 0;
public:

	Move(int sh, int sc, int th, int tc);

	int getSource() const;
	int getSourceCoins() const;
	int getTarget() const;
	int getTargetCoins() const;

	friend std::ostream& operator << (std::ostream& out, const Move &move);
};

Move::Move(int sh, int sc, int th, int tc)
{
	sourceh = sh;
	targeth = th;
	sourcec = sc;
	targetc = tc;
}

int Move::getSource() const
{
	return sourceh;
}

int Move::getSourceCoins() const
{
	return sourcec;
}

int Move::getTarget() const
{
	return targeth;
}

int Move::getTargetCoins() const
{
	return targetc;
}

std::ostream& operator << (std::ostream& out, const Move &move)
{
	if (move.getTargetCoins() > 0)
	{
		out << " takes " << move.getSourceCoins() << " coins from heap " << move.getSource() << " and puts " << move.getTargetCoins() << " coins to heap " << move.getTarget();
		return out;
	}
	else
	{
		out << " takes " << move.getSourceCoins() << " coins from heap " << move.getSource() << " and puts nothing";
		return out;
	}
}

class State
{
	int heaps = 0;
	int *coins;
public:
	State(int h, const int c[]);
	~State();

	void next(const Move &move) throw(std::logic_error);
	bool winning() const;

	int getHeaps() const;
	int getCoins(int h) const throw(std::logic_error);

	friend std::ostream &operator<<(std::ostream &out, const State &state);
};

State::State(int h, const int c[])
{
	heaps = h;
	coins = new int[heaps];
	for (int i = 0; i < heaps; i++)
	{
		coins[i] = c[i];
	}
}

State::~State()
{
	delete[] coins;
	coins = nullptr;
}

void State::next(const Move &move) throw(std::logic_error)
{
	if ((move.getSource() < 0) or (move.getSource() > heaps) or (move.getTarget()) < 0 or (move.getTarget() > heaps))
	{
		throw std::logic_error("invalid heap!");
		return;
	}
	else if ((move.getSourceCoins() < 1) or (move.getTargetCoins() < 0) or (move.getSourceCoins() > getCoins(move.getSource())) or (move.getTargetCoins() >= move.getSourceCoins()))
	{
		throw std::logic_error("Invalid coins!");
		return;
	}
	else
	{
		coins[move.getSource()] -= move.getSourceCoins();
		coins[move.getTarget()] += move.getTargetCoins();
	}
}

bool State::winning() const
{
	int sum = 0;
	for (int i = 0; i < heaps; i++)
	{
		sum += getCoins(i);
	}
	return(sum != 0 ? true : false);
}

int State::getHeaps() const
{
	return heaps;
}

int State::getCoins(int h) const throw(std::logic_error)
{
	if (h < 0 or h > heaps)
	{
		throw std::logic_error("Invalid heap!");
	}
	else return coins[h];
}

std::ostream& operator << (std::ostream& out, const State &state)
{
	for (int i = 0; i < state.getHeaps(); i++)
	{
		if (i == state.getHeaps() - 1)
		{
			out << state.getCoins(i);
			break;
		}
		out << state.getCoins(i) << ", ";
	}
	return out;
}

class Player {
protected:
	std::string PlayerName;
public:
	Player(const std::string &n);
	virtual ~Player();

	virtual const std::string& getType() const = 0;
	virtual Move play(const State &s) = 0;

	friend std::ostream& operator << (std::ostream &out, const Player &player);
};

Player::Player(const std::string &n)
{
	PlayerName = n;
}

Player::~Player()
{
	PlayerName.clear();
}

std::ostream& operator << (std::ostream& out, const Player &player)
{
	out << player.getType() << " player " << player.PlayerName;
	return out;
}

class GreedyPlayer : public Player
{
private:
	std::string type;
public:
	GreedyPlayer(const std::string &n) : Player(n)
	{
		type = "Greedy";
	}
	const std::string& getType() const override
	{
		return type;
	}
	Move play(const State &s) override
	{
		int maxi = 0;
		for (int i = 0; i < s.getHeaps(); i++)
		{
			if (s.getCoins(i) > s.getCoins(maxi)) maxi = i;
		}
		Move m(maxi, s.getCoins(maxi), 0, 0);
		return m;
	}
};

class SpartanPlayer : public Player
{
private:
	std::string type;
public:
	SpartanPlayer(const std::string &n) : Player(n)
	{
		type = "Spartan";
	}
	const std::string& getType() const override
	{
		return type;
	}
	Move play(const State &s) override
	{
		int maxi = 0;
		for (int i = 0; i < s.getHeaps(); i++)
		{
			if (s.getCoins(i) > s.getCoins(maxi)) maxi = i;
		}
		Move m(maxi, 1, 0, 0);
		return m;
	}
};

class SneakyPlayer : public Player
{
private:
	std::string type;
public:
	SneakyPlayer(const std::string &n) : Player(n)
	{
		type = "Sneaky";
	}
	const std::string& getType() const override
	{
		return type;
	}
	Move play(const State &s) override
	{
		int mini = 0;
		while (s.getCoins(mini) == 0)
		{
			mini++;
		}
		for (int i = mini + 1; i < s.getHeaps(); i++)
		{
			if ((s.getCoins(i) < s.getCoins(mini)) and (s.getCoins(i) > 0)) mini = i;
		}
		Move m(mini, s.getCoins(mini), 0, 0);
		return m;
	}
};

class RighteousPlayer : public Player
{
private:
	std::string type;
public:
	RighteousPlayer(const std::string &n) : Player(n)
	{
		type = "Righteous";
	}
	const std::string& getType() const override
	{
		return type;
	}
	Move play(const State &s) override
	{
		int mini = 0, maxi = 0;
		for (int i = 0; i < s.getHeaps(); i++)
		{
			if (s.getCoins(i) > s.getCoins(maxi)) maxi = i;
			else if ((s.getCoins(i) < s.getCoins(mini)) and (s.getCoins(i) > 0)) mini = i;
		}
		int c = s.getCoins(maxi) - (s.getCoins(maxi) / 2);
		Move m(maxi, c, mini, c - 1);
		return m;
	}
};

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
	p = new Player*[PLAYERS];
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
	if (heapi > HEAPS) throw std::logic_error("All Heaps are full!");
	if (coins < 0) throw std::logic_error("Coins must be a positive number!");
	else
	{
		c[heapi++] = coins;
	}
}

void Game::addPlayer(Player *player) throw(std::logic_error)
{
	if (playeri >= PLAYERS) throw std::logic_error("All players are added!");
	else
	{
		p[playeri++] = player;
	}
}

void Game::play(std::ostream &out) throw(std::logic_error)
{
	if (playeri != PLAYERS and heapi != HEAPS) throw std::logic_error("All players and heaps were not added!");
	else
	{
		int i = 0;
		State s(HEAPS, c);
		while (s.winning())
		{
			out << "State: " << s << std::endl;
			out << *p[i % PLAYERS] << p[i % PLAYERS]->play(s) << std::endl;
			s.next(p[i % PLAYERS]->play(s));
			i++;

		}
		i--;
		out << "State: " << s << std::endl;
		out << *p[i % PLAYERS] << " wins" << std::endl;
	}
}


int main() {
	Game specker(3, 4);
	specker.addHeap(10);
	specker.addHeap(20);
	specker.addHeap(17);
	specker.addPlayer(new SneakyPlayer("Tom"));
	specker.addPlayer(new SpartanPlayer("Mary"));
	specker.addPlayer(new GreedyPlayer("Alan"));
	specker.addPlayer(new RighteousPlayer("Robin"));
	specker.play(std::cout);
	return 0;
}