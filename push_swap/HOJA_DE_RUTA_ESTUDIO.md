# 🗺️ HOJA DE RUTA COMPLETA PARA DOMINAR PUSH_SWAP

## 📚 **FASE 1: FUNDAMENTOS CONCEPTUALES (2-3 días)**

### **1.1 Entender el problema base**
- **¿Qué es push_swap?** Un programa que ordena números usando dos pilas con operaciones limitadas
- **Objetivo:** Ordenar números de menor a mayor en la pila A con el mínimo número de operaciones
- **Restricciones:** Solo puedes usar operaciones específicas (sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr)

### **1.2 Estructura de datos fundamental**
```c
typedef struct s_stack_node {
    int nbr;                    // El número a ordenar
    int index;                  // Posición en la pila
    int push_cost;              // Costo de mover este nodo
    bool above_median;          // Si está en la mitad superior
    bool cheapest;              // Si es el más barato de mover
    struct s_stack_node *target_node;  // Nodo objetivo en pila opuesta
    struct s_stack_node *next;  // Puntero al siguiente
    struct s_stack_node *prev;  // Puntero al anterior
} t_stack_node;
```

**⚡ PUNTOS CLAVE PARA LA PRESENTACIÓN:**
- Es una lista doblemente enlazada circular
- Cada nodo tiene metadata para optimizar el algoritmo
- La estructura permite acceso bidireccional eficiente

---

## 📖 **FASE 2: OPERACIONES BÁSICAS (1-2 días)**

### **2.1 Estudiar las 11 operaciones permitidas:**

| Operación | Descripción | Archivo |
|-----------|-------------|---------|
| `sa`, `sb`, `ss` | Intercambiar dos primeros elementos | `swap.c` |
| `pa`, `pb` | Push: mover elemento entre pilas | `push.c` |
| `ra`, `rb`, `rr` | Rotate: primer elemento al final | `rotate.c` |
| `rra`, `rrb`, `rrr` | Reverse rotate: último al principio | `rev_rotate.c` |

### **2.2 Analizar implementaciones:**
1. **Empezar con `swap.c`** - Es la más simple
2. **Seguir con `push.c`** - Fundamental para el algoritmo
3. **Entender rotaciones** - Clave para posicionamiento

---

## 🧠 **FASE 3: ALGORITMOS DE ORDENAMIENTO (3-4 días)**

### **3.1 Caso especial: 3 elementos (`sort_three.c`)**
```c
void sort_three(t_stack_node **a);
```
- **Estudiar todas las combinaciones posibles:** 3! = 6 casos
- **Memorizar la lógica:** Encuentra el máximo y determina la secuencia óptima
- **Pregunta típica:** "¿Por qué solo necesitas encontrar el máximo?"

### **3.2 Algoritmo principal: Turk Algorithm (`sort_stacks.c`)**

**🎯 CONCEPTO CENTRAL:** Algoritmo de costo mínimo por nodo

**Flujo principal:**
1. **Fase A→B:** Mover todos excepto 3 elementos de A a B
2. **Ordenar 3:** Usar `sort_three` en los últimos 3
3. **Fase B→A:** Devolver todos de B a A en orden correcto
4. **Finalizar:** Asegurar que el mínimo esté arriba

---

## 🔬 **FASE 4: ANÁLISIS PROFUNDO DEL ALGORITMO TURK (4-5 días)**

### **4.1 Inicialización de nodos A→B (`init_a_to_b.c`)**

**Funciones clave:**
```c
void current_index(t_stack_node *stack);        // Asignar índices
void set_target_a(t_stack_node *a, t_stack_node *b); // Encontrar objetivos
void cost_analysis_a(t_stack_node *a, t_stack_node *b); // Calcular costos
void set_cheapest(t_stack_node *stack);         // Marcar el más barato
```

**⚡ PREGUNTA CLAVE:** "¿Cómo se calcula el costo de mover un nodo?"
- **Respuesta:** Suma del costo de rotar el nodo a la cima + costo de rotar su objetivo a la cima

### **4.2 Inicialización de nodos B→A (`init_b_to_a.c`)**

**Diferencia crucial:**
- En A→B: Buscamos el siguiente menor en B
- En B→A: Buscamos el siguiente mayor en A

### **4.3 Análisis de costo (FUNDAMENTAL)**

```c
static void cost_analysis_a(t_stack_node *a, t_stack_node *b)
{
    int len_a = stack_len(a);
    int len_b = stack_len(b);
    
    // Costo de rotar nodo A a la cima
    if (a->above_median)
        a->push_cost = a->index;
    else
        a->push_cost = len_a - a->index;
        
    // Añadir costo del nodo objetivo en B
    if (a->target_node->above_median)
        a->push_cost += a->target_node->index;
    else
        a->push_cost += len_b - a->target_node->index;
}
```

**🎯 PREGUNTA CRUCIAL:** "¿Por qué usamos `above_median`?"
- **Respuesta:** Para decidir si es más eficiente rotar hacia adelante (ra) o hacia atrás (rra)

