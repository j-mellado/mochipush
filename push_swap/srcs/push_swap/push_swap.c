#include "../../inc/push_swap.h"

int	main(int argc, char **argv) //Define un programa que toma una entrada aleatoria de números y los ordena en orden ascendente
{
	t_stack_node	*a; //Para almacenar un puntero a la pila `a`
	t_stack_node	*b; //Para almacenar un puntero a la pila `b`

	a = NULL; //Establece ambos punteros a NULL para evitar comportamiento indefinido
	b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0])) //Verifica conteos de argumentos incorrectos o si el 2do argumento es `0`
		return (1);
	else if (argc == 2) //Verifica si el conteo de argumentos es 2 y el 2do no está vacío, esto implica una cadena
		argv = split(argv[1], ' '); //Llama a `split()` para extraer cada subcadena
	init_stack_a(&a, argv + 1); //Inicia la pila `a`, que también maneja errores
	if (!stack_sorted(a)) //Verifica si la pila no está ordenada
	{
		if (stack_len(a) == 2) //Si no, y hay dos números, intercambia los primeros dos nodos
			sa(&a, false);
		else if (stack_len(a) == 3) //Si no, y hay tres números, llama al algoritmo de ordenamiento de tres
			sort_three(&a);
		else
			sort_stacks(&a, &b); //Si no, y hay más de tres números, llama al algoritmo de ordenamiento de pilas
	}
	free_stack(&a); //Limpia la pila
	return (0);
}
