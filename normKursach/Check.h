struct Check
{
	int id = 0;
	int Revenue;
	int RentTime;
	int Data;
};

struct CheckList{
	Check* �heck = NULL;
	CheckList* next = NULL;
};

class Checks{
private:
	CheckList* First;
	string FileAddress;

	void AddCheckToList(Check* s){
		if (First == NULL){
			First = new CheckList;
			First->�heck = s;
		}
		else {
			CheckList* temp = First;
			while (temp->next != NULL) temp = temp->next;
			temp->next = new CheckList;
			temp->next->�heck = s;
		}
	}

	Check* EnterNewCheck(){
		string* buf = new string;
		Check* ch = new Check;

		while (true){
			cout << "\n������� �������: ";
			getline(cin, *buf);
			if (isNumber(*buf)){
				ch->Revenue = atoi(buf->c_str());
				buf = new string;
				break;
			}
			else
				PrintError("������! ������� �����! ");
		}

		while (true){
			cout << "\n������� �� ������� ���� ����� �����: ";
			getline(cin, *buf);
			if (isNumber(*buf)){
				ch->RentTime = atoi(buf->c_str());
				buf = new string;
				break;
			}
			else
				PrintError("������! ������� �����! ");
		}

		while (true){
			cout << "\n������� ������ ����� ��� ����� �����: ";
			getline(cin, *buf);
			if (isNumber(*buf)){
				ch->Data = atoi(buf->c_str());
				buf = new string;
				break;
			}
			else
				PrintError("������! ��e���� �����! ");
		}
		return ch;
 	}

public:
	string ErrorMessage;

	Checks(string fileAddress) {
		First = NULL;
		ErrorMessage = "";
		FileAddress = fileAddress;
		ifstream data(fileAddress);
		string buf;
		getline(data, buf);
		int numStr = 1;
		while (buf.compare("") != 0){
			Check* tempCheck = new Check;
			string* temp = new string;
			int pos = 0;

			temp = readTo(buf, ',', pos);
			if (isNumber(*temp)){
				tempCheck->id = atoi(temp->c_str());
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
			if (isNumber(*temp)){
				tempCheck->Revenue = atoi(temp->c_str());
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
			if (isNumber(*temp)){
				tempCheck->RentTime = atoi(temp->c_str());
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

			temp = readTo(buf, '.', pos);
			if (isNumber(*temp)){
				tempCheck->Data = atoi(temp->c_str());
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

			AddCheckToList(tempCheck);
			delete temp;
			getline(data, buf);
			numStr++;
		}
	}

	void UpdateCheck(){
		int i, j, id = 0;
		string* buf = new string;
		while (true){
			cout << "\n������� Id �����: ";
			getline(cin, *buf);
			if (isNumber(*buf)){
				id = atoi(buf->c_str());
				break;
			}
			else
				PrintError("������! ������� �����!");
		}
		Check* selectedCheck = this->FindById(id);
		if (selectedCheck == NULL){
			PrintError("������! ����� � ����� Id �� ����������\r\n");
			return;
		}

		do {
			string* temp = new string;

			cout << "(��������: 1 - �������, 2 - ����� ������(���), 3 - ����)\r\n";

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
				while (true){
					cout << "\n������� �������: ";
					getline(cin, *buf);
					if (isNumber(*buf)){
						selectedCheck->Revenue = atoi(buf->c_str());
						buf = new string;
						break;
					}
					else
						PrintError("������! ������� �����! ");
				}
				break;
			case 2:
				while (true){
					cout << "\n������� �� ������� ���� ����� �����: ";
					getline(cin, *buf);
					if (isNumber(*buf)){
						selectedCheck->RentTime = atoi(buf->c_str());
						buf = new string;
						break;
					}
					else
						PrintError("������! ������� �����! ");
				}
				break;
			case 3:
				while (true){
					cout << "\n������� ������ ����� ��� ����� �����: ";
					getline(cin, *buf);
					if (isNumber(*buf)){
						selectedCheck->Data = atoi(buf->c_str());
						buf = new string;
						break;
					}
					else
						PrintError("������! ��e���� �����! ");
				}
				break;
			default:
				PrintError("������ ������������ ����� ������ ����!\r\n");
			}
			cout << "\r\n���������� �������������� ���������� � ������ �����? (1 - ��, 2 - ���) : ";
			while (true){
				cout << "������� �����: ";
				getline(cin, *buf);
				if (isNumber(*buf)){
					j = atoi(buf->c_str());
					break;
				}
				else
					PrintError("������! ������� �����!\r\n");
			}
		} while (j == 1);
		cout << "������ � ����� ������� ��������!\r\n";
	}

	Check* FindById(int id){
		CheckList* temp = First;
		while (temp != NULL && temp->�heck->id != id) temp = temp->next;
		if (temp != NULL && temp->�heck->id == id)
			return temp->�heck;
		return NULL;
	}

	void WriteData(){
		printf("________________________________________________________________________________\r\n");
		printf("%4s |  %9s | %17s | %10s           | %s", "ID", "�������", "����� ������(���)", " ���� |\r");
		printf("________________________________________________________________________________\r\n");
		CheckList* temp = First;
		while (temp != NULL){
			cout << setw(4) << temp->�heck->id << " |"
				<< setw(9) << temp->�heck->Revenue << " |"
				<< setw(17) << temp->�heck->RentTime << " |"
				<< setw(10) << temp->�heck->Data << " |";
			temp = temp->next;
		}
		delete temp;
		printf("________________________________________________________________________________");
	}

	void ReadData(){
		Check* temp;
		do{
			cout << "_______________________________________________________________________________\n";
			temp = EnterNewCheck();
			cout << "_______________________________________________________________________________";
		} while (temp->RentTime != 0); // ��������� ���� �� ����� ����� �� ���� �� ������
		if (temp != NULL) delete temp;
	}

	void SaveChanges(string address){
		ofstream data;
		data.open(address + "/checks.txt");

		CheckList* temp = First;
		while (temp != NULL){
			data << temp->�heck->id << ","
				<< temp->�heck->Revenue << ","
				<< temp->�heck->RentTime<< ","
				<< temp->�heck->Data << ".\n";
			temp = temp->next;
		}
		delete temp;
		data.close();
	}

	void DeleteCheck(int id){
		if (First->�heck->id != id){
			CheckList* tempcl = First;
			while (tempcl->next != NULL && tempcl->next->�heck->id != id) tempcl = tempcl->next;
			if (tempcl->next->next != NULL)
				tempcl->next = tempcl->next->next;
			else
				tempcl->next = NULL;
		}
		else
			First = First->next;
	}
};