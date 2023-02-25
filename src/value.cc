#include "value.hh"
#include <iostream>

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

ListValue::ListValue(std::vector<Value*> l): v(l)
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

ObjectValue::ObjectValue(std::unordered_map<std::string, Value*>& m): map(m)
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