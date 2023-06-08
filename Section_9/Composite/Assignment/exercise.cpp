#include <iostream>
#include <vector>
#include <numeric>

/*
Consider the code presented below. The sum() function takes a vector of pointers to either SingleValue or ManyValues instances and adds up all their elements together.

Please complete the implementation so that the sum() function starts to operate correctly. This may involve giving the classes a common interface, among other things.

Here is an example of how the function might be used:

SingleValue single_value{ 1 };
ManyValues other_values;
other_values.add(2);
other_values.add(3);
sum({ &single_value, &other_values }); // returns 6

*/

class ContainsIntegers {
public:
	virtual int sum() = 0;
};

class SingleValue : public ContainsIntegers
{
	int value;
public:
	SingleValue() = default;
	SingleValue(const int& value) : value{ value } 
	{}
	int sum() override {
		return value;
	}
};

class ManyValues : public ContainsIntegers
{
	std::vector<int> values;
public:
	ManyValues() = default;
	ManyValues(const std::vector<int>& vec) : values{ vec }
	{}

	void add(int value) {
		values.emplace_back(value);
	}

	int sum() override {
		return std::accumulate(values.begin(), values.end(), 0);
	}
};

int sum(std::vector<ContainsIntegers*> vec) {
	int result{ 0 };
	for (auto&& obj : vec) {
		result += obj->sum();
	}
	return result;
}

int main() {
	SingleValue single_value{ 1 };
	ManyValues other_values;
	other_values.add(2);
	other_values.add(3);
	std::cout << sum({ &single_value, &other_values }) << std::endl;
	return 0;
}