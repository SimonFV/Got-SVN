#include <client.hpp>
#include <controlServerCliente.hpp>

// Listar los directorios que hay dentro
void ControlServerCliente::list_dir(const char *dir_name)
{
    DIR *d;
    d = opendir(dir_name);
    if (!d)
    {
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        struct dirent *entry;
        const char *d_name;
        entry = readdir(d);
        if (!entry)
        {
            break;
        }
        d_name = entry->d_name;

        if (!(entry->d_type & DT_DIR))
        {
            string ruta1 = dir_name;
            string ruta2 = d_name;
            string ruta3 = ruta1 + "/" + ruta2;

            string quitar_ruta_actual = Command::thisPath;
            control_local_server(ruta3.erase(0, quitar_ruta_actual.size()));
        }

        if (entry->d_type & DT_DIR)
        {
            if (strcmp(d_name, "..") != 0 &&
                strcmp(d_name, ".") != 0)
            {
                int path_length;
                char path[PATH_MAX];

                path_length = snprintf(path, PATH_MAX,
                                       "%s/%s", dir_name, d_name);
                if (path_length >= PATH_MAX)
                {
                    exit(EXIT_FAILURE);
                }
                list_dir(path);
            }
        }
    }
    
    if (closedir(d))
    {
        exit(EXIT_FAILURE);
    }
}

void ControlServerCliente::control_local_server(string elem)
{

    ifstream ifs(Command::thisPath + ".got/control_cliente.json");
    Json::Reader reader;
    Json::Value root;
    reader.parse(ifs, root);
    Json::StyledStreamWriter writer;
    std::ofstream outFile;

    bool guardar = true;
    // No copiar los archivos nuevamente
    for (Json::Value::const_iterator it = root["archivos"].begin(); it != root["archivos"].end(); ++it)
    {
        if (it.key().asString() == elem)
        {
            guardar = false;
        }
    }

    if (guardar)
    {
        root["archivos"][elem] = "no_controlado";
    }

    outFile.open(Command::thisPath + ".got/control_cliente.json");
    writer.write(outFile, root);
    outFile.close();
}

void ControlServerCliente::escribir_json(string ruta, Json::Value root)
{

    Json::StyledStreamWriter writer;
    std::ofstream outFile;
    outFile.open(Command::thisPath + ruta);
    writer.write(outFile, root);
    outFile.close();
}

std::string ControlServerCliente::leer_json(string ruta, string llave)
{

    ifstream ifs(Command::thisPath + ruta);
    Json::Reader reader;
    Json::Value root;
    reader.parse(ifs, root);

    return root[llave].asString();
}

std::string ControlServerCliente::leer_json2(string ruta, string key)
{

    ifstream ifs(Command::thisPath + ruta);
    Json::Reader reader;
    Json::Value root;
    reader.parse(ifs, root);
    const Json::Value &characters = root["rows"]; // array of characters
    string valor;
    for (int i = 0; i < characters.size(); i++)
    {
        for (Json::Value::const_iterator it = characters[i].begin(); it != characters[i].end(); ++it)
        {
            if (it.key().asString() == key)
            {
                valor = it->asString();
                break;
            }
        }
    }

    return valor;
}