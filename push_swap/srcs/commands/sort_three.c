#include "../../inc/push_swap.h"

void	sort_three(t_stack_node **a) //Define una función que maneja cuando la pila `a` tiene tres nodos, y la ordena
{
	t_stack_node	*biggest_node; //Para almacenar un puntero al nodo más grande en la pila `a`

	biggest_node = find_max(*a);
	if (biggest_node == *a) //Verifica si el nodo actual es el más grande
		ra(a, false); //Si es así, rota el nodo superior al fondo de la pila
	else if ((*a)->next == biggest_node) //Verifica si el segundo nodo es el más grande
		rra(a, false); //Si es así, rota en reversa el nodo del fondo, a la cima de la pila
	if ((*a)->nbr > (*a)->next->nbr) //Verifica si el nodo del fondo es el más grande, pero el nodo superior es mayor que el segundo nodo
		sa(a, false); //Si es así, simplemente intercambia los nodos superior y segundo
}
