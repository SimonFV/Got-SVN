
#include <client.hpp>

int main(int argc, char *argv[])
{
    /*
    //POST
    {
        std::cout << "Action: Create Product with Id = 1" << std::endl;
        auto r = cpr::Post(cpr::Url{"http://localhost:51654/api/products/create"},
                           cpr::Body{R"({"Id":1, 
            "Name":"ElectricFan","Qty":14,"Price":20.90})"},
                           cpr::Header{{"Content-Type", "application/json"}});
        std::cout << "Returned Status:" << r.status_code << std::endl;
    }
    */

    //GET
    {
        spdlog::info("GET REQUEST");

        auto r = cpr::Get(cpr::Url{"http://localhost:3000"});

        spdlog::info("Returned Text: {}", r.text);
    }

    /*
    {
        std::cout << "Action: Update Product with Id = 1" << std::endl;
        auto r = cpr::Post(cpr::Url{"http://localhost:51654/api/products/1"},
                           cpr::Body{R"({"Id":1, 
            "Name":"ElectricFan","Qty":15,"Price":29.80})"},
                           cpr::Header{{"Content-Type", "application/json"}});
        std::cout << "Returned Status:" << r.status_code << std::endl;
    }
    {
        std::cout << "Action: Retrieve all products" << std::endl;
        auto r = cpr::Get(cpr::Url{"http://localhost:51654/api/products"});
        std::cout << "Returned Text:" << r.text << std::endl;
    }
    {
        std::cout << "Action: Delete the product with id = 1" << std::endl;
        auto r = cpr::Delete(cpr::Url{"http://localhost:51654/api/products/1"});
        std::cout << "Returned Status:" << r.status_code << std::endl;
    }
    {
        std::cout << "Action: Retrieve all products" << std::endl;
        auto r = cpr::Get(cpr::Url{"http://localhost:51654/api/products"});
        std::cout << "Returned Text:" << r.text << std::endl;
    }
    */
    return 0;
}