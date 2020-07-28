#include "defendiendo_torres.h"
#include "animos.h"
#include "utiles.h"
#include <time.h>
#include <stdbool.h>
#include "conio.h"

/******************************************************************************************** Constantes *********************************************************************************************/

#define BLANCO "\033[0m"
#define AMARILLO "\033[1;33m"
#define ROJO "\033[0;31m"
#define L_ROJO "\033[1;31m"
#define VERDE "\033[1;32m"
#define L_VERDE "\033[0;32m"
#define MARRON "\033[0;33m"
#define NEGRO "\033[0;30m"
const int NIVEL_1 = 1;
const int NIVEL_2 = 2;
const int NIVEL_3 = 3;
const int NIVEL_4 = 4;
const int CANT_DEFENSORES_1 = 5;
const int CANT_DEFENSORES_2 = 5;
const int CANT_DEFENSORES_3 = 3;
const int CANT_DEFENSORES_4 = 4;
const char ELFOS = 'L';
const char ENANOS ='G';
const int ATAQUE_ENANOS = 60;
const int ATAQUE_ELFOS = 30;
const int POS_MAX_1_2 = 14;
const int POS_MIN_1_2 = 0;
const int POS_MAX_3_4 = 19;
const int POS_MIN_3_4 = 0;
const int ENEMIGOS_NV_1 = 100;
const int ENEMIGOS_NV_2 = 200;
const int ENEMIGOS_NV_3 = 300;
const int ENEMIGOS_NV_4 = 500;
const int CAMINO_1 = 1;
const int CAMINO_2 = 2;
const char SI = 'Y';
const char NO = 'N';
const int COSTO_DEF_EXTRA = 50;

/*********************************************************************************************** Menu ************************************************************************************************/
/*
*	Postcondiciones: Mostrara por pantalla el menu con la opcion actual elegida.
*/
void actualizar_menu(int *opcion_actual){
	if(*opcion_actual == -1){
		*opcion_actual = 2;
	}else if(*opcion_actual == 3){
		*opcion_actual = 0;
	}
	system("clear");
	printf(AMARILLO"╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                                         ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣               DEFENDIENDO               ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                   LAS                   ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                 TORRES!                 ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                                         ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣   Puedes moverte en el menu con W y S   ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	if(*opcion_actual == 0){
		printf(AMARILLO"╠╬╬╬╬╣ -> Jugar                                ╠╬╬╬╬╣\n");
	}else{
		printf(AMARILLO"╠╬╬╬╬╣    Jugar                                ╠╬╬╬╬╣\n");
	}
	if(*opcion_actual == 1){
		printf(AMARILLO"╠╬╬╬╬╣ -> Cambiar velocidad                    ╠╬╬╬╬╣\n");
	}else{
		printf(AMARILLO"╠╬╬╬╬╣    Cambiar velocidad                    ╠╬╬╬╬╣\n");
	}
	if(*opcion_actual == 2){
		printf(AMARILLO"╠╬╬╬╬╣ -> Salir                                ╠╬╬╬╬╣\n");
	}else{
		printf(AMARILLO"╠╬╬╬╬╣    Salir                                ╠╬╬╬╬╣\n");
	}
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n");
}

/*
*	Precondiciones: Debe recibir una opcion valida (0,1,2).
*	Postcondiciones: Devolvera la opcion elegida segun lo que haya elegido el usuario.
*/
void entrar_menu(int opcion_actual, bool *entro_a_menu, int *opcion_elegida){
	if(opcion_actual == 0){
		*opcion_elegida = 0;
		*entro_a_menu = true;
	}else if(opcion_actual == 1){
		*opcion_elegida = 1;
		*entro_a_menu = true;
	}else{
		*opcion_elegida = 2;
		*entro_a_menu = true;
	}
}

/*
*	Postcondiciones: Mostrara un mensaje de cargando para el menu.
*/
void mostrar_mensaje_cargando_menu(){
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 5; j++){
			system("clear");
			printf(AMARILLO"╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
			printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
			printf(AMARILLO"╠╬╬╬╬╣                                         ╠╬╬╬╬╣\n");
			printf(AMARILLO"╠╬╬╬╬╣               DEFENDIENDO               ╠╬╬╬╬╣\n");
			printf(AMARILLO"╠╬╬╬╬╣                   LAS                   ╠╬╬╬╬╣\n");
			printf(AMARILLO"╠╬╬╬╬╣                 TORRES!                 ╠╬╬╬╬╣\n");
			printf(AMARILLO"╠╬╬╬╬╣                                         ╠╬╬╬╬╣\n");
			printf(AMARILLO"╠╬╬╬╬╣                 Suerte!                 ╠╬╬╬╬╣\n");
			printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
			printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
			printf(AMARILLO"╠╬╬╬╬╣                                         ╠╬╬╬╬╣\n");
			printf(AMARILLO"╠╬╬╬╬╣              Cargando ");
			if(j == 0){
				printf(".                 ╠╬╬╬╬╣\n");
			}else if(j == 1){
				printf("..                ╠╬╬╬╬╣\n");
			}else if(j == 2){
				printf("...               ╠╬╬╬╬╣\n");
			}else if(j == 3){
				printf("....              ╠╬╬╬╬╣\n");
			}else if(j == 4){
				printf(".....             ╠╬╬╬╬╣\n");
			}
			fflush(stdout);
			printf(AMARILLO"╠╬╬╬╬╣                                         ╠╬╬╬╬╣\n");
			printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
			printf(AMARILLO"╠╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╣\n");
			printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n");
			detener_el_tiempo(0.25);
		}

	}
}

/*
*	Precondiciones: Recibe un estado del menu.
*	Postcondiciones: Modificara el estado del menu segun lo elegido por el usuario (0 para jugar, 1 para modificar velocidad y 2 para salir).
*/
void menu_principal(int *estado_menu){
	int opcion_actual = 0;
	int tecla_pulsada;
	bool entro_a_menu = false;
	int opcion_elegida = 0;
	actualizar_menu(&opcion_actual);
	while(!entro_a_menu){
		tecla_pulsada = getch();
		switch(tecla_pulsada){
			case 'W':
				opcion_actual --;
				actualizar_menu(&opcion_actual);
				break;
			case 'w':
				opcion_actual --;
				actualizar_menu(&opcion_actual);
				break;
			case 'S':
				opcion_actual ++;
				actualizar_menu(&opcion_actual);
				break;
			case 's':
				opcion_actual ++;
				actualizar_menu(&opcion_actual);
				break;
			case '\n':
				entrar_menu(opcion_actual,&entro_a_menu,&opcion_elegida);
				break;
		}
	}
	mostrar_mensaje_cargando_menu();
	*estado_menu = opcion_elegida;
}


/************************************************************************************ Cambiar velocidad de juego *************************************************************************************/

