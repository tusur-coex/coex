#include "taskSearchArchive.h"
#include "writerXML.h"
#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QFileInfo>
#include <src/qzipreader_p.h>
#include <QTextStream>
#include <QDir>
#include <QDebug>
#include <qtextcodec.h>

TaskSearchArchive::TaskSearchArchive()
{
    m_bDebug = false;
};

QString TaskSearchArchive::help()
{
    return "\t--debug - viewing debug messages";
};

QString TaskSearchArchive::name()
{
    return "Search Archives";
};

QString TaskSearchArchive::author()
{
    return "Igor Polyakov";
};

QString TaskSearchArchive::description()
{
    return "task Search Archive";
};

bool TaskSearchArchive::isSupportOS(const coex::ITypeOperationSystem *os)
{
    return (os->platform() == "Windows");
};

void TaskSearchArchive::setOption(QStringList options)
{
    /*
    *
    * */
    if (options.contains("--debug"))
        m_bDebug = true;
};

/*!
Вывод информации об zip архиве
\param[out] QString listZipFile список файлов архива
\param[in] QString zipFile файл архива
*/
QString TaskSearchArchive::listZip(QString zipFile)
{
    QZipReader zip_reader(zipFile);
    QString listZipFile;
    if (zip_reader.exists()) {
        // вывод информации об архиве
        if (m_bDebug)
            qDebug() << "Number of items in the zip archive =" << zip_reader.count();
        foreach(QZipReader::FileInfo info, zip_reader.fileInfoList()) {
            if (info.isFile) {
                listZipFile += info.filePath;
            }
            /*else if (info.isDir)
                if(m_bDebug)
                    qDebug() << "Dir:" << info.filePath;
            else
                if(m_bDebug)
                    qDebug() << "SymLink:" << info.filePath;*/
            listZipFile += "\t";
        }
    }
    return listZipFile;
};

/*!
Определение типа архива по его заголовку
\param[out] QString ---
\param[in] QString path файл архива
*/
void TaskSearchArchive::determineTypeArchive(QString path)
{
/*
*/
}

bool TaskSearchArchive::execute(const coex::IConfig *config)
{
    if (m_bDebug) {
        std::cout << "Debug mode on.\n";
        std::cout << "InputFolder: " << config->inputFolder().toStdString() << "\n";
        std::cout << "---------------TaskSearchArchive::execute-----------------" << std::endl;
    };
    QDir dir(config->outputFolder());
    dir.mkdir("archive");
    writerFoudnArchive searchArchive(config->outputFolder() + "//archive/found.xml");;
    if (!searchArchive.opened()) {
        std::cout << "Failed task :: Can't create output folder & files\n";
        return false;
    }
    QDirIterator fileListDirit(config->inputFolder(), QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while (fileListDirit.hasNext()) {

        QString str = QString("%1").arg(fileListDirit.next());
        QFileInfo fInfo(str);
        QFile file(fInfo.absoluteFilePath());
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString plainText = file.readLine().trimmed();
            QString pathWay, archiveType, suffix, password, archiveFileList;
            QString size;

            if (plainText.contains(QRegExp("PK.*"))) {
                if (plainText.contains(QRegExp("PK.14*"))) {
                    archiveFileList = listZip(fInfo.absoluteFilePath());
                    suffix = fInfo.suffix();
                    archiveType = "ZIP";
                    password = "Yes";
                    size = QString::number(fInfo.size(), 10) + " b";
                    pathWay = fInfo.absoluteFilePath();
                    searchArchive.writeFound(pathWay, archiveType, suffix, size, password, archiveFileList);

                } else if (plainText.contains(QRegExp("PK.*"))) {
                    archiveFileList = listZip(fInfo.absoluteFilePath());
                    suffix = fInfo.suffix();
                    archiveType = "ZIP";
                    password = "No";
                    size = QString::number(fInfo.size(), 10) + " b";
                    pathWay = fInfo.absoluteFilePath();
                    searchArchive.writeFound(pathWay, archiveType, suffix, size, password, archiveFileList);

                }
            } else if (plainText.contains(QRegExp("Rar!.*"))) {
                suffix = fInfo.suffix();
                archiveType = "RAR";
                password = "No";
                size = QString::number(fInfo.size(), 10) + " b";
                pathWay = fInfo.absoluteFilePath();
                //searchArchive.writeFound(pathWay,archiveType,suffix,size,password,archiveFileList);

            } else if (plainText.contains(QRegExp("*7zXZ.*"))) {
                suffix = fInfo.suffix();
                archiveType = "XZ"; //да есть такой формат.
                password = "No";
                size = QString::number(fInfo.size(), 10) + " b";
                pathWay = fInfo.absoluteFilePath();
                //searchArchive.writeFound(pathWay,archiveType,suffix,size,password,archiveFileList);

            } else if (plainText.contains(QRegExp("7z.*"))) {
                suffix = fInfo.suffix();
                archiveType = "7 ZIP";
                password = "No";
                size = QString::number(fInfo.size(), 10) + " b";
                pathWay = fInfo.absoluteFilePath();
                //searchArchive.writeFound(pathWay,archiveType,suffix,size,password,archiveFileList);/
            }
        };
    };
    std::cout << " *  *  * Report created\n";
    return true;
};

coex::ITask* createTask()
{
    return (coex::ITask*)(new TaskSearchArchive());
}
