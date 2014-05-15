#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDateTime>
#include "writerMessages.h"

writerMessages::writerMessages()
{
}
writerMessages::~writerMessages()
{
}
bool writerMessages::opened()
{
}

bool writerMessagesSkype::opened()
{
    return m_bOpened;
}

bool writerMessagesPidgin::opened()
{
    return m_bOpened;
}

writerMessagesPidgin::writerMessagesPidgin(QString fileName, QString messangerName)
{
    m_bOpened = true;
    m_pFile = new QFile(fileName);
    if (!m_pFile->open(QIODevice::Append))
    {
        //std::cout << " failed task\n";
        m_bOpened = false;
        return;
    }
    m_pXmlWriter = new QXmlStreamWriter();
    m_pXmlWriter->setDevice(m_pFile);

    m_pXmlWriter->setAutoFormatting(true);
    m_pXmlWriter->writeStartDocument();
    m_pXmlWriter->writeStartElement("Messages ");
    m_pXmlWriter->writeAttribute("Messenger" ,messangerName);
}

writerMessagesPidgin::~writerMessagesPidgin()
{
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndDocument();
    delete m_pXmlWriter;
    delete m_pFile;
}

//about account.xml file
void writerMessagesPidgin::writeAccountInfo(
    QString name,
    QString email,
    QString protocol,
    QString password
)
{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("info_account");
    m_pXmlWriter->writeAttribute("name", name);
    m_pXmlWriter->writeAttribute("email", email);
    m_pXmlWriter->writeAttribute("password", password);
    m_pXmlWriter->writeAttribute("protocol", protocol);
    m_pXmlWriter->writeEndElement();
}

//about contacts.xml file
void writerMessagesPidgin::writeContactList(
    QString account,
    QString protocol,
    QString alias,
    QString name
)
{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("Contact_list");
    m_pXmlWriter->writeAttribute("account", account);
    m_pXmlWriter->writeAttribute("protocol", protocol);
    m_pXmlWriter->writeAttribute("name", alias);
    m_pXmlWriter->writeAttribute("emails", name);
    m_pXmlWriter->writeEndElement();
}

//about log file
void writerMessagesPidgin::writeInfoLog(
    QString chathID,
    QString account,
    QString data,
    QString protocol
)
{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("info");
    m_pXmlWriter->writeAttribute("chathID", chathID);
    m_pXmlWriter->writeAttribute("account", account);
    m_pXmlWriter->writeAttribute("data", data);
    m_pXmlWriter->writeAttribute("protocol", protocol);
    m_pXmlWriter->writeEndElement();
}

//like pidgin
void writerMessagesPidgin::writeMessage(
    QString author,
    QString dataTime,
    QString message
)
{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("message");
    m_pXmlWriter->writeAttribute("author", author);
    m_pXmlWriter->writeAttribute("dataTime", dataTime);
    m_pXmlWriter->writeAttribute("message", message);
    m_pXmlWriter->writeEndElement();
}

//constructor
writerMessagesSkype::writerMessagesSkype(
    QString fileType,
    QString type,
    QString messangerName
)
{
    m_bOpened = true;
    m_pFile= new QFile(fileType);
    if (!m_pFile->open(QIODevice::Append))
    {
        m_bOpened = false;
        return;
    }
    m_pXmlWriter= new QXmlStreamWriter();
    m_pXmlWriter->setDevice(m_pFile);
    m_pXmlWriter->setAutoFormatting(true);
    m_pXmlWriter->writeStartDocument();
    m_pXmlWriter->writeStartElement(type);
    m_pXmlWriter->writeAttribute("Messenger" ,messangerName);
}
//destructor
writerMessagesSkype::~writerMessagesSkype()
{
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndDocument();
    delete m_pXmlWriter;
    delete m_pFile;
}

// like skype
void writerMessagesSkype::writeMessage(
        QString author,
        QString timestamp,
        QString body_xml
)
{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("message");
    m_pXmlWriter->writeAttribute("author" ,author);
    m_pXmlWriter->writeAttribute("timestamp" ,timestamp);
    m_pXmlWriter->writeAttribute("body_xml" ,body_xml);
    m_pXmlWriter->writeEndElement();
};

void writerMessagesSkype::writeCalls(
    QString begin_timestamp,
    QString duration,
    QString host_identity,
    QString current_video_audience
)
{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("message");

    bool isconverted;
    uint iunixtime_integer = begin_timestamp .toUInt(&isconverted);
    QString idatetime = QDateTime::fromTime_t(iunixtime_integer).toString();

    m_pXmlWriter->writeAttribute("begin_timestamp" ,idatetime);
    m_pXmlWriter->writeAttribute("duration" ,duration);
    m_pXmlWriter->writeAttribute("host_identity" ,host_identity);
    m_pXmlWriter->writeAttribute("current_video_audience" ,current_video_audience);
    m_pXmlWriter->writeEndElement();
};

// like skype contact
void writerMessagesSkype::writeContacts(
        QString skypename ,
        QString fullName,
        QString birthday,
        QString gender,
        QString phone_mobile,
        QString languages,
        QString country,
        QString city
)
{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("contact");
    m_pXmlWriter->writeAttribute("skypeName" ,skypename);
    m_pXmlWriter->writeAttribute("fullName" ,fullName);
    m_pXmlWriter->writeAttribute("birthday" ,birthday);
    if (gender == "1")
        gender = "Male";
    else if (gender == "2")
        gender = "Felmale";
    else
        gender = "Unknow";
    m_pXmlWriter->writeAttribute("gender" ,gender);
    m_pXmlWriter->writeAttribute("phone_mobile" ,phone_mobile);
    if (languages == "ru")
        languages = "Russain";
    else if (languages == "en")
        languages = "English";
    else
        languages = "Other";
    m_pXmlWriter->writeAttribute("languages" ,languages);
    if (country == "ru")
        country = "Russia";
    else if (country == "en")
        country = "English/USA";
    else
        country = "Other";
    m_pXmlWriter->writeAttribute("country" ,country);
    m_pXmlWriter->writeAttribute("city" ,city);
    m_pXmlWriter->writeEndElement();
};

void writerMessagesSkype::writeInfo(
    QString skypeName,
    QString fullName,
    QString emails,
    QString ipcountry
)
{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("info_account");
    m_pXmlWriter->writeAttribute("skypeName" ,skypeName);
    m_pXmlWriter->writeAttribute("fullName" ,fullName);
    m_pXmlWriter->writeAttribute("emails" ,emails);
    m_pXmlWriter->writeAttribute("ipcountry" ,ipcountry);
    m_pXmlWriter->writeEndElement();
};
