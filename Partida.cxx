#include "Partida.h"
#include <iostream>
#include <limits>

std::vector<std::vector<char>> Partida::getMapa() {
	return this->mapa;
}

void Partida::setMapa(TipoMapa mapa) {
	this->mapa = mapa;
}

void Partida::inicializarMapa() {
	for (int i = 0; i < 3; i++) {
		std::vector<char> temp;
		mapa.push_back(temp);
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mapa[j].push_back(' ');
		}
	}
}

char Partida::getTurno() {
	return this->turno;
}

void Partida::setTurno(char turno) {
	this->turno = turno;
}

char Partida::getTurnoJugador() {
	return turnoJugador;
}

void Partida::setTurnoJugador(char turnoJugador) {
	this->turnoJugador = turnoJugador;
}

TipoMapa Partida::generarArbol() {
	ArbolGeneral< MapaHeuristica> arbol;
	NodoGeneral< MapaHeuristica>* raiz = new NodoGeneral<MapaHeuristica>;
	MapaHeuristica mapaRaiz = std::make_pair(mapa, 0);
	raiz->fijarDato(mapaRaiz);
	generarDescendientesJugada(raiz, turno);
	std::list< NodoGeneral<MapaHeuristica>*> desc = raiz->obtenerDesc();
	std::list< NodoGeneral<MapaHeuristica>*>::iterator it = desc.begin();
	if (turno == 'X') {
		for (; it != desc.end(); it++) {
			if (ganador((*it)->obtenerDato().first) == ' ') {
				generarDescendientesJugada(*it, 'O');
			}
		}
	}
	else {
		for (; it != desc.end(); it++) {
			if (ganador((*it)->obtenerDato().first) == ' ') {
				generarDescendientesJugada(*it, 'X');
			}
		}
	}
	arbol.fijarRaiz(raiz);
	if (turnoJugador == 'X') {
		return calcularMinMax(arbol);
	}
	else {
		return calcularMaxMin(arbol);
	}
}

char Partida::ganador(TipoMapa mapa) {
	int cantidadLlenos = 0;
	char ganadorHorizontal = revisarHorizontales(cantidadLlenos, mapa);
	if (ganadorHorizontal != ' ') {
		return ganadorHorizontal;
	}
	char ganadorVertical = revisarVerticales(mapa);
	if (ganadorVertical != ' ') {
		return ganadorVertical;
	}
	char ganadorDiagonal = revisarDiagonales(mapa);
	if (ganadorDiagonal != ' ') {
		return ganadorDiagonal;
	}
	if (cantidadLlenos == 9) {
		return 'E';
	}
	return ' ';
}

char Partida::revisarHorizontales(int& cantidadLlenos, TipoMapa mapa) {
	int cantidadTurno = 0;
	for (int i = 0; i < 3; i++) {
		cantidadTurno = 0;
		for (int j = 0; j < 3; j++) {
			if (mapa[i][j] == turno) {
				cantidadTurno++;
			}
			if (mapa[i][j] != ' ') {
				cantidadLlenos++;
			}
		}
		if (cantidadTurno == 3) {
			return turno;
		}
	}
	return ' ';
}

char Partida::revisarVerticales(TipoMapa mapa) {
	int cantidadTurno = 0;
	for (int i = 0; i < 3; i++) {
		cantidadTurno = 0;
		for (int j = 0; j < 3; j++) {
			if (mapa[j][i] == turno) {
				cantidadTurno++;
			}
		}
		if (cantidadTurno == 3) {
			return turno;
		}
	}
	return ' ';
}

char Partida::revisarDiagonales(TipoMapa mapa) {
	int cantidadTurno = 0;
	for (int i = 0; i < 3; i++) {
		if (mapa[i][i] == turno) {
			cantidadTurno++;
		}
		if (cantidadTurno == 3) {
			return turno;
		}
	}
	cantidadTurno = 0;
	for (int i = 0; i < 3; i++) {
		if (mapa[i][2 - i] == turno) {
			cantidadTurno++;
		}
		if (cantidadTurno == 3) {
			return turno;
		}
	}
	return ' ';
}