---

## 🛠️ **FASE 5: MANEJO DE ENTRADA Y ERRORES (1-2 días)**

### **5.1 Inicialización (`stack_init.c`)**
- **Conversión:** `ft_atol` para convertir strings a números
- **Validación:** Verificar límites de int
- **Construcción:** Crear lista enlazada

### **5.2 Manejo de errores (`handle_errors.c`)**
- **Sintaxis:** Números inválidos, caracteres no numéricos
- **Duplicados:** Números repetidos
- **Memoria:** Liberación correcta en caso de error

### **5.3 Parsing especial (`split.c`)**
- **Caso especial:** Entrada como string único "1 2 3 4 5"
- **Tokenización:** Dividir por espacios
- **Diferencia con libft:** Versión mutable vs inmutable

---

## 🎯 **FASE 6: PREPARACIÓN PARA PREGUNTAS TÉCNICAS (2-3 días)**

### **6.1 Preguntas típicas y respuestas:**

**P: "¿Cuál es la complejidad temporal del algoritmo?"**
**R:** O(n²) en el peor caso, pero en promedio es más eficiente que otros algoritmos simples.

**P: "¿Por qué usas lista doblemente enlazada circular?"**
**R:** Permite acceso eficiente tanto al primer como último elemento, crucial para las operaciones de rotación.

**P: "¿Cómo decides qué nodo mover primero?"**
**R:** Calculando el costo total de cada nodo (costo propio + costo del objetivo) y eligiendo el menor.

**P: "¿Qué pasa si todos los números ya están ordenados?"**
**R:** El programa detecta esto con `stack_sorted()` y termina inmediatamente sin operaciones.

**P: "¿Por qué el algoritmo es de A→B y luego B→A?"**
**R:** Porque necesitamos espacio de trabajo (pila B) y es más eficiente hacer dos pasadas optimizadas.

**P: "¿Cómo manejas los números negativos?"**
**R:** El algoritmo funciona igual, solo ordena de menor a mayor independientemente del signo.

**P: "¿Qué pasa si hay duplicados?"**
**R:** El programa detecta duplicados y termina con error antes de procesar.

**P: "¿Por qué no usas quicksort o mergesort?"**
**R:** Porque estamos limitados a operaciones específicas de pila, no tenemos acceso aleatorio al array.

### **6.2 Optimizaciones clave:**

1. **Rotación doble:** Cuando nodo y objetivo están en el mismo lado
2. **Cálculo de median:** Para decidir dirección de rotación
3. **Búsqueda de objetivos:** Algoritmo específico para encontrar el mejor match

---

## 📝 **FASE 7: PRÁCTICA Y SIMULACIÓN (2-3 días)**

### **7.1 Ejercicios recomendados:**
1. **Traza manual:** Ejecutar el algoritmo paso a paso con ejemplos pequeños
2. **Casos edge:** ¿Qué pasa con 2 números? ¿Con números negativos?
3. **Optimización:** ¿Puedes encontrar casos donde el algoritmo no es óptimo?

### **7.2 Casos de prueba importantes:**
```bash
# Caso simple
./push_swap 3 2 1

# Caso complejo
./push_swap 5 4 3 2 1

# Números negativos
./push_swap -1 -2 0 1 2

# String como argumento
./push_swap "3 2 1 5 4"

# Casos edge
./push_swap 1         # Solo un número
./push_swap 1 2       # Ya ordenado
./push_swap 2147483647 -2147483648  # Límites de int
```

---

## 🚀 **CHECKLIST FINAL PARA LA PRESENTACIÓN:**

### ✅ **Conceptos que DEBES dominar:**
- [ ] Estructura `t_stack_node` y por qué cada campo existe
- [ ] Las 11 operaciones y cuándo usar cada una
- [ ] Algoritmo Turk: concepto de costo mínimo
- [ ] Diferencia entre fase A→B y B→A
- [ ] Cómo se calcula `push_cost`
- [ ] Por qué se usa `above_median`
- [ ] Manejo de casos especiales (2, 3 elementos)
- [ ] Detección y manejo de errores
- [ ] Por qué es más eficiente que otros algoritmos simples
- [ ] Cómo se optimiza la selección del nodo a mover

### ✅ **Preguntas que te pueden hacer:**
- [ ] "Explica el algoritmo en 2 minutos"
- [ ] "¿Por qué elegiste esta estructura de datos?"
- [ ] "¿Cómo optimizarías el algoritmo?"
- [ ] "¿Qué pasa si cambias el orden de las operaciones?"
- [ ] "Explica la diferencia entre rotate y reverse rotate"
- [ ] "¿Cómo decides cuándo usar ra vs rra?"
- [ ] "¿Qué ventajas tiene sobre bubble sort?"
- [ ] "¿Cómo funciona la búsqueda del nodo objetivo?"

---

## 📊 **CRONOGRAMA SUGERIDO (14 días):**

**Días 1-3:** Fundamentos y estructura de datos
- Leer `push_swap.h` completo
- Entender `t_stack_node`
- Estudiar el problema conceptual

