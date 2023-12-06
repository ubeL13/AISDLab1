#include <gtest/gtest.h>
#include <complex>
#include <PolyLine.h>
#include <typeinfo>

using namespace std;



TEST(BrokenLineTests, ConstructTypePoint)
{
    BrokenLine<int> intBrokenLine(2, 3);
    BrokenLine<float> floatBrokenLine(2.1f, 3.3f);
    BrokenLine<double> doubleBrokenLine(5.1f, 3.8f);
    BrokenLine<complex<float>> complexFloatBrokenLine(5.1f, 3.8f);

    EXPECT_EQ(intBrokenLine.size(), 1);
    EXPECT_EQ(floatBrokenLine.size(), 1);
    EXPECT_EQ(doubleBrokenLine.size(), 1);
    EXPECT_EQ(complexFloatBrokenLine.size(), 1);

    EXPECT_EQ(intBrokenLine[0].x, 2);
    EXPECT_EQ(intBrokenLine[0].y, 3);

    EXPECT_EQ(floatBrokenLine[0].x, 2.1f);
    EXPECT_EQ(floatBrokenLine[0].y, 3.3f);

    EXPECT_EQ(doubleBrokenLine[0].x, 5.1f);
    EXPECT_EQ(doubleBrokenLine[0].y, 3.8f);

    EXPECT_EQ(complexFloatBrokenLine[0].x, 5.1f);
    EXPECT_EQ(complexFloatBrokenLine[0].y, 3.8f);

}
TEST(BrokenLineTests, ConstructCopy)
{
    BrokenLine<int> intBrokenLine(2, 3);
    BrokenLine<float> floatBrokenLine(2.1f, 3.3f);
    BrokenLine<double> doubleBrokenLine(5.1f, 3.8f);
    BrokenLine<complex<float>> complexFloatBrokenLine(5.1f, 3.8f);

    BrokenLine<int> intBrokenLine2(intBrokenLine);
    BrokenLine<float> floatBrokenLine2(floatBrokenLine);
    BrokenLine<double> doubleBrokenLine2(doubleBrokenLine);
    BrokenLine<complex<float>> complexFloatBrokenLine2(complexFloatBrokenLine);

    EXPECT_EQ(intBrokenLine2.size(), 1);
    EXPECT_EQ(floatBrokenLine2.size(), 1);
    EXPECT_EQ(doubleBrokenLine2.size(), 1);
    EXPECT_EQ(complexFloatBrokenLine2.size(), 1);

    EXPECT_EQ(intBrokenLine2[0].x, 2);
    EXPECT_EQ(intBrokenLine2[0].y, 3);

    EXPECT_EQ(floatBrokenLine2[0].x, 2.1f);
    EXPECT_EQ(floatBrokenLine2[0].y, 3.3f);

    EXPECT_EQ(doubleBrokenLine2[0].x, 5.1f);
    EXPECT_EQ(doubleBrokenLine2[0].y, 3.8f);

    EXPECT_EQ(complexFloatBrokenLine2[0].x, 5.1f);
    EXPECT_EQ(complexFloatBrokenLine2[0].y, 3.8f);

}
TEST(BrokenLineTests, ConstructRandom)
{
    BrokenLine<int> intBrokenLine(1, 5, 10);
    BrokenLine<float> floatBrokenLine(2.1f, 3.3f, 10);

    size_t countInt = 0;
    size_t countFloat = 0;


    for (int i = 0; i < intBrokenLine.size(); ++i)
    {
        if ((intBrokenLine[i].x <= 5) and (intBrokenLine[i].x >= 1) and (intBrokenLine[i].y <= 5) and (intBrokenLine[i].y >= 1))
        {
            countInt += 1;
        }
        if ((floatBrokenLine[i].x <= 3.3f) and (floatBrokenLine[i].x >= 2.1f) and (floatBrokenLine[i].y <= 3.3f) and (floatBrokenLine[i].y >= 2.1f))
        {
            countFloat += 1;
        }
    }

    EXPECT_EQ(intBrokenLine.size(), 10);
    EXPECT_EQ(floatBrokenLine.size(), 10);
    EXPECT_EQ(countInt, 10);
    EXPECT_EQ(countFloat, 10);

}
TEST(BrokenLineTests, Access_by_index)
{
    BrokenLine<int> intBrokenLine(2, 3);
    BrokenLine<float> floatBrokenLine(2.1f, 3.3f);

    EXPECT_EQ(intBrokenLine[0].x, 2);
    EXPECT_EQ(intBrokenLine[0].y, 3);

    EXPECT_EQ(floatBrokenLine[0].x, 2.1f);
    EXPECT_EQ(floatBrokenLine[0].y, 3.3f);

    intBrokenLine[0] = Point<int>(1, 1);
    floatBrokenLine[0] = Point<float>(1.1f, 1.1f);

    EXPECT_EQ(intBrokenLine[0].x, 1);
    EXPECT_EQ(intBrokenLine[0].y, 1);

    EXPECT_EQ(floatBrokenLine[0].x, 1.1f);
    EXPECT_EQ(floatBrokenLine[0].y, 1.1f);
}

