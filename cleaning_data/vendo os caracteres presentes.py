import os
import glob
import re, string, unicodedata
from typing import TextIO
import cleantext
import nltk

lista = []
path = r'C:\Users\julia\OneDrive\Documents\cleaning_data\test_clean_data\clean_docs'

all_files = glob.glob(os.path.join(path, "*.txt"))

for path_doc in all_files:
    with open(path_doc, 'rt') as file:
        print(path_doc)
        file = file.read().replace('\n', '')
        for i in str(file):
            lista.append(i)
            conjunto_caracteres = set(lista)
        print(conjunto_caracteres)
    print("--------------")

print(conjunto_caracteres)
print(len(conjunto_caracteres))