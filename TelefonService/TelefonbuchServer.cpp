#include <iostream>
#include <string>
#include "TelefonbuchServer.h"
#include "Eintrag.h"
#include "MyThread.h"
using namespace std;

TelefonbuchServer::TelefonbuchServer(int port)
{
	// 1) ServerSocket() - erzeugt einen Serversocket
	server = new ServerSocket(port);

	daten = new Telefonbuch();
	daten->toString();
}

TelefonbuchServer::~TelefonbuchServer(void)
{
	delete server;
	delete daten;
}

void TelefonbuchServer::start()
{
	MyThread AWorkThread(daten);
	MyThread BWorkThread(daten);
	MyThread CWorkThread(daten);

	AWorkThread.start();
	BWorkThread.start();
	CWorkThread.start();

	while (1) {
		// 3) accept() - erzeugt einen ArbeitsSocket (workSocket), wenn ein Client eine Verbindung anfragt
		//    Der Aufruf von accept() blockiert solange, bis ein Client Verbindung aufnimmt
		Socket* work = server->accept();
		if (work == nullptr) continue;
		while (work != nullptr){
			if (AWorkThread.getSocket() == nullptr) {
				AWorkThread.setSocket(work);
				work = nullptr;
			}
			else if (BWorkThread.getSocket() == nullptr) {
				BWorkThread.setSocket(work);
				work = nullptr;
			}
			else if (CWorkThread.getSocket() == nullptr) {
				CWorkThread.setSocket(work);
				work = nullptr;
			}
			Sleep(500);
		}
	}
	// 8) ServerSocket abmelden
	AWorkThread.join();
	BWorkThread.join();
	CWorkThread.join();

	this->~TelefonbuchServer();
}