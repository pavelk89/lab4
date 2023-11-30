#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

template <typename T1, typename T2>
class Pair {
public:
    Pair() {}
    Pair(const T1& first, const T2& second) : first(first), second(second) {}

    void displayPair() const {
        std::cout << first << ": " << second << std::endl;
    }

    void savePairToFile(std::ofstream& outFile) const {
        outFile << first << " " << second << " ";
    }

private:
    T1 first;
    T2 second;
};

template <typename T>
class Grades {
public:
    void inputGrades() {
        std::cout << "Введите оценки по предметам:" << std::endl;

        std::cout << "Количество предметов: ";
        std::cin >> numSubjects;

        subjectGrades.resize(numSubjects);

        for (int i = 0; i < numSubjects; ++i) {
            std::cout << "Оценка за предмет " << i + 1 << ": ";
            std::cin >> subjectGrades[i];
        }

        calculateAverageGrade();
    }

    void displayGrades() const {
        std::cout << "Оценки по предметам: ";
        for (int grade : subjectGrades) {
            std::cout << grade << " ";
        }
        std::cout << std::endl;

        std::cout << "Средний балл: " << averageGrade << std::endl;
    }

    void saveGradesToFile(std::ofstream& outFile) const {
        outFile << numSubjects << " ";
        for (int grade : subjectGrades) {
            outFile << grade << " ";
        }
        outFile << std::endl;
    }

private:
    int numSubjects;
    std::vector<T> subjectGrades;
    double averageGrade;

    void calculateAverageGrade() {
        if (numSubjects == 0) {
            averageGrade = 0.0;
            return;
        }

        T sum = 0;
        for (T grade : subjectGrades) {
            sum += grade;
        }

        averageGrade = static_cast<double>(sum) / numSubjects;
    }
};

class Student {
public:
    Student(const std::string& firstName, const std::string& lastName, const std::string& group)
        : firstName(firstName), lastName(lastName), group(group) {}

    ~Student() {}

    const std::string& getFirstName() const {
        return firstName;
    }

    const std::string& getLastName() const {
        return lastName;
    }

    const std::string& getGroup() const {
        return group;
    }

    void setFirstName(const std::string& newFirstName) {
        firstName = newFirstName;
    }

    void setLastName(const std::string& newLastName) {
        lastName = newLastName;
    }

    void setGroup(const std::string& newGroup) {
        group = newGroup;
    }

    void displayInfo() const {
        std::cout << "Студент: " << firstName << " " << lastName << ", Группа: " << group;
        grades.displayGrades();
    }

    void inputGrades() {
        grades.inputGrades();
    }

    void saveToFile(std::ofstream& outFile) const {
        outFile << firstName << " " << lastName << " " << group << " ";
        grades.saveGradesToFile(outFile);
    }

    static bool compareByLastName(const Student* student1, const Student* student2) {
        return student1->getLastName() < student2->getLastName();
    }

private:
    std::string firstName;
    std::string lastName;
    std::string group;
    Grades<int> grades;  // Изменил на Grades<int> для использования целочисленных оценок
};

void modifyStudent(Student* student) {
    std::cout << "Студент найден. Что вы хотите изменить?" << std::endl;
    std::cout << "1. Имя" << std::endl;
    std::cout << "2. Фамилия" << std::endl;
    std::cout << "3. Группа" << std::endl;
    std::cout << "4. Оценки" << std::endl;

    int choice;
    std::cout << "Введите ваш выбор: ";
    std::cin >> choice;

    switch (choice) {
        case 1: {
            std::string newName;
            std::cout << "Введите новое имя: ";
            std::cin >> newName;
            student->setFirstName(newName);
            break;
        }
        case 2: {
            std::string newLastName;
            std::cout << "Введите новую фамилию: ";
            std::cin >> newLastName;
            student->setLastName(newLastName);
            break;
        }
        case 3: {
            std::string newGroup;
            std::cout << "Введите новую группу: ";
            std::cin >> newGroup;
            student->setGroup(newGroup);
            break;
        }
        case 4:
            student->inputGrades();
            break;
        default:
            std::cout << "Неверный выбор." << std::endl;
    }
}

