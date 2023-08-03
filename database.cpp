#include "database.h"
#include "qdebug.h"

Database::Database(QObject *parent)
    : QObject{parent}
{
    database = new QSqlDatabase();
}

bool Database::connectDB(int task,QString newPath)
{
    if(task == 0)
    {
        //подключаем базу по пути DBPath
        *database = QSqlDatabase::addDatabase("QSQLITE");
        database->setDatabaseName(DBPath);

        if(database->open())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if(newPath != "")
        {
            //*database = QSqlDatabase::addDatabase("QSQLITE");
            database->close();
            database->setDatabaseName(newPath);

            DBPath = newPath;

            if(database->open())
            {
                createTables();
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }

    }


}

void Database::closeConnection()
{
    //database->close();
}

void Database::createTables()
{
    QSqlQuery createTbl = QSqlQuery(*database);

    createTbl.prepare("CREATE TABLE IF NOT EXISTS Steps ("
                           "Name         TEXT,"
                           "Step         TEXT,"
                           "Screenshot   TEXT,"
                           "StepId       INTEGER"
                           ");");
    createTbl.exec();

    createTbl.clear();
    createTbl.prepare("CREATE TABLE IF NOT EXISTS ScriptName ("
                           "Name         TEXT UNIQUE,"
                           "Screenshot   TEXT,"
                           "ExpectResult TEXT,"
                           "Result       TEXT,"
                           "Status       BOOLEAN"
                           ");");
    createTbl.exec();
}

void Database::doQuery(QString script)
{
    QSqlQuery query = QSqlQuery(*database);

    query.prepare(script);
    query.exec();
}

QSqlQuery Database::getRequest(QString request)
{
    QSqlQuery query = QSqlQuery(*database);

    query.prepare(request);
    query.exec();

    return query;
}

QString Database::getDBPath()
{
    return DBPath;
}

void Database::setDBPath(QString DBPath)
{
    this->DBPath = DBPath;
}

void Database::createDB(QString path, QString name)
{
    closeConnection();

    //*database = QSqlDatabase::addDatabase("QSQLITE");
    //qDebug() << path + "/" + name + ".sqlite" ;
    database->setDatabaseName(path + "/" + name + ".sqlite");

    if(database->open())
    {

    }


}
