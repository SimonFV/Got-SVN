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

class ControlServerCliente
{
         
    public:
        void list_dir(string dir);
        void control_local_server (string elem, string tipo_control);
        int auxiliar_control_local_server(string elem, string key);
        void escribir_json(string ruta, Json::Value root);
        std::string leer_json(string ruta, string dato);
        std::string leer_json2(string ruta, string dato);
        
};

#endif