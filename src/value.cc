#include "value.hh"
#include <iostream>

namespace Json {
Value::Value() { }
Value::~Value() { }
void Value::print() { }

StringValue::StringValue(std::string s): v(s)
{
}
StringValue::~StringValue()
{
}
void StringValue::print()
{
    std::cout << v;
}

IntValue::IntValue(int i): v(i)
{

}
IntValue::~IntValue()
{

}
void IntValue::print()
{
    std::cout << v;
}

BoolValue::BoolValue(bool b): v(b)
{

}
BoolValue::~BoolValue()
{

}
void BoolValue::print()
{
    std::cout << v;
}

ListValue::ListValue(std::vector<std::unique_ptr<Value>>& l): v(std::move(l))
{
}
ListValue::~ListValue()
{

}

void ListValue::print()
{
    std::cout << '[';
    for (auto& val: v)
    {
        val->print();
    }
    std::cout << ']';
}

ObjectValue::ObjectValue(std::unordered_map<std::string, std::unique_ptr<Value>>& m): map(std::move(m))
{
}
ObjectValue::~ObjectValue()
{

}
void ObjectValue::print()
{
    std::cout << "{\n";
    for (auto it = map.begin(); it != map.end(); it++)
    {
        std::cout << it->first << " : ";
        it->second->print();
        std::cout << '\n';
    }
    std::cout << "}\n";
}

std::unique_ptr<Value> ObjectValue::get(std::string k)
{
    return std::move(map[k]);
}

NullValue::NullValue()
{
}

NullValue::~NullValue()
{
}
void NullValue::print()
{
    std::cout << "null";
}

FloatValue::FloatValue(float f): v(f)
{
}

FloatValue::~FloatValue()
{
}

void FloatValue::print()
{
    std::cout << v;
}

}