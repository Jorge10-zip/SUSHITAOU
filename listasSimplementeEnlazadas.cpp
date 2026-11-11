#include <iostream>
#include <string>

using namespace std;

// --- ESTRUCTURAS BASE ---
struct Dato {
    int id;
    string nombre;
};

struct Nodo {
    Dato info;
    Nodo* siguiente;

    Nodo(Dato d) {
        info = d;
        siguiente = nullptr;
    }
};

// --- PROTOTIPOS DE TODAS LAS FUNCIONES ---
void insertarAlInicio(Nodo*& cabeza, Dato d);
void insertarAlFinal(Nodo*& cabeza, Dato d);
void insertarOrdenado(Nodo*& cabeza, Dato d);
void eliminarAlInicio(Nodo*& cabeza);
void eliminarAlFinal(Nodo*& cabeza);
void eliminarPorValor(Nodo*& cabeza, int id);
Nodo* buscarNodo(Nodo* cabeza, int id);
int contarNodos(Nodo* cabeza);
Nodo* obtenerUltimo(Nodo* cabeza);
void invertirLista(Nodo*& cabeza);
void vaciarLista(Nodo*& cabeza);
void concatenarListas(Nodo*& cabeza1, Nodo* cabeza2);
void mostrarLista(Nodo* cabeza);

// ==========================================
// 1. INSERCIONES
// ==========================================

void insertarAlInicio(Nodo*& cabeza, Dato d) {
    Nodo* nuevo = new Nodo(d);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

void insertarAlFinal(Nodo*& cabeza, Dato d) {
    Nodo* nuevo = new Nodo(d);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        return;
    }
    Nodo* actual = cabeza;
    while (actual->siguiente != nullptr) {
        actual = actual->siguiente;
    }
    actual->siguiente = nuevo;
}

void insertarOrdenado(Nodo*& cabeza, Dato d) {
    Nodo* nuevo = new Nodo(d);
    // Si la lista está vacía o el nuevo es menor que la cabeza
    if (cabeza == nullptr || cabeza->info.id >= d.id) {
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        return;
    }
    Nodo* actual = cabeza;
    // Buscar el nodo anterior al lugar de inserción
    while (actual->siguiente != nullptr && actual->siguiente->info.id < d.id) {
        actual = actual->siguiente;
    }
    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
}

// ==========================================
// 2. ELIMINACIONES
// ==========================================

void eliminarAlInicio(Nodo*& cabeza) {
    if (cabeza == nullptr) return;
    Nodo* temp = cabeza;
    cabeza = cabeza->siguiente;
    delete temp;
}

void eliminarAlFinal(Nodo*& cabeza) {
    if (cabeza == nullptr) return;
    // Si solo hay un nodo
    if (cabeza->siguiente == nullptr) {
        delete cabeza;
        cabeza = nullptr;
        return;
    }
    // Llegar al penúltimo nodo
    Nodo* actual = cabeza;
    while (actual->siguiente->siguiente != nullptr) {
        actual = actual->siguiente;
    }
    delete actual->siguiente; // Borramos el último
    actual->siguiente = nullptr; // El penúltimo ahora es el último
}

void eliminarPorValor(Nodo*& cabeza, int id) {
    if (cabeza == nullptr) return;

    if (cabeza->info.id == id) {
        Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        return;
    }
    Nodo* actual = cabeza;
    while (actual->siguiente != nullptr && actual->siguiente->info.id != id) {
        actual = actual->siguiente;
    }
    if (actual->siguiente != nullptr) {
        Nodo* temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        delete temp;
    }
}

// ==========================================
// 3. CONSULTAS Y BÚSQUEDAS
// ==========================================

Nodo* buscarNodo(Nodo* cabeza, int id) {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->info.id == id) return actual;
        actual = actual->siguiente;
    }
    return nullptr;
}

int contarNodos(Nodo* cabeza) {
    int contador = 0;
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}

Nodo* obtenerUltimo(Nodo* cabeza) {
    if (cabeza == nullptr) return nullptr;
    Nodo* actual = cabeza;
    while (actual->siguiente != nullptr) {
        actual = actual->siguiente;
    }
    return actual;
}

// ==========================================
// 4. MODIFICACIONES Y UTILIDADES
// ==========================================

void invertirLista(Nodo*& cabeza) {
    Nodo* anterior = nullptr;
    Nodo* actual = cabeza;
    Nodo* siguiente = nullptr;

    while (actual != nullptr) {
        siguiente = actual->siguiente; // Guardamos el siguiente
        actual->siguiente = anterior;  // Invertimos el enlace
        anterior = actual;             // Avanzamos anterior
        actual = siguiente;            // Avanzamos actual
    }
    cabeza = anterior; // La nueva cabeza es el último nodo que visitamos
}

void vaciarLista(Nodo*& cabeza) {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
    cabeza = nullptr;
}

