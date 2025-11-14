<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  Taller de Programación Orientada a Objetos en C++

</head>
<body>

<h1>Taller de Programación Orientada a Objetos en C++</h1>
<p>
  <strong>Universidad Nacional de Colombia</strong>, sede de La Paz <br>
  <strong>Curso:</strong> Programación Avanzada <br>
  <strong>Autores:</strong> Carlos Alberto Oviedo Machado, Luiyi David Brito Palmezano, Ismael David Perez Cudris
</p>

<h2>Descripción General</h2>
<p>
Este repositorio presenta la solución a seis ejercicios enfocados en los fundamentos y aplicaciones de la Programación Orientada a Objetos en C++. Cada archivo corresponde a un reto diferente, abordando desde operaciones matemáticas hasta la lógica completa de un juego de dominó para varios jugadores humanos.
</p>

<hr>

<h2>Instrucciones de Compilación y Ejecución</h2>
<ol>
  <li>Asegúrese de tener un compilador C++ compatible (<code>g++</code> recomendado).</li>
  <li>Para compilar un ejercicio, ejecute por ejemplo:<br>
      <pre><code>g++ Ejercicio1_T2.cpp -o ejercicio1</code></pre>
  </li>
  <li>Para ejecutar:<br>
      <pre><code>./ejercicio1</code></pre>
  </li>
  <li>Repita para cada archivo, modificando el nombre según corresponda (<code>Ejercicio2_T2.cpp</code>, ..., <code>Ejercicio6_T2cpp.cpp</code>).</li>
</ol>
<blockquote>
  <strong>Nota:</strong> Todos los archivos incluyen menús interactivos y están comentados para facilitar la comprensión y uso.
</blockquote>

<hr>

<h2>Ejercicios y Solución Implementada</h2>

<h3>Ejercicio 1: Vector3D</h3>
<p>
Modela vectores tridimensionales y permite sumarlos, restarlos, calcular su magnitud y normalizarlos. Usa la clase <code>Vector3D</code> con atributos <code>x</code>, <code>y</code>, <code>z</code> y sobrecarga de operadores matemáticos.
</p>
<h4>Ejemplo:</h4>
<pre><code>
Ingrese coordenadas para el vector: 2 3 6
La magnitud es: 7.0
¿Desea normalizar? S/N: S
Vector normalizado: (0.285, 0.428, 0.857)
</code></pre>
<h4>Detalles técnicos:</h4>
<ul>
  <li>Encapsulamiento mediante métodos get/set.</li>
  <li>Manejo de memoria para sumas y operaciones matemáticas.</li>
  <li>Validación para evitar normalización de vectores nulos.</li>
</ul>

<hr>

<h3>Ejercicio 2: Matriz</h3>
<p>
Implementa la clase <code>Matriz</code>, permite trabajar con matrices cuadradas, calcular transpuesta, matriz identidad, multiplicar y llenar matrices aleatoriamente.
</p>
<h4>Ejemplo:</h4>
<pre><code>
1. Ingresar matriz manualmente
2. Generar matriz aleatoria
5. Crear matriz identidad
9. Multiplicar A*B
</code></pre>
<h4>Detalles técnicos:</h4>
<ul>
  <li>Memoria dinámica para almacenamiento y operaciones.</li>
  <li>Sobrecarga de operadores para indexación.</li>
  <li>Menú intuitivo para todas las operaciones.</li>
</ul>

<hr>

<h3>Ejercicio 3: Polinomio</h3>
<p>
Define la clase <code>Polinomio</code> para trabajar con polinomios: sumar, multiplicar, derivar y evaluar.
</p>
<h4>Ejemplo:</h4>
<pre><code>
Ingrese polinomio grado 2:
Coeficientes: 3 0 -1
El polinomio es: 3x^2 - 1
Seleccione operación: Derivar
El polinomio derivado es: 6x
</code></pre>
<h4>Detalles técnicos:</h4>
<ul>
  <li>Arreglo dinámico de coeficientes.</li>
  <li>Métodos para derivación y evaluación.</li>
  <li>Sobrecarga de operadores y salida formateada.</li>
</ul>

<hr>

<h3>Ejercicio 4: Números Complejos</h3>
<p>
Gestiona números complejos tanto en forma binomial como polar, permite sumas, restas, multiplicaciones, divisiones, módulo y conjugado. Clases <code>Complex</code> y <code>Polar</code>.
</p>
<h4>Ejemplo:</h4>
<pre><code>
Ingrese número complejo: 2 + 4i
Ingrese otro complejo: 1 - 3i
Suma: 3 + 1i
Módulo del primero: 4.472
</code></pre>
<h4>Detalles técnicos:</h4>
<ul>
  <li>Operaciones algebraicas con sobrecarga de operadores.</li>
  <li>Conversión entre formas binomial y polar.</li>
  <li>Menú de opciones y validación para operaciones no válidas (división por cero, etc).</li>
</ul>

<hr>

<h3>Ejercicio 5: Ecuaciones Algebraicas (Polinomios por Términos)</h3>
<p>
Modela polinomios como suma de términos, operaciones entre polinomios, y solución de ecuaciones algebraicas.
</p>
<h4>Ejemplo:</h4>
<pre><code>
Polinomio Px: 2x^2 + 3x - 4
Polinomio Qx: x^2 - x
Suma Px + Qx: 3x^2 + 2x - 4
Multiplicación Px * Qx: 2x^4 + x^3 - 2x^2 - 3x^2 - 3x
</code></pre>
<h4>Detalles técnicos:</h4>
<ul>
  <li>Clases <code>CTermino</code> y <code>CPolinomio</code> para términos y polinomios.</li>
  <li>Sumas, multiplicaciones, resolución de ecuaciones y ordenación de términos.</li>
  <li>Generación automática de polinomios para pruebas.</li>
</ul>

<hr>

<h3>Ejercicio 6: Juego de Dominó</h3>
<p>
Desarrolla el juego de dominó clásico para 2 a 4 jugadores humanos. Implementa clases <code>Ficha</code>, <code>Jugador</code> y <code>JuegoDomino</code>, con reglas reales, opción de elegir extremos, registro de victorias y lógica de bloqueo según menor cantidad de pintas.
</p>
<h4>Ejemplo:</h4>
<pre><code>
Mesa: [2|4][4|6]
Fichas: 0:[2|6] 1:[4|1]
Seleccione la ficha: 0
¿Colocar por la cola (2) o la punta (6)? 1
...
Nadie puede jugar. El ganador por menos pintas es Laura con 6 pintas.
</code></pre>
<h4>Detalles técnicos:</h4>
<ul>
  <li>Gestión completa del juego y las rondas.</li>
  <li>Preguntas interactivas y validación de jugada en ambos extremos.</li>
  <li>Marcador por rondas y gestión de bloqueo por pintas.</li>
  <li>Interfaz de consola clara y mensajes descriptivos en cada paso.</li>
</ul>

<hr>

<h2>Créditos y agradecimientos</h2>
<p>
  Trabajo realizado por Carlos Alberto Oviedo Machado, Luiyi David Brito Palmezano e Ismael David Perez Cudris para el curso de Programación Avanzada en la Universidad Nacional de Colombia, sede de La Paz. Todos los ejercicios incluyen comentarios y estructura didáctica según las directrices académicas.
</p>

</body>
</html>
