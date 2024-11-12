

	# Compilador a utilizar
	CC = gcc

	# Opciones de compilación
	CFLAGS = -Wall -Wextra -pthread  
	# -Wall y -Wextra activan advertencias; -pthread permite el uso de hilos

	# Targets (programas a compilar)
	TARGETS = publicadorp suscriptorp_modificado sistemap_modificado

	# Regla por defecto que se ejecuta al invocar 'make' sin argumentos
	all: $(TARGETS)

	# Regla para compilar el programa 'publicadorp'
	publicadorp: publicadorp.c
		$(CC) $(CFLAGS) -o publicadorp publicadorp.c  
		# Compila 'publicadorp.c' y genera el ejecutable 'publicadorp'

	# Regla para compilar el programa 'suscriptorp_modificado'
	suscriptorp_modificado: suscriptorp_modificado.c
		$(CC) $(CFLAGS) -o suscriptorp_modificado suscriptorp_modificado.c  
		# Compila 'suscriptorp_modificado.c'

	# Regla para compilar el programa 'sistemap_modificado'
	sistemap_modificado: sistemap_modificado.c
		$(CC) $(CFLAGS) -o sistemap_modificado sistemap_modificado.c  # Compila 'sistemap_modificado.c'

	# Regla para limpiar los archivos generados
	clean:
		rm -f $(TARGETS)  
		# Elimina los archivos ejecutables especificados en TARGETS