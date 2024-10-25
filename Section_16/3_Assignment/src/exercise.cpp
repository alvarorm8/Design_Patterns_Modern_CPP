/*
You are asked to write an expression processor for simple numeric expressions with the following constraints:

- Expressions use integral values (e.g., "13" ), single-letter variables defined in variables , as well as + and - operators only
There is no need to support braces or any other operations
- If a variable is not found in Variables  (or if we encounter a variable with >1 letter, e.g. ab), the evaluator returns 0 (zero)
- In case of any parsing failure, evaluator returns 0

Example:

- calculate("1+2+3")  should return 6
- calculate("1+2+xy")  should return 0
- calculate("10-2-x")  when x=3 is in variables should return 5
*/

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

inline vector<string> split(const string& stringToSplit)
{
  vector<string> result;
  size_t pos = 0, lastPos = 0;
  while ((pos = stringToSplit.find_first_of("+-", lastPos)) != string::npos)
  {
    result.push_back(stringToSplit.substr(lastPos, pos-lastPos+1));
    lastPos = pos+1;
  }
  result.push_back(stringToSplit.substr(lastPos));
  return result;
}

struct ExpressionProcessor
{
  map<char,int> variables;

  enum NextOp
  {
    nothing,
    plus,
    minus
  };

  int calculate(const string& expression)
  {
    // TODO
    int current;
    auto next_op = nothing;

    auto parts = split(expression);

    cout << "parts (" << parts.size() << "): ";
    for (auto& part : parts)
      cout << "`" << part << "` ";
    cout << endl;

    for (auto& part : parts)
    {
      auto no_op = split(part);
      auto first = no_op[0];
      int value, z;

      try
      {
        value = stoi(first);
      }
      catch (const invalid_argument&)
      {
        if (first.length() == 1 &&
            variables.find(first[0]) != variables.end())
        {
          value = variables[first[0]];
        }
        else return 0;
      }

      switch (next_op)
      {
        case nothing:
          current = value;
          break;
        case plus:
          current += value;
          break;
        case minus:
          current -= value;
          break;
      }

      if (*part.rbegin() == '+') next_op = plus;
      else if (*part.rbegin() == '-') next_op = minus;
    }

    return current;
  }
};