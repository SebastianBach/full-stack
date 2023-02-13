#include "test_utilities.h"

int main()
{
    static_assert(test::test("test", "test"));
    static_assert(test::test("TEST", "test"));
    static_assert(test::test("TeSt", "test"));
    static_assert(test::test("This Is A Test!", "this is a test!"));


    static_assert(test::test2("TesT", "test"));

    return 0;
}
