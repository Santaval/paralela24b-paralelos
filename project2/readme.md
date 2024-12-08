# Simulación de Partículas Gravitacionales

## Descripción del Proyecto

Este proyecto simula un sistema de partículas en el espacio, donde cada puna de ellas artícula interactúan gravitacionalmente entre sí. El objetivo es modelar cómo las se mueven a través del tiempo bajo la influencia de la gravedad, detectando colisiones entre ellas y fusionándolas cuando entran en contacto. La simulación utiliza la ley de gravitación universal de Newton para calcular las fuerzas de atracción entre las partículas y actualizar sus posiciones y velocidades en un rango de tiempo llamado **delta_time** hasta que se llegue a un tiempo final **t_final**.
### Problema a Resolver

En el mundo real, los sistemas gravitacionales, como los planetas que orbitan el sol, están sujetos a interacciones gravitacionales mutuas. Estos sistemas pueden ser muy complejos cuando hay muchas partículas involucradas, ya que cada partícula siente la fuerza de todas las demás. Además, las partículas pueden chocar y fusionarse entre sí, lo que introduce un nivel adicional de complejidad en el modelo.

El problema aquí resuelto es crear una simulación que modele estos comportamientos básicos:
1. Las partículas se mueven bajo la influencia de la gravedad.
2. Las partículas pueden colisionar y fusionarse cuando se encuentran lo suficientemente cerca.
3. El sistema debe actualizarse en pequeños pasos de tiempo, simulando la evolución del sistema a lo largo del tiempo.

---

## Estructura del Sistema

El sistema está compuesto por dos clases principales: **`Universe`** y **`Particle`**.

### 1. Clase `Universe`

La clase `Universe` representa el sistema general de partículas y maneja la simulación en su totalidad. Las funciones clave de esta clase incluyen:

- **`addParticle(Particle* particle)`**: Añade una nueva partícula al sistema.
- **`next()`**: Avanza la simulación un paso de tiempo, actualizando las posiciones, velocidades y detectando colisiones.
- **`detectCollisions()`**: Detecta colisiones entre todas las partículas del sistema.
- **`handleCollision()`**: Maneja las colisiones entre partículas, fusionándolas si es necesario.
- **`updateVelocities()`**: Calcula y actualiza las velocidades de las partículas en función de las fuerzas gravitacionales.
- **`updatePositions()`**: Calcula y actualiza las posiciones de las partículas en función de sus velocidades.
- **`chargeFromFile()`**: Carga las partículas desde un archivo, con sus propiedades (masa, radio, posición, velocidad).
- **`clean()`**: Limpia el sistema eliminando las partículas absorbidas.

### 2. Clase `Particle`

La clase `Particle` representa una partícula en el sistema. Cada partícula tiene propiedades como masa, radio, posición y velocidad. Las funciones clave de esta clase incluyen:

- **`calcAttractionForce(const Particle* attractor)`**: Calcula la fuerza gravitacional entre esta partícula y otra, usando la ley de gravitación universal de Newton.
- **`setAcceleration(Vector acceleration)`**: Establece la aceleración de la partícula.
- **`setVelocity(magnitude_t delta_time)`**: Actualiza la velocidad de la partícula en función de su aceleración y el paso de tiempo.
- **`setPosition(magnitude_t delta_time)`**: Actualiza la posición de la partícula en función de su velocidad y el paso de tiempo.
- **`absorb(Particle& other)`**: Fusiona esta partícula con otra. La partícula absorbente adquiere la masa, el radio y la velocidad de la partícula absorbida.

---

## Modelado Físico

### 1. Gravitación Universal

El modelo utiliza la ley de gravitación de Newton para calcular la fuerza de atracción entre dos partículas:

$$F = \frac{G \cdot m_1 \cdot m_2}{r^2}$$

Donde:
- \( F \) es la fuerza de atracción entre las dos partículas.
- \\( G \\) es la constante gravitacional.
- \\( m_1 \\) y \\( m_2 \\) son las masas de las partículas.
- \\( r \\) es la distancia entre las partículas.

La fuerza de atracción se calcula en cada paso de tiempo y se usa para actualizar las velocidades y posiciones de las partículas.

### 2. Colisiones y Absorción de Partículas

Cuando dos partículas se acercan lo suficientemente (su distancia es menor que la suma de sus radios), se considera que han colisionado. Dependiendo de sus masas y radios, una de las partículas absorbe a la otra:

- Si una partícula es absorbida, se elimina del sistema y sus propiedades (masa, radio, velocidad) se incorporan a la partícula absorbente.
- La nueva partícula resultante de la absorción tiene un radio que es la raíz cúbica de la suma de los volúmenes de las dos partículas originales. Su masa es la suma de las masas de las partículas absorbidas, y su velocidad se calcula utilizando la ley de conservación del momento lineal.

---

## Descripción Detallada del Flujo de la Simulación

### Paso 1: Inicialización
Las partículas se pueden cargar desde un archivo que contiene su masa, radio, posición y velocidad inicial. Si no se proporciona un archivo, el sistema se puede inicializar sin partículas.

### Paso 2: Simulación del Universo

En cada iteración del ciclo de simulación:
1. Se calculan las fuerzas gravitacionales entre todas las partículas del sistema.
2. Las partículas actualizan sus velocidades en función de las fuerzas que experimentan.
3. Se actualizan las posiciones de las partículas en función de sus nuevas velocidades.
4. Se detectan colisiones entre partículas. Si dos partículas colisionan, se fusionan según las reglas de absorción descritas.

### Paso 3: Limpieza
Cuando una partícula es absorbida, se elimina de la memoria para evitar fugas. Al final de cada simulación, el sistema se limpia, eliminando todas las partículas absorbidas.

---

## Análisis de Complejidad

La detección de colisiones en este modelo es de **O(n²)**, ya que cada partícula debe verificar si colisiona con todas las demás. Este enfoque es adecuado para un número pequeño o moderado de partículas, pero puede volverse ineficiente a medida que el número de partículas crece.

### Posibles Mejoras:
- Implementar algoritmos de detección de colisiones más eficientes, como el **algoritmo de Barnes-Hut** o el uso de **espacios de partición (quadtrees, octrees)**.
- Utilizar métodos de integración más precisos y eficientes, como el **método de Runge-Kutta**.

---

## Requisitos

- **Lenguaje**: C++
- **Dependencias**: Ninguna (uso de bibliotecas estándar de C++).
- **Compilador**: C++11 o superior.

---

## Instrucciones de Uso

### Compilación y Ejecución

