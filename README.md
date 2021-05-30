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

Ahora a probar!!

Contamos con dos ejemplos, uno tiene una carpeta `src` donde contamos tanto el archivo de test como el .c donde estan definidas las funcions. El otro tiene dentro una shared library con las mismas funciones.

Para correr el primero la unica libreria que necesita es cpecs, como se encuentra en el makefile se le agrega el flag `-lcspecs`.

Para instalar cspec:
```bash
$ > git clone https://github.com/mumuki/cspec.git
$ > cd cspec
$ > make
$ > sudo make install
```

[Documentacion de cspec](https://github.com/mumuki/cspec)

Ahora que tenemos cpecs instalado a nivel sistema podemos compilar y correr el archivo de test de la siguiente manera
```bash
$ > cd TestSimpleSrcs && make
$ > ./serialization-test
```

El segundo ejemplo cuneta con una shared library creada mediante eclipse, la cual tiene el mismo codigo que el ejemplo anterior. Lo unico que agregamos es como testear codigo que se encuentra en una libreria.

Para compilarlo y correrlo
```bash
$ > cd TestSharedLibrary && make
$ > LD_LIBRARY_PATH="libSerializacion/Debug/" ./serialization-test
```

Para ver los packetes con tcpdump en ascii:
```
$ > sudo tcpdump 'tcp[13] & 8!=0' and -A -nvvv -i lo port SERVER_PORT
#Example
$ > sudo tcpdump 'tcp[13] & 8!=0' and -A -nvvv -i lo port 8080
```
 PD: la parte de `'tcp[13] & 8!=0'` es para [filtrar por flag push](https://danielmiessler.com/study/tcpdump/).
