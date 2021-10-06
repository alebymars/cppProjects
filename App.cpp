#include "App.h"

void App::start() {

	List list;

	list.getListFromFile(const_cast<char*>("Date.txt"));

	int key = -1;
	do {

		cout << "\n  _________________________________________"
			<< "\n |                                         |"
			<< "\n |       *** �������� �������� ***         |"
			<< "\n |                                         |"
			<< "\n |  1) �������� ��� ����                   |"
			<< "\n |  2) �������� ���� - ��������� ����      |"
			<< "\n |  3) �������� ��������� ���� � �����     |"
			<< "\n |  0) �����                               |"
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
			//����� ��������� ����
			datetime sysTime;
			sysTime.showSysDate();
			break;
		}

		default:

			if (key != 0) cout << "\n\n������, ����� �� ������. ���������� ��� ���." << endl;

			break;
		}

	} while (key != 0);

}
