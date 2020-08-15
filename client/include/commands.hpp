#ifndef COMMANDS_H
#define COMMANDS_H

#include <client.hpp>

/**
 * Clase que contiene los métodos necesarios para manejar los comandos de consola.
 */
class Command
{
public:
    /**
     * Variable que almacena la ruta donde se encuentra el ejecutable.
     */
    static string thisPath;

    /**
     * Método que permite realizar merge entre dos archivos.
     * @param fileAfter Archivo nuevo.
     * @param fileBefore Archivo viejo.
     * @param patch Ruta donde se guarda el parche.
     */
    static void diff_sync(string fileAfter, string fileBefore, string patch);

    /**
     * Método que permite sacar las diferencias entre dos archivos.
     * @param fileAfter Archivo nuevo.
     * @param fileBefore Archivo viejo.
     * @param patch Ruta donde se guarda el parche.
     */
    static void diff(string fileAfter, string fileBefore, string result);

    /**
     * Método que permite modificar un archivo aplicandole un parche.
     * @param original Archivo original.
     * @param changes Ruta donde se encuentra el parche.
     */
    static void applyChanges(string original, string changes);

    /**
     * Método que actualiza la lista de archivos en base al .gotignore.
     */
    static void updateIgnore();

    /**
     * Método que retorna la ruta del ejecutable.
     * @return Ruta del ejecutable.
     */
    static string get_selfpath();

    /**
     * Método que inicializa el repositorio en la ruta actual, agregando los archivos necesarios.
     * @param repoName Archivo original.
     */
    static void init(string repoName);

    /**
     * Método que agrega los archivos para el commit.
     * @param archivos Archivo original.
     */
    static void add(string archivos);

    /**
     * Método que realiza el commit de los archivos agregados con un mensaje.
     * @param mensaje Archivo original.
     */
    static void commit(string mensaje);

    /**
     * Método que extrae el contenido del archivo parche.
     * @return Contenido del parche.
     */
    static string diff_a_string();

    /**
     * Método que solicita el estado de un archivo en el cliente respecto al servidor.
     * @param archivo Archivo en el cliente.
     */
    static void status(string archivo);

    /**
     * Método que muestra los commits realizados y sus mensajes.
     */
    static void log();

    /**
     * Método que devuelve un archivo a un commit específico.
     * @param archivo Archivo en el cliente.
     * @param commit Archivo en el cliente.
     */
    static void rollback(string archivo, string commit, bool ruta_externa);

    /**
     * Método que devuelve un archivo al último commit.
     * @param archivo Archivo en el cliente.
     */
    static void reset(string archivo);

    /**
     * Método que permite sincronizar un archivo en el cliente con el del servidor.
     * @param archivo Archivo en el cliente.
     */
    static void sync(string archivo);
};

#endif
