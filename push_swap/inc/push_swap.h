/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:13:13 by jmellado          #+#    #+#             */
/*   Updated: 2025/07/01 19:13:14 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h> //Para usar flags bool, ej. para imprimir o no imprimir
# include <limits.h> //Para definir macros MIN y MAX
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"

typedef struct s_stack_node //Un contenedor de datos encerrado en llaves {}. `s_` para struct
{
	int					nbr; //El número a ordenar
	int					index; //La posición del número en la pila
	int					push_cost; //Cuántos comandos en total
	bool				above_median; //Usado para calcular `push_cost`
	bool				cheapest; //El nodo que es más barato para ejecutar comandos
	struct s_stack_node	*target_node; //El nodo objetivo de un nodo en la pila opuesta
	struct s_stack_node	*next; //Un puntero al siguiente nodo
	struct s_stack_node	*prev; //Un puntero al nodo anterior
}	t_stack_node; //El "nombre acortado", "t_stack_node". `t_` para tipo

//***Manejo de errores
int				error_syntax(char *str_n);
int				error_duplicate(t_stack_node *a, int n);
void			free_stack(t_stack_node **stack);
void			free_errors(t_stack_node **a);

//***Iniciación de pilas
void			init_stack_a(t_stack_node **a, char **argv); //Iniciar pila `a` antes del procesamiento
char			**split(char *s, char c); //Para manejar entrada de números como argumento string, ej. encerrados en " "

//***Iniciación de nodos
void			init_nodes_a(t_stack_node *a, t_stack_node *b); //Para preparar todos los nodos para empujar `a` a `b`
void			init_nodes_b(t_stack_node *a, t_stack_node *b); //Para preparar todos los nodos para empujar `b` de vuelta a `a`
void			current_index(t_stack_node *stack); //Establecer el índice actual del nodo
void			set_cheapest(t_stack_node *stack); //Establecer el nodo más barato de la pila
t_stack_node	*get_cheapest(t_stack_node *stack); //Obtener el nodo más barato de una pila
void			prep_for_push(t_stack_node **s, t_stack_node *n, char c); //Preparar los nodos requeridos en la cima para empujar

//***Utilidades de pila
int				stack_len(t_stack_node *stack); //Calcular la longitud de una pila
t_stack_node	*find_last(t_stack_node *stack); //Encontrar el último nodo de una pila
bool			stack_sorted(t_stack_node *stack); //Para verificar si una pila está ordenada
t_stack_node	*find_min(t_stack_node *stack); //Encontrar el número más pequeño
t_stack_node	*find_max(t_stack_node *stack); //Encontrar el número más grande

//***Comandos
void			sa(t_stack_node **a, bool print);
void			sb(t_stack_node **b, bool print);
void			ss(t_stack_node **a, t_stack_node **b, bool print);
void			ra(t_stack_node **a, bool print);
void			rb(t_stack_node **b, bool print);
void			rr(t_stack_node **a, t_stack_node **b, bool print);
void			rra(t_stack_node **a, bool print);
void			rrb(t_stack_node **b, bool print);
void			rrr(t_stack_node **a, t_stack_node **b, bool print);
void			pa(t_stack_node **a, t_stack_node **b, bool print);
void			pb(t_stack_node **b, t_stack_node **a, bool print);

//***Algoritmo
void			sort_three(t_stack_node **a);
void			sort_stacks(t_stack_node **a, t_stack_node **b); //Algoritmo Turk

#endif
