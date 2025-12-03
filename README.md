# Fila de Prioridade – Show da Katy Perry

O cenário escolhido foi a entrada de fãs em um **show da Katy Perry**: cada fã recebe uma prioridade, e quem tem prioridade mais alta entra primeiro.

**Alunos:** Pedro Vilela Alves de Castro, Michel Delforge Siqueira, Diana Galdino e Maria Fernanda Luna.
---

## Ideia Geral

Uma fila comum segue a regra **FIFO (First In, First Out)**: o primeiro que entra é o primeiro que sai.

Na **fila de prioridade**, além da ordem de chegada, cada elemento possui um **peso** (prioridade). No nosso caso:

- Fãs **VIP** podem ter prioridade maior (por exemplo, 10)  
- Fãs de **pista premium** podem ter prioridade média (5)  
- Fãs de **ingresso comum** podem ter valor menor (1)  

A remoção sempre pega o fã com maior prioridade dentre os que estão na fila.

---

## Estruturas Utilizadas

As estruturas principais estão no arquivo `fila.h`:

- `NoFila`  
  - Guarda o `nome` do fã  
  - Um inteiro `prioridade`  
  - Ponteiro `prox` para o próximo nó da lista

- `FilaPrioridade`  
  - Guarda somente o ponteiro para o `inicio` da fila  
  - O início é sempre o fã mais prioritário naquele momento

---

## Funcionamento das Operações

Todas as operações da fila de prioridade são implementadas em `fila.c`.

### `criar_fila()`

Reserva memória para a estrutura da fila e inicializa o ponteiro de início como `NULL`, indicando que ela começa vazia.

### `inserir(f, nome, prioridade)`

Insere um novo fã na posição correta, para que a lista **permaneça ordenada** por prioridade (do maior para o menor).

A lógica funciona assim:

1. Cria um nó novo com o nome e prioridade recebidos.  
2. Percorre a lista usando um **ponteiro para ponteiro** até encontrar o primeiro nó que tenha prioridade **menor** que a do novo fã.  
3. Insere o novo nó exatamente nessa posição.  

Dessa forma, o início da fila (`f->inicio`) é sempre o fã de maior prioridade.

### `remover(f)`

Remove o nó localizado no início da lista (que é o fã mais prioritário).  
Mostra uma mensagem indicando quem está entrando no show e libera a memória do nó removido.

### `imprimir(f)`

Percorre a fila inteira mostrando, em ordem:

- posição na fila  
- nome do fã  
- prioridade

### `consultar(f, nome)`

Procura um fã pelo nome, percorrendo a lista nó a nó. Caso encontre, mostra sua prioridade e posição na fila. Se não encontrar, informa que o fã não está na fila.

---

## Arquivos do Projeto

- `fila.h` – definição das estruturas e cabeçalhos das funções  
- `fila.c` – implementação da fila de prioridade do show  
- `main.c` – menu de interação com o usuário  
- `fila_exemplo.c` – exemplo de fila simples (sem prioridade), apenas para ilustrar o funcionamento de uma fila comum  

---

## Uso do Programa (main.c)

Ao executar o programa principal, o usuário tem acesso a um menu interativo:

1. Inserir fã na fila  
2. Chamar próximo fã (remove o de maior prioridade)  
3. Listar toda a fila atual  
4. Consultar fã pelo nome  
0. Sair do sistema  

As prioridades podem ser digitadas conforme a convenção definida (por exemplo, 10 para VIP, 5 para pista premium, 1 para ingresso comum), mas o sistema funciona com qualquer número inteiro.

