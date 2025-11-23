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
	string anfrageName = "";
	string antwort;
	while (1) {
		// 3) accept() - erzeugt einen ArbeitsSocket (workSocket), wenn ein Client eine Verbindung anfragt
		//    Der Aufruf von accept() blockiert solange, bis ein Client Verbindung aufnimmt
		Socket* work = server->accept();
		if (work == nullptr) continue;
		MyThread AWorkThread(work, daten);
		MyThread BWorkThread(work, daten);
		MyThread CWorkThread(work, daten);
		cout << "Client verbunden!" << endl;
		
		
		while (anfrageName != "exit")
		{
			// 5b) Kommunikation mit read() write()
			anfrageName = work->readLine();
			cout << anfrageName << "\n";
			if (anfrageName.substr(0, 4) == "add ") {
				string zs = anfrageName;
				zs.erase(0,4);
				daten->eintragEinfuegen(new Eintrag(zs.substr(0, zs.find(" ")), zs.substr(zs.find(" ") + 1, zs.size() - zs.find(" "))));
				antwort = "wurde hinzugefuegt " + zs.substr(0, zs.find(" ")) + " " + zs.substr(zs.find(" ") + 1, zs.size() - zs.find(" "));
				work->write(antwort);
				daten->toString();
			}
			else if (anfrageName.substr(0, 7) == "remove ") {
				string zs = anfrageName;
				zs.erase(0,7);
				daten->eintragLoeschen(zs);
				antwort = "wurde geloescht " + zs;
				work->write(antwort);
				daten->toString();
			}
			else {
				antwort = daten->nrSuche(anfrageName);
				work->write(antwort);
			}
			antwort.clear();
		}

		// 7) ArbeitsSocket abmelden
		work->close();
	}

	// 8) ServerSocket abmelden
	this->~TelefonbuchServer();
}