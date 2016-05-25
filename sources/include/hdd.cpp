#include "hdd.h"
#include <QDebug>

Hdd::Hdd(QString path){
    QDirIterator dirPath(path, QDir::Dirs | QDir::NoSymLinks | QDir::Hidden, QDirIterator::Subdirectories);
    QList<QDir> dirList;

    while (dirPath.hasNext())
    {
        QDir directory(dirPath.next());
        if (!dirList.contains(directory))
        {
            dirList.append(directory);
        }
    }

    this->infoList = dirList;

    //debug
    /*
    QFile file("/home/ventar/test/test.txt");
    QStringList wildcard = (QStringList() << "*.jpg");
    if (file.open(QIODevice::WriteOnly))
    {
        foreach(QDir directory, this->infoList)
        {
            QTextStream stream(&file);
            stream << directory.absolutePath() << endl;
            QFileInfoList list = directory.entryInfoList(QDir::Files | QDir::NoSymLinks | QDir::Hidden);
            foreach (QFileInfo fileInfo, list)
            {
                stream << fileInfo.absoluteFilePath() << endl;
            }
        }
    }
    */
}

Hdd::~Hdd(){

}

QFileInfoList Hdd::getFiles(QStringList wildcardlist){

    QFileInfoList allists;
    foreach(QDir dir, Hdd::infoList){
        allists.append(dir.entryInfoList( wildcardlist, QDir::Files  | QDir::NoSymLinks | QDir::Hidden ));
    }

    return allists;
}

QFileInfoList Hdd::getFiles(QString wildcard){

    QStringList wildcardlist;
    wildcardlist.append(wildcard);
    return Hdd::getFiles(wildcardlist);
}
