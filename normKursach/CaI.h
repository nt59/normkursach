struct CaI   //связь информации и клиента
{
	int clientID = 0;
	int informationID = 0;
};

struct CaIList
{
	CaI* cai;
	CaIList *next;
};

class CaIs{
private:
	CaIList* First;
	string FileAddress;

	void AddCaIToList(CaI* cai){
		if (First == NULL){
			First = new CaIList;
			First->cai = cai;
		}
		else {
			CaIList* temp = First;
			while (temp->next != NULL) temp = temp->next;
			temp->next = new CaIList;
			temp->next->cai = cai;
		}
	}

	CaI* EnterNewCaI(){
		string* buf = new string;
		CaI* tempCaI = new CaI;

		cout << "\nВведите ID клиента: ";
		getline(cin, *buf);
		if (buf->compare("") == 0)
			return tempCaI;
		tempCaI->clientID = atoi(buf->c_str());

		buf = new string;

		while (true){
			cout << "\nВведите ID информации: ";
			getline(cin, *buf);
			if (isNumber(*buf)){
				tempCaI->informationID = atoi(buf->c_str());
				buf = new string;
				break;
			}
			else
				PrintError("Ошибка! Введите число! ");
		}

		delete buf;
		AddCaIToList(tempCaI);
		return tempCaI;
	}

public:
	string ErrorMessage;
	Clients* _clients;
	Infoes* _infoes;

	CaIs(string fileAddress, Clients* c, Infoes* i) {
		First = NULL;
		_clients = c;
		_infoes = i;
		ErrorMessage = "";
		FileAddress = fileAddress;
		ifstream data(fileAddress);
		string buf;
		getline(data, buf);
		int numStr = 1;
		while (buf.compare("") != 0){
			CaI* tempCaI = new CaI;
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
				tempCaI->clientID = x;
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

			temp = readTo(buf, ',', pos);
			if (isNumber(*temp)){
				int x = atoi(temp->c_str());
				temp->clear();
				if (i->FindById(x) == NULL){
					char* bufer = new char;
					ErrorMessage.append("\n  Ошибка в строке ");
					ErrorMessage.append(itoa(numStr, bufer, 10));
					ErrorMessage.append(". Информации с таким индентификатором не существует!");
					delete bufer;
					getline(data, buf);
					numStr++;
					continue;
				}
				tempCaI->informationID = x;
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

			AddCaIToList(tempCaI);
			delete temp;
			getline(data, buf);
			numStr++;
		}

		data.close();
	}

	CaIList* GetFirst(){
		return First;
	}

	CaI* FindById(int id_cl, int id_in){
		CaIList* temp = First;
		while (temp != NULL && (temp->cai->clientID != id_cl || temp->cai->informationID != id_in)) temp = temp->next;
		if (temp != NULL)
			return temp->cai;
		return NULL;
	}

	void WriteData(){
		printf("\n________________________________________________________________________________\r\n");
		printf("%19s |  %28s", "Клиент (Id)", "Информация (Id) |\r\n");
		printf("________________________________________________________________________________\r\n");
		CaIList* temp = First;
		while (temp != NULL){
			cout << setw(15) << *_clients->FindById(temp->cai->clientID)->Name << " (" << temp->cai->clientID << ") |"
				<< setw(22) << *_infoes->FindById(temp->cai->informationID)->Audio_Video << " (" << temp->cai->informationID << ") |\r\n";
			temp = temp->next;
		}
		delete temp;
		printf("________________________________________________________________________________");
	}

	void ReadData(){
		CaI* temp;
		do{
			cout << "_______________________________________________________________________________\n";
			temp = EnterNewCaI();
			cout << "_______________________________________________________________________________";
		} while (temp->clientID != 0);
		if (temp != NULL) delete temp;
	}

	/*CaI* EnterNewCaI(){
		string* buf = new string;
		CaI* tempCaI = new CaI;
		bool flag;

		do{
			flag = false;
			cout << "\nВведите ID клиента: ";
			getline(cin, *buf);
			if (buf->compare("") == 0)
				return tempCaI;
			if (isNumber(*buf)){
				if (_clients->FindById(atoi(buf->c_str())) != NULL)
					tempCaI->clientID = atoi(buf->c_str());
				else{
					PrintError("Ошибка! Клиента с таким индентификатором не существует!\r\n");
					flag = true;
				}
			}
		} while (flag);

		do{
			flag = false;
			cout << "\nВведите ID информации: ";
			getline(cin, *buf);
			if (isNumber(*buf)){
				if (_infoes->FindById(atoi(buf->c_str())) != NULL)
					tempCaI->informationID = atoi(buf->c_str());
				else{
					PrintError("Ошибка! Информации с таким индентификатором не существует!\r\n");
					flag = true;
				}
			}
			else {
				PrintError("Ошибка! Введите число!\r\n");
				flag = true;
			}
		} while (flag);

		delete buf;

		if (this->FindById(tempCaI->clientID, tempCaI->informationID) != NULL){
			PrintError("Ошибка! Такая запись уже существует!");
			return NULL;
		}
		AddCaIToList(tempCaI);
		cout << "Запись успешно добавлена!";
		return tempCaI;
	}*/

	void SaveChanges(string address){
		ofstream data;
		data.open(address + "/cais.txt");

		CaIList* temp = First;
		while (temp != NULL){
			data << temp->cai->clientID << ","
				<< temp->cai->informationID << ".\n";
			temp = temp->next;
		}
		delete temp;
		data.close();
	}

	
};