#include <iostream>
#include <stdexcept>

#include <iostream>  
#include <stdexcept>  

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
		out << "takes " << move.getSourceCoins() << " coins from heap " << move.getSource() << " and puts " << move.getTargetCoins() << " coins to heap " << move.getTarget();
		return out;
	}
	else
	{
		out << "takes " << move.getSourceCoins() << " coins from heap " << move.getSource() << " and puts nothing";
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
	return(sum != 0 ? false : true);
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
private:
private:
private:
private:

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
	delete[] c;
	delete[] p;
	HEAPS = 0;
	PLAYERS = 0;
	if (heapi > HEAPS) throw std::logic_error("All Heaps are full!");
	if (coins < 0) throw std::logic_error("Coins must be a positive number!");
	else
	if (playeri >= PLAYERS) throw std::logic_error("All players are added!");
	if (playeri < PLAYERS or heapi < HEAPS) throw std::logic_error("All players and heaps were not added!");

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
}