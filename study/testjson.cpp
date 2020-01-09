#include "testjson.h"
#include <string>
#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include "easyjson.h"
using namespace std;

struct A
{
    int x, y;
};

void fromJson(const EasyJson &json, A &a)
{
    a.x = json["x"];
    a.y = json["y"];
}

EasyJson toJson(A a)
{
    EasyJson json;
    json["x"] = a.x;
    json["y"] = a.y;
    return json;
}

struct B
{
    A a;
    int m, n;
};

void fromJson(const EasyJson &json, B &b)
{
    fromJson(json["a"], b.a);
    b.m = json["m"];
    b.n = json["n"];
}

EasyJson toJson(const B &b)
{
    EasyJson json;
    json["a"] = toJson(b.a);
    json["m"] = b.m;
    json["n"] = b.n;
    return json;
}

struct C
{
    int u, v;
    B b;
};

void fromJson(const EasyJson &json, C &c)
{
    c.u = json["u"];
    c.v = json["v"];
    fromJson(json["b"], c.b);
}

EasyJson toJson(const C &c)
{
    EasyJson json;
    json["u"] = c.u;
    json["v"] = c.v;
    json["b"] = toJson(c.b);
    return json;
}

void testJson()
{
    EasyJson obj;
    obj["a"] = "value a";
    qDebug() << obj.byteArray();
    obj["b"]["c"] = 100;
    obj["x"]["y"]["z"] = obj["a"];
    obj["obj"] = obj["x"];
    obj["obj"] = 1000;
    obj["new"] = obj;
    obj["a"];
    qDebug() << obj.byteArray();

    C c1, c2;
    c1.u = 100;
    c1.v = 200;
    c1.b.m = 101;
    c1.b.n = 102;
    c1.b.a.x = 201;
    c1.b.a.y = 202;
    EasyJson json = toJson(c1);
    fromJson(json, c2);
    qDebug() << json.byteArray();


}
