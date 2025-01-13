### queue

estrutura de dados linear onde todas as operações são feitas numa ordem **FIFO (First In First out).** comporta-se como uma fila de pessoas, pessoas entram no fim da fila e saem do inicio ****

vantagens:

- eficiência

desvantagens:

- acesso limitado aos elementos (apenas podemos aceder ao topo da queue) ⇒ no random access
- overflow no caso de queues estáticas ⇒ capacidade limitada

aplicações:

- priority queue para thread scheduling pelo sistema operativo
- buffer entre um elemento que produz informação e outro que consome essa mesma informação, mantendo assim a ordem pela qual foi produzida
- …

- complexidade
    
    time complexity: 
    
    - access (front e rear):
        - worst scenario: O(1), existe um ponteiro para o topo da pilha o que torna o acesso simples
    - update (não existe)
    - search (não existe): só temos acesso ao topo
    - insertion (enqueue):
        - worst case: O(1), adicionar um elemento ao fim da fila é simples basta atualizar o ponteiro que aponta para o fim e garantir a sequência do resto da fila
    - deletion (dequeue):
        - worst case: O(1), mesmo raciocionio da insersão aplica-se à remoção de elementos
    
    space complexity: O(n) - pode ser implementado com um array (stack estática ou dinâmica) ou linked list (stack dinâmica)