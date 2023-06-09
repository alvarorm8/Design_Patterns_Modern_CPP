#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

/*
You are given a class called Sentence, which takes a string such as "hello world".
You need to provide an interface such that the indexer (operator [] ) returns a WordToken
that can be used to capitalize a particular word in the sentence.

Typical use would be something like:

Sentence sentence("hello world");
sentence[1].capitalize = true;
cout << sentence.str(); // prints "hello WORLD"
*/

struct Sentence
{
	struct WordToken
	{
		WordToken() = default;
		WordToken(bool capitalize, size_t start, size_t end)
			: capitalize{ capitalize }, start{ start }, end{ end }
		{}
		bool capitalize;

		friend class Sentence;
	private:
		size_t start, end;
	};

	Sentence(const std::string& text) : sentence{ text }
	{
		countWords(sentence);
	}

	WordToken& operator[](size_t index)
	{
		if (index < formatting.size())
			return formatting[index];
	}

	std::string str() const
	{
		std::string result{ sentence };
		for (auto& wordToken : formatting) {
			if (wordToken.capitalize) {
				for (int i = wordToken.start; i <= wordToken.end; ++i) {
					result[i] = toupper(result[i]);
				}
			}
		}
		return result;
	}
private:
	std::string sentence;
	std::vector<WordToken> formatting;

	void countWords(const std::string& sentence) {
		size_t previousPosition{ 0 };
		size_t position = sentence.find(" ");
		while (position != std::string::npos) {
			if (previousPosition == 0)
				formatting.emplace_back(WordToken{ false, 0, position - 1 });
			else
				formatting.emplace_back(WordToken{ false, previousPosition + 1, position - 1 });
			previousPosition = position;
			position = sentence.find(" ", position + 1);
		}
		if (previousPosition < sentence.length() - 1)
			formatting.emplace_back(WordToken{ false, previousPosition + 1, sentence.length() - 1 });
	}
};

int main() {
	std::string aa{ "hello world hello" };
	Sentence sent{ aa };
	sent[1].capitalize = true;
	std::cout << sent.str() << std::endl;
	return 0;
}