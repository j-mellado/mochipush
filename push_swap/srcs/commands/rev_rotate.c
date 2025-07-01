/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:00:52 by jmellado          #+#    #+#             */
/*   Updated: 2025/07/01 19:00:53 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

static void	rev_rotate(t_stack_node **stack) //Define una función que rota el nodo del fondo de una pila, a la cima
{
	t_stack_node	*last; //Para almacenar el puntero al último nodo

	if (!*stack || !(*stack)->next) //Verifica si la pila está vacía, o si hay un nodo
		return ;
	last = find_last(*stack);
	last->prev->next = NULL; //Asigna al atributo `next` del nodo antes de sí mismo, `NULL` efectivamente estableciéndolo como el último nodo actual
	last->next = *stack; //Asigna a su propio atributo `next` como el nodo superior de la pila
	last->prev = NULL; //Se desconecta del nodo antes de él
	*stack = last;  //Completa agregándose a la cima de la pila, y ahora mantiene el puntero al nodo superior
	last->next->prev = last; //Actualiza el último nodo actual de la pila
}

void	rra(t_stack_node **a, bool print) //Rota el fondo de `a` a la cima de la pila e imprime la instrucción
{
	rev_rotate(a);
	if (!print)
		ft_printf("rra\n");
}

void	rrb(t_stack_node **b, bool print) //Rota el fondo de `b` a la cima de la pila e imprime la instrucción
{
	rev_rotate(b);
	if (!print)
		ft_printf("rrb\n");
}

void	rrr(t_stack_node **a, t_stack_node **b, bool print) //Simultáneamente rota los nodos del fondo de ambas pilas a la cima de sus pilas, reduciendo a la mitad el costo de las instrucciones
{
	rev_rotate(a);
	rev_rotate(b);
	if (!print)
		ft_printf("rrr\n");
}
