#include "App.h"

void App::start() {

	List list;

	list.getListFromFile(const_cast<char*>("Date.txt"));

	int key = -1;
	do {

		cout << "\n  _________________________________________"
			<< "\n |                                         |"
			<< "\n |       *** Выберите операцию ***         |"
			<< "\n |                                         |"
			<< "\n |  1) Показать все даты                   |"
			<< "\n |  2) Показать дату - Следующая дата      |"
			<< "\n |  3) Показать системную дату и время     |"
			<< "\n |  0) Выйти                               |"
			<< "\n |_________________________________________|"
			<< "\n  > ";
		cin >> key;

		switch (key)
		{
		case 1: {

			list.listPrint();

			break;
		}

		case 2: {

			list.listPrintSort();

			break;
		}

		case 3: {
			//Вывод системной даты
			datetime sysTime;
			sysTime.showSysDate();
			break;
		}

		default:

			if (key != 0) cout << "\n\nОшибка, номер не найден. Попробуйте еще раз." << endl;

			break;
		}

	} while (key != 0);

}