void concatenarListas(Nodo*& cabeza1, Nodo* cabeza2) {
    if (cabeza1 == nullptr) {
        cabeza1 = cabeza2;
        return;
    }
    Nodo* ultimo = obtenerUltimo(cabeza1);
    ultimo->siguiente = cabeza2;
}

void mostrarLista(Nodo* cabeza) {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        cout << "[" << actual->info.id << ": " << actual->info.nombre << "] -> ";
        actual = actual->siguiente;
    }
    cout << "nullptr" << endl;
}

// ==========================================
// 5. MAIN (Para probar todo)
// ==========================================
int main() {
    Nodo* lista = nullptr;

    cout << "--- Insertando ---" << endl;
    insertarAlFinal(lista, { 10, "Juan" });
    insertarAlFinal(lista, { 20, "Maria" });
    insertarAlInicio(lista, { 5, "Pedro" });
    insertarOrdenado(lista, { 15, "Ana" }); // Debería quedar ordenado por ID
    mostrarLista(lista); // 5, 10, 15, 20

    cout << "\n--- Búsquedas ---" << endl;
    Nodo* encontrado = buscarNodo(lista, 15);
    if (encontrado != nullptr) cout << "Encontrado: " << encontrado->info.nombre << endl;
    cout << "Total de nodos: " << contarNodos(lista) << endl;

    cout << "\n--- Eliminando ---" << endl;
    eliminarAlInicio(lista); // Borra el 5
    eliminarAlFinal(lista);  // Borra el 20
    eliminarPorValor(lista, 15); // Borra a Ana
    mostrarLista(lista); // Solo queda el 10

    cout << "\n--- Invertir ---" << endl;
    insertarAlFinal(lista, { 30, "Luis" });
    insertarAlFinal(lista, { 40, "Sofia" });
    mostrarLista(lista);
    invertirLista(lista);
    mostrarLista(lista);

    cout << "\n--- Limpieza ---" << endl;
    vaciarLista(lista);
    mostrarLista(lista); // Debe decir nullptr

    return 0;
}



==============================================================================================================



#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

struct Dato {
    int id;
    string nombre;
};

// Funciones básicas
void insertarAlFinalEstatica(Dato arreglo[], int& cantidad, Dato d) {
    if (cantidad >= MAX) {
        cout << "Lista llena." << endl;
        return;
    }
    arreglo[cantidad] = d;
    cantidad++;
}
/*
ESPECIFICACION TIPO TAD
	PROPOSITO: Insertar un elemento al inicio de un arreglo estático.
	ENTRADAS:
		- arreglo: Arreglo de tipo Dato donde se insertará el nuevo elemento.
		- cantidad: Referencia a un entero que indica la cantidad actual de elementos en el arreglo.
		- d: Elemento de tipo Dato que se desea insertar al inicio del arreglo.
	SALIDAS:
		- Modifica el arreglo y la cantidad de elementos si la inserción es exitosa.
	RESTRICCIONES:
		- La cantidad de elementos no debe superar MAX (capacidad máxima del arreglo).
*/

void insertarAlInicioEstatica(Dato arreglo[], int& cantidad, Dato d) {
    if (cantidad >= MAX) return;
    // Mover todos una posición a la derecha
    for (int i = cantidad; i > 0; i--) {
        arreglo[i] = arreglo[i - 1];
    }
    arreglo[0] = d;
    cantidad++;
}

void eliminarPorIndiceEstatica(Dato arreglo[], int& cantidad, int indice) {
    if (indice < 0 || indice >= cantidad) return;
    // Mover todos una posición a la izquierda desde el índice
    for (int i = indice; i < cantidad - 1; i++) {
        arreglo[i] = arreglo[i + 1];
    }
    cantidad--;
}

int buscarElementoEstatica(Dato arreglo[], int cantidad, int id) {
    for (int i = 0; i < cantidad; i++) {
        if (arreglo[i].id == id) return i; // Retorna el índice
    }
    return -1; // No encontrado
}

void mostrarListaEstatica(Dato arreglo[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        cout << "[" << arreglo[i].id << ": " << arreglo[i].nombre << "] ";
    }
    cout << endl;
}

int main() {
    Dato listaEstatica[MAX];
    int cantidad = 0;

    cout << "--- Lista Estatica ---" << endl;
    insertarAlFinalEstatica(listaEstatica, cantidad, { 1, "A" });
    insertarAlFinalEstatica(listaEstatica, cantidad, { 2, "B" });
    insertarAlInicioEstatica(listaEstatica, cantidad, { 0, "Z" });

    mostrarListaEstatica(listaEstatica, cantidad); // Z, A, B

    int pos = buscarElementoEstatica(listaEstatica, cantidad, 2);
    cout << "El ID 2 esta en el indice: " << pos << endl;

    eliminarPorIndiceEstatica(listaEstatica, cantidad, 0); // Borra a Z
    mostrarListaEstatica(listaEstatica, cantidad); // A, B

    return 0;
}