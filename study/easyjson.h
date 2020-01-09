#ifndef EASYJSON_H
#define EASYJSON_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

/**
 * @brief The EasyJson class
 * 只做为一个简单的json和对象之间的转换
 */
class EasyJson
{
public:
    EasyJson();
    EasyJson(const EasyJson &) = delete;
    EasyJson(EasyJson &&th)
        :_parent(th._parent),
         _val(std::move(th._val)) ,
         _jsonObj(std::move(th._jsonObj)),
         _parentName(std::move(th._parentName))
    {
        th._parent = nullptr;
    }

    EasyJson& operator=(EasyJson &&th)
    {
        // qDebug() << "move &&";
        if (this != &th) {
            th._parent = nullptr;
             _val = std::move(th._val);
             if (!th._jsonObj.isEmpty()) {
                 _jsonObj = std::move(th._jsonObj);
             }
        }
        return *this;
    }
    ~EasyJson();
    bool loads(const QByteArray &bytes);
    bool load(const QString &filename);
    bool load(const QJsonObject &obj);
    bool load(const QJsonDocument &doc);
    bool isNull() const
    {
        return _jsonObj.isEmpty();
    }
    EasyJson operator[](const char *key) {
        return (*this)[QString(key)];
    }

    EasyJson operator[](const char *key) const {
        return (*this)[QString(key)];
    }

    EasyJson operator[](const QString &key) {
        return EasyJson(this, key, _jsonObj[key]);
    }
    EasyJson operator[](const QString &key) const {
        qDebug() << key << "const";
        return EasyJson(nullptr, key, _jsonObj[key]);
    }

    EasyJson &operator=(const QJsonValue &value) {
        // qDebug() << "jsonValue";
        if (!this->_parent && !value.isObject()) {
            qDebug() << "非法json类型";
            return *this;
        }
        _val = value;
        return *this;
    }
    EasyJson &operator=(const EasyJson &obj) {
        // qDebug() << "easyJson value";
        if (!this->_parent && obj.isNull()) {
            qDebug() << "非法json类型";
            return *this;
        }
        if (obj._jsonObj.isEmpty()) {
            _val = obj._val;
        }
        else {
            _val = obj._jsonObj;
        }
        return *this;
    }
    QByteArray byteArray() const;

    operator int()
    {
        return _val.toInt();
    }

    operator QString()
    {
        return _val.toString();
    }

    operator bool()
    {
        return _val.toBool();
    }

    operator double()
    {
        return _val.toDouble();
    }
private:
    QJsonObject _jsonObj;
    QJsonDocument _jsonDoc;
    QJsonValue _val;
    EasyJson *_parent;
    QString _parentName;
private:
    EasyJson(EasyJson *parent, QString parentName, const QJsonValue &obj);
    bool load();
};

#endif // EASYJSON_H
