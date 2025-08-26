#include <iostream>
#include <string>
#include <vector>

using namespace std;

// clase libro
class Libro {
public:
    string titulo;
    string autor;
    int anio;
    bool disp;

    Libro() {
        anio = 0;
        disp = true; // siempre nuevo esta libre
    }

    void mostrar() {
        cout << "Titulo: " << titulo << "\n";
        cout << "Autor: " << autor << "\n";
        cout << "Anio: " << anio << "\n";
        if (disp) {
            cout << "Disponible\n";
        } else {
            cout << "Prestado\n";
        }
    }
};

// clase biblioteca
class Biblioteca {
public:
    vector<Libro> lista;

    void agregar(Libro l) {
        lista.push_back(l);
    }

    void inventario() {
        if (lista.size() == 0) {
            cout << "No hay libros\n";
        } else {
            cout << "\n--- INVENTARIO ---\n";
            for (int i = 0; i < lista.size(); i++) {
                cout << "\nLibro #" << i+1 << endl;
                lista[i].mostrar();
            }
        }
    }

    int buscar(string t) {
        for (int i = 0; i < lista.size(); i++) {
            if (lista[i].titulo == t) {
                return i;
            }
        }
        return -1;
    }

    void prestar(string t) {
        int pos = buscar(t);
        if (pos == -1) {
            cout << "No esta ese libro\n";
        } else {
            if (lista[pos].disp) {
                lista[pos].disp = false;
                cout << "Prestado con exito\n";
            } else {
                cout << "Ya estaba prestado\n";
            }
        }
    }

    void devolver(string t) {
        int pos = buscar(t);
        if (pos == -1) {
            cout << "No esta ese libro\n";
        } else {
            if (!lista[pos].disp) {
                lista[pos].disp = true;
                cout << "Devuelto\n";
            } else {
                cout << "Ese libro no estaba prestado\n";
            }
        }
    }
};

int main() {
    Biblioteca biblio;
    int op = 0;

    // Cargar 5 libros al inicio
    Libro l1; l1.titulo = "Don Quijote de la Mancha"; l1.autor = "Miguel de Cervantes"; l1.anio = 1605;
    Libro l2; l2.titulo = "Crimen de la calle Morgue"; l2.autor = "Edgar Allan Poe"; l2.anio = 1841;
    Libro l3; l3.titulo = "Hamlet"; l3.autor = "William Shakespeare"; l3.anio = 1603;
    Libro l4; l4.titulo = "La Biblia"; l4.autor = "Varios"; l4.anio = -500;
    Libro l5; l5.titulo = "Juego de Tronos"; l5.autor = "George R. R. Martin"; l5.anio = 1996;

    biblio.agregar(l1);
    biblio.agregar(l2);
    biblio.agregar(l3);
    biblio.agregar(l4);
    biblio.agregar(l5);

    while (op != 4) {
        // Mostrar inventario SIEMPRE antes del menú
        biblio.inventario();

        cout << "\n--- MENU ---\n";
        cout << "1. Anadir libro\n";
        cout << "2. Prestar\n";
        cout << "3. Devolver\n";
        cout << "4. Salir\n";
        cout << "opcion: ";
        cin >> op;
        cin.ignore();

        if (op == 1) {
            Libro l;
            cout << "Titulo: ";
            getline(cin, l.titulo);
            cout << "Autor: ";
            getline(cin, l.autor);
            cout << "Anio: ";
            cin >> l.anio;
            cin.ignore();
            biblio.agregar(l);

        } else if (op == 2) {
            string t;
            cout << "Titulo: ";
            getline(cin, t);
            biblio.prestar(t);

        } else if (op == 3) {
            string t;
            cout << "Titulo: ";
            getline(cin, t);
            biblio.devolver(t);

        } else if (op == 4) {
            cout << "Adios\n";
        } else {
            cout << "opcion no valida\n";
        }
    }

    return 0;
}