
#include <client.hpp>
#include <jsoncons/json.hpp>

int main(int argc, char *argv[])
{

    /*
    diff("/home/simon/Cpp/Got-SVN/client/repo/testAfter.cpp",
         "/home/simon/Cpp/Got-SVN/client/repo/testBefore.cpp",
         "/home/simon/Cpp/Got-SVN/client/repo/test.patch");

    applyChanges("/home/simon/Cpp/Got-SVN/client/repo/testBefore.cpp",
                 "/home/simon/Cpp/Got-SVN/client/repo/test.patch");
    

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

    return 0;
    */
}