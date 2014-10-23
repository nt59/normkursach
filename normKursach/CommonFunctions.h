using namespace std;

bool isNumber(string s){
	bool isNumber = true;
	if (s == "")
		return false;
	for (int i = 0; i < s.length(); i++){
		if (!(s[i] >= '0' && s[i] <= '9')){
			isNumber = false;
			break;
		}
	}
	return isNumber;
}

string* readTo(string s, char c, int& pos){
	string* buf = new string;
	while (s[pos] != c){
		*buf += s[pos++];
	}
	pos++;
	return buf;
}

void PrintError(string s){
	System::ConsoleColor buffer = System::Console::ForegroundColor;
	System::Console::ForegroundColor = System::ConsoleColor::Red;
	cout << s << "\r\n";
	System::Console::ForegroundColor = buffer;
}

int Menu(string s, int count){
	System::ConsoleColor buffer = System::Console::ForegroundColor;
	System::Console::ForegroundColor = System::ConsoleColor::White;
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\r\n";
	int pos = 0;
	cout << "    ���� \"" << *readTo(s, ',', pos) << "\"\r\n\n";
	for (int j = 1; j < count; j++)
		cout << j << " - " << *readTo(s, ',', pos) << endl;
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\r\n";
	System::Console::ForegroundColor = buffer;
	int i = 0;
	string buf;
	while (true){
		cout << "������� �����: ";
		getline(cin, buf);
		if (isNumber(buf)){
			i = atoi(buf.c_str());
			break;
		}
		else
			PrintError("������! ������� �����!\r\n");
	}
	return i;
}

int MainMenu(){
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\r\n";
	cout << "�������� ����� ����: \r\n\n"
		<< " 1 - �������\r\n"
		<< " 2 - ��������� � ���������\r\n"
		<< " 3 - ����\r\n"
		<< " 4 - ����� ���������� � �������\r\n"
		<< " 5 - ����� ������� � �����\r\n"
		<< " 6 - ����� � ����������� ������ ��� ������\r\n"
		<< " 7 - ����� � ���������� ��������� ���������� ������\r\n"
		<< " 8 - ��������� ���������\r\n"
		<< " 9 - ��������� ������\r\n"
		<< " 0 - ����� � ������� ����\r\n"
		<< "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"
		<< "\r\n";
	int selection = 0;
	string buf;
	while (true){
		cout << "������� �����: ";
		getline(cin, buf);
		if (isNumber(buf)){
			selection = atoi(buf.c_str());
			break;
		}
		else
			cout << "������! ������� �����!\r\n";
	}
	return selection;
}
