#pragma once

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include "token.hh"

namespace Json {

class Value;
class StringValue;
class IntValue;
class BoolValue;
class FloatValue;
class NullValue;
class ListValue;
class ObjectValue;

class Parser
{
private:
    std::size_t  currTok;
    std::size_t currLex;
    std::vector<Token> tokens;
    std::vector<std::string> lexemes;
public:
    Parser(std::vector<Token>& tok, std::vector<std::string>&);
    std::unique_ptr<ObjectValue> parse();
private:
    std::string parseKey();

    std::unique_ptr<Value> parseValue();
    std::unique_ptr<StringValue> parseString();
    std::unique_ptr<IntValue> parseInt(bool isPos);
    std::unique_ptr<FloatValue> parseFloat(bool isPos);
    std::unique_ptr<BoolValue> parseTrue();
    std::unique_ptr<BoolValue> parseFalse();
    std::unique_ptr<NullValue> parseNull();
    std::unique_ptr<ListValue> parseList();
    std::unique_ptr<ObjectValue> parseObj();

    bool matchCurr(Tokentype) noexcept;
};
}