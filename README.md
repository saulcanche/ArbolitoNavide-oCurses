# Árbol Binario con Gráfica en ncurses

Este programa implementa un árbol binario de búsqueda que almacena valores enteros y genera una representación gráfica compacta en la consola utilizando la biblioteca `ncurses`. El objetivo es asociar a cada nodo un par de coordenadas `(x, y)` que permiten graficar el árbol de forma clara y compacta.
La implementación de la estructura árbol fue la vista en clase y esta definida en el archivo arbolB.h

## Características

- Cada nodo del árbol en el mismo nivel tiene la misma coordenada `y`.
- Cada nodo está centrado horizontalmente (`x`) entre sus nodos hijos, si los tiene.
- La representación gráfica se despliega en consola, similar a un dendograma, usando líneas horizontales y verticales.

### Ejemplo de Gráfica

La representación gráfica no requiere líneas diagonales. Un ejemplo básico podría verse así:
    10
   ┌─┴─┐
  5     15
 ┌┴┐   ┌┴┐
3   7  13 20
## Requisitos Previos

Asegúrate de tener instalado:

- Un compilador de C++ compatible con el estándar C++11 o superior (por ejemplo, `g++`).
- La biblioteca `ncurses` para manejar la interfaz gráfica en la terminal.
- `make` para compilar y ejecutar el programa fácilmente.

## Instrucciones de Instalación y Ejecución

1. Clonar el repositorio o descargar los archivos:  
   git clone <https://github.com/saulcanche/ArbolitoNavideñoCurses>  

2. Instalar la biblioteca `ncurses` si no está disponible en tu sistema:  
   En Ubuntu/Debian: `sudo apt-get install libncurses5-dev libncursesw5-dev`  
   En otros sistemas, consulta la documentación de tu paquete gestor.

3. Compilar el programa usando make:  
   make

4. Ejecutar el programa:  
   ./hola

5. Limpiar archivos generados (opcional):  
   make clean

## Funcionalidades del Programa

- Generar un árbol binario de búsqueda con números aleatorios.
- Calcular y asignar coordenadas `(x, y)` a cada nodo.
- Representar gráficamente el árbol en consola utilizando `ncurses`.


