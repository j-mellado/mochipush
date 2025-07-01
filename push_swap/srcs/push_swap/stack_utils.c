#include "../../inc/push_swap.h"

int	stack_len(t_stack_node *stack) //Define una función que calcula y retorna la longitud de una pila
{
	int	count; //Para almacenar el conteo de nodos

	if (!stack) 
		return (0);
	count = 0;
	while (stack) //Hace bucle hasta que se alcance el final de la pila
	{
		stack = stack->next; //Se mueve al siguiente nodo
		count++;
	}
	return (count);
}

t_stack_node	*find_last(t_stack_node *stack) //Define una función que retorna el puntero al último nodo
{
	if (!stack)
		return (NULL);
	while (stack->next) //Hace bucle hasta que se alcance el final de la pila
		stack = stack->next;
	return (stack);
}

bool	stack_sorted(t_stack_node *stack) //Define una función que verifica si la pila está ordenada en orden ascendente
{
	if (!stack)
		return (1);
	while (stack->next) //Hace bucle hasta que se alcance el final de la pila
	{
		if (stack->nbr > stack->next->nbr) //Verifica si el valor actual es mayor que el valor del siguiente nodo, indicando que está fuera de orden
			return (false);
		stack = stack->next; //Si no, se mueve al siguiente nodo para procesamiento
	}
	return (true);
}

t_stack_node	*find_min(t_stack_node *stack) //Define una función que busca en una pila y retorna el nodo con el número más pequeño
{
	long			min; //Para almacenar el valor más pequeño hasta ahora
	t_stack_node	*min_node; //Para almacenar un puntero que apunta al número más pequeño

	if (!stack)
		return (NULL);
	min = LONG_MAX; //Asigna al valor más pequeño hasta ahora, el entero long máximo
	while (stack) //Hace bucle hasta que se alcance el final de la pila
	{
		if (stack->nbr < min) //Verifica si el valor del nodo actual es menor que el más pequeño hasta ahora
		{
			min = stack->nbr; //Si es así, actualiza el número más pequeño hasta ahora
			min_node = stack; //Establece el puntero para que apunte al nodo con el número más pequeño hasta ahora
		}
		stack = stack->next; //Se mueve al siguiente nodo para procesamiento
	}
	return (min_node);
}

t_stack_node	*find_max(t_stack_node *stack) //Define una función que busca en una pila y retorna el nodo con el número más grande
{
	long			max; //Para almacenar el valor más grande hasta ahora
	t_stack_node	*max_node; //Para almacenar un puntero que apunta al número más grande

	if (!stack)
		return (NULL);
	max = LONG_MIN; //Asigna al valor más grande hasta ahora, el entero long mínimo
	while (stack) //Hace bucle hasta que se alcance el final de la pila
	{
		if (stack->nbr > max) //Verifica si el valor del nodo actual es mayor que el más grande hasta ahora
		{
			max = stack->nbr; //Si es así, actualiza el número más grande hasta ahora
			max_node = stack; //Establece el puntero para que apunte al nodo con el número más grande hasta ahora
		}
		stack = stack->next; //Se mueve al siguiente nodo para procesamiento
	}
	return (max_node);
}
