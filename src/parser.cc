#include "parser.hh"
#include "value.hh"
#include <iostream>

namespace Json {
Parser::Parser(std::vector<Token>& t, std::vector<std::string>& l)
    : tokens(t), lexemes(l), currTok(0), currLex(0)
{

}

bool Parser::matchCurr(Tokentype t) noexcept {
    if (currTok >= tokens.size()) return false;
    if (tokens[currTok].t == t)
    {
        currTok++;
        return true;
    }
    return false;
}

std::unique_ptr<ObjectValue> Parser::parse()
{
    return parseObj();
}

std::unique_ptr<ObjectValue> Parser::parseObj()
{
    std::unordered_map<std::string, std::unique_ptr<Value>> map;
    if (matchCurr(Tokentype::LBR))
    {
        do {
            std::string key = parseKey(); 
            if (!matchCurr(Tokentype::SEMI))
            {
                throw("missing semicolon");
            }
            std::unique_ptr<Value> val = parseValue();

            // insert key and value into the object
            map[key] = std::move(val);
        } while(matchCurr(Tokentype::COMA));
    }

    if (matchCurr(Tokentype::RBR))
    {
        return std::make_unique<ObjectValue>(map);
    }
    throw("missing closing bracket");
}

std::string Parser::parseKey()
{
    if (matchCurr(Tokentype::STRING))
    {
        // get the lexeme
        std::string l = lexemes[currLex];
        currLex++;
        return l;
    }
    throw("invalid key");
}

std::unique_ptr<Value> Parser::parseValue()
{
    using enum Tokentype;
    switch (tokens[currTok].t)
    {
    case STRING: {
        currTok++; 
        return parseString();
    }
    case POS_INT: {
        currTok++; 
        return parseInt(true);
    }
    case NEG_INT: {
        currTok++; 
        return parseInt(false);
    }
    case POS_FLOAT: {
        currTok++; 
        return parseFloat(true);
    }
    case NEG_FLOAT: {
        currTok++; 
        return parseFloat(false);
    }
    case LSQ: {
        currTok++; 
        return parseList(); 
    }
    case LBR: {
        return parseObj();
    }
    case JSON_NULL: {
        currTok++; 
        return parseNull();
    }
    case TRUE: {
        currTok++; 
        return parseTrue();
    }
    case FALSE: {
        currTok++; 
        return parseFalse();
    }
    default: break;
    }
    return nullptr;
}

std::unique_ptr<StringValue> Parser::parseString()
{
    auto v = std::make_unique<StringValue>(lexemes[currLex]);
    currLex++;
    return v;
}

std::unique_ptr<IntValue> Parser::parseInt(bool isPos)
{
    auto v = isPos
        ? std::make_unique<IntValue>(std::stoi(lexemes[currLex]))
        : std::make_unique<IntValue>(std::stoi(lexemes[currLex]));
    currLex++;
    return v;
}

std::unique_ptr<FloatValue> Parser::parseFloat(bool isPos)
{
    auto v = isPos
        ? std::make_unique<FloatValue>(std::stof(lexemes[currLex]))
        : std::make_unique<FloatValue>(-std::stof(lexemes[currLex]));
    currLex++;
    return v;
}

std::unique_ptr<BoolValue> Parser::parseTrue()
{
    auto v = std::make_unique<BoolValue>(true);
    return v;
}

std::unique_ptr<BoolValue> Parser::parseFalse()
{
    auto v = std::make_unique<BoolValue>(false);
    return v;
}

std::unique_ptr<NullValue> Parser::parseNull()
{
    auto v = std::make_unique<NullValue>();
    return v;
}

std::unique_ptr<ListValue> Parser::parseList()
{
    std::vector<std::unique_ptr<Value>> values;
    do {
        std::unique_ptr<Value> v = parseValue();
        values.push_back(std::move(v));
    } while(matchCurr(Tokentype::COMA));
    if (matchCurr(Tokentype::RSQ))
    {
        return std::make_unique<ListValue>(values);
    }
    throw("missing closing bracket");
}

}