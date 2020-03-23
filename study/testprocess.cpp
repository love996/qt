#include "testprocess.h"
#include <QProcess>
#include <thread>
void TestProcess()
{

    std::thread th([]{
        QProcess process;
        process.setProgram("bash");
        QStringList args{"-c", "cd \"/home/shenlan\" && bash ./run_qt.sh"};
        // QProcess::execute("bash");
        process.setArguments(args);
        // process.open(QProcess::ReadWrite);
        process.startDetached();
        process.waitForFinished(-1);
    });
    th.detach();

}
