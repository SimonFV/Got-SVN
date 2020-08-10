
#include <client.hpp>
#include <controlServerCliente.hpp>

using namespace std;

string Command::thisPath = "";
ControlServerCliente control;

string Command::diff_a_string()
{

    fstream ficheroEntrada;
    string linea_texto = "";
    string texto_final = "";

    ficheroEntrada.open(Command::thisPath + "../repo/test.patch", ios::in);
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
        spdlog::error("Fichero inexistente o faltan permisos para abrirlo (Diff)");
    }
    texto_final.erase(texto_final.size() - 1);
    return texto_final;
}

void Command::diff(string fileAfter, string fileBefore, string patch)
{
    string command = "diff -e " + fileBefore + " " + fileAfter + " > " + patch;
    int sin_uso = system(command.c_str());
}

void Command::applyChanges(string original, string changes)
{
    string command = "patch " + original + " " + changes;
    int sin_uso = system(command.c_str());
}

string Command::get_selfpath()
{
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    return std::string(result, (count > 0) ? count : 0);
}

void Command::init(string repoName)
{
    if (mkdir(".got", 0777) == -1)
    {
        spdlog::error("Error : {}", strerror(errno));
    }
    else
    {
        spdlog::info("Directorio .got creado");
    }

    ofstream file;
    file.open(thisPath + ".gotignore");
    file.close();
    spdlog::info("Agregado el archivo .gotignore");

    //Agrega los archivos JSON
    file.open(thisPath + ".got/enviado.json");
    file.close();
    file.open(thisPath + ".got/recibido.json");
    file.close();
    file.open(thisPath + ".got/control_cliente.json");
    file.close();

    // Crea la estructura control cliente-server
    Json::Value root;
    root["id_repositorio"] = 0;
    root["commit"] = 0;
    root["hash_commit"] = "";
    root["archivos"];
    control.escribir_json(".got/control_cliente.json", root);

    // Agregar directorios al json
    const char *dir_name = thisPath.c_str();
    control.list_dir(dir_name);

    // Escribe la estructura repositorio y envia datos
    Json::Value root0;
    root0["nombre_repositorio"] = repoName;
    control.escribir_json(".got/enviado.json", root0);
    Client::getI()->POST("repositorio", thisPath + ".got/enviado.json");
    spdlog::info("Repositorio agregado en el server!");
    spdlog::info(Client::getI()->getStatus());

    // Guardar el # del repositorio
    string dato_retornado = control.leer_json(".got/recibido.json", "id_repositorio");
    // Leer archivo para acualizarlo
    ifstream ifs1(Command::thisPath + ".got/control_cliente.json");
    Json::Reader reader1;
    Json::Value root1;
    reader1.parse(ifs1, root1);
    root1["id_repositorio"] = dato_retornado;
    control.escribir_json(".got/control_cliente.json", root1);
}

void Command::add(string solicitud_archivos)
{
    // Antes de agregar agregar los archivos, actualizar directorio
    const char *dir_name = thisPath.c_str();
    control.list_dir(dir_name);

    // Leer control_cliente.json
    ifstream ifs(Command::thisPath + ".got/control_cliente.json");
    Json::Reader reader;
    Json::Value root;
    reader.parse(ifs, root);
    bool archivo_existente = true;

    if (solicitud_archivos == "-A")
    {
        string aux = "archivos";
        for (Json::Value::const_iterator it = root[aux].begin(); it != root[aux].end(); ++it)
        {

            if (root["archivos"][it.key().asString()] == "no_controlado")
            {
                root["archivos"][it.key().asString()] = "agregado";
                spdlog::info("Archivo agregado!");
            }
            else if (root["archivos"][it.key().asString()] == "server")
            {
                root["archivos"][it.key().asString()] = "modificado";
                spdlog::info("El archivo ha sido modificado!");
            }
            else if (root["archivos"][it.key().asString()] == "agregado")
            {
                spdlog::info("El archivo ya ha sido agregado!");
            }
        }
    }
    else
    {
        //Agregar uno
        if (root["archivos"][solicitud_archivos] == "no_controlado")
        {
            root["archivos"][solicitud_archivos] = "agregado";
            spdlog::info("Archivo agregado!");
        }
        else if (root["archivos"][solicitud_archivos] == "server")
        {
            root["archivos"][solicitud_archivos] = "modificado";
            spdlog::info("El archivo ha sido modificado!");
        }
        else if (root["archivos"][solicitud_archivos] == "agregado")
        {
            spdlog::info("El archivo ya ha sido agregado!");
        }
        else
        {
            archivo_existente = false;
            spdlog::info("El archivo no existe!");
        }
    }

    if (archivo_existente == true)
    {
        control.escribir_json(".got/control_cliente.json", root);
    }
}

