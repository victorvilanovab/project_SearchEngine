import os
import glob
import re, string, unicodedata
import cleantext
import unidecode


path = r'C:\Users\julia\Documents\project_SearchEngine\project_SearchEngine\cleaning_data\wiki_files'

# pegando todos os arquivos txt
all_files = glob.glob(os.path.join(path, "*.txt"))

path_titles = r'C:\Users\julia\Documents\project_SearchEngine\project_SearchEngine\cleaning_data\titles_docs'
path_docs = r'C:\Users\julia\Documents\project_SearchEngine\project_SearchEngine\cleaning_data\docs'
path_clean_docs = r'C:\Users\julia\Documents\project_SearchEngine\project_SearchEngine\cleaning_data\clean_docs'
n_doc = 0

#separando título do corpo
for path_doc in all_files:
    with open(path_doc, 'rt') as file:
        file = file.read()
        while file.find("title=") != -1:
            titles = open (os.path.join(path_titles,"doc_"+str(n_doc)+".txt"), 'w')
            begin = file.find("title=")
            end = file.find("nonfiltered=")
            title = file[begin + 7:end - 2]
            titles.write(title)
            titles.close()

            novo_doc = open(os.path.join(path_docs, "doc_"+str(n_doc)+".txt"), 'w')
            begin = file.find("dbindex=")
            end = file.find("ENDOFARTICLE.")
            doc = file[begin + 12:end]
            novo_doc.write(doc)
            novo_doc.close()
            file = file[end + 13:]
            n_doc += 1







