#include "../../inc/push_swap.h"

static void	set_target_b(t_stack_node *a, t_stack_node *b) //Define una función que establece para el nodo `a` actual, su nodo objetivo de la pila `a`
{
	t_stack_node	*current_a; //Para almacenar el puntero al nodo `a` actual
	t_stack_node	*target_node; //Para almacenar el puntero del nodo objetivo para el nodo `b`
	long			best_match_index; //Para almacenar el número "más grande más cercano" hasta ahora

	while (b)
	{
		best_match_index = LONG_MAX; //Establece la mejor coincidencia actual al long máximo
		current_a = a; //Asigna el puntero para que apunte al nodo `a` actual
		while (current_a) //Mientras el puntero no esté establecido a NULL
		{
			if (current_a->nbr > b->nbr 
				&& current_a->nbr < best_match_index) //Verifica si el valor del nodo `a` es mayor que el nodo `b`, && menor que el "más grande más cercano" hasta ahora
			{
				best_match_index = current_a->nbr; //Establece la mejor coincidencia como el valor en el nodo `a` actual
				target_node = current_a; //Establece el puntero del nodo objetivo del nodo `b` para que apunte al nodo `a` actual
			}
			current_a = current_a->next; //Se mueve al siguiente nodo `a` para procesamiento
		}
		if (best_match_index == LONG_MAX) //Si el valor de la mejor coincidencia no ha cambiado
			b->target_node = find_min(a); //Establece el puntero del nodo objetivo del nodo `b` para que apunte al número más pequeño en la pila `a`
		else
			b->target_node = target_node; //Si el valor de la mejor coincidencia ha sido actualizado, entonces tenemos un nodo objetivo para el nodo `b` actual
		b = b->next; //Se mueve al siguiente nodo `b` para procesamiento
	}
}

void	init_nodes_b(t_stack_node *a, t_stack_node *b) //Define una función que prepara los nodos para empujar `b` a `a`
{
	current_index(a);
	current_index(b);
	set_target_b(a, b);
}