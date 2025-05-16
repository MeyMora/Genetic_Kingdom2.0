# PROYECTO 2 GENETIC KINGDOM
Instituto Tecnológico de Costa Rica<br>
Escuela de Ingeniería en Computadores<br>
Algoritmos y Estructuras de Datos II (CE 2103)<br>
I Semestre 2025<br>

## Descripción General

Genetic Kingdom es un juego tower defense ambientado en la época medieval donde defiendes tu castillo contra oleadas de enemigos que evolucionan. A medida que eliminas enemigos, estos se adaptan a tu estrategia mediante algoritmos genéticos, volviéndose progresivamente más desafiantes. El juego implementa el algoritmo de pathfinding A* para el movimien

# REQUERIMIENTOS

| ID | Descripción | Puntos |
|-----------|-----------|-----------|
| 001   | El mapa es una cuadrícula de tamaño fijo definida por el grupo de trabajo. El usuario puede colocar torres en cualquiera de los cuadros del mapa asegurando que no bloqueen todos los posibles caminos hacia el puente. El mapa tiene un único punto de ingreso de los enemigos y está en el lado contrario al puente del castillo     | 10    |
| 002    | Cada torre tiene los siguientes atributos: daño, velocidad, alcance, tiempo de regeneración del poder especial, tiempo de recarga de ataque. Las torres atacan a los enemigos cuando están en su alcance. Con cada muerte de enemigo, se considera su categoría y tipo para devolver cierta cantidad de oro al jugador. La cantidad de oro retornado debe ser calculado de forma justa y consistente. El grupo de trabajo define esto    | 10    |
| 003    | Todas las torres tienen 3 upgrades. Cada upgrade aumenta el daño que pueden causar y cada torre tiene ataques especiales que ocurren cada cierto tiempo con una probabilidad definida por los estudiantes. Los upgrades tienen un costo en oro. Cada upgrade es más caro que la anterior. Cada upgrade modifica los atributos en un valor definido por el grupo de trabajo    | 10    |
| 004   | Hay 3 tipos de torres:<br>•Arqueros: bajo costo, alto alcance, poco daño, tiempo de recarga de ataque bajo <br> •Magos: costo medio, alcance medio, daño medio, tiempo de recarga de ataque medio <br> •Artilleros: costo alto, alcance bajo, daño alto, tiempo de recarga de ataque alto <br>     | 5     |
| 005    | El jugador puede ir colocando las torres en cada lugar disponible. Al seleccionar un lugar disponible, puede escoger el tipo de torre que desea crear. Cada torre tiene un costo en oro.    | 10    |
| 006    | Los enemigos aparecen por oleadas. Cada oleada es una generación que evoluciona.<br>Los enemigos pueden ser los siguientes:<br> •Ogros: son el enemigo más básico. Son resistentes a los arqueros y débiles contra la magia y la artillería. Son lentos.<br> •Elfos Oscuros: son resistentes a la magia, pero débiles a los arqueros y a la artillería. Son muy rápidos<br> •Harpías: solo pueden ser atacadas por magia y arqueros. Tienen una velocidad intermedia<br> •Mercenarios: son débiles a la magia, pero resistentes a arqueros y artillería.<br> Cada enemigo tiene atributos como:<br> •Vida<br> •Velocidad<br> •Resistencia a flechas<br> •Resistencia a la magia<br> •Resistencia a la artillería   | 20    |
| 007    | Cada generación selecciona los individuos con el mejor fitness, los cruza e ingresar los nuevos individuos a la población. Pueden ocurrir mutaciones con cierto grado de probabilidad. El estudiante debe definir cada elemento del algoritmo genético y explicarlo adecuadamente en la documentación. Las oleadas son de tamaño variable y se generan con un intervalo parametrizable    | 10    |
| 008    | Los enemigos utilizan Pathfinding A* para encontrar el camino hacia el puente del castillo.    | 20    |
| 009    | El juego muestra un panel con estadísticas como:<br> •Generaciones transcurridas <br> •Enemigos muertos en cada oleada<br> •Fitness de cada individuo de la oleada<br> •Nivel de cada torre <br> •Probabilidad de mutaciones y cantidad de mutaciones ocurridas <br>   | 5     |


### Requisitos Previos

- Compilador compatible con C++17 (se recomienda g++ 11.2.0 o más reciente)
- Bibliotecas SDL2, SDL2_image y SDL2_ttf

## Características

- Tres tipos únicos de torres (Arqueros, Magos, Artillería) con diferentes habilidades
- Cuatro clases de enemigos (Ogros, Elfos Oscuros, Harpías, Mercenarios) con resistencias variadas
- Los enemigos evolucionan después de cada oleada usando algoritmos genéticos
- Pathfinding A* para movimiento inteligente de enemigos
- Sistema de mejora de torres con ataques especiales
- Sistema de retroalimentación de combate en tiempo real
- Gestión dinámica de recursos

## Cómo Jugar

1. **Inicia el juego** ejecutando el programa.
2. **Construye torres** seleccionando un tipo de torre desde el menú superior y haciendo clic en un espacio vacío del mapa.
3. **Defiende tu castillo** de las oleadas de enemigos que intentan cruzar el puente.
4. **Mejora tus torres** seleccionando una torre existente y haciendo clic en el botón de mejora.
5. **Adapta tu estrategia**: los enemigos evolucionarán según las torres que usaste previamente.

