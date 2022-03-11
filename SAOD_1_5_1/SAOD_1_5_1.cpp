#include <iostream>
#include <set>
#include <locale>
#include <ctime>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DBG_NEW new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW

using namespace std;

int numberOfNodes;

struct Node
{
    int info;
    Node* right;
    Node* left;
};

Node* root;

int CheckedInput(int begin, int end) // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        if (choice < begin || choice > end)
        {
            cout << "Вводите данные корректно: ";
            continue;
        }
        break;
    }
    return choice;
}

int CheckedInput() // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        break;
    }
    return choice;
}

void AddNodes(Node*& pCurr, int aN) // рекурсивная процедура добавления вершины
{
    Node* pTemp;
    int Nl, Nr;
    if (aN == 0)
    {
        pCurr = NULL;
    }
    else
    {
        Nl = aN / 2;
        Nr = aN - Nl - 1;
        pTemp = new Node;
        pTemp->info = rand() % 100;
        AddNodes(pTemp->left, Nl);
        AddNodes(pTemp->right, Nr);
        pCurr = pTemp; 
    }
}

void Print(int info, int lvl) // вывод в консоль текущей вершины
{
    for (int i = 0; i < lvl * 5; i++)
    {
        cout << " ";
    }
    cout << info << "\n";
}

void PrintForward(Node* pCurr ,int lvl) // прямой обход 
{
    if (pCurr != NULL)
    {
        Print(pCurr->info, lvl);
        PrintForward(pCurr->left, ++lvl); --lvl;
        PrintForward(pCurr->right, ++lvl); --lvl;
    }
}

void PrintSymmetric(Node* pCurr, int lvl) // симметричный проход
{
    if (pCurr != NULL)
    {
        PrintSymmetric(pCurr->left, ++lvl); --lvl;
        Print(pCurr->info, lvl);
        PrintSymmetric(pCurr->right, ++lvl); --lvl;
    }
}

void PrintBack(Node* pCurr, int lvl) // обратно-симметрический проход
{
    if (pCurr != NULL)
    {
        PrintBack(pCurr->right, ++lvl); --lvl;
        Print(pCurr->info, lvl);
        PrintBack(pCurr->left, ++lvl); --lvl;
        /*Back(pCurr->left, ++lvl); --lvl;
        Back(pCurr->right, ++lvl); --lvl;
        Print(pCurr->info, lvl);*/
    }
}

void Delete(Node* pTemp) // рекурсивная функция освобождения памяти
{
    if (pTemp != NULL)
    {
        Delete(pTemp->left);
        Delete(pTemp->right);
        delete pTemp->left;
        delete pTemp->right;
    }
}

void CallMenu()
{
    cout << "Введите количество вершин деревьев (с учётом корня) до 30: "; numberOfNodes = CheckedInput(1, 30);
    AddNodes(root, numberOfNodes);
    cout << "Вывод дерева: \n";
    cout << "\nПрямой обход\n"; PrintForward(root, 0);
    cout << "\nСимметричный проход\n"; PrintSymmetric(root, 0);
    cout << "\nОбратно-симметричный проход\n"; PrintBack(root, 0);
    Delete(root);
    delete root;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    CallMenu();
    _CrtDumpMemoryLeaks();
}
