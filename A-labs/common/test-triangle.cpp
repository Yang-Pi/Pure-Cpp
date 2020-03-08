#include <boost/test/auto_unit_test.hpp>
#include <stdexcept>

#include "triangle.hpp"

const double CORRECTNESS = 0.01;

BOOST_AUTO_TEST_SUITE(testSuiteTriangle)

const int N_TOPS = 3;

BOOST_AUTO_TEST_CASE(testInvariabilityOfDimensions)
{
  pylaev::Triangle testTriangle({0.0, 0.0}, {10.0, 5.0}, {3.0, 6.0});

  const double sides[N_TOPS] = {testTriangle.getSide(0), testTriangle.getSide(1), testTriangle.getSide(2)};
  const double area = testTriangle.getArea();

  testTriangle.move(5.0, 5.5);
  for (int i = 0; i < N_TOPS; i++) {
    BOOST_CHECK_CLOSE(testTriangle.getSide(i), sides[i], CORRECTNESS);
  }
  BOOST_CHECK_CLOSE(testTriangle.getArea(), area, CORRECTNESS);

  testTriangle.move({100.0, 100.0});
  for (int i = 0; i < N_TOPS; i++) {
    BOOST_CHECK_CLOSE(testTriangle.getSide(i), sides[i], CORRECTNESS);
  }
  BOOST_CHECK_CLOSE(testTriangle.getArea(), area, CORRECTNESS);
}

BOOST_AUTO_TEST_CASE(testSquareChangeAreaAfterScaling)
{
  pylaev::Triangle testTriangle({0.0, 0.0}, {10.0, 5.0}, {3.0, 6.0});

  const double area = testTriangle.getArea();
  const double kScaling = 2.5;

  testTriangle.scale(kScaling);
  BOOST_CHECK_CLOSE(testTriangle.getArea(), area * kScaling * kScaling, CORRECTNESS);
}

BOOST_AUTO_TEST_CASE(testIncorrectScale)
{
  pylaev::Triangle testTriangle({2.0, 0.0}, {5.0, 10.0}, {4.0, 7.0});
  BOOST_CHECK_THROW(testTriangle.scale(0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testIncorrectInitialization)
{
  BOOST_CHECK_THROW(pylaev::Triangle testTriangle({0.0, 0.0}, {0.0, 0.0}, {0.0, 5.0}), std::logic_error);
}

BOOST_AUTO_TEST_SUITE_END();
