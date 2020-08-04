#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <fstream>
#include <string>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <cpr/cpr.h>
#include <jsoncons/json.hpp>
#include <huffman.hpp>
#include "md5.h"
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <jsoncpp/json/json.h>

using namespace std;

void diff(string fileAfter, string fileBefore, string result);

void applyChanges(string original, string changes);

string get_selfpath();

class Client
{
private:
    static Client *client_instance;
    string post_body, received_body, url;
    int status_response;
    jsoncons::json Json_received;

private:
    /**
     * Constructor de la clase cliente.
     */
    Client()
    {
        url = "http://localhost:9000/";
        post_body = "";
        received_body = "";
        status_response = 0;
    }
    /**
     * Destructor de la clase cliente.
     */
    ~Client()
    {
    }

public:
    /**
     * Método que obtiene la instancia del cliente
     * @return - Instancia del cliente
     */
    static Client *getI();
    /**
     * Método que evita la reasignación de la instancia del cliente
     * @param other - Cliente creado
     */
    Client(Client &other) = delete;
    /**
     * Método que evita la reasignación de la instancia del cliente
     */
    void operator=(const Client &) = delete;

public:
    void setBody(string jsonFile);
    jsoncons::json getReceivedBody();
    int getStatus();

    void POST(string _url, string jsonFile);
    void GET(string _url, string jsonFile);
    void PUT(string _url, string jsonFile);
    void DELETE(string _url);
    void limpiar();
};

#endif