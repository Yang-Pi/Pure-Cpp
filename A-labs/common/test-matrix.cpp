#include <boost/test/auto_unit_test.hpp>
#include <stdexcept>

#include "matrix.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

BOOST_AUTO_TEST_SUITE(testSuiteMatrix)

BOOST_AUTO_TEST_CASE(testIntersection)
{
  pylaev::Rectangle testRectangle({ 0.0, 0.0 }, { 0.0, 2.0 }, { 4.0, 2.0 }, { 4.0, 0.0 });
  pylaev::Circle testCircle({2.0, 8.0}, 3.0);
  pylaev::Triangle testTriangle({0.0, 3.0}, {0.0, 6.0}, {4.0, 3.0});

  BOOST_CHECK_EQUAL(pylaev::intersection(testRectangle.getFrameRect(), testCircle.getFrameRect()), false);
  BOOST_CHECK_EQUAL(pylaev::intersection(testTriangle.getFrameRect(), testCircle.getFrameRect()), true);
}

BOOST_AUTO_TEST_CASE(testInitialization)
{
  pylaev::Rectangle testRectangle({ 0.0, 0.0 }, { 0.0, 2.0 }, { 4.0, 2.0 }, { 4.0, 0.0 });
  pylaev::Circle testCircle({2.0, 8.0}, 3.0);
  pylaev::Triangle testTriangle({0.0, 3.0}, {0.0, 6.0}, {4.0, 3.0});

  pylaev::CompositeShape testCoShape;
  testCoShape.add(&testRectangle);
  testCoShape.add(&testCircle);
  testCoShape.add(&testTriangle);

  BOOST_CHECK_NO_THROW(pylaev::Matrix testMatrix1);
  BOOST_CHECK_NO_THROW(pylaev::Matrix testMatrix2 = testCoShape.split());

  pylaev::Matrix testMatrix = testCoShape.split();

  BOOST_CHECK_EQUAL(testMatrix.getSize(), 3);
  BOOST_CHECK_EQUAL(testMatrix.getCountOfLayers(), 2);

  BOOST_CHECK_NO_THROW(pylaev::Matrix testMatrixCopy(testMatrix));
  BOOST_CHECK_NO_THROW(pylaev::Matrix testMatrixMove(std::move(testMatrix)));
}

BOOST_AUTO_TEST_CASE(testOperators)
{
  pylaev::Rectangle testRectangle({ 0.0, 0.0 }, { 0.0, 2.0 }, { 4.0, 2.0 }, { 4.0, 0.0 });
  pylaev::Circle testCircle({2.0, 8.0}, 3.0);
  pylaev::Triangle testTriangle({0.0, 3.0}, {0.0, 6.0}, {4.0, 3.0});

  pylaev::CompositeShape testCoShape;
  testCoShape.add(&testRectangle);
  testCoShape.add(&testCircle);
  testCoShape.add(&testTriangle);

  pylaev::Matrix testMatrix1;
  pylaev::Matrix testMatrix2 = testCoShape.split();

  BOOST_CHECK_NO_THROW(testMatrix1 = testMatrix2);
  BOOST_CHECK_NO_THROW(testMatrix1 = std::move(testMatrix2));

  BOOST_CHECK_THROW(testMatrix2[100], std::out_of_range);
  BOOST_CHECK_THROW(testMatrix2[0][100], std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END();
