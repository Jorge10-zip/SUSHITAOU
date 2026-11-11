#include <iostream>
using namespace std;

// 1. El Dato (Puede ser un int, un string, o un struct complejo)
struct Dato {
	int valor;
};

// 2. El Nodo (El eslabón)
struct Nodo {
	Dato info;          // La caja donde guardas el dato
	Nodo* siguiente;    // La mano (puntero) que agarra al próximo nodo

	// Constructor: Cuando nace un nodo, su mano está vacía (nullptr)
	Nodo(Dato d) {
		info = d;
		siguiente = nullptr;
	}
};

void insertarAlInicio(Nodo*& cabeza, Dato d) {
	Nodo* nuevoNodo = new Nodo(d);
	nuevoNodo->siguiente = cabeza;
	cabeza = nuevoNodo;
}

void insertarAlFinal(Nodo*& cabeza, Dato d) {
	Nodo* nuevoNodo = new Nodo(d);
	if (cabeza == nullptr) {
		cabeza = nuevoNodo;
	}
	else {
		Nodo* actual = cabeza;
		while (actual->siguiente != nullptr) {
			actual = actual->siguiente;
		}
		actual->siguiente = nuevoNodo;
	}
}

void mostrarLista(Nodo* cabeza) {
	Nodo* actual = cabeza;
	while (actual != nullptr) {
		cout << actual->info.valor << " -> ";
		actual = actual->siguiente;
	}
	cout << "nullptr" << endl;
}

void eliminarNodo(Nodo*& cabeza, int valor) {
	if (cabeza == nullptr) return;
	if (cabeza->info.valor == valor) {
		Nodo* temp = cabeza;
		cabeza = cabeza->siguiente;
		delete temp;
		return;
	}
	Nodo* actual = cabeza;
	while (actual->siguiente != nullptr && actual->siguiente->info.valor != valor) {
		actual = actual->siguiente;
	}
	if (actual->siguiente != nullptr) {
		Nodo* temp = actual->siguiente;
		actual->siguiente = actual->siguiente->siguiente;
		delete temp;
	}
}

void vaciarLista(Nodo*& cabeza) {
	while (cabeza != nullptr) {
		Nodo* temp = cabeza;
		cabeza = cabeza->siguiente;
		delete temp;
	}
}

int main() {
	Nodo* cabeza = nullptr;
	Dato d1 = { 10 };
	Dato d2 = { 20 };
	Dato d3 = { 30 };
	insertarAlInicio(cabeza, d1);
	insertarAlFinal(cabeza, d2);
	insertarAlFinal(cabeza, d3);
	cout << "Lista despues de insertar: ";
	mostrarLista(cabeza);
	eliminarNodo(cabeza, 20);
	cout << "Lista despues de eliminar 20: ";
	mostrarLista(cabeza);
	vaciarLista(cabeza);
	cout << "Lista despues de vaciar: ";
	mostrarLista(cabeza);
	return 0;
}