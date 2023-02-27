#pragma once

#include <string>
#include <vector>

namespace Json
{
class Scanner;
class Parser;
class ObjectValue;
class Value;

class JsonObj
{
private:
    std::string input;
    std::unique_ptr<ObjectValue> object;
public:
    JsonObj(std::string input);
public:
    std::unique_ptr<Value> get(std::string key);
    std::unique_ptr<ObjectValue> parse();
    bool exists(std::string key);
};
    
} // namespace Json
