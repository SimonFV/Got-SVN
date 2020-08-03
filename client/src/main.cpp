
#include <client.hpp>

int main(int argc, char *argv[])
{
    string thisPath = get_selfpath();
    thisPath.erase(thisPath.length() - 3, thisPath.length());
    spdlog::info(thisPath);

    if (argc < 2)
    {
        spdlog::warn("Argumentos insuficientes.");
        spdlog::info("Para ver la lista de opciones disponibles utilice el comando: ./got help");
    }
    else if (!strcmp(argv[1], "init"))
    {
        if (argc != 3)
        {
            spdlog::warn("Indique un nombre para el repositorio.");
            spdlog::info("Para ver la lista de opciones disponibles utilice el comando: ./got help");
        }
        else
        {
            spdlog::info("Iniciando el repositorio en la ruta actual.");
            //INICIA EL REPOSITORIO
            spdlog::info("Repositorio {} listo.", argv[2]);
        }
    }
    else if (!strcmp(argv[1], "add"))
    {
        if (argc < 3)
        {
            spdlog::warn("Indique cuales archivos desea agregar.");
            spdlog::info("Para ver la lista de opciones disponibles utilice el comando: ./got help");
        }
        else if (!strcmp(argv[2], "-A"))
        {
            //AGREGANDO TODOS LOS ARCHIVOS
            spdlog::info("Agregando todos los archivos al commit.");
        }
        else
        {
            for (int i = 2; i < argc; i++)
            {
                //AGREGANDO ARCHIVO
                spdlog::info("Agregando el archivo {} al commit.", argv[i]);
            }
        }
    }
    else if (!strcmp(argv[1], "commit"))
    {
        if (argc < 3)
        {
            spdlog::warn("Agregue un mensaje para el commit.");
            spdlog::info("Para ver la lista de opciones disponibles utilice el comando: ./got help");
        }
        else
        {
            string msg = "";
            for (int i = 2; i < argc; i++)
            {
                msg += argv[i];
                msg += " ";
            }
            //REALIZA EL COMMIT
            spdlog::info("Commit realizado: {}", msg);
        }
    }
    else if (!strcmp(argv[1], "status"))
    {
        if (argc < 3)
        {
            spdlog::info("Mostrando historial completo...");
            //MOSTRAR HISTORIAL PARA TODOS LOS ARCHIVOS
        }
        else if (argc > 3)
        {
            spdlog::warn("Indique únicamente un archivo para mostrar.");
            spdlog::info("Para ver la lista de opciones disponibles utilice el comando: ./got help");
        }
        else
        {
            spdlog::info("Mostrando historial para {}", argv[2]);
            //MOSTRAR HISTORIAL PARA 1 ARCHIVO
        }
    }
    else if (!strcmp(argv[1], "rollback"))
    {
        if (argc < 3)
        {
            spdlog::warn("Especifique el commit.");
            spdlog::info("Para ver la lista de opciones disponibles utilice el comando: ./got help");
        }
        else if (argc > 4)
        {
            spdlog::warn("Especifique únicamente un commit y un archivo.");
            spdlog::info("Para ver la lista de opciones disponibles utilice el comando: ./got help");
        }
        else if (argc == 3)
        {
            spdlog::info("Regresando todos los archivos al commit {}", argv[2]);
            //DEVOLVER LOS ARCHIVOS AL COMMIT ESPECIFICO
        }
        else
        {
            spdlog::info("Regresando el archivo {} al commit {}", argv[3], argv[2]);
            //DEVOLVER EL ARCHIVO AL COMMIT ESPECIFICO
        }
    }
    else if (!strcmp(argv[1], "reset"))
    {
        if (argc < 3)
        {
            spdlog::info("Regresando todos los archivos al commit anterior.");
            //DEVOLVER LOS ARCHIVOS AL COMMIT ANTERIOR
        }
        else if (argc == 3)
        {
            spdlog::info("Regresando el archivo {} al commit anterior.", argv[2]);
            //DEVOLVER EL ARCHIVO AL COMMIT ANTERIOR
        }
        else
        {
            spdlog::warn("Especifique únicamente un archivo.");
            spdlog::info("Para ver la lista de opciones disponibles utilice el comando: ./got help");
        }
    }
    else if (!strcmp(argv[1], "sync"))
    {
        if (argc != 3)
        {
            spdlog::warn("Especifique un archivo.");
            spdlog::info("Para ver la lista de opciones disponibles utilice el comando: ./got help");
        }
        else
        {
            spdlog::info("Sincronizando el archivo {}", argv[2]);
            //SINCRONIZA EL ARCHIVO Y PERMITE EL MERGE
        }
    }
    else if (!strcmp(argv[1], "help"))
    {
        string help = R"(

    LISTA DE COMANDOS DISPONIBLES PARA GOT:

    1. ./got init <nombre> : Inicia el repositorio en la ruta actual y lo identifica con <nombre>.

    2. ./got add -A                    : Agrega todos los archivos locales para el siguiente commit.
       ./got add <archivo1> <archivo2> : Agrega los <archivo>s para el siguiente commit.

    3. ./got commit <mensaje> : Realiza el commit de los archivos agregados con el <mensaje>.

    4. ./got status           : Muestra cuales archivos han sido modificados de acuerdo al commit anterior.
       ./got status <archivo> : Muestra los cambios realizados al <archivo> en base al commit anterior.
        
    5. ./got rollback <commit>           : Permite regresar los archivos al <commit>.
       ./got rollback <commit> <archivo> : Permite regresar el <archivo> al <commit>.

    6. ./got reset           : Deshace cambios locales y los regresa al último commit.
       ./got reset <archivo> : Deshace cambios locales para el <archivo> y lo regresa al último commit.
        
    7. ./got sync <archivo> : Sincroniza el <archivo> en el servidor con el local. Permite realizar un merge.
    )";
        spdlog::info(help);
    }
    else
    {
        spdlog::warn("Comando incorrecto.");
        spdlog::info("Para ver la lista de opciones disponibles utilice el comando: ./got help");
    }

    diff(thisPath + "../repo/testAfter.cpp",
         thisPath + "../repo/testBefore.cpp",
         thisPath + "../repo/test.patch");

    applyChanges(thisPath + "../repo/testBefore.cpp",
                 thisPath + "../repo/test.patch");

    /*
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
    */
    return 0;
}