TEST(BrokenLineTests, PolylinyConBrokenLine)
{
    BrokenLine<float> floatBrokenLine(4);
    floatBrokenLine[0] = Point(1.1f, 1.1f);
    floatBrokenLine[1] = Point(2.2f, 2.2f);
    floatBrokenLine[2] = Point(3.3f, 3.3f);
    floatBrokenLine[3] = Point(4.4f, 4.4f);

    BrokenLine<float> floatBrokenLine2(3);
    floatBrokenLine2[0] = Point(5.5f, 5.5f);
    floatBrokenLine2[1] = Point(6.6f, 6.6f);
    floatBrokenLine2[2] = Point(7.7f, 7.7f);

    BrokenLine<float> floatBrokenLine3 = floatBrokenLine + floatBrokenLine2;
    EXPECT_EQ(floatBrokenLine3.size(), 7);
    EXPECT_EQ(floatBrokenLine3[0].x, 1.1f);
    EXPECT_EQ(floatBrokenLine3[0].y, 1.1f);
    EXPECT_EQ(floatBrokenLine3[1].x, 2.2f);
    EXPECT_EQ(floatBrokenLine3[1].y, 2.2f);
    EXPECT_EQ(floatBrokenLine3[2].x, 3.3f);
    EXPECT_EQ(floatBrokenLine3[2].y, 3.3f);
    EXPECT_EQ(floatBrokenLine3[3].x, 4.4f);
    EXPECT_EQ(floatBrokenLine3[3].y, 4.4f);
    EXPECT_EQ(floatBrokenLine3[4].x, 5.5f);
    EXPECT_EQ(floatBrokenLine3[4].y, 5.5f);
    EXPECT_EQ(floatBrokenLine3[5].x, 6.6f);
    EXPECT_EQ(floatBrokenLine3[5].y, 6.6f);
    EXPECT_EQ(floatBrokenLine3[6].x, 7.7f);
    EXPECT_EQ(floatBrokenLine3[6].y, 7.7f);

}
TEST(BrokenLineTests, BrokenLineConPoint)
{
    BrokenLine<float> floatBrokenLine(4);
    floatBrokenLine[0] = Point(1.1f, 1.1f);
    floatBrokenLine[1] = Point(2.2f, 2.2f);
    floatBrokenLine[2] = Point(3.3f, 3.3f);
    floatBrokenLine[3] = Point(4.4f, 4.4f);

    Point<float> p(5.5f, 5.5f);

    BrokenLine<float> floatBrokenLine3 = floatBrokenLine + p;
    EXPECT_EQ(floatBrokenLine3.size(), 5);
    EXPECT_EQ(floatBrokenLine3[0].x, 1.1f);
    EXPECT_EQ(floatBrokenLine3[0].y, 1.1f);
    EXPECT_EQ(floatBrokenLine3[1].x, 2.2f);
    EXPECT_EQ(floatBrokenLine3[1].y, 2.2f);
    EXPECT_EQ(floatBrokenLine3[2].x, 3.3f);
    EXPECT_EQ(floatBrokenLine3[2].y, 3.3f);
    EXPECT_EQ(floatBrokenLine3[3].x, 4.4f);
    EXPECT_EQ(floatBrokenLine3[3].y, 4.4f);
    EXPECT_EQ(floatBrokenLine3[4].x, 5.5f);
    EXPECT_EQ(floatBrokenLine3[4].y, 5.5f);

}
TEST(BrokenLineTests, PointConBrokenLine)
{
    BrokenLine<float> floatBrokenLine(4);
    floatBrokenLine[0] = Point(2.2f, 2.2f);
    floatBrokenLine[1] = Point(3.3f, 3.3f);
    floatBrokenLine[2] = Point(4.4f, 4.4f);
    floatBrokenLine[3] = Point(5.5f, 5.5f);

    Point<float> p(1.1f, 1.1f);

    BrokenLine<float> floatBrokenLine3 = p + floatBrokenLine;
    EXPECT_EQ(floatBrokenLine3.size(), 5);
    EXPECT_EQ(floatBrokenLine3[0].x, 1.1f);
    EXPECT_EQ(floatBrokenLine3[0].y, 1.1f);
    EXPECT_EQ(floatBrokenLine3[1].x, 2.2f);
    EXPECT_EQ(floatBrokenLine3[1].y, 2.2f);
    EXPECT_EQ(floatBrokenLine3[2].x, 3.3f);
    EXPECT_EQ(floatBrokenLine3[2].y, 3.3f);
    EXPECT_EQ(floatBrokenLine3[3].x, 4.4f);
    EXPECT_EQ(floatBrokenLine3[3].y, 4.4f);
    EXPECT_EQ(floatBrokenLine3[4].x, 5.5f);
    EXPECT_EQ(floatBrokenLine3[4].y, 5.5f);
}
TEST(BrokenLineTests, Assignment_operator_BrokenLine)
{
    BrokenLine<float> floatBrokenLine(1);
    floatBrokenLine[0] = Point(2.2f, 2.2f);

    BrokenLine<float> floatBrokenLine2 = floatBrokenLine;
    EXPECT_EQ(floatBrokenLine2.size(), 1);
    EXPECT_EQ(floatBrokenLine2[0].x, 2.2f);
    EXPECT_EQ(floatBrokenLine2[0].y, 2.2f);


}
TEST(BrokenLineTests, Addition_operator_by_assignment)
{
    BrokenLine<float> floatBrokenLine1(1);
    floatBrokenLine1[0] = Point(2.2f, 2.2f);

    BrokenLine<float> floatBrokenLine2(1);
    floatBrokenLine2[0] = Point(3.2f, 3.2f);

    floatBrokenLine1 += floatBrokenLine2;
    EXPECT_EQ(floatBrokenLine1.size(), 2);
    EXPECT_EQ(floatBrokenLine1[0].x, 2.2f);
    EXPECT_EQ(floatBrokenLine1[0].y, 2.2f);
    EXPECT_EQ(floatBrokenLine1[1].x, 3.2f);
    EXPECT_EQ(floatBrokenLine1[1].y, 3.2f);

    floatBrokenLine1 += Point(4.2f, 4.2f);
    EXPECT_EQ(floatBrokenLine1.size(), 3);
    EXPECT_EQ(floatBrokenLine1[0].x, 2.2f);
    EXPECT_EQ(floatBrokenLine1[0].y, 2.2f);
    EXPECT_EQ(floatBrokenLine1[1].x, 3.2f);
    EXPECT_EQ(floatBrokenLine1[1].y, 3.2f);
    EXPECT_EQ(floatBrokenLine1[2].x, 4.2f);
    EXPECT_EQ(floatBrokenLine1[2].y, 4.2f);
}
TEST(BrokenLineTests, Length_of_BrokenLine)
{
    BrokenLine<float> floatBrokenLine1(1);
    floatBrokenLine1[0] = Point(0.f, 0.f);

    BrokenLine<float> floatBrokenLine2(1);
    floatBrokenLine2[0] = Point(3.0f, 4.0f);

    floatBrokenLine1 += floatBrokenLine2;
    floatBrokenLine1 += Point(6.0f, 0.0f);

    EXPECT_EQ(floatBrokenLine1.length(0, 2), 10.f);
}



