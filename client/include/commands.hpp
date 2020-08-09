#ifndef COMMANDS_H
#define COMMANDS_H

#include <client.hpp>

class Command
{
public:
    static string thisPath;
    static void diff(string fileAfter, string fileBefore, string result);
    static void applyChanges(string original, string changes);
    static string get_selfpath();
    static void init(string repoName);
    static void add(string archivos);
    static void commit(string mensaje);
    static string diff_a_string();
};

#endif