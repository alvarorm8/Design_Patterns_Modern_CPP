/*
Strategy Coding Exercise
Consider the quadratic equation and its canonical solution:

ax^2 + bx + c = 0

x = (-b +- sqrt(b^2 -4ac))/2a

The part b^2-4*a*c is called the discriminant. Suppose we want to provide an API with two different strategies for calculating the discriminant:

In OrdinaryDiscriminantStrategy , If the discriminant is negative, we return it as-is. This is OK, since our main API returns std::complex  numbers anyway.
In RealDiscriminantStrategy , if the discriminant is negative, the return value is NaN (not a number). NaN propagates throughout the calculation, so the equation solver gives two NaN values.
Please implement both of these strategies as well as the equation solver itself. With regards to plus-minus in the formula, please return the + result as the first element and - as the second.
*/

#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
using namespace std;

struct DiscriminantStrategy
{
    virtual double calculate_discriminant(double a, double b, double c) = 0;
};

struct OrdinaryDiscriminantStrategy : DiscriminantStrategy
{
    double calculate_discriminant(double a, double b, double c) override {
      return (b*b - 4*a*c);
    }
};

struct RealDiscriminantStrategy : DiscriminantStrategy
{
    double calculate_discriminant(double a, double b, double c) override {
      auto discriminant{b*b - 4*a*c};
      if (discriminant < 0) {
        return NAN;
      }
      return discriminant;
    }
};

class QuadraticEquationSolver
{
    DiscriminantStrategy& strategy;
public:
    QuadraticEquationSolver(DiscriminantStrategy &strategy) : strategy(strategy) {}

    tuple<complex<double>, complex<double>> solve(double a, double b, double c)
    {
        complex<double> discriminant{strategy.calculate_discriminant(a,b,c), 0};
        complex<double> positiveSolution{(-b + std::sqrt(discriminant))/(2*a)};
        complex<double> negativeSolution{(-b - std::sqrt(discriminant))/(2*a)};
        return {positiveSolution, negativeSolution};
    }
};

#include <gtest/gtest.h>

namespace {

    class Evaluate : public ::testing::Test {};

    TEST_F(Evaluate, PositiveTestOrdinaryStrategy)
    {
      OrdinaryDiscriminantStrategy strategy;
      QuadraticEquationSolver solver{strategy};
      auto results = solver.solve(1,10,16);
      ASSERT_EQ(complex<double>(-2,0), get<0>(results));
      ASSERT_EQ(complex<double>(-8,0), get<1>(results));
    }

    TEST_F(Evaluate, PositiveTestRealStrategy)
    {
      RealDiscriminantStrategy strategy;
      QuadraticEquationSolver solver{strategy};
      auto results = solver.solve(1,10,16);
      ASSERT_EQ(complex<double>(-2,0), get<0>(results));
      ASSERT_EQ(complex<double>(-8,0), get<1>(results));
    }

    TEST_F(Evaluate, NegativeTestOrdinaryStrategy)
    {
      OrdinaryDiscriminantStrategy strategy;
      QuadraticEquationSolver solver{strategy};
      auto results = solver.solve(1,4,5);
      ASSERT_EQ(complex<double>(-2,1), get<0>(results));
      ASSERT_EQ(complex<double>(-2,-1), get<1>(results));
    }

    TEST_F(Evaluate, NegativeTestRealStrategy)
    {
      RealDiscriminantStrategy strategy;
      QuadraticEquationSolver solver{strategy};
      auto results = solver.solve(1,4,5);
      auto x1 = get<0>(results);
      auto x2 = get<1>(results);
      ASSERT_TRUE(isnan(x1.real()));
      ASSERT_TRUE(isnan(x2.real()));
      ASSERT_TRUE(isnan(x1.imag()));
      ASSERT_TRUE(isnan(x2.imag()));
    }

}  // namespace

// ERROR ON UDEMY'S END, POST AGAIN

int main(int ac, char* av[])
{
  //::testing::GTEST_FLAG(catch_exceptions) = false;
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}