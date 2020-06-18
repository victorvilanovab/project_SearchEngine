import os
import glob
import re, string, unicodedata
import cleantext
import nltk
import unidecode
nltk.download('stopwords')


param = {'extra_spaces': False,  # Remove extra white space
'stemming': False, # Stem the words
'stopwords': False, # Remove stop words
'lowercase': True, # Convert to lowercase
'numbers': True, # Remove all digits
'punct': True, # Remove all punctuations
'stp_lang': 'english'}


path_titles = r'C:\Users\julia\Documents\project_SearchEngine\project_SearchEngine\cleaning_data\clean_02\titles'
path_docs = r'C:\Users\julia\Documents\project_SearchEngine\project_SearchEngine\cleaning_data\clean_02\docs'
path_clean_docs = r'C:\Users\julia\Documents\project_SearchEngine\project_SearchEngine\cleaning_data\clean_02\clean_docs'
path_clean_titles= r'C:\Users\julia\Documents\project_SearchEngine\project_SearchEngine\cleaning_data\clean_02\clean_titles'
n_doc = 0

def remove_empty_lines(filename):
    if not os.path.isfile(filename):
        print("{} does not exist ".format(filename))
        return
    with open(filename) as filehandle:
        lines = filehandle.readlines()

    with open(filename, 'w') as filehandle:
        lines = filter(lambda x: x.strip(), lines)
        filehandle.writelines(lines)

n_doc = 798881

print("começando o clean docs:")
regex = re.compile('[(),\/.!''?*""]')

# lista dos documentos não limpos
for i in range(560331):
    with open(os.path.join(path_docs, "doc_"+str(n_doc)+".txt"), 'rt') as file:
        novo_clean_doc = open(os.path.join(path_clean_docs, "doc_"+str(n_doc))+'.txt', 'w')
        clean_document = cleantext.clean(file.read(), **param)
        clean_document = unidecode.unidecode(clean_document)
        clean_document = regex.sub('', clean_document)
        novo_clean_doc.write(clean_document)
        remove_empty_lines(os.path.join(path_clean_docs, "doc_"+str(n_doc))+'.txt')
        novo_clean_doc.close()
        n_doc += 1
    if(i%10000 == 0):
        print(i)


n_doc = 798881
regex = re.compile('[(),\/.!''?*""]')

# lista dos títulos não limpos
print("começando o clean titles")
for i in range(560331):
    with open(os.path.join(path_titles, "doc_"+str(n_doc)+".txt"), 'rt') as file:
        novo_clean_doc = open(os.path.join(path_clean_titles, "doc_"+str(n_doc))+'.txt', 'w')
        clean_document = cleantext.clean(file.read(), **param)
        clean_document = unidecode.unidecode(clean_document)
        clean_document = regex.sub('', clean_document)
        novo_clean_doc.write(clean_document)
        remove_empty_lines(os.path.join(path_clean_titles, "doc_"+str(n_doc))+'.txt')
        novo_clean_doc.close()
        n_doc += 1
    if(i%1000 == 0):
        print(i)






