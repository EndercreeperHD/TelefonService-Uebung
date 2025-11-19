#pragma once
#include "ServerSocket.hpp"
#include "Telefonbuch.h"
#include "MyThread.h"

// 2.5 Aufgabe
class TelefonbuchServer
{
private:
	ServerSocket *server;
	Telefonbuch *daten;

public:
	void start();
	TelefonbuchServer(int);
	~TelefonbuchServer();
};