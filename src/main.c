#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "Animacion.h"
#include "AnimacionMultiple.h"
#include "Bala.h"
#include "Colision.h"
#include "Enemigo.h"
#include "Flota.h"
#include "Galaxia.h"
#include "SDL_Wrapper.h"
#include "Personaje.h"
#include "Potenciador.h"
#include "Puntuacion.h"
#include "Rafaga.h"

// SDL_Wrapper
#define wSDL_Wrapper 600
#define hSDL_Wrapper 800
// Men�
#define wLogo 390
#define hLogo 112
#define wMenu 174
#define hMenu 142
// Personaje
#define wPersonaje 50
#define hPersonaje (4*wPersonaje)/5
#define vPersonaje 6
#define num_sprite_nave 5
// Enemigos
#define wEnemigo wPersonaje
#define hEnemigo hPersonaje
#define vxEnemigo 4
#define vyEnemigo 3
#define num_sprite_enemigo 5
#define vGiro_min 2
#define vGiro_max 5
#define frec_enemigos 100
// Disparo
#define wDisparo 18
#define hDisparo 14
#define vDisparo 50
#define wBala 3
#define hBala 14
#define bombasMax 9
#define mul_bomba 16
#define wBomba 30
#define hBomba 30
#define wDisparo_enem 15
#define hDisparo_enem wDisparo_enem
#define vDisparo_enem 8
#define frec_disparo 5
#define frec_disparo_enemigo 25
// Explosi�n
#define estadosExplosion 9
#define delayExplosion 6
// Aceleraci�n
#define acel_time 300
// Onda destructora
#define enem_onda 3
// Ayudantes
#define sepAyudantes wPersonaje/3
#define wAyudantes wPersonaje/3
#define hAyudantes hPersonaje/3
#define ayudantes_time 300
// Reaparici�n
#define reaparicion_time 20
#define inmunidad_time 150
#define frec_parpadeo 5
// Galaxia
#define vGalaxia 2
#define max_powers 4
#define tipos_powers 10
#define tam_iconos 24
#define vFondo 1
#define frec_powers 150


/**
    \mainpage Space Warrior
    Space Warrior es un peque�o shotem'up de naves al estilo arcade en el que nuestro objetivo ser� aguantar el mayor tiempo posible para lograr la puntuaci�n m�s alta.<br/>
    Nos enfrentaremos a numerosos enemigos a la par que iremos recogiendo diversos potenciadores que nos dar�n ciertas ventajas o puntuaci�n.<br/>

    Los controles son simples. Con las flechas de direcci�n moveremos a nuestra nave, con la tecla X haremos que esta dispare y con la tecla C haremos que dispare bombas (si disponemos de ellas)<br/>.
    Para movernos por los men�s utilizaremos las flechas de direcci�n y Enter.<br/>

    En el juego encontraremos diferentes tipos de potenciadores (o m�s conocidos como Power UP's) que, aunque no se explican dentro del juego (al igual que hac�an los juegos de las recreativas), se expondr�n a continuaci�n:
    - Puntos: habr� tres potenciadores diferentes que dar�n cada uno 5, 10 o 25 puntos. Los dos primeros son distinguibles por llevar el n�mero, pero el tercero no lo lleva: es el orbe de color azul.
    - Vidas extra: a�ade una vida extra a nuestro jugador. Es el coraz�n con alas, bastante distinguible.
    - Bombas: a�ade una bomba al ca��n de la nave, la cual funciona igual que una bala normal solo que esta al colisionar producir� una gran explosi�n destruyendo a los enemigos que se vean atrapados en ella. Es el orbe de color rojo.
    - Escudo: a�ade al jugador un escudo autom�ticamente que le proteger� de cualquier golpe hasta que este sea destruido. Es el orbe azul que tiene la letra "S" (de "Shield").
    - Rayo destructor: destruye autom�ticamente a los 3 enemigos m�s cercanos al jugador. Es el orbe de color rosa que tiene una triple flecha.
    - Ayudantes: dos naves aliadas aparecer�n durante un breve periodo de tiempo que disparar�n al mismo tiempo que nosotros, d�ndonos as� un mayor rango de disparo. Es el orbe verde con un s�mbolo "+".
    - Aceler�n: aumenta la velocidad de la nave durante un breve periodo de tiempo. Es el orbe de color amarillo.
*/

