#include "funs.h"

using namespace std;


void menu()
{
    cout << " ______________________ MENU ______________________\n";
    cout << "|   1 Обработка строки                             |\n";
    cout << "|   2 Посчитать кол-во чисел в строках в файле     |\n";
    cout << "|   3 Создать список студентов                     |\n";
    cout << "|   4 Показать список студентов                    |\n";
    cout << "|   5 Показать студентов без допусков              |\n";
    cout << "|   6 Изменить статус аттестации                   |\n";
    cout << "|__________________________________________________|\n";
    cout << "|   9 Меню                                         |\n";
    cout << "|   0 Выход                                        |\n";
    cout << "|__________________________________________________|\n";
}


int main()
{
    setlocale(LC_ALL, "Rus");

    bool tf = true;
    int o;
    menu();

    while (tf) {
        cout << "Выберите пункт меню: ";
        cin >> o;

        switch (o) {
        case 1:
        {
            char str[256];
            cout << "Введите свою строку:\n"
                    "Обратите внимание, что максимальный размер строки 255 символов!\n"
                    ">> ";
            cin.ignore(1);
            cin.getline(str, 256);
            cout << "\nСтрока: \"" << str << "\"\n";
            change_cstring(str);
            print_cstring(str);
            break;
        }
        case 2:
        {
            string file_name;
            cout << "Введите название файла (без расширения): ";  // TestFile
            cin.ignore(1);
            getline(cin, file_name);
            ifstream file(file_name + ".txt");
            if (!file.is_open())
                cout << "Нет такого файла!\n";
            else {
                // Создаём новый файл, в который будем записывать новые строки
                ofstream temp_file("TempFile.txt");
                if (temp_file.is_open()) {
                    while (!file.eof()) {
                        // Алгоритм считает числа в строке. Учитываються целые и вещественные
                        // Строка "3.14.15" считается за дробное и целое число
                        string row;
                        int k{ 0 };
                        getline(file, row);
                        for (int i{ 0 }; i < row.length(); ++i) {
                            if (isdigit(row[i])) {
                                bool is_dbl = false;
                                while (isdigit(row[i]) || (!is_dbl && row[i] == '.')) {
                                    if (row[i] == '.')
                                        is_dbl = true;
                                    ++i;
                                }
                                ++k;
                            }
                        }
                        // Соединяем количество цифр со строкой через ' ' и выводим в файл
                        row = to_string(k) + " " + row;
                        temp_file << row << '\n';
                    }
                    temp_file.close();
                }
                file.close();
                cout << "Файл успешно обработан (см. сам файл)!\n\n";

                // Удаляем старый файл и меняем название нового файла на имя удалённого файла
                file_name = file_name + ".txt";
                char* filename = new char[file_name.length() + 1];
                for (int i{ 0 }; i <= file_name.length(); ++i) {
                    filename[i] = file_name.c_str()[i];
                }
                remove(filename);
                rename("TempFile.txt", filename);
                delete[] filename;
            }

            
            break;
        }
        case 3:
        {
            cout << "Введите название файла (без расширения): ";
            string bfile_name;
            cin.ignore(1);
            getline(cin, bfile_name);
            create_students_list(bfile_name);
            cout << "Список успешно создан и сохранён в файл " << bfile_name << ".dat!\n\n";
            break;
        }
        case 4:
        {
            cout << "Введите название файла (без расширения): ";
            string bfile_name;
            cin.ignore(1);
            getline(cin, bfile_name);
            try
            {
                read_students_list(bfile_name);
            }
            catch (int)
            {
                cout << "Нет такого файла!\n\n";
            }
            break;
        }
        case 5:
        {
            cout << "Введите название файла (без расширения): ";
            string bfile_name;
            cin.ignore(1);
            getline(cin, bfile_name);
            try
            {
                print_students_without_attestation(bfile_name);
            }
            catch (int)
            {
                cout << "Нет такого файла!\n\n";
            }
            break;
        }
        case 6:
        {
            cout << "Введите название файла (без расширения): ";
            string bfile_name;
            cin.ignore(1);
            getline(cin, bfile_name);
            try
            {
                read_students_list(bfile_name);
                change_attestation(bfile_name);
                cout << "Статус аттестации успешно изменён!\n\n";
            }
            catch (int)
            {
                cout << "Нет такого файла!\n\n";
            }
            break;
        }
        case 9:
            menu();
            break;
        case 0:
            tf = false;
            break;
        default:
            cout << "Нет такого пункта меню!\n\n";
        }
    }


    //system("pause");
    return EXIT_SUCCESS;
}
