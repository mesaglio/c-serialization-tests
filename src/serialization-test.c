#include <stdio.h>
#include <stdbool.h>
#include <cspecs/cspec.h>
#include "serialization.c"
context (example) {

    describe("t_error serialization test") {

        it("serialization-deserialization size-test") {
            t_error* _error = crear_error("Error al crear log");
            void* buffer = serializar_paquete_error(_error);
            t_error* __error = deserializar_paquete_error(buffer+8);
            should_int(_error->size_descripcion) be equal to(__error->size_descripcion);
        }end

        it("serialization-deserialization content-test") {
            t_error* _error = crear_error("Error al crear log");
            void* buffer = serializar_paquete_error(_error);
            t_error* __error = deserializar_paquete_error(buffer+8);
            should_string(_error->descripcion) be equal to(__error->descripcion);
        }end
    }end

}