int main (int argc, char **argv)
{
    /* Preparativos iniciales */
    SDL_Wrapper_Crea("Space Warrior", wSDL_Wrapper,hSDL_Wrapper);
    srand(time(NULL));

    typedef struct
    {
        Imagen img;
        int w,h;
    } Imagen_Powers;

    Imagen numeros[11];
    numeros[0] = SDL_Wrapper_ImagenLee("assets/hud/num0.bmp", 1);
    numeros[1] = SDL_Wrapper_ImagenLee("assets/hud/num1.bmp", 1);
    numeros[2] = SDL_Wrapper_ImagenLee("assets/hud/num2.bmp", 1);
    numeros[3] = SDL_Wrapper_ImagenLee("assets/hud/num3.bmp", 1);
    numeros[4] = SDL_Wrapper_ImagenLee("assets/hud/num4.bmp", 1);
    numeros[5] = SDL_Wrapper_ImagenLee("assets/hud/num5.bmp", 1);
    numeros[6] = SDL_Wrapper_ImagenLee("assets/hud/num6.bmp", 1);
    numeros[7] = SDL_Wrapper_ImagenLee("assets/hud/num7.bmp", 1);
    numeros[8] = SDL_Wrapper_ImagenLee("assets/hud/num8.bmp", 1);
    numeros[9] = SDL_Wrapper_ImagenLee("assets/hud/num9.bmp", 1);
    numeros[10] = SDL_Wrapper_ImagenLee("assets/hud/x.bmp", 1);

    /** MEN� PRINCIPAL **/

    while (SDL_Wrapper_Activa())
    {
        Imagen fondo_menu = SDL_Wrapper_ImagenLee("assets/backgrounds/menuprinc.bmp", 0);
        Imagen logo = SDL_Wrapper_ImagenLee("assets/menu/logo.bmp", 1);
        Imagen menu = SDL_Wrapper_ImagenLee("assets/menu/menu.bmp", 1);
        Imagen controles = SDL_Wrapper_ImagenLee("assets/menu/controles.bmp", 0);
        Imagen record = SDL_Wrapper_ImagenLee("assets/menu/records.bmp", 0);
        Imagen creditos = SDL_Wrapper_ImagenLee("assets/menu/creditos.bmp", 0);
        Imagen flecha = SDL_Wrapper_ImagenLee("assets/menu/flecha.bmp", 1);
        int fin = 0;
        int cont = 0;
        int flag = 1;
        int v_aux = -wPersonaje;
        int y = hSDL_Wrapper/2;

        /* Intro */
        Imagen nave_intro = SDL_Wrapper_ImagenLee("assets/menu/nave_intro.bmp", 1);
        SDL_Wrapper_ColorTrazo(255, 255, 255, 255);

        // Nave cruzando
        while (SDL_Wrapper_Activa() && (v_aux < wSDL_Wrapper))
        {
            SDL_Wrapper_DibujaRellenoFondo(0, 0, 0, 255);
            SDL_Wrapper_DibujaLinea(0, hSDL_Wrapper/2, v_aux, hSDL_Wrapper/2);
            SDL_Wrapper_DibujaImagen(nave_intro, v_aux,hSDL_Wrapper/2-hPersonaje/6, wPersonaje, hPersonaje/3);
            v_aux += vPersonaje*2;
            SDL_Wrapper_Actualiza();
            SDL_Wrapper_Espera(10);
        }
        v_aux = hSDL_Wrapper/2;
        SDL_Wrapper_ColorTrazo(0, 0, 0, 255);
        SDL_Wrapper_ColorRelleno(0, 0, 0, 255);

        // Barrido de pantalla
        while (SDL_Wrapper_Activa() && (v_aux > 0))
        {
            SDL_Wrapper_DibujaImagen(fondo_menu, cont, 0, wSDL_Wrapper, hSDL_Wrapper);
            SDL_Wrapper_DibujaImagen(fondo_menu, cont+wSDL_Wrapper, 0, wSDL_Wrapper, hSDL_Wrapper);
            SDL_Wrapper_DibujaImagen(logo, wSDL_Wrapper/2-wLogo/2, hSDL_Wrapper/4, wLogo, hLogo);
            SDL_Wrapper_DibujaImagen(menu, wSDL_Wrapper/2-85, hSDL_Wrapper/2, wMenu, hMenu);
            SDL_Wrapper_DibujaRectangulo(0, 0, wSDL_Wrapper, v_aux);
            SDL_Wrapper_DibujaRectangulo(0, hSDL_Wrapper-v_aux, wSDL_Wrapper, v_aux);
            v_aux -= 15;
            cont -= vFondo;
            SDL_Wrapper_Actualiza();
            SDL_Wrapper_Espera(10);
        }
        SDL_Wrapper_ImagenLibera(nave_intro);

        /* Men� */
        while (SDL_Wrapper_Activa() && !fin)
        {
            /* Controles men� */
            if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_UP) && !flag)
            {
                if (y == hSDL_Wrapper/2)
                    y = hSDL_Wrapper/2 + 120;
                else
                    y -= 30;
                flag = 1;
            }
            if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_DOWN) && !flag)
            {
                if (y == hSDL_Wrapper/2+120)
                    y = hSDL_Wrapper/2;
                else
                    y += 30;
                flag = 1;
            }
            if (!SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_UP) && !SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_DOWN))
                flag = 0;

            /* Men�s extra*/
            if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_RETURN))
            {
                switch (y)
                {
                case hSDL_Wrapper/2:
                    fin = 1;
                    break;

                case hSDL_Wrapper/2 + 30:  /* Muestra los controles */
                    SDL_Wrapper_DibujaImagen(controles, 0, 0, wSDL_Wrapper, hSDL_Wrapper);
                    while(SDL_Wrapper_Activa())
                    {
                        if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_ESCAPE))
                            break;
                        SDL_Wrapper_Actualiza();
                        SDL_Wrapper_Espera(20);
                    }
                    break;

                case hSDL_Wrapper/2 + 60:  /* Muestra los r�cords */
                    SDL_Wrapper_DibujaImagen(record, 0, 0, wSDL_Wrapper, hSDL_Wrapper);
                    int* top = LeerTop("record.txt",5);
                    for (int i=0; i<5; i++)
                        DibujarPuntuacionDerecha(numeros, 6*wSDL_Wrapper/7, hSDL_Wrapper/6+i*(hSDL_Wrapper/8)-5, 50, 50, wSDL_Wrapper/2, top[i]);
                    while(SDL_Wrapper_Activa())
                    {
                        if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_ESCAPE))
                            break;
                        SDL_Wrapper_Actualiza();
                        SDL_Wrapper_Espera(20);
                    }
                    free(top);
                    break;

                case hSDL_Wrapper/2 + 90:  /* Muestra los cr�ditos */
                    SDL_Wrapper_DibujaImagen(creditos, 0, 0, wSDL_Wrapper, hSDL_Wrapper);
                    while(SDL_Wrapper_Activa())
                    {
                        if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_ESCAPE))
                            break;
                        SDL_Wrapper_Actualiza();
                        SDL_Wrapper_Espera(20);
                    };
                    break;

                case hSDL_Wrapper/2 + 120:
                    return 0;
                }
            }

            /* Dibuja los elementos y actualiza la pantalla */
            SDL_Wrapper_DibujaImagen(fondo_menu, cont, 0, wSDL_Wrapper, hSDL_Wrapper);
            SDL_Wrapper_DibujaImagen(fondo_menu, cont+wSDL_Wrapper, 0, wSDL_Wrapper, hSDL_Wrapper);
            SDL_Wrapper_DibujaImagen(logo, wSDL_Wrapper/2-wLogo/2, hSDL_Wrapper/4, wLogo, hLogo);
            SDL_Wrapper_DibujaImagen(menu, wSDL_Wrapper/2-85, hSDL_Wrapper/2, wMenu, hMenu);
            SDL_Wrapper_DibujaImagen(flecha, wSDL_Wrapper/2-100, y, 12, 22);
            cont -= vFondo;
            if (cont <= -wSDL_Wrapper)
                cont = 0;
            SDL_Wrapper_Actualiza();
            SDL_Wrapper_Espera(10);
        }

        // Desvanecimiento de pantalla
        int i=0;
        SDL_Wrapper_ColorTrazo(0,0,0,255);
        while (SDL_Wrapper_Activa()&& i<255)
        {
            SDL_Wrapper_ColorRelleno(0,0,0,i);
            SDL_Wrapper_DibujaRectangulo(0,0,wSDL_Wrapper,hSDL_Wrapper);
            i += 5;
            SDL_Wrapper_Actualiza();
            SDL_Wrapper_Espera(10);
        }

        /** Preparativos (temporales)**/

        /* Liberamos elementos innecesarios del men� */
        SDL_Wrapper_ImagenLibera(fondo_menu);
        SDL_Wrapper_ImagenLibera(menu);
        SDL_Wrapper_ImagenLibera(flecha);
        SDL_Wrapper_ImagenLibera(controles);
        SDL_Wrapper_ImagenLibera(creditos);
        SDL_Wrapper_ImagenLibera(record);

        /* Personaje */
        Imagen nave[num_sprite_nave];
        nave[0] = SDL_Wrapper_ImagenLee("assets/characters/nave0.bmp", 1);     // normal (arriba y abajo)
        nave[1] = SDL_Wrapper_ImagenLee("assets/characters/nave1.bmp", 1);     // arriba izquierda
        nave[2] = SDL_Wrapper_ImagenLee("assets/characters/nave2.bmp", 1);     // izquierda
        nave[3] = SDL_Wrapper_ImagenLee("assets/characters/nave3.bmp", 1);     // arriba derecha
        nave[4] = SDL_Wrapper_ImagenLee("assets/characters/nave4.bmp", 1);     // derecha
        Personaje p = Personaje_Crea(nave, wSDL_Wrapper/2-wPersonaje/2, hSDL_Wrapper-hPersonaje, wPersonaje, hPersonaje);
        Imagen bala_per = SDL_Wrapper_ImagenLee("assets/bullets/0_2.bmp",1);
        Imagen bala_ayu = SDL_Wrapper_ImagenLee("assets/bullets/0.bmp", 1);
        Rafaga RafagaPersonaje = Rafaga_Crea();
        Bala bomba = Bala_Crea(SDL_Wrapper_ImagenLee("assets/bullets/1.bmp",1), 0, 0, wBomba, hBomba, 0, -vDisparo);
        v_aux = vPersonaje;

        /* Enemigos */
        Imagen enem[num_sprite_enemigo];
        enem[0] = SDL_Wrapper_ImagenLee("assets/characters/enemigo0.bmp", 1);
        enem[1] = SDL_Wrapper_ImagenLee("assets/characters/enemigo1.bmp", 1);
        enem[2] = SDL_Wrapper_ImagenLee("assets/characters/enemigo2.bmp", 1);
        enem[3] = SDL_Wrapper_ImagenLee("assets/characters/enemigo3.bmp", 1);
        enem[4] = SDL_Wrapper_ImagenLee("assets/characters/enemigo4.bmp", 1);
        Flota flota = Flota_Crea();
        Imagen bala_enem = SDL_Wrapper_ImagenLee("assets/bullets/2.bmp",1);
        Rafaga RafagaEnemiga = Rafaga_Crea();

        /* Sprite explosion */
        Imagen explosion_roja[estadosExplosion];
        explosion_roja[0] = SDL_Wrapper_ImagenLee("assets/explosion/0_0.bmp", 1);
        explosion_roja[1] = SDL_Wrapper_ImagenLee("assets/explosion/0_1.bmp", 1);
        explosion_roja[2] = SDL_Wrapper_ImagenLee("assets/explosion/0_2.bmp", 1);
        explosion_roja[3] = SDL_Wrapper_ImagenLee("assets/explosion/0_3.bmp", 1);
        explosion_roja[4] = SDL_Wrapper_ImagenLee("assets/explosion/0_4.bmp", 1);
        explosion_roja[5] = SDL_Wrapper_ImagenLee("assets/explosion/0_5.bmp", 1);
        explosion_roja[6] = SDL_Wrapper_ImagenLee("assets/explosion/0_6.bmp", 1);
        explosion_roja[7] = SDL_Wrapper_ImagenLee("assets/explosion/0_7.bmp", 1);
        explosion_roja[8] = SDL_Wrapper_ImagenLee("assets/explosion/0_8.bmp", 1);
        Imagen explosion_azul[estadosExplosion];
        explosion_azul[0] = SDL_Wrapper_ImagenLee("assets/explosion/1_0.bmp", 1);
        explosion_azul[1] = SDL_Wrapper_ImagenLee("assets/explosion/1_1.bmp", 1);
        explosion_azul[2] = SDL_Wrapper_ImagenLee("assets/explosion/1_2.bmp", 1);
        explosion_azul[3] = SDL_Wrapper_ImagenLee("assets/explosion/1_3.bmp", 1);
        explosion_azul[4] = SDL_Wrapper_ImagenLee("assets/explosion/1_4.bmp", 1);
        explosion_azul[5] = SDL_Wrapper_ImagenLee("assets/explosion/1_5.bmp", 1);
        explosion_azul[6] = SDL_Wrapper_ImagenLee("assets/explosion/1_6.bmp", 1);
        explosion_azul[7] = SDL_Wrapper_ImagenLee("assets/explosion/1_7.bmp", 1);
        explosion_azul[8] = SDL_Wrapper_ImagenLee("assets/explosion/1_8.bmp", 1);
        AnimacionMultiple explosiones = AnimacionMultiple_Crea();

        /* Power UP's */
        Galaxia galaxia = Galaxia_Crea(max_powers);
        Imagen_Powers Power[tipos_powers];
        Power[0].img = SDL_Wrapper_ImagenLee("assets/icons/0.bmp", 1);  // vidas extra
        Power[0].w = tam_iconos+8;
        Power[0].h = tam_iconos+4;
        Power[1].img = SDL_Wrapper_ImagenLee("assets/icons/1.bmp", 1);  // 5 puntos
        Power[1].w = tam_iconos;
        Power[1].h = tam_iconos;
        Power[2].img = SDL_Wrapper_ImagenLee("assets/icons/2.bmp", 1);  // 10 puntos
        Power[2].w = tam_iconos;
        Power[2].h = tam_iconos;
        Power[3].img = SDL_Wrapper_ImagenLee("assets/icons/3.bmp", 1);  // escudo
        Power[3].w = tam_iconos+4;
        Power[3].h = tam_iconos+4;
        Power[4].img = SDL_Wrapper_ImagenLee("assets/icons/4.bmp", 1);  // bomba
        Power[4].w = tam_iconos;
        Power[4].h = tam_iconos;
        Power[5].img = SDL_Wrapper_ImagenLee("assets/icons/5.bmp", 1);  // turbo
        Power[5].w = tam_iconos;
        Power[5].h = tam_iconos;
        Power[6].img = SDL_Wrapper_ImagenLee("assets/icons/6.bmp", 1);  // ayudantes
        Power[6].w = tam_iconos;
        Power[6].h = tam_iconos;
        Power[7].img = SDL_Wrapper_ImagenLee("assets/icons/7.bmp", 1);  // 25 puntos
        Power[7].w = tam_iconos;
        Power[7].h = tam_iconos;
        Power[8].img = SDL_Wrapper_ImagenLee("assets/icons/8.bmp", 1);  // rayo destructor
        Power[8].w = tam_iconos;
        Power[8].h = tam_iconos;
        Power[9].img = SDL_Wrapper_ImagenLee("assets/icons/life.bmp", 1);   // icono para el contador de vidas
        Power[9].w = tam_iconos;
        Power[9].h = tam_iconos;

        /* HUD */
        Imagen score = SDL_Wrapper_ImagenLee("assets/hud/score.bmp", 1);
        Imagen trueno = SDL_Wrapper_ImagenLee("assets/hud/thunderbolt.bmp", 1);
        Imagen fondo = SDL_Wrapper_ImagenLee("assets/backgrounds/juego.bmp", 0);

        /* Miscel�nea */
        int vidas = 3;
        int puntos = 0;
        cont = hSDL_Wrapper;
        int disparo_flag = 0;
        int disparo_enem_flag = 0;
        int bomba_flag = 0;
        int cont_bombas = 3;
        int escudo = 0;
        int aceleracion = 0;
        int inmunidad = 0;
        int cont_parpadeo = 0;
        int reaparicion = 0;
        int ayudantes = 0;
        int get_type;    // variable auxiliar para poder obtener el tipo de Potenciador tras la colisi�n
        int pausa = 0;
        Enemigo aux_enem = NULL;
        fin = 0;
        SDL_Wrapper_ColorTrazo(0,0,0,255);

        /* Efecto de transici�n a juego */
        while (SDL_Wrapper_Activa() && i>0)
        {
            cont -= 6;
            if (cont < 0)
                cont = hSDL_Wrapper;
            SDL_Wrapper_DibujaImagen (fondo, 0, -cont, wSDL_Wrapper, hSDL_Wrapper);
            SDL_Wrapper_DibujaImagen (fondo, 0, hSDL_Wrapper-cont, wSDL_Wrapper, hSDL_Wrapper);
            Personaje_Dibuja(p);
            Personaje_Mueve(p, 0, -hSDL_Wrapper/275);
            SDL_Wrapper_ColorRelleno(0, 0, 0, i);
            SDL_Wrapper_DibujaRectangulo(-10, -10, wSDL_Wrapper+10, hSDL_Wrapper+10);
            SDL_Wrapper_ColorRelleno(0, 0, 0, 255);
            SDL_Wrapper_DibujaRectangulo(0, 0, wSDL_Wrapper, hSDL_Wrapper/5);
            SDL_Wrapper_DibujaRectangulo(0, 4*hSDL_Wrapper/5, wSDL_Wrapper, hSDL_Wrapper/5);
            i -= 2;
            SDL_Wrapper_Actualiza();
            SDL_Wrapper_Espera(10);
        }
        i = 1;
        SDL_Wrapper_ColorRelleno(0,0,0,255);
        while (SDL_Wrapper_Activa() && i<hSDL_Wrapper/5)
        {
            cont -= 6;
            if (cont < 0)
                cont = hSDL_Wrapper;
            SDL_Wrapper_DibujaImagen (fondo, 0, -cont, wSDL_Wrapper, hSDL_Wrapper);
            SDL_Wrapper_DibujaImagen (fondo, 0, hSDL_Wrapper-cont, wSDL_Wrapper, hSDL_Wrapper);
            SDL_Wrapper_DibujaImagen(score, 0, hSDL_Wrapper-16, 80, 16);
            DibujarPuntuacionIzquierda(numeros, 82, hSDL_Wrapper-16, 16, 16, 0, puntos);
            SDL_Wrapper_DibujaImagen(Power[9].img, wSDL_Wrapper-20, hSDL_Wrapper-18, 20, 18);
            DibujarContador(numeros, numeros[10], wSDL_Wrapper-44, hSDL_Wrapper-16, 16, 16, vidas);
            SDL_Wrapper_DibujaImagen(Power[4].img, wSDL_Wrapper-20, hSDL_Wrapper-40, 20, 20);
            DibujarContador(numeros, numeros[10], wSDL_Wrapper-44, hSDL_Wrapper-34, 16, 16, cont_bombas);
            Personaje_Dibuja(p);
            SDL_Wrapper_DibujaRectangulo(0, 0-i, wSDL_Wrapper, hSDL_Wrapper/5);
            SDL_Wrapper_DibujaRectangulo(0, 4*hSDL_Wrapper/5+i, wSDL_Wrapper, hSDL_Wrapper/5);
            i += 4;
            SDL_Wrapper_Actualiza();
            SDL_Wrapper_Espera(10);
        }

        /* Post-preparativos */
        int t2 = time(NULL);
        int t1 = 0;
        SDL_Wrapper_ColorTrazo(0, 255, 255, 255);
        SDL_Wrapper_ColorRelleno(255, 255, 255, 125);

        /** JUEGO PRINCIPAL **/

        while (SDL_Wrapper_Activa() && !fin)
        {
            /* Controles y personaje */
            if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_LEFT))
            {
                Personaje_Mueve(p, -v_aux, 0);
                Personaje_CambiaEstado(p, 2);
            }
            if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_RIGHT))
            {
                Personaje_Mueve(p, v_aux, 0);
                Personaje_CambiaEstado(p, 4);
            }
            if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_UP))
                Personaje_Mueve(p, 0, -v_aux);
            if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_DOWN))
                Personaje_Mueve(p, 0, v_aux);
            if ((!SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_RIGHT) && !SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_LEFT)) || (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_RIGHT) && SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_LEFT)))
                Personaje_CambiaEstado(p, 0);
            if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_LEFT) && SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_UP))
                Personaje_CambiaEstado(p, 1);
            if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_RIGHT) && SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_UP))
                Personaje_CambiaEstado(p, 3);
            if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_X) && !disparo_flag && !reaparicion)
            {
                Rafaga_InsertaNuevaBala(RafagaPersonaje, Bala_Crea(bala_per,Personaje_GetX(p)+(wPersonaje/2)-(wDisparo/2),Personaje_GetY(p),wDisparo,hDisparo,0,-vDisparo));
                if (ayudantes)
                {
                    Rafaga_InsertaNuevaBala(RafagaPersonaje, Bala_Crea(bala_ayu, Personaje_GetX(p)+wPersonaje/2-sepAyudantes-wAyudantes/2, Personaje_GetY(p)+hBala/3, wBala, hBala, 0, -vDisparo));
                    Rafaga_InsertaNuevaBala(RafagaPersonaje, Bala_Crea(bala_ayu, Personaje_GetX(p)+wPersonaje/2+sepAyudantes+wAyudantes/2, Personaje_GetY(p)+hBala/3, wBala, hBala, 0, -vDisparo));
                }
                disparo_flag = 1;
            }
            if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_C) && !bomba_flag && cont_bombas && !reaparicion && !flag)
            {
                Bala_CambiaCoordenadas(bomba, Personaje_GetX(p)+wPersonaje/2-wBomba/2, Personaje_GetY(p));
                cont_bombas--;
                bomba_flag = 1;
                flag = 1;
            }
            if (!SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_C))
                flag = 0;
            if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_ESCAPE))
                pausa = 1;

            /* Flota */
            if (!(rand()%(frec_enemigos)) || Flota_Vacia(flota))
            {
                if (rand()%(2))
                    Flota_InsertaNuevoEnemigo(flota, Enemigo_Crea(enem, rand()%(wSDL_Wrapper-wEnemigo), 0, wEnemigo, hEnemigo, -vxEnemigo, vyEnemigo));
                else
                    Flota_InsertaNuevoEnemigo(flota, Enemigo_Crea(enem, rand()%(wSDL_Wrapper-wEnemigo), 0, wEnemigo, hEnemigo, vxEnemigo, vyEnemigo));
            }
            Flota_Mueve(flota);

            /* Disparo de flota */
            if (!disparo_enem_flag && !(rand()%(frec_disparo_enemigo)))
            {
                int aux = rand()%(2);
                switch (aux)
                {
                case 0: // disparo recto
                    aux_enem = Flota_EnemigoAleatorio(flota);
                    if (aux_enem != NULL)
                    {
                        Rafaga_InsertaNuevaBala(RafagaEnemiga, Bala_Crea(bala_enem, Enemigo_GetX(aux_enem)+wEnemigo/2, Enemigo_GetY(aux_enem), wDisparo_enem, hDisparo_enem, 0, vDisparo_enem-3 + rand()%(3)));
                        disparo_enem_flag++;
                    }
                    break;
                case 1: // disparo guiado (IA)
                    aux_enem = Flota_EnemigoMejorATiro(flota, Personaje_GetX(p), Personaje_GetY(p), Personaje_GetW(p), Personaje_GetH(p));
                    if (aux_enem != NULL)
                    {
                        int xaux = Personaje_GetX(p)+Personaje_GetW(p)/2 - (Enemigo_GetX(aux_enem)+Enemigo_GetW(aux_enem)/2);
                        int yaux = Personaje_GetY(p)+Personaje_GetH(p)/2 - (Enemigo_GetY(aux_enem)+Enemigo_GetH(aux_enem)/2);
                        int vyaux = vDisparo_enem-3 + rand()%(3);
                        int vxaux = xaux / (yaux / vyaux);
                        if (abs(vxaux) > vDisparo_enem)
                        {
                            if (vxaux > 0)
                                vxaux = vDisparo_enem;
                            else
                                vxaux = -vDisparo_enem;
                        }
                        Rafaga_InsertaNuevaBala(RafagaEnemiga, Bala_Crea(bala_enem, Enemigo_GetX(aux_enem)+wEnemigo/2, Enemigo_GetY(aux_enem), wDisparo_enem, hDisparo_enem, vxaux, vyaux));
                        disparo_enem_flag++;
                    }
                    break;
                }
            }
            if (disparo_enem_flag)
            {
                disparo_enem_flag++;
                if (disparo_enem_flag >= frec_disparo_enemigo)
                    disparo_enem_flag = 0;
            }
            Rafaga_Mueve(RafagaEnemiga);

            /* Colisi�n del personaje con flota */
            if (!inmunidad && !reaparicion)
            {
                if (Flota_Colision_ConExplosion(flota, explosiones, explosion_roja, estadosExplosion, Personaje_GetX(p), Personaje_GetY(p), Personaje_GetW(p), Personaje_GetH(p), delayExplosion))
                {
                    if(!escudo)
                    {
                        vidas--;
                        reaparicion = 1;
                        ayudantes = 0;
                        if (aceleracion)
                        {
                            aceleracion = 0;
                            v_aux = vPersonaje;
                        }
                        AnimacionMultiple_InsertaNuevaAnimacion(explosiones, Animacion_Crea(explosion_roja, Personaje_GetX(p), Personaje_GetY(p), Personaje_GetW(p), Personaje_GetH(p), estadosExplosion, delayExplosion));
                    }
                    else
                        escudo = 0;
                }
            }


            /* Colisi�n entre r�faga enemiga y personaje */
            if (!inmunidad && !reaparicion)
            {
                if (Rafaga_Colision(RafagaEnemiga, Personaje_GetX(p), Personaje_GetY(p), Personaje_GetW(p), Personaje_GetH(p)))
                {
                    if(!escudo)
                    {
                        vidas--;
                        reaparicion = 1;
                        ayudantes = 0;
                        if (aceleracion)
                        {
                            aceleracion = 0;
                            v_aux = vPersonaje;
                        }
                        AnimacionMultiple_InsertaNuevaAnimacion(explosiones, Animacion_Crea(explosion_roja, Personaje_GetX(p), Personaje_GetY(p), Personaje_GetW(p), Personaje_GetH(p), estadosExplosion, delayExplosion));
                    }
                    else
                        escudo = 0;
                }
            }

            /* Reaparici�n e inmunidad */
            if (reaparicion)
            {
                reaparicion++;
                if (reaparicion >= reaparicion_time)
                {
                    inmunidad = 1;
                    reaparicion = 0;
                    Personaje_CambiaCoordenadas(p, wSDL_Wrapper/2-wPersonaje/2, 4*hSDL_Wrapper/5);
                }
            }
            if (inmunidad)
            {
                inmunidad++;
                if (inmunidad >= inmunidad_time)
                    inmunidad = 0;
            }

            /* Power UP's */
            if (!(rand()%(frec_powers)))
            {
                int tipo = (rand()%(tipos_powers-1));
                Galaxia_InsertaNuevoPotenciador(galaxia, Potenciador_Crea(Power[tipo].img, rand()%(wSDL_Wrapper-Power[tipo].w), -Power[tipo].h, Power[tipo].w, Power[tipo].h, tipo));
            }
            Galaxia_Mueve(galaxia, 0, vGalaxia);

            /* Colisi�n entre personaje y Power UP's */
            if (!reaparicion)
            {
                if (Galaxia_Colision(galaxia, Personaje_GetX(p), Personaje_GetY(p), Personaje_GetW(p), Personaje_GetH(p), &get_type))
                {
                    switch (get_type)
                    {
                    case 0: // vida extra
                        if (vidas<10)
                            vidas++;
                        break;
                    case 1: // 5 puntos
                        puntos += 5;
                        break;
                    case 2: // 10 puntos
                        puntos += 10;
                        break;
                    case 3: // escudo
                        escudo = 1;
                        break;
                    case 4: //bombas
                        if (cont_bombas < bombasMax)
                            cont_bombas++;
                        break;
                    case 5: // aceleracion
                        if (!aceleracion)
                            v_aux *= 1.5;
                        aceleracion = 1;
                        break;
                    case 6: // ayudantes
                        ayudantes = 1;
                        break;
                    case 7: // 25 puntos
                        puntos += 25;
                        break;
                    case 8: // onda destructora
                        aux_enem = Flota_EnemigoMasCercano(flota, Personaje_GetX(p)+wPersonaje/2, Personaje_GetY(p)+hPersonaje/2);
                        for (int j=1; j < enem_onda && aux_enem != NULL; j++)
                        {
                            AnimacionMultiple_InsertaNuevaAnimacion(explosiones, Animacion_Crea(explosion_azul, Enemigo_GetX(aux_enem), Enemigo_GetY(aux_enem), Enemigo_GetW(aux_enem), Enemigo_GetH(aux_enem), estadosExplosion, delayExplosion));
                            Flota_EnemigoLibera(flota, aux_enem);
                            puntos += j*5;
                            aux_enem = Flota_EnemigoMasCercano(flota, Personaje_GetX(p)+wPersonaje/2, Personaje_GetY(p)+hPersonaje/2);
                        }
                        break;
                    }
                }
            }

            /* Disparo */
            if (disparo_flag)
            {
                disparo_flag++;
                if (disparo_flag >= frec_disparo)
                {
                    disparo_flag = 0;
                }
            }
            Rafaga_Mueve(RafagaPersonaje);

            /* Colisi�n entre r�faga y enemigos */
            if (Rafaga_ColisionFlota_ConExplosion(RafagaPersonaje, flota, explosiones, explosion_roja, estadosExplosion, delayExplosion))
                puntos += 5;

            /* Bomba */
            if (bomba_flag)
            {
                if (Bala_Mueve(bomba))
                    bomba_flag = 0;
            }

            /* Colis�n entre bomba y enemigos */
            if (bomba_flag)
            {
                if (Flota_Colision(flota, Bala_GetX(bomba), Bala_GetY(bomba), Bala_GetW(bomba), Bala_GetH(bomba)))
                {
                    puntos += 20 + 40*Flota_ColisionMultiple(flota, Bala_GetX(bomba)-wBomba*(mul_bomba/2), Bala_GetY(bomba)-hBomba*(mul_bomba/2), Bala_GetW(bomba)*mul_bomba, Bala_GetH(bomba)*mul_bomba);
                    AnimacionMultiple_InsertaNuevaAnimacion(explosiones, Animacion_Crea(explosion_roja, Bala_GetX(bomba)-wBomba*(mul_bomba/2), Bala_GetY(bomba)-hBomba*(mul_bomba/2), Bala_GetW(bomba)*mul_bomba, Bala_GetH(bomba)*mul_bomba, estadosExplosion, delayExplosion));
                    bomba_flag = 0;
                }
            }

            /* Aceleraci�n */
            if (aceleracion)
            {
                aceleracion++;
                if (aceleracion >= acel_time)
                {
                    aceleracion = 0;
                    v_aux = vPersonaje;
                }
            }
            /* Ayudantes */
            if (ayudantes)
            {
                ayudantes++;
                if (ayudantes >= ayudantes_time)
                {
                    ayudantes = 0;
                }
            }

            /* Condici�n de terminaci�n */
            if (vidas == 0 && reaparicion == (reaparicion_time-1))
                fin = 1;

            /* Dibuja todos los elementos en pantalla */
            cont -= 6;
            if (cont < 0)
                cont = hSDL_Wrapper;
            SDL_Wrapper_DibujaImagen (fondo, 0, -cont, wSDL_Wrapper, hSDL_Wrapper);
            SDL_Wrapper_DibujaImagen (fondo, 0, hSDL_Wrapper-cont, wSDL_Wrapper, hSDL_Wrapper);
            t1 = t2;
            t2 = time(NULL);
            puntos += t2 - t1;
            SDL_Wrapper_DibujaImagen(score, 0, hSDL_Wrapper-16, 80, 16);
            DibujarPuntuacionIzquierda(numeros, 82, hSDL_Wrapper-16, 16, 16, 0, puntos);
            SDL_Wrapper_DibujaImagen(Power[9].img, wSDL_Wrapper-20, hSDL_Wrapper-18, 20, 18);
            DibujarContador(numeros, numeros[10], wSDL_Wrapper-44, hSDL_Wrapper-16, 16, 16, vidas);
            SDL_Wrapper_DibujaImagen(Power[4].img, wSDL_Wrapper-20, hSDL_Wrapper-40, 20, 20);
            DibujarContador(numeros, numeros[10], wSDL_Wrapper-44, hSDL_Wrapper-34, 16, 16, cont_bombas);
            Galaxia_Dibuja(galaxia);

            if (bomba_flag)
            {
                Bala_Dibuja(bomba);
            }
            Rafaga_Dibuja(RafagaPersonaje);
            if (!inmunidad && !reaparicion)
            {
                Personaje_Dibuja(p);
                if (ayudantes)
                {
                    Personaje_DibujaEnPosicion(p, Personaje_GetX(p)+wPersonaje/2-sepAyudantes-wAyudantes, Personaje_GetY(p), wAyudantes, hAyudantes);
                    Personaje_DibujaEnPosicion(p, Personaje_GetX(p)+wPersonaje/2+sepAyudantes, Personaje_GetY(p), wAyudantes, hAyudantes);
                }
            }
            else
            {
                if (!reaparicion)
                {
                    cont_parpadeo++;
                    if (cont_parpadeo < frec_parpadeo)
                    {
                        Personaje_Dibuja(p);
                        if (ayudantes)
                        {
                            Personaje_DibujaEnPosicion(p, Personaje_GetX(p)+wPersonaje/2-sepAyudantes-wAyudantes, Personaje_GetY(p), wAyudantes, hAyudantes);
                            Personaje_DibujaEnPosicion(p, Personaje_GetX(p)+wPersonaje/2+sepAyudantes, Personaje_GetY(p), wAyudantes, hAyudantes);
                        }
                    }
                    else
                        cont_parpadeo=0;
                }
            }
            if (escudo)
                SDL_Wrapper_DibujaCirculo(Personaje_GetX(p)+wPersonaje/2, Personaje_GetY(p)+hPersonaje/2, hPersonaje);
            Rafaga_Dibuja(RafagaEnemiga);
            Flota_Dibuja(flota, vGiro_min, vGiro_max);
            AnimacionMultiple_ActualizaEstado(explosiones);
            AnimacionMultiple_Dibuja(explosiones);
            if (aceleracion)
                SDL_Wrapper_DibujaImagen(trueno,wSDL_Wrapper/2-7,hSDL_Wrapper-35,15,30);

            /* Refresca la imagen */
            SDL_Wrapper_Actualiza();
            SDL_Wrapper_Espera(10);

            /* Bot�n de pausa */
            if (pausa)
            {
                Imagen flecha = SDL_Wrapper_ImagenLee("assets/menu/flecha.bmp", 1);
                Imagen menu_pausa = SDL_Wrapper_ImagenLee("assets/menu/pausa.bmp", 1);
                y = hSDL_Wrapper/2;
                flag = 1;
                while (SDL_Wrapper_Activa() && pausa)
                {
                    if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_RETURN))
                    {
                        switch (y)
                        {
                        case hSDL_Wrapper/2:
                            pausa = 0;
                            break;
                        case hSDL_Wrapper/2+30:
                            pausa = 0;
                            fin = 1;
                            flag = 1;
                            break;
                        }
                    }
                    if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_UP) && !flag)
                    {
                        if (y == hSDL_Wrapper/2)
                            y = hSDL_Wrapper/2+30;
                        else
                            y = hSDL_Wrapper/2;
                        flag = 1;
                    }
                    if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_DOWN) && !flag)
                    {
                        if (y == hSDL_Wrapper/2+30)
                            y = hSDL_Wrapper/2;
                        else
                            y = hSDL_Wrapper/2+30;
                        flag = 1;
                    }
                    if (!SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_UP) && !SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_DOWN))
                        flag = 0;
                    SDL_Wrapper_DibujaRellenoFondo(0, 0, 0, 0);
                    SDL_Wrapper_DibujaImagen(menu_pausa, wSDL_Wrapper/2-100, hSDL_Wrapper/2, 207, 56);
                    SDL_Wrapper_DibujaImagen(flecha, wSDL_Wrapper/2-115, y, 12, 22);
                    SDL_Wrapper_Actualiza();
                    SDL_Wrapper_Espera(10);
                }
                flag = 1;
                SDL_Wrapper_ImagenLibera(flecha);
                SDL_Wrapper_ImagenLibera(menu_pausa);
            }
        }
        /** SDL_WRAPPER FINAL **/

        /* Liberamos elementos de memoria */
        Personaje_Libera(p);
        Rafaga_Libera(RafagaPersonaje);
        SDL_Wrapper_ImagenLibera(bala_per);
        SDL_Wrapper_ImagenLibera(bala_ayu);
        Bala_Libera(bomba);
        Flota_Libera(flota);
        SDL_Wrapper_ImagenLibera(bala_enem);
        Rafaga_Libera(RafagaEnemiga);
        Galaxia_Libera(galaxia);
        AnimacionMultiple_Libera(explosiones);
        SDL_Wrapper_ImagenLibera(score);
        SDL_Wrapper_ImagenLibera(trueno);
        SDL_Wrapper_ImagenLibera(fondo);

        /* Imprimimos la pantalla final */
        int PuntosMax = LeerRecord("record.txt");
        GuardarPuntuacion("record.txt", puntos);

        fin = 0;

        if (puntos > PuntosMax)
        {
            Imagen newrecord = SDL_Wrapper_ImagenLee("assets/menu/newrecord.bmp", 0);
            SDL_Wrapper_DibujaImagen(newrecord, 0, 0, wSDL_Wrapper, hSDL_Wrapper);
            SDL_Wrapper_ImagenLibera(newrecord);
            DibujarPuntuacionCentrada(numeros, wSDL_Wrapper/2, hSDL_Wrapper/2, 40, 40, puntos);
        }
        else
        {
            Imagen endscreen = SDL_Wrapper_ImagenLee("assets/menu/endscreen.bmp", 0);
            SDL_Wrapper_DibujaImagen(endscreen, 0, 0, wSDL_Wrapper, hSDL_Wrapper);
            SDL_Wrapper_ImagenLibera(endscreen);
            DibujarPuntuacionCentrada(numeros, wSDL_Wrapper/2, hSDL_Wrapper/2, 40, 40, puntos);
            DibujarPuntuacionCentrada(numeros, wSDL_Wrapper/2, 3*hSDL_Wrapper/4, 40, 40, PuntosMax);
        }

        while (SDL_Wrapper_Activa() && !fin)
        {
            if (SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_RETURN) && !flag)
                fin = 1;
            if (!SDL_Wrapper_TeclaPulsada(SDL_SCANCODE_RETURN))
                flag = 0;
            SDL_Wrapper_Actualiza();
            SDL_Wrapper_Espera(20);
        }

    }
    return 0;
}