void Partida::generarDescendientesJugada(NodoGeneral< MapaHeuristica>* nodoMapa,
	char turno) {
	std::vector<TipoMapa> jugadasPosibles;
	MapaHeuristica heuristicaMapaActual = nodoMapa->obtenerDato();
	TipoMapa mapaActual = heuristicaMapaActual.first;
	TipoMapa mapaTemp = mapaActual;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (mapaActual[i][j] == ' ') {
				mapaTemp[i][j] = turno;
				jugadasPosibles.push_back(mapaTemp);
				mapaTemp = mapaActual;
			}
			else if (mapaActual[i][j] == turno) {
				revisarMovimientosPosibles(i, j, mapaTemp, jugadasPosibles, mapaActual,turno);
			}
		}
	}
	agregarHijosJugadas(nodoMapa, jugadasPosibles);
}

void Partida::revisarMovimientosPosibles(int i, int j, TipoMapa& mapaTemp,
										 std::vector<TipoMapa>& jugadasPosibles,
	TipoMapa mapa, char turno) {
	if (i - 1 >= 0) {
		if (mapa[i - 1][j] == ' ') {
			mapaTemp[i - 1][j] = turno;
			agregarJugadaPosible(mapaTemp, jugadasPosibles, i, j, mapa);
		}
	}
	if (i + 1 <= 2) {
		if (mapa[i + 1][j] == ' ') {
			mapaTemp[i + 1][j] = turno;
			agregarJugadaPosible(mapaTemp, jugadasPosibles, i, j, mapa);
		}
	}
	if (j - 1 >= 0) {
		if (mapa[i][j - 1] == ' ') {
			mapaTemp[i][j - 1] = turno;
			agregarJugadaPosible(mapaTemp, jugadasPosibles, i, j, mapa);
		}
	}
	if (j + 1 <= 2) {
		if (mapa[i][j + 1] == ' ') {
			mapaTemp[i][j + 1] = turno;
			agregarJugadaPosible(mapaTemp, jugadasPosibles, i, j, mapa);
		}
	}
}

void Partida::agregarJugadaPosible(TipoMapa& mapaTemp,
								   std::vector<TipoMapa>& jugadasPosibles, int i, int j,
	TipoMapa mapa) {
	mapaTemp[i][j] = ' ';
	jugadasPosibles.push_back(mapaTemp);
	mapaTemp = mapa;
}

void Partida::agregarHijosJugadas(NodoGeneral< MapaHeuristica>* raiz,
								  std::vector<TipoMapa>& jugadasPosibles) {
	for (int i = 0; i < jugadasPosibles.size(); i++) {
		MapaHeuristica hijoActual = std::make_pair(jugadasPosibles[i], calcularHeuristica(jugadasPosibles[i]));
		raiz->adicionarDesc(hijoActual);
	}
}

int Partida::calcularHeuristica(TipoMapa mapa) {
	return heuristicaHorizontalYEstrategica(mapa) + heuristicaVertical(mapa) + heuristicaDiagonal(mapa);
}

int Partida::heuristicaHorizontalYEstrategica(TipoMapa mapa) {
	int cantidadTriosO = 0, cantidadTriosX = 0, cantidadEstrategicasO = 0, cantidadEstrategicasX = 0,
		cantidadVaciasO = 0, cantidadVaciasX = 0, ganarO = 0, ganarX = 0;
	int cantidadX = 0, cantidadO = 0, cantidadVacio = 0;
	for (int i = 0; i < 3; i++) {
		cantidadX = cantidadO = cantidadVacio = 0; //Inicializa las variables en 0
		for (int j = 0; j < 3; j++) {
			if (mapa[i][j] == 'X') {
				cantidadX++;
			}
			else if (mapa[i][j] == 'O') {
				cantidadO++;
			}
			else {
				cantidadVacio++;
			}
			calcularIndicadoresEstrategicos(i, j, mapa, cantidadEstrategicasX, cantidadEstrategicasO);
		}
		calcularIndicadores(cantidadX, cantidadVacio, cantidadTriosX, cantidadO, cantidadTriosO,
			cantidadVaciasX, cantidadVaciasO, ganarX, ganarO);
	}
	return (cantidadTriosO * CANTTRIOSO) + (cantidadTriosX * CANTTRIOSX) + (cantidadEstrategicasO * CANTESTO) +
		(cantidadEstrategicasX * CANTESTX) + (cantidadVaciasO * CANTVACO) + (cantidadVaciasX * CANTVACX) +
		(ganarO * GANAX) + (ganarX * GANAO);
}

