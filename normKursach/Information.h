struct Info
{
	int id = 0; 
	string* Audio_Video = NULL;
	string* Cd_Dvd = NULL;
	string* Genre = NULL;
};

struct InfoList{
	Info* info = NULL;
	InfoList* next = NULL;
};

class Infoes{
private:
	InfoList* First;
	string FileAddress;

	void AddInfoToList(Info* s){
		if (First == NULL){
			First = new InfoList;
			First->info = s;
		}
		else {
			InfoList* temp = First;
			while (temp->next != NULL) temp = temp->next;
			temp->next = new InfoList;
			temp->next->info = s;
		}
	}

	Info* EnterNewInfo(){
		string* buf = new string;
		Info* tempInfo = new Info;

		cout << "\n(1 - Audio, 2 - Video)";
		cout << "\n������� Audio ��� Video: ";
		bool flag;
		do{
			flag = false;
			getline(cin, *buf);
			switch (atoi(buf->c_str())){
			case 1:
				*tempInfo->Audio_Video = "Audio";
				break;
			case 2:
				*tempInfo->Audio_Video = "Video";
				break;
			default:
				return tempInfo;
			}
		} while (flag);

		if (First != NULL){
			InfoList* in = First;
			while (in->next != NULL){
				in = in->next;
			}
			tempInfo->id = in->info->id + 1;
		}
		else{
			tempInfo->id = 1;
		}

		buf = new string;

		cout << "\n(1 - CD, 2 - DVD)";
		cout << "\n������� CD ��� DvD: ";
//		bool flag;
		do{
			flag = false;
			getline(cin, *buf);
			switch (atoi(buf->c_str())){
			case 1:
				*tempInfo->Cd_Dvd = "CD";
				break;
			case 2:
				*tempInfo->Cd_Dvd = "DvD";
				break;
			default:
				return NULL;
			}
		} while (flag);

		if (tempInfo->Audio_Video->compare("Audio") == 0){
			cout << "\n(1 - ��������, 2 - ���, 3 - ������������, 4 - ����, 5 - ���)";
			cout << "\n������� ���� ������: ";
//			bool flag;
			do{
				flag = false;
				getline(cin, *buf);
				switch (atoi(buf->c_str())){
				case 1:
					*tempInfo->Genre = "��������";
					break;
				case 2:
					*tempInfo->Genre = "���";
					break;
				case 3:
					*tempInfo->Genre = "������������";
				case 4:
					*tempInfo->Genre = "����";
				case 5:
					*tempInfo->Genre = "���";
				default:
					return NULL;
				}
			} while (flag);
		}
		else{
			cout << "\n(1 - �����, 2 - �������, 3 - �����������, 4 - ��������, 5 - �����)";
			cout << "\n������� ���� ������: ";
			bool flag;
			do{
				flag = false;
				getline(cin, *buf);
				switch (atoi(buf->c_str())){
				case 1:
					*tempInfo->Genre = "�����";
					break;
				case 2:
					*tempInfo->Genre = "�������";
					break;
				case 3:
					*tempInfo->Genre = "�����������";
				case 4:
					*tempInfo->Genre = "��������";
				case 5:
					*tempInfo->Genre = "�����";
				default:
					return NULL;
				}
			} while (flag);
		}

		delete buf;
		AddInfoToList(tempInfo);
		return tempInfo;
	}

public:
	string ErrorMessage;

