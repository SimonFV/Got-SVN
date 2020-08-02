#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <fstream>
#include <string>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <cpr/cpr.h>

using namespace std;

void diff(string fileAfter, string fileBefore, string result);

void applyChanges(string original, string changes);

//HTML REQUESTS

//POST
class Client
{
    static void send()
    {
        std::cout << "Action: Create Product with Id = 1" << std::endl;
        cpr::Response r = cpr::Post(cpr::Url{"http://localhost:4000"},
                                    cpr::Body{R"(
                                    {
                                        "Id":1,
                                        "Name":"ElectricFan",
                                        "Qty":14,
                                        "Price":20.90
                                    }
                                    )"},
                                    cpr::Header{{"Content-Type", "application/json"}});
        std::cout << "Returned Status:" << r.status_code << std::endl;

        //GET

        spdlog::info("GET REQUEST");

        cpr::Response r1 = cpr::Get(cpr::Url{"http://localhost:4000"});

        spdlog::info("Returned Text: {}", r.text);

        std::cout << "Action: Update Product with Id = 1" << std::endl;
        cpr::Response r2 = cpr::Post(cpr::Url{"http://localhost:51654/api/products/1"},
                                     cpr::Body{R"({"Id":1, 
            "Name":"ElectricFan","Qty":15,"Price":29.80})"},
                                     cpr::Header{{"Content-Type", "application/json"}});
        std::cout << "Returned Status:" << r.status_code << std::endl;

        std::cout << "Action: Retrieve all products" << std::endl;
        cpr::Response r3 = cpr::Get(cpr::Url{"http://localhost:51654/api/products"});
        std::cout << "Returned Text:" << r.text << std::endl;

        std::cout << "Action: Delete the product with id = 1" << std::endl;
        cpr::Response r4 = cpr::Delete(cpr::Url{"http://localhost:51654/api/products/1"});
        std::cout << "Returned Status:" << r.status_code << std::endl;

        std::cout << "Action: Retrieve all products" << std::endl;
        cpr::Response r5 = cpr::Get(cpr::Url{"http://localhost:51654/api/products"});
        std::cout << "Returned Text:" << r.text << std::endl;
    }
};

#endif