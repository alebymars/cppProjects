#include "Data.h"
#pragma warning(disable : 4996)

int checkData(int left, int right) {

    double temp;
    cout << " Вставить значение между " << left << " и " << right; cin >> temp;
    while (temp<left || temp>right || (temp - (int)temp) > 0) {
        cout << "Неверное значение. Попробуйте снова! "; cin >> temp;
    }

    return temp;
};

void datetime::showInfo() {

    cout << data.hour << ":" << data.minute << ":" << data.sec << " " << data.day << "/" << data.month << "/" << data.year;

}

void datetime::showSysDate() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    cout << "\nСистемная дата: " << buf << endl;
}

void datetime::addData(Data new_data) {

    data = new_data;

}

void List::getListFromFile(char* fileName) {

    int i = 0;

    fileWork file;

    file.countData(fileName, i);

    Data* new_data = new Data[i];

    file.getData(fileName, i, new_data);

    for (int j = 0; j < i; j++) {
        addNode(new_data[j]);
    }

    delete[] new_data;

}

void fileWork::getData(char* fileName, int& i, Data*& data_new) {
    ifstream fin(fileName);

    if (fin) {
        Data new_data;

        int j = 0;

        while (fin >> new_data.hour >> new_data.minute >> new_data.sec >> new_data.day >> new_data.month >> new_data.year) {
            data_new[j] = new_data;
            j++;
        }
    }
    else {
        cout << "Ошибка, с файл с данными не найден.";
    }

    fin.close();
}

void fileWork::countData(char* fileName, int& i) {
    ifstream fin(fileName);

    if (fin) {
        Data new_data;
        while (fin >> new_data.hour >> new_data.minute >> new_data.sec >> new_data.day >> new_data.month >> new_data.year) {
            i++;
        }
    }
    else {
        cout << "Ошибка, с файл с данными не найден.";
    }

    fin.close();
}

void List::addNode(Data new_data) {


    if (first == NULL) {
        Node* temp = new Node;

        temp->next = NULL;
        temp->prev = NULL;

        C = temp;
        first = temp;
        last = temp;

        temp->objPush(new_data);

    }
    else

        if (first != NULL && last != NULL) {
            Node* temp = new Node;
            if (first == last) {


                temp->prev = first;
                temp->next = NULL;
                temp->prev->next = temp;

                C = temp;
                last = temp;

                temp->objPush(new_data);

            }

            if (first != last && C != last) {

                temp->prev = C;
                temp->next = C->next;
                C->next->prev = temp;
                C->next = temp;

                C = temp;

                temp->objPush(new_data);

            }

            if (C == last && first != last) {

                temp->prev = C;
                temp->next = NULL;
                C->next = temp;

                last = temp;
                C = temp;

                temp->objPush(new_data);

            }


        }


}

void List::clearC() {
    C->deleteData();
    delete C;
};

void List::deleteCurrent() {
    if (C == first && C == last) {
        clearC();
        first = NULL;
        last = NULL;
        C = NULL;
    }
    else


        if (C != first && C != last) {
            C->prev->next = C->next;
            C->next->prev = C->prev;

            Node* temp = C->prev;

            clearC();

            C = temp;
        }
        else

            if (C == first && first != last) {
                first = first->next;
                first->prev = NULL;

                clearC();

                C = first;
            }
            else

                if (C == last && first != last) {
                    last = last->prev;
                    last->next = NULL;

                    clearC();

                    C = last;
                }

    cout << "Чистим память (удаляем)!" << endl;

}

void List::deleteAll() {

    C = first;
    while (first != NULL) {
        deleteCurrent();
    }

}

void List::moveNext() {

    if (C != NULL) C = C->next;

};

void List::movePrev() {
    C = C->prev;
};

void List::printNode() {
    C->data->showInfo();
}
//Вывод списка всех дат
void List::listPrint() {

    cout << "\nВывели все даты из файла : \n" << endl;

    if (first != NULL) {

        Node* temp = C;
        C = first;
        while (C != NULL) {

            printNode(); cout << endl;

            moveNext();
        }
    }
}
//Вывод списком даты и следующей даты 
void List::listPrintSort() {

    if (first != NULL) {

        Node* temp = C;
        C = first;
        while (C != NULL) {
            if (C->next != NULL) {
                cout << "\nДата: ";  C->data->showInfo(); 
                cout << "\nСледующая дата: "; C->next->data->showInfo(); 
                cout << endl;
                moveNext();
            }
            if (C->next == NULL) {
                cout << "\nДата: ";  C->data->showInfo(); 
                cout << "\nСледующая дата не найдена..." << endl;
                break;
            }
        }

        C = temp;

    }
}

void Node::objPush(Data new_data) {

    datetime* newObj = new datetime;
    data = newObj;
    newObj->addData(new_data);

}

void Node::deleteData() {
    delete data;
    data = NULL;
}