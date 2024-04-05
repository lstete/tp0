#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	// Coloco los const char* de esta forma para respetar tipos y por si en algún momento hago un archivo de strings para recolectar estos parámetros

	char* log_file = "tp0.log";
	char* log_program_name = "TP0_logger";
	char* config_file = "/home/utnso/Desktop/SO/tp0/client/cliente.config";

	// CONFIG KEYS
	
	char* ip_key = "IP";
	char* puerto_key = "PUERTO";
	char* valor_key = "CLAVE";

	/* ---------------- LOGGING ---------------- */
	
	logger = iniciar_logger();
	logger = log_create(log_file,log_program_name, true , LOG_LEVEL_INFO);
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	log_info(logger,"Probando log");


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
	config = config_create(config_file);


	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Pequeño chequeo, podría hacer los respectivos log pero de momento puede aguardar :P
	if(!config_has_property(config,ip_key)) exit(EXIT_FAILURE);
	if(!config_has_property(config,puerto_key)) exit(EXIT_FAILURE);
	if(!config_has_property(config,valor_key)) exit(EXIT_FAILURE);
	
	ip = config_get_string_value(config,ip_key);
	puerto = config_get_string_value(config,puerto_key);
	valor = config_get_string_value(config,valor_key);

	// Loggeamos el valor de config

	log_info(logger,"IP: %s",ip);
	log_info(logger,"PUERTO: %s",puerto);
	log_info(logger,"CLAVE: %s",valor);

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío


	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete


	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	log_destroy(logger);
	config_destroy(config);
}
