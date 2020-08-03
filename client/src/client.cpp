
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

void Client::POST(string _url, string jsonFile)
{
    setBody(jsonFile);
    std::cout << "Action: Create Product with Id = 1" << std::endl;
    cpr::Response r = cpr::Post(cpr::Url{url + _url},
                                cpr::Body{post_body},
                                cpr::Header{{"Content-Type", "application/json"}});
    Json_received = jsoncons::json::parse(r.text);
    status_response = r.status_code;
}

void Client::GET(string _url)
{
    cpr::Response r = cpr::Get(cpr::Url{url + _url});
    Json_received = jsoncons::json::parse(r.text);
    status_response = r.status_code;
}

void Client::PUT(string _url, string jsonFile)
{
    setBody(jsonFile);
    cpr::Response r = cpr::Put(cpr::Url{url + _url},
                               cpr::Body{post_body},
                               cpr::Header{{"Content-Type", "application/json"}});
    Json_received = jsoncons::json::parse(r.text);
    status_response = r.status_code;
}

void Client::DELETE(string _url)
{
    cpr::Response r = cpr::Delete(cpr::Url{url + _url});
    Json_received = jsoncons::json::parse(r.text);
    status_response = r.status_code;
}