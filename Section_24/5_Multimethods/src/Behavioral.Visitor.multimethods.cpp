#include <iostream>
#include <string>
#include <typeindex>
#include <map>
#include <functional>
using namespace std;

/*
In this example we are taking a look at the double dispatch used in the classic example in the section 3, but with the idea that the accept functions receive more than one argument (This is called multi-methods).
The problem is that in the context of a visitor this can get really ugly, so we are going to use an example which is really old, which is the example of space collision.

We have different types of objects, and depending on which one collides with which one, you have different behaviours.

We have the global function collide, which takes two objects, and the base class GameObject, which inside of it reuses the global function collide.

The class GameObjectImpl is an in-between class used to use CRTP. The Curiously Recurring Template Pattern (CRTP) is a C++ idiom where a class derives from a template instantiation of itself.
It’s mainly used for static polymorphism — enabling compile-time resolution of behavior without the runtime cost of virtual functions. This is used for the classes Planet, Asteroid, etc., 
so we can have the type_index of each one at compile time.

Later we define the functions that define the behaviour of the possible collisions, and a map which relates the possible kind of objects (using the type_index) with the functions to call.

Finally, we define the collide global function, using the map just defined to find the function to execute.
*/

struct GameObject;
void collide(GameObject& first, GameObject& second);

struct GameObject
{
	virtual ~GameObject() = default;
	virtual type_index type() const = 0;

	virtual void collide(GameObject& other) { ::collide(*this, other); }
};

template <typename T> struct GameObjectImpl : GameObject
{
	type_index type() const override
	{
		return typeid(T);
	}
};

struct Planet : GameObjectImpl<Planet> {};
struct Asteroid : GameObjectImpl<Asteroid> {};
struct Spaceship : GameObjectImpl<Spaceship> {};
struct ArmedSpaceship : Spaceship
{
	type_index type() const override {
		return typeid(ArmedSpaceship); // required for collision to function
	}
}; // model limitation

void spaceship_planet() { cout << "spaceship lands on planet\n"; }
void asteroid_planet() { cout << "asteroid burns up in atmosphere\n"; }
void asteroid_spaceship() { cout << "asteroid hits and destroys spaceship\n"; }
void asteroid_armed_spaceship() { cout << "spaceship shoots asteroid\n"; }

map<pair<type_index,type_index>, void(*)(void)> outcomes{
	{{typeid(Spaceship), typeid(Planet)}, spaceship_planet},
	{{typeid(Asteroid),typeid(Planet)}, asteroid_planet},
	{{typeid(Asteroid),typeid(Spaceship)}, asteroid_spaceship},
	{{typeid(Asteroid), typeid(ArmedSpaceship)}, asteroid_armed_spaceship}
};

void collide(GameObject& first, GameObject& second)
{
	auto it = outcomes.find({ first.type(), second.type() });
	if (it == outcomes.end())
	{
		it = outcomes.find({ second.type(), first.type() });
		if (it == outcomes.end())
		{
			cout << "objects pass each other harmlessly\n";
			return;
		}
	}
	it->second();
}

int main(int argc, char* argv[])
{
	ArmedSpaceship spaceship;
	Asteroid asteroid;
	Planet planet;

	collide(planet, spaceship);
	collide(planet, asteroid);
	collide(spaceship, asteroid);
	collide(planet, planet);

	cout << "Member collision:\n";
	planet.collide(asteroid);

	// but this won't work
	spaceship.collide(planet);
	return 0;
}
