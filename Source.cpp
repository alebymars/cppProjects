#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Data {
    string name; // ��������
    int quantity; // ���-��
    bool availability; // � �������
    float cost; // ���������
};

struct Node {
    struct Data data; // ���� ������

    Node* left; // ����� �������
    Node* right; // ������ �������
};

Node* root; // ������ ������
Node* temp; // �����-�� ���������� ��� ����-�� ���



void printTree_value(Node*&, int); // �������� ���������� �� ��������� 
void printTree_char(Node*&, char); // �� ������ �����
void sort(Node*& T); // �������� ����������
void sort_str(Node*& T); // �������� ����-��
void push(Node*&, struct Data); // �������� ���������� ��������
void push_str(Node*&, struct Data); // ��������� �����
void menu(); // �������� ����
void deleteTree(Node*&); // ������� ������
void fileWrite(Node*&, ofstream&); // ������ � ����
void fileRead(ifstream&); // ������ �����
void printTree(Node*& T); // ����� ������

int main()
{
    menu(); // ����� ����

    return 0;
}

void menu() {

    setlocale(LC_ALL, "rus");

    bool exit = 0;

    do {

        cout << "\n����:\n\n";

        cout << "1. ����������� �� ��������\n";
        cout << "2. ����������� �� ���������\n";
        cout << "3. ������� ������ ������ �������� ���������\n";
        cout << "4. ������� ������ �� ������ �����\n";
        cout << "5. �������� ����� �������\n";
        cout << "6. �������� ������\n";
        cout << "7. ������ �������\n\n";

        cout << "8. ������� � �����\n";
        cout << "9. �������� ������ � ����\n\n";

        cout << "0. �����\n\n";

        cout << "�������� ����� �� ����-> ";
        int choice; cin >> choice; // �����
        cout << endl;

        system("cls"); // ������� ������ �������

        switch (choice) {

        case 1: {

            sort_str(root); // ���������� �� ����� ������

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

            cout << "������� �������� ����� -> ";
            int value; cin >> value;

            system("cls");

            printTree_value(root, value); // ������� ��� ������ 

            system("pause");
            system("cls");

            break;
        }

        case 4: {

            cout << "������� ������ ����� ������ -> ";
            char start_char; cin >> start_char;

            system("cls");

            printTree_char(root, start_char); // ������� ��� ������ 

            system("pause");
            system("cls");

            cout << endl;

            break;
        }

        case 5: {

            struct Data data; // 
            cout << "������� �������� ������: "; cin >> data.name; // ����� �� ���� ������
            cout << "������� ���������: "; cin >> data.cost; // ����� �� ���� ������
            cout << "������� ����������: "; cin >> data.quantity; // ����� �� ���� ������
            cout << "������� �������: "; cin >> data.availability; // ����� �� ���� ������

            system("cls");

            push(root, data); // ���������� �������� 

            break;
        }

        case 6: {

            deleteTree(root); // ��������� ������

            break;
        }


        case 7: {

            system("cls");

            printTree(root); // ����� ������ �� �����

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
            cout << "\n������ ������ ������ ����, ���������� ���������)\n";
            break;
        }


        }



        if (exit == 1) break;
    } while (exit != 1);

    deleteTree(root); // ������� ������

}

void fileWrite(Node*& T, ofstream& fout) {
    if (!T) return;

    fileWrite(T->left, fout); // ������ � �������� �� ���������, ������ � ���� (���������� � ����� ����� ������)

    fout << T->data.name << " " << T->data.cost << " " << T->data.quantity << " " << T->data.availability << endl;

    fileWrite(T->right, fout); // (���������� � ������ ����� ������)
}

void fileRead(ifstream& fin) {

    struct Data data; // ���� ������

    while (fin >> data.name >> data.cost >> data.quantity >> data.availability) push(root, data); 
}

void sort(Node*& T) { // ����������

    if (T) {

        if (T->left) sort(T->left);
        if (T->right) sort(T->right);

        struct Data data = T->data;
        push(temp, data);
        delete T;
        T = NULL;
    }
    else {
        cout << "������ ������";
    }

}

void sort_str(Node*& T) { // ���������� �� ��������

    if (T) {

        if (T->left) sort_str(T->left);
        if (T->right) sort_str(T->right);

        struct Data data = T->data;
        push_str(temp, data);
        delete T;
        T = NULL;
    }
    else {
        cout << "������� ������";
    }

}

void push(Node*& T, struct Data data) { // �-� ���������� ��������

    if (!T) { //���� ������ ���, �� ��������� ������

        T = new Node; // ��������� ������
        T->data = data; // ���������� � ���� ������
        T->left = NULL; // ����� �������������� ��������
        T->right = NULL; // ����� �������������� ��������
        return;
    }

    if (data.cost < T->data.cost) { // ���� ������� � ������ ���������, ������ �����
        push(T->left, data); // ���������� ��������� �������
    }
    else { // ����� ������ ������
        push(T->right, data); // ���������� ��������� ������� ������
    }

}

void push_str(Node*& T, struct Data data) {

    if (!T) {

        T = new Node; // ��������� ������
        T->data = data; // ���������� � ���� ������
        T->left = NULL; // ����� �������������� ��������
        T->right = NULL; // ����� �������������� ��������
        return;
    }

    if (strcmp(data.name.c_str(), T->data.name.c_str()) < 0) { // ��������� �����, 
        push_str(T->left, data); // ������ � ������ ����� ???
    }
    else {
        push_str(T->right, data); // ������ � ������ ???
    }

}

void printTree(Node*& T) {
    if (!T) return; // ���� �� ���������� ������ ����

    printTree(T->left); // ����������� ������� ������ ������ ���������

    cout << "\n��������: " << T->data.name;
    cout << "\n���������: " << T->data.cost << "\t������";
    cout << "\n����������: " << T->data.quantity;
    cout << "\n�������: " << (T->data.availability == 1 ? "� �������" : "��� � ������� ");
    cout << endl;

    printTree(T->right); // ����������� ������� ������ ������ ���������
}

void printTree_value(Node*& T, int value) { // ���������� ��� ���������� �����
    if (!T) return;

    printTree_value(T->left, value);

    if (T->data.cost < value) {
        cout << "\n��������: " << T->data.name;
        cout << "\n���������: " << T->data.cost << "\t������";
        cout << "\n����������: " << T->data.quantity;
        cout << "\n�������: " << (T->data.availability == 1 ? "� �������" : "��� � �������");
        cout << endl;
    }

    printTree_value(T->right, value);
}

void printTree_char(Node*& T, char first_letter) {
    if (!T) return;

    printTree_char(T->left, first_letter); // first_letter - �� ���������� �� ������� ���� �����, ���������� � ��� �����

    if (T->data.name[0] == first_letter) {
        cout << "\n��������: " << T->data.name;
        cout << "\n���������: " << T->data.cost << "\t������";
        cout << "\n����������: " << T->data.quantity;
        cout << "\n�������: " << (T->data.availability == 1 ? "� �������" : "��� � �������");
        cout << endl;
    }

    printTree_char(T->right, first_letter);

}

void deleteTree(Node*& T) {

    if (T) {

        if (T->left) deleteTree(T->left); // ���������� ������� ����� �����
        if (T->right) deleteTree(T->right); // ���������� ������� ������ �����

        delete T;  // ������� ������
        T = NULL;
    }

    else {

        cout << "\n������ ������\n";
    }
}