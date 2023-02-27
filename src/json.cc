#include "parser.hh"
#include "scanner.hh"
#include "json.hh"
#include "value.hh"

namespace Json {

JsonObj::JsonObj(std::string inp): input(inp)
{
}

std::unique_ptr<ObjectValue> JsonObj::parse()
{
    // first create the scanner
    std::unique_ptr<Scanner> scanner = std::make_unique<Scanner>(input);
    scanner->scan();
    std::vector<Token> tokens = scanner->getTokens();
    std::vector<std::string> lexemes = scanner->getLexemes();
    std::unique_ptr<Parser> parser = std::make_unique<Parser>(tokens, lexemes);
    return parser->parse();
}

std::unique_ptr<Value> JsonObj::get(std::string k)
{
    return object->get(k);
}

}