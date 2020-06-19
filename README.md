# project_SearchEngine
Esse repositório tem como objetivo a implementação do Search Engine para a matéria Estrutura de Dados e Algoritmos. Esse algoritmo tem como objetivo fazer uma busca de palavras usando a estrutura de dados Trie após a limpeza dos documentos que feita em Python. Ao buscarmos a palavra, se a mesma existir, o algoritmo retornará o documento em que contém a palavra procurada, caso contrário, haverá uma sugestão de palavras semelhantes e então buscaremos uma delas.

Requisitos:

Link para download dos documentos necessários para o projeto: https://gvmail-my.sharepoint.com/:f:/g/personal/b39003_fgv_edu_br/EnaiGxh-msxDjfTcPZtGD1AB_CqPiyN78FfUPzdZrqyKGQ?e=eCDvks
No link acima, estão os arquivos de serialização da trie, a fim de que possamos fazer a deserialização com o nosso executavel (trie_execute.cpp) e os arquivos de documentos e títulos nas pastas devidas que são necessários para serem retornados ao usuário.

Instruções:

Para rodar o programa:
1. Baixe todos os arquivos do link especificado acima clicando em "Baixar" no menu de tarefas do One Drive. Irá baixar um arquivo zipado que corresponde a pasta dos dados necessários para nosso projeto.
    
2. Extraia a pasta do arquivo baixado.
    
3. Dentro dessa pasta, deve conter uma pasta chamada (docs), uma pasta chamada (titles) e um arquivo chamado (serialization_docs_titles.txt).
    
4. Dentro da pasta docs, deve conter 7 arquivos, 4 referentes a docs_p1 e  3 referentes a docs_p2. É necessário que estraia esses arquivos .rar nessa mesma pasta que vieram (colocar extrair aqui). Ficando ao final dentro da pasta docs 2 pastas. A primeira pasta chamada de docs_p1 que deverá conter 798.881 arquivos txt e a segunda pasta chamada de docs_p2 que deverá conter 560.331 arquivos txt.
    
5. Dentro da pasta titles, deve conter 2 arquivos, 1 referente a titles_p1 e  1 referente a titles_p2. É necessário que estraia esses arquivos .rar nessa mesma pasta que vieram (colocar extrair aqui). Ficando ao final dentro da pasta titles 2 pastas. A primeira pasta chamada de titles_p1 que deverá conter 798.881 arquivos txt e a segunda pasta chamada de titles_p2 que deverá conter 560.331 arquivos txt.
       
6. O código em C++ chamado trie_execute.cpp está no Github. Nele, está implementado a estrutura de dados e a função que faz a deserialização do arquivo de serialização. Assim, criando a nossa árvore.
    
7. É necessário realizar alterações no código (trie\_execute.cpp), indicando os paths corretos das pastas dos docs, titles e do arquivo de serialização. Assim, alterando os paths locais. Será necessário alterar as variáveis [path_docs], [path_titles] e [path_serialization_file]. O [path_docs] é o caminho onde estará as pastas (docs_p1 e docs_p2); O [path_titles] é o caminho onde estará as pastas (titles_p1 e titles_p2); E, finalmente, [path_serialization_file] é o caminho onde estará armazenado o arquivo (serialization_docs_titles.txt).
    
8. Bibliotecas que são necessárias para o código (trie_execute.cpp): <iostream>, <vector>, <string>, <fstream>, <sstream>, <algorithm>, <typeinfo>, <chrono> e <iterator>
