import re
import shutil
import sys

def text_file_as_string(filepath):
	with open(filepath, 'r') as textfile:
		return textfile.read()

def string_to_text_file(text, filepath):
	with open(filepath, 'w') as textfile:
		textfile.write(text)

def main():
	input_file  = sys.argv[1]
	output_file = sys.argv[2]

	to_replace = re.findall(r"{{(.*)}}", text_file_as_string(input_file))
	new_text = text_file_as_string(input_file)

	for path in to_replace:
		new_text = new_text.replace("{{"+path+"}}", text_file_as_string(path))

	string_to_text_file(new_text, output_file)

if __name__=="__main__":
    main()
