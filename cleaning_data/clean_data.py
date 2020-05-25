import os
import glob
import re, string, unicodedata
import cleantext
import unidecode


param= {'extra_spaces':False ,  # Remove extra white space
'stemming':False , # Stem the words
'stopwords':False ,# Remove stop words
'lowercase':True ,# Convert to lowercase
'numbers':True ,# Remove all digits
'punct':True ,# Remove all punctuations
'stp_lang':'english'}

path = r'C:\Users\Victor Vilanova\Documents\Search_Engine_Git\project_SearchEngine\cleaning_data\test_wiki_files'

all_files = glob.glob(os.path.join(path, "*.txt"))

path_titles = r'C:\Users\Victor Vilanova\Documents\Search_Engine_Git\project_SearchEngine\cleaning_data\test_clean_data\titles_docs'
path_docs = r'C:\Users\Victor Vilanova\Documents\Search_Engine_Git\project_SearchEngine\cleaning_data\test_clean_data\docs'
path_clean_docs = r'C:\Users\Victor Vilanova\Documents\Search_Engine_Git\project_SearchEngine\cleaning_data\test_clean_data\clean_docs'
n_doc=0

for path_doc in all_files:
    with open(path_doc, 'rt') as file:
        file = file.read()
        while file.find ("title=") != -1:
            titles = open (os.path.join (path_titles,"doc_"+str(n_doc)+".txt"), 'w')
            begin = file.find("title=")
            end = file.find("nonfiltered=")
            title = file[begin+7:end-2]
            titles.write(title)
            titles.close ()

            novo_doc = open (os.path.join (path_docs, "doc_" + str (n_doc) + ".txt"), 'w')
            begin = file.find ("dbindex=")
            end = file.find ("ENDOFARTICLE.")
            doc = file[begin + 12:end]
            novo_doc.write (doc)
            novo_doc.close ()
            file = file[end + 13:]
            n_doc += 1



def remove_empty_lines(filename):
    if not os.path.isfile(filename):
        print("{} does not exist ".format(filename))
        return
    with open(filename) as filehandle:
        lines = filehandle.readlines()

    with open(filename, 'w') as filehandle:
        lines = filter(lambda x: x.strip(), lines)
        filehandle.writelines(lines)

n_doc=0

path = r'C:\Users\Victor Vilanova\Documents\Search_Engine_Git\project_SearchEngine\cleaning_data\test_clean_data\docs'
regex = re.compile('[(),\/.!''?*""]')
#lista dos documentos não limpos
all_files = glob.glob(os.path.join(path, "*.txt"))
for i in range(len(all_files)):
    with open(os.path.join (path_docs, "doc_" + str (n_doc) + ".txt"), 'rt') as file:
        novo_clean_doc = open(os.path.join(path_clean_docs,"doc_"+str(n_doc))+'.txt','w')
        clean_document = cleantext.clean(file.read(), **param)
        clean_document = unidecode.unidecode(clean_document)
        clean_document = regex.sub('', clean_document)
        novo_clean_doc.write(clean_document)
        remove_empty_lines(os.path.join(path_clean_docs,"doc_"+str(n_doc))+'.txt')
        novo_clean_doc.close()
        n_doc+=1