/*
*	Postcondiciones: Mostrara la pantalla de seleccion de velocidad de juego con la opcion actual elegida.
*/
void actualizar_velocidad_juego(int *opcion_actual){
	system("clear");
	printf(AMARILLO"╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                                         ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    Ajusta la barra con A y D, segun     ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    la velocidad que prefieras.          ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    Presiona ENTER para confirmar        ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    y volver al menu                     ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                                         ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");

	if(*opcion_actual == -1){
		*opcion_actual = 0;
	}else if(*opcion_actual == 5){
		*opcion_actual = 4;
	}

	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                                         ╠╬╬╬╬╣\n");
	if(*opcion_actual == 0){
		printf(AMARILLO"╠╬╬╬╬╣"L_VERDE"          ▓▓░░░░░░░░ Muy lenta           "AMARILLO"╠╬╬╬╬╣\n");
	}else if(*opcion_actual == 1){
		printf(AMARILLO"╠╬╬╬╬╣"VERDE"          ▓▓▓▓░░░░░░ Lenta               "AMARILLO"╠╬╬╬╬╣\n");
	}else if(*opcion_actual == 2){
		printf(AMARILLO"╠╬╬╬╬╣"AMARILLO"          ▓▓▓▓▓▓░░░░ Normal              "AMARILLO"╠╬╬╬╬╣\n");
	}else if(*opcion_actual == 3){
		printf(AMARILLO"╠╬╬╬╬╣"L_ROJO"          ▓▓▓▓▓▓▓▓░░ Rapida              "AMARILLO"╠╬╬╬╬╣\n");
	}else if(*opcion_actual == 4){
		printf(AMARILLO"╠╬╬╬╬╣"ROJO"          ▓▓▓▓▓▓▓▓▓▓ Muy rapida          "AMARILLO"╠╬╬╬╬╣\n");
	}
	printf(AMARILLO"╠╬╬╬╬╣                                         ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n");
}

/*
*	Precondiciones: Debe recibir una opcion actual valida.
*	Postcondiciones: Modificara la velocidad elegida segun sea la opcion elegida por el usuario.
*/
void confirmar_velocidad_juego(int opcion_actual, float *velocidad_elegida, bool *eligio_velocidad){
	if(opcion_actual == 0){
		*velocidad_elegida = 1.25;
	}else if(opcion_actual == 1){
		*velocidad_elegida = 1;
	}else if(opcion_actual == 2){
		*velocidad_elegida = 0.75;
	}else if(opcion_actual == 3){
		*velocidad_elegida = 0.5;
	}else if(opcion_actual == 4){
		*velocidad_elegida = 0.25;
	}
	*eligio_velocidad = true;
}

/*
*	Precondiciones: Debe recibir una velocidad de juego valida (0.25, 0.5, 0.75, 1.0, 1.25).
*	Postcondiciones: Modificara la velocidad del juego por la elegida por el usuario.
*/
void cambiar_velocidad_de_juego(float *velocidad_de_juego){
	int opcion_actual;
	if(*velocidad_de_juego == 0.25){
		opcion_actual = 4;
	}else if(*velocidad_de_juego == 0.5){
		opcion_actual = 3;
	}else if(*velocidad_de_juego == 0.75){
		opcion_actual = 2;
	}else if(*velocidad_de_juego == 1){
		opcion_actual = 1;
	}else if(*velocidad_de_juego == 1.25){
		opcion_actual = 0;
	}
	int tecla_pulsada;
	bool eligio_velocidad = false;
	actualizar_velocidad_juego(&opcion_actual);
	while(!eligio_velocidad){
		tecla_pulsada = getch();
		switch(tecla_pulsada){
			case 'A':opcion_actual --;actualizar_velocidad_juego(&opcion_actual);break;
			case 'a':opcion_actual --;actualizar_velocidad_juego(&opcion_actual);break;
			case 'D':opcion_actual ++;actualizar_velocidad_juego(&opcion_actual);break;
			case 'd':opcion_actual ++;actualizar_velocidad_juego(&opcion_actual);break;
			case '\n':confirmar_velocidad_juego(opcion_actual,velocidad_de_juego,&eligio_velocidad);break;
		}
	}
}

/******************************************************************************************* Presentacion ********************************************************************************************/

