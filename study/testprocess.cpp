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
        process.setProgram("bash");
        process.setArguments(args);
        process.setStandardErrorFile("stderr.txt");
        process.setStandardOutputFile("stdout.txt");
        qint64 pid;
        process.startDetached();
        QProcess::wa
    });
    th.detach();

}
