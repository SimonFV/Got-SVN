
#include <client.hpp>
#include <jsoncons/json.hpp>
#include <huffman.hpp>
#include "md5.h"

int main(int argc, char *argv[])
{

    /*
    diff("/home/simon/Cpp/Got-SVN/client/repo/testAfter.cpp",
         "/home/simon/Cpp/Got-SVN/client/repo/testBefore.cpp",
         "/home/simon/Cpp/Got-SVN/client/repo/test.patch");

    applyChanges("/home/simon/Cpp/Got-SVN/client/repo/testBefore.cpp",
                 "/home/simon/Cpp/Got-SVN/client/repo/test.patch");
    

    //EXTRAER DESDE STRING
    std::string data = R"(
    {
        "application": "hiking",
        "rater": "HikingAsylum",
        "assertion": "advanced",
        "reputons": [
        {
        
           "rated": "Marilyn C",
           "rating": 0.90,
           "confidence": 0.99
        }
        ]
    }
    )";

    // Parse the string of data into a json value
    jsoncons::json j = jsoncons::json::parse(data);

    spdlog::info(j["application"].as<std::string>());

    const jsoncons::json &v = j["reputons"];

    // Iterate over reputons array
    for (const auto &item : v.array_range())
    {
        // Access rated as string and rating as double
        std::cout << item["rated"].as<std::string>() << ", " << item["rating"].as<double>() << "\n";
    }
    */

    // ------ Codigo para probar Huffman ----------------

    fstream ficheroEntrada;
    string nombre = "/home/davidaqc/Documents/Got-SVN/client/src/huffman.cpp";
    string linea_texto;
    string texto_final;

    ficheroEntrada.open(nombre.c_str(), ios::in);
    if (ficheroEntrada.is_open())
    {
        while (!ficheroEntrada.eof())
        {
            getline(ficheroEntrada, linea_texto);
            texto_final += linea_texto + "\n";
        }
        ficheroEntrada.close();
    }
    else
    {
        std::cout << "Fichero inexistente o faltan permisos para abrirlo" << endl;
    }

    buildHuffmanTree(texto_final);
    string cod_binario = pedir_codigoBinario();
    string sim_cod = pedir_simboloCodigo();
    string cadena_descomprimida = descomprimir_data(cod_binario, sim_cod);

    if (cadena_descomprimida == texto_final)
    {
        cout << "Las cadenas son iguales" << endl;
    }
    else
    {
        cout << "Las cadenas NO son iguales" << endl;
    }

    // Copiar datos en txt
    ofstream fs("/home/davidaqc/Documents/Got-SVN/client/src/prueba.txt");
    fs << cadena_descomprimida << endl;
    fs.close();

    // ------ Codigo para probar MD5 ----------------

    string password = md5("1123");
    cout << password << endl;

    return 0;
}