
#include <client.hpp>
#include <huffman.hpp>
#include "md5.h"

int main(int argc, char *argv[])
{

    diff("/home/simon/Cpp/Got-SVN/client/repo/testAfter.cpp",
         "/home/simon/Cpp/Got-SVN/client/repo/testBefore.cpp",
         "/home/simon/Cpp/Got-SVN/client/repo/test.patch");

    applyChanges("/home/simon/Cpp/Got-SVN/client/repo/testBefore.cpp",
                 "/home/simon/Cpp/Got-SVN/client/repo/test.patch");

    /*
    //POST
    {
        std::cout << "Action: Create Product with Id = 1" << std::endl;
        auto r = cpr::Post(cpr::Url{"http://localhost:51654/api/products/create"},
                           cpr::Body{R"({"Id":1, 
            "Name":"ElectricFan","Qty":14,"Price":20.90})"},
                           cpr::Header{{"Content-Type", "application/json"}});
        std::cout << "Returned Status:" << r.status_code << std::endl;
    }
    

    //GET
    {
        spdlog::info("GET REQUEST");

        auto r = cpr::Get(cpr::Url{"http://localhost:4000"});

        spdlog::info("Returned Text: {}", r.text);
    }

    
    {
        std::cout << "Action: Update Product with Id = 1" << std::endl;
        auto r = cpr::Post(cpr::Url{"http://localhost:51654/api/products/1"},
                           cpr::Body{R"({"Id":1, 
            "Name":"ElectricFan","Qty":15,"Price":29.80})"},
                           cpr::Header{{"Content-Type", "application/json"}});
        std::cout << "Returned Status:" << r.status_code << std::endl;
    }
    {
        std::cout << "Action: Retrieve all products" << std::endl;
        auto r = cpr::Get(cpr::Url{"http://localhost:51654/api/products"});
        std::cout << "Returned Text:" << r.text << std::endl;
    }
    {
        std::cout << "Action: Delete the product with id = 1" << std::endl;
        auto r = cpr::Delete(cpr::Url{"http://localhost:51654/api/products/1"});
        std::cout << "Returned Status:" << r.status_code << std::endl;
    }
    {
        std::cout << "Action: Retrieve all products" << std::endl;
        auto r = cpr::Get(cpr::Url{"http://localhost:51654/api/products"});
        std::cout << "Returned Text:" << r.text << std::endl;
    }
    */

    // ------ Codigo para probar Huffman ----------------

    fstream ficheroEntrada;
    string nombre = "/home/davidaqc/Documents/Got-SVN/client/src/huffman.cpp";
    string linea_texto;
    string texto_final;
 
    ficheroEntrada.open ( nombre.c_str() , ios::in);
    if (ficheroEntrada.is_open()) {
        while (! ficheroEntrada.eof() ) {
            getline (ficheroEntrada,linea_texto);
            texto_final += linea_texto + "\n";
        }
        ficheroEntrada.close();
    }else{
        std::cout << "Fichero inexistente o faltan permisos para abrirlo" << endl;  
    }

	buildHuffmanTree(texto_final); 
	string cod_binario = pedir_codigoBinario(); 
	string sim_cod = pedir_simboloCodigo();
	string cadena_descomprimida = descomprimir_data(cod_binario, sim_cod);

	if(cadena_descomprimida==texto_final){
		cout << "Las cadenas son iguales" << endl;
	}else{
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