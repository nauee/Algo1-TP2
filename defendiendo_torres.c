#include "defendiendo_torres.h"
#include <stdbool.h>
#include <math.h>

/******************************************************************************************** Constantes *********************************************************************************************/

#define TAMANIO_TABLERO_1 15
#define TAMANIO_TABLERO_2 15
#define TAMANIO_TABLERO_3 20
#define TAMANIO_TABLERO_4 20
#define BLANCO "\033[0m"
#define MARRON "\033[0;33m"
#define AZUL "\033[1;34m"
#define AMARILLO "\033[1;33m"
#define ROJO "\033[0;31m"
#define VERDE "\033[0;32m"
const char CAMINO = 'C';
const char ENTRADA = 'E';
const char TORRE = 'T';
const char PASTO = '~';
const char ORCO = 'O';
const int VIDA_INICIAL_TORRES = 600;
const int ELFOS_INICIALES_EXTRA = 10;
const int ENANOS_INICIALES_EXTRA = 10;
const char MAL_ANIMO = 'M';
const char REGULAR_ANIMO = 'R';
const char BUEN_ANIMO = 'B';
const int CRITICOS_MALO = 0;
const int CRITICOS_REGULAR = 10;
const int CRITICOS_BUENO = 25;
const int DIVISOR_FALLO = 2;
static const int NIVEL_1 = 1;
static const int NIVEL_2 = 2;
static const int NIVEL_3 = 3;
static const int NIVEL_4 = 4;
static const int CAMINO_1 = 1;
static const int CAMINO_2 = 2;
const char ENANO = 'G';
const char ELFO = 'L';
const int DISTANCIA_ATAQUE_ENANOS = 1;
const int DANIO_ENANOS = 60;
const int DISTANCIA_ATAQUE_ELFOS = 3;
const int DANIO_ELFOS = 30;
const int AGREGADO_CRITICO = 40;
const int MINIMO_BUENA_RESI = 400;
const int MINIMO_REGULAR_RESI = 200;
const int MINIMO_MALA_RESI = 0;


/***************************************************************************************** Inicializar juego *****************************************************************************************/

/*
*	Postcondiciones: Devolvera la torre con los valores iniciales deseados para el juego.
*/
torres_t torres_iniciales(){
	torres_t torres;
	torres.resistencia_torre_1 = VIDA_INICIAL_TORRES;
	torres.resistencia_torre_2 = VIDA_INICIAL_TORRES;
	torres.enanos_extra = ENANOS_INICIALES_EXTRA;
	torres.elfos_extra = ELFOS_INICIALES_EXTRA;
	return torres;
}

/*
*	Precondiciones: Debe recibir un animo valido (Malo, Regular o Bueno).
*	Postcondiciones: Devolvera el porcentaje de critico segun el animo que reciba.
*/
int critico_segun_animo(char animo){
	int porcentaje_critico;
	if(animo == MAL_ANIMO){
		porcentaje_critico = CRITICOS_MALO;
	}else if(animo == REGULAR_ANIMO){
		porcentaje_critico = CRITICOS_REGULAR;
	}else if(animo == BUEN_ANIMO){
		porcentaje_critico = CRITICOS_BUENO;
	}
	return porcentaje_critico;
}

/*
*	Precondiciones: Debe recibir un condicionante de fallo valido (viento o humedad dependiendo del fallo)
*	Postcondiciones: Devolvera el porcentaje de fallo segun el valor
*/
int fallo_segun_condicionante(int condicionante_fallo){
	int porcentaje_fallo;
	porcentaje_fallo = (condicionante_fallo / DIVISOR_FALLO);
	return porcentaje_fallo;
}

/*
*	Precondiciones: Debe recibir validos a viento(25,50,75), humedad(25,50,75) y animos (M,R,B).
*	Postcondiciones: Inicializara el juego con los valores iniciales indicados.
*/
void inicializar_juego(juego_t *juego, int viento, int humedad, char animo_legolas, char animo_gimli){
	juego -> torres = torres_iniciales();
	juego -> critico_legolas = critico_segun_animo(animo_legolas);
	juego -> critico_gimli = critico_segun_animo(animo_gimli);
	juego -> fallo_legolas = fallo_segun_condicionante(viento);
	juego -> fallo_gimli = fallo_segun_condicionante(humedad);
	juego -> nivel_actual = NIVEL_1;
}