/*
*	Postcondiciones: Mostrara la introduccion al juego.
*/
void mostrar_dibujo_portada (){

	for(int i = 0; i < 4; i++){
	system("clear");
		printf("                                o\n");
		printf("                             .-'|\n");
		printf("                             |-'|\n");
		printf("                                |   _.-'`.\n");
		printf("                               _|-''_.-'|.`.\n");
		printf("                              |:^.-'_.-'`.;.`.\n");
		printf("                              | `.'.   ,-'_.-'|\n");
		printf("                              |   + '-'.-'   J\n");
		printf("           __.            .d88| +. `.-' _-.  |\n");
		printf("      _.--'_..`.    .d88888888| ||] |  | J] J8b.\n");
		printf("   +:'' ,--'_.|`.`.d88888888888|-' J |  | J|.|888b.\n");
		printf("   | \\ \\-'_.--'_.-+888888888+'  _-F F +:    `88888bo.                  ");
		if(i == 0){
			printf("\n");
		}
		else if(i > 0){
			printf("________  _______   ________ _______   ________   ________  ___  _______   ________   ________  ________      \n");
		}
		printf("    L \\ +'_.--'   |88888+''  _.' J J J  `.    +8888888b.              ");
		if(i == 0){
			printf("\n");
		}
		else if(i > 0){
			printf("|\\   ___ \\|\\  ___ \\ |\\  _____\\\\  ___ \\ |\\   ___  \\|\\   ___ \\|\\  \\|\\  ___ \\ |\\   ___  \\|\\   ___ \\|\\   __  \\     \n");
		}
		printf("    L \\ +'_.--'   |88888+''  _.' J J J  `.    +8888888b.              ");
		if(i == 0){
			printf("\n");
		}
		else if(i > 0){
			printf("\\ \\  \\_|\\ \\ \\   __/|\\ \\  \\__/\\ \\   __/|\\ \\  \\\\ \\  \\ \\  \\_|\\ \\ \\  \\ \\   __/|\\ \\  \\\\ \\  \\ \\  \\_|\\ \\ \\  \\|\\  \\    \n");
		}
		printf("    |  `+'   __   |8+''  _.-'    | | |    +    `+8888888._-'.          ");
		if(i == 0){
			printf("\n");
		}
		else if(i > 0){
			printf("\\ \\  \\ \\\\ \\ \\  \\_|/_\\ \\   __\\\\ \\  \\_|/_\\ \\  \\\\ \\  \\ \\  \\ \\\\ \\ \\  \\ \\  \\_|/_\\ \\  \\\\ \\  \\ \\  \\ \\\\ \\ \\  \\\\\\  \\   \n");
		}
		printf("  .d8L  L   / \\\\  J' _.-'        | | |     `.,   `+888+'^.-|.`.         ");
		if(i == 0){
			printf("\n");
		}
		else if(i > 0){
			printf("\\ \\  \\_\\\\ \\ \\  \\_|\\ \\ \\  \\_| \\ \\  \\_|\\ \\ \\  \\\\ \\  \\ \\  \\_\\\\ \\ \\  \\ \\  \\_|\\ \\ \\  \\\\ \\  \\ \\  \\_\\\\ \\ \\  \\\\\\  \\  \n");
		}
		printf(" d888|  |   F  FL J-'            F F F      /`/  _.-'_.-'_.+.`.`.        ");
		if(i == 0){
			printf("\n");
		}
		else if(i > 0){
			printf("\\ \\_______\\ \\_______\\ \\__\\   \\ \\_______\\ \\__\\\\ \\__\\ \\_______\\ \\__\\ \\_______\\ \\__\\\\ \\__\\ \\_______\\ \\_______\\ \n");
		}
		printf("d88888L  L  |  \\L  L            J J J      /`/ `|. +'_.-'    `_+ `;       ");
		if(i == 0){
			printf("\n");
		}
		else if(i > 0){
			printf("\\|_______|\\|_______|\\|__|    \\|_______|\\|__| \\|__|\\|_______|\\|__|\\|_______|\\|__| \\|__|\\|_______|\\|_______| \n");
		}
		fflush(stdout);
		printf("888888J  |  K    \\ L         _.-+.|.'.    /`/   F `.`.     .-'_.-'J\n");
		printf("8888888|  L L\\    \\|     _.-'     '   `. /`/   J  ,_`.`..-'.-'    |            ");
		if(i < 2){
			printf("\n");
		}else if(i == 2){
			printf("___       ________  ________\n");
		}else if(i == 3){
			printf("___       ________  ________           _________  ________  ________  ________  _______   ________      \n");
		}
		printf("8888888PL | | \\    `._.-'               /`/    | || \\ `..-'      J.b          ");
		if(i < 2){
			printf("\n");
		}else if(i == 2){
			printf("|\\  \\     |\\   __  \\|\\   ____\\\n");
		}else if(i == 3){
			printf("|\\  \\     |\\   __  \\|\\   ____\\         |\\___   ___\\\\   __  \\|\\   __  \\|\\   __  \\|\\  ___ \\ |\\   ____\\    \n");
		}
		printf("8888888 |  L L `.    \\     _.-+.       /`/`.   L+`'  |  |        F88b         ");
		if(i < 2){
			printf("\n");
		}else if(i == 2){
			printf("\\ \\  \\    \\ \\  \\|\\  \\ \\  \\___|_\n");
		}else if(i == 3){
			printf("\\ \\  \\    \\ \\  \\|\\  \\ \\  \\___|_        \\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\ \\   __/|\\ \\  \\___|_ \n");
		}
		printf("8888888  L | |   \\   _:.--'_.-|.`.    '`/   >-'     .J J        |8888b         ");
		if(i < 2){
			printf("\n");
		}else if(i == 2){
			printf("\\ \\  \\    \\ \\   __  \\ \\_____  \\\n");
		}else if(i == 3){
			printf("\\ \\  \\    \\ \\   __  \\ \\_____  \\            \\ \\  \\ \\ \\  \\\\\\  \\ \\   _  _\\ \\   _  _\\ \\  \\_|/_\\ \\_____  \\  \n");
		}
		printf("8888888  |  L L   +:' _.--'_.-'.`.`.    _.-'    :'|' | |       JY88888b         ");
		if(i < 2){
			printf("\n");
		}else if(i == 2){
			printf("\\ \\  \\____\\ \\  \\ \\  \\|____|\\  \\\n");
		}else if(i == 3){
			printf("\\ \\  \\____\\ \\  \\ \\  \\|____|\\  \\            \\ \\  \\ \\ \\  \\\\\\  \\ \\  \\\\  \\\\ \\  \\\\  \\\\ \\  \\_|\\ \\|____|\\  \\  \n");
		}
		printf("8888888   L | |   J \\ \\_.-'     `.`.`.-'    :'|-'   J J        F Y88888b         ");
		if(i < 2){
			printf("\n");
		}else if(i == 2){
			printf("\\ \\_______\\ \\__\\ \\__\\____\\_\\  \\\n");
		}else if(i == 3){
			printf("\\ \\_______\\ \\__\\ \\__\\____\\_\\  \\            \\ \\__\\ \\ \\_______\\ \\__\\\\ _\\\\ \\__\\\\ _\\\\ \\_______\\____\\_\\  \\ \n");
		}
		printf("Y888888    \\ L L   L \\ `.      _.-'_.-+ :'|-'       | |       |   Y88888b         ");
		if(i < 2){
			printf("\n");
		}else if(i == 2){
			printf("\\|_______|\\|__|\\|__|\\_________\\\n");
		}else if(i == 3){
			printf("\\|_______|\\|__|\\|__|\\_________\\            \\|__|  \\|_______|\\|__|\\|__|\\|__|\\|__|\\|_______|\\_________\\ \n");
		}
		printf("`888888b    \\| |   |  `. \\ _.-'_.-'   |-'          J J       J     Y88888b                           ");
		if(i < 2){
			printf("\n");
		}else if(i == 2){
			printf("\\|_________|\n");
		}else if(i == 3){
			printf("\\|_________|                                                          \\|_________|\n");
		}
		printf(" Y888888     +'\\   J    \\ '_.-'       F    ,-T'\\   | |    .-'      )888888\n");
		printf("  Y88888b.      \\   L    +'          J    /  | J  J J  .-'        .d888888\n");
		printf("   Y888888b      \\  |    |           |    F  '.|.-'+|-'         .d88888888\n");
		printf("    Y888888b      \\ J    |           F   J    -:              .od88888888P\n");
		printf("     Y888888b      \\ L   |          J    | .' ` \\d8888888888888888888888P\n");
		printf("      Y888888b      \\|   |          |  .-'`.  `\\ `+88888888888888888888P\n");
		printf("       Y888888b.     J   |          F-'     \\ ` \\ \\88888888888888888P'\n");
		printf("        Y8888888b     L  |         J       d8+.`\\  \\`+8888888888888P'\n");
		printf("         Y8888888b    |  |        .+      d8888\\  ` .'  `Y888888P'\n");
		printf("         `88888888b   J  |     .-'     .od888888\\.-'\n");
		printf("          Y88888888b   \\ |  .-'     d888888888P'\n");
		printf("          `888888888b   \\|-'       d88888888'\n");
		printf("           `Y88888888b            d8888888P'\n");
		printf("             Y88888888bo.      .od88888888\n");
		printf("             `8888888888888888888888888888\n");
		printf("              Y88888888888888888888888888P\n");
		printf("               `Y8888888888888888888888P'\n");
		printf("                 `Y8888888888888P'\n");
		printf("                      `Y88888P'\n");
		detener_el_tiempo(1);
	}
	//system("clear");
}

