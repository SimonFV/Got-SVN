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

    int guarda_noGuarda;
    if(tipo_control=="local"){
        for(int i=0; i<4; i++){
            if(i==0){
                guarda_noGuarda = auxiliar_control_local_server(elem, "archivos_del_cliente");
            }else if(i==1){
                guarda_noGuarda = auxiliar_control_local_server(elem, "archivos_agregados");
            }else if(i==2){
                guarda_noGuarda = auxiliar_control_local_server(elem, "archivos_del_server");
            }else{
                guarda_noGuarda = auxiliar_control_local_server(elem, "archivos_posibles_modificados");
            }

            if(guarda_noGuarda==1){
                break;
            }
        }

        if(guarda_noGuarda==-1){
            root["archivos_del_cliente"][elem];
        }

    }else{
        bool verificar_existencia = false;
        string aux = "archivos_del_cliente";
        for (Json::Value::const_iterator it=root[aux].begin(); it!=root[aux].end(); ++it){
            if(it.key().asString() == elem){
                verificar_existencia = true;
                break;
            }
        }
        if(verificar_existencia==true){
            for(int i=0; i<2; i++){
                if(i==0){
                    guarda_noGuarda = auxiliar_control_local_server(elem, "archivos_del_server");
                    if(guarda_noGuarda==1){
                        root["archivos_posibles_modificados"][elem];
                    }
                }else if(i==1 && guarda_noGuarda!=1){
                    guarda_noGuarda = auxiliar_control_local_server(elem, "archivos_agregados");
                    if(guarda_noGuarda==-1){
                        root["archivos_agregados"][elem];
                    }
                }
            }
        }else{
            spdlog::warn("El archivo no existe!");
        }

    }

    outFile.open(Command::thisPath + ".got/control_cliente.json");
    writer.write(outFile, root);
    outFile.close();
}

int ControlServerCliente::auxiliar_control_local_server(string elem, string key){

    ifstream ifs(Command::thisPath + ".got/control_cliente.json");
    Json::Reader reader;
    Json::Value  root;
    reader.parse(ifs, root); 

    bool agregar_archivo;

    // No copiar los archivos locales nuevamente
    agregar_archivo = true;
    for (Json::Value::const_iterator it=root[key].begin(); it!=root[key].end(); ++it){
            if(it.key().asString() == elem){
                agregar_archivo = false;
                return 1;
            }
    }

    return -1;
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