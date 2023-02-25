#include "scanner.hh"
#include "parser.hh"
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
    Scanner scanner = Scanner(s);
    try {
        scanner.scan();
        scanner.printTokens();
        //std::cout << std::endl;
        //scanner.printLexemes();
    } catch(const char* ex) {
        std::cout << ex << '\n';
    }

    auto tokens = scanner.getTokens();
    auto lexemes = scanner.getLexemes();

    Parser parser = Parser(tokens, lexemes);
    try {
        auto json = parser.parse();
        json->print();
    } catch(const char* err) {
        std::cout << err << '\n';
    }
}