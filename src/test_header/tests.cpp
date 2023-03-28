#include "test_utilities.h"
#include <string>

int main()
{
   static_assert(test::test_title_case("test", "Test"));

   static_assert(test::test_title_case("test text", "Test Text"));

   static_assert(test::test_title_case(" test ", " Test "));

   static_assert(test::test_title_case("test self-report", "Test Self-Report"));

   static_assert(test::test_title_case(" this is the headline!", " This Is the Headline!"));

   static_assert(test::test_title_case("don't make the T upper case", "Don't Make the T Upper Case"));

    // debug code

    std::string data("this is the headline");
    text_conversion_constexpr::convert_to_title_case(data);

    return 0;
}
