
#include <client.hpp>

Client *Client::client_instance = nullptr;

Client *Client::getI()
{
    if (client_instance == nullptr)
    {
        client_instance = new Client();
    }
    return client_instance;
}

void Client::setBody(string jsonFile)
{
    ifstream jsonStream;
    string line;

    jsonStream.open(jsonFile);
    if (!jsonStream)
    {
        spdlog::error("No se pudo abrir el archivo.");
        return;
    }

    while (jsonStream >> line)
    {
        post_body = post_body + line;
    }

    jsonStream.close();
}

jsoncons::json Client::getReceivedBody()
{
    return Json_received;
}

int Client::getStatus()
{
    return status_response;
}

void Client::limpiar()
{
    post_body = "";
    received_body = "";
    status_response = 0;
}

void Client::POST(string _url, string jsonFile)
{

    limpiar();
    setBody(jsonFile);
    cpr::Response r = cpr::Post(cpr::Url{url + _url},
                                cpr::Body{post_body},
                                cpr::Header{{"Content-Type", "application/json"}});

    spdlog::info(r.text);
    status_response = r.status_code;
}

void Client::GET(string _url, string jsonFile)
{

    limpiar();
    setBody(jsonFile);
    cpr::Response r = cpr::Get(cpr::Url{url + _url},
                                cpr::Body{post_body},
                                cpr::Header{{"Content-Type", "application/json"}});


    // Copiar datos al json
    string thisPath = get_selfpath();
    thisPath.erase(thisPath.length() - 3, thisPath.length());
    ofstream fs(thisPath + "../archivos_json/recibido.json");
    fs << r.text << endl;
    fs.close();

    status_response = r.status_code;
}

void Client::PUT(string _url, string jsonFile)
{

    limpiar();
    setBody(jsonFile);
    cpr::Response r = cpr::Put(cpr::Url{url + _url},
                               cpr::Body{post_body},
                               cpr::Header{{"Content-Type", "application/json"}});
    Json_received = jsoncons::json::parse(r.text);
    status_response = r.status_code;
}

void Client::DELETE(string _url)
{

    limpiar();
    cpr::Response r = cpr::Delete(cpr::Url{url + _url});
    Json_received = jsoncons::json::parse(r.text);
    status_response = r.status_code;
}