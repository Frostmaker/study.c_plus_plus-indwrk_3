#include "funs.h"

using namespace std;


/// <summary>
/// ������� �������� ������
/// </summary>
/// <param name="str"></param>
void print_cstring(char* str)
{
	cout << "������: \"";
	while (*str != '\0') {
		cout << *str;
		*str++;
	}
	cout << "\"\n\n";

	return;
}


/// <summary>
/// ������� � ������ ������������������ ������ ������ ��������
/// �������� ��� �������, ����� ������� �� ������ *
/// </summary>
/// <param name="str"> � ������ ��������</param>
void change_cstring(char* str)
{
	bool second_space{ false };  // ��������� �������� ������ ������ �� ���������
	while (*str != '\0') {
		if (isspace(*str) && second_space)  // ���� ������ � ����� ��� ��� ���(�) �������
			*str = '*';
		else if (isspace(*str))  // ���� ������ ������
			second_space = true;
		else if (!isspace(*str) && second_space)  // ���� ��� �� ������, �� ����� ��� ��� ������
			second_space = false;
		*str++;
	}

	return;
}


/// <summary>
/// ������� ������ ������ ��������� � ��������� ��� � ����
/// </summary>
/// <param name="bfile_name"> � ��� ������ ����� ��� ���������� ������</param>
void create_students_list(string bfile_name)
{
	cout << "����������:\n";
	cout << "��� �������� ��������� � ������� � ������� �. �.\n";
	cout << "����� �����. ������ � ������� � ��0000\n";
	cout << "���� � �������� ���� ���������� �� ��������, �� ��������� 1, ����� 0\n\n";

	int n{};
	cout << "������� ���-�� ���������: ";
	cin >> n;


	fstream bfile(bfile_name + ".dat", ios::binary | ios::out);
	if (!bfile.is_open())
		throw - 1;
	else {
		// ���������� � ���� ���-�� ��������� ��� ��������
		bfile.write(reinterpret_cast<char*>(&n), sizeof(int));

		// ��������� ���� ��������� � ���������� � ����
		for (int i{ 1 }; i <= n; ++i) {
			Student stud;
			cout << "������� ������� � �������� " << i << "-�� ��������: ";
			cin.ignore(1);
			cin.getline(stud.Name, 50);

			cout << "������� ����� ������� " << i << "-�� ��������: ";
			cin >> stud.number;

			cout << "������� ���������� " << i << "-�� ��������: \n";
			cout << "���������� � \t";	cin >> stud.attestation[0];
			cout << "������� � \t";	cin >> stud.attestation[1];
			cout << "���������������� � \t";	cin >> stud.attestation[2];
			cout << "��������� � \t";	cin >> stud.attestation[3];
			cout << "��������� � \t";	cin >> stud.attestation[4];

			bfile.write(reinterpret_cast<char*>(&stud), sizeof(Student));
		}
		bfile.close();
	}

	return;
}


/// <summary>
/// ������� ������� ������ ��������� �� ����� � �������
/// </summary>
/// <param name="bfile_name"> � ��� ����� �� ������� ���������</param>
void read_students_list(string bfile_name)
{
	fstream bfile(bfile_name + ".dat", ios::binary | ios::in);
	if (!bfile.is_open())
		throw - 1;
	else {
		int k{ 1 }, n;  // k � ������� ��� ���������; n � ���-�� ��������� �� �����
		bfile.read(reinterpret_cast<char*>(&n), sizeof(int));
		
		// ����� ������� ���������
		cout << "  � | " << setw(20) << "������� �. �." << " | " << setw(13) << "����� �������" << " | � � � � �\n";
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
/// ������� ������� ���������, � ������� ��� �� ����� ����������
/// </summary>
/// <param name="bfile_name"> � ��� ����� �� ������� ���������</param>
void print_students_without_attestation(string bfile_name)
{
	fstream bfile(bfile_name + ".dat", ios::binary | ios::in);
	if (!bfile.is_open())
		throw - 1;
	else {
		int k{ 1 }, n;
		bfile.read(reinterpret_cast<char*>(&n), sizeof(int));
		cout << "������ ���������, ������� �� ����� �� ����� ����������:\n";
		cout << "  � | " << setw(20) << "������� �. �." << " | " << setw(13) << "����� �������" << " | � � � � �\n";
		Student stud;
		while (bfile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {

			// ���� � �������� ���� ���� ���� ���������� ��� ����������
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
/// ������� ������ ������ ���������� �������� �� ������ �������
/// </summary>
/// <param name="bfile_name"> � ��� ����� �� ������� ���������</param>
void change_attestation(string bfile_name)
{
	fstream bfile(bfile_name + ".dat", ios::binary | ios::in | ios::out);
	if (!bfile.is_open())
		throw - 1;
	else {

		// ������������ ������ ����� ������� � ����� ��������, ������� ����� ��������
		char num[7];
		int subject;
		cout << "�������� ����� ������� � ";
		cin.getline(num, 7);
		cout << "�������� ����� ��������, � �������� ������ �������� ������ ���������� (�-1, �-2, �-3, �-4, �-5): ";
		cin >> subject;
		bfile.seekg(sizeof(int), ios::beg);
		int size{ sizeof(Student) };
		Student stud;
		while (bfile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
			// ���������� �� ����� � ���� ������ �����. ������
			bool tf{ true };
			for (int i{ 0 }; i < strlen(num); ++i) {
				if (stud.number[i] != num[i]) {
					tf = false;
					break;
				}
			}

			// ����� �����, ����������� ��������� � ��������� �������� ����������
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