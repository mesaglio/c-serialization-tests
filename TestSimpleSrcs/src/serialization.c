#include "serialization.h"

int main(void) {
    t_error* _error = crear_error("Error al crear log");
    void* buffer = serializar_paquete_error(_error);
    t_error* __error = deserializar_paquete_error(buffer+8);
    return EXIT_SUCCESS;
}
int char_length(char* str){
    return strlen(str)+1;
}

t_error* crear_error(char* descripcion) {
    int size_descripcion = char_length(descripcion);
    t_error* error = malloc(sizeof(t_error));
    error->descripcion = malloc(size_descripcion);
    error->size_descripcion = size_descripcion;
    memcpy(error->descripcion, descripcion, error->size_descripcion);
    return error;
}

void* serializar_paquete_error(t_error* error) {
    int bytes = sizeof(int) + char_length(error->descripcion) + sizeof(int) * 2;
    int comando = ERROR;
    int puntero = 0;
    void* magic = malloc(bytes);
    memcpy(magic + puntero, &comando, 4);
    puntero += 4;
    memcpy(magic + puntero, &bytes, 4);
    puntero += 4;
    memcpy(magic + puntero, &error->size_descripcion, 4);
    puntero += 4;
    memcpy(magic + puntero, error->descripcion, error->size_descripcion);
    puntero += error->size_descripcion;
    return magic;
}

t_error* deserializar_paquete_error(void* magic) {
    t_error* error = malloc(sizeof(t_error));
    int puntero = 0;
    memcpy(&error->size_descripcion, magic + puntero, 4);
    puntero += 4;
    error->descripcion = malloc(error->size_descripcion);
    memcpy(error->descripcion, magic + puntero, error->size_descripcion);
    puntero += error->size_descripcion;
    return error;
}
