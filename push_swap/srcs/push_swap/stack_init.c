#include "../../inc/push_swap.h"

static long	ft_atol(const char *s) //Define una función que convierte cada cadena en un valor long
{
	long	result;
	int		sign;

	result = 0;
	sign = 1; 
	while (*s == ' ' || *s == '\t' || *s == '\n' || \
			*s == '\r' || *s == '\f' || *s == '\v')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (ft_isdigit(*s))
		result = result * 10 + (*s++ - '0');
	return (result * sign);
}

static void	append_node(t_stack_node **stack, int n) //Define una función que busca el último nodo para agregar a la lista enlazada
{
	t_stack_node	*node; //Para almacenar un puntero al nuevo nodo a ser creado con el valor `n`
	t_stack_node	*last_node; //Para almacenar un puntero al último nodo actual de la pila

	if (!stack)
		return ;
	node = malloc(sizeof(t_stack_node)); //Asigna memoria para el nuevo nodo
	if (!node)
		return ;
	node->next = NULL; //Establece el puntero next del nuevo nodo a NULL porque será el último nodo en la lista
	node->nbr = n; //Establece el dato `next` del nuevo nodo al valor `n`
	node->cheapest = 0; // Inicializa cheapest a 0;
	// otros elementos en el struct podrían ser inicializados también pero por ahora, este era el único causando un problema de valgrind
	if (!(*stack)) //Verifica si la pila está vacía o actualmente apuntando a NULL, indicando que se necesita encontrar un primer nodo
	{
		*stack = node; //Si está vacía, actualiza el puntero *stack para que apunte al nodo, efectivamente haciéndolo la nueva cabeza de la lista enlazada
		node->prev = NULL; //Establece el puntero anterior del nodo cabeza a NULL ya que es el primer nodo
	}
	else //Si la pila no está vacía, significa que hay nodos existentes en la lista enlazada
	{
		last_node = find_last(*stack); //En cuyo caso, encuentra el último nodo
		last_node->next = node; //Agrega el nuevo nodo al último nodo
		node->prev = last_node; //Actualiza el puntero anterior del nuevo nodo y completa el agregado
	}
}

void	init_stack_a(t_stack_node **a, char **argv) //Define una función que inicia la pila `a` manejando cualquier error y agregando nodos requeridos para completar una pila
{
	long	n;
	int		i;

	i = 0;
	while (argv[i])
	{
		if (error_syntax(argv[i]))
			free_errors(a);
		n = ft_atol(argv[i]);
		if (n > INT_MAX || n < INT_MIN) //Verifica desbordamiento
			free_errors(a);
		if (error_duplicate(*a, (int)n))
			free_errors(a); 
		append_node(a, (int)n); //Si no hay errores, agrega el nodo a la lista enlazada tomando un puntero a la pila `a`, crea un nuevo nodo y asigna `n` a ese nuevo nodo
		i++;
	}
}

t_stack_node	*get_cheapest(t_stack_node *stack) //Define una función que busca el nodo más barato, que está establecido por bool
{
	if (!stack)
		return (NULL);
	while (stack)
	{
		if (stack->cheapest)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}

void	prep_for_push(t_stack_node **stack,
						t_stack_node *top_node,
						char stack_name) //Define una función que mueve el nodo requerido a la cima de la pila
{
	while (*stack != top_node) //Verifica si el nodo requerido no es ya el primer nodo
	{
		if (stack_name == 'a') //Si no, y es la pila `a`, ejecuta lo siguiente
		{
			if (top_node->above_median)
				ra(stack, false);
			else
				rra(stack, false);
		}
		else if (stack_name == 'b') //Si no, y es la pila `b`, ejecuta lo siguiente
		{
			if (top_node->above_median)
				rb(stack, false);
			else
				rrb(stack, false);
		}	
	}
}