/******************************************************************************************** Estado nivel *******************************************************************************************/

int estado_nivel(nivel_t nivel){
	int estado_nivel = 1;
	if(nivel.tope_enemigos == nivel.max_enemigos_nivel){
		for(int i = 0; i < nivel.tope_enemigos;i++){
			if(nivel.enemigos[i].vida > 0){
				estado_nivel = 0;
			}
		}
	}else{
		estado_nivel = 0;
	}
	return estado_nivel;
}

// Estado juego

int estado_juego(juego_t juego){
	if((juego.nivel_actual == NIVEL_4) && (estado_nivel(juego.nivel) == 1)){
		return 1;
	}else if((juego.torres.resistencia_torre_1 <= 0) || (juego.torres.resistencia_torre_2 <= 0)){
		return -1;
	}else{
		return 0;
	}
}

/****************************************************************************************** Agregar defensor *****************************************************************************************/

/*
*	Precondiciones: Debe recibir un nivel con sus estructuras validas, y una posicion que este dentro del tablero.
*	Postcondiciones: Devolvera true si el defensor a ubicar no esta sobre el camino o sobre otro defensor, y false si lo està.
*/
bool es_posible_poner_defensor(nivel_t nivel, coordenada_t posicion){

	bool posicion_valida = true;
	for(int i = 0; i < nivel.tope_camino_1;i++){
		if((posicion.fil == nivel.camino_1[i].fil) && (posicion.col == nivel.camino_1[i].col)){
			posicion_valida = false;
		}
	}

	for(int j = 0; j < nivel.tope_camino_2;j++){
		if((posicion.fil == nivel.camino_2[j].fil) && (posicion.col == nivel.camino_2[j].col)){
			posicion_valida = false;
		}
	}

	for(int k = 0; k < nivel.tope_defensores; k++){
		if((posicion.fil == nivel.defensores[k].posicion.fil) && (posicion.col == nivel.defensores[k].posicion.col)){
			posicion_valida = false;
		}
	}

	return posicion_valida;
}

int agregar_defensor(nivel_t *nivel, coordenada_t posicion, char tipo){
	if(es_posible_poner_defensor(*nivel, posicion)){
		nivel -> defensores[nivel -> tope_defensores].tipo = tipo;
		nivel -> defensores[nivel -> tope_defensores].posicion = posicion;
		if(tipo == ENANO){
			nivel -> defensores[nivel -> tope_defensores].fuerza_ataque = DANIO_ENANOS;
		}else if(tipo == ELFO){
			nivel -> defensores[nivel -> tope_defensores].fuerza_ataque = DANIO_ELFOS;
		}
		(nivel -> tope_defensores ++);
		return 0;
	}else{
		return -1;
	}
}

/******************************************************************************************** Jugar turno ********************************************************************************************/

/*
*	Precondiciones: Debe recibir un enemigo con su posicion dentro del camino valida y la posicion del enano debe ser valida (estar dentro del tablero).
*	Postcondiciones: Devolvera true si el enemigo esta alrededor del enano y false si no lo esta.
*
*/
bool esta_a_rango_de_enano(enemigo_t enemigo, coordenada_t camino[MAX_LONGITUD_CAMINO], coordenada_t pos_enano){

	return ((abs(camino[enemigo.pos_en_camino].fil - pos_enano.fil) <= DISTANCIA_ATAQUE_ENANOS) && (abs(camino[enemigo.pos_en_camino].col - pos_enano.col) <= DISTANCIA_ATAQUE_ENANOS));
}

