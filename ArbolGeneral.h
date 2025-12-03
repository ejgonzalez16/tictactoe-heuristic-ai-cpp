#ifndef __ArbolGeneral_h__
#define __ArbolGeneral_h__
#include "NodoGeneral.h"
#include <iostream>
#include <vector>
#include <string>

template<class T>
class ArbolGeneral {
protected:
	NodoGeneral<T>* raiz;
	bool insertarRecursion(NodoGeneral<T>* nodo, T& padre, T& n);
	bool eliminarRecursion(NodoGeneral<T>* nodo, T& n);
	bool buscarRecursion(NodoGeneral<T>* nodo, T& n);
	void tamanoRecursion(NodoGeneral<T>* nodo, unsigned int& tam);
	void preOrdenRecursion(NodoGeneral<T>* nodo);
	void posOrdenRecursion(NodoGeneral<T>* nodo);
	bool buscarCaminoRecursion(NodoGeneral<T>* nodo, std::string ruta, T val, std::string& rutaFinal);
public:
	ArbolGeneral();
	ArbolGeneral(T& val);
	~ArbolGeneral();
	bool esVacio();
	NodoGeneral<T>* obtenerRaiz();
	void fijarRaiz(NodoGeneral<T>* nraiz);
	bool insertarNodo(T& padre, T& n);
	bool eliminarNodo(T& n);
	bool buscar(T& n);
	int altura();
	unsigned int tamano();
	void preOrden();
	void posOrden();
	void nivelOrden();
	std::string buscarCamino(T val);
};
#include "ArbolGeneral.hxx"
#endif
