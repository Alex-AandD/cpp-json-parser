#include "json.hh"
#include "value.hh"
#include <string>
#include <vector>
#include <iostream>

using namespace Json;
int main()
{
    std::string s = "{" 
            "\"firstName\" : \"alex\" ,"
            "\"lastName\" : \"aleksandrov\" ,"
            "\"age\" : 15 ,"
            "\"skills\" : {" 
            "    \"math\" : true ,"
            "    \"programming\" : false }"
            "}";
    JsonObj json = JsonObj(s);
    try {
        auto v = json.parse();
        auto v1 = v->get("firstName");
        v1->print();
    } catch(const char* ex)
    {
        std::cout << ex << '\n';
    }
}