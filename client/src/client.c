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
	enviar_mensaje(valor, conexion);
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
	// Quité la primera lectura ya que preferí que entre directamente en el bucle
	char* leido;

	while (1) {
        leido = readline("> ");

        if(!strlen(leido)) break;

		log_info(logger,"%s",leido);

        free(leido);
    }

}

void consola_a_paquete(t_paquete* paquete)
{
	char* leido;
	int len;
	
	while (1) {
        leido = readline("> ");
		len=strlen(leido);

        if(!len) break;

		agregar_a_paquete(paquete,leido,len);
		//log_info(logger,"SE AÑADIO A PAQUETE :: %s",leido);

        free(leido);
    }
}

void paquete(int conexion)
{
	t_paquete* paquete;
	paquete=crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete
	consola_a_paquete(paquete); // Como tengo un paquete pointer me tomé la libertad de añadir una función que lee la consola y lo añade a un paquete
	enviar_paquete(paquete,conexion);

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}
