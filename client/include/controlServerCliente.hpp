#ifndef MANEJAR_JSON_H
#define MANEJAR_JSON_H

#include <iostream>
#include <dirent.h>
#include <string>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <jsoncpp/json/json.h>

using namespace std;

/**
 * Clase que se encarga de manipular los archivos de control del proyecto locales.
 */
class Control
{
public:
    /**
     * Método que lista los archivos que se encuentran en el directorio.
     * @param dir_name ruta del directorio actual.
     */
    static void list_dir(const char *dir_name);

    /**
     * Método que modifica la estructura de control de los archivos locales.
     * @param elem nuevo archivo a agregar o actualizar.
     */
    static void control_local_server(string elem);

    /**
     * Método que escribe el objeto json en el archivo.
     * @param ruta ruta del archivo .json.
     * @param root objeto json.
     */
    static void escribir_json(string ruta, Json::Value root);

    /**
     * Método que escribe el objeto json en el archivo.
     * @param ruta ruta del archivo .json.
     * @param root dato a obtener.
     * @return string de la llave especifica.
     */
    static std::string leer_json(string ruta, string dato);

    /**
     * Método que escribe el objeto json en el archivo.
     * @param ruta ruta del archivo .json.
     * @param root dato a obtener.
     * @return string de la llave especifica.
     */
    static std::string leer_json2(string ruta, string dato);

    /**
     * Método consulta el archivo .gotignore para saber si el archivo es ignorado.
     * @param ruta ruta del archivo.
     * @return true si el archivo esta en la lista.
     */
    static bool isIgnored(string ruta);

    /**
     * Método que encripta texto a ascii.
     * @param texto texto a encriptar.
     * @return texto en ascii.
     */
    static std::string encriptar_texto_a_ascii(string texto);

    /**
     * Método que desencripta texto de ascii.
     * @param texto_final_ascii texto a desencriptar en ascii.
     * @return texto normal.
     */
    static std::string desencriptar_ascii_a_texto(string texto_final_ascii);
};

#endif