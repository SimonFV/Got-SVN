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
};

#endif