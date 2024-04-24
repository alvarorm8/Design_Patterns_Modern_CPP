/*
Chain of Responsibility Coding Exercise
You are given a game scenario with classes Goblin and GoblinKing. Please implement the following rules:

A goblin has base 1 attack/1 defense (1/1), a goblin king is 3/3.
When the Goblin King is in play, every other goblin gets +1 Attack.
Goblins get +1 to Defense for every other Goblin in play (a GoblinKing is a Goblin!).
Example:

Suppose you have 3 ordinary goblins in play. Each one is a 1/3 (1/1 + 0/2 defense bonus).
A goblin king comes into play. Now every ordinary goblin is a 2/4 (1/1 + 0/3 defense bonus from each other + 1/0 from goblin king)
Meanwhile, the goblin king itself is 3/6 (3/3 + 0/3 defense bonus from other goblins)
Here is an example of the kind of test that will be run on the system:

Game game;
Goblin goblin(game);
game.creatures.push_back(&goblin);
ASSERT_EQ(1, goblin.get_attack());
ASSERT_EQ(1, goblin.get_defense());
*/

#include <vector>
#include <gtest/gtest.h>

using namespace std;

struct Creature;

struct Game
{
  vector<Creature*> creatures;
};

struct StatQuery
{
  enum Statistic { attack, defense } statistic;
  int result;
};

struct Creature
{
protected:
  Game& game;
  int base_attack, base_defense;

public:
  Creature(Game &game, int base_attack, int base_defense) : game(game), base_attack(base_attack),
                                                            base_defense(base_defense) {}
  virtual int get_attack() = 0;
  virtual int get_defense() = 0;
  virtual void query(void* obj, StatQuery& query) = 0;
};

class Goblin : public Creature
{
    int getStatisticModification(StatQuery::Statistic statistic) {
        StatQuery sq{statistic, 0};
        for (auto c : game.creatures) {
            c->query(this, sq);
        }
        return sq.result;
    }
public:
  Goblin(Game &game, int base_attack, int base_defense) : Creature(game, base_attack, base_defense) {}

  Goblin(Game &game) : Creature(game, 1, 1) {}

  int get_attack() override {
    // todo
    return base_attack + getStatisticModification(StatQuery::attack);
  }

  int get_defense() override {
    // todo
    return base_defense + getStatisticModification(StatQuery::defense);
  }

  void query(void* obj, StatQuery& query) override
  {
    if (obj != this) {
        switch (query.statistic){
            case StatQuery::defense:
                query.result++;
                break;
            default:
                break;
        }
    }
  }
};

class GoblinKing : public Goblin
{
public:
  GoblinKing(Game &game) : Goblin(game, 3, 3) {}

  // todo
  void query(void* obj, StatQuery& query) override
  {
    if (obj != this) {
        switch (query.statistic){
            case StatQuery::defense:
                Goblin::query(obj, query);
                break;
            case StatQuery::attack:
                query.result++;
                break;
        }
    }
  }
};

namespace
{
  class Evaluate : public testing::Test
  {
  public:
  };

  TEST_F(Evaluate, ManyGoblinsTest)
  {
    Game game;
    Goblin goblin{game};
    game.creatures.push_back(&goblin);

    cout << "Checking that a baseline goblin is a 1/1...\n";

    ASSERT_EQ(1, goblin.get_attack());
    ASSERT_EQ(1, goblin.get_defense());

    cout << "Adding a second goblin, now they should be 1/2...\n";
    Goblin goblin2{game};
    game.creatures.push_back(&goblin2);

    ASSERT_EQ(1, goblin.get_attack());
    ASSERT_EQ(2, goblin.get_defense());

    cout << "Adding a goblin king, now a goblin should be 2/3...\n";
    GoblinKing goblin3{game};
    game.creatures.push_back(&goblin3);

    ASSERT_EQ(2, goblin.get_attack());
    ASSERT_EQ(3, goblin.get_defense());

    cout << "Goblin king should be 2/3...\n";
    ASSERT_EQ(3, goblin3.get_attack());
    ASSERT_EQ(5, goblin3.get_defense());
  }

} // namespace

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}