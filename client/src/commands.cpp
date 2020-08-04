
#include <client.hpp>

using namespace std;

string Command::thisPath = "";

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
}