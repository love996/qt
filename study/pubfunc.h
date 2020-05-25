#ifndef PUBFUNC_H
#define PUBFUNC_H

#include <QString>

QString fileMD5(const QString &filename);

QString zipDir(const QString &filename, const QString &target);

QString unzip(const QString &zipFilename, const QString &target = QString());


#endif // PUBFUNC_H
