import sys
import os
import unittest

module_location = os.getenv('PYTHON_MODULE_PATH', '')

print(f"module location is {module_location}")

sys.path.append(module_location)

import text_conversion

class TestPythonModule(unittest.TestCase):

    def test_base(self):

        print("Test module 'text_conversion'")
        print(text_conversion)

        input = "this is the headline"
        expected = "This Is the Headline"

        res = text_conversion.title_case(input)
        self.assertEqual(res, expected)

        print(res)

        print(text_conversion.get_library_build_date())
