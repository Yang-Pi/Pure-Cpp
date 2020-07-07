#include <boost/test/auto_unit_test.hpp>
#include <stdexcept>

#include "rectangle.hpp"

const double CORRECTNESS = 0.01;

BOOST_AUTO_TEST_SUITE(testSuiteRectangle)

BOOST_AUTO_TEST_CASE(testInvariabilityOfDimensions)
{
  pylaev::Rectangle testRectangle({0.0, 0.0}, 10.0, 5.0);

  const double width = testRectangle.getWidth();
  const double height = testRectangle.getHeight();
  const double area = testRectangle.getArea();

  testRectangle.move(5.0, 5.5);
  BOOST_CHECK_CLOSE(testRectangle.getWidth(), width, CORRECTNESS);
  BOOST_CHECK_CLOSE(testRectangle.getHeight(), height, CORRECTNESS);
  BOOST_CHECK_CLOSE(testRectangle.getArea(), area, CORRECTNESS);

  testRectangle.move({100.0, 100.0});
  BOOST_CHECK_CLOSE(testRectangle.getWidth(), width, CORRECTNESS);
  BOOST_CHECK_CLOSE(testRectangle.getHeight(), height, CORRECTNESS);
  BOOST_CHECK_CLOSE(testRectangle.getArea(), area, CORRECTNESS);
}

BOOST_AUTO_TEST_CASE(testSquareChangeAreaAfterScaling)
{
  pylaev::Rectangle testRectangle({0.0, 0.0}, 10.0, 5.0);

  const double area = testRectangle.getArea();
  const double kScaling = 2.5;

  testRectangle.scale(kScaling);
  BOOST_CHECK_CLOSE(testRectangle.getArea(), area * kScaling * kScaling, CORRECTNESS);
}

BOOST_AUTO_TEST_CASE(testIncorrectScale)
{
  pylaev::Rectangle testRectangle({2.0, 0.0}, 5, 7);
  BOOST_CHECK_THROW(testRectangle.scale(0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testIncorrectInitialization)
{
  BOOST_CHECK_THROW(pylaev::Rectangle testRectangle({0.0, 0.0}, 0.0, -5.0), std::invalid_argument);
  BOOST_CHECK_THROW(pylaev::Rectangle testSquare({0.0, 0.0}, -1.0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END();