/******************************************************************************************* Iniciar nivel *******************************************************************************************/

/*
*	Postcondiciones: Mostrara un mensaje de cargando.
*/
void mostrar_mensaje_cargando_simple(){
	printf(AMARILLO" -> Cargando .");
	for(int i = 0; i < 10; i++){
		printf(".");
		fflush(stdout);
		detener_el_tiempo(0.25);
	}
}

/*
*	Precondiciones: Debe recibir un nivel_actual valido (1,2,3,4).
*	Postcondiciones: Mostrara la introduccion del nivel que se haya ingresado.
*/
void mostrar_introduccion_nivel(int nivel_actual){
	mostrar_mensaje_cargando_simple();
	system("clear");
	printf(""AMARILLO"╔═════════════════════════════════════════════════════════╗\n");
	printf("║ ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ ║\n");
	printf("║ ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ ║\n");
	printf("║ ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ ║\n");
	printf("║ ░░░░░ ╔══════════════════════════════════════════╗ ░░░░ ║\n");
	printf("║ ▒▒▒▒▒ ║                                          ║ ▒▒▒▒ ║\n");
	printf("║ ░░░░░ ║  ██    █   █   █     █   █▀▀▀▀   █       ║ ░░░░ ║\n");
	printf("║ ▒▒▒▒▒ ║  █ █   █   █   █     █   █       █       ║ ▒▒▒▒ ║\n");
	printf("║ ░░░░░ ║  █  █  █   █    █   █    █■■■■   █       ║ ░░░░ ║\n");
	printf("║ ▒▒▒▒▒ ║  █   █ █   █     █ █     █       █       ║ ▒▒▒▒ ║\n");
	printf("║ ░░░░░ ║  █    ██   █      █      █▄▄▄▄   █▄▄▄▄▄  ║ ░░░░ ║\n");
	printf("║ ▒▒▒▒▒ ║                                          ║ ▒▒▒▒ ║\n");
	printf("║ ░░░░░ ║                                          ║ ░░░░ ║\n");
	if(nivel_actual == NIVEL_1){
		printf("║ ▒▒▒▒▒ ║                 ▀▀█▀▀                    ║ ▒▒▒▒ ║\n");
		printf("║ ░░░░░ ║                   █                      ║ ░░░░ ║\n");
		printf("║ ▒▒▒▒▒ ║                   █                      ║ ▒▒▒▒ ║\n");
		printf("║ ░░░░░ ║                   █                      ║ ░░░░ ║\n");
		printf("║ ▒▒▒▒▒ ║                 ▄▄█▄▄                    ║ ▒▒▒▒ ║\n");
	}else if(nivel_actual == NIVEL_2){
		printf("║ ▒▒▒▒▒ ║                ▀▀█▀▀▀█▀▀                 ║ ▒▒▒▒ ║\n");
		printf("║ ░░░░░ ║                  █   █                   ║ ░░░░ ║\n");
		printf("║ ▒▒▒▒▒ ║                  █   █                   ║ ▒▒▒▒ ║\n");
		printf("║ ░░░░░ ║                  █   █                   ║ ░░░░ ║\n");
		printf("║ ▒▒▒▒▒ ║                ▄▄█▄▄▄█▄▄                 ║ ▒▒▒▒ ║\n");
	}else if(nivel_actual == NIVEL_3){
		printf("║ ▒▒▒▒▒ ║             ▀▀█▀▀▀█▀▀▀█▀▀                ║ ▒▒▒▒ ║\n");
		printf("║ ░░░░░ ║               █   █   █                  ║ ░░░░ ║\n");
		printf("║ ▒▒▒▒▒ ║               █   █   █                  ║ ▒▒▒▒ ║\n");
		printf("║ ░░░░░ ║               █   █   █                  ║ ░░░░ ║\n");
		printf("║ ▒▒▒▒▒ ║             ▄▄█▄▄▄█▄▄▄█▄▄                ║ ▒▒▒▒ ║\n");
	}else if(nivel_actual == NIVEL_4){
		printf("║ ▒▒▒▒▒ ║            ▀▀█▀▀▀█▀▀▀▀▀█▀▀               ║ ▒▒▒▒ ║\n");
		printf("║ ░░░░░ ║              █   █     █                 ║ ░░░░ ║\n");
		printf("║ ▒▒▒▒▒ ║              █    █   █                  ║ ▒▒▒▒ ║\n");
		printf("║ ░░░░░ ║              █     █ █                   ║ ░░░░ ║\n");
		printf("║ ▒▒▒▒▒ ║            ▄▄█▄▄▄▄▄▄█▄▄▄▄                ║ ▒▒▒▒ ║\n");
	}
	printf("║ ░░░░░ ║                                          ║ ░░░░ ║\n");
	printf("║ ▒▒▒▒▒ ╚══════════════════════════════════════════╝ ▒▒▒▒ ║\n");
	printf("║ ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ ║\n");
	printf("║ ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ ║\n");
	printf("║ ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ ║\n");
	printf("╚═════════════════════════════════════════════════════════╝"BLANCO"\n");

	detener_el_tiempo(2);
	system("clear");
}

/*
*	Precondiciones: Debe recibir un juego con caminos creados.
*	Postcondiciones: Devolvera true si los caminos no se juntan, y false si lo hacen.
*/
bool son_caminos_separados(juego_t juego){

	bool caminos_separados = true;
	int i = 0;

	while(caminos_separados == true && i < juego.nivel.tope_camino_1){
		for(int j = 0; j < juego.nivel.tope_camino_2; j++){
			if((juego.nivel.camino_1[i].fil == juego.nivel.camino_2[j].fil) && (juego.nivel.camino_1[i].col == juego.nivel.camino_2[j].col)){
				caminos_separados = false;
			}
		}
		i++;
	}

	return caminos_separados;
}

