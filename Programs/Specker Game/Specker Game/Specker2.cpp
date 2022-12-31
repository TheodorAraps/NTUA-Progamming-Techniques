#include <iostream>

class Player
{
protected:
	std::string PlayerName;

public:
	Player(const std::string &n);
	virtual ~Player();

	virtual const std::string &getType() const = 0;
	virtual Move play(const State &s) = 0;

	friend std::ostream &operator<<(std::ostream &out, const Player &player);
};

Player::Player(const std::string &n)
{
	PlayerName = n;
}

Player::~Player()
{
	PlayerName.clear();
}

std::ostream &operator<<(std::ostream &out, const Player &player)
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
	const std::string &getType() const override
	{
		return type;
	}
	Move play(const State &s) override
	{
		int maxi = 0;
		for (int i = 0; i < s.getHeaps(); i++)
		{
			if (s.getCoins(i) > s.getCoins(maxi))
				maxi = i;
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
	const std::string &getType() const override
	{
		return type;
	}
	Move play(const State &s) override
	{
		int maxi = 0;
		for (int i = 0; i < s.getHeaps(); i++)
		{
			if (s.getCoins(i) > s.getCoins(maxi))
				maxi = i;
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
	const std::string &getType() const override
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
			if ((s.getCoins(i) < s.getCoins(mini)) and (s.getCoins(i) > 0))
				mini = i;
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
	const std::string &getType() const override
	{
		return type;
	}
	Move play(const State &s) override
	{
		int mini = 0, maxi = 0;
		for (int i = 0; i < s.getHeaps(); i++)
		{
			if (s.getCoins(i) > s.getCoins(maxi))
				maxi = i;
			else if ((s.getCoins(i) < s.getCoins(mini)))
				mini = i;
		}
		int c = s.getCoins(maxi) - (s.getCoins(maxi) / 2);
		Move m(maxi, c, mini, c - 1);
		return m;
	}
};