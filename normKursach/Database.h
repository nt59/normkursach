#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "CommonFunctions.h"
#include "Client.h"
#include "Information.h"
#include "Check.h"
#include "CaI.h"
#include "CaC.h"

class Database{
public:
	Clients* clients;
	string AddressOfFolder = "C:/db";

	Infoes* infoes;

	Checks* checks;

	CaIs* cais;
	
	CaCs* cacs;

	Database(string address) {
		AddressOfFolder = address;
		clients = new Clients(AddressOfFolder + "/clients.txt");
		if (clients->ErrorMessage != "")
			PrintError("\n���� \"�������\"\n" + clients->ErrorMessage);

		infoes = new Infoes(AddressOfFolder + "/infoes.txt");
		if (clients->ErrorMessage != "")
			PrintError("\n���� \"����������\"\n" + infoes->ErrorMessage);
		
		checks = new Checks(AddressOfFolder + "/checks.txt");
		if (clients->ErrorMessage != "")
			PrintError("\n���� \"����\"\n" + checks->ErrorMessage);

		cais = new CaIs(AddressOfFolder + "/cais.txt", clients, infoes);
		if (clients->ErrorMessage != "")
			PrintError("\n���� \"����� ������� � ����������\"\n" + cais->ErrorMessage);

		cacs = new CaCs(AddressOfFolder + "/cacs.txt", clients, checks);
		if (clients->ErrorMessage != "")
			PrintError("\n���� \"����� ������� � �����\"\n" + cacs->ErrorMessage);
	}

	/*void GetReportOfDebt(){
		cout << "������� Id ������� ";
		string t;
		getline(cin, t);
		Client* selectedClient = NULL;
		if (isNumber(t))
			selectedClient = clients->FindById(atoi(t.c_str()));
		else
			selectedClient = clients->FindById;
		if ( selectedClient == NULL){
			PrintError("������! ������ � ����� Id ��� ��������� �� ����������\r\n");
			return;
		}

		cout << "----------------------------------------------------------------------------\n";
		cout << "����� �� ������������ ��������\n\n" << *selectedClient->Name << endl;

		printf("\n________________________________________________________________________________\r\n");
		printf("%20s |  %27s                             ", "��� ������� ", "������ ����������� |");
		printf("________________________________________________________________________________\n");

		cout << "������� ����������� ����: " << endl;
		int Today;

		cout << "\n������ ���������:\n";
		ClientList *node = First;
		while (node != NULL)
		{
			ClientList * nodeCaC = head_cac;
			while (nodeCaC != NULL && (node->client.clientID != nodeCaC->cac.clientID))
			{
				nodeCaC = nodeCaC->next;
			}
			ClientList *nodecheck = head_check;
			while (nodecheck != NULL && (nodeCaC->cac.checkId != nodecheck->check.checkId))
			{
				nodecheck = nodecheck->next;
			}
			if ((Today - nodecheck->check.Data) > nodecheck->check.RentTime){
				cout << node->client.C_name << "\n";
			}
			node = node->next;
		}
		cout << "\n----------------------------------------------------------------------------\n";
	}*/
};