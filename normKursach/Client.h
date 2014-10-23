struct Client
{
	int id = 0;
	string* Name = NULL;
	bool Type = false;
};

struct ClientList{
	Client* client = NULL;
	ClientList* next = NULL;
};

class Clients{
private:
	ClientList* First;
	string FileAddress;

	void AddClientToList(Client* s){
		if (First == NULL){
			First = new ClientList;
			First->client = s;
		}
		else {
			ClientList* temp = First;
			while (temp->next != NULL) temp = temp->next;
			temp->next = new ClientList;
			temp->next->client = s;
		}
	}

	Client* EnterNewClient(){
		string* buf = new string;
		Client* tempClient = new Client;

		cout << "\n������� ��� �������: ";
		getline(cin, *buf);
		if (buf->compare("") == 0)
			return tempClient;
		tempClient->Name = buf;
		buf = new string;

		if (First != NULL){
			ClientList* sl = First;
			while (sl->next != NULL){
				sl = sl->next;
			}
			tempClient->id = sl->client->id + 1;
		}
		else{
			tempClient->id = 1;
		}

		buf = new string;

		cout << "\n(1 - ����������, 2 - ������������)";
		cout << "\n������� ��� �������: ";
		bool flag;
		do{
			flag = false;
			getline(cin, *buf);
			switch (atoi(buf->c_str())){
			case 1:
				tempClient->Type = true;
				break;
			case 2:
				tempClient->Type = false;
				break;
			default:
				PrintError("������� �� ���������� ������!");
				flag = true;
			}
		} while (flag);

		delete buf;
		AddClientToList(tempClient);
		return tempClient;
	}

public:
	string ErrorMessage;

	Clients(string fileAddress) {
		First = NULL;
		ErrorMessage = "";
		FileAddress = fileAddress;
		ifstream data(fileAddress);
		string buf;
		getline(data, buf);
		int numStr = 1;
		while (buf.compare("") != 0){
			Client* tempClient = new Client;
			string* temp = new string;
			int pos = 0;

			temp = readTo(buf, ',', pos);
			if (isNumber(*temp)){
				tempClient->id = atoi(temp->c_str());
				temp->clear();
			}
			else{
				char* bufer = new char;
				ErrorMessage.append("  ������ � ������ ");
				ErrorMessage.append(itoa(numStr, bufer, 10));
				ErrorMessage.append(". ������������ ��������������!\n");
				getline(data, buf);
				numStr++;
				continue;
			}

			temp = readTo(buf, ',', pos);
			tempClient->Name = temp;
			temp = new string;

			temp = readTo(buf, '.', pos);
			if (isNumber(*temp) && (atoi(temp->c_str()) == 1))
				tempClient->Type = true;
			else{
				tempClient->Type = false;
			}


			AddClientToList(tempClient);
			delete temp;
			getline(data, buf);
			numStr++;
		}

		data.close();
	}

	void UpdateClient(){
		int i, j, id = 0;
		string* buf = new string;
		while (true){
			cout << "\n������� Id �������: ";
			getline(cin, *buf);
			if (isNumber(*buf)){
				id = atoi(buf->c_str());
				break;
			}
			else
				PrintError("������! ������� �����!");
		}
		Client* selectedClient = this->FindById(id);
		if (selectedClient == NULL){
			PrintError("������! ������� � ����� Id �� ����������\r\n");
			return;
		}

		do {
			string* temp = new string;

			cout << "(��������: 1 - ���, 2 - ���)\r\n";

			while (true){
				cout << "������� �����: ";
				getline(cin, *buf);
				if (isNumber(*buf)){
					i = atoi(buf->c_str());
					break;
				}
				else
					PrintError("������! ������� �����!\r\n");
			}
			switch (i){
			case 1:
				cout << "������� ���: ";
				getline(cin, *temp);
				selectedClient->Name = temp;
				break;
			case 2:
				cout << "\n(1 - ����������, 2 - ������������)";
				cout << "\n������� ��� �������: ";
				bool flag;
				do{
					flag = false;
					getline(cin, *buf);
					switch (atoi(buf->c_str())){
					case 1:
						selectedClient->Type = true;
						break;
					case 2:
						selectedClient->Type = false;
						break;
					default:
						PrintError("������� �� ���������� ������!");
						flag = true;
					}
				} while (flag);
				break;
			default:
				PrintError("������ ������������ ����� ������ ����!\r\n");
			}
			cout << "\r\n���������� �������������� ���������� � ������ �������? (1 - ��, 2 - ���) : ";
			while (true){
				cout << "\r\n������� �����: ";
				getline(cin, *buf);
				if (isNumber(*buf)){
					j = atoi(buf->c_str());
					break;
				}
				else
					PrintError("������! ������� �����!\r\n");
			}
		} while (j == 1);
		cout << "������ � ������� ������� ��������!\r\n";
	}

	void DeleteClient(int id){
		if (First->client->id != id){
			ClientList* tempcl = First;
			while (tempcl->next != NULL && tempcl->next->client->id != id) tempcl = tempcl->next;
			if (tempcl->next->next != NULL)
				tempcl->next = tempcl->next->next;
			else
				tempcl->next = NULL;
		}
		else
			First = First->next;
	}

	Client* FindById(int id){
		ClientList* temp = First;
		while (temp != NULL && temp->client->id != id) temp = temp->next;
		if (temp != NULL && temp->client->id == id)
			return temp->client;
		return NULL;
	}

	void WriteData(){
		printf("________________________________________________________________________________\r\n");
		printf("%4s |                 %3s |  %12s |\r\n", "ID", "���", " ��� �������");
		printf("________________________________________________________________________________\r\n");
		ClientList* temp = First;
		while (temp != NULL){
			cout << setw(4) << temp->client->id << " |"
				<< setw(20) << temp->client->Name->c_str() << " |"
				<< setw(14) << ((temp->client->Type) ? ("����������") : ("������������")) << " |\r\n";
			temp = temp->next;
		}
		delete temp;
		printf("________________________________________________________________________________");
	}

	void ReadData(){
		Client* temp;
		do{
			cout << "_______________________________________________________________________________\n";
			temp = EnterNewClient();
			cout << "_______________________________________________________________________________";
		} while (temp->Name != NULL && temp->Name->compare("") != 0);
		if (temp != NULL) delete temp;
	}

	void SaveChanges(string address){
		ofstream data;
		data.open(address + "/clients.txt");

		ClientList* temp = First;
		while (temp != NULL){
			data << temp->client->id << ","
				<< temp->client->Name->c_str() << ","
				<< ((temp->client->Type)?("1"):("2") )<< ".\n";
			temp = temp->next;
		}
		delete temp;
		data.close();
	}

};