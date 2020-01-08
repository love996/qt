#ifndef MYJSON_H
#define MYJSON_H
#include <QJsonObject>
#include <QVariantMap>

struct JsonNode
{
    JsonNode(QVariant &obj)
        :_obj(obj)
    {}
    JsonNode operator[](const QString &key)
    {
        //if ()
    }
private:
    QVariant &_obj;
};

class MyJson
{
public:
    MyJson();
private:
    QJsonObject _json_obj;
    QVariantMap _map;
};

#endif // MYJSON_H
