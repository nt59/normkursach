struct CaC   //связь клиента и проверки
{
	int clientID = 0;
	int checkID = 0;
};

struct CaCList
{
	CaC* cac = NULL;
	CaCList  *next = NULL;
};

class CaCs{
private:
	CaCList* First;
	string FileAddress;
	Clients* _clients;
	Checks* _checks;

	void AddCaCToList(CaC* cac){
		if (First == NULL){
			First = new CaCList;
			First->cac = cac;
		}
		else {
			CaCList* temp = First;
			while (temp->next != NULL) temp = temp->next;
			temp->next = new CaCList;
			temp->next->cac = cac;
		}
	}

public:
	string ErrorMessage;

	CaCs(string fileAddress, Clients* c, Checks* ch) {
		First = NULL;
		_clients = c;
		_checks = ch;
		FileAddress = fileAddress;
		ifstream data(FileAddress);
		string buf;
		int numStr = 1;
		getline(data, buf);
		while (buf.compare("") != 0){
			CaC* tempCaC = new CaC;
			string* temp = new string;
			int pos = 0;

			temp = readTo(buf, ',', pos);
			if (isNumber(*temp)){
				int x = atoi(temp->c_str());
				temp->clear();
				if (c->FindById(x) == NULL){
					char* bufer = new char;
					ErrorMessage.append("\n  Ошибка в строке ");
					ErrorMessage.append(itoa(numStr, bufer, 10));
					ErrorMessage.append(". Клиента с таким индентификатором не существует!");
					delete bufer;
					getline(data, buf);
					numStr++;
					continue;
				}
				tempCaC->clientID = x;
			}
			else{
				char* bufer = new char;
				ErrorMessage.append("\n  Ошибка в строке ");
				ErrorMessage.append(itoa(numStr, bufer, 10));
				ErrorMessage.append(". Некорректный индентификатор!");
				getline(data, buf);
				numStr++;
				continue;
			}

			temp = readTo(buf, '.', pos);
			if (isNumber(*temp)){
				int x = atoi(temp->c_str());
				temp->clear();
				if (ch->FindById(x) == NULL){
					char* bufer = new char;
					ErrorMessage.append("\n  Ошибка в строке ");
					ErrorMessage.append(itoa(numStr, bufer, 10));
					ErrorMessage.append(". Учета с таким индентификатором не существует!");
					delete bufer;
					getline(data, buf);
					numStr++;
					continue;
				}
				tempCaC->checkID = x;
			}
			else{
				char* bufer = new char;
				ErrorMessage.append("\n  Ошибка в строке ");
				ErrorMessage.append(itoa(numStr, bufer, 10));
				ErrorMessage.append(". Некорректный индентификатор!");
				getline(data, buf);
				numStr++;
				continue;
			}

			delete temp;
			AddCaCToList(tempCaC);
			getline(data, buf);
		}

		data.close();
	}

	CaCList* GetFirst(){
		return First;
	}

	CaC* FindById(int id_c, int id_ch){
		CaCList* temp = First;
		while (temp != NULL && (temp->cac->clientID != id_c || temp->cac->checkID != id_ch)) temp = temp->next;
		if (temp != NULL)
			return temp->cac;
		return NULL;
	}

	void WriteData(){
		printf("\n________________________________________________________________________________\r\n");
		printf("%19s |  %28s", "Имя клиента (Id)", "Время аренды (Id учета) |\r\n");
		printf("________________________________________________________________________________\r\n");
		CaCList* temp = First;
		while (temp != NULL){
			cout << setw(15) << *_clients->FindById(temp->cac->clientID)->Name << " (" << temp->cac->clientID<< ") |"
				<< setw(22) << _checks->FindById(temp->cac->clientID)->RentTime << " (" << temp->cac->checkID << ") |\r\n";
			temp = temp->next;
		}
		delete temp;
		printf("________________________________________________________________________________");
	}

	void ReadData(){
		CaC* temp;
		do{
			cout << "_______________________________________________________________________________\n";
			temp = EnterNewCaC();
			cout << "_______________________________________________________________________________";
		} while (temp->clientID != 0);
		if (temp != NULL) delete temp;
	}

	CaC* EnterNewCaC(){
		string* buf = new string;
		CaC* tempCaC = new CaC;
		bool flag;

		do{
			flag = false;
			cout << "\nВведите ID клиента: ";
			getline(cin, *buf);
			if (buf->compare("") == 0)
				return tempCaC;
			if (isNumber(*buf)){
				if (_clients->FindById(atoi(buf->c_str())) != NULL)
					tempCaC->clientID = atoi(buf->c_str());
				else{
					PrintError("Ошибка! Клиента с таким индентификатором не существует!\r\n");
					flag = true;
				}
			}
		} while (flag);

		do{
			flag = false;
			cout << "\nВведите ID учета: ";
			getline(cin, *buf);
			if (isNumber(*buf)){
				if (_checks->FindById(atoi(buf->c_str())) != NULL)
					tempCaC->checkID = atoi(buf->c_str());
				else{
					PrintError("Ошибка! Учета с таким индентификатором не существует!\r\n");
					flag = true;
				}
			}
			else {
				PrintError("Ошибка! Введите число!\r\n");
				flag = true;
			}
		} while (flag);

		delete buf;

		if (this->FindById(tempCaC->clientID, tempCaC->checkID) != NULL){
			PrintError("Ошибка! Такая запись уже существует!");
			return NULL;
		}
		AddCaCToList(tempCaC);
		cout << "Запись успешно добавлена!";
		return tempCaC;
	}

	void SaveChanges(string address){
		ofstream data;
		data.open(address + "/cac.txt");

		CaCList* temp = First;
		while (temp != NULL){
			data << temp->cac->clientID << ","
				<< temp->cac->checkID << ".\n";
			temp = temp->next;
		}
		delete temp;
		data.close();
	}
};