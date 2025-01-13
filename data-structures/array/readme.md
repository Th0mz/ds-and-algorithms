### array

coleção de elementos do mesmo tipo guardados num espaço de memória contíguo. 

vantagens:

- fast random access to elements
- good cache locality as all elements are contiguous

desvantagens:

- fix sized

- complexidade
    
    time complexity: 
    
    - access:
        - best and worst scenario: $\Omega$(1) and O(1), operação reduz-se a uma adição do índice + tamanho de cada elemento ao ponteiro base
    - update:
        - best and worst scenario: $\Omega$(1) and O(1), mesma operação do access
    - search:
        - worst case: O(n), temos de iterar por todo o array
        - sorted case: O(log n), podemos fazer uma binary search
    - insertion:
        - best case: $\Omega$(1), adicionar elemento no fim do array onde já existe espaço alocado
        - worst case: O(n), necessário fazer um shift de toda a informação de forma a que o elemento seja posto no local certo
    - deletion:
        - best case: $\Omega$(1), remover elemento do fim da lista
        - worst case: O(n), remover elemento mais fazer shift de toda a informação do array um índice para trás
    
    space complexity: O(n)