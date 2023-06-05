//This is the solution to the exercise uploaded by the teacher

#include <functional>
using namespace std;

namespace solution {

struct SingletonTester
{
    template <typename T>
    bool is_singleton(function<T* ()> factory)
    {
        T* _1 = factory();
        T* _2 = factory();
        return _1 == _2;
    }
};

}

#include <gtest/gtest.h>

//#include "helpers/iohelper.h"

//#include "exercise.cpp"


namespace
{
  class Evaluate : public testing::Test
  {
  };

  TEST_F(Evaluate, SimpleTest)
  {
    solution::SingletonTester tester;
    ASSERT_TRUE(tester.is_singleton<solution::SingletonTester>(
      [&]() -> solution::SingletonTester* { return &tester; }))
      << "Expected a singleton in this case; provided lambda is yielding the same object over and over.";
    ASSERT_FALSE(tester.is_singleton<solution::SingletonTester>([]() { return new solution::SingletonTester{}; }));
  }
} // namespace


//int main(int ac, char* av[])
//{
//  testing::InitGoogleTest(&ac, av);
//  return RUN_ALL_TESTS();
//}
