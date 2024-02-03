#include <iostream>
#include <fstream>
#include <string>
#include "text_conversion.h"

int main()
{
   //  this is some long script
   std::string text = "this is some test headline to process bla bla";

   text_conversion::convert_to_title_case(text);

   std::cout << text << std::endl;

   {
      const std::string temp((std::istreambuf_iterator<char>(std::ifstream("my_data.txt").rdbuf())), std::istreambuf_iterator<char>());
      text = temp;
   }

   std::cout << text << std::endl;

   text_conversion::convert_to_title_case(text);

   std::cout << text << std::endl;

   std::ofstream("my_data.txt") << text;

   return 0;
}

