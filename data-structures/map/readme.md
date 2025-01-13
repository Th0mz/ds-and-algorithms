### map

estrutura de dados abstrata que compõe uma coleção de pares key-value onde cada chave é única e associada a um único valor. a esta associação pode ser implementada de diversas formas: hash function, binary tree, …

não só isso mas a forma como se lida com colisões também pode feita de diversos métodos: open addressing, seperate chaning, …

vantagens:

- inserção, remoção e acesso a elementos muito eficiente
- estrutura flexível, tanto as chaves como os valores podem ser de qualquer tipo

desvantagens:

- colisões potenciais
- overhead da key storage

- complexidade - seperate chaning
    
    é uma forma de open addressing (a resolução é feita através de consecutivos offsets até ser encontrado um espaço vazio), neste caso uma segunda hash é usada para determinar o offset.  
    
    time complexity: mesma complexidade de uma linked list já que todas as operações são feitas sob ela, com um pequeno overhead de se calcular a hash para determinar qual das linked list (head guardada num array ao qual chamamos hash table) possívelmente contem o elemento, esta operação é muito simples O(1).
    
    space complexity: O(n)
    
- complexidade - double hashing
    
    a resolução de conflito é feita usando uma linked list para cada bucket do mapa, guardando todos os elementos com a mesma hash na mesma linked list/bucket
    
    time complexity: 
    
    - insertion:
        - best and worst scenario: $\Omega$(1) no melhor dos casos podemos inserir o elemento no primeiro bucket que é derivado apartir da hash. O(n) no pior caso temos de percorrer todos os buckets até encontrar um vazio. (isto pode ser evitado fazer um rehashing há medida que mais elementos são adicionados evitado que o load factor fique demasiado grande)
    - search:
        - best and worst scenario: $\Omega$(1) ou O(n), pela mesma razão do insert
    - deletion:
        - best and worst scenario: $\Omega$(1) ou O(n), pela mesma razão do insert
    
    space complexity: O(n)