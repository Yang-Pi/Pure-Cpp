#include <boost/test/auto_unit_test.hpp>
#include <stdexcept>

#include "circle.hpp"

const double CORRECTNESS = 0.01;

BOOST_AUTO_TEST_SUITE(testSuiteCircle)

BOOST_AUTO_TEST_CASE(testInvariabilityOfDimensions)
{
  pylaev::Circle testCircle({0.0, 0.0}, 5.0);

  const double radius = testCircle.getRadius();
  const double area = testCircle.getArea();

  testCircle.move(5.0, 5.5);
  BOOST_CHECK_CLOSE(testCircle.getRadius(), radius, CORRECTNESS);
  BOOST_CHECK_CLOSE(testCircle.getArea(), area, CORRECTNESS);

  testCircle.move({100.0, 100.0});
  BOOST_CHECK_CLOSE(testCircle.getRadius(), radius, CORRECTNESS);
  BOOST_CHECK_CLOSE(testCircle.getArea(), area, CORRECTNESS);
}

BOOST_AUTO_TEST_CASE(testSquareChangeAreaAfterScaling)
{
  pylaev::Circle testCircle({0.0, 0.0}, 5.0);

  const double area = testCircle.getArea();
  const double kScaling = 2.5;

  testCircle.scale(kScaling);
  BOOST_CHECK_CLOSE(testCircle.getArea(), area * kScaling * kScaling, CORRECTNESS);
}

BOOST_AUTO_TEST_CASE(testIncorrectScale)
{
  pylaev::Circle testCircle({2.0, 0.0}, 10);
  BOOST_CHECK_THROW(testCircle.scale(0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testIncorrectInitialization)
{
  BOOST_CHECK_THROW(pylaev::Circle testCircle({0.0, 0.0}, -1.0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END();
