#include <iostream>
#include "Partida.h"
#include <cstdlib>

void turnos();
void jugadaIA();
void jugadaJugador();
void ponerFicha(std::vector<std::vector<char>>& mapa);
void moverFicha(std::vector<std::vector<char>>& mapa);
bool movimientoAdyacente(int filaDestino, int columnaDestino, int fila, int columna);
void turno(char turnoJugador, bool& fin);
bool puedeMover();
bool movimientoAdyacente(int i, int j);

Partida partida;

int main(){
	partida.inicializarMapa();
	turnos();
	system("pause");
	return 0;
}

void turnos() {
	bool fin = false;
	char turnoJugador = ' ';
	do {
		std::cout << "quiere ser X o O?: ";
		std::cin >> turnoJugador;
		turnoJugador = toupper(turnoJugador);
	} while (turnoJugador != 'O' && turnoJugador != 'X');
	partida.setTurnoJugador(turnoJugador);
	while (!fin) {
		turno(turnoJugador, fin);
	}
}

void turno(char turnoJugador, bool& fin) {
	if (turnoJugador != partida.getTurno()) {
		jugadaIA();
	}
	else {
		jugadaJugador();
	}
	char hayGanador = partida.ganador(partida.getMapa());
	if (hayGanador != ' ') {
		if (hayGanador == 'E') {
			std::cout << "\nLa partida ha quedado en EMPATE!!!\n";
		}
		else if (hayGanador == partida.getTurnoJugador()) {
			std::cout << "\nFelicidades, lo has conseguido, por fin, has derrotado a la PODEROSA IA, HAS GANADO!!!\n";
		}
		else {
			std::cout << "\nLa PODEROSA IA te ha ganado\n";
		}
		fin = true;
	}
	else if (partida.getTurno() == 'X') {
		partida.setTurno('O');
	}
	else {
		partida.setTurno('X');
	}
}

void jugadaIA() {
	std::vector<std::vector<char>> jugadaSiguiente = partida.generarArbol();
	partida.setMapa(jugadaSiguiente);
	std::cout << "La PODEROSA IA ha jugado!\n";
	partida.imprimirMapa();
}

void jugadaJugador() {
	char tipoMovimiento;
	std::vector<std::vector<char>> mapa = partida.getMapa();
	do {
		std::cout << "\nQuiere mover o quiere poner (M/P): ";
		std::cin >> tipoMovimiento;
		if (toupper(tipoMovimiento) == 'M') {
			if (!puedeMover()) {
				tipoMovimiento = 'Z';
				std::cout << "No puede mover fichas actualmente";
			}
		}
	} while (toupper(tipoMovimiento) != 'M' && toupper(tipoMovimiento) != 'P');
	if (toupper(tipoMovimiento) == 'P') {
		ponerFicha(mapa);
	}
	else {
		moverFicha(mapa);
	}
	partida.setMapa(mapa);
	partida.imprimirMapa();
}

bool puedeMover() {
	bool fichaExistente = false;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (partida.getMapa()[i][j] == partida.getTurno()) {
				fichaExistente = true;
				if (movimientoAdyacente(i, j)) {
					return true;
				}
			}
		}
	}
	return false;
}

bool movimientoAdyacente(int i, int j) {
	std::vector<std::vector<char>> mapa = partida.getMapa();
	if (i - 1 >= 0) {
		if (mapa[i - 1][j] == ' ') {
			return true;
		}
	}
	if (i + 1 <= 2) {
		if (mapa[i + 1][j] == ' ') {
			return true;
		}
	}
	if (j - 1 >= 0) {
		if (mapa[i][j - 1] == ' ') {
			return true;
		}
	}
	if (j + 1 <= 2) {
		if (mapa[i][j + 1] == ' ') {
			return true;
		}
	}
	return false;
}

void ponerFicha(std::vector<std::vector<char>>& mapa) {
	int fila, columna;
	bool movimientoValido = false;
	do {
		do {
			std::cout << "\nEscoja donde quiere jugar (fila columna) (1-3) (ej: 1 3): ";
			std::cin >> fila >> columna;
		} while (fila > 3 || fila < 1 || columna > 3 || columna < 1);
		fila--;
		columna--;
		mapa = partida.getMapa();
		if (mapa[fila][columna] == ' ') {
			mapa[fila][columna] = partida.getTurnoJugador();
			movimientoValido = true;
		}
	} while (!movimientoValido);
}

void moverFicha(std::vector<std::vector<char>>& mapa) {
	int fila, columna;
	bool fichaMovible = false;
	do {
		do {
			std::cout << "\nEscoja la ficha a mover (fila columna) (1-3) (ej: 1 3): ";
			std::cin >> fila >> columna;
		} while (fila > 3 || fila < 1 || columna > 3 || columna < 1);
		fila--;
		columna--;
		if (mapa[fila][columna] == partida.getTurnoJugador()) {
			fichaMovible = true;
		}
	} while (!fichaMovible);
	bool movimientoValido = false;
	int filaDestino, columnaDestino;
	do {
		do {
			std::cout << "\nEscoja el lugar a mover (fila columna) (1-3) (ej: 1 3): ";
			std::cin >> filaDestino >> columnaDestino;
		} while (filaDestino > 3 || filaDestino < 1 || columnaDestino > 3 || columnaDestino < 1);
		filaDestino--;
		columnaDestino--;
		if (mapa[filaDestino][columnaDestino] == ' ' && movimientoAdyacente(filaDestino, columnaDestino, fila, columna)) {
			movimientoValido = true;
			mapa[filaDestino][columnaDestino] = partida.getTurnoJugador();
			mapa[fila][columna] = ' ';
		}
	} while (!movimientoValido);
}

bool movimientoAdyacente(int filaDestino, int columnaDestino, int fila, int columna) {
	if (abs(filaDestino - fila) == 1 && columnaDestino == columna) {
		return true;
	}
	else if (abs(columnaDestino - columna) == 1 && filaDestino == fila) {
		return true;
	}
	return false;
}
