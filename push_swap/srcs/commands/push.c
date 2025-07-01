#include "../../inc/push_swap.h"

static void	push(t_stack_node **dst, t_stack_node **src) //Define una función que empuja un nodo superior, de una pila al nodo superior de otra
{
	t_stack_node	*push_node; //Usado para almacenar el puntero al nodo a ser empujado

	if (!*src) //El nodo superior de una pila a ser empujado
		return ;
	push_node = *src; //El nodo superior a empujar es asignado a la variable `t_stack_node`
	*src = (*src)->next; //Mueve el puntero de la pila al siguiente nodo, que se convertirá en el siguiente `nodo superior` después de que el nodo anterior sea "sacado"
	if (*src) //Verifica si el nodo actual existe
		(*src)->prev = NULL; //Establece el nodo actual como la cabeza de la pila
	push_node->prev = NULL; //Desacopla el nodo a empujar de su pila
	if (!*dst) //Verifica si la otra pila está vacía
	{
		*dst = push_node; //Si está vacía, asigna como el primer nodo de esa pila, el nodo que queremos empujar
		push_node->next = NULL; //Asegura que también se establezca como el último nodo, ej. termina apropiadamente la pila con null
	}
	else //Si la otra pila a la que queremos empujar no está vacía
	{
		push_node->next = *dst; //Asigna el nodo a empujar, a la cima del nodo superior actual de la pila
		push_node->next->prev = push_node; //Asigna al atributo `prev` del "segundo nodo", el nodo empujado como el nodo superior actual
		*dst = push_node; //Completa el agregado del nodo. El puntero al nodo superior de la pila ahora apunta a nuestro nodo recientemente empujado
	}
}

void	pa(t_stack_node **a, t_stack_node **b, bool print) //Empuja encima de `b`, la cima de `a` e imprime la instrucción
{
	push(a, b); 
	if (!print) 
		ft_printf("pa\n");
}

void	pb(t_stack_node **b, t_stack_node **a, bool print) //Empuja encima de `a`, la cima de `b` e imprime la instrucción
{
	push(b, a);
	if (!print)
		ft_printf("pb\n");
}