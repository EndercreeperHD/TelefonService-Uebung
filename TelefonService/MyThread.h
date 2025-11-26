#pragma once
#include <iostream>
#include <string>
#include <mutex>
#include "Thread.h"
#include "Socket.hpp"
#include "Telefonbuch.h"
#include "Eintrag.h"
using namespace std;

class MyThread : public Thread
{
private:
	static int counter;
	int ThreadNr;
	Socket* work;
	Telefonbuch* daten;
public:
	MyThread(Telefonbuch* ini_TB) { daten = ini_TB; work = nullptr; ThreadNr = counter; counter++; };
	void setSocket(Socket* ini) { work = ini; };
	Socket* getSocket() { return work; };
	void run() override {
		mutex coutMoutex;
		mutex TBMoutex;
		while (1) {
			while (work == nullptr) {
				Sleep(400);
			}
			string anfrageName = "";
			string antwort;
			coutMoutex.lock();
			cout << "Client mit Thread Nr." << ThreadNr << " verbunden!\n";
			coutMoutex.unlock();
			while (anfrageName != "exit" || anfrageName != "EXIT")
			{
				// 5b) Kommunikation mit read() write()
				anfrageName = work->readLine();
				coutMoutex.lock();
				cout << "Thread Nr." << ThreadNr << "\n";
				cout << anfrageName << "\n";
				coutMoutex.unlock();
				if (anfrageName.substr(0, 4) == "add ") {
					string zs = anfrageName;
					zs.erase(0, 4);
					TBMoutex.lock();
					daten->eintragEinfuegen(new Eintrag(zs.substr(0, zs.find(" ")), zs.substr(zs.find(" ") + 1, zs.size() - zs.find(" "))));
					TBMoutex.unlock();
					antwort = "wurde hinzugefuegt " + zs.substr(0, zs.find(" ")) + " " + zs.substr(zs.find(" ") + 1, zs.size() - zs.find(" "));
					work->write(antwort);
					coutMoutex.lock();
					cout << "Thread Nr." << ThreadNr << "\n";
					daten->toString();
					coutMoutex.unlock();
				}
				else if (anfrageName.substr(0, 7) == "remove ") {
					string zs = anfrageName;
					zs.erase(0, 7);
					TBMoutex.lock();
					daten->eintragLoeschen(zs);
					TBMoutex.unlock();
					antwort = zs + " wurde geloescht";
					work->write(antwort);
					coutMoutex.lock();
					cout << "Thread Nr." << ThreadNr << "\n";
					daten->toString();
					coutMoutex.unlock();
				}
				else if (anfrageName == "help") {
					work->write("add [name] [nummer] Antwort: wurde hinzugefuegt [name] [nummer]; remove [name] ,Antwort: [name] wurde geloescht; [name] Antwort: [nummer]");
				}
				else {
					antwort = daten->nrSuche(anfrageName);
					work->write(antwort);
				}
				antwort.clear();
			}
			coutMoutex.lock();
			cout << "verbindung mit Thread Nr." << ThreadNr << " getrennt!\n";
			coutMoutex.unlock();
			work->close();
			work = nullptr;
		}
	};
};