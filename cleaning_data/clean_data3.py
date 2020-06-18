import os
# pega todos os txt dos docs que estão em documentos separados e coloca em um único txt

path_docs_1 = r'C:\Users\julia\Documents\project_SearchEngine\project_SearchEngine\cleaning_data\titles1'
path_docs_2 = r'C:\Users\julia\Documents\project_SearchEngine\project_SearchEngine\cleaning_data\titles2'
n_doc = 0
print("começando o clean docs:")

novo_clean_doc = open(r'C:\Users\julia\Documents\project_SearchEngine\project_SearchEngine\cleaning_data\clean_titles.txt', 'w')
for i in range(798881):
    with open(os.path.join(path_docs_1, "doc_"+str(n_doc)+".txt"), 'rt') as file:
        file = file.read()
        file = str.join(" ", file.splitlines())
        novo_clean_doc.write(file)
        novo_clean_doc.write("\n")
        n_doc += 1
    if(i%10000 == 0):
        print(i)

for i in range(560331):
    with open(os.path.join(path_docs_2, "doc_"+str(n_doc)+".txt"), 'rt') as file:
        file = file.read()
        file = str.join(" ", file.splitlines())
        novo_clean_doc.write(file)
        novo_clean_doc.write("\n")
        n_doc += 1
    if(i%10000 == 0):
        print(i)

novo_clean_doc.close()




