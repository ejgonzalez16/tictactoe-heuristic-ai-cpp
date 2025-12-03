#include "ArbolGeneral.h"
#include <queue>

template<class T>
ArbolGeneral<T>::ArbolGeneral() {
	this->raiz = NULL;
}

template<class T>
ArbolGeneral<T>::ArbolGeneral(T& val) {
	NodoGeneral<T>* temp = new NodoGeneral<T>;
	temp->fijarDato(val);
	this->raiz = temp;
}

template<class T>
ArbolGeneral<T>::~ArbolGeneral() {
}

template<class T>
bool ArbolGeneral<T>::esVacio() {
	if (!this->raiz) {
		return true;
	}
	return false;
}

template<class T>
NodoGeneral<T>* ArbolGeneral<T>::obtenerRaiz() {
	return this->raiz;
}

template<class T>
void ArbolGeneral<T>::fijarRaiz(NodoGeneral<T>* nraiz) {
	this->raiz = nraiz;
}

template<class T>
bool ArbolGeneral<T>::insertarNodo(T& padre, T& n) {
	if (this->esVacio()) {
		NodoGeneral<T>* temp = new NodoGeneral<T>;
		temp->fijarDato(n);
		this->raiz = temp;
		return true;
	}
	return insertarRecursion(this->raiz, padre, n);
}

template<class T>
bool ArbolGeneral<T>::insertarRecursion(NodoGeneral<T>* nodo, T& padre, T& n) {
	if (nodo->obtenerDato() == padre) {
		nodo->adicionarDesc(n);
		return true;
	}
	else {
		std::list<NodoGeneral<T>*> desc = nodo->obtenerDesc();
		typename std::list<NodoGeneral<T>*>::iterator it = desc.begin();
		for (; it != desc.end(); it++) {
			if (insertarRecursion(*it, padre, n)) {
				return true;
			}
		}
	}
	return false;
}

template<class T>
bool ArbolGeneral<T>::eliminarNodo(T& n) {
	if (this->esVacio()) {
		return false;
	}
	if (n == this->raiz->obtenerDato()) {
		delete this->raiz;
		this->raiz = NULL;
		return true;
	}
	return eliminarRecursion(this->raiz, n);
}

template<class T>
bool ArbolGeneral<T>::eliminarRecursion(NodoGeneral<T>* nodo, T& n) {
	std::list<NodoGeneral<T>*> desc = nodo->obtenerDesc();
	typename std::list<NodoGeneral<T>*>::iterator it = desc.begin();
	for (; it != desc.end(); it++) {
		if ((*it)->obtenerDato() == n) {
			nodo->eliminarDesc(n);
			return true;
		}
		else {
			eliminarRecursion(*it, n);
		}
	}
	return false;
}

template<class T>
bool ArbolGeneral<T>::buscar(T& n) {
	if (this->esVacio()) {
		return false;
	}
	return buscarRecursion(this->raiz, n);
}

template<class T>
bool ArbolGeneral<T>::buscarRecursion(NodoGeneral<T>* nodo, T& n) {
	if (nodo->obtenerDato() == n) {
		return true;
	}
	else {
		std::list<NodoGeneral<T>*> desc = nodo->obtenerDesc();
		typename std::list<NodoGeneral<T>*>::iterator it = desc.begin();
		for (; it != desc.end(); it++) {
			if (buscarRecursion(*it, n)) {
				return true;
			}
		}
	}
	return false;
}

template<class T>
int ArbolGeneral<T>::altura() {
	if (this->esVacio()) {
		return -1;
	}
	else {
		return this->raiz->altura();
	}
}

template<class T>
unsigned int ArbolGeneral<T>::tamano() {
	if (this->esVacio()) {
		return 0;
	}
	unsigned int tam = 1;
	tamanoRecursion(this->raiz, tam);
	return tam;
}

template<class T>
void ArbolGeneral<T>::tamanoRecursion(NodoGeneral<T>* nodo, unsigned int& tam) {
	std::list<NodoGeneral<T>*> desc = nodo->obtenerDesc();
	typename std::list<NodoGeneral<T>*>::iterator it = desc.begin();
	for (; it != desc.end(); it++) {
		tam++;
		tamanoRecursion(*it, tam);
	}
}

template<class T>
void ArbolGeneral<T>::preOrden() {
	if (!this->esVacio()) {
		preOrdenRecursion(this->raiz);
	}
}

template<class T>
void ArbolGeneral<T>::preOrdenRecursion(NodoGeneral<T>* nodo) {
	std::cout << nodo->obtenerDato() << " ";
	std::list<NodoGeneral<T>*> desc = nodo->obtenerDesc();
	typename std::list<NodoGeneral<T>*>::iterator it = desc.begin();
	for (; it != desc.end(); it++) {
		preOrdenRecursion(*it);
	}
}

template<class T>
void ArbolGeneral<T>::posOrden() {
	if (!this->esVacio()) {
		posOrdenRecursion(this->raiz);
	}
}

template<class T>
void ArbolGeneral<T>::posOrdenRecursion(NodoGeneral<T>* nodo) {
	std::list<NodoGeneral<T>*> desc = nodo->obtenerDesc();
	typename std::list<NodoGeneral<T>*>::iterator it = desc.begin();
	for (; it != desc.end(); it++) {
		posOrdenRecursion(*it);
	}
	std::cout << nodo->obtenerDato() << " ";
}

template<class T>
void ArbolGeneral<T>::nivelOrden() {
	if (!this->esVacio()) {
		std::queue<NodoGeneral<T>*> cola;
		cola.push(this->raiz);
		NodoGeneral<T>* nodo;
		while (!cola.empty()) {
			nodo = cola.front();
			cola.pop();
			std::cout << nodo->obtenerDato() << " ";
			std::list<NodoGeneral<T>*> desc = nodo->obtenerDesc();
			typename std::list<NodoGeneral<T>*>::iterator it = desc.begin();
			for (; it != desc.end(); it++) {
				cola.push(*it);
			}
		}
	}
}

template<class T>
std::string ArbolGeneral<T>::buscarCamino(T val) {
	if (this->raiz == NULL) {
		return "";
	}
	std::string ruta = "";
	buscarCaminoRecursion(this->raiz, "", val, ruta);
	return ruta;
}

template<class T>
bool ArbolGeneral<T>::buscarCaminoRecursion(NodoGeneral<T>* nodo, std::string ruta, T val,
	std::string& rutaFinal) {
	if (nodo->obtenerDato() == val) {
		rutaFinal = ruta;
		return true;
	}
	std::list<NodoGeneral<T>*> desc = nodo->obtenerDesc();
	typename std::list<NodoGeneral<T>*>::iterator it = desc.begin();
	int i = 0;
	for (; it != desc.end(); it++) {
		//Cada string es por separado en cada hijo siendo asi una ruta por cada uno de estos
		std::string rutaTemp = ruta + std::to_string(i);
		if (buscarCaminoRecursion(*it, rutaTemp, val, rutaFinal))
			return true;
		i++;
	}
	return false;
}