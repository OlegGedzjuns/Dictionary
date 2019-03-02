#include <string>
#include <time.h>

#include "Manager.h"

using namespace std;

int main()
{
	string inp = "input.txt";
	Manager* manager = new Manager(inp);
	manager->GetData();
	string buf;
	manager->PrinToFile();
}