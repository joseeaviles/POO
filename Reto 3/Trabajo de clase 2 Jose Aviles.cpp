#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Clase base Vehiculo
class Vehiculo {
public:
    string marca;
    string modelo;
    int año;
    double precioBase;

    Vehiculo() {
        año = 0;
        precioBase = 0;
    }

    virtual double calcularPrecioFinal() {
        return precioBase; 
    }

    virtual void mostrar() {
        cout << "Marca: " << marca << "\n";
        cout << "Modelo: " << modelo << "\n";
        cout << "Año: " << año << "\n";
        cout << "Precio base: $" << precioBase << "\n";
    }
};

// Clase Auto
class Auto : public Vehiculo {
public:
    int numeroPuertas;

    Auto() {
        numeroPuertas = 0;
    }

    double calcularPrecioFinal() override {
        return precioBase + (precioBase * 0.15); // 15% impuesto
    }

    void mostrar() override {
        Vehiculo::mostrar();
        cout << "Puertas: " << numeroPuertas << "\n";
        cout << "Precio final: $" << calcularPrecioFinal() << "\n";
    }
};

// Clase Moto
class Moto : public Vehiculo {
public:
    int cilindrada;

    Moto() {
        cilindrada = 0;
    }

    double calcularPrecioFinal() override {
        return precioBase + (precioBase * 0.10); // 10% impuesto
    }

    void mostrar() override {
        Vehiculo::mostrar();
        cout << "Cilindrada: " << cilindrada << "cc\n";
        cout << "Precio final: $" << calcularPrecioFinal() << "\n";
    }
};

// Clase Concesionaria
class Concesionaria {
public:
    vector<Vehiculo*> lista;

    void agregar(Vehiculo* v) {
        lista.push_back(v);
    }

    void inventario() {
        if (lista.size() == 0) {
            cout << "No hay vehiculos\n";
        } else {
            cout << "\n--- INVENTARIO ---\n";
            for (int i = 0; i < lista.size(); i++) {
                cout << "\nVehiculo #" << i+1 << endl;
                lista[i]->mostrar();
            }
        }
    }
};

int main() {
    Concesionaria cons;
    int op = 0;

    // Cargar 1 auto y 1 moto de ejemplo
    Auto* a1 = new Auto();
    a1->marca = "Toyota";
    a1->modelo = "Corolla";
    a1->año = 2022;
    a1->precioBase = 20000;
    a1->numeroPuertas = 4;

    Moto* m1 = new Moto();
    m1->marca = "Yamaha";
    m1->modelo = "MT-07";
    m1->año = 2021;
    m1->precioBase = 8000;
    m1->cilindrada = 689;

    cons.agregar(a1);
    cons.agregar(m1);

    while (op != 3) {
        // Mostrar inventario SIEMPRE antes del menú
        cons.inventario();

        cout << "\n--- MENU ---\n";
        cout << "1. Anadir Auto\n";
        cout << "2. Anadir Moto\n";
        cout << "3. Salir\n";
        cout << "opcion: ";
        cin >> op;
        cin.ignore();

        if (op == 1) {
            Auto* a = new Auto();
            cout << "Marca: ";
            getline(cin, a->marca);
            cout << "Modelo: ";
            getline(cin, a->modelo);
            cout << "Año: ";
            cin >> a->año;
            cout << "Precio base: ";
            cin >> a->precioBase;
            cout << "Numero de puertas: ";
            cin >> a->numeroPuertas;
            cin.ignore();
            cons.agregar(a);

        } else if (op == 2) {
            Moto* m = new Moto();
            cout << "Marca: ";
            getline(cin, m->marca);
            cout << "Modelo: ";
            getline(cin, m->modelo);
            cout << "Año: ";
            cin >> m->año;
            cout << "Precio base: ";
            cin >> m->precioBase;
            cout << "Cilindrada: ";
            cin >> m->cilindrada;
            cin.ignore();
            cons.agregar(m);

        } else if (op == 3) {
            cout << "Adios\n";
        } else {
            cout << "opcion no valida\n";
        }
    }

    return 0;
}