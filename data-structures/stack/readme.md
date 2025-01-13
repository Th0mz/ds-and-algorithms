### stack

estrutura de dados linear onde todas as operações são feitas numa ordem **LIFO (Last In Fist out).** comporta-se como uma pilha de pratos, colocamos no topo e podemos aceder ao topo ****

vantagens:

- eficiência

desvantagens:

- acesso limitado aos elementos (apenas podemos aceder ao topo da stack) ⇒ no random access
- overflow no caso de stacks estáticas ⇒ capacidade limitada

aplicações:

- function call stack, guarda os endereços de retorno das chamadas de funções
- avaliação de expressões como calculadoras podem ser vistas como uma stack de inputs
- …

- complexidade
    
    time complexity: 
    
    - access (top):
        - worst scenario: O(1), existe um ponteiro para o topo da pilha o que torna o acesso simples
    - update (não existe)
    - search (não existe): só temos acesso ao topo
    - insertion (push):
        - worst case: O(1), adicionar um elemento ao topo da stack é simples basta atualizar o ponteiro que aponta para o topo e garantir a sequência do resto da stack
    - deletion (pop):
        - worst case: O(1), mesmo raciocínio da inserção aplica-se à remoção de elementos
    
    space complexity: O(n) - pode ser implementado com um array (stack estática ou dinâmica) ou linked list (stack dinâmica)