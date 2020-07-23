# Ejemplo de como testear funciones de serializacion en c con cspec

La estructura a utilizar es
```c
typedef struct {
    int size_descripcion;
    char* descripcion;
} t_error;
```

Contamos con las siguientes funciones:
```c
t_error* deserializar_paquete_error(void* magic);
t_error* crear_error(char* descripcion);
void* serializar_paquete_error(t_error* error);
int char_length(char* str);
```

Ahora viendo el archivo de test:
```c
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
```

Podemos ver que tenemos dos test, el primero para validar que el `size_descripcion` sea igual el del deserializado al `t_error` original.
El segundo nos confirma que el contenido sea el mismo.

Algo importante que podemos ver en **ambos** tests es que lo que le estamos pasando a la funcion de deserializacion no el buffer, si no que el buffer apartir de la posicion 8.

Porque??

Si vemos la funcion de `serializar_paquete_error` en los primeros 4 bytes pone el numero del codigo de operacion, el cual es 0 del enum de codigos.
En el segundo pone la cantidad de bytes que ocupa todo el buffer, ya que esta pensado para enviar a un servidor multi-hilo.

Para correr los test primero tenemos que compilarlo con la libreria cspec y luego ejecutar el binario
```bash
$ > gcc src/serialization-test.c -o tests -lcspecs
$ > ./tests
```

Para instalar cspec:
```bash
$ > git clone https://github.com/mumuki/cspec.git
$ > cd cspec
$ > make
$ > sudo make install
```

[Documentacion de cspec](https://github.com/mumuki/cspec)
