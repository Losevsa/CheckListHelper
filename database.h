#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);

    bool connectDB(int task, QString newPath);
    void closeConnection();
    void createTables();
    void doQuery(QString script);
    QSqlQuery getRequest(QString request);
    QString getDBPath();
    void setDBPath(QString DBPath);
    //bool checkScriptNameInSteps

public slots:
    void createDB(QString path, QString name);

private:
    QSqlDatabase* database;
    QString DBPath;

};

#endif // DATABASE_H


