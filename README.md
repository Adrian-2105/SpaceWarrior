![Space Warrior](https://github.com/Adrian-2105/SpaceWarrior/blob/main/assets/logo.png)

Space Warrior es un pequeño videojuego de tipo *shoot 'em up* que presenté como un proyecto para una asignatura de mi 1º año de universidad (por lo que el código presentado es bastante mejorable, sobre todo en cuanto a estructuración del proyecto). Este toma como inspiración los juegos *1943* y *Gemini Wing* (tomando de este último algunos de sus assets).

El juego consiste en controlar una nave que deberá aguantar el mayor tiempo posible a la vez que va destruyendo enemigos, esquivando los disparos y recogiendo diversos *power UP's* (hay que descubrir para qué sirve cada uno ;) ). El objetivo final del juego es obtener las puntuaciones más altas y coronarnos en la tabla de los récords.

# Cómo compilarlo y jugarlo

Por el momento, en este repositorio **únicamente se da soporte para ser ejecutado en Linux, concretamente Ubuntu**. También puede ser compilado y ejecutado en Windows y otras distribuciones de Linux adecuando la instalación a cada uno de ellos.

### Requisitos previos

Antes de poder instalarlo es necesario instalar la librería SDL y algunos paquetes adicionales. Se ofrece un script de para su autoinstalación ejecutando el siguiente comando:

```bash
sudo bash install_dependencies.sh
```

**Nota:** para otras distribuciones de Linux, modificar convenientemente dicho script para poder instalar los mismos paquetes desde el gestor de paquetes correspondiente.

### Compilación y ejecución

Tras haber instalado todos los requisitos previos con el script, la compilación debería de poder realizarse correctamente con el siguiente comando:

```bash
make
```

Por último, se generará el ejecutable y el juego podrá ser iniciado con el siguiente comando:

```bash
./SpaceWarrior
```

# Controles

- **Menús**
  - `UP / DOWN`: desplazamiento
  - `ENTER`: aceptar
  - `ESC`: retroceder
- **Partida**
  - `UP / DOWN / LEFT / RIGHT`: movimiento de la nave
  - `X`: disparar balas (ilimitadas)
  - `C`: disparar bomba (limitadas)
  - `ESC`: menú de pausa
  
# Configuración

- Este juego originalmente está diseñado para ser jugado en una resolución de 600x800. No obstante, este puede ser cambiado modificando la macro `hPantalla` de `main.c` para así especificar la altura de la pantalla. Se puede hacer lo mismo con la anchura, `wPantalla`, aunque no es recomendable. La modificación de estos parámetros puede afectar a la experiencia de juego final, obteniendo tamaños para los que no se diseñó específicamente el juego.

- Cualquier otro parámetro de las macros de `main.c` puede ser cambiado si se quiere "trastear" un poco con el proyecto. Recuerda siempre recompilar tras introducir cualquier nuevo cambio.