void Partida::calcularIndicadoresEstrategicos(int i, int j, TipoMapa mapa, int& cantidadEstrategicasX,
	int& cantidadEstrategicasO) {
	if ((i + j) % 2 == 0) {
		if (mapa[i][j] == 'X') {
			cantidadEstrategicasX++;
		}
		else if (mapa[i][j] == 'O') {
			cantidadEstrategicasO++;
		}
	}
}

void Partida::calcularIndicadores(int cantidadX, int cantidadVacio, int& cantidadTriosX, int cantidadO, 
	int& cantidadTriosO, int& cantidadVaciasX, int& cantidadVaciasO, int& ganarX, int& ganarO) {
	if (cantidadX == 2 && cantidadVacio == 1) {
		cantidadTriosX++;
	}
	else if (cantidadO == 2 && cantidadVacio == 1) {
		cantidadTriosO++;
	}
	else if (cantidadX == 1 && cantidadVacio == 2) {
		cantidadVaciasX++;
	}
	else if (cantidadO == 1 && cantidadVacio == 2) {
		cantidadVaciasO++;
	}
	else if (cantidadX == 3) {
		ganarX++;
	}
	else if (cantidadO == 3) {
		ganarO++;
	}
}

int Partida::heuristicaVertical(TipoMapa mapa) {
	int cantidadTriosO = 0, cantidadTriosX = 0, cantidadEstrategicasO = 0, cantidadEstrategicasX = 0,
		cantidadVaciasO = 0, cantidadVaciasX = 0, ganarO = 0, ganarX = 0;
	int cantidadX = 0, cantidadO = 0, cantidadVacio = 0;
	for (int i = 0; i < 3; i++) {
		cantidadX = cantidadO = cantidadVacio = 0; //Inicializa las variables en 0
		for (int j = 0; j < 3; j++) {
			if (mapa[j][i] == 'X') {
				cantidadX++;
			}
			else if (mapa[j][i] == 'O') {
				cantidadO++;
			}
			else {
				cantidadVacio++;
			}
		}
		calcularIndicadores(cantidadX, cantidadVacio, cantidadTriosX, cantidadO, cantidadTriosO,
			cantidadVaciasX, cantidadVaciasO, ganarX, ganarO);
	}
	return (cantidadTriosO * CANTTRIOSO) + (cantidadTriosX * CANTTRIOSX) + (cantidadEstrategicasO * CANTESTO) +
		(cantidadEstrategicasX * CANTESTX) + (cantidadVaciasO * CANTVACO) + (cantidadVaciasX * CANTVACX) +
		(ganarO * GANAX) + (ganarX * GANAO);
}


int Partida::heuristicaDiagonal(TipoMapa mapa) {
	int cantidadTriosO = 0, cantidadTriosX = 0, cantidadEstrategicasO = 0, cantidadEstrategicasX = 0,
		cantidadVaciasO = 0, cantidadVaciasX = 0, ganarO = 0, ganarX = 0;
	int cantidadX = 0, cantidadO = 0, cantidadVacio = 0;
	for (int i = 0; i < 3; i++) { //Diagonal
		if (mapa[i][i] == 'X') {
			cantidadX++;
		}
		else if (mapa[i][i] == 'O') {
			cantidadO++;
		}
		else {
			cantidadVacio++;
		}
		calcularIndicadores(cantidadX, cantidadVacio, cantidadTriosX, cantidadO, cantidadTriosO,
			cantidadVaciasX, cantidadVaciasO, ganarX, ganarO);
	}
	cantidadX = cantidadO = cantidadVacio = 0; //Inicializa las variables en 0
	for (int i = 0; i < 3; i++) { //Diagonal inversa
		if (mapa[i][2-i] == 'X') {
			cantidadX++;
		}
		else if (mapa[i][2-i] == 'O') {
			cantidadO++;
		}
		else {
			cantidadVacio++;
		}
		calcularIndicadores(cantidadX, cantidadVacio, cantidadTriosX, cantidadO, cantidadTriosO,
			cantidadVaciasX, cantidadVaciasO, ganarX, ganarO);
	}
	return (cantidadTriosO * CANTTRIOSO) + (cantidadTriosX * CANTTRIOSX) + (cantidadEstrategicasO * CANTESTO) +
		(cantidadEstrategicasX * CANTESTX) + (cantidadVaciasO * CANTVACO) + (cantidadVaciasX * CANTVACX) +
		(ganarO * GANAX) + (ganarX * GANAO);
}

