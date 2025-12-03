#include "NodoGeneral.h"
#include <list>
#include <vector>

template<class T>
NodoGeneral<T>::NodoGeneral() {
	this->desc.clear();
}

template<class T>
NodoGeneral<T>::~NodoGeneral() {
}

template<class T>
T NodoGeneral<T>::obtenerDato() {
	return this->dato;
}

template<class T>
void NodoGeneral<T>::fijarDato(T& val) {
	this->dato = val;
}

template<class T>
void NodoGeneral<T>::limpiarLista() {
	this->desc.clear();
}

template<class T>
void NodoGeneral<T>::adicionarDesc(T& nval) {
	NodoGeneral<T>* temp = new NodoGeneral<T>;
	temp->fijarDato(nval);
	this->desc.push_back(temp);
}

template<class T>
bool NodoGeneral<T>::eliminarDesc(T& val) {
	typename std::list<NodoGeneral<T>*>::iterator i = desc.begin();
	for (; i != desc.end(); i++) {
		if ((*i)->obtenerDato() == val) {
			delete* i;
			desc.erase(i);
			return true;
		}
	}
	return false;
}

template<class T>
std::list<NodoGeneral<T>*> NodoGeneral<T>::obtenerDesc() {
	return this->desc;
}

template<class T>
unsigned int NodoGeneral<T>::altura() {
	int altura = 0;
	alturaRecursion(this, 0, altura);
	return altura;
}

template<class T>
void NodoGeneral<T>::alturaRecursion(NodoGeneral<T>* nodo, unsigned int altura, int& alturaMayor) {
	std::list<NodoGeneral<T>*> desc = nodo->obtenerDesc();
	typename std::list<NodoGeneral<T>*>::iterator it = desc.begin();
	for (; it != desc.end(); it++) {
		alturaRecursion(*it, altura + 1, alturaMayor);
	}
	if (alturaMayor < altura) {
		alturaMayor = altura;
	}
}