
#include <client.hpp>

using namespace std;

void diff(string fileAfter, string fileBefore, string patch)
{
    string command = "diff -e " + fileBefore + " " + fileAfter + " > " + patch;
    system(command.c_str());
}

void applyChanges(string original, string changes)
{
    string command = "patch " + original + " " + changes;
    system(command.c_str());
}