TipoMapa Partida::calcularMinMax(ArbolGeneral<MapaHeuristica> arbol) {
	std::list< NodoGeneral<MapaHeuristica>*> desc = arbol.obtenerRaiz()->obtenerDesc();
	std::list< NodoGeneral<MapaHeuristica>*>::iterator it = desc.begin();
	std::vector<int> heuristicasMinNietos;
	for (; it != desc.end(); it++) {
		std::list< NodoGeneral<MapaHeuristica>*> descIt = (*it)->obtenerDesc();
		std::list< NodoGeneral<MapaHeuristica>*>::iterator jt = descIt.begin();
		int heuristicaMinima = std::numeric_limits<int>::max();
		for (; jt != descIt.end(); jt++) {
			if ((*jt)->obtenerDato().second < heuristicaMinima) {
				heuristicaMinima = (*jt)->obtenerDato().second;
			}
		}
		if (heuristicaMinima == std::numeric_limits<int>::max()) { //Si no tiene nietos (gana o empata)
			heuristicaMinima = (*it)->obtenerDato().second;
		}
		heuristicasMinNietos.push_back(heuristicaMinima);
	}
	int heuristicaMaxHijos = std::numeric_limits<int>::min();
	int i, posHijo = 0;
	for (i = 0; i < heuristicasMinNietos.size(); i++) {
		if (heuristicaMaxHijos < heuristicasMinNietos[i]) {
			heuristicaMaxHijos = heuristicasMinNietos[i];
			posHijo = i;
		}
	}
	it = desc.begin();
	std::advance(it, posHijo);
	return (*it)->obtenerDato().first;
}


TipoMapa Partida::calcularMaxMin(ArbolGeneral<MapaHeuristica> arbol) {
	std::list< NodoGeneral<MapaHeuristica>*> desc = arbol.obtenerRaiz()->obtenerDesc();
	std::list< NodoGeneral<MapaHeuristica>*>::iterator it = desc.begin();
	std::vector<int> heuristicasMaxNietos;
	for (; it != desc.end(); it++) {
		std::list< NodoGeneral<MapaHeuristica>*> descIt = (*it)->obtenerDesc();
		std::list< NodoGeneral<MapaHeuristica>*>::iterator jt = descIt.begin();
		int heuristicaMaximo = std::numeric_limits<int>::min();
		for (; jt != descIt.end(); jt++) {
			if ((*jt)->obtenerDato().second > heuristicaMaximo) {
				heuristicaMaximo = (*jt)->obtenerDato().second;
			}
		}
		if (heuristicaMaximo == std::numeric_limits<int>::min()) { //Si no tiene nietos (gana o empata)
			heuristicaMaximo = (*it)->obtenerDato().second;
		}
		heuristicasMaxNietos.push_back(heuristicaMaximo);
	}
	int heuristicaMinHijos = std::numeric_limits<int>::max();
	int i, posHijo = 0;
	for (i = 0; i < heuristicasMaxNietos.size(); i++) {
		if (heuristicaMinHijos > heuristicasMaxNietos[i]) {
			heuristicaMinHijos = heuristicasMaxNietos[i];
			posHijo = i;
		}
	}
	it = desc.begin();
	std::advance(it, posHijo);
	return (*it)->obtenerDato().first;
}

void Partida::imprimirMapa() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (j != 2) {
				std::cout << mapa[i][j] << " |";
			}
			if (j == 2) {
				std::cout << mapa[i][j] << std::endl;
			}
		}
		if (i != 2) {
			std::cout << "__ __ __\n";
		}
	}
	std::cout << "\n\n";
}

void Partida::imprimirMapa(TipoMapa mapa) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (j != 2) {
				std::cout << mapa[i][j] << " |";
			}
			if (j == 2) {
				std::cout << mapa[i][j] << std::endl;
			}
		}
		if (i != 2) {
			std::cout << "__ __ __\n";
		}
	}
	std::cout << "\n\n";
}