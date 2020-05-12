#include <iostream>
#include <string>
#include <list>
#include <iostream>
#include <algorithm>
#include "connection.h"
#include "eventlooper.h"

using namespace std;
using namespace ucom;


class TestServer : public IConnectorAcceptorSink, public IConnectionSink
{
	Acceptor *m_acceptor;
	typedef list<Connection*> ConnectionList;
	ConnectionList m_connections;
public:
	TestServer(const string &addr, short port)
		: m_acceptor(new Acceptor(addr, port, this))
	{
	}

	~TestServer(){
		m_acceptor->Stop();
		delete m_acceptor;
		m_acceptor = NULL;
	}

	bool Start(){
		return m_acceptor->StartListen() == 0;
	}

protected:
	virtual void OnConnection(Connection *conn, IConnectorAcceptor *ca){
		if (conn){
			cout << "Acceptor: new connection from " << conn->GetPeerAddress() << ":" << conn->GetPeerPort() << endl;
			conn->SetConnectionSink(this);
			m_connections.push_back(conn);
		}
	}

	virtual void OnData(const char *buf, int length, Connection *conn){
		cout << "OnData" << endl;
		string s(buf, length);
		cout << "recv: " << s << endl;
		conn->Send(buf, length);
	}

	virtual void OnWrite(Connection *conn){
		cout << "OnWrite" << endl;
	}

	virtual void OnDisconnect(int reason, Connection *conn)
	{
		cout << "OnDisconnect from " << conn->GetPeerAddress() << ":" << conn->GetPeerPort() << endl;
		m_connections.erase(std::find(m_connections.begin(), m_connections.end(), conn));
		delete conn;
	}
};

class TestClient : public IConnectorAcceptorSink, public IConnectionSink
{
	string m_peerAddr;
	short m_peerPort;
	Connector *m_connector;
	Connection *m_connection;
public:
	TestClient(const string &peerAddr, short peerPort)
		: m_peerAddr(peerAddr)
		, m_peerPort(peerPort)
		, m_connector(NULL)
		, m_connection(NULL)
	{
	}

	bool Connect(){
		if (m_connector)
			return true;
		m_connector = new Connector(m_peerAddr, m_peerPort, this);
		return m_connector->Connect(3000) == 0; //3 seconds
	}
protected:
	virtual void OnConnection(Connection *conn, IConnectorAcceptor *ca){
		if (conn){
			cout << "Client: connected succeed to " << conn->GetPeerAddress() << ":" << conn->GetPeerPort() << endl;
			m_connection = conn;

			string msg("hello, libevent!");
			conn->SetConnectionSink(this);
			conn->Send(msg.c_str(), msg.length());
		} else {
			cout << "Client: connect to " << m_peerAddr << ":" << m_peerPort << " failed." << endl;
		}
		delete m_connector;
		m_connector = NULL;

		if (!conn){
			cout << "not connected, try again!" << endl;
			Connect();
		}
	}

	virtual void OnData(const char *buf, int length, Connection *conn){
		cout << "OnData" << endl;
		string s(buf, length);
		cout << "recv: " << s << endl;
		
		//conn->Send(buf, length);
		EventLooper::GetInstance().StopEventLoop(5000);
	}

	virtual void OnWrite(Connection *conn){
		cout << "OnWrite" << endl;
	}

	virtual void OnDisconnect(int reason, Connection *conn)
	{
		cout << "OnDisconnect from " << conn->GetPeerAddress() << ":" << conn->GetPeerPort() << endl;
		delete m_connection;
		m_connection = NULL;
	}
};

int main(int argc,char **argv)
{
	cout << argc << " " << *argv << endl;


	EventLooper &el = EventLooper::GetInstance();

	char mode = 's';
	if (argc > 1)
		mode = argv[1][0];
	cout << "run in mode " << mode << endl;

	if (mode == 's'){
		TestServer *server = new TestServer("127.0.0.1", 5678);
		if (!server->Start())
			cerr << "server start failed." << endl;
	} else {
		string addr("127.0.0.1");
		TestClient *client = new TestClient(addr, 5678);
		if (!client->Connect())
			cerr << "client connect " << addr << " failed" << endl;
	}
	el.RunEventLoop();

	return 0;
}
