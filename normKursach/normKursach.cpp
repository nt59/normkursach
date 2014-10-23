#include "stdafx.h"
#include "windows.h"
#include "Database.h"

using namespace std;

struct shop{
	int id;
	string* Name = NULL;
	string* FolderAddress = NULL;
	Database* db = NULL;
};

int main()
{
	System::Console::Title = "��������� ����� ��������";

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	setlocale(LC_ALL, "Russian");
	shop mas[5];
	int ishop = 0;
	shop currentShop;
	char c;
	int x = 0;
	bool exit = false;
	string* buf = new string;
	for (int i = 0; i < 5; i++){
		shop* temp = new shop;
		temp->id = i + 1;
		temp->Name = new string;
		*temp->Name = "�������� ����� �������";
		temp->FolderAddress = new string;
		mas[i] = *temp;
		delete temp;
	}

	while (!exit){

		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\r\n";
		cout << "�������� �������: \n\n";
		for (x = 0; x < 5; x++){
			cout << (x + 1) << ". " << *mas[x].Name << "\n";
		}
		cout << (x + 1) << ". ����� �� ���������\r\n";
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\r\n";
		string s;
		while (true){
			cout << "������� �����: ";
			getline(cin, s);
			if (isNumber(s)){
				ishop = atoi(s.c_str());
				break;
			}
			else{
				cout << "������� �����! \r\n";
			}
		}

		if (ishop == x + 1)
			return 0;
		
		currentShop = mas[ishop - 1];

		if (currentShop.Name->compare("�������� ����� �������") == 0){
			cout << "\n������� �������� ��������: ";
			currentShop.Name->clear();
			getline(cin, *currentShop.Name);
			cout << "\n������� ��� ������� ��������!\n\n";
			currentShop.db = new Database("c:/db/new");
		}
		else {
			currentShop.db = new Database(*currentShop.FolderAddress);
		}

		bool exit2 = false;
		while (!exit2){
			int selection = MainMenu();
			switch (selection){
			case 1:
				switch (Menu("������,�������� ������� � ����������,�������� ������ � �������,������� ������ � �������,������� ��� ������� �� �����,������� ��������� � ����,�����,", 7)){
				case 1:
					currentShop.db->clients->ReadData();
					break;
				case 2:
					currentShop.db->clients->UpdateClient();
					break;
				case 3:
					//currentShop.db->clients->DeleteClient();
					break;
				case 4:
					currentShop.db->clients->WriteData();
					break;
				case 5:
					exit2 = true;
					break;
				default:
					break;
				}
				break;
			case 2:
				switch (Menu("����������,�������� ���������� � ����������,�������� ����������,������� ����������,������� ���������� �� �����,������� ��������� � ����,�����,", 7)){
				case 1:
					currentShop.db->infoes->ReadData();
					break;
				case 2:
					currentShop.db->infoes->UpdateInfo();
					break;
				case 3:
		//			currentShop.db->infoes->;
					break;
				case 4:
					currentShop.db->infoes->WriteData();
					break;
				case 5:
					exit2 = true;
					break;
				default:
					break;
				}
				break;
			case 3:
				switch (Menu("����,�������� ���� � ����������,�������� ������ �� �����,������� ������ �� �����,������� ������ �� �����  �� �����,������� ��������� � ����,�����,", 7)){
				case 1:
					currentShop.db->checks->ReadData();
					break;
				case 2:
					currentShop.db->checks->UpdateCheck();
					break;
				case 3:
					//
					break;
				case 4:
					currentShop.db->checks->WriteData();
					break;
				case 5:
					exit2 = true;
					break;	
				default:
					break;
				}
				break;

			case 4:
				switch (Menu("����� ���������� � �������,�������� ����� � ����������,�������� ������ �����,������� ������ � �����,������� ������ � ���������� �� �����,������� ��������� � ����,�����,", 7)){
				case 1:
					currentShop.db->cais->ReadData();
					break;
				case 2:
					//currentShop.db->cais->
					break;
				case 3:
					currentShop.db->cais->WriteData();
					break;
				case 4:
					exit2 = true;
					break;
				default:
					break;
				}
				break;
			case 5:
				switch (Menu("����� ������� � �����,�������� �������� � ����������,�������� ������ �� ��������,������� ������ �� ��������,������� ������ �� ��������� �� �����,������� ��������� � ����,�����,", 7)){
				case 1:
					currentShop.db->cacs->ReadData();
					break;
				case 2:
		//
					break;
				case 3:
					currentShop.db->cacs->WriteData();
					break;
				case 4:
					exit2 = true;
					break;
				default:
					break;
				}
				break;

				/*
			case 6:
				break;

			case 7:
				mas[0].shop->ReportOfDebt();
				break;
				*/

			case 0:
				cout << "exit" << endl;
				break;

			default:
				break;
			}
		}
		
		//_getch();
	}
}