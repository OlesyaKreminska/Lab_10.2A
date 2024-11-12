#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <Windows.h>
using namespace std;

enum Spetsialnist { KOMPYUTERNI_NAUKY, INFORMATYKA, MATEMATYKA_TA_EKONOMIKA, FIZYKA_TA_INFORMATYKA, TRUDOVE_NAVCHANNYA };

struct Student {
    string prizv = "";
    int kurs = 0;
    Spetsialnist spetsialnist = KOMPYUTERNI_NAUKY;
    int ozenka_fizyka = 0;
    int ozenka_matematyka = 0;
    int ozenka_informatyka = 0;
    double average_score = 0.0;
};

void Create(Student* s, const int N);
void Print(const Student* s, const int N);
void CalculateAverageScore(Student* s, const int N);
void SortStudents(Student* s, const int N);
void BuildIndexArray(int* indexArray, Student* s, const int N);
int BinarySearch(Student* s, int* indexArray, int N, const string& prizv, double avgScore, int thirdSubjectScore);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: ";
    cin >> N;

    Student* students = new Student[N];
    int* indexArray = new int[N];

    int menuItem;
    do {
        cout << "\nМеню:\n";
        cout << " [1] - введення даних\n";
        cout << " [2] - виведення даних\n";
        cout << " [3] - сортування студентів\n";
        cout << " [4] - пошук студента за прізвищем, середнім балом і оцінкою з інформатики\n";
        cout << " [0] - вихід\n";
        cout << "Введіть ваш вибір: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            Create(students, N);
            CalculateAverageScore(students, N);
            BuildIndexArray(indexArray, students, N);
            break;
        case 2:
            Print(students, N);
            break;
        case 3:
            SortStudents(students, N);
            BuildIndexArray(indexArray, students, N);
            cout << "Список студентів відсортовано за умовами завдання.\n";
            break;
        case 4: {
            string prizv;
            double avgScore;
            int thirdSubjectScore;
            cout << "Введіть прізвище студента для пошуку: ";
            cin.ignore();
            getline(cin, prizv);
            cout << "Введіть середній бал студента: ";
            cin >> avgScore;
            cout << "Введіть оцінку з інформатики: ";
            cin >> thirdSubjectScore;
            int index = BinarySearch(students, indexArray, N, prizv, avgScore, thirdSubjectScore);
            if (index != -1) {
                cout << "Студент знайдений:\n";
                Print(&students[index], 1);
            }
            else {
                cout << "Студента не знайдено.\n";
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "Помилка! Слід вибрати коректний номер.\n";
        }
    } while (menuItem != 0);

    delete[] students;
    delete[] indexArray;
    return 0;
}

void Create(Student* s, const int N) {
    for (int i = 0; i < N; i++) {
        cout << "Студент №" << i + 1 << ":\n";
        s[i] = Student();
        cin.ignore();
        cout << "Прізвище: ";
        getline(cin, s[i].prizv);
        cout << "Курс: ";
        cin >> s[i].kurs;
        cout << "Спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        int sp;
        cin >> sp;
        s[i].spetsialnist = static_cast<Spetsialnist>(sp);
        cout << "Оцінка з фізики: ";
        cin >> s[i].ozenka_fizyka;
        cout << "Оцінка з математики: ";
        cin >> s[i].ozenka_matematyka;
        cout << "Оцінка з інформатики: ";
        cin >> s[i].ozenka_informatyka;
        cout << endl;
    }
}

void CalculateAverageScore(Student* s, const int N) {
    for (int i = 0; i < N; i++) {
        s[i].average_score = (s[i].ozenka_fizyka + s[i].ozenka_matematyka + s[i].ozenka_informatyka) / 3.0;
    }
}

void Print(const Student* s, const int N) {
    cout << "=======================================================================================================\n";
    cout << "| №   | Прізвище     | Курс | Спеціальність       | Фізика          | Математика     | Інформатика    | Середній бал |\n";
    cout << "-------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < N; i++) {
        cout << left << "| " << setw(3) << i + 1 << " ";
        cout << "| " << setw(13) << left << s[i].prizv;
        cout << "| " << setw(4) << s[i].kurs << " ";
        string spets;
        switch (s[i].spetsialnist) {
        case KOMPYUTERNI_NAUKY: spets = "Комп'ютерні науки"; break;
        case INFORMATYKA: spets = "Інформатика"; break;
        case MATEMATYKA_TA_EKONOMIKA: spets = "Математика та економіка"; break;
        case FIZYKA_TA_INFORMATYKA: spets = "Фізика та інформатика"; break;
        case TRUDOVE_NAVCHANNYA: spets = "Трудове навчання"; break;
        }
        cout << "| " << setw(20) << left << spets;
        cout << "| " << setw(16) << s[i].ozenka_fizyka;
        cout << "| " << setw(15) << s[i].ozenka_matematyka;
        cout << "| " << setw(14) << s[i].ozenka_informatyka;
        cout << "| " << setw(13) << s[i].average_score;
        cout << " |\n";
    }
    cout << "=======================================================================================================\n";
}

void SortStudents(Student* s, const int N) {
    sort(s, s + N, [](const Student& a, const Student& b) {
        if (a.average_score != b.average_score) return a.average_score > b.average_score;
        if (a.ozenka_informatyka != b.ozenka_informatyka) return a.ozenka_informatyka > b.ozenka_informatyka;
        return a.prizv > b.prizv;
        });
}

void BuildIndexArray(int* indexArray, Student* s, const int N) {
    for (int i = 0; i < N; i++) indexArray[i] = i;
    sort(indexArray, indexArray + N, [&](int a, int b) {
        if (s[a].average_score != s[b].average_score) return s[a].average_score > s[b].average_score;
        if (s[a].ozenka_informatyka != s[b].ozenka_informatyka) return s[a].ozenka_informatyka > s[b].ozenka_informatyka;
        return s[a].prizv > s[b].prizv;
        });
}

int BinarySearch(Student* s, int* indexArray, int N, const string& prizv, double avgScore, int thirdSubjectScore) {
    int left = 0, right = N - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int idx = indexArray[mid];
        if (s[idx].average_score == avgScore && s[idx].ozenka_informatyka == thirdSubjectScore && s[idx].prizv == prizv) {
            return idx;
        }
        if (s[idx].average_score > avgScore ||
            (s[idx].average_score == avgScore && s[idx].ozenka_informatyka > thirdSubjectScore) ||
            (s[idx].average_score == avgScore && s[idx].ozenka_informatyka == thirdSubjectScore && s[idx].prizv > prizv)) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}
