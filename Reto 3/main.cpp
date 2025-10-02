#include <iostream>
#include "biblioteca.h"

using namespace std;

int main() {
    BibliotecaDB db; // carga datos en constructor
    int opcion = -1;

    while (opcion != 0) {
        cout << "\n==== Sistema Biblioteca ====
";
        cout << "1. Agregar Autor\n2. Listar Autores\n3. Agregar Libro\n4. Listar Libros\n5. Agregar Estudiante\n6. Listar Estudiantes\n7. Registrar Prestamo\n8. Listar Prestamos\n9. Devolver Prestamo\n10. Consultas (libros por estudiante / autores mas libros)\n11. Guardar ahora\n0. Salir\n";
        cout << "Opcion: ";
        if (!(cin >> opcion)) { cin.clear(); cin.ignore(10000,'\n'); cout << "Entrada no valida\n"; continue; }

        if (opcion == 1) {
            Autor a;
            cout << "ID: "; cin >> a.id; cin.ignore();
            cout << "Nombre: "; getline(cin, a.nombre);
            cout << "Nacionalidad: "; getline(cin, a.nacionalidad);
            cout << "Cantidad de libros: "; cin >> a.cantidad_libros;
            if (db.agregarAutor(a)) cout << "Autor agregado\n"; else cout << "Fallo: ID duplicado\n";
        }
        else if (opcion == 2) {
            db.listarAutores();
        }
        else if (opcion == 3) {
            Libro l; cout << "ID: "; cin >> l.id; cin.ignore();
            cout << "Titulo: "; getline(cin, l.titulo);
            cout << "ISBN: "; getline(cin, l.isbn);
            cout << "Anio: "; cin >> l.anio;
            cout << "Paginas: "; cin >> l.paginas;
            cout << "ID Autor: "; cin >> l.id_autor;
            l.disponible = true;
            if (db.agregarLibro(l)) cout << "Libro agregado\n"; else cout << "Fallo: ID duplicado o autor inexistente\n";
        }
        else if (opcion == 4) {
            db.listarLibros();
        }
        else if (opcion == 5) {
            Estudiante e;
            cout << "ID: "; cin >> e.id; cin.ignore();
            cout << "Nombre: "; getline(cin, e.nombre);
            cout << "Grado: "; getline(cin, e.grado);
            cout << "Carga universitaria: "; getline(cin, e.carga_universitaria);
            if (db.agregarEstudiante(e)) cout << "Estudiante agregado\n"; else cout << "Fallo: ID duplicado\n";
        }
        else if (opcion == 6) {
            db.listarEstudiantes();
        }
        else if (opcion == 7) {
            Prestamo p;
            cout << "ID Prestamo: "; cin >> p.id;
            cout << "ID Libro: "; cin >> p.id_libro;
            cout << "ID Estudiante: "; cin >> p.id_estudiante; cin.ignore();
            cout << "Fecha prestamo (YYYY-MM-DD): "; getline(cin, p.fecha_prestamo);
            p.fecha_devolucion = "";
            if (db.agregarPrestamo(p)) cout << "Prestamo registrado\n"; else cout << "Fallo: validacion (libro/estudiante) o libro no disponible\n";
        }
        else if (opcion == 8) {
            db.listarPrestamos();
        }
        else if (opcion == 9) {
            int idp; string fdev;
            cout << "ID Prestamo a devolver: "; cin >> idp; cin.ignore();
            cout << "Fecha devolucion (YYYY-MM-DD): "; getline(cin, fdev);
            if (db.devolverPrestamo(idp, fdev)) cout << "Devolucion registrada\n"; else cout << "Prestamo no encontrado\n";
        }
        else if (opcion == 10) {
            int sub;
            cout << "1. Listar libros prestados por estudiante\n2. Autores con mas libros\nOpcion: "; cin >> sub;
            if (sub == 1) { int id; cout << "ID Estudiante: "; cin >> id; db.listarLibrosPrestadosPorEstudiante(id); }
            else if (sub == 2) db.autoresConMasLibros();
        }
        else if (opcion == 11) {
            db.guardarDatos(); cout << "Guardado manual completo\n";
        }
        else if (opcion == 0) {
            cout << "Saliendo... (datos guardados al cerrar)\n";
        }
        else {
            cout << "Opcion no valida\n";
        }
    }

    return 0;
}
