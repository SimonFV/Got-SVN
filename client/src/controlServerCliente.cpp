#include <client.hpp>
#include <controlServerCliente.hpp>

// Listar los directorios que hay dentro
void ControlServerCliente::list_dir(string dir) {
    dir = Command::thisPath;
    DIR * directorio;
    struct dirent * elemento;
    string elem;

    if((directorio=opendir(dir.c_str()))) {
        while ((elemento=readdir(directorio))) {
            elem=elemento->d_name;
            if (elem !="."&& elem !=".."){
                control_local_server (elem, "local");
            } 
        }
    }
    closedir(directorio);
}

void ControlServerCliente::control_local_server (string elem, string tipo_control){

    ifstream ifs(Command::thisPath + ".got/control_cliente.json");
    Json::Reader reader;
    Json::Value  root;
    reader.parse(ifs, root); 
    Json::StyledStreamWriter writer;
    std::ofstream outFile;

    bool guardar = true;
    // No copiar los archivos nuevamente
    for (Json::Value::const_iterator it=root["archivos"].begin(); it!=root["archivos"].end(); ++it){
            if(it.key().asString() == elem){
                guardar = false;
            }    
    }

    if(guardar){
            root["archivos"][elem] = "no_controlado";
    }

    outFile.open(Command::thisPath + ".got/control_cliente.json");
    writer.write(outFile, root);
    outFile.close();
}

void ControlServerCliente::escribir_json(string ruta, Json::Value root){

    Json::StyledStreamWriter writer;
    std::ofstream outFile;
    outFile.open(Command::thisPath + ruta);
    writer.write(outFile, root);
    outFile.close();

}

std::string ControlServerCliente::leer_json(string ruta, string llave){

    ifstream ifs(Command::thisPath + ruta);
    Json::Reader reader;
    Json::Value  root;
    reader.parse(ifs, root); 
    
    return root[llave].asString();

}

std::string ControlServerCliente::leer_json2(string ruta, string key){

    ifstream ifs(Command::thisPath + ruta);
    Json::Reader reader;
    Json::Value  root;
    reader.parse(ifs, root); 
    const Json::Value& characters = root["rows"]; // array of characters
    string valor;
    for (int i = 0; i < characters.size(); i++){
        for (Json::Value::const_iterator it=characters[i].begin(); it!=characters[i].end(); ++it){
            if(it.key().asString()==key){
                valor = it->asString();
                break;
            }     
        } 
    }

    return valor;

}