#ifndef _Partida_h_
#define _Partida_h_

#include <vector>
#include "ArbolGeneral.h"
#include "NodoGeneral.h"
#define CANTTRIOSO 5
#define CANTTRIOSX -5
#define CANTESTO 2
#define CANTESTX -2
#define CANTVACO 1
#define CANTVACX -1
#define GANAX 20
#define GANAO -20

typedef std::vector<std::vector<char>> TipoMapa;
typedef std::pair<TipoMapa, int> MapaHeuristica;

class Partida {
private:
	TipoMapa mapa;
	char turno = 'X';
	char turnoJugador;
	void revisarMovimientosPosibles(int i, int j, TipoMapa& mapaTemp,
		std::vector<TipoMapa>& jugadasPosibles,
		TipoMapa mapa, char turno);
	void agregarJugadaPosible(TipoMapa& mapaTemp,
		std::vector<TipoMapa>& jugadasPosibles, int i, int j,
		TipoMapa mapa);
	void agregarHijosJugadas(NodoGeneral< MapaHeuristica>* raiz,
		std::vector<TipoMapa>& jugadasPosibles);
	void generarDescendientesJugada(NodoGeneral< MapaHeuristica>* nodoMapa,
		char turno);
	int calcularHeuristica(TipoMapa mapa);
	int heuristicaHorizontalYEstrategica(TipoMapa mapa);
	int heuristicaVertical(TipoMapa mapa);
	void calcularIndicadoresEstrategicos(int i, int j, TipoMapa mapa, int& cantidadEstrategicasX,
		int& cantidadEstrategicasO);
	void calcularIndicadores(int cantidadX, int cantidadVacio, int& cantidadTriosX, int cantidadO,
		int& cantidadTriosO, int& cantidadVaciasX, int& cantidadVaciasO, int& ganarX, int& ganarO);
	int heuristicaDiagonal(TipoMapa mapa);
	TipoMapa calcularMinMax(ArbolGeneral<MapaHeuristica> arbol);
	TipoMapa calcularMaxMin(ArbolGeneral<MapaHeuristica> arbol);
	void imprimirMapa(TipoMapa mapa);
	char revisarHorizontales(int& cantidadLlenos, TipoMapa mapa);
	char revisarVerticales(TipoMapa map);
	char revisarDiagonales(TipoMapa map);
public:
	std::vector<std::vector<char>> getMapa();
	void setMapa(std::vector<std::vector<char>> mapa);
	void inicializarMapa();
	char getTurno();
	void setTurno(char turno);
	char getTurnoJugador();
	void setTurnoJugador(char turnoJugador);
	TipoMapa generarArbol();
	void imprimirMapa();
	char ganador(TipoMapa map);
};

#endif
