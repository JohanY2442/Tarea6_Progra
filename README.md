# Tarea6_Programación
# Integrantes:
Johan Yadir Huayta Enriquez

Nicolas Lara Alvarez
# Ejercicio 1 - Análisis de Degradación del BST

Un Árbol Binario de Búsqueda (BST) sin balanceo puede degradarse a complejidad $O(n)$ cuando los datos se insertan en orden. A continuación se explica matemáticamente por qué ocurre.

## El costo depende de la altura

Insertar, buscar y eliminar recorren un único camino desde la raíz hacia abajo, con trabajo constante por nivel. Por lo tanto, el costo de cada operación es $\Theta(h)$, donde $h$ es la altura del árbol.

Un BST con $n$ nodos cumple:

$$\lceil \log_2(n+1) \rceil \le h \le n$$

La cota inferior se debe a que un árbol de altura $h$ tiene como máximo $2^h - 1$ nodos. La cota superior se debe a que cada nivel tiene al menos un nodo. La propiedad del BST no obliga a que $h$ se acerque a la cota inferior.

## Inserción de claves ordenadas

Sea $T_k$ el árbol que resulta de insertar $1, 2, \dots, k$ en ese orden. Se demuestra por inducción que $T_k$ es una cadena derecha de $k$ nodos:

- **Base:** $T_1$ es un solo nodo.
- **Paso:** si $T_k$ es una cadena derecha cuyo máximo es $k$, la clave $k+1$ es mayor que todas las existentes. La inserción baja siempre por la derecha hasta el último nodo y se enlaza como su hijo derecho, por lo que $T_{k+1}$ es una cadena derecha de $k+1$ nodos.

Entonces $h(T_n) = n$.

## Costo total

Insertar la clave $i$ requiere recorrer una cadena de $i-1$ nodos. El costo acumulado es:

$$\sum_{i=1}^{n} i = \frac{n(n+1)}{2} = \Theta(n^2)$$

Es decir, $\Theta(n)$ por inserción, y cualquier búsqueda posterior también cuesta $\Theta(n)$.

## Se pierde la propiedad AVL

En la cadena, para $n \ge 3$, se cumple $H(r_{left}) = 0$ y $H(r_{right}) = n-1$, de modo que:

$$|H(r_{left}) - H(r_{right})| = n - 1 > 1$$

El árbol deja de ser AVL y no hay garantía de complejidad logarítmica.

## Resultado:

La complejidad $O(\log n)$ del BST solo se cumple cuando $h = O(\log n)$. Un BST sin balanceo no impone esa condición, y un orden de inserción adverso produce $h = \Theta(n)$. Estructuras auto-balanceadas como el Red-Black Tree agregan reglas de color y rotaciones que garantizan $h \le 2\log_2(n+1)$, evitando esta degradación.

# Problema 3 - DFS Iterativo

En este problema se implementó un recorrido DFS de forma iterativa utilizando `std::stack`, sin usar recursión.

El objetivo es encontrar un camino desde la raíz hasta una hoja cuya suma de valores sea igual a un valor `K`.

Para realizar el recorrido se utiliza una pila que guarda los nodos que todavía deben ser procesados. También se mantiene una pila con el camino actual y una variable con la suma acumulada.

Cada nodo se guarda junto con un valor booleano que permite saber si se está entrando al nodo o si se está regresando de él. Esto sirve para simular el comportamiento que normalmente tendría una función recursiva.

Cuando se entra a un nodo, su valor se agrega al camino y a la suma actual. Si el nodo es una hoja, se compara la suma acumulada con `K`. Si son iguales, se encontró el camino buscado.

Cuando se termina de recorrer una rama, se elimina el nodo del camino y su valor se resta de la suma acumulada para poder continuar con las demás ramas.

## ¿Por qué DFS es adecuado?

DFS es adecuado porque permite recorrer una rama completa del árbol desde la raíz hasta una hoja antes de continuar con otra rama.

Como el problema busca un camino completo raíz-hoja, este recorrido permite mantener fácilmente los nodos que forman el camino actual y la suma de sus valores.

Además, al utilizar `std::stack` se puede realizar el recorrido de forma iterativa sin necesidad de usar recursión.

## Complejidad

En el peor caso puede ser necesario visitar todos los nodos del árbol antes de encontrar un camino válido o determinar que no existe.

Por lo tanto, si `n` es la cantidad de nodos:

**Complejidad temporal:**

`O(n)`

La memoria adicional depende principalmente de la cantidad de nodos almacenados en las pilas. En el peor caso puede llegar a ser proporcional al número de nodos:

**Complejidad espacial:**

`O(n)`


# Problema 4 - BFS Iterativo

En este problema se utilizó BFS de forma iterativa mediante `std::queue`, sin utilizar recursión.

Se implementaron tres operaciones:

- Determinar si el árbol es completo.
- Calcular el ancho máximo del árbol.
- Calcular la profundidad mínima.

BFS recorre el árbol nivel por nivel, lo cual resulta conveniente para estas operaciones.

## Árbol completo

Para verificar si el árbol es completo se agregan los hijos izquierdo y derecho de cada nodo a una cola.

Cuando se encuentra por primera vez una posición vacía (`nullptr`), se guarda esta información.

A partir de ese momento, si aparece nuevamente un nodo válido, significa que existe un espacio vacío antes de otro nodo y, por lo tanto, el árbol no es completo.

Si después de encontrar una posición vacía no aparece ningún otro nodo, el árbol cumple con la condición de ser completo.

## Ancho máximo

El ancho de un nivel corresponde a la cantidad de nodos que existen en ese nivel.

Como BFS trabaja por niveles, antes de procesar cada uno se obtiene el tamaño actual de la cola.

Ese tamaño representa la cantidad de nodos del nivel actual. Se compara este valor con el máximo encontrado anteriormente y se conserva el mayor.

De esta forma se obtiene el ancho máximo del árbol.

## Profundidad mínima

La profundidad mínima corresponde a la distancia desde la raíz hasta la hoja más cercana.

En BFS los nodos se procesan en orden creciente de profundidad.

Por esta razón, la primera hoja que se encuentra durante el recorrido necesariamente pertenece al nivel más cercano a la raíz.

En ese momento se puede devolver directamente su profundidad sin necesidad de continuar recorriendo el árbol.

## ¿Por qué BFS es adecuado?

BFS es el enfoque natural para estas operaciones porque procesa los nodos nivel por nivel.

Para verificar si el árbol es completo es importante conocer el orden en que aparecen los nodos y los espacios vacíos dentro de los niveles.

Para calcular el ancho máximo se necesita conocer cuántos nodos existen en cada nivel.

Finalmente, para calcular la profundidad mínima, BFS permite garantizar que la primera hoja encontrada es una de las hojas con menor profundidad.

Por estas razones, BFS permite resolver las tres operaciones directamente utilizando `std::queue`.

## Complejidad

En las tres operaciones cada nodo se procesa como máximo una vez.

Por lo tanto:

**Complejidad temporal:**

`O(n)`

En el peor caso la cola puede almacenar una cantidad de nodos proporcional al tamaño del árbol.

Por lo tanto:

**Complejidad espacial:**

`O(n)`