/*
*	Precondiciones: Debera recibir un juego con un nivel valido (1,2,3,4).
*	Postcondiciones: Creara el o los caminos validos segun el nivel correspondiente.
*/
void crear_caminos(juego_t *juego){

	coordenada_t entrada1;
	coordenada_t torre1;
	coordenada_t entrada2;
	coordenada_t torre2;

	if(juego -> nivel_actual == NIVEL_1){
		entrada1.fil = rand() % 15;
		entrada1.col = 14;
		torre1.fil = rand() % 15;
		torre1.col = 0;
	}else if(juego -> nivel_actual == NIVEL_2){
		entrada2.fil = rand() % 15;
		entrada2.col = 0;
		torre2.fil = rand() % 15;
		torre2.col = 14;
	}else if(juego -> nivel_actual == NIVEL_3){
		entrada1.fil = 0;
		entrada1.col = rand() % 10;;
		torre1.fil = 19;
		torre1.col = rand() % 10;;
		entrada2.fil = 0;
		entrada2.col = rand() % 10 + 10;;
		torre2.fil = 19;
		torre2.col = rand() % 10 + 10;
	}else if(juego -> nivel_actual == NIVEL_4){
		entrada1.fil = 19;
		entrada1.col = rand() % 10;
		torre1.fil = 0;
		torre1.col = rand() % 10;

		entrada2.fil = 19;
		entrada2.col = rand() % 10 + 10;
		torre2.fil = 0;
		torre2.col = rand() % 10 + 10;
	}

	if(juego -> nivel_actual == NIVEL_1){
		obtener_camino(juego -> nivel.camino_1,&(juego -> nivel.tope_camino_1), entrada1, torre1);
		while(juego -> nivel.tope_camino_1 < 50){
			obtener_camino(juego -> nivel.camino_1,&(juego -> nivel.tope_camino_1), entrada1, torre1);
		}
		juego -> nivel.tope_camino_2 = 0;
	}else if(juego -> nivel_actual == NIVEL_2){
		obtener_camino(juego -> nivel.camino_2,&(juego -> nivel.tope_camino_2), entrada2, torre2);
		while(juego -> nivel.tope_camino_2 < 50){
			obtener_camino(juego -> nivel.camino_2,&(juego -> nivel.tope_camino_2), entrada2, torre2);
		}
		juego -> nivel.tope_camino_1 = 0;
	}else if(juego -> nivel_actual == NIVEL_3 || juego -> nivel_actual == NIVEL_4){
		obtener_camino(juego -> nivel.camino_1, &(juego -> nivel.tope_camino_1), entrada1, torre1);
		while(juego -> nivel.tope_camino_1 < 50){
			obtener_camino(juego -> nivel.camino_1,&(juego -> nivel.tope_camino_1), entrada1, torre1);
		}
		obtener_camino(juego -> nivel.camino_2, &(juego -> nivel.tope_camino_2), entrada2, torre2);
		while(juego -> nivel.tope_camino_1 < 50){
			obtener_camino(juego -> nivel.camino_2,&(juego -> nivel.tope_camino_2), entrada2, torre2);
		}
		while(!son_caminos_separados(*juego)){
			obtener_camino(juego -> nivel.camino_1, &(juego -> nivel.tope_camino_1), entrada1, torre1);
			while(juego -> nivel.tope_camino_1 < 50){
				obtener_camino(juego -> nivel.camino_1,&(juego -> nivel.tope_camino_1), entrada1, torre1);
			}
			obtener_camino(juego -> nivel.camino_2, &(juego -> nivel.tope_camino_2), entrada2, torre2);
			while(juego -> nivel.tope_camino_1 < 50){
				obtener_camino(juego -> nivel.camino_2,&(juego -> nivel.tope_camino_2), entrada2, torre2);
			}
		}
	}
}

/*
*	Precondiciones: Debe recibir un juego con un nivel valido (1,2,3,4).
*	Postcondiciones: Devolvera true si la posicion esta dentro del tablero o false si no lo esta.
*/
bool esta_dentro_del_tablero(juego_t juego, coordenada_t posicion){
	bool esta_dentro = true;
	if(juego.nivel_actual == NIVEL_1 || juego.nivel_actual == NIVEL_2){
		if((posicion.fil > POS_MAX_1_2) || (posicion.fil < POS_MIN_1_2) || (posicion.col > POS_MAX_1_2) || (posicion.col < POS_MIN_1_2)){
			esta_dentro = false;
		}
	}else{
		if((posicion.fil > POS_MAX_3_4) || (posicion.fil < POS_MIN_3_4) || (posicion.col > POS_MAX_3_4) || (posicion.col < POS_MIN_3_4)){
			esta_dentro = false;
		}
	}
	return esta_dentro;
}

/*
*	Precondiciones: Sea un nivel valido (1,2,3,4) y un camino valido.
*	Postcondiciones: Pondra los enanos en donde el usuario lo decida, siempre y cuando sea posible.
*/
void poner_enanos(juego_t *juego, int tope){
	int enanos_disponibles = tope;
	int num_defensor = 0;
	int inicial = 0;

	if((juego -> nivel_actual == 3) || (juego -> nivel_actual == 4)){
		inicial = tope;
		tope += tope;
	}

	for(int i = inicial; i < tope; i++){
		mostrar_juego(*juego);
		printf(""AMARILLO" -> Tenes disponibles %i enanos. ¿Donde queres ubicarlos?\n"VERDE, enanos_disponibles);
		printf(""AMARILLO" -> Posicion enano Nº%i (Escribe fila): "VERDE"",num_defensor+1);
		scanf("%i", &(juego -> nivel.defensores[i].posicion.fil));
		printf(""AMARILLO" -> Posicion enano Nº%i (Escribe columna): "VERDE"",num_defensor+1);
		scanf("%i", &(juego -> nivel.defensores[i].posicion.col));
		int estado_defensor = -1;
		if(esta_dentro_del_tablero(*juego,juego -> nivel.defensores[i].posicion)){
			estado_defensor = agregar_defensor(&(juego -> nivel), juego -> nivel.defensores[i].posicion, ENANOS);;
		}
		while(estado_defensor == -1){
			printf(""AMARILLO" -> Esa posicion no es valida"VERDE"\n");
			printf(""AMARILLO" -> Posicion enano Nº%i (Escribe fila): "VERDE"",num_defensor+1);
			scanf("%i", &(juego -> nivel.defensores[i].posicion.fil));
			printf(""AMARILLO" -> Posicion enano Nº%i (Escribe columna): "VERDE"",num_defensor+1);
			scanf("%i", &(juego -> nivel.defensores[i].posicion.col));
			if(esta_dentro_del_tablero(*juego,juego -> nivel.defensores[i].posicion)){
				estado_defensor = agregar_defensor(&(juego -> nivel), juego -> nivel.defensores[i].posicion, ENANOS);;
			}
		}
		enanos_disponibles --;
		num_defensor ++;
		system("clear");
	}
}

