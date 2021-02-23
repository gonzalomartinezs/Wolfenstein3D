## Módulo 1 - SERVIDOR

### Descripción general

​	El servidor es el módulo encargado de aceptar conexiones entrantes por parte de los clientes, y proveerles mediante el intercambio de mensajes una comunicación a través de la cual de manera centralizada le permiten al cliente en un primer instante crear una partida nueva o unirse a una ya existente para luego entrar en lo que es el juego en sí, proceso que se puede resumir brevemente con el patrón denominado GameLoop el cual se tomó como inspiración para el desarrollo del proyecto y se basa en:

- Recibir instrucciones.
- Realizar el correspondiente update a los elementos del juego.
- Enviar la información actualizada
- Repetir

### Clases

#### ClientHandler
​	Se encarga de la comunicación con el cliente en el tiempo que comprende desde que se conecta al servidor hasta que finaliza el proceso de selección de partida/mapa. La primera interacción se da cuando el cliente le comunica si desea crear una nueva partida o unirse a una ya existente. En base a eso el servidor responde con un mensaje con la información de los mapas que tiene disponibles con su correspondiente cantidad de players máxima, en el otro caso responde con un mensaje con la información correspondientes a las partidas esperando a ser comenzadas por el jugador que las creó. En el caso de que este proceso falle y se lance alguna excepción el ClientHandler finaliza su ejecución y libera los correspondientes recursos (ThClient).

#### ClientManager

Pone el socket aceptador a la espera de conexiones entrantes de manera permanente y los deriva con un ClientHandler que se encarga de la comunicación inicial. A su vez, cada vez que un nuevo cliente se conecta se eliminan y liberan los recursos de los ClientHandler que hayan terminado su ejecución. En el caso de que el servidor se cierre se encarga de finalizar la ejecución de todos los ClientHandler sin importar el estado en el que se encuentren.

![DiagramaDeClaseMultiplesPartidas]https://github.com/gonzalomartinezs/Wolfenstein3D/blob/master/Informe/Images/DiagramaDeClaseMultiplesPartidas.png)

#### DirectoryWalker

Levanta los archivos de la carpeta que se le pase por parámetro y los lee.

#### Game
​	Una de las clases centrales del TP que se encarga de llevar un patrón fundamental, el GameLoop, el cual se encarga de recibir instrucciones de los clientes, actualizar todos los elementos involucrados en el juego y enviar un mensaje a todos los clientes con el estado actual del juego.

