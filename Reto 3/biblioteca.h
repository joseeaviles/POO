#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <string>
#include <vector>

// Estructuras que representan las tablas
struct Autor {
    int id;
    std::string nombre;
    std::string nacionalidad;
    int cantidad_libros;
};

struct Libro {
    int id;
    std::string titulo;
    std::string isbn;
    int anio;
    int paginas;
    int id_autor; // FK
    bool disponible;
};

struct Estudiante {
    int id;
    std::string nombre;
    std::string grado;
    std::string carga_universitaria;
};

struct Prestamo {
    int id;
    int id_libro;
    int id_estudiante;
    std::string fecha_prestamo;
    std::string fecha_devolucion;
};

// Clase que contiene los "vectores" (tablas) y operaciones
class BibliotecaDB {
public:
    // Tablas en memoria
    std::vector<Autor> autores;
    std::vector<Libro> libros;
    std::vector<Estudiante> estudiantes;
    std::vector<Prestamo> prestamos;

    // Constructor / Destructor
    BibliotecaDB();
    ~BibliotecaDB();

    // CRUD Autores
    bool agregarAutor(const Autor &a);
    void listarAutores() const;
    bool eliminarAutor(int id);
    bool actualizarAutor(const Autor &a);

    // CRUD Libros
    bool agregarLibro(const Libro &l);
    void listarLibros() const;
    bool eliminarLibro(int id);
    bool actualizarLibro(const Libro &l);

    // CRUD Estudiantes
    bool agregarEstudiante(const Estudiante &e);
    void listarEstudiantes() const;
    bool eliminarEstudiante(int id);
    bool actualizarEstudiante(const Estudiante &e);

    // CRUD Prestamos
    bool agregarPrestamo(const Prestamo &p);
    void listarPrestamos() const;
    bool devolverPrestamo(int id_prestamo, const std::string &fecha_devolucion);

    // Consultas útiles
    void listarLibrosPrestadosPorEstudiante(int id_estudiante) const;
    void autoresConMasLibros() const;

    // Persistencia (guardar / cargar)
    void guardarDatos() const;
    void cargarDatos();

private:
    // helpers internos
    bool existeAutor(int id) const;
    bool existeLibro(int id) const;
    bool existeEstudiante(int id) const;
    bool libroDisponible(int id) const;
};

#endif // BIBLIOTECA_H
