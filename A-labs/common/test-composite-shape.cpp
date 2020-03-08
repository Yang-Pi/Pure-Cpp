#include <boost/test/auto_unit_test.hpp>
#include <stdexcept>

#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"

const double CORRECTNESS = 0.01;

BOOST_AUTO_TEST_SUITE(testSuiteCompositeShape)

BOOST_AUTO_TEST_CASE(testInvariabilityOfDimensions)
{
  pylaev::Rectangle testRectangle({1.0, 1.0}, 2.0);
  pylaev::Circle testCircle({5.0, 1.0}, 2.0);
  pylaev::Triangle testTriangle({2.0, 2.0}, {2.0, 6.0}, {5.0, 2.0});

  pylaev::CompositeShape testCoShape;
  testCoShape.add(&testRectangle);
  testCoShape.add(&testCircle);
  testCoShape.add(&testTriangle);

  const pylaev::rectangle_t coShapeFrameRect = testCoShape.getFrameRect();
  const double coShapeArea = testCoShape.getArea();

  testCoShape.move(5.0, 5.5);
  BOOST_CHECK_CLOSE(testCoShape.getFrameRect().width, coShapeFrameRect.width, CORRECTNESS);
  BOOST_CHECK_CLOSE(testCoShape.getFrameRect().height, coShapeFrameRect.height, CORRECTNESS);
  BOOST_CHECK_CLOSE(testCoShape.getArea(), coShapeArea, CORRECTNESS);
}

BOOST_AUTO_TEST_CASE(testSquareChangeAreaAfterScaling)
{
  pylaev::Rectangle testRectangle({1.0, 1.0}, 2.0);
  pylaev::Circle testCircle({5.0, 1.0}, 2.0);
  pylaev::Triangle testTriangle({2.0, 2.0}, {2.0, 6.0}, {5.0, 2.0});

  pylaev::CompositeShape testCoShape;
  testCoShape.add(&testRectangle);
  testCoShape.add(&testCircle);
  testCoShape.add(&testTriangle);

  const double coShapeArea1 = testCoShape.getArea();
  const double kScaling1 = 1.5;
  testCoShape.scale(kScaling1);
  BOOST_CHECK_CLOSE(testCoShape.getArea(), coShapeArea1 * kScaling1 * kScaling1, CORRECTNESS);

  const double coShapeArea2 = testCoShape.getArea();
  const double kScaling2 = 0.5;
  testCoShape.scale(kScaling2);
  BOOST_CHECK_CLOSE(testCoShape.getArea(), coShapeArea2 * kScaling2 * kScaling2, CORRECTNESS);
}

BOOST_AUTO_TEST_CASE(testInitialization)
{
  pylaev::Rectangle testRectangle({1.0, 1.0}, 2.0);
  pylaev::Circle testCircle({5.0, 1.0}, 2.0);
  pylaev::Triangle testTriangle({2.0, 2.0}, {2.0, 6.0}, {5.0, 2.0});

  BOOST_CHECK_NO_THROW(pylaev::CompositeShape testCoShapeNull);

  pylaev::CompositeShape testCoShape1;
  testCoShape1.add(&testRectangle);
  testCoShape1.add(&testCircle);
  testCoShape1.add(&testTriangle);

  pylaev::CompositeShape testCoShape2;

  BOOST_CHECK_NO_THROW(pylaev::CompositeShape testCoShapeCopy(testCoShape1));
  BOOST_CHECK_NO_THROW(testCoShape2 = testCoShape1);
  BOOST_CHECK_NO_THROW(pylaev::CompositeShape testCoShapeMove(std::move(testCoShape2)));
  BOOST_CHECK_NO_THROW(testCoShape2 = std::move(testCoShape1));
}

BOOST_AUTO_TEST_CASE(testInvalidValues)
{
  pylaev::Rectangle testRectangle({1.0, 1.0}, 2.0);
  pylaev::Circle testCircle({5.0, 1.0}, 2.0);
  pylaev::Triangle testTriangle({2.0, 2.0}, {2.0, 6.0}, {5.0, 2.0});

  pylaev::CompositeShape testCoShape;
  testCoShape.add(&testRectangle);
  testCoShape.add(&testCircle);
  testCoShape.add(&testTriangle);

  BOOST_CHECK_THROW(testCoShape.add(nullptr), std::invalid_argument);
  BOOST_CHECK_THROW(testCoShape.remove(nullptr), std::invalid_argument);
  BOOST_CHECK_THROW(testCoShape.scale(-5.0), std::invalid_argument);

  BOOST_CHECK_THROW(testCoShape[-5], std::out_of_range);
  BOOST_CHECK_THROW(testCoShape[50], std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END();
