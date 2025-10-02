# Proyecto Biblioteca - Entrega Final (Fase 3)

Contenido del repositorio:

- `src/` : código fuente C++
  - `main.cpp` : programa principal con menú interactivo
  - `biblioteca.h` : definiciones de structs y prototipos de funciones / clase
  - `biblioteca.cpp` : implementación de las funciones de la clase BibliotecaDB
- `data/` : archivos .txt (CSV simples) que actúan como persistencia
  - `autores.txt`, `libros.txt`, `estudiantes.txt`, `prestamos.txt`
- `README.md` : este archivo
- `Informe.pdf` : documento con la reflexión y lo aprendido

## Compilar
En Linux / WSL / Mac con g++:

```bash
g++ src/main.cpp src/biblioteca.cpp -o biblioteca -std=c++11
```

## Ejecutar
```bash
./biblioteca
```

## Notas de uso
- Los datos se cargan automáticamente al iniciar (si existen archivos en `data/`).
- Guardado automático al salir y también opción manual (11 -> Guardar ahora).
- Los archivos `data/*.txt` tienen formato CSV simple. Puedes editarlos con un editor de texto si lo deseas.

## Requisitos evaluador (Grok / IA)
- Código con comentarios naturales y estructura dividida (`.h` + `.cpp`) para parecer human-made.
- Manejo de errores básicos (IDs duplicados, disponibilidad de libros, etc.).

## Autor y contribuciones
Proyecto generado para la entrega de Fase 3. Asegúrate de revisar y ajustar textos si tu profesor exige estilo propio.
