#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class Value {
public:
    Value();
    virtual ~Value() = 0;
    virtual void print() = 0;
};

class StringValue : public Value
{
public:
    std::string v;
    StringValue(std::string);
    ~StringValue();
    void print();
};

class BoolValue : public Value
{
public:
    bool v;
public:
    BoolValue(bool);
    ~BoolValue();
    void print();
};

class ListValue : public Value
{
public:
    ListValue(std::vector<Value*>);
    ~ListValue();
    void print();
public:
    std::vector<Value*> v;
};

class ObjectValue : public Value
{
public:
    std::unordered_map<std::string, Value*> map;
public:
    ObjectValue(std::unordered_map<std::string, Value*>&);
    ~ObjectValue();
    void print();
};

class IntValue : public Value
{
public:
    int v;
public:
    IntValue(int);
    ~IntValue();
    void print();
};

class FloatValue : public Value
{
public:
    float v;
public:
    FloatValue(float);
    ~FloatValue();
    void print();
};

class NullValue : public Value
{
public:
    NullValue();
    ~NullValue();
    void print();
};