/*
*	Precondiciones: Debe recibir un juego con sus estructuras validas, y un indice de enemigo y de enano que no supere al tope de cada uno respectivamente.
*	Postcondiciones: Realizara el ataque del enano sobre el enemigo en caso de que sea posible (el enemigo debe estar alrededor del enano).
*/
void atacan_enanos(juego_t *juego, int n_enano, int n_enemigo, bool *enano_ataco){

	coordenada_t camino[MAX_LONGITUD_CAMINO];
	int tope;
	if(juego -> nivel.enemigos[n_enemigo].camino == CAMINO_1){
		tope = juego -> nivel.tope_camino_1;
		for(int i = 0; i < tope; i++){
			camino[i] = juego -> nivel.camino_1[i];
		}
	}else if(juego -> nivel.enemigos[n_enemigo].camino == CAMINO_2){
		tope = juego -> nivel.tope_camino_2;
		for(int i = 0; i < tope; i++){
			camino[i] = juego -> nivel.camino_2[i];
		}
	}

	if((esta_a_rango_de_enano(juego -> nivel.enemigos[n_enemigo], camino, juego -> nivel.defensores[n_enano].posicion)) && (juego -> nivel.enemigos[n_enemigo].vida > 0)){
		int pos_fallo = rand() % 100;
		*enano_ataco = true;
		if(pos_fallo >= juego -> fallo_gimli){
				int pos_critico = rand() % 100;
				if(pos_critico < juego -> critico_gimli){
					juego -> nivel.enemigos[n_enemigo].vida -= juego -> nivel.defensores[n_enano].fuerza_ataque + AGREGADO_CRITICO;
				}else{
					juego -> nivel.enemigos[n_enemigo].vida -= juego -> nivel.defensores[n_enano].fuerza_ataque;
				}
			}
	}
}

/*
*	Precondiciones: Debe recibir un enemigo con su posicion dentro del camino valida y la posicion del elfo debe ser valida (estar dentro del tablero).
*	Postcondiciones: Devolvera true si el enemigo esta a 3 o menos de distancia del elfo y false si no lo esta.
*/
bool esta_a_rango_de_elfo(enemigo_t enemigo, coordenada_t camino[MAX_LONGITUD_CAMINO], coordenada_t pos_elfo){

	return((abs(camino[enemigo.pos_en_camino].fil - pos_elfo.fil)) + (abs(camino[enemigo.pos_en_camino].col - pos_elfo.col)) <= DISTANCIA_ATAQUE_ELFOS);
}

