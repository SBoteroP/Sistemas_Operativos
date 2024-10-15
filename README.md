# Sistema de Distribución de Noticias

## Descripción del Proyecto

Este proyecto implementa un patrón Publicador/Suscriptor para un Sistema de Distribución de Noticias. Consta de tres componentes principales:

1. Publicadores
2. Suscriptores
3. Sistema de Comunicación

## Componentes

### Publicadores

- Publican noticias sin conocer a los destinatarios
- Se ejecutan desde la línea de comandos: `$ publicador –p pipePSC –f file –t timeN`
- Leen noticias de un archivo y las envían al Sistema de Comunicación
- Soportan 5 categorías de noticias: Arte (A), Espectáculos (E), Ciencia (C), Política (P), Sucesos (S)

### Suscriptores

- Se suscriben a categorías específicas de noticias
- Se ejecutan desde la línea de comandos: `$ suscriptor -s pipeSSC`
- Reciben noticias de interés del Sistema de Comunicación
- Muestran las noticias recibidas en pantalla

### Sistema de Comunicación

- Gestiona la comunicación entre Publicadores y Suscriptores
- Se ejecuta desde la línea de comandos: `$ sistema –p pipePSC -s pipeSSC –t timeF`
- Hace coincidir las suscripciones con las noticias publicadas
- Asegura la entrega correcta de noticias a los Suscriptores interesados

## Detalles de Implementación

- Desarrollado en ANSI C
- Utiliza pipes nominales para la comunicación entre procesos
- Soporta la creación dinámica de Publicadores y Suscriptores
- Longitud máxima de noticias: 80 caracteres

## Instrucciones de Compilación

Utiliza el Makefile proporcionado para compilar el proyecto: _'make all'_

## Ejecución del Sistema

1. Inicia el Sistema de Comunicación
2. Lanza los Suscriptores
3. Lanza los Publicadores

Consulta la sintaxis de línea de comandos proporcionada en la sección de Componentes.

## Estructura del Proyecto

- `publicador.c`: Implementación del Publicador
- `suscriptor.c`: Implementación del Suscriptor
- `sistema.c`: Implementación del Sistema de Comunicación
- `Makefile`: Para compilar el proyecto

## Notas

- Diseñado con fines educativos para un curso de Sistemas Operativos
- Demuestra la comunicación entre procesos y el patrón publicador/suscriptor
