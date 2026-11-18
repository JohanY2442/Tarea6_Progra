# Tarea6_Progra
# Integrantes:
Johan Yadir Huayta Enriquez
Nicolas Lara Alvarez

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
