### linked list

coleção de elementos do mesmo tipo guardados de forma sequencial (elementos sequenciais estão relacionados através de referencias ou ponteiros)

vantagens:

- tamanho dinâmico por default
- fácil de inserir e remover elementos
- forma eficiente de definir queue e stack structures

desvantagens:

- sequential access ⇒ slow access time
- overhead de informação por elemento
- memória não contigua

- complexidade
    
    time complexity: 
    
    - access:
        - best and worst scenario: $\Omega$(1) and O(n),  no pior dos casos temos de iterar por toda a lista para aceder ao item, não é possível random access (sequential access)
    - update:
        - best and worst scenario: $\Omega$(1) and O(n), mesma operação do access
    - search:
        - worst case: O(n), temos de iterar por toda a lista
    - insertion:
        - best case: $\Omega$(1), adicionar elemento ao inicio da lista onde já existe espaço alocado
        - worst case: O(n), temos de encontrar o local onde inserir o novo elemento, a operação de inserção é relativamente simples é só atualizar o 2 ponteiros
    - deletion:
        - best case: $\Omega$(1), remover elemento do inicio da lista
        - worst case: O(n), temos de encontrar o elemento a remover, a operação em si é relativamente simples é só preciso atualizar 2 ponteiros
    
    space complexity: O(n)