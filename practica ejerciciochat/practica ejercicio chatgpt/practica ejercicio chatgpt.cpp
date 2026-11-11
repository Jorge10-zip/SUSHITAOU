#include<iostream>
#include<string>

using namespace std;

struct Materia {
	string nombre;
	int codigo;
};
struct Estudiante {
	string nombre;
	string carnet;
	int edad;
	Materia materia;
};
struct Nodo {
	Estudiante estudiante;
	Nodo* siguiente;
};

int main() {
	Nodo* cabeza = nullptr;
	Nodo* actual = nullptr;
	int cantidadEstudiantes;
	cout << "Ingrese la cantidad de estudiantes: ";
	cin >> cantidadEstudiantes;
	for (int i = 0; i < cantidadEstudiantes; i++) {
		Estudiante estudiante;
		cout << "Ingrese el nombre del estudiante: ";
		cin >> estudiante.nombre;
		cout << "Ingrese el carnet del estudiante: ";
		cin >> estudiante.carnet;
		cout << "Ingrese la edad del estudiante: ";
		cin >> estudiante.edad;
		cout << "Ingrese el nombre de la materia: ";
		cin >> estudiante.materia.nombre;
		cout << "Ingrese el codigo de la materia: ";
		cin >> estudiante.materia.codigo;
		Nodo* nuevoNodo = new Nodo();
		nuevoNodo->estudiante = estudiante;
		nuevoNodo->siguiente = nullptr;
		if (cabeza == nullptr) {
			cabeza = nuevoNodo;
			actual = cabeza;
		}
		else {
			actual->siguiente = nuevoNodo;
			actual = actual->siguiente;
		}
	}
	actual = cabeza;
	while (actual != nullptr) {
		cout << "Nombre: " << actual->estudiante.nombre << endl;
		cout << "Carnet: " << actual->estudiante.carnet << endl;
		cout << "Edad: " << actual->estudiante.edad << endl;
		cout << "Materia: " << actual->estudiante.materia.nombre << endl;
		cout << "Codigo de Materia: " << actual->estudiante.materia.codigo << endl;
		cout << endl;
		actual = actual->siguiente;
	}
	return 0;
}