/*
*	Precondiciones: Debe recibir un juego con sus estructuras validas, y un indice de enemigo y de elfo que no supere al tope de cada uno respectivamente.
*	Postcondiciones: Realizara el ataque del elfo sobre el enemigo en caso de que sea posible (el enemigo este a 3 o menos de distancia del elfo).
*/
void atacan_elfos(juego_t *juego, int n_elfo, int n_enemigo){

	coordenada_t camino[MAX_LONGITUD_CAMINO];
	int tope;
	if(juego -> nivel.enemigos[n_enemigo].camino == CAMINO_1){
		tope = juego -> nivel.tope_camino_1;
		for(int i = 0; i < tope; i++){
			camino[i] = juego -> nivel.camino_1[i];
		}
	}else if(juego -> nivel.enemigos[n_enemigo].camino == CAMINO_2){
		tope = juego -> nivel.tope_camino_2;
		for(int i = 0; i < tope; i++){
			camino[i] = juego -> nivel.camino_2[i];
		}
	}

	if((esta_a_rango_de_elfo(juego -> nivel.enemigos[n_enemigo], camino, juego -> nivel.defensores[n_elfo].posicion)) && (juego -> nivel.enemigos[n_enemigo].vida > 0)){
			int pos_fallo = rand() % 100;
			if(pos_fallo >= juego -> fallo_legolas){
				int pos_critico = rand() % 100;
				if(pos_critico < juego -> critico_legolas){
					juego -> nivel.enemigos[n_enemigo].vida -= juego -> nivel.defensores[n_elfo].fuerza_ataque + AGREGADO_CRITICO;
				}else{
					juego -> nivel.enemigos[n_enemigo].vida -= juego -> nivel.defensores[n_elfo].fuerza_ataque;
				}
			}
		}
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas.
*	Postcondiciones: Realizara el ataque de los defensores en caso de que sea posible (los enemigos esten dentro del rango de ataque de los defensores.
*/
void atacan_defensores(juego_t *juego){
	for(int i = 0; i < juego -> nivel.tope_defensores; i++){
		if((juego -> nivel.defensores[i].tipo) == ENANO){
			int j = 0;
			bool enano_ataco = false;
			while(j < juego -> nivel.tope_enemigos && !enano_ataco){
				atacan_enanos(juego, i, j,&enano_ataco);
				j++;
			}
		}else if((juego -> nivel.defensores[i].tipo) == ELFO){
			for(int j = 0; j < juego -> nivel.tope_enemigos; j++){
				atacan_elfos(juego, i, j);
			}
		}
	}
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas y un camino valido (1 o 2).
*	Postcondiciones: Creara un nuevo orco con todos sus datos validos en la posicion del tope del vector de enemigos.
*/
void crear_nuevo_orco(juego_t *juego, int camino){
	juego -> nivel.enemigos[juego -> nivel.tope_enemigos].camino = camino;
	juego -> nivel.enemigos[juego -> nivel.tope_enemigos].pos_en_camino = 0;
	juego -> nivel.enemigos[juego -> nivel.tope_enemigos].vida = rand() % 101 + 200;
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas.
*	Postcondiciones: Realizara el movimiento de todos los enemigos vivos en el campo, y creara uno nuevo si no se llego al maximo de enemigos del nivel.
*/
void mover_orcos(juego_t *juego){

	if(juego -> nivel.tope_enemigos < juego -> nivel.max_enemigos_nivel){
		if(juego -> nivel_actual == NIVEL_1){
			crear_nuevo_orco(juego,1);
			(juego -> nivel.tope_enemigos) ++;
		}else if(juego -> nivel_actual == NIVEL_2){
			crear_nuevo_orco(juego,2);
			(juego -> nivel.tope_enemigos) ++;
		}else if((juego -> nivel_actual == NIVEL_3) || (juego -> nivel_actual == NIVEL_4)){
			crear_nuevo_orco(juego,1);
			(juego -> nivel.tope_enemigos) ++;
			crear_nuevo_orco(juego,2);
			(juego -> nivel.tope_enemigos) ++;
		}
	}

	for(int i = 0; i < juego -> nivel.tope_enemigos; i++){
		if (juego -> nivel.enemigos[i].vida > 0){
			(juego -> nivel.enemigos[i].pos_en_camino) ++;
		}
	}
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas.
*	Postcondiciones: Comprobara si un enemigo llego a la torre, y en caso de que lo haya hecho, le restara su vida a la torre.
*/
void actualizar_torres(juego_t *juego){
	for(int i = 0; i < (juego -> nivel.tope_enemigos); i++){
		if((juego -> nivel.enemigos[i].pos_en_camino == (juego -> nivel.tope_camino_1 - 1)) && (juego -> nivel.enemigos[i].camino == 1)){
			if(juego -> nivel.enemigos[i].vida >= 0){
				juego -> torres.resistencia_torre_1 -= (juego -> nivel.enemigos[i].vida);
			}
			juego -> nivel.enemigos[i].vida = 0;
		}else if((juego -> nivel.enemigos[i].pos_en_camino == (juego -> nivel.tope_camino_2 - 1)) && (juego -> nivel.enemigos[i].camino == 2)){
			if(juego -> nivel.enemigos[i].vida >= 0){
				juego -> torres.resistencia_torre_2 -= (juego -> nivel.enemigos[i].vida);
			}
			juego -> nivel.enemigos[i].vida = 0;
		}
	}
}

void jugar_turno(juego_t *juego){

	atacan_defensores(juego);
	mover_orcos(juego);
	actualizar_torres(juego);
}

/******************************************************************************************* Mostrar juego *******************************************************************************************/

/*
*	Precondiciones: Debe recibir un tablero y un tope que no supere los maximos de dicho tablero.
*	Postcondiciones: Inicializara todo el tablero con ~, el cual es el caracter de fondo.
*/
void inicializar_tablero(char tablero[MAX_FILAS][MAX_COLUMNAS], int tope){
	for(int i = 0; i < tope; i++){
		for(int j = 0; j < tope; j++){
			tablero[i][j] = '~';
		}
	}
}

/*
*	Precondiciones: Debe recibir un juego con los caminos validos y un nivel actual valido, y un tablero inicializado.
*	Postcondiciones: Dibujara el camino o los caminos sobre el tablero.
*/
void dibujar_camino(char tablero[MAX_FILAS][MAX_COLUMNAS], juego_t juego){
	if(juego.nivel_actual == 1){
		for(int i = 0; i < juego.nivel.tope_camino_1; i++){
			if(i == 0){
				tablero[juego.nivel.camino_1[i].fil][juego.nivel.camino_1[i].col] = ENTRADA;
			}else if(i == (juego.nivel.tope_camino_1 - 1)){
				tablero[juego.nivel.camino_1[i].fil][juego.nivel.camino_1[i].col] = TORRE;
			}else{
				tablero[juego.nivel.camino_1[i].fil][juego.nivel.camino_1[i].col] = CAMINO;
			}
		}
	}else if(juego.nivel_actual == 2){
		for(int i = 0; i < juego.nivel.tope_camino_2; i++){
			if(i == 0){
				tablero[juego.nivel.camino_2[i].fil][juego.nivel.camino_2[i].col] = ENTRADA;
			}else if(i == (juego.nivel.tope_camino_2 - 1)){
				tablero[juego.nivel.camino_2[i].fil][juego.nivel.camino_2[i].col] = TORRE;
			}else{
				tablero[juego.nivel.camino_2[i].fil][juego.nivel.camino_2[i].col] = CAMINO;
			}
		}
	}else if(juego.nivel_actual == 3 || juego.nivel_actual == 4){
		for(int i = 0; i < juego.nivel.tope_camino_1; i++){
			if(i == 0){
				tablero[juego.nivel.camino_1[i].fil][juego.nivel.camino_1[i].col] = ENTRADA;
			}else if(i == (juego.nivel.tope_camino_1 - 1)){
				tablero[juego.nivel.camino_1[i].fil][juego.nivel.camino_1[i].col] = TORRE;
			}else{
				tablero[juego.nivel.camino_1[i].fil][juego.nivel.camino_1[i].col] = CAMINO;
			}
		}
		for(int i = 0; i < juego.nivel.tope_camino_2; i++){
			if(i == 0){
				tablero[juego.nivel.camino_2[i].fil][juego.nivel.camino_2[i].col] = ENTRADA;
			}else if(i == (juego.nivel.tope_camino_2 - 1)){
				tablero[juego.nivel.camino_2[i].fil][juego.nivel.camino_2[i].col] = TORRE;
			}else{
				tablero[juego.nivel.camino_2[i].fil][juego.nivel.camino_2[i].col] = CAMINO;
			}
		}
	}
}

/*
*	Precondiciones: Debe recibir un nivel con sus defensores y su tope validos.
*	Postcondiciones: Dibujara los defensores sobre el tablero.
*/
void dibujar_defensores(char tablero[MAX_FILAS][MAX_COLUMNAS], nivel_t nivel){
	for(int i = 0; i < nivel.tope_defensores; i++){
		tablero[nivel.defensores[i].posicion.fil][nivel.defensores[i].posicion.col] = nivel.defensores[i].tipo;
	}
}

/*
*	Precondiciones: Debe recibir un juego con sus caminos, enemigos y respectivos topes validos.
*	Postcondiciones: Dibujara los enemigos sobre el tablero.
*/
void dibujar_enemigos(char tablero[MAX_FILAS][MAX_COLUMNAS], juego_t juego){
	for(int i = 0; i < juego.nivel.tope_enemigos; i++){
		if(juego.nivel.enemigos[i].camino == 1 && juego.nivel.enemigos[i].vida > 0){
			tablero[juego.nivel.camino_1[juego.nivel.enemigos[i].pos_en_camino].fil][juego.nivel.camino_1[juego.nivel.enemigos[i].pos_en_camino].col] = ORCO;
		}else if(juego.nivel.enemigos[i].camino == 2 && juego.nivel.enemigos[i].vida > 0){
			tablero[juego.nivel.camino_2[juego.nivel.enemigos[i].pos_en_camino].fil][juego.nivel.camino_2[juego.nivel.enemigos[i].pos_en_camino].col] = ORCO;
		}
	}
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas y un tablero con todo dibujado encima.
*	Postcondiciones: Mostrara el tablero con todo lo dibujado anteriormente.
*/
void mostrar_tablero(char tablero[MAX_FILAS][MAX_COLUMNAS], int tope){
	if(tope == TAMANIO_TABLERO_1 || tope == TAMANIO_TABLERO_2){
		printf(""AMARILLO"╔═════════════════════════════════════════════════════════╗"BLANCO"\n");
		printf(""AMARILLO"║                                                         ║"BLANCO"\n");
		printf(""AMARILLO"║       0  1  2  3  4  5  6  7  8  9  10 11 12 13 14      ║"BLANCO"\n");
		printf(""AMARILLO"║     ╔═════════════════════════════════════════════╗     ║"BLANCO"\n");

	}else if(tope == TAMANIO_TABLERO_3 || tope == TAMANIO_TABLERO_4){
		printf(""AMARILLO"╔════════════════════════════════════════════════════════════════════════╗"BLANCO"\n");
		printf(""AMARILLO"║                                                                        ║"BLANCO"\n");
		printf(""AMARILLO"║       0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19      ║"BLANCO"\n");
		printf(""AMARILLO"║     ╔════════════════════════════════════════════════════════════╗     ║"BLANCO"\n");
	}
	for(int i = 0; i < tope; i++){
		if(i < 10){
			printf(""AMARILLO"║    %i║"BLANCO"",i);
		}else{
			printf(""AMARILLO"║   %i║"BLANCO"",i);
		}
		for(int j = 0; j < tope; j++){
			if(tablero[i][j] == CAMINO){
				printf (" "MARRON"■"BLANCO" ");
			}else if(tablero[i][j] == PASTO){
				printf(" "VERDE"%c"BLANCO" ",tablero[i][j]);
			}else if(tablero[i][j] == ORCO){
				printf(" "ROJO"%c"BLANCO" ",tablero[i][j]);
			}else{
				printf(" "AZUL"%c"BLANCO" ",tablero[i][j]);
			}
		}
		if(i < 10){
			printf(""AMARILLO"║%i    ║"BLANCO"\n",i);
		}else{
			printf(""AMARILLO"║%i   ║"BLANCO"\n",i);
		}
	}
	if(tope == TAMANIO_TABLERO_1 || tope == TAMANIO_TABLERO_2){
		printf(""AMARILLO"║     ╚═════════════════════════════════════════════╝     ║"BLANCO"\n");
		printf(""AMARILLO"║       0  1  2  3  4  5  6  7  8  9  10 11 12 13 14      ║"BLANCO"\n");
		printf(""AMARILLO"║                                                         ║"BLANCO"\n");
		printf(""AMARILLO"╠═════════════════════════════════════════════════════════╣"BLANCO"\n");
	}else if(tope == TAMANIO_TABLERO_3 || tope == TAMANIO_TABLERO_4){
		printf(""AMARILLO"║     ╚════════════════════════════════════════════════════════════╝     ║"BLANCO"\n");
		printf(""AMARILLO"║       0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19      ║\n");
		printf(""AMARILLO"║                                                                        ║"BLANCO"\n");
		printf(""AMARILLO"╠════════════════════════════════════════════════════════════════════════╣"BLANCO"\n");
	}
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas.
*	Postcondiciones: Mostrara la resistencia restante de las torres.
*/
void mostrar_vida(juego_t juego){
	printf(""AMARILLO"║ Vida Torre 1:  "BLANCO"");

	for(int i = 0; i < 30;i++){
		if((i*20) < (juego.torres.resistencia_torre_1) && (juego.torres.resistencia_torre_1 >= MINIMO_BUENA_RESI)){
			printf(""VERDE"▒");
		}else if((i*20) < (juego.torres.resistencia_torre_1) && (juego.torres.resistencia_torre_1 >= MINIMO_REGULAR_RESI)){
			printf(""AMARILLO"▒");
		}else if((i*20) < (juego.torres.resistencia_torre_1) && (juego.torres.resistencia_torre_1 > MINIMO_MALA_RESI)){
			printf(""ROJO"▒");
		}else if(juego.torres.resistencia_torre_1 <= 0){
			printf(""ROJO"░");
		}else{
			printf("░");
		}
	}

	if(juego.nivel_actual == NIVEL_1 || juego.nivel_actual == NIVEL_2){
		if(juego.torres.resistencia_torre_1 >= 100){
			printf(" %i/600   "AMARILLO"║"BLANCO"\n", juego.torres.resistencia_torre_1);
		}else if((juego.torres.resistencia_torre_1 >= 10) && (juego.torres.resistencia_torre_1 < 100)){
			printf(" 0%i/600   "AMARILLO"║"BLANCO"\n", juego.torres.resistencia_torre_1);
		}else if((juego.torres.resistencia_torre_1 > 0) && (juego.torres.resistencia_torre_1 < 10)){
			printf(" 00%i/600   "AMARILLO"║"BLANCO"\n", juego.torres.resistencia_torre_1);
		}else{
			printf(" 000/600   "AMARILLO"║"BLANCO"\n");
		}

		printf(""AMARILLO"╠═════════════════════════════════════════════════════════╣"BLANCO"\n");
	}else{
		if(juego.torres.resistencia_torre_1 >= 100){
			printf(" %i/600                  "AMARILLO"║"BLANCO"\n", juego.torres.resistencia_torre_1);
		}else if((juego.torres.resistencia_torre_1 >= 10) && (juego.torres.resistencia_torre_1 < 100)){
			printf(" 0%i/600                  "AMARILLO"║"BLANCO"\n", juego.torres.resistencia_torre_1);
		}else if((juego.torres.resistencia_torre_1 > 0) && (juego.torres.resistencia_torre_1 < 10)){
			printf(" 00%i/600                  "AMARILLO"║"BLANCO"\n", juego.torres.resistencia_torre_1);
		}else{
			printf(" 000/600                  "AMARILLO"║"BLANCO"\n");
		}

		printf(""AMARILLO"╠════════════════════════════════════════════════════════════════════════╣"BLANCO"\n");
	}

	printf(""AMARILLO"║ Vida Torre 2:  ");

	for(int i = 0; i < 30;i++){
		if((i*20) < (juego.torres.resistencia_torre_2) && (juego.torres.resistencia_torre_2 >= MINIMO_BUENA_RESI)){
			printf(""VERDE"▒");
		}else if((i*20) < (juego.torres.resistencia_torre_2) && (juego.torres.resistencia_torre_2 >= MINIMO_REGULAR_RESI)){
			printf(""AMARILLO"▒");
		}else if((i*20) < (juego.torres.resistencia_torre_2) && (juego.torres.resistencia_torre_2 > MINIMO_MALA_RESI)){
			printf(""ROJO"▒");
		}else if(juego.torres.resistencia_torre_2 <= 0){
			printf(""ROJO"░");
		}else{
			printf("░");
		}
	}
	if(juego.nivel_actual == NIVEL_1 || juego.nivel_actual == NIVEL_2){
		if(juego.torres.resistencia_torre_2 >= 100){
			printf(" %i/600   "AMARILLO"║"BLANCO"\n", juego.torres.resistencia_torre_2);
		}else if((juego.torres.resistencia_torre_2 >= 10) && (juego.torres.resistencia_torre_2 < 100)){
			printf(" 0%i/600   "AMARILLO"║"BLANCO"\n", juego.torres.resistencia_torre_2);
		}else if((juego.torres.resistencia_torre_2 > 0) && (juego.torres.resistencia_torre_2 < 10)){
			printf(" 00%i/600   "AMARILLO"║"BLANCO"\n", juego.torres.resistencia_torre_2);
		}else{
			printf(" 000/600   "AMARILLO"║"BLANCO"\n");
		}
		printf(""AMARILLO"╠═════════════════════════════════════════════════════════╣"BLANCO"\n");
	}else{
		if(juego.torres.resistencia_torre_2 >= 100){
			printf(" %i/600                  "AMARILLO"║"BLANCO"\n", juego.torres.resistencia_torre_2);
		}else if((juego.torres.resistencia_torre_2 >= 10)  && (juego.torres.resistencia_torre_2 < 100)){
			printf(" 0%i/600                  "AMARILLO"║"BLANCO"\n", juego.torres.resistencia_torre_2);
		}else if((juego.torres.resistencia_torre_2 > 0)  && (juego.torres.resistencia_torre_2 < 100)){
			printf(" 00%i/600                  "AMARILLO"║"BLANCO"\n", juego.torres.resistencia_torre_2);
		}else{
			printf(" 000/600                  "AMARILLO"║"BLANCO"\n");
		}
		printf(""AMARILLO"╠════════════════════════════════════════════════════════════════════════╣"BLANCO"\n");
	}
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas.
*	Postcondiciones: Mostrara los defensores extras restantes que el usuario puede colocar.
*
*/
void mostrar_defensores_extra(juego_t juego){
	if(juego.nivel_actual == NIVEL_1 || juego.nivel_actual == NIVEL_2){
		if(juego.torres.enanos_extra >= 10){
			printf(""AMARILLO"║ Enanos extra restantes = %i/%i                          ║\n",juego.torres.enanos_extra, ENANOS_INICIALES_EXTRA);
		}else{
			printf(""AMARILLO"║ Enanos extra restantes = %i/%i                           ║\n",juego.torres.enanos_extra, ENANOS_INICIALES_EXTRA);
		}
		if(juego.torres.elfos_extra >= 10){
			printf(""AMARILLO"║ Elfos extra restantes = %i/%i                           ║\n",juego.torres.elfos_extra, ELFOS_INICIALES_EXTRA);
		}else{
			printf(""AMARILLO"║ Elfos extra restantes = %i/%i                            ║\n",juego.torres.elfos_extra, ELFOS_INICIALES_EXTRA);
		}
		printf(""AMARILLO"╚═════════════════════════════════════════════════════════╝"BLANCO"\n");
	}else{
		if(juego.torres.enanos_extra >= 10){
			printf(""AMARILLO"║ Enanos extra restantes = %i/%i                                         ║\n",juego.torres.enanos_extra, ENANOS_INICIALES_EXTRA);
		}else{
			printf(""AMARILLO"║ Enanos extra restantes = %i/%i                                          ║\n",juego.torres.enanos_extra, ENANOS_INICIALES_EXTRA);
		}
		if(juego.torres.elfos_extra >= 10){
			printf(""AMARILLO"║ Elfos extra restantes = %i/%i                                          ║\n",juego.torres.elfos_extra, ELFOS_INICIALES_EXTRA);
		}else{
			printf(""AMARILLO"║ Elfos extra restantes = %i/%i                                           ║\n",juego.torres.elfos_extra, ELFOS_INICIALES_EXTRA);
		}
		printf(""AMARILLO"╚════════════════════════════════════════════════════════════════════════╝"BLANCO"\n");
	}
}

void mostrar_juego(juego_t juego){
	system("clear");
	char tablero[MAX_FILAS][MAX_COLUMNAS];
	int tope_tablero = 0;
	if(juego.nivel_actual == NIVEL_1){
		tope_tablero = TAMANIO_TABLERO_1;
	}else if(juego.nivel_actual == NIVEL_2){
		tope_tablero = TAMANIO_TABLERO_2;
	}else if(juego.nivel_actual == NIVEL_3){
		tope_tablero = TAMANIO_TABLERO_3;
	}else if(juego.nivel_actual == NIVEL_4){
		tope_tablero = TAMANIO_TABLERO_4;
	}
	inicializar_tablero(tablero, tope_tablero);
	dibujar_camino(tablero, juego);
	dibujar_defensores(tablero, juego.nivel);
	dibujar_enemigos(tablero, juego);
	mostrar_tablero(tablero, tope_tablero);
	mostrar_vida(juego);
	mostrar_defensores_extra(juego);
}

/*****************************************************************************************************************************************************************************************************/
