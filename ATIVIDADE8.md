# CC0021 - PROGRAMAÇÃO CONCORRENTE - UFCA

Escreva um texto em Markdown, ou uma apresentação no google apresentações que aborde os seguintes temas:
- O que são OpenMP tasks
- Como utilizar
- Exemplos de utilização
- Qual a diferença para as OpenMP Sections
- Quando utilizar ? (em que tipo de problemas)

## O QUE SÃO OpenMP TASKS?

• Uma tarefa OpenMP é uma única linha de código ou um bloco estruturado que é imediatamente “escrito” em uma lista de tarefas. A mesma, pode ser executada
imediatamente ou pode ser adiada.

• Se a cláusula `if` for usada e o argumento for avaliado como 0, a tarefa será executada imediatamente, substituindo qualquer outra coisa que o thread esteja fazendo.

• Deve haver uma equipe de encadeamento paralelo existente para que isso funcione. Caso contrário, um thread acaba fazendo todas as tarefas e assim, não é obtida
nenhuma contribuição para o paralelismo.

## COMO UTILIZAR E EXEMPLOS DE UTILIZAÇÃO

De início, é necessário identificar regiões do código que podem ser paralelizadas. As tarefas a serem executadas em paralelo devem ser isoladas em blocos.

```c
omp_set_num_threads(2);
// Região paralela
#pragma omp parallel default(none) //Sem isso, o thread #0 tem que fazer tudo.
{
      #pragma omp task  // Adiciona a próxima linha de código (ou bloco de código) à lista de tarefas
      {
          // código da primeira tarefa  
          fprintf( stderr, “A\n” );
      }
      #pragma omp task
      {
          // código da segunda tarefa
          fprintf( stderr, “B\n” );
      }
}
```
Se você executar isso várias vezes, obterá isso:

| 1 | 2 | 3 | 4 | 5 |
| - | - | - | - | - |
| B | B | B | B | B |
| A | B | A | A | A |
| B | A | A | A | B |
| A | A | B | B | A |

É possível perceber que nem sempre é obtida a mesma saída, isso acontece pois a ordem de execução das diferentes tarefas é indefinida. Como também foram obtidos 4 itens quando na verdade, eram apenas instruções de impressão em duas tarefas, isto acontece porque foi pedido aos dois encadeamentos que cada um colocasse duas tarefas nas notas adesivas, totalizando quatro.

Para que apenas uma thread execute as tarefas, mas quer que todas as threads sejam capazes de executar, utiliza-se:

```c
omp_set_num_threads(2);
// Região paralela
#pragma omp parallel default(none) //Sem isso, o thread #0 tem que fazer tudo.
{
    #pragma omp single   //Indica que apenas uma thread deve executar as tarefas.
    {
        #pragma omp task  // Adiciona a próxima linha de código (ou bloco de código) à lista de tarefas
        {
            // código da primeira tarefa  
            fprintf( stderr, “A\n” );
        }
        #pragma omp task
        {
            // código da segunda tarefa
            fprintf( stderr, “B\n” );
        }
    }
}
```
Vale ressaltar que ainda assim, a ordem não é determinada. 

Se o objetivo for a ordem, é necessário fazer o seguinte:

```c
omp_set_num_threads( 2 );
#pragma omp parallel
{
   #pragma omp single default(none)
   {
      #pragma omp task
          fprintf( stderr, “A\n” );
   
      #pragma omp taskwait //Faz com que todas as tarefas esperem até serem concluídas
    
      #pragma omp task
          fprintf( stderr, “B\n” );
  
      #pragma omp taskwait
  }
}
```

OBS: É possível criar uma barreira de tarefa com:
 
 *#pragma omp taskwait*

## QUAL A DIFERENÇA PARA AS OpenMP SECTIONS

As tarefas são muito parecidas com as *Seções* do OpenMP, mas as seções são estáticas, ou seja, o número de seções é definido quando é o código é escrito, enquanto as
*Tarefas* podem ser criadas a qualquer momento e em qualquer número, sob controle da lógica do programa.






## Referência

https://web.engr.oregonstate.edu/~mjb/cs575/Handouts/tasks.1pp.pdf
