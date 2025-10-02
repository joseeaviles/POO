#include "biblioteca.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

BibliotecaDB::BibliotecaDB() {
    // Al crear la instancia tratamos de cargar datos desde archivos
    cargarDatos();
}

BibliotecaDB::~BibliotecaDB() {
    // Al destruir la instancia guardamos automáticamente
    guardarDatos();
}

// ------------------ helpers ------------------
bool BibliotecaDB::existeAutor(int id) const {
    for (auto &a : autores) if (a.id == id) return true;
    return false;
}
bool BibliotecaDB::existeLibro(int id) const {
    for (auto &l : libros) if (l.id == id) return true;
    return false;
}
bool BibliotecaDB::existeEstudiante(int id) const {
    for (auto &e : estudiantes) if (e.id == id) return true;
    return false;
}
bool BibliotecaDB::libroDisponible(int id) const {
    for (auto &l : libros) if (l.id == id) return l.disponible;
    return false;
}

// ------------------ CRUD Autores ------------------
bool BibliotecaDB::agregarAutor(const Autor &a) {
    if (existeAutor(a.id)) return false;
    autores.push_back(a);
    return true;
}
void BibliotecaDB::listarAutores() const {
    cout << "== Autores ==\n";
    for (auto &a : autores) {
        cout << a.id << " | " << a.nombre << " | " << a.nacionalidad << " | Libros: " << a.cantidad_libros << "\n";
    }
}
bool BibliotecaDB::eliminarAutor(int id) {
    auto it = remove_if(autores.begin(), autores.end(), [&](const Autor &a){ return a.id == id; });
    if (it == autores.end()) return false;
    autores.erase(it, autores.end());
    return true;
}
bool BibliotecaDB::actualizarAutor(const Autor &a) {
    for (auto &x : autores) if (x.id == a.id) { x = a; return true; }
    return false;
}

// ------------------ CRUD Libros ------------------
bool BibliotecaDB::agregarLibro(const Libro &l) {
    if (existeLibro(l.id)) return false;
    // validar que autor exista
    if (!existeAutor(l.id_autor)) return false;
    libros.push_back(l);
    return true;
}
void BibliotecaDB::listarLibros() const {
    cout << "== Libros ==\n";
    for (auto &l : libros) {
        cout << l.id << " | " << l.titulo << " (" << l.anio << ") | AutorID:" << l.id_autor
             << " | Pag:" << l.paginas << " | " << (l.disponible ? "Disponible" : "Prestado") << "\n";
    }
}
bool BibliotecaDB::eliminarLibro(int id) {
    auto it = remove_if(libros.begin(), libros.end(), [&](const Libro &l){ return l.id == id; });
    if (it == libros.end()) return false;
    libros.erase(it, libros.end());
    return true;
}
bool BibliotecaDB::actualizarLibro(const Libro &l) {
    for (auto &x : libros) if (x.id == l.id) { x = l; return true; }
    return false;
}

// ------------------ CRUD Estudiantes ------------------
bool BibliotecaDB::agregarEstudiante(const Estudiante &e) {
    if (existeEstudiante(e.id)) return false;
    estudiantes.push_back(e);
    return true;
}
void BibliotecaDB::listarEstudiantes() const {
    cout << "== Estudiantes ==\n";
    for (auto &e : estudiantes) {
        cout << e.id << " | " << e.nombre << " | " << e.grado << " | Carga: " << e.carga_universitaria << "\n";
    }
}
bool BibliotecaDB::eliminarEstudiante(int id) {
    auto it = remove_if(estudiantes.begin(), estudiantes.end(), [&](const Estudiante &e){ return e.id == id; });
    if (it == estudiantes.end()) return false;
    estudiantes.erase(it, estudiantes.end());
    return true;
}
bool BibliotecaDB::actualizarEstudiante(const Estudiante &e) {
    for (auto &x : estudiantes) if (x.id == e.id) { x = e; return true; }
    return false;
}

// ------------------ CRUD Prestamos ------------------
bool BibliotecaDB::agregarPrestamo(const Prestamo &p) {
    if (!existeLibro(p.id_libro)) return false;
    if (!existeEstudiante(p.id_estudiante)) return false;
    // verificar disponibilidad libro
    for (auto &l : libros) {
        if (l.id == p.id_libro) {
            if (!l.disponible) return false;
            l.disponible = false;
            break;
        }
    }
    prestamos.push_back(p);
    return true;
}
void BibliotecaDB::listarPrestamos() const {
    cout << "== Prestamos ==\n";
    for (auto &p : prestamos) {
        cout << p.id << " | LibroID:" << p.id_libro << " | EstudianteID:" << p.id_estudiante
             << " | FechaPrest:" << p.fecha_prestamo << " | FechaDev:" << p.fecha_devolucion << "\n";
    }
}
bool BibliotecaDB::devolverPrestamo(int id_prestamo, const string &fecha_devolucion) {
    for (auto &p : prestamos) {
        if (p.id == id_prestamo) {
            p.fecha_devolucion = fecha_devolucion;
            // marcar libro disponible
            for (auto &l : libros) if (l.id == p.id_libro) { l.disponible = true; break; }
            return true;
        }
    }
    return false;
}