![DiagramaSecuenciaGameLoop](https://github.com/gonzalomartinezs/Wolfenstein3D/blob/master/Informe/Images/DiagramaSecuenciaGameLoop.png)

Protocolo utilizado en el mensaje en cuestión:

- Información del HUD.

- Byte “hasLost”, que indica si el jugador se quedó sin vidas.

- Información de la posición del jugador.

- Información de los ítems.

- Información de los sonidos.

- Información de las puertas.

- Posiciones del resto de los jugadores.

- Posiciones de los Rockets.



​	Si bien los primeros 3 campos tienen un tamaño constante, el resto puede variar con cada mensaje.

(Ver implementación en Game.cpp)

![DiagramaDeClaseGame](https://github.com/gonzalomartinezs/Wolfenstein3D/blob/master/Informe/Images/DiagramaDeClaseGame.png)

​	Vale destacar que cada mensaje contiene toda la información acerca del estado actual del juego, en ningún momento el servidor comunica “cambios” de solo algunos elementos del juego. Si bien esto implica un problema de escalabilidad no se vio la necesidad de implementarlo de esa manera ya que el juego por la dinámica que tiene no está pensado para ser jugado en mapas de tamaño descomunal. 

​	Además, hacerlo de tal manera hizo que agregar el feature del modo espectador sea sumamente sencillo.

#### GameManager

Es la clase raíz del server, cuya funcionalidad se limita a comenzar la ejecución del ClientManager para luego concluir la misma junto con la de todas las partidas que se encuentran en ejecución cuando el server recibe la orden de cerrarse.

#### GamesHandler

​	La clase en cuestión actúa como una especie de Wrapper thread-safe del vector de partidas (Lobby’s). Como se puede observar la interfaz que provee es prácticamente idéntica.

#### Key

​	Esta clase representa el objeto llave que el jugador puede utilizar para abrir determinadas puertas. Es la encargada de interactuar con las mismas ya sea que necesiten llave o no.

#### LeaderBoard

​	Utilizando el estado de los players una vez que la ejecución se sale del GameLoop (Ya sea porque se acabó el tiempo, queda un solo jugador vivo, o se está efectuando el cierre del servidor) se encarga de crear el correspondiente mensaje con la información de los jugadores con más bajas, puntos, y balas disparadas y enviarlo a todos los clientes.

#### Lobby

​	Actúa en torno a la clase Game. Se encarga de esperar la instrucción para comenzar la partida por parte del cliente que la creó, mientras tanto recibe clientes que desean unirse a la partida en cuestión (Se van agregando a un vector de ThClients) y que quedan a la espera de que la partida comience. Por último, una vez finalizado el juego en sí, se encarga de cerrar la comunicación con cada uno de los clientes y liberar los recursos correspondientes. 

#### MapsReader

​	Es la clase encargada de levantar los mapas de la carpeta Maps. Utiliza DirectoryWalker para obtener los archivos de la carpeta y quedarse sólo con los que cumplan el formato .yaml/.yml. De esta forma sólo se necesita agregar un nuevo archivo a la carpeta y el servidor va a saber identificarlo como un posible mapa.

#### Player

​	Es una clase central ya que almacena todos los atributos correspondientes al estado del jugador. La clase tiene una interfaz extensa que maneja el comportamiento del mismo.

#### PlayerActions

​	Es la clase a la que Player delega sus métodos. Se encarga de la interacción con los ítems y de delegar el comportamiento de las armas a la clase Weapons. Contiene además el contador de muertes, balas usadas y puntos hechos a lo largo de la partida.

#### RandomPosition

​	Se utiliza para calcular posiciones aleatorias alrededor del jugador al momento de morir y dejar sus ítems en el piso. Tiene 2 get (x e y) que van cambiando la dirección cada vez que se llama.

#### Sound

​	Se crea una instancia de esta clase cada vez que se emite un sonido en algún punto del mapa el cual corresponde que sea escuchado por el resto de los jugadores. El mismo se construye con una coordenada (x, y) y un SoundID. A la hora de mandar los sonidos simplemente se calcula la distancia del jugador a este.


#### TheClient
​	Esta clase es el medio de comunicación que tiene el servidor con cada cliente. Por cada cliente que se conecta al servidor se crea una instancia de la misma la cual a su vez lanza 2 threads que se encargan específicamente de iterar las funciones Receive y Send del socket (Peer). En el caso del Receive está constantemente recibiendo y acolando las instrucciones en una cola protegida, por otro lado el Send itera constantemente una cola bloqueante enviando todos los bytes que ingresen en ella.

![DiagramaDeClaseThClient](https://github.com/gonzalomartinezs/Wolfenstein3D/blob/master/Informe/Images/DiagramaDeClasesThClient.png)

#### Weapon

​	Esta clase es la clase base de la cual heredan las clases Knife, Pistol, MachineGun, ChainGun, RocketLauncher.

​	Las clases MachineGun y ChainGun al ser armas automáticas utilizan Timer’s para controlar la frecuencia de los disparos. En cambio las clases Pistol y Knife actúan como armas semiautomáticas.

​	La lógica de disparo se basa en ir recorriendo un vector de Player’s verificando si existe una pared de por medio, en el caso de que no haya se calcula una función de probabilidad que decae linealmente con el ángulo y la distancia. En el caso de acertar el disparo se corta la iteración sobre los clientes y se aplica el daño correspondiente al jugador impactado.

![DiagramaDeClaseWeapon-1](https://github.com/gonzalomartinezs/Wolfenstein3D/blob/master/Informe/Images/DiagramaDeClaseWeapon-1.png)
![DiagramaDeClaseWeapon-2](https://github.com/gonzalomartinezs/Wolfenstein3D/blob/master/Informe/Images/DiagramaDeClaseWeapon-2.png)



El RocketLauncher es el arma que más difiere al resto. Esto es debido a que la lógica del disparo es completamente diferente. Cada vez que dispara se crea un objeto Rocket, el cual comienza a ser actualizado por el GameLoop y enviada la correspondiente información a los clientes.

##### Descripción de archivos y protocolos
Los archivos utilizados están en formato yaml. Del lado del servidor se utilizan 2 tipos, uno de configuración (config.yaml) y otro para mapas.
###### config.yaml
Contiene valores ajustables del juego para hacerlo más balanceado según el usuario. Los valores son: 
	port (puerto) por el que escuchará el socket del servidor.
	tick_rate es la cantidad de veces que se actualiza el servidor por segundo.
	game_duration es la duración de las partidas en caso que haya más de un jugador vivo.
	weapons_general tiene los valores usados por cada arma para facilitar ajustes.
Dentro de weapons_general cada arma tiene sus propios valores:
	time_between_shots es el tiempo entre cada disparo del arma.
	time_between_bursts es el tiempo entre cada ráfaga de disparo.
	bullets_per_burst cantidad de balas que se usan por ráfaga de disparo.
	move_speed es la velocidad a la que el rocket (cohete) se mueve.
	size es el tamaño del cohete, se usa para calcular cuándo hay colisión.
	max_damage es el daño máximo que puede provocar el rocket.
	max_damage_distance representa el alcance del cohete una vez que explota, medido en 	distancia euclidiana.
	max_health es la vida máxima del jugador.
A continuación se detallan los atributos de player (jugador):
	move_speed es la velocidad a la que se mueve el jugador.
	rot_speed es la velocidad a la que gira hacia los lados el jugador.
	size es el tamaño del jugador, se usa para calcular las colisiones.
	initial_health es la vida inicial.
	initial_score es la puntuación inicial.
	total_lives es la cantidad total de vidas de cada jugador.
	key contiene el radio del key item.
En el apartado weapons hay:
	initial_weapon puede valer 0 si se empieza con knife o 1 si se empieza con pistol.
	bullet contiene la cantidad inicial de balas (initial_bullets), la cantidad máxima 	(max_bullets) y el radio de bullet item.
Los atributos de knife representan el tiempo que pasa entre un ataque y otro (time_between_stabs) y el rango (range) desde el cual hace daño.
	bot_path indica la ruta hacia un archivo Lua que contiene instrucciones de la inteligencia artificial del bot.
	ítems tiene un listado de todos los items del juego con sus respectivos valores. En todos los casos radius representa el tamaño del ítem usado para saber si el jugador lo agarró o no.
	cross, crown, cup y chest son las cruces, coronas, copas y tesoros respectivamente. Su value representa los puntos que otorga al jugador.
	food, medical_kit, blood representan la comida, kit médicos y la sangre respectivamente. Su value representa la vida que cura al jugador. Tienen una referencia a la vida máxima para que el jugador no se pueda curar más allá de su vida máxima.
	bullet tiene como value la cantidad de balas que tiene el jugador al momento de pasar por el ítem. A su vez contiene la cantidad máxima de balas para no cargar más allá del máximo.

###### map.yaml
En el caso del mapa estos contienen:
	map_name indica el nombre del mapa
	max_players es la cantidad máxima de jugadores en ese mapa.
	lenght y width indican el largo y ancho del mapa respectivamente.
	map representa el mapa en sí. Los valores que puede tener entre sus elementos son:
		0 representa un espacio vacío.
		1 representa una pared naranja.
		2 representa un pared grid con musgo.
		10 representa una puerta con llave.
		11 representa un pasadizo.
		12 representa una puerta automática.
	player representa cada uno de los jugadores, dependiendo de la cantidad máxima de jugadores que puedan haber en la partida. Entre sus atributos contiene:
	pos_x, pos_y que representan la posición inicial en el mapa.
	dir_x, dir_y que representan la dirección a la cual el jugador estará apuntando al inicio de la partida.
En cuanto a los items pueden estar todos como no. Cada estará representado por su nombre (como en config.yaml) y dentro tendrá:
	cant_item representa la cantidad de ese mismo tipo de item en el mapa.
	item_i representa el item i desde el 0 hasta cant_item conteniendo dentro la pos_x y pos_y respecto del mapa.



## Módulo 2 - CLIENTE

### Descripción General

​	El cliente es el módulo encargado de brindarle al usuario una interfaz gráfica lo suficientemente rica como para permitirle al usuario jugar y que, simultáneamente, se comunique con el servidor enviando las acciones del jugador y recibiendo la respuesta adecuada a cada una de ellas, así como también información sobre su entorno.

​	En Wolfenstein3D, el cliente comienza la ejecución con una pantalla de LogIn que invita al usuario a conectarse al servidor deseado. Tras esto, se encontrará con la posibilidad de unirse a un juego existente o crear uno donde, siguiendo los pasos indicados, podrá unirse a una partida. 

​	Una vez realizado esto, el cliente le mostrará al usuario una interfaz en la que puede observar la imagen del juego en sí, acompañada por un HUD (Head-Up Display) el cual proporciona toda la información sobre cantidad de vidas, balas, arma equipada, entre otras.

​	Asimismo, para que esto ocurra el cliente se encuentra constantemente comunicándose con el servidor para enviarle las instrucciones indicadas por el usuario y, de igual manera, recibir información sobre el estado del juego y los demás jugadores para, posteriormente, procesarla y renderizarla.

### Clases

#### Client

​	Es una de las clases troncales de este módulo, la misma contiene el socket mediante el cual se realiza la comunicación con el servidor, siendo la encargada de enviar las instrucciones del jugador y parsear los mensajes recibidos del server (que luego serán procesados y encolados en una cola de ```UI_Info```). 

​	Posee 2 métodos interesantes de mencionar: ```sendInstruction()``` y ```receiveInformation()```, los cuales dentro del método ```gameLoop()``` de ```clientwindow``` se cargan en 2 hilos distintos que corren en paralelo. Por un lado ```sendInstruction()``` realiza un pop de las instrucciones de una cola bloqueante, la cual contiene las instrucciones indicadas por el usuario (cargadas por el ```EventHandler```). Por otra parte, ```receiveInformation()``` recibe el mensaje del servidor de acuerdo al protocolo establecido, cargando los valores parseados en la cola mencionada al comienzo del apartado.


#### ClientData

​	Contiene instancias de todos los objetos necesarios para la correcta ejecución del cliente.

#### clientwindow
​	Maneja la ventana del login, 
#### DynamicTexture

​	Es un arreglo de instancias de la clase ```Texture``` (```TextureSet```) creado con el objetivo de dar la sensación de movimiento. El mismo contiene un timer y un período de repetición de la animación, en base a los cuales se puede saber qué textura renderizar.

#### EventHandler

​	Clase cuya función consiste en procesar las teclas presionadas por el usuario y colocarlas en una cola de instrucciones.

#### FontTexture

​	Clase encargada de generar y renderirzar una textura de SDL a partir de texto.

#### GameInterface

​	Se trata de otra clase fundamental del juego cuya función yace en desencolar instancias de ```UI_Info``` y delegar la renderización y musicalización del juego a partir de las mismas.

#### InstructionLooper

​	Ejecuta el loop encargado de levantar las teclas presionadas por el usuario hasta que se cierra la ventana o se termina la partida.

#### LeaderboardRenderer

​	Clase cuyo objetivo es renderizar el leaderboard del juego una vez acabada la partida. 

#### Music

​	Abstracción basada en SDL realizada para reproducir la música de fondo del juego.

#### PlayerView

​	Clase contenedora de las coordenadas de la dirección en la que se encuentra mirando el jugador.

#### Raycaster

​	Esta clase contiene toda la matemática utilizada para calcular la distancia del jugador a los muros y puertas más cercanos. Es la base del motor gráfico del cliente.

#### RaycastingRenderer

​	Al recibir las distancias obtenidas de la clase anterior, hace las debidas modificaciones a las texturas de paredes y puertas para graficarlas dando una sensación de perspectiva.

#### SDLException

​	Excepción creada con el fin de ser lanzada cada vez que se produzca un error a la hora de crear instancias de objetos que dependan de SDL para ser renderizados o reproducidos.

#### SoundEffect

​	Abstracción basada en SDL con el objeto de reproducir los efectos de sonido del juego, tales como disparos, pasos, recolección de ítems, entre otros.
#### SoundHandler

​	Clase encargada de administrar la reproducción de sonido y música. 

#### SoundsContainer

​	Clase contenedora de todos los sonidos y canciones utilizadas en el juego. Su razón de ser consiste en tener una única instancia de cada ```Music``` o ```SoundEffect``` de manera tal que pueda ser accedida por otras clases a lo largo de todo el juego.

#### SpriteRenderer

​	Esta clase se encarga de renderizar los sprites del juego (figuras de jugadores, ítems, misiles del rocket launcher).

#### SpriteSelector

​	Clase cuyo fin es seleccionar el sprite a renderizar en función de la orientación del mismo y, en caso de ser dinámico, escoge la textura de la animación correspondiente.

#### Texture

​	Clase encargada de generar y renderizar una textura de SDL a partir de una imagen .bmp o .png.

#### TexturesContainer

​	Clase contenedora de todas las texturas utilizadas en el juego. Su razón de ser consiste en tener una única instancia de cada ```Texture``` de manera tal que pueda ser accedida por otras clases a lo largo de todo el juego. De esta manera se evita alocar memoria constantemente, mejorando la performance.

#### TextureSet

​	Clase compuesta por un vector de ```Texture```.

#### UI_Handler

​	Es la clase encargada de administrar la visualización de la interfaz del usuario, incluyendo la imagen de fondo, raycasting, leaderboard y carga del HUD.

#### UI_Info

​	Clase contenedora de toda la información pertinente para la interfaz del usuario, incluyendo sonidos, posición de otros jugadores, ítems, estados de las puertas, entre otros.

#### Window
​	Esta clase se encarga de crear un ventana de SDL y el renderer asociado a esta, así como también inicializar las bibliotecas de SDL, SDL_image, SDL_ttf y SDL_mixer.

### Diagramas UML

![Client](https://github.com/gonzalomartinezs/Wolfenstein3D/blob/master/Informe/Images/Client.png)

![GameInterfaceVSHandlers](https://github.com/gonzalomartinezs/Wolfenstein3D/blob/master/Informe/Images/GameInterfaceVSHandlers.png)

![Raycasting](https://github.com/gonzalomartinezs/Wolfenstein3D/blob/master/Informe/Images/Raycasting.png)

![Sound](https://github.com/gonzalomartinezs/Wolfenstein3D/blob/master/Informe/Images/Sound.png)

### Descripción de archivos y protocolos

El protocolo utilizado fue mencionado previamente en el módulo del Servidor.



## Módulo 3  Editor
### Descripción General

​	El Editor es el módulo encargado de brindarle al usuario una interfaz amigable donde pueda crear/editar sus mapas en el juego, garantizando el correcto formato de los archivos para que luego el cliente las pueda leer. 

### Clases
#### Coordinate

​	Representa una coordenada en el plano.


#### IconsContainer

​	Clase contenedora de QPixmaps, es usada para tener una única referencia de cada imagen y aprovechar la memoria. Contiene un Map donde los valores son QPixmaps y las key asociadas son los respectivos ID. (Representados en el enum Editor_icon).

#### InvalidFileException

​	Arrojada cuando no se puede parsear el archivo Yaml correctamente. En el flujo del tp esta es cacheada por MapHandler quien genera un Pop Up mediante una señal a la clase MessageBox.

#### ItemList

​	Clase itemList, es la encargada de contener los ítems que se pueden colocar en el mapa, se puede visualizar a la izquierda de la ventana principal. Tiene implementada el StartDrag, es la fuente de los drags que llegan al ManHandler.

#### MainWindow

​	Ventana principal, es la encargada de iniciar todos los widgets, contiene las referencias necesarias para cargar los widgets hijos desde el archivo “.ui”, también dentro de esta clase se hace el connect entre los correspondientes signals y slots. 
Adicionalmente es la encargada de generar la Menubar superior y linkear los botones con las correspondientes acciones.

#### Map

​	Clase mapa, usada para guardar los elementos que fueron colocados mediante el Drag & Drop, cuando el mapHandler recibe un elemento calcula sus coordenadas y las almacena en la clase Map (Ver diagrama de secuencia). Sirve como contenedor de los elementos que deben ser imprimidos por pantalla.




#### MapElement

​	Representa un elemento del mapa contiene un Id y una coordenada que son lo que le da identidad. El ID es usado tanto para imprimir por pantalla y observar de qué icono se trata como para luego exportar en el YAML.

#### MapHandler

​	Contiene un Map
​	Es la clase encargada de recibir los drops provenientes de la lista, calcula sus coordenadas y si el lugar está disponible lo guarda en el Map. También tiene a cargo mostrar por pantalla el estado actual del mapa.

#### MapParser

​	Clase encargada de leer / exportar los archivos en formato Yaml.
Es instanciada al momento que se requiere hacer alguna de estas operaciones.

#### MessageBox

​	Clase encargada de generar los Pop Ups para el usuario. Contiene slots que dependiendo de la necesidad muestran distintos mensajes.

#### MessageBox

​	Clase encargada de generar los Pop Ups para el usuario. Contiene slots que dependiendo de la necesidad muestran distintos mensajes.

#### TrashBin

​	Clase que solo recibe Drops, es usada para eliminar elementos de la pantalla principal. Al recibir un elemento realiza una pequeña animación.


#### Diagramas UML

![ClasesEdtir](/Images/DiagramaDeClasesEditor.png)
![seqDrop](/Images/SeqDropEvent.png)



# Programas intermedios y de prueba

A fines de depurar el raycasting en sus comienzos, se utilizó un minimapa auxiliar el cual mostraba la vista desde arriba del mismo y los impactos de los rayos emitidos por el jugador durante este proceso. De esta manera, se pudieron corregir los errores de ese entonces y se guardó parte del script utilizado con la esperanza de volver a utilizarlo en un futuro. Si bien finalmente esto no sucedió así, a continuación se muestra parte de dicho código.

```c
void drawMap(SDL_Renderer* renderer, Map map, int window_width, int window_height){
    int cell_size_x = window_width/map.getWidth();
    int cell_size_y = window_height/map.getHeight();
    for(int i=0; i<map.getWidth(); i++){
        for(int j=0; j<map.getHeight(); j++){
            if (map.get(i, j) != WALKABLE){
                SDL_Rect fillRect = {cell_size_x*i, cell_size_y*j, cell_size_x, cell_size_y};
                SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
                SDL_RenderFillRect( renderer, &fillRect );
            }
        }
    }
}
```