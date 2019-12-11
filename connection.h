#ifndef CONNECTION_H
#define CONNECTION_H
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSql>
#include<QDebug>
#include<QtSql>
#include"qdom.h"
static bool creatconnection()
{
    QSqlDatabase db =QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("databaseHCX_3.db");
    if(!db.open())
    {
        return false;
    }
    QSqlQuery query;
    //建立三个表，分别为商品表，密码表，出售信息表
    query.exec("create table cargo(id int primary key, name varchar, price int, amount int, year int, month int, day int)");
    query.exec("insert into cargo values('0','请选择商品','0','0','0','0','0')");
    query.exec("create table sell(id int primary key, name varchar, price int, amount int, profile int, year int, month int)");
    query.exec("insert into sell values('0','查看清单','0','0','0','0','0')");
    query.exec("create table password(id int primary key , pwd varchar)");
    query.exec("insert into password values('0','123456')");

    return true;
}
#endif // CONNECTION_H
