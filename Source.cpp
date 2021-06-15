#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Data {
    string name; // название
    int quantity; // кол-во
    bool availability; // в наличие
    float cost; // стоимость
};

struct Node {
    struct Data data; // поле данных

    Node* left; // левый потомок
    Node* right; // правой потомок
};

Node* root; // корень дерева
Node* temp; // какая-то переменная для чего-то там



void printTree_value(Node*&, int); // прототип сортировки по стоимости 
void printTree_char(Node*&, char); // по первой букве
void sort(Node*& T); // прототип сортировки
void sort_str(Node*& T); // прототип чего-то
void push(Node*&, struct Data); // прототип добавления элемента
void push_str(Node*&, struct Data); // сравнение строк
void menu(); // прототип меню
void deleteTree(Node*&); // очистка дерева
void fileWrite(Node*&, ofstream&); // запись в файл
void fileRead(ifstream&); // чтение файла
void printTree(Node*& T); // вывод дерева

int main()
{
    menu(); // вывод меню

    return 0;
}

void menu() {

    setlocale(LC_ALL, "rus");

    bool exit = 0;

    do {

        cout << "\nМеню:\n\n";

        cout << "1. Сортировать по названию\n";
        cout << "2. Сортировать по стоимости\n";
        cout << "3. Вывести товары меньше заданной стоимости\n";
        cout << "4. Вывести товары по первой букве\n";
        cout << "5. Добавить новый элемент\n";
        cout << "6. Очистить дерево\n";
        cout << "7. Печать товаров\n\n";

        cout << "8. Считать с файла\n";
        cout << "9. Добавить товары в файл\n\n";

        cout << "0. Выход\n\n";

        cout << "Выберите пункт из меню-> ";
        int choice; cin >> choice; // выбор
        cout << endl;

        system("cls"); // очистка экрана консоли

        switch (choice) {

        case 1: {

            sort_str(root); // сортировка по корню дерева

            root = temp;
            temp = NULL;

            break;
        }

        case 2: {

            sort(root);

            root = temp;
            temp = NULL;

            break;
        }

        case 3: {

            cout << "Введите желаемое число -> ";
            int value; cin >> value;

            system("cls");

            printTree_value(root, value); // функция для вывода 

            system("pause");
            system("cls");

            break;
        }

        case 4: {

            cout << "Введите первую букву товара -> ";
            char start_char; cin >> start_char;

            system("cls");

            printTree_char(root, start_char); // функция для вывода 

            system("pause");
            system("cls");

            cout << endl;

            break;
        }

        case 5: {

            struct Data data; // 
            cout << "Введите название товара: "; cin >> data.name; // берем из поля данных
            cout << "Введите стоимость: "; cin >> data.cost; // берем из поля данных
            cout << "Введите количество: "; cin >> data.quantity; // берем из поля данных
            cout << "Введите наличие: "; cin >> data.availability; // берем из поля данных

            system("cls");

            push(root, data); // добавление элемента 

            break;
        }

        case 6: {

            deleteTree(root); // удаленеие дерева

            break;
        }


        case 7: {

            system("cls");

            printTree(root); // вывод дерева от корня

            system("pause");
            system("cls");

            break;
        }

        case 0: {

            exit = 1;

            break;
        }

        case 8: {

            ifstream fin("tree.txt");

            fileRead(fin);

            break;
        }

        case 9: {

            ofstream fout("tree.txt", ios::trunc);

            fileWrite(root, fout);

            break;
        }

        default: {
            cout << "\nОшибка выбора пункта меню, пожалуйста повторите)\n";
            break;
        }


        }



        if (exit == 1) break;
    } while (exit != 1);

    deleteTree(root); // очистка дерева

}

void fileWrite(Node*& T, ofstream& fout) {
    if (!T) return;

    fileWrite(T->left, fout); // доступ к элементу по указателю, запись в файл (добавление в левую часть дерева)

    fout << T->data.name << " " << T->data.cost << " " << T->data.quantity << " " << T->data.availability << endl;

    fileWrite(T->right, fout); // (добавление в правую часть дерева)
}

