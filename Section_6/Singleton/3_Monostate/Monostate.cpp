/*
* The monostate is a variation of the singleton pattern.
* 
* The idea is to have a class where all its members are static like Printer.
* 
* Later, we can create several instances of Printer and it looks like they're different variables but they really are not.
* 
* This is a bad idea since, for example, in inheritance you can not inherit static members.
* 
* So it does not matter how many instances of Printer you make, id will be always the same.
* 
* Is not a good idea to use it, but it's shown as an alternative of singleton design.
*/

class Printer {
	static int id;
public:
	int get_id() const { return id; }
	void set_id(int value) { id = value; };
};

int main() {
	Printer p;
	int p = p.get_id();

	Printer p2;
	int p2 = p2.get_id();
}