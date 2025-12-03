#ifndef NodoGeneral_h
#define NodoGeneral_h

#include <list>
#include <vector>

template<class T>
class NodoGeneral {
protected:
	T dato;
	std::list<NodoGeneral<T>*> desc;
	void alturaRecursion(NodoGeneral<T>* nodo, unsigned int altura, int& alturaMayor);
public:
	NodoGeneral();
	~NodoGeneral();
	T obtenerDato();
	void fijarDato(T& val);
	void limpiarLista();
	void adicionarDesc(T& nval);
	bool eliminarDesc(T& val);
	std::list<NodoGeneral<T>*> obtenerDesc();
	unsigned int altura();
};
#include "NodoGeneral.hxx"
#endif
