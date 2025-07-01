#include "../../inc/push_swap.h"

void	current_index(t_stack_node *stack)
{
	int	i; //Para almacenar el índice del nodo actual
	int	median; //Para almacenar la posición de la mediana de la pila

	i = 0; //El primer índice es `0`
	if (!stack) //Verifica una pila vacía
		return ;
	median = stack_len(stack) / 2; //Calcula la mediana dividiendo la longitud de una pila por 2
	while (stack) //Hace bucle a través de todos los nodos hasta que se alcance el final de la pila
	{
		stack->index = i; //Asigna el valor del índice actual al nodo actual
		if (i <= median) //Verifica si el nodo actual está arriba o abajo de la mediana
			stack->above_median = true; //Si está arriba, establece el dato above_median del nodo a true
		else
			stack->above_median = false; //Si está abajo, establece el dato above_median del nodo a false
		stack = stack->next; //Se mueve al siguiente nodo para indexar
		++i; //Incrementa el valor del índice para establecer el siguiente nodo con
	}
}

static void	set_target_a(t_stack_node *a, t_stack_node *b)//Encuentra el objetivo del nodo `a` en la pila `b`
{
	t_stack_node	*current_b; //Para almacenar el puntero al nodo actual en la pila `b` e iterar a través de cada nodo siguiente
	t_stack_node	*target_node; //Para almacenar el puntero al nodo objetivo en la pila `b`
	long			best_match_index; //En este caso, el mejor índice de coincidencia almacena el valor del "número más pequeño más cercano" hasta ahora

	while (a) //Mientras tengamos nodos en la pila `a`
	{
		best_match_index = LONG_MIN; //Asigna el `long` más pequeño como el número más pequeño más cercano hasta ahora
		current_b = b; //Asigna a `current_b` el nodo `b` actual
		while (current_b) //Busca iterativamente a través de todos los nodos en la pila `b` hasta que se alcance el final de la pila
		{
			if (current_b->nbr < a->nbr 
				&& current_b->nbr > best_match_index) //Verifica si el nodo `b` es menor que el nodo `a` && mayor que el número más pequeño más cercano hasta ahora
			{
				best_match_index = current_b->nbr; //Si es así, actualiza el valor del número más pequeño más cercano hasta ahora
				target_node = current_b; //Asigna el nodo `b` actual como el `target_node`
			}
			current_b = current_b->next; //Se mueve al siguiente nodo `b` para comparación, hasta que se encuentre un "número más pequeño más cercano"
		}
		if (best_match_index == LONG_MIN) //Verifica si el LONG_MIN no ha cambiado, significa que no hemos encontrado nada más pequeño
			a->target_node = find_max(b); //Si es así, encuentra el `nbr` más grande y establece esto como el nodo objetivo
		else
			a->target_node = target_node; //Si no se encuentra un "número más pequeño más cercano", y la mejor coincidencia ha cambiado
		a = a->next; //Se mueve al siguiente nodo `a` para encontrar su nodo objetivo `b`
	}
}

static void	cost_analysis_a(t_stack_node *a, t_stack_node *b) //Define una función que analiza el costo del nodo `a` junto con su nodo objetivo `b`, que es la suma del número de instrucciones para que ambos nodos roten a la cima de sus pilas
{
	int	len_a; //Para almacenar la longitud de la pila `a`
	int	len_b; //Para almacenar la longitud de la pila `b`

	len_a = stack_len(a);
	len_b = stack_len(b);
	while (a) //Hace bucle a través de cada nodo hasta que se alcance el final de la pila
	{
		a->push_cost = a->index; //Asigna al costo de empuje del nodo `a` actual, su valor de índice
		if (!(a->above_median)) //Verifica si el dato above_median es false, significando que está abajo de la mediana
			a->push_cost = len_a - (a->index); //Si es así, actualiza el costo de empuje del nodo `a` a la longitud de la pila - índice
		if (a->target_node->above_median) //Verifica si el nodo objetivo `b` del nodo `a` tiene un atributo above median "true", significando que el nodo objetivo `b` está arriba de la mediana
			a->push_cost += a->target_node->index; //Si es así, actualiza el costo de empuje del nodo `a`, la suma de (su índice actual) + (el índice de su nodo objetivo `b`)
		else //Si el nodo `a` está efectivamente arriba de la mediana y su nodo objetivo `b` está abajo de la mediana
			a->push_cost += len_b - (a->target_node->index); //Actualiza el costo de empuje del nodo `a`, la suma de (su índice actual) + (longitud de la pila `b` - el índice de su nodo objetivo `b`)
		a = a->next; //Se mueve al siguiente nodo `a` para su análisis de costo
	}
}

void	set_cheapest(t_stack_node *stack) //Define una función que establece el atributo `cheapest` de un nodo como `true` o `false`
{
	long			cheapest_value; //Para almacenar el valor del nodo más barato hasta ahora
	t_stack_node	*cheapest_node; //Para almacenar un puntero al nodo más barato hasta ahora

	if (!stack) //Verifica una pila vacía
		return ;
	cheapest_value = LONG_MAX; //Asigna el `long` más grande como el valor más barato hasta ahora
	while (stack) //Hace bucle a través de cada nodo hasta que se alcance el final de la pila, y encontramos el nodo más barato
	{
		if (stack->push_cost < cheapest_value) //Verifica si el costo de empuje del nodo actual es más barato que el valor más barato hasta ahora
		{
			cheapest_value = stack->push_cost; //Si es así, actualiza el valor más barato al costo de empuje del nodo actual
			cheapest_node = stack; //Asigna el nodo actual como el nodo más barato hasta ahora
		}
		stack = stack->next; //Se mueve al siguiente nodo para comparación
	}
	cheapest_node->cheapest = true; //Después de iterar a través de la pila, si no se encuentra un nodo más barato que el actual, entonces establece el atributo `cheapest` del nodo más barato a `true` en la estructura de datos
}

void	init_nodes_a(t_stack_node *a, t_stack_node *b) //Define una función que combina todas las funciones necesarias para preparar la pila `a`, lista para nuestro empuje y ordenamiento. Estas funciones establecen los datos dentro de la estructura del nodo
{
	current_index(a);
	current_index(b);
	set_target_a(a, b);
	cost_analysis_a(a, b);
	set_cheapest(a);
}