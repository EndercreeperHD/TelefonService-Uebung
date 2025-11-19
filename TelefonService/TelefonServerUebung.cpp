#include <iostream>
#include "TelefonbuchServer.h"

using namespace std;
#define SERVERPORT 54321
#define SERVERIP "127.0.0.1"


int main()
{
	// Mehr sollte in der main() nicht stehen!

	TelefonbuchServer* srv = new TelefonbuchServer(SERVERPORT);
	cout << "------------SERVER--------------" << endl;
	srv->start();


	delete srv;
	return 0;
}