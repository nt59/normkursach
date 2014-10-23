struct Check
{
	int id = 0;
	int Revenue;
	int RentTime;
	int Data;
};

struct CheckList{
	Check* сheck = NULL;
	CheckList* next = NULL;
};

class Checks{
private:
	CheckList* First;
	string FileAddress;

	void AddCheckToList(Check* s){
		if (First == NULL){
			First = new CheckList;
			First->сheck = s;
		}
		else {
			CheckList* temp = First;
			while (temp->next != NULL) temp = temp->next;
			temp->next = new CheckList;
			temp->next->сheck = s;
		}
	}

	Check* EnterNewCheck(){
		string* buf = new string;
		Check* ch = new Check;

		while (true){
			cout << "\nВведите выручку: ";
			getline(cin, *buf);
			if (isNumber(*buf)){
				ch->Revenue = atoi(buf->c_str());
				buf = new string;
				break;
			}
			else
				PrintError("Ошибка! Введите число! ");
		}

		while (true){
			cout << "\nВведите на сколько дней выдан товар: ";
			getline(cin, *buf);
			if (isNumber(*buf)){
				ch->RentTime = atoi(buf->c_str());
				buf = new string;
				break;
			}
			else
				PrintError("Ошибка! Введите число! ");
		}

		while (true){
			cout << "\nВведите какого числа был выдан товар: ";
			getline(cin, *buf);
			if (isNumber(*buf)){
				ch->Data = atoi(buf->c_str());
				buf = new string;
				break;
			}
			else
				PrintError("Ошибка! Ввeдите число! ");
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
				ErrorMessage.append("  Ошибка в строке ");
				ErrorMessage.append(itoa(numStr, bufer, 10));
				ErrorMessage.append(". Некорректный индентификатор!\n");
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
				ErrorMessage.append("  Ошибка в строке ");
				ErrorMessage.append(itoa(numStr, bufer, 10));
				ErrorMessage.append(". Некорректный индентификатор!\n");
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
				ErrorMessage.append("  Ошибка в строке ");
				ErrorMessage.append(itoa(numStr, bufer, 10));
				ErrorMessage.append(". Некорректный индентификатор!\n");
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
				ErrorMessage.append("  Ошибка в строке ");
				ErrorMessage.append(itoa(numStr, bufer, 10));
				ErrorMessage.append(". Некорректный индентификатор!\n");
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
			cout << "\nВведите Id учета: ";
			getline(cin, *buf);
			if (isNumber(*buf)){
				id = atoi(buf->c_str());
				break;
			}
			else
				PrintError("Ошибка! Введите число!");
		}
		Check* selectedCheck = this->FindById(id);
		if (selectedCheck == NULL){
			PrintError("ОШИБКА! Учета с таким Id не существует\r\n");
			return;
		}

		do {
			string* temp = new string;

			cout << "(Изменить: 1 - Выручка, 2 - Время аренды(дни), 3 - Дата)\r\n";

			while (true){
				cout << "Выбрать пункт: ";
				getline(cin, *buf);
				if (isNumber(*buf)){
					i = atoi(buf->c_str());
					break;
				}
				else
					PrintError("Ошибка! Введите число!\r\n");
			}
			switch (i){
			case 1:
				while (true){
					cout << "\nВведите выручку: ";
					getline(cin, *buf);
					if (isNumber(*buf)){
						selectedCheck->Revenue = atoi(buf->c_str());
						buf = new string;
						break;
					}
					else
						PrintError("Ошибка! Введите число! ");
				}
				break;
			case 2:
				while (true){
					cout << "\nВведите на сколько дней выдан товар: ";
					getline(cin, *buf);
					if (isNumber(*buf)){
						selectedCheck->RentTime = atoi(buf->c_str());
						buf = new string;
						break;
					}
					else
						PrintError("Ошибка! Введите число! ");
				}
				break;
			case 3:
				while (true){
					cout << "\nВведите какого числа был выдан товар: ";
					getline(cin, *buf);
					if (isNumber(*buf)){
						selectedCheck->Data = atoi(buf->c_str());
						buf = new string;
						break;
					}
					else
						PrintError("Ошибка! Ввeдите число! ");
				}
				break;
			default:
				PrintError("Введен некорректный номер пункта меню!\r\n");
			}
			cout << "\r\nПродолжить редактирование информации о данном учете? (1 - да, 2 - нет) : ";
			while (true){
				cout << "Выбрать пункт: ";
				getline(cin, *buf);
				if (isNumber(*buf)){
					j = atoi(buf->c_str());
					break;
				}
				else
					PrintError("Ошибка! Введите число!\r\n");
			}
		} while (j == 1);
		cout << "Данные о учете успешно изменены!\r\n";
	}

	Check* FindById(int id){
		CheckList* temp = First;
		while (temp != NULL && temp->сheck->id != id) temp = temp->next;
		if (temp != NULL && temp->сheck->id == id)
			return temp->сheck;
		return NULL;
	}

	void WriteData(){
		printf("________________________________________________________________________________\r\n");
		printf("%4s |  %9s | %17s | %10s           | %s", "ID", "Выручка", "Время аренды(дни)", " Дата |\r");
		printf("________________________________________________________________________________\r\n");
		CheckList* temp = First;
		while (temp != NULL){
			cout << setw(4) << temp->сheck->id << " |"
				<< setw(9) << temp->сheck->Revenue << " |"
				<< setw(17) << temp->сheck->RentTime << " |"
				<< setw(10) << temp->сheck->Data << " |";
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
		} while (temp->RentTime != 0); // проверить нулю ли равно когда мы учет не вводим
		if (temp != NULL) delete temp;
	}

	void SaveChanges(string address){
		ofstream data;
		data.open(address + "/checks.txt");

		CheckList* temp = First;
		while (temp != NULL){
			data << temp->сheck->id << ","
				<< temp->сheck->Revenue << ","
				<< temp->сheck->RentTime<< ","
				<< temp->сheck->Data << ".\n";
			temp = temp->next;
		}
		delete temp;
		data.close();
	}

	void DeleteCheck(int id){
		if (First->сheck->id != id){
			CheckList* tempcl = First;
			while (tempcl->next != NULL && tempcl->next->сheck->id != id) tempcl = tempcl->next;
			if (tempcl->next->next != NULL)
				tempcl->next = tempcl->next->next;
			else
				tempcl->next = NULL;
		}
		else
			First = First->next;
	}
};