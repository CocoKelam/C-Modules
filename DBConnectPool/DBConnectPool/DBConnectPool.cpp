#include "DBConnectPool.h"



DBConnectPool::DBConnectPool()
{
}

DBConnectPool::~DBConnectPool()
{
}

Connection* DBConnectPool::CreateConnection()
{
	Connection* conn;
	try {
		conn = m_driver->connect(m_strUrl, m_strUsr, m_strPwd);  //create a conn 
		return conn;
	}
	catch (sql::SQLException& e)
	{
		perror("link error");
		return nullptr;
	}
	catch (std::runtime_error& e)
	{
		perror("run error");
		return nullptr;
	}
}

void DBConnectPool::DestoryConnection(Connection *conn)
{
	if (conn)
	{
		try
		{
		   conn->close();
		}
		catch (SQLException& e)
		{
			perror(e.what());
		}
		catch (std::exception& e)
		{
			perror(e.what());
		}
		delete conn;
		conn = nullptr;
	}
	
}

void DBConnectPool::DestoryConnPool()
{
	std::lock_guard<std::mutex> lk(m_Mtx);
	for (auto& itr : m_connList)
	{
		DestoryConnection(itr);
	}
	m_curSize = 0;
	m_connList.clear();
	m_driver->getMinorVersion();
}

void DBConnectPool::InitConnection(int initSize)
{
	Connection* conn;
	std::lock_guard<std::mutex> lk(m_Mtx);
	for (int i = 0; i < initSize; i++)
	{
		conn = CreateConnection();
		if (conn)
		{
			m_connList.push_back(conn);
			m_curSize++;
		}
		else
		{
			perror("create conn error");
		}
	}
}
void DBConnectPool::initPool(std::string url_, std::string user_, std::string password_, int maxSize_)
{
	m_strUrl  = url_;
	m_strUsr  = user_;
	m_strPwd  = password_;
	m_maxSize = maxSize_;
	m_curSize = 0;

	try 
	{

		m_driver = mysql::get_driver_instance();
	}
	catch (SQLException& e)
	{
		perror("Get sql driver failed");
	}
	catch (std::runtime_error& e)
	{
		perror("Runtime error");
	}

	InitConnection(m_maxSize/2);
}

sql::Connection* DBConnectPool::GetConnection()
{
	std::lock_guard<std::mutex> lk(m_Mtx);
	if (m_connList.size() > 0)
	{
		Connection*	pConn = m_connList.front();
		m_connList.pop_front();
		if (pConn->isClosed())
		{
			delete pConn;

			pConn = this->CreateConnection();
		}

		if (pConn = NULL)
		{
			--m_curSize;
		}

		return pConn;
	}
	else
	{
		if (m_curSize < m_maxSize)
		{
			Connection* pConn = CreateConnection();
			if (pConn)
			{
				m_curSize++;

				return pConn;
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			return nullptr;
		}
	}
}

void DBConnectPool::ReleaseConnection(Connection *conn)
{
	if (conn)
	{
		std::lock_guard<std::mutex> lk(m_Mtx);
		m_connList.push_back(conn);
	}

}

