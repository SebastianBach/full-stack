import sys
import os
import unittest

script_dir = os.path.dirname(os.path.abspath(__file__))
product_location = os.path.abspath(os.path.join(script_dir, "..", "..", "build", "product", "py3_module"))
sys.path.append(product_location)

import func

class TestPythonModule(unittest.TestCase):

    def test_base(self):

        print("Test module 'func'")
        print(func)

        res = func.convert("This Is SPARTA!")
        self.assertEqual(res, "this is sparta!")

        print(res)

        print(func.get_library_build_date())

