import sys
import os
import unittest

script_dir = os.path.dirname(os.path.abspath(__file__))
product_location = os.path.abspath(os.path.join(script_dir, "..", "..", "build", "product", "python"))
sys.path.append(product_location)

import text_conversion

class TestPythonModule(unittest.TestCase):

    def test_base(self):

        print("Test module 'text_conversion'")
        print(text_conversion)

        res = text_conversion.title_case("this is the headline")
        self.assertEqual(res, "This Is the Headline")

        print(res)

        print(text_conversion.get_library_build_date())

