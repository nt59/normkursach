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
	cout << "    Меню \"" << *readTo(s, ',', pos) << "\"\r\n\n";
	for (int j = 1; j < count; j++)
		cout << j << " - " << *readTo(s, ',', pos) << endl;
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\r\n";
	System::Console::ForegroundColor = buffer;
	int i = 0;
	string buf;
	while (true){
		cout << "Выбрать пункт: ";
		getline(cin, buf);
		if (isNumber(buf)){
			i = atoi(buf.c_str());
			break;
		}
		else
			PrintError("Ошибка! Введите число!\r\n");
	}
	return i;
}

int MainMenu(){
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\r\n";
	cout << "Выберите пункт меню: \r\n\n"
		<< " 1 - Клиенты\r\n"
		<< " 2 - Инфомация о продукции\r\n"
		<< " 3 - Учет\r\n"
		<< " 4 - Связь информации и клиента\r\n"
		<< " 5 - Связь клиента и учета\r\n"
		<< " 6 - Отчет о результатах сессии для группы\r\n"
		<< " 7 - Отчет о получаемой стипендии студентами группы\r\n"
		<< " 8 - Сохранить изменения\r\n"
		<< " 9 - Загрузить данные\r\n"
		<< " 0 - Выход в главное меню\r\n"
		<< "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"
		<< "\r\n";
	int selection = 0;
	string buf;
	while (true){
		cout << "Выбрать пункт: ";
		getline(cin, buf);
		if (isNumber(buf)){
			selection = atoi(buf.c_str());
			break;
		}
		else
			cout << "Ошибка! Введите число!\r\n";
	}
	return selection;
}
