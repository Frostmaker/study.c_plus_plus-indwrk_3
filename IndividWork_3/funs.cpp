#include "funs.h"

using namespace std;


/// <summary>
/// Функция печатает строку
/// </summary>
/// <param name="str"></param>
void print_cstring(char* str)
{
	cout << "Строка: \"";
	while (*str != '\0') {
		cout << *str;
		*str++;
	}
	cout << "\"\n\n";

	return;
}


/// <summary>
/// Функция в каждой последовательности подряд идущих пробелов
/// заменяет все пробелы, кроме первого на символ *
/// </summary>
/// <param name="str"> — массив символов</param>
void change_cstring(char* str)
{
	bool second_space{ false };  // Позволяет отличать первый пробел от остальных
	while (*str != '\0') {
		if (isspace(*str) && second_space)  // Если пробел и перед ним уже был(и) пробелы
			*str = '*';
		else if (isspace(*str))  // Если первый пробел
			second_space = true;
		else if (!isspace(*str) && second_space)  // Если уже НЕ пробел, но перед ним был пробел
			second_space = false;
		*str++;
	}

	return;
}


/// <summary>
/// Функция создаёт список студентов и сохраняет его в файл
/// </summary>
/// <param name="bfile_name"> — имя нового файла для сохранения списка</param>
void create_students_list(string bfile_name)
{
	cout << "Инструкция:\n";
	cout << "Имя студента вводиться в формате — Фамилия И. О.\n";
	cout << "Номер зачёт. книжки в формате — АА0000\n";
	cout << "Если у студента есть аттестация по предмету, то ставиться 1, иначе 0\n\n";

	int n{};
	cout << "Введите кол-во студентов: ";
	cin >> n;


	fstream bfile(bfile_name + ".dat", ios::binary | ios::out);
	if (!bfile.is_open())
		throw - 1;
	else {
		// Записываем в файл кол-во студентов для удобства
		bfile.write(reinterpret_cast<char*>(&n), sizeof(int));

		// Заполняем поля структуры и записываем в файл
		for (int i{ 1 }; i <= n; ++i) {
			Student stud;
			cout << "Введите фамилию и инициалы " << i << "-го студента: ";
			cin.ignore(1);
			cin.getline(stud.Name, 50);

			cout << "Введите номер зачётки " << i << "-го студента: ";
			cin >> stud.number;

			cout << "Введите аттестации " << i << "-го студента: \n";
			cout << "Математика — \t";	cin >> stud.attestation[0];
			cout << "Русский — \t";	cin >> stud.attestation[1];
			cout << "Программирование — \t";	cin >> stud.attestation[2];
			cout << "Философия — \t";	cin >> stud.attestation[3];
			cout << "Экономика — \t";	cin >> stud.attestation[4];

			bfile.write(reinterpret_cast<char*>(&stud), sizeof(Student));
		}
		bfile.close();
	}

	return;
}


/// <summary>
/// Функция выводит список студентов из файла в консоль
/// </summary>
/// <param name="bfile_name"> — имя файла со списком студентов</param>
void read_students_list(string bfile_name)
{
	fstream bfile(bfile_name + ".dat", ios::binary | ios::in);
	if (!bfile.is_open())
		throw - 1;
	else {
		int k{ 1 }, n;  // k – счётчик для студентов; n – кол-во студентов из файла
		bfile.read(reinterpret_cast<char*>(&n), sizeof(int));
		
		// Вывод таблицы студентов
		cout << "  № | " << setw(20) << "Фамилия И. О." << " | " << setw(13) << "Номер зачётки" << " | М Р П Ф Э\n";
		for (int k{ 1 }; k <= n; ++k) {
			Student stud;
			bfile.read(reinterpret_cast<char*>(&stud), sizeof(Student));
			cout << setw(3) << k << " | " << setw(20) << stud.Name << " | " << setw(13) << stud.number << " | ";
			for (int i{ 0 }; i < 5; ++i) {
				cout << stud.attestation[i] << ' ';
			}
			cout << '\n';
		}
		cout << '\n';
		bfile.close();
	}

	return;
}


/// <summary>
/// Функция выводит студентов, у которых нет ни одной аттестации
/// </summary>
/// <param name="bfile_name"> — имя файла со списком студентов</param>
void print_students_without_attestation(string bfile_name)
{
	fstream bfile(bfile_name + ".dat", ios::binary | ios::in);
	if (!bfile.is_open())
		throw - 1;
	else {
		int k{ 1 }, n;
		bfile.read(reinterpret_cast<char*>(&n), sizeof(int));
		cout << "Список студентов, которые не имеют ни одной аттестации:\n";
		cout << "  № | " << setw(20) << "Фамилия И. О." << " | " << setw(13) << "Номер зачётки" << " | М Р П Ф Э\n";
		Student stud;
		while (bfile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {

			// Если у студента есть хоть одна аттестация его пропускаем
			bool tf{ true };
			for (int i{ 0 }; i < 5; ++i) {
				if (stud.attestation[i] == 1) {
					tf = false;
					break;
				}
			}

			if (tf) {
				cout << setw(3) << k << " | " << setw(20) << stud.Name << " | " << setw(13) << stud.number << " | ";
				for (int i{ 0 }; i < 5; ++i) {
					cout << stud.attestation[i] << ' ';
				}
				cout << '\n';
				++k;
			}
		}
		cout << '\n';
		bfile.close();
	}

	return;
}


/// <summary>
/// Функция меняет статус аттестации студента по номеру зачётки
/// </summary>
/// <param name="bfile_name"> — имя файла со списком студентов</param>
void change_attestation(string bfile_name)
{
	fstream bfile(bfile_name + ".dat", ios::binary | ios::in | ios::out);
	if (!bfile.is_open())
		throw - 1;
	else {

		// Пользователь вводит номер зачётки и номер предмета, который хочет изменить
		char num[7];
		int subject;
		cout << "Напишите номер зачётки — ";
		cin.getline(num, 7);
		cout << "Выберите номер предмета, у которого хотите изменить статус аттестации (М-1, Р-2, П-3, Ф-4, Э-5): ";
		cin >> subject;
		bfile.seekg(sizeof(int), ios::beg);
		int size{ sizeof(Student) };
		Student stud;
		while (bfile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
			// Проходимся по файлу и ищем нужную зачёт. книжку
			bool tf{ true };
			for (int i{ 0 }; i < strlen(num); ++i) {
				if (stud.number[i] != num[i]) {
					tf = false;
					break;
				}
			}

			// Когда нашли, переписывем структуру с изменённым статусом аттестации
			if (tf) {
				stud.attestation[subject - 1] = not stud.attestation[subject - 1];
				bfile.seekg(-size, ios::cur);
				bfile.write(reinterpret_cast<char*>(&stud), sizeof(Student));
				break;
			}

		}
		bfile.close();
	}
	return;
}