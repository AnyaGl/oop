#define CATCH_CONFIG_MAIN
#include "../People/AdvancedStudent.h"
#include "../People/IPerson.h"
#include "../People/IStudent.h"
#include "../People/Pupil.h"
#include "../People/Student.h"
#include "../People/Teacher.h"
#include "../People/Worker.h"
#include "catch2/catch.hpp"
#include <string>

struct ExpectedPerson
{
	std::string name;
	std::string patronymic;
	std::string surname;
	std::string address;
};

struct ExpectedStudent
{
	std::string universityName;
	std::string studentCardNumber;
};

void CheckPerson(IPerson* person, const ExpectedPerson& expectedPerson)
{
	CHECK(person->GetName() == expectedPerson.name);
	CHECK(person->GetPatronymic() == expectedPerson.patronymic);
	CHECK(person->GetSurname() == expectedPerson.surname);
	CHECK(person->GetAddress() == expectedPerson.address);
}

void CheckStudent(IStudent* student, const ExpectedStudent& expectedStudent)
{
	CHECK(student->GetUniversityName() == expectedStudent.universityName);
	CHECK(student->GetStudentCardNumber() == expectedStudent.studentCardNumber);
}

TEST_CASE("Worker must have name, patronymic, surname, address, speciality")
{
	CWorker worker;
	worker.SetName("Vladimir");
	worker.SetSurname("Zolotov");
	worker.SetPatronymic("Ivanovich");
	worker.SetAddress("st. Sovetskaya");
	worker.SetSpeciality("Programmer");

	ExpectedPerson expectedPerson{ "Vladimir", "Ivanovich", "Zolotov", "st. Sovetskaya" };

	CHECK(worker.GetSpeciality() == "Programmer");
	CheckPerson(&worker, expectedPerson);
}

TEST_CASE("Teacher must have name, patronymic, surname, address, subject")
{
	CTeacher teacher;
	teacher.SetName("Vladimir");
	teacher.SetSurname("Zolotov");
	teacher.SetPatronymic("Ivanovich");
	teacher.SetAddress("st. Sovetskaya");
	teacher.SetSubject("Math");

	ExpectedPerson expectedPerson{ "Vladimir", "Ivanovich", "Zolotov", "st. Sovetskaya" };

	CHECK(teacher.GetSubject() == "Math");
	CheckPerson(&teacher, expectedPerson);
}

TEST_CASE("Student must have name, patronymic, surname, address, universityName, studentCardNumber")
{
	CStudent student;
	student.SetName("Vladimir");
	student.SetSurname("Zolotov");
	student.SetPatronymic("Ivanovich");
	student.SetAddress("st. Sovetskaya");
	student.SetUniversityName("Volga State University of Technology");
	student.SetStudentCardNumber("S1234567890");

	ExpectedPerson expectedPerson{ "Vladimir", "Ivanovich", "Zolotov", "st. Sovetskaya" };
	ExpectedStudent expectedStudent{ "Volga State University of Technology", "S1234567890" };

	CheckPerson(&student, expectedPerson);
	CheckStudent(&student, expectedStudent);
}

TEST_CASE("Advanced student must have name, patronymic, surname, address, universityName, studentCardNumber, dissertationTopic")
{
	CAdvancedStudent student;
	student.SetName("Vladimir");
	student.SetSurname("Zolotov");
	student.SetPatronymic("Ivanovich");
	student.SetAddress("st. Sovetskaya");
	student.SetUniversityName("Volga State University of Technology");
	student.SetStudentCardNumber("S1234567890");
	student.SetDissertationTopic("Something");

	ExpectedPerson expectedPerson{ "Vladimir", "Ivanovich", "Zolotov", "st. Sovetskaya" };
	ExpectedStudent expectedStudent{ "Volga State University of Technology", "S1234567890" };

	CHECK(student.GetDissertationTopic() == "Something");
	CheckPerson(&student, expectedPerson);
	CheckStudent(&student, expectedStudent);
}

TEST_CASE("Pupil must have name, patronymic, surname, address, schoolName, grade")
{
	CPupil pupil;
	pupil.SetName("Vladimir");
	pupil.SetSurname("Zolotov");
	pupil.SetPatronymic("Ivanovich");
	pupil.SetAddress("st. Sovetskaya");
	pupil.SetSchoolName("Meggatech");
	pupil.SetGrade("10.1");

	ExpectedPerson expectedPerson{ "Vladimir", "Ivanovich", "Zolotov", "st. Sovetskaya" };

	CHECK(pupil.GetSchoolName() == "Meggatech");
	CHECK(pupil.GetGrade() == "10.1");
	CheckPerson(&pupil, expectedPerson);
}