void saveStudentsToFile(const std::vector<Student*>& students, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия файла для записи." << std::endl;
        return;
    }

    for (const auto* student : students) {
        student->saveToFile(outFile);
    }

    outFile.close();
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::vector<Student*> students;

    int choice;
    std::string filename;

    do {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Добавить студента" << std::endl;
        std::cout << "2. Изменить данные о студенте" << std::endl;
        std::cout << "3. Удалить студента" << std::endl;
        std::cout << "4. Найти студента" << std::endl;
        std::cout << "5. Вывести список студентов" << std::endl;
        std::cout << "6. Сохранить в файл" << std::endl;
        std::cout << "7. Сортировать по фамилии" << std::endl;
        std::cout << "8. Выход" << std::endl;

        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string firstName, lastName, group;

                std::cout << "Введите данные студента:" << std::endl;
                std::cout << "Имя: ";
                std::cin >> firstName;
                std::cout << "Фамилия: ";
                std::cin >> lastName;
                std::cout << "Группа: ";
                std::cin >> group;

                students.push_back(new Student(firstName, lastName, group));
                students.back()->inputGrades();

                break;
            }
            case 2: {
                std::string firstName, lastName;
                std::cout << "Введите данные студента для изменения:" << std::endl;
                std::cout << "Имя: ";
                std::cin >> firstName;
                std::cout << "Фамилия: ";
                std::cin >> lastName;

                auto it = std::find_if(students.begin(), students.end(), [&](const Student* student) {
                    return student->getFirstName() == firstName && student->getLastName() == lastName;
                });

                if (it != students.end()) {
                    modifyStudent(*it);
                } else {
                    std::cout << "Студент не найден." << std::endl;
                }

                break;
            }
            case 3: {
                std::string firstName, lastName;
                std::cout << "Введите данные студента для удаления:" << std::endl;
                std::cout << "Имя: ";
                std::cin >> firstName;
                std::cout << "Фамилия: ";
                std::cin >> lastName;

                auto it = std::find_if(students.begin(), students.end(), [&](const Student* student) {
                    return student->getFirstName() == firstName && student->getLastName() == lastName;
                });

                if (it != students.end()) {
                    delete *it;
                    students.erase(it);
                    std::cout << "Студент удален." << std::endl;
                } else {
                    std::cout << "Студент не найден." << std::endl;
                }

                break;
            }
            case 4: {
                std::string firstName, lastName;
                std::cout << "Введите данные студента для поиска:" << std::endl;
                std::cout << "Имя: ";
                std::cin >> firstName;
                std::cout << "Фамилия: ";
                std::cin >> lastName;

                auto it = std::find_if(students.begin(), students.end(), [&](const Student* student) {
                    return student->getFirstName() == firstName && student->getLastName() == lastName;
                });

                if (it != students.end()) {
                    (*it)->displayInfo();
                } else {
                    std::cout << "Студент не найден." << std::endl;
                }

                break;
            }
            case 5: {
                std::cout << "Список студентов:" << std::endl;
                for (const auto* student : students) {
                    student->displayInfo();
                }
                break;
            }
            case 6: {
                std::cout << "Введите имя файла для сохранения данных: ";
                std::cin >> filename;
                saveStudentsToFile(students, filename);
                break;
            }
            case 7: {
                std::sort(students.begin(), students.end(), Student::compareByLastName);
                std::cout << "Список студентов отсортирован по фамилии." << std::endl;
                break;
            }
            case 8:
                std::cout << "Выход." << std::endl;
                break;
            default:
                std::cout << "Неверный выбор." << std::endl;
        }
    } while (choice != 8);

    for (const auto* student : students) {
        delete student;
    }

    return 0;
}