**Días 4-5:** Operaciones básicas
- Analizar `swap.c`, `push.c`, `rotate.c`, `rev_rotate.c`
- Practicar mentalmente las operaciones
- Entender las funciones con double suffix (ss, rr, rrr)

**Días 6-9:** Algoritmo Turk (núcleo del proyecto)
- Estudiar `sort_stacks.c` línea por línea
- Analizar `init_a_to_b.c` y `init_b_to_a.c`
- Entender el cálculo de costos
- Practicar con ejemplos pequeños

**Días 10-11:** Manejo de entrada/errores
- Revisar `stack_init.c`, `handle_errors.c`, `split.c`
- Entender `stack_utils.c`
- Probar casos edge

**Días 12-14:** Práctica y preparación para preguntas
- Simular presentaciones
- Preparar respuestas a preguntas comunes
- Revisar puntos débiles

---

## 🎭 **TIPS PARA LA PRESENTACIÓN:**

### **Estructura recomendada (10-15 min):**

1. **Introducción (2 min):**
   - "Push_swap es un algoritmo de ordenamiento con restricciones"
   - Mostrar las dos pilas y operaciones permitidas

2. **Estructura de datos (2 min):**
   - Explicar `t_stack_node`
   - Por qué lista doblemente enlazada circular

3. **Algoritmo principal (6-8 min):**
   - Casos especiales (2-3 elementos)
   - Algoritmo Turk para casos mayores
   - Concepto de costo mínimo
   - Fases A→B y B→A

4. **Demostración (2-3 min):**
   - Ejemplo con 5 números
   - Mostrar cálculo de costos

5. **Preguntas y respuestas**

### **Consejos específicos:**

1. **Empieza con el problema:** "Imaginen que tienen dos pilas y solo pueden hacer estas operaciones..."
2. **Usa ejemplos visuales:** Dibuja las pilas en la pizarra
3. **Explica el "por qué":** No solo qué hace el código, sino por qué está diseñado así
4. **Demuestra comprensión:** Menciona alternativas y por qué las descartaste
5. **Sé honesto:** Si hay partes que no optimizaste, explica por qué
6. **Prepara respuestas cortas:** Las preguntas técnicas necesitan respuestas concisas
7. **Usa terminología correcta:** "Lista doblemente enlazada circular", "costo de rotación", etc.

---

## 📋 **ARQUITECTURA DEL PROYECTO:**

### **Modularización:**
```
push_swap/
├── inc/push_swap.h          # Definiciones y prototipos
├── srcs/
│   ├── commands/            # Operaciones básicas
│   │   ├── swap.c          # sa, sb, ss
│   │   ├── push.c          # pa, pb
│   │   ├── rotate.c        # ra, rb, rr
│   │   ├── rev_rotate.c    # rra, rrb, rrr
│   │   ├── sort_three.c    # Caso especial 3 elementos
│   │   └── sort_stacks.c   # Algoritmo principal
│   └── push_swap/          # Lógica principal
│       ├── push_swap.c     # Main y control de flujo
│       ├── stack_init.c    # Inicialización
│       ├── stack_utils.c   # Utilidades
│       ├── handle_errors.c # Manejo de errores
│       ├── split.c         # Parsing especial
│       ├── init_a_to_b.c   # Preparación A→B
│       └── init_b_to_a.c   # Preparación B→A
└── libft/                   # Librería auxiliar
```

### **Flujo de ejecución:**
1. `main()` → Validar argumentos
2. `init_stack_a()` → Crear pila inicial
3. `stack_sorted()` → Verificar si ya está ordenado
4. `sort_three()` o `sort_stacks()` → Algoritmo apropiado
5. Finalizar

---

## 🎯 **PUNTOS CLAVE PARA RECORDAR:**

### **Lo más importante:**
1. **El algoritmo Turk es el corazón del proyecto**
2. **El concepto de "costo mínimo" es fundamental**
3. **La estructura `t_stack_node` está optimizada para el algoritmo**
4. **Las dos fases (A→B y B→A) tienen lógicas diferentes**
5. **La eficiencia viene de elegir siempre el nodo más barato**

### **Errores comunes en presentaciones:**
- No explicar por qué se usa lista doblemente enlazada
- No mencionar la optimización de costos
- No diferenciar entre las dos fases del algoritmo
- No explicar `above_median`
- No prepararse para preguntas sobre complejidad temporal

---

## 🏆 **OBJETIVOS DE APRENDIZAJE:**

Al final de estos 14 días deberías poder:

1. **Explicar el algoritmo completo** en menos de 10 minutos
2. **Responder cualquier pregunta técnica** sobre implementación
3. **Simular el algoritmo manualmente** con ejemplos pequeños
4. **Justificar cada decisión de diseño** del código
5. **Comparar con otros algoritmos** y explicar ventajas/desventajas
6. **Identificar y explicar optimizaciones** implementadas
7. **Manejar preguntas sobre casos edge** y manejo de errores

---

¡Buena suerte con tu presentación! 🚀
