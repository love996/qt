#include "pubfunc.h"

#include <QCryptographicHash>
#include <QFile>
#include <QProcess>
#include <QFileInfo>



QString fileMD5(const QString &filename)
{
    QFile file(filename);
    file.open(QFile::ReadOnly);
    QByteArray readBuffer;
    QCryptographicHash md5(QCryptographicHash::Md5);
    while (!(readBuffer = file.read(4096)).isEmpty()) {
        md5.addData(readBuffer);
    }
    return md5.result().toHex();
}

QString zipDir(const QString &dirName, const QString &target)
{
    QString command=QString("zip -r %1 %2").arg(target).arg(dirName);
    if (QProcess::execute(command) == 0)
        return target;
    return QString();
}

QString unzip(const QString &zipFilename, const QString &target)
{
    auto dirname = target;
    if (dirname.isEmpty()) {
        dirname = QFileInfo(zipFilename).baseName();
    }
    QString command=QString("unzip -d %1 %2").arg(dirname).arg(zipFilename);
    if (QProcess::execute(command) == 0)
        return dirname;
    return QString();
}
