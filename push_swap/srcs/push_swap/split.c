/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:01:23 by jmellado          #+#    #+#             */
/*   Updated: 2025/07/01 19:01:24 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Ver las notas a continuación sobre por qué tuvimos que crear un ft_split "mutable", en lugar de usar nuestra versión de libft

#include "../../inc/push_swap.h"

static int	count_words(char *s, char c) //Define una función que devuelve el número de subcadenas en una cadena separadas por un delimitador
{
	int		count; //Para almacenar el conteo de subcadenas
	bool	inside_word; //Una bandera para indicar si estamos dentro de una subcadena o un delimitador

	count = 0;
	while (*s) //Bucle hasta que se alcance el final de la cadena
	{
		inside_word = false; //Establecer el bool a false para iniciar el bucle
		while (*s == c) //Mientras el caracter actual sea el delimitador
			++s; //Moverse al siguiente caracter
		while (*s != c && *s) //Mientras el caracter actual no sea un delimitador y no se haya alcanzado el final de la cadena
		{
			if (!inside_word) //Si no estamos actualmente dentro de la subcadena
			{
				++count; //Incrementar el conteo ya que estamos a punto de entrar en una subcadena
				inside_word = true; //Establecer el bool a true, indicando que hemos encontrado una subcadena
			}
			++s; //Moverse al siguiente caracter de la cadena
		}
	}
	return (count);
}

static char	*get_next_word(char *s, char c) //Define una función que devuelve la nueva subcadena encontrada dentro de una cadena
{
	static int	cursor = 0; //Para mantener registro de la posición dentro de la cadena `s` a través de múltiples llamadas a la función, necesario para continuar procesando la cadena desde donde la dejamos en llamadas previas, esencial para tokenizar una cadena
	char		*next_word; //Para almacenar un puntero de la nueva subcadena
	int			len; //Para almacenar la longitud de la subcadena siendo extraída
	int			i; //Usado para indexar caracteres en la nueva subcadena

	len = 0;
	i = 0;
	while (s[cursor] == c) //Saltar cualquier caracter delimitador consecutivo en la posición actual de la cadena
		++cursor;
	while ((s[cursor + len] != c) && s[cursor + len]) //Calcular la longitud de la subcadena contando caracteres hasta encontrar un delimitador o el final de la cadena
		++len;
	next_word = malloc((size_t)len * sizeof(char) + 1); //Asignar memoria para la nueva subcadena basada en su longitud más un byte para el terminador null
	if (!next_word) //Verificar asignación de memoria fallida
		return (NULL);
	while ((s[cursor] != c) && s[cursor]) //Bucle hasta que se encuentre un delimitador y se alcance el final de la cadena
		next_word[i++] = s[cursor++]; //Copiar cada caracter de la cadena a la nueva subcadena e incrementar `i` y `cursor` después de cada caracter
	next_word[i] = '\0'; //Terminar apropiadamente con null la subcadena recién creada
	return (next_word);
}

char **split(char *s, char c) //Define una función que devuelve las subcadenas de una cadena separadas por un delimitador
{
	int		words_count; //Usado para mantener registro del número de subcadenas en la cadena
	char	**result_array; //Para almacenar un puntero a punteros, el array de todas las subcadenas
	int		i; //Usado para iterar a través del array

	i = 0;
	words_count = count_words(s, c);
	if (!words_count) //Verificar `0` palabras
		exit(1);
	result_array = malloc(sizeof(char *) * (size_t)(words_count + 2)); //Asignar memoria para el result_array basado en el número de palabras (words_count) más dos slots adicionales para tener en cuenta el terminador null al final de la última cadena, y para terminar con null todo el array
	if (!result_array) //Verificar asignación de memoria fallida
		return (NULL);
	while (words_count-- >= 0) //Itera a través de las palabras a ser divididas hasta que todas las palabras hayan sido procesadas
	{
		if (i == 0) //Verificar si el primer caracter de la cadena de entrada es el delimitador
		{
			result_array[i] = malloc(sizeof(char)); //Asignar memoria para una cadena vacía (un solo terminador null)
			if (!result_array[i]) //Verificar asignación de memoria fallida
				return (NULL);
			result_array[i++][0] = '\0'; //Incluir en el array resultado como elementos distintos
			continue ;
		}
		result_array[i++] = get_next_word(s, c); //Si el primer caracter de la cadena no es un delimitador, extraer la subcadena y copiarla en el array resultado
	}
	result_array[i] = NULL; //Terminar apropiadamente con null el array
	return (result_array);
}


/*
 Ambas funciones, `ft_split()` y `split()` dividen una cadena en un array de subcadenas usando un caracter delimitador especificado.
 Sin embargo, las diferencias son:

 #1	Firma de la Función:
	- `ft_split` toma una cadena constante (const char *s) como entrada.
	- `split` toma una cadena mutable (char *s) como entrada.

#2	Mutabilidad de la Entrada:
	- `ft_split` toma una cadena constante (const char *s) como entrada, indicando que no modifica la cadena de entrada.
	- `split` toma una cadena mutable (char *s) como entrada, indicando que puede modificar la cadena de entrada durante la tokenización.
	- Las cadenas mutables pueden ser modificadas in-situ, significando que puedes cambiar los caracteres dentro de la cadena sin crear
	  un nuevo objeto cadena.
	- Las cadenas inmutables, por otro lado, no pueden ser modificadas una vez que son creadas. Cualquier operación que parezca modificar
	  una cadena inmutable en realidad crea una nueva cadena con los cambios deseados.

#TOKENIZACIÓN:
	- La tokenización es el proceso de descomponer un texto o una secuencia de caracteres en unidades más pequeñas llamadas tokens.
	- Los tokens son típicamente palabras, frases, símbolos, u otros elementos significativos dentro del texto.
	- En el caso de push_swap, la tokenización de palabras es el proceso de dividir texto en palabras o unidades similares a palabras.
	  Involucra identificar límites de palabras y separar palabras unas de otras. Por ejemplo, en la oración "La tokenización
	  es importante," las palabras "La," "tokenización," "es," e "importante" son tokens individuales.
	- Propósito:
	  La tokenización es un paso de preprocesamiento que simplifica las tareas de análisis de texto.
	  Permite que el texto sea representado en una forma que puede ser fácilmente procesada por algoritmos y modelos.

#3	Gestión de Memoria:
	- `ft_split` asigna memoria para el array de cadenas resultante y las subcadenas individuales dentro de la función,
	  y libera memoria
	- `split` también asigna memoria para el array de cadenas resultante y subcadenas pero depende del llamador para liberar la memoria.

#4	Uso de Variables Estáticas:
	- `ft_split` no usa variables estáticas en su implementación.
	- `split` usa una variable estática cursor para mantener registro de la posición en la cadena de entrada para tokenización.

#5	Manejo de Errores:
	- `ft_split` devuelve NULL si la asignación de memoria falla durante el proceso de tokenización.
	- `split` sale del programa con un código de error si el número de palabras es cero.

En resumen, ambas funciones realizan tokenización de cadenas, pero tienen diferencias en términos de mutabilidad de entrada, gestión
de memoria, y manejo de errores.
*/