	Infoes(string fileAddress) {
		First = NULL;
		ErrorMessage = "";
		FileAddress = fileAddress;
		ifstream data(fileAddress);
		string buf;
		getline(data, buf);
		int numStr = 1;
		while (buf.compare("") != 0){
			Info* tempInfo = new Info;
			string* temp = new string;
			int pos = 0;

			temp = readTo(buf, ',', pos);
			if (isNumber(*temp)){
				tempInfo->id = atoi(temp->c_str());
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
			if (temp->compare("1") == 0)
			{
				*tempInfo->Audio_Video = "Audio";
				temp->clear();
			}
			else{
				*tempInfo->Audio_Video = "Video";
				temp->clear();
			}

			temp = readTo(buf, ',', pos);
			if (temp->compare("1") == 0)
			{
				*tempInfo->Cd_Dvd = "CD";
				temp->clear();

			}
			else{
				*tempInfo->Cd_Dvd = "DVD";
				temp->clear();
			}
				
			temp = readTo(buf, '.', pos);
			if (isNumber(*temp)){
					if (tempInfo->Audio_Video->compare("Audio") == 0){
							switch (atoi(temp->c_str())){
							case 1:
								*tempInfo->Genre = "��������";
								break;
							case 2:
								*tempInfo->Genre = "���";
								break;
							case 3:
								*tempInfo->Genre = "������������";
							case 4:
								*tempInfo->Genre = "����";
							case 5:
								*tempInfo->Genre = "���";
							default:
								*tempInfo->Genre = "��������";
							}
					}
					else{
							switch (atoi(temp->c_str())){
							case 1:
								*tempInfo->Genre = "�����";
								break;
							case 2:
								*tempInfo->Genre = "�������";
								break;
							case 3:
								*tempInfo->Genre = "�����������";
							case 4:
								*tempInfo->Genre = "��������";
							case 5:
								*tempInfo->Genre = "�����";
							default:
								*tempInfo->Genre = "�����";
							}
					}
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

			AddInfoToList(tempInfo);
			delete temp;
			getline(data, buf);
			numStr++;
		}
	}

	void UpdateInfo(){
		int i, j, id = 0;
		string* buf = new string;
		while (true){
			cout << "\n������� Id ����������: ";
			getline(cin, *buf);
			if (isNumber(*buf)){
				id = atoi(buf->c_str());
				break;
			}
			else
				PrintError("������! ������� �����!");
		}
		Info* selectedInfo = this->FindById(id);
		if (selectedInfo == NULL){
			PrintError("������! ���������� � ����� Id �� ����������\r\n");
			return;
		}

		do {
			string* temp = new string;

			cout << "(��������: 1 - ��� ������, 2 - ��� �����, 3 - ����)\r\n";

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
				cout << "\n(1 - Audio, 2 - Video)";
				bool flag;
				do{
					cout << "\n������� Audio ��� Video: ";
					flag = false;
					getline(cin, *buf);
					switch (atoi(buf->c_str())){
					case 1:
						*selectedInfo->Audio_Video = "Audio";
						break;
					case 2:
						*selectedInfo->Audio_Video = "Video";
						break;
					}
				} while (flag);
				break;
			case 2:
				cout << "\n(1 - CD, 2 - DVD)";
//				bool flag;
				do{
					cout << "\n������� CD ��� DvD: ";
					flag = false;
					getline(cin, *buf);
					switch (atoi(buf->c_str())){
					case 1:
						*selectedInfo->Cd_Dvd = "CD";
						break;
					case 2:
						*selectedInfo->Cd_Dvd = "DvD";
						break;
					}
				} while (flag);
				break;
			case 3:
				if (selectedInfo->Audio_Video->compare("Audio") == 0){
					cout << "\n(1 - ��������, 2 - ���, 3 - ������������, 4 - ����, 5 - ���)";
					bool flag;
					do{
						cout << "\n������� ���� ������: ";
						flag = false;
						getline(cin, *buf);
						switch (atoi(buf->c_str())){
						case 1:
							*selectedInfo->Genre = "��������";
							break;
						case 2:
							*selectedInfo->Genre = "���";
							break;
						case 3:
							*selectedInfo->Genre = "������������";
						case 4:
							*selectedInfo->Genre = "����";
						case 5:
							*selectedInfo->Genre = "���";
						}
					} while (flag);
				}
				else{
					cout << "\n(1 - �����, 2 - �������, 3 - �����������, 4 - ��������, 5 - �����)";
					bool flag;
					do{
						cout << "\n������� ���� ������: ";
						flag = false;
						getline(cin, *buf);
						switch (atoi(buf->c_str())){
						case 1:
							*selectedInfo->Genre = "�����";
							break;
						case 2:
							*selectedInfo->Genre = "�������";
							break;
						case 3:
							*selectedInfo->Genre = "�����������";
						case 4:
							*selectedInfo->Genre = "��������";
						case 5:
							*selectedInfo->Genre = "�����";
						}
					} while (flag);
				}
				break;
			default:
				PrintError("������ ������������ ����� ������ ����!\r\n");
				}
				cout << "\r\n���������� �������������� ���������� � ������ �������? (1 - ��, 2 - ���) : ";
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
			cout << "������ � ������� ������� ��������!\r\n";
		}

	Info* FindById(int id){
		InfoList* temp = First;
		while (temp != NULL && temp->info->id != id) temp = temp->next;
		if (temp != NULL && temp->info->id == id)
			return temp->info;
		return NULL;
	}

	void WriteData(){
		printf("________________________________________________________________________________\r\n");
		printf("%4s |  %10s | %12s | %19s      | %s", "ID", "Audio ��� Video", "CD ��� DVD" ," ���� |");
		printf("________________________________________________________________________________\r\n");
		InfoList* temp = First;
		while (temp != NULL){
			cout << setw(4) << temp->info->id << " |"
				<< setw(18) << temp->info->Audio_Video->c_str() << " |"
				<< setw(18) << temp->info->Cd_Dvd->c_str() << " |"
				<< setw(13) << temp->info->Genre->c_str() << " |";
			temp = temp->next;
		}
		delete temp;
		printf("________________________________________________________________________________");
	}

	void ReadData(){
		Info* temp;
		do{
			cout << "_______________________________________________________________________________\n";
			temp = EnterNewInfo();
			cout << "_______________________________________________________________________________";
		} while (temp->Audio_Video != NULL && temp->Audio_Video->compare("") != 0);
		if (temp != NULL) delete temp;
	}

	void SaveChanges(string address){
		ofstream data;
		data.open(address + "/infoes.txt");

		InfoList* temp = First;
		while (temp != NULL){
			data << temp->info->id << ","
				<< temp->info->Audio_Video->c_str() << ","
				<< temp->info->Cd_Dvd->c_str() << ","
				<< temp->info->Genre->c_str() << ".\n";
			temp = temp->next;
		}
		delete temp;
		data.close();
	}

	void DeleteInfoes(int id){
		if (First->info->id != id){
			InfoList* tempcl = First;
			while (tempcl->next != NULL && tempcl->next->info->id != id) tempcl = tempcl->next;
			if (tempcl->next->next != NULL)
				tempcl->next = tempcl->next->next;
			else
				tempcl->next = NULL;
		}
		else
			First = First->next;
	}
};