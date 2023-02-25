#include "scanner.hh"
#include <string>
#include <vector>
#include <iostream>

int main()
{
    std::string s = "{ [ , 2, 2,, 4.43 : \"hellow\" ]}";
    Scanner scanner = Scanner(s);
    try {
        scanner.scan();
        scanner.printTokens();
        std::cout << std::endl;
        scanner.printLexemes();
    } catch(std::string& ex) {
        std::cout << ex << '\n'; } }