/*
*	Precondiciones: Sea un nivel valido (1,2,3,4) y un camino valido.
*	Postcondiciones: Pondra los elfos en donde el usuario lo decida, siempre y cuando sea posible.
*/
void poner_elfos(juego_t *juego,int tope){
	int elfos_disponibles = tope;
	for(int i = 0; i < tope; i++){
		mostrar_juego(*juego);
		printf(""AMARILLO" -> Tenes disponibles %i elfos. ¿Donde queres ubicarlos?\n"VERDE"", elfos_disponibles);
		printf(""AMARILLO" -> Posicion elfo Nº%i (Escribe fila): "VERDE"",i+1);
		scanf("%i", &(juego -> nivel.defensores[i].posicion.fil));
		printf(""AMARILLO" -> Posicion elfo Nº%i (Escribe columna): "VERDE"",i+1);
		scanf("%i", &(juego -> nivel.defensores[i].posicion.col));
		int estado_defensor = -1;
		if(esta_dentro_del_tablero(*juego,juego -> nivel.defensores[i].posicion)){
			estado_defensor = agregar_defensor(&(juego -> nivel), juego -> nivel.defensores[i].posicion, ELFOS);;
		}
		while(estado_defensor == -1){
			printf(""AMARILLO" -> Esa posicion no es valida\n");
			printf(""AMARILLO" -> Posicion elfo Nº%i (Escribe fila): "VERDE"",i+1);
			scanf("%i", &(juego -> nivel.defensores[i].posicion.fil));
			printf(""AMARILLO" -> Posicion elfo Nº%i (Escribe columna): "VERDE"",i+1);
			scanf("%i", &(juego -> nivel.defensores[i].posicion.col));
			if(esta_dentro_del_tablero(*juego,juego -> nivel.defensores[i].posicion)){
				estado_defensor = agregar_defensor(&(juego -> nivel), juego -> nivel.defensores[i].posicion, ELFOS);;
			}
		}
		elfos_disponibles --;
		system("clear");
		}
}

/*
*	Precondiciones: Sea un nivel valido (1,2,3,4) y un camino valido.
*	Postcondiciones: Pondra los defensores en donde el usuario lo decida, siempre y cuando sea posible.
*/
void poner_defensores(juego_t *juego){
	system("clear");
	juego -> nivel.tope_defensores = 0;
	if(juego -> nivel_actual == NIVEL_1){
		poner_enanos(juego,CANT_DEFENSORES_1);
	}else if(juego -> nivel_actual == NIVEL_2){
		poner_elfos(juego,CANT_DEFENSORES_2);
	}else if(juego -> nivel_actual == NIVEL_3){
		poner_elfos(juego,CANT_DEFENSORES_3);
		poner_enanos(juego,CANT_DEFENSORES_3);
	}else{
		poner_elfos(juego,CANT_DEFENSORES_4);
		poner_enanos(juego,CANT_DEFENSORES_4);
	}
}

/*
*	Precondiciones: Debe recibir un juego con un nivel valido (1,2,3,4).
*	Postcondiciones: Modificara el maximo de enemigos segun el nivel correspondiente e inicializara el tope de enemigos a 0.
*/
void inicializar_enemigos(juego_t *juego){
	if(juego -> nivel_actual == NIVEL_1){
		juego -> nivel.max_enemigos_nivel = ENEMIGOS_NV_1;
	}else if(juego -> nivel_actual == NIVEL_2){
		juego -> nivel.max_enemigos_nivel = ENEMIGOS_NV_2;
	}else if(juego -> nivel_actual == NIVEL_3){
		juego -> nivel.max_enemigos_nivel = ENEMIGOS_NV_3;
	}else if(juego -> nivel_actual == NIVEL_4){
		juego -> nivel.max_enemigos_nivel = ENEMIGOS_NV_4;
	}

	juego -> nivel.tope_enemigos = 0;
}

/*
*	Precondiciones: Debe recibir un juego con un nivel valido (1,2,3,4).
*	Postcondiciones: Iniciara el nivel correspondiente.
*/
void iniciar_nivel(juego_t *juego){
	mostrar_introduccion_nivel(juego -> nivel_actual);
	crear_caminos(juego);
	poner_defensores(juego);
	inicializar_enemigos(juego);
}

/*************************************************************************************** Poner nuevo defensor ****************************************************************************************/

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas.
*	Postcondiciones: Devolvera true si se llegó a la cantidad indicada para poner un nuevo defensor, y false si no se llegó.
*/
bool es_posible_poner_nuevo_defensor(juego_t juego){
	bool es_posible = false;
	int cada_cuanto_def_extra = 0;
	if(juego.nivel_actual == NIVEL_1){
		cada_cuanto_def_extra = 25;
	}else{
		cada_cuanto_def_extra = 50;
	}

	if(((juego.nivel.tope_enemigos % cada_cuanto_def_extra) == 0) && (juego.nivel.tope_enemigos != 0) && (juego.nivel.tope_enemigos != juego.nivel.max_enemigos_nivel) &&
			( (juego.nivel_actual == NIVEL_1 && juego.torres.enanos_extra > 0) || (juego.nivel_actual == NIVEL_2 && juego.torres.elfos_extra > 0) ||
			( (juego.nivel_actual == NIVEL_3 || juego.nivel_actual == NIVEL_4) && (juego.torres.elfos_extra > 0 || juego.torres.enanos_extra > 0)) )){
			es_posible = true;
	}

	return es_posible;
}

/*
*	Postcondiciones: Devolvera true si la opcion elegida es Si(S) o No(N), y false en el caso contrario.
*/
bool es_eleccion_valida_si_no(char opcion_elegida){

	return(opcion_elegida == SI || opcion_elegida == NO);
}

