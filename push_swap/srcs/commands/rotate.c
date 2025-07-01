#include "../../inc/push_swap.h"

static void	rotate(t_stack_node **stack) //Define una función que rota el nodo superior de la pila al fondo de la pila
{
	t_stack_node	*last_node; //Para almacenar un puntero al último nodo de una pila

	if (!*stack || !(*stack)->next) //Verifica si la pila está vacía, o si hay un nodo
		return ;
	last_node = find_last(*stack); 
	last_node->next = *stack; //Asigna al último nodo, su atributo `next` como el nodo superior, efectivamente estableciendo el nodo superior actual como el último nodo
	*stack = (*stack)->next; //Asigna al puntero del nodo superior, el nodo después de él (segundo desde la cima)
	(*stack)->prev = NULL; //Completa el establecimiento del nodo superior actual desconectándolo de su nodo superior anterior
	last_node->next->prev = last_node; //Reconecta el puntero prev del segundo nodo para que apunte a lo que anteriormente era el último nodo en la pila
	last_node->next->next = NULL; //Asigna al atributo `next` del último nodo actual, `NULL` efectivamente estableciéndolo como el último nodo actual, y terminando apropiadamente la pila con null
}		

void	ra(t_stack_node **a, bool print) //Rota el nodo superior `a` al fondo de la pila, e imprime la instrucción
{
	rotate(a);
	if (!print)
		ft_printf("ra\n");
}

void	rb(t_stack_node **b, bool print) //Rota el nodo superior `b` al fondo de la pila, e imprime la instrucción
{
	rotate(b);
	if (!print)
		ft_printf("rb\n");
}

void	rr(t_stack_node **a, t_stack_node **b, bool print) //Simultáneamente rota ambos nodos superiores `a` y `b` al fondo de la pila, e imprime la instrucción
{
	rotate(a);
	rotate(b);
	if (!print)
		ft_printf("rr\n");
}