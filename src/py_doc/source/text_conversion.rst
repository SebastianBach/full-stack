
Text Conversion Documentation
=============================

title_case
----------

.. function:: title_case(input_string: str) -> str

   Converts the given string formatted as a headline.

   This function takes a single string argument and returns a new string that has been formatted as an APA style headline.

   :param input_string: The string to be converted.
   :type input_string: str
   :returns: The converted string.
   :rtype: str

   **Example:**

   .. code-block:: python

      >>> import text_conversion
      >>> result = text_conversion.title_case('this is a headline')
      >>> print(result)
      'This Is a Headline'


get_library_build_date
----------------------

.. function:: get_library_build_date() -> str

   Returns the build date of the module as a string.

   This function does not take any arguments and returns a string representing the date on which the module was built. This can be useful for version checks or logging when using the module.

   :returns: The build date of the module, typically in 'YYYY-MM-DD' format.
   :rtype: str

   **Example:**

   .. code-block:: python

      >>> import text_conversion
      >>> build_date = text_conversion.get_library_build_date()
      >>> print(build_date)
      '2024-01-01'
