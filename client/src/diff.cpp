
#include <client.hpp>

using namespace std;

void diff(string fileAfter, string fileBefore, string patch)
{
    string command = "diff -e " + fileBefore + " " + fileAfter + " > " + patch;
    int sin_uso = system(command.c_str());
}

void applyChanges(string original, string changes)
{
    string command = "patch " + original + " " + changes;
    int sin_uso =  system(command.c_str());
}

string get_selfpath()
{
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    return std::string(result, (count > 0) ? count : 0);
}