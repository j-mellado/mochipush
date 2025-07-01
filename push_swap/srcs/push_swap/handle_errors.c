#include "../../inc/push_swap.h"

int	error_syntax(char *str_n) //Define una función para manejar errores de sintaxis, y retorna `1` para `error` si alguna de las siguientes condiciones se cumple
{
	if (!(*str_n == '+'
			|| *str_n == '-'
			|| (*str_n >= '0' && *str_n <= '9'))) //Verifica si el primer carácter de la cadena de entrada no contiene un signo o un dígito
		return (1);
	if ((*str_n == '+'
			|| *str_n == '-')
		&& !(str_n[1] >= '0' && str_n[1] <= '9')) //Verifica si el primer carácter de la cadena de entrada contiene un signo, pero el segundo carácter no contiene un dígito
		return (1);
	while (*++str_n) //Si las condiciones de error anteriores se pasan, pre-incrementa para apuntar al siguiente carácter en la cadena, y hace bucle hasta que se alcance el final de la cadena
	{
		if (!(*str_n >= '0' && *str_n <= '9')) //Verifica si el siguiente carácter en la cadena no es un dígito
			return (1);
	}
	return (0);
}

int	error_duplicate(t_stack_node *a, int n) //Define una función que verifica números de entrada duplicados en la pila `a`
{
	if (!a) //Verifica una pila vacía
		return (0);
	while (a) //Hace bucle hasta que se alcance el final de la pila `a`
	{
		if (a->nbr == n) //Verifica si el valor del nodo actual es igual a `n`. Referirse a `init_stack_a()`
			return (1);
		a = a->next; //Se mueve al siguiente nodo para verificar duplicados
	}
	return (0);
}

void	free_stack(t_stack_node **stack) //Define una función para liberar una pila si hay errores
{
	t_stack_node	*tmp; //Para almacenar el siguiente nodo en la pila antes de que el nodo actual sea liberado, porque una vez que un nodo es liberado, no puedes acceder a su puntero next
	t_stack_node	*current;

	if (!stack) //Verifica una pila vacía
		return ;
	current = *stack;
	while (current) //Mientras un nodo exista en la pila
	{
		tmp = current->next; //Asigna a `tmp` el puntero al siguiente nodo
		current->nbr = 0; //Asignar el nodo a `0` antes de liberar no es estrictamente necesario pero puede ayudar a detectar errores potenciales como memory-leaks y mejorar la depuración
		free(current); //Libera el nodo actual, desasignando la memoria ocupada por ese nodo
		current = tmp; //Asigna `tmp` como el primer nodo actual
	}
	*stack = NULL;
}

void	free_errors(t_stack_node **a) //Define una función que, al encontrar un error único, libera la pila e imprime un mensaje de error
{
	free_stack(a);
	ft_printf("Error\n");
	exit(1);
}
