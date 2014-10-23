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
			PrintError("Ошибка! Введите число!");
	}
	return selection;
}

void makeData(int* day, int* month, int* year)
{
	string buf;
	while (true){
		cout << "Введите число: ";
		getline(cin, buf);
		if (isNumber(buf) && (atoi(buf.c_str()) <= 31) && (atoi(buf.c_str()) >= 1))
		{
			*day = atoi(buf.c_str());
			break;
		}
		else
		{
			PrintError("Ошибка! Введите корректное число!");
		}
	}
	while (true){
		cout << "Введите месяц: ";
		getline(cin, buf);
		if (isNumber(buf) && (atoi(buf.c_str()) <= 12) && (atoi(buf.c_str()) >= 1))
		{
			*month = atoi(buf.c_str());
			break;
		}
		else
		{
			PrintError("Ошибка! Введите корректное число!");
		}
	}
	while (true){
		cout << "Введите год: ";
		getline(cin, buf);
		if (isNumber(buf) && (atoi(buf.c_str()) >= 2014))
		{
			*year = atoi(buf.c_str());
			break;
		}
		else
		{
			PrintError("Ошибка! Введите корректное число!");
		}
	}

}

int getCountDays(int day, int month, int year){
	int daysOfYear = (year - 2014) * 365;
	int daysOfMonth = 0;
	switch (month - 1)
	{
	case 1:
		daysOfMonth = 31;
	case 2:
		daysOfMonth = 59;
	case 3:
		daysOfMonth = 90;
	case 4:
		daysOfMonth = 120;
	case 5:
		daysOfMonth = 151;
	case 6:
		daysOfMonth = 181;
	case 7:
		daysOfMonth = 212;
	case 8:
		daysOfMonth = 243;
	case 9:
		daysOfMonth = 273;
	case 10:
		daysOfMonth = 304;
	case 11:
		daysOfMonth = 334;
	}
	return day + daysOfMonth + daysOfYear;
}

int getData()
{
	int* day = new int;
	int* month = new int;
	int* year = new int;
	makeData(day, month, year);
	return getCountDays(*day, *month, *year);
}

