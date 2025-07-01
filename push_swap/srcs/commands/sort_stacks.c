#include "../../inc/push_swap.h"

static void	rotate_both(t_stack_node **a,
						t_stack_node **b,
						t_stack_node *cheapest_node) //Define una función que rota ambos nodos superiores `a` y `b` al fondo de sus pilas, si es el movimiento más barato
{
	while (*b != cheapest_node->target_node
		&& *a != cheapest_node) //Mientras el nodo `b` actual no sea el nodo objetivo del nodo más barato de `a`, y el nodo superior `a` actual no sea el nodo superior
		rr(a, b, false); //Rota ambos nodos `a` y `b`
	current_index(*a);
	current_index(*b);
}

static void	rev_rotate_both(t_stack_node **a,
								t_stack_node **b,
								t_stack_node *cheapest_node) //Define una función que rota ambos nodos del fondo `a` y `b` a la cima de sus pilas, si es el movimiento más barato
{
	while (*b != cheapest_node->target_node
		&& *a != cheapest_node) //Mientras el nodo `b` actual no sea el nodo objetivo del nodo más barato de `a` && y el nodo `a` actual no sea el más barato
		rrr(a, b, false); //Rota en reversa ambos nodos `a` y `b`
	current_index(*a); //Actualiza las posiciones actuales de los nodos
	current_index(*b);
}

static void	move_a_to_b(t_stack_node **a, t_stack_node **b) //Define una función que prepara los nodos más baratos en la cima de las pilas para empujar nodos `a` a la pila `b`, hasta que queden tres nodos en `a`
{
	t_stack_node	*cheapest_node; //Para almacenar el puntero al nodo `a` más barato

	cheapest_node = get_cheapest(*a); 
	if (cheapest_node->above_median 
		&& cheapest_node->target_node->above_median) //Si tanto el nodo `a` más barato como su nodo objetivo `b` están arriba de la mediana
		rotate_both(a, b, cheapest_node);
	else if (!(cheapest_node->above_median) 
		&& !(cheapest_node->target_node->above_median)) //Si tanto el nodo `a` más barato como su nodo objetivo `b` están abajo de la mediana
		rev_rotate_both(a, b, cheapest_node); //`rev_rotate_both` se ejecutará si ninguno de los nodos está en la cima
	prep_for_push(a, cheapest_node, 'a'); //Asegura que el nodo más barato esté en la cima, listo para empujar
	prep_for_push(b, cheapest_node->target_node, 'b'); //Asegura que el nodo objetivo esté en la cima, listo para empujar
	pb(b, a, false);
}

static void	move_b_to_a(t_stack_node **a, t_stack_node **b) //Define una función que prepara los nodos objetivo `a` de `b` para empujar todos los nodos `b` de vuelta a la pila `a`
{
	prep_for_push(a, (*b)->target_node, 'a'); //Asegura que el nodo objetivo `a` de `b` esté en la cima de la pila
	pa(a, b, false); 
}

static void	min_on_top(t_stack_node **a) //Define una función que mueve el número más pequeño a la cima
{
	while ((*a)->nbr != find_min(*a)->nbr) //Mientras el número más pequeño no esté en la cima
	{
		if (find_min(*a)->above_median) //Rota o rota en reversa según la posición del nodo en la mediana
			ra(a, false);
		else
			rra(a, false);
	}
}

void	sort_stacks(t_stack_node **a, t_stack_node **b) //Define una función que ordena la pila `a` si tiene más de 3 nodos
{
	int	len_a; //Para almacenar la longitud de la pila `a`

	len_a = stack_len(*a);
	if (len_a-- > 3 && !stack_sorted(*a)) //Si la pila `a` tiene más de tres nodos y no están ordenados
		pb(b, a, false);
	if (len_a-- > 3 && !stack_sorted(*a)) //Si la pila `a` aún tiene más de tres nodos y no están ordenados
		pb(b, a, false);
	while (len_a-- > 3 && !stack_sorted(*a)) //Si la pila `a` aún tiene más de tres nodos y no están ordenados
	{
		init_nodes_a(*a, *b); //Inicia todos los nodos de ambas pilas
		move_a_to_b(a, b); //Mueve los nodos `a` más baratos a una pila `b` ordenada, hasta que queden tres nodos en la pila `a`
	}
	sort_three(a);
	while (*b) //Hasta que se alcance el final de la pila `b`
	{
		init_nodes_b(*a, *b); //Inicia todos los nodos de ambas pilas
		move_b_to_a(a, b); //Mueve todos los nodos `b` de vuelta a una pila `a` ordenada
	}
	current_index(*a); //Actualiza la posición actual de la pila `a`
	min_on_top(a); //Asegura que el número más pequeño esté en la cima
}
