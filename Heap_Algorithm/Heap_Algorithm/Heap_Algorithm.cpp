
#include "pch.h"
#include <iostream>
using namespace std;

//------------------------------------
//Player Interface
//------------------------------------

class Player {
private:
	int m_xp = 0;
	int m_level = 0;
	int m_strength = 0;
	
public:
	Player();
	Player(int xp, int level, int strength);
	~Player();

	int getXP();
	void setXP(int xp);

	int getLevel();
	void setLevel(int level);

	int getStrength();
	void setStrength(int strength);
};

//------------------------------------
//PlayerHeap Interface
//------------------------------------

class PlayerHeap {
private:

	Player *m_players;
	int m_heapCapacity = 0;
	int m_heapSize = 0;

public:
	PlayerHeap(int capacity);
	~PlayerHeap();

	void setHeap(Player *players);

	int getCapacity();
	void setCapacity(int capacity);

	int getSize();
	void setSize(int size);

	Player getElement(int index);

	Player getMax();

	int getParentIndex(int i);
	int getLeftChildIndex(int i);
	int getRightChildIndex(int i);

	template<typename Function>
	void insert(Player newPlayer, Function sortBy);
	
	void swap(Player* pA, Player* pB);

	//Re-sort by the getter's return value
	template<typename Function>
	void sortBy(Function method);

	bool hasParent(int index);
	bool hasLeftChild(int index);
	bool hasRightChild(int index);

	void printProperties();
};

int main()
{
	PlayerHeap playerHeap = PlayerHeap(10);

	//SORT BY XP
	cout << "Sort By XP" << endl;
	playerHeap.insert(Player(20, 2, 19),    &Player::getXP);
	playerHeap.insert(Player(85, 4, 29),    &Player::getXP);
	playerHeap.insert(Player(1000, 11, 70), &Player::getXP);
	playerHeap.insert(Player(100, 5, 28),   &Player::getXP);
	playerHeap.insert(Player(1004, 9, 68),  &Player::getXP);
	playerHeap.insert(Player(25, 2, 30),    &Player::getXP);
	playerHeap.insert(Player(1020, 10, 65), &Player::getXP);
	playerHeap.insert(Player(753, 7, 71),   &Player::getXP);

	playerHeap.printProperties();

	cout <<"Max XP located: " << playerHeap.getMax().getXP() << endl;
	system("pause");

	system("CLS");


	//SORT BY STRENGTH
	cout << "Sort By Strength" << endl;
	playerHeap.sortBy(&Player::getStrength);

	playerHeap.printProperties();

	cout << "Max Strength located: " << playerHeap.getMax().getStrength() << endl;
	
	system("pause");
	system("CLS");

	//SORT BY LEVEL
	cout << "Sort By Level" << endl;
	playerHeap.sortBy(&Player::getLevel);
	
	playerHeap.printProperties();
	cout << "Max Level located: " << playerHeap.getMax().getLevel() << endl;

	system("pause");
	system("CLS");
}

//------------------------------------
//PlayerHeap Implementation
//------------------------------------

//Constructor
PlayerHeap::PlayerHeap(int heapCapacity)
{
	m_heapCapacity = heapCapacity;
	m_players = new Player[heapCapacity];
}

PlayerHeap::~PlayerHeap()
{
}

int PlayerHeap::getParentIndex(int i)
{
	return (i - 1) / 2;
}

int PlayerHeap::getLeftChildIndex(int i)
{
	return 2 * i + 1;
}

int PlayerHeap::getRightChildIndex(int i)
{
	return 2 * i + 2;
}

//Get top element of heap
Player PlayerHeap::getMax()
{
	return *m_players;
}

template<typename Function>
void PlayerHeap::insert(Player newPlayer, Function method)
{
	//Check that heap size will not go OOB
	if (m_heapSize == m_heapCapacity) {
		return;
	}

	m_heapSize++;
	
	//Get the n - 1 position of last element
	int i = m_heapSize - 1;
	m_players[i] = newPlayer;

	//Bubble up until new player is at correct position or is the root of tree
	while (i != 0 && (m_players[i].*method)() > (m_players[getParentIndex(i)].*method)()) {
		swap(&m_players[i], &m_players[getParentIndex(i)]);
		i = getParentIndex(i);
	}
}

//Swap positions of players when sorting
void PlayerHeap::swap(Player * pA, Player * pB)
{
	Player tmpPlayer = *pA;
	*pA = *pB;
	*pB = tmpPlayer;
}

void PlayerHeap::setHeap(Player * players)
{
	m_players = players;
}

int PlayerHeap::getCapacity()
{
	return m_heapCapacity;
}

void PlayerHeap::setCapacity(int capacity)
{
	m_heapCapacity = capacity;
}

int PlayerHeap::getSize()
{
	return m_heapSize;
}

void PlayerHeap::setSize(int size)
{
	m_heapSize = size;
}

//Check for parent at position i
bool PlayerHeap::hasParent(int index)
{
	return getParentIndex(index) >=0;
}

//Check for left child at position i
bool PlayerHeap::hasLeftChild(int index)
{
	return getLeftChildIndex(index) < m_heapSize;
}

//Check for right child at position i
bool PlayerHeap::hasRightChild(int index)
{
	return getRightChildIndex(index) < m_heapSize;
}

//Print stats of players
void PlayerHeap::printProperties()
{
	for (int i = 0; i < m_heapSize; i++) {
		cout <<"XP: " << getElement(i).getXP() << " , "
			<< "Level: " << getElement(i).getLevel() << ", "
			<< "Strength: " << getElement(i).getStrength() << endl;
	}
}

Player PlayerHeap::getElement(int index)
{
	return m_players[index];
}

template<typename Function>
void PlayerHeap::sortBy(Function method)
{
	//Create a new heap
	PlayerHeap newHeap = PlayerHeap(m_heapCapacity);


	for (int i = 0; i < m_heapSize; i++) 
	{
		//Reinsert values into heap and re-sort by the new getter reference
		newHeap.insert(m_players[i], method);
	}

	//Assign the pointer of player array to heap
	setHeap(newHeap.m_players);
}

//------------------------------------
//Player Implementation
//------------------------------------

Player::Player() {}

Player::Player(int xp, int level, int strength) : m_xp(xp), m_level(level), m_strength(strength) { }

Player::~Player() {}



void Player::setXP(int xp)
{
	m_xp = xp;
}

int Player::getLevel()
{
	return m_level;
}

void Player::setLevel(int level)
{
	m_level = level;
}

int Player::getStrength()
{
	return m_strength;
}

void Player::setStrength(int strength)
{
	m_strength = strength;
}

int Player::getXP()
{
	return m_xp;
}