/*
*	Postcondiciones: Devolvera true si la opcion elegida es Enano(G) o ELfo(L), y false en el caso contrario.
*/
bool es_eleccion_valida_tipo_def(char tipo_defensor){

	return (tipo_defensor == ENANOS || tipo_defensor == ELFOS);
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas.
*	Postcondiciones: Devolvera el tipo de defensor que se quiere crear si es que el usuario lo desea. Y modificara quiere_defensor a true si el usuario
*	quiere poner un defensor, y a no en el caso contrario.
*/
void preguntar_si_quiere_defensor(juego_t juego, bool *quiere_defensor,char *tipo_defensor){
	char opcion_elegida = NO;
	if(juego.nivel_actual == NIVEL_1){
		printf(""AMARILLO" -> Tenes disponible un enano extra para ubicar, esto te costara 50 puntos de resistencia a la Torre 1 "VERDE"\n");
		printf(""AMARILLO" -> Quieres poner un enano extra? Si(Y) No(N): ");
	}else if(juego.nivel_actual == NIVEL_2){
		printf(""AMARILLO" -> Tenes disponible un elfo extra para ubicar, esto te costara 50 puntos de resistencia a la Torre 2 "VERDE"\n");
		printf(""AMARILLO" -> Quieres poner un elfo extra? Si(Y) No(N): ");
	}else{
		if(juego.torres.enanos_extra > 0 && juego.torres.elfos_extra > 0){
			printf(""AMARILLO" -> Tenes disponible un enano o un elfo extra para ubicar, esto te costara 50 puntos de resistencia a la torre 1 o 2 respectivamente"VERDE"\n");
			printf(""AMARILLO" -> Quieres poner un defensor extra? Si(Y) No(N): "VERDE"");
		}else if(juego.torres.enanos_extra > 0){
			printf(""AMARILLO" -> Tenes disponible un enano extra para ubicar, esto te costara 50 puntos de resistencia a la Torre 1 "VERDE"\n");
			printf(""AMARILLO" -> Quieres poner un enano extra? Si(Y) No(N): ");
		}else{
			printf(""AMARILLO" -> Tenes disponible un elfo extra para ubicar, esto te costara 50 puntos de resistencia a la Torre 2 "VERDE"\n");
			printf(""AMARILLO" -> Quieres poner un elfo extra? Si(Y) No(N): ");
		}
	}
	scanf(" %c",&opcion_elegida);
	while(!es_eleccion_valida_si_no(opcion_elegida)){
		printf(""AMARILLO" -> Esa opcion no es valida, elige otra Si(Y) No(N): "VERDE"");
		scanf(" %c",&opcion_elegida);
	}
	if(opcion_elegida == SI){
		*quiere_defensor = true;
		if(juego.nivel_actual == NIVEL_1){
			*tipo_defensor = ENANOS;
		}else if(juego.nivel_actual == NIVEL_2){
			*tipo_defensor = ELFOS;
		}else if(juego.nivel_actual == NIVEL_3 || juego.nivel_actual == NIVEL_4){
			if(juego.torres.enanos_extra > 0 && juego.torres.elfos_extra > 0){
				printf(""AMARILLO" -> Quieres un enano o un elfo extra?: Enano(%c) Elfo(%c): "VERDE"",ENANOS,ELFOS);
				scanf(" %c", tipo_defensor);
				while(!es_eleccion_valida_tipo_def(*tipo_defensor)){
					printf(""AMARILLO" -> Esa opcion no es valida, elige otra: Enano(%c) Elfo(%c): "VERDE"",ENANOS,ELFOS);
					scanf(" %c", tipo_defensor);
				}
			}else if(juego.torres.enanos_extra > 0){
				*tipo_defensor = ENANOS;
			}else{
				*tipo_defensor = ELFOS;
			}
		}
	}
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas y un tipo de defensor valido (Enano o Elfo).
*	Postcondiciones: Descontara la resistencia que ocasiona crear un defensor nuevo a la torre 1 o 2 segun corresponda.
*/
void descontar_resistencia_torres(juego_t *juego, char tipo_defensor){
	if(tipo_defensor == ENANOS){
		juego -> torres.resistencia_torre_1 -= COSTO_DEF_EXTRA;
	}else{
		juego -> torres.resistencia_torre_2 -= COSTO_DEF_EXTRA;
	}
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas y un tipo de defensor valido (Enano o Elfo).
*	Postcondiciones: Descontara en 1 a los enanos extra disponibles o a los enanos extra disponibles segun corresponda.
*/
void descontar_un_defensor_extra(juego_t *juego, char tipo_defensor){
	if(tipo_defensor == ENANOS){
		(juego -> torres.enanos_extra) --;
	}else{
		(juego -> torres.elfos_extra) --;
	}
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas.
*	Postcondiciones: Devolvera la posicion valida en donde el usuario quiere ubicar su defensor extra.
*/
void preguntar_donde_poner_defensor(juego_t juego, coordenada_t *pos_defensor){
	printf(""AMARILLO" -> En que fila queres poner el nuevo defensor? "VERDE"");
	scanf(" %i",&(pos_defensor -> fil));
	printf(""AMARILLO" -> En que columna queres poner el nuevo defensor? "VERDE"");
	scanf(" %i",&(pos_defensor -> col));
	while(!esta_dentro_del_tablero(juego, *pos_defensor)){
		printf(""AMARILLO" -> Esa posicion esta fuera del tablero, elige otra\n");
		printf(""AMARILLO" -> En que fila queres poner el nuevo defensor? "VERDE"");
		scanf(" %i",&(pos_defensor -> fil));
		printf(""AMARILLO" -> En que columna queres poner el nuevo defensor? "VERDE"");
		scanf(" %i",&(pos_defensor -> col));
	}
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas.
*	Postcondiciones: Ubicara un nuevo defensor si el usuario lo quiere.
*/
void poner_nuevo_defensor(juego_t *juego){
	if(es_posible_poner_nuevo_defensor(*juego)){
		bool quiere_defensor;
		char tipo_defensor;
		preguntar_si_quiere_defensor(*juego, &quiere_defensor, &tipo_defensor);
		if(quiere_defensor){
			coordenada_t pos_defensor;
			preguntar_donde_poner_defensor(*juego, &pos_defensor);
			int estado_defensor = agregar_defensor(&(juego -> nivel),pos_defensor,tipo_defensor);
			while(estado_defensor == -1){
				printf(""AMARILLO"No es posible poner un defensor ahi\n");
				preguntar_donde_poner_defensor(*juego, &pos_defensor);
				estado_defensor = agregar_defensor(&(juego -> nivel),pos_defensor,tipo_defensor);
			}
			descontar_resistencia_torres(juego, tipo_defensor);
			descontar_un_defensor_extra(juego, tipo_defensor);
		}
	}
}

/************************************************************************************* Pasar al siguiente nivel **************************************************************************************/

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas.
*	Postcondiciones: Pasara al siguiente nivel con todos sus valores inicializados.
*/
void pasar_al_siguiente_nivel(juego_t *juego){
	(juego -> nivel_actual) ++;
	iniciar_nivel(juego);
	mostrar_juego(*juego);
}

/****************************************************************************************** Finalizar juego ******************************************************************************************/

/*
*	Postcondiciones: Mostrara la pantalla final con el mensaje de que se ganó el juego.
*/
void mostrar_que_gano(){
	system("clear");
	printf("   "MARRON"***\n");
	printf("  "MARRON"*****\n");
	printf("  "MARRON"*****\n");
	printf("   "MARRON"***\n");
	printf("   "MARRON":::"AMARILLO"\\  .,,,,,,,..\n");
	printf("   "MARRON":::"AMARILLO" \\;;;;;;;;;;;;;;,.            ..,,;;;;;;;;;;;,.         .   \n");
	printf("   "MARRON":::  "AMARILLO";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;,      ,;,   \n");
	printf("   "MARRON":::  "AMARILLO";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;,,,,;;;'   \n");
	printf("   "MARRON":::  "AMARILLO";;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;"BLANCO"####"AMARILLO";;;;;;;;;;;;;;;"BLANCO"#####"AMARILLO";;"BLANCO"#"AMARILLO";;;;;;;;;;;;;;;;'   \n");
	printf("   "MARRON":::  "AMARILLO";;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#####"AMARILLO";:"BLANCO"####"AMARILLO";;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;"BLANCO"##"AMARILLO":;;;;;;;;;'    \n");
	printf("   "MARRON":::  "AMARILLO";;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;;;;;;"BLANCO"#"AMARILLO";;;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;"BLANCO"#"AMARILLO";;"BLANCO"#"AMARILLO";;;;;;;;'     \n");
	printf("   "MARRON":::  "AMARILLO";;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;;;;;;"BLANCO"#"AMARILLO";;;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#####"AMARILLO";;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";;;;;;'      \n");
	printf("   "MARRON":::  "AMARILLO";;;"BLANCO"#"AMARILLO";;"BLANCO"#"AMARILLO";;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";;;"BLANCO"#"AMARILLO";;;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;"BLANCO"#"AMARILLO";;"BLANCO"#"AMARILLO";"BLANCO"######"AMARILLO";;;;;'       \n");
	printf("   "MARRON":::  "AMARILLO";;;;"BLANCO"##"AMARILLO";;;"BLANCO"#"AMARILLO";;"BLANCO"####"AMARILLO";;;;"BLANCO"#"AMARILLO";;;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";;;;'        \n");
	printf("   "MARRON":::  "AMARILLO";;;;;;;;;;;;;;;;;;;;"BLANCO"#"AMARILLO";;;;"BLANCO"####"AMARILLO";;;;;;;;;;;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";;;'         \n");
	printf("   "MARRON":::  "AMARILLO";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'          \n");
	printf("   "MARRON":::  "AMARILLO";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'           \n");
	printf("   "MARRON":::"AMARILLO" /''';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;            \n");
	printf("   "MARRON":::"AMARILLO"/        '''::;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;            \n");
	printf("   "MARRON":::                 "AMARILLO"'\"\"\"\"\"\";;;;;;;;;;;;;;\"\"\"\"\"\"';;;;            \n");
	printf("   "MARRON":::                                             "AMARILLO":;;'\n");
	printf("   "MARRON":::                                             "AMARILLO";;'\n");
	printf("   "MARRON":::                                             "AMARILLO";'\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf(" "MARRON"/:::::\\\n");
	printf(" "MARRON":::::::\n");
	printf(" "MARRON"=======\n");
}

/*
*	Postcondiciones: Mostrara la pantalla final con el mensaje de que se perdió el juego.
*/
void mostrar_que_perdio(){
	system("clear");
	printf("   "MARRON"***\n");
	printf("  "MARRON"*****\n");
	printf("  "MARRON"*****\n");
	printf("   "MARRON"***\n");
	printf("   "MARRON":::"BLANCO"\\  .,,,,,,,..\n");
	printf("   "MARRON":::"BLANCO" \\;;;;;;;;;;;;;;,.            ..,,;;;;;;;;;;;,.         .   \n");
	printf("   "MARRON":::  "BLANCO";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;,      ,;,   \n");
	printf("   "MARRON":::  "BLANCO";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;,,,,;;;'   \n");
	printf("   "MARRON":::  "BLANCO";"AMARILLO"#####"BLANCO";;"AMARILLO"######"BLANCO";;;;;;;;;;;;;;;;"AMARILLO"####"BLANCO";;"AMARILLO"#####"BLANCO";;;;;;;;;;;;;;'   \n");
	printf("   "MARRON":::  "BLANCO";"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";"AMARILLO"#"BLANCO";;;;;;"AMARILLO"#####"BLANCO";;"AMARILLO"#####"BLANCO";;"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";;;"AMARILLO"#"BLANCO";;;;;"AMARILLO"##"BLANCO";;;;;;;;'    \n");
	printf("   "MARRON":::  "BLANCO";"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";"AMARILLO"#####"BLANCO";;"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";;;"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";;"AMARILLO"#"BLANCO":;;;;;'     \n");
	printf("   "MARRON":::  "BLANCO";"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";"AMARILLO"#"BLANCO";;;;;;"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";;;"AMARILLO"#"BLANCO";;;"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";;;;'      \n");
	printf("   "MARRON":::  "BLANCO";"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";"AMARILLO"#"BLANCO";;;;;;"AMARILLO"#####"BLANCO";;"AMARILLO"#####"BLANCO";;"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";;;"AMARILLO"#"BLANCO";;;"AMARILLO"######"BLANCO";;;'       \n");
	printf("   "MARRON":::  "BLANCO";"AMARILLO"#####"BLANCO";;"AMARILLO"######"BLANCO" "AMARILLO"#"BLANCO";;;"AMARILLO"#"BLANCO";;"AMARILLO"#"BLANCO";;;"AMARILLO"#"BLANCO";;;"AMARILLO"####"BLANCO";;;;"AMARILLO"#"BLANCO";;;"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";;'        \n");
	printf("   "MARRON":::  "BLANCO";;;;;;;;;;;;;;;"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";;;;;;;;;;;;;;"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";'         \n");
	printf("   "MARRON":::  "BLANCO";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'          \n");
	printf("   "MARRON":::  "BLANCO";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'           \n");
	printf("   "MARRON":::"BLANCO" /''';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;            \n");
	printf("   "MARRON":::"BLANCO"/        '''::;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;            \n");
	printf("   "MARRON":::                 "BLANCO"'\"\"\"\"\"\";;;;;;;;;;;;;;\"\"\"\"\"\"';;;;            \n");
	printf("   "MARRON":::                                             "BLANCO":;;'\n");
	printf("   "MARRON":::                                             "BLANCO";;'\n");
	printf("   "MARRON":::                                             "BLANCO";'\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf(" "MARRON"/:::::\\\n");
	printf(" "MARRON":::::::\n");
	printf(" "MARRON"=======\n");
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas.
*	Postcondiciones: Mostrara si la pantalla final de victoria o derrota segun el caso.
*/
void finalizar_juego(juego_t juego){
	if(estado_juego(juego) == 1){
		mostrar_que_gano();
	}else{
		mostrar_que_perdio();
	}
}

/************************************************************************************************ Main ***********************************************************************************************/

int main(){
	srand ((unsigned)time(NULL));
	int viento;
	int humedad;
	char animo_legolas;
	char animo_gimli;
	juego_t juego;
	float velocidad_de_juego = 0.75;
	int estado_menu;
	menu_principal(&estado_menu);
	while(estado_menu != 0 && estado_menu != 2){
		cambiar_velocidad_de_juego(&velocidad_de_juego);
		menu_principal(&estado_menu);
	}
	if(estado_menu == 0){
		mostrar_dibujo_portada();
		animos(&viento,&humedad,&animo_legolas,&animo_gimli);
		inicializar_juego(&juego, viento, humedad, animo_legolas,animo_gimli);
		iniciar_nivel(&juego);
		mostrar_juego(juego);
		while (estado_juego(juego) == 0){
			if(estado_nivel(juego.nivel) == 1){
				pasar_al_siguiente_nivel(&juego);
			}else if(estado_nivel(juego.nivel) == 0){
				jugar_turno(&juego);
				mostrar_juego(juego);
				poner_nuevo_defensor(&juego);
				detener_el_tiempo(velocidad_de_juego);
			}
		}
		finalizar_juego(juego);
	}
}

/*****************************************************************************************************************************************************************************************************/