void Command::commit(string comentario)
{

    // Guardar el # repo actual
    string repo_actual = control.leer_json(".got/control_cliente.json", "id_repositorio");

    // Guardar el # commit actual
    string dato_retornado = control.leer_json(".got/control_cliente.json", "commit");
    string dato_retornado2;

    int relacion_actual_commit = stoi(dato_retornado) + 1;

    // Escribe la estructura commit y envia datos
    Json::Value root;
    root["hash_commit"] = relacion_actual_commit;
    root["comentario"] = comentario;
    root["relacion_repositorio"] = stoi(repo_actual);
    control.escribir_json(".got/enviado.json", root);
    Client::getI()->POST("commit", thisPath + ".got/enviado.json");
    spdlog::info("Commit agregado en el server!");
    spdlog::info(Client::getI()->getStatus());

    // Guardar HASH generado
    dato_retornado = control.leer_json(".got/recibido.json", "hash_commit");

    // Leer archivo para acualizarlo
    ifstream ifs1(Command::thisPath + ".got/control_cliente.json");
    Json::Reader reader1;
    Json::Value root1;
    reader1.parse(ifs1, root1);
    root1["hash_commit"] = dato_retornado;
    root1["commit"] = relacion_actual_commit;
    control.escribir_json(".got/control_cliente.json", root1);

    // Enviar archivos
    string aux = "archivos";
    string texto_final;
    string cod_binario;
    string sim_cod;
    for (Json::Value::const_iterator it = root1[aux].begin(); it != root1[aux].end(); ++it)
    {

        if (root1["archivos"][it.key().asString()] == "agregado")
        {
            // Comprimir datos
            texto_final = generar_string_de_archivo(Command::thisPath + it.key().asString());
            buildHuffmanTree(texto_final);
            cod_binario = pedir_codigoBinario();
            sim_cod = pedir_simboloCodigo();

            // Escribe la estructura  archivo y envia datos
            Json::Value root2;
            root2["nombre_archivo"] = it.key().asString();
            root2["codigo_huffman"] = cod_binario;
            root2["simbolo_codigo"] = sim_cod;
            root2["relacion_commit"] = relacion_actual_commit;
            control.escribir_json(".got/enviado.json", root2);

            Client::getI()->POST("archivo", thisPath + ".got/enviado.json");
            spdlog::info("Archivo agregado en el server!");
            spdlog::info(Client::getI()->getStatus());

            // Cambiar estado agregado -> server
            root1["archivos"][it.key().asString()] = "server";
            control.escribir_json(".got/control_cliente.json", root1);
        }
        else if (root1["archivos"][it.key().asString()] == "modificado")
        {
            string comparacion_diff;
            if (relacion_actual_commit == 2)
            {
                spdlog::info("Agregando diff's del commit 2!");
                // Pedir Huffman del commit 1
                Json::Value root3;
                root3["id_commit"] = 1; // Directamente al commit 1
                root3["nombre_archivo"] = it.key().asString();
                control.escribir_json(".got/enviado.json", root3);
                Client::getI()->GET("codigo_huffman", thisPath + ".got/enviado.json");
                spdlog::info("Obteniendo codigo huffman!");
                spdlog::info(Client::getI()->getStatus());
                // Guardar hufmman
                dato_retornado = control.leer_json2(".got/recibido.json", "CONVERT(archivo.codigo_huffman USING utf8)");
                dato_retornado2 = control.leer_json2(".got/recibido.json", "simbolo_codigo");
                // Crear archivo con huffman
                ofstream fs(Command::thisPath + "../repo/" + it.key().asString());
                fs << descomprimir_data(dato_retornado, dato_retornado2);
                fs.close();

                // Saca diferencias del Antes con el Despues. Poner RUTA DESPUES, LUEGO RUTA ANTES
                Command::diff(Command::thisPath + it.key().asString(),
                              Command::thisPath + "../repo/" + it.key().asString(),
                              Command::thisPath + "../repo/test.patch");

                comparacion_diff = Command::diff_a_string();
            }
            else
            {
                spdlog::info("Agregando diff's del commit 2!");
                // Pedir diferencias (diff anterior)
                // Escribe la estructura diff_anterior y envia datos
                Json::Value root4;
                root4["id_commit"] = relacion_actual_commit - 1; // Se resta 1 para obtener diff_anterior
                root4["nombre_archivo"] = it.key().asString();
                control.escribir_json(".got/enviado.json", root4);
                Client::getI()->GET("commit_anterior", thisPath + ".got/enviado.json");
                spdlog::info("Obteniendo codigo diff!");
                spdlog::info(Client::getI()->getStatus());
                // Obtener codigo_diff_anterior
                dato_retornado = control.leer_json2(".got/recibido.json", "codigo_diff_anterior");

                // Para revisar si hay cambios
                // Copiar codigo_diff_anterio en test.patch
                ofstream fs(Command::thisPath + "../repo/test.patch");
                fs << dato_retornado;
                fs.close();

                // Regresar el archivo al commmit pasado
                Command::applyChanges(Command::thisPath + "../repo/" + it.key().asString(),
                                      Command::thisPath + "../repo/test.patch");

                // Compararlo con el actual
                Command::diff(Command::thisPath + it.key().asString(),
                              Command::thisPath + "../repo/" + it.key().asString(),
                              Command::thisPath + "../repo/test.patch");

                comparacion_diff = Command::diff_a_string();
            }

            // Si el archivo .patch esta en blanco, no hay diferencia
            if (comparacion_diff == "")
            {
                spdlog::info("No hay cambios en el archivo!");
            }
            else
            {
                // Sacar MD5
                string codigo_checksum = md5(to_string(relacion_actual_commit));

                // Escribe la estructura diff y envia datos
                Json::Value root5;
                root5["nombre_archivo"] = it.key().asString();
                root5["codigo_diff_anterior"] = comparacion_diff;
                root5["codigo_diff_posterior"] = ""; // Va vacio, el proximo commit lo actualiza
                root5["checksum"] = codigo_checksum;
                root5["relacion_commit"] = relacion_actual_commit;
                control.escribir_json(".got/enviado.json", root5);

                Client::getI()->POST("diff", thisPath + ".got/enviado.json");
                spdlog::info("Diff agregado en el server!");
                spdlog::info(Client::getI()->getStatus());
            }

            // Cambiar estado modificado -> server
            root1["archivos"][it.key().asString()] = "server";
            control.escribir_json(".got/control_cliente.json", root1);
        }
    }
}