#ifndef LIB_SERIALIZACION_H_
#define LIB_SERIALIZACION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    ERROR
} codigos;

typedef struct {
    int size_descripcion;
    char* descripcion;
} t_error;

t_error* deserializar_paquete_error(void* magic);
t_error* crear_error(char* descripcion);
void* serializar_paquete_error(t_error* error);
int char_length(char* str);

#endif /* LIB_SERIALIZACION_H_ */