void fileRead(ifstream& fin) {

    struct Data data; // узел дерева

    while (fin >> data.name >> data.cost >> data.quantity >> data.availability) push(root, data); 
}

void sort(Node*& T) { // сортировка

    if (T) {

        if (T->left) sort(T->left);
        if (T->right) sort(T->right);

        struct Data data = T->data;
        push(temp, data);
        delete T;
        T = NULL;
    }
    else {
        cout << "Дерево пустое";
    }

}

void sort_str(Node*& T) { // сортировка по названию

    if (T) {

        if (T->left) sort_str(T->left);
        if (T->right) sort_str(T->right);

        struct Data data = T->data;
        push_str(temp, data);
        delete T;
        T = NULL;
    }
    else {
        cout << "Деревое пустое";
    }

}

void push(Node*& T, struct Data data) { // ф-я добавления элемента

    if (!T) { //если дерева нет, то формируем корень

        T = new Node; // выделение памяти
        T->data = data; // записываем в поле данных
        T->left = NULL; // ветви инициализируем пустотой
        T->right = NULL; // ветви инициализируем пустотой
        return;
    }

    if (data.cost < T->data.cost) { // Если элемент х меньше корневого, уходим влево
        push(T->left, data); // рекурсивно добавляем элемент
    }
    else { // иначе уходим вправо
        push(T->right, data); // рекурсивно добавляем элемент вправо
    }

}

void push_str(Node*& T, struct Data data) {

    if (!T) {

        T = new Node; // выделение памяти
        T->data = data; // записываем в поле данных
        T->left = NULL; // ветви инициализируем пустотой
        T->right = NULL; // ветви инициализируем пустотой
        return;
    }

    if (strcmp(data.name.c_str(), T->data.name.c_str()) < 0) { // сравнение строк, 
        push_str(T->left, data); // запись в дерево слева ???
    }
    else {
        push_str(T->right, data); // запись в дерево ???
    }

}

void printTree(Node*& T) {
    if (!T) return; // пока не встретится пустой узел

    printTree(T->left); // рекурсивная функция вывода левого поддерева

    cout << "\nНазвание: " << T->data.name;
    cout << "\nСтоимость: " << T->data.cost << "\tрублей";
    cout << "\nКоличество: " << T->data.quantity;
    cout << "\nНаличие: " << (T->data.availability == 1 ? "В наличии" : "Нет в наличии ");
    cout << endl;

    printTree(T->right); // рекурсивная функция вывода левого поддерева
}

void printTree_value(Node*& T, int value) { // переменная для введенного числа
    if (!T) return;

    printTree_value(T->left, value);

    if (T->data.cost < value) {
        cout << "\nНазвание: " << T->data.name;
        cout << "\nСтоимость: " << T->data.cost << "\tрублей";
        cout << "\nКоличество: " << T->data.quantity;
        cout << "\nНаличие: " << (T->data.availability == 1 ? "В наличии" : "Нет в наличии");
        cout << endl;
    }

    printTree_value(T->right, value);
}

void printTree_char(Node*& T, char first_letter) {
    if (!T) return;

    printTree_char(T->left, first_letter); // first_letter - та переменная по которой ищем товар, записываем в нее букву

    if (T->data.name[0] == first_letter) {
        cout << "\nНазвание: " << T->data.name;
        cout << "\nСтоимость: " << T->data.cost << "\tрублей";
        cout << "\nКоличество: " << T->data.quantity;
        cout << "\nНаличие: " << (T->data.availability == 1 ? "В наличии" : "Нет в наличии");
        cout << endl;
    }

    printTree_char(T->right, first_letter);

}

void deleteTree(Node*& T) {

    if (T) {

        if (T->left) deleteTree(T->left); // рекурсивно удаляем левую ветку
        if (T->right) deleteTree(T->right); // рекурсивно удаляем правую ветку

        delete T;  // удаляем корень
        T = NULL;
    }

    else {

        cout << "\nДерево пустое\n";
    }
}