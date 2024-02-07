import text_conversion

if __name__ == '__main__':
   # this is some long script
   text = "this is some test headline to process bla bla"
   text = text_conversion.title_case(text)
   print(text)
   with open("my_data.txt", 'r') as file:
      text = file.read()
   print(text)
   text = text_conversion.title_case(text)
   print(text)
   with open("my_data.txt", "w") as file:
      file.write(text)

