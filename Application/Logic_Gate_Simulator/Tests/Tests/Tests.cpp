#include "Tests.h"

Tests::Tests()
{

}

Tests::~Tests()
{

}

void Tests::test_case1()
{
    QCOMPARE(1, true);
}

QTEST_APPLESS_MAIN(Tests)
