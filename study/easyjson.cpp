#include "easyjson.h"
#include <QFile>
#include <QDebug>

EasyJson::EasyJson()
    :_parent(nullptr)
{

}

EasyJson::~EasyJson()
{
    if (_parent) {
        if (!this->_jsonObj.isEmpty()) {
            _parent->_jsonObj[_parentName] = this->_jsonObj;
        }
        else {
            _parent->_jsonObj[_parentName] = this->_val;
        }
    }
}

bool EasyJson::loads(const QByteArray &bytes)
{
    QJsonParseError error;
    _jsonDoc.fromJson(bytes, &error);
    if (error.error != QJsonParseError::NoError) {
        qDebug() << "parser json error:" << error.errorString();
        return false;
    }
    return load();
}

bool EasyJson::load(const QString &filename)
{
    QFile file(filename);
    file.open(QFile::ReadOnly);
    return loads(file.readAll());
}

bool EasyJson::load(const QJsonObject &obj)
{
    _jsonDoc.setObject(obj);
    return load();
}

bool EasyJson::load(const QJsonDocument &doc)
{
    _jsonDoc = doc;
    return load();
}

bool EasyJson::load()
{
    // _byteArray = _jsonDoc.toJson(QJsonDocument::JsonFormat::Compact);
    _jsonObj = _jsonDoc.object();
    return true;
}

QByteArray EasyJson::byteArray() const
{
    return QJsonDocument(_jsonObj).toJson(QJsonDocument::JsonFormat::Compact);
}

//const QJsonObject &EasyJson::json() const
//{
//    return _jsonObj;
//}

EasyJson::EasyJson(EasyJson *parent, QString parentName, const QJsonValue &val)
    :_parent(parent),
     _parentName(parentName)
{
    _val = val;
    if (_val.isObject()) {
        _jsonObj = val.toObject();
    }
}