// ------------------ Consultas ------------------
void BibliotecaDB::listarLibrosPrestadosPorEstudiante(int id_estudiante) const {
    cout << "Libros prestados al estudiante " << id_estudiante << ":\n";
    for (auto &p : prestamos) if (p.id_estudiante == id_estudiante) {
        // buscar libro
        for (auto &l : libros) if (l.id == p.id_libro) {
            cout << " - " << l.id << " | " << l.titulo << " | Prestado en: " << p.fecha_prestamo << "\n";
            break;
        }
    }
}
void BibliotecaDB::autoresConMasLibros() const {
    cout << "Autores y cantidad de libros (segun registro):\n";
    for (auto &a : autores) {
        cout << a.id << " | " << a.nombre << " | Libros: " << a.cantidad_libros << "\n";
    }
}

// ------------------ Persistencia ------------------
void BibliotecaDB::guardarDatos() const {
    ofstream fa("data/autores.txt");
    for (auto &a : autores) fa << a.id << "," << a.nombre << "," << a.nacionalidad << "," << a.cantidad_libros << "\n";
    fa.close();

    ofstream fl("data/libros.txt");
    for (auto &l : libros)
        fl << l.id << "," << l.titulo << "," << l.isbn << "," << l.anio << "," << l.paginas << "," << l.id_autor << "," << (l.disponible?1:0) << "\n";
    fl.close();

    ofstream fe("data/estudiantes.txt");
    for (auto &e : estudiantes) fe << e.id << "," << e.nombre << "," << e.grado << "," << e.carga_universitaria << "\n";
    fe.close();

    ofstream fp("data/prestamos.txt");
    for (auto &p : prestamos) fp << p.id << "," << p.id_libro << "," << p.id_estudiante << "," << p.fecha_prestamo << "," << p.fecha_devolucion << "\n";
    fp.close();
}

void BibliotecaDB::cargarDatos() {
    // Cargar autores
    ifstream fa("data/autores.txt");
    if (fa.is_open()) {
        string line;
        while (getline(fa, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            Autor a;
            string tmp;
            getline(ss, tmp, ','); a.id = stoi(tmp);
            getline(ss, a.nombre, ',');
            getline(ss, a.nacionalidad, ',');
            getline(ss, tmp, ','); a.cantidad_libros = stoi(tmp);
            autores.push_back(a);
        }
        fa.close();
    }
    // Cargar libros
    ifstream fl("data/libros.txt");
    if (fl.is_open()) {
        string line;
        while (getline(fl, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            Libro l; string tmp;
            getline(ss, tmp, ','); l.id = stoi(tmp);
            getline(ss, l.titulo, ',');
            getline(ss, l.isbn, ',');
            getline(ss, tmp, ','); l.anio = stoi(tmp);
            getline(ss, tmp, ','); l.paginas = stoi(tmp);
            getline(ss, tmp, ','); l.id_autor = stoi(tmp);
            getline(ss, tmp, ','); l.disponible = (tmp == "1");
            libros.push_back(l);
        }
        fl.close();
    }
    # Cargar estudiantes
    ifstream fe("data/estudiantes.txt");
    if (fe.is_open()) {
        string line;
        while (getline(fe, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            Estudiante e; string tmp;
            getline(ss, tmp, ','); e.id = stoi(tmp);
            getline(ss, e.nombre, ',');
            getline(ss, e.grado, ',');
            getline(ss, e.carga_universitaria, ',');
            estudiantes.push_back(e);
        }
        fe.close();
    }
    // Cargar prestamos
    ifstream fp("data/prestamos.txt");
    if (fp.is_open()) {
        string line;
        while (getline(fp, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            Prestamo p; string tmp;
            getline(ss, tmp, ','); p.id = stoi(tmp);
            getline(ss, tmp, ','); p.id_libro = stoi(tmp);
            getline(ss, tmp, ','); p.id_estudiante = stoi(tmp);
            getline(ss, p.fecha_prestamo, ',');
            getline(ss, p.fecha_devolucion, ',');
            prestamos.push_back(p);
        }
        fp.close();
    }
}
