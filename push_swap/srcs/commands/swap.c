#include "../../inc/push_swap.h"

static void	swap(t_stack_node **head) //Define una función que intercambia las posiciones del nodo superior y segundo nodo de una pila
{
	if (!*head || !(*head)->next) //Verifica si el nodo superior, o segundo nodo de una pila existe
		return ;
	*head = (*head)->next; //Actualiza `head` para que apunte al siguiente nodo, efectivamente intercambiando el primer y segundo nodos
	(*head)->prev->prev = *head; //Actualiza el puntero `prev` del nodo antes del `nuevo head` para que apunte al `nuevo head`
	(*head)->prev->next = (*head)->next; //Actualiza el puntero `next` del nodo antes del `nuevo head` para saltar el `viejo head` y apuntar directamente al `nuevo head`
	if ((*head)->next) //Verifica si hay un nodo `next` después del `nuevo head` y
		(*head)->next->prev = (*head)->prev; //Si es así, actualiza su puntero `prev` para que apunte de vuelta al `nuevo head`
	(*head)->next = (*head)->prev; //Actualiza el puntero `next` del `nuevo head` para que apunte al `viejo head`, efectivamente revirtiendo sus posiciones
	(*head)->prev = NULL; //Establece el puntero `prev` del `nuevo head` a `NULL` completando el intercambio
}

void	sa(t_stack_node	**a, bool print) //Intercambia los primeros dos nodos de la pila `a` e imprime la instrucción
{
	swap(a);
	if (!print)
		ft_printf("sa\n");
}

void	sb(t_stack_node **b, bool print) //Intercambia los primeros dos nodos de la pila `b` e imprime la instrucción
{
	swap(b);
	if (!print)
		ft_printf("sb\n");
}

void	ss(t_stack_node **a, t_stack_node **b, bool print) //Simultáneamente intercambia los primeros dos nodos de la pila e imprime la instrucción
{
	swap(a);
	swap(b);
	if (!print)
		ft_printf("ss\n");
}