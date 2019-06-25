#ifndef _DBPOOL_H
#define _DBPOOL_H

#include <string>
#include <mutex>
#include <list>
#include "jdbc\mysql_connection.h"
#include "jdbc\mysql_driver.h"

using namespace std;
using namespace sql;

class DBConnectPool
{
public:
	DBConnectPool();

	//init pool
	void initPool(std::string url_, std::string user_, std::string password_, int maxSize_);

	//get a conn from pool
	Connection* GetConnection();

	//put the conn back to pool
	void ReleaseConnection(Connection *conn);

	~DBConnectPool();

private:
	//init DB pool
	void InitConnection(int initSize);

	// create a connection
	Connection* CreateConnection();

	//destroy connection
	void DestoryConnection(Connection *conn);

	//destroy db pool
	void DestoryConnPool();

private:
	string   m_strUsr;
	string   m_strPwd;
	string   m_strUrl;
	int      m_maxSize;
	int      m_curSize;

	Driver*             m_driver;     //sql driver (the sql will free it)
	list<Connection*>   m_connList;   //create conn list

	
	std::mutex  m_Mtx;             //thread lock mutex
};

#endif

