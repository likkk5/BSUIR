package org.example
import java.text.SimpleDateFormat

def x = 10
def y = 25

print 'Sum of x + y = ' + (x + y)
class Person {
  String name
  int age

  // Конструктор класса
  Person(String name, int age) {
    this.name = name
    this.age = age
  }

  // Метод для вывода информации о человеке
  void displayInfo() {
    println("Имя: $name, Возраст: $age лет")
  }

  // Метод для проверки совершеннолетия
  boolean isAdult() {
    return age >= 18
  }

  // Статический метод для создания объекта с возможностью указания только имени
  static Person createWithName(String name) {
    return new Person(name, 0)
  }

  // Геттер, который автоматически добавляет приветствие
  String getGreetings() {
    "Привет, $name!"
  }
}

// Создание объекта Person с использованием статического метода
def person2 = Person.createWithName("Мария")

// Вызов методов объекта
person2.displayInfo()

if (person2.isAdult()) {
  println("${person2.name} совершеннолетняя")
} else {
  println("${person2.name} несовершеннолетняя")
}

// Использование геттера с автоматическим приветствием
println(person2.greetings)

// Использование коллекции для хранения нескольких объектов Person
def people = [
        new Person("Иван", 25),
        new Person("Анна", 17),
        new Person("Петр", 30)
]

// Использование each для итерации по коллекции и вызова метода displayInfo для каждого объекта
people.each { it.displayInfo() }

// Фильтрация с использованием findAll для поиска совершеннолетних
def adults = people.findAll { it.isAdult() }
println "Совершеннолетние: $adults"

class Address {
  String city
  String street

  Address(String city, String street) {
    this.city = city
    this.street = street
  }

  void displayAddress() {
    println("Город: $city, Улица: $street")
  }
}

class ExtendedPerson extends Person {
  Address address

  ExtendedPerson(String name, int age, Address address) {
    super(name, age)
    this.address = address
  }

  // Метод для изменения адреса
  void changeAddress(String city, String street) {
    this.address = new Address(city, street)
  }
}
// Переопределение метода displayInfo для вывода также информации об адресе
void displayInfo() {
  super.displayInfo()
  address.displayAddress()
}


def address1 = new Address("Город1", "Улица1")
def address2 = new Address("Город2", "Улица2")

def extendedPerson1 = new ExtendedPerson("Алексей", 28, address1)
def extendedPerson2 = new ExtendedPerson("Екатерина", 22, address2)

// Создание коллекции из объектов ExtendedPerson
def extendedPeople = [extendedPerson1, extendedPerson2]

// Использование цикла for в стиле Groovy для вывода информации о людях и их адресах
extendedPeople.each {
  it.displayInfo()
}

// Функция, объединяющая имена всех людей в коллекции
String concatenateNames(Collection<Person> people) {
  people.collect { it.name }.join(', ')
}

class Company {
  String companyName
  List<Person> employees
  List<Project> projects

  Company(String companyName) {
    this.companyName = companyName
    this.employees = []
    this.projects = []
  }

  // Метод для добавления нового сотрудника
  void addEmployee(Person employee) {
    employees.add(employee)
  }

  // Метод для добавления нового проекта
  void addProject(Project project) {
    projects.add(project)
  }

  // Метод для отображения информации о компании, ее сотрудниках и проектах
  void displayCompanyInfo() {
    println("Компания: $companyName")
    println("Сотрудники:")
    employees.each { it.displayInfo() }
    println("Проекты:")
    projects.each { it.displayProjectInfo() }
  }

}



// Создание компании
def company1 = new Company("ABC Corporation")

// Добавление сотрудников в компанию
company1.addEmployee(new Person("Иван", 25))
company1.addEmployee(new Person("Анна", 30))

// Отображение информации о компании и ее сотрудниках
company1.displayCompanyInfo()
class Team {
  String teamName
  List<Person> members

  Team(String teamName) {
    this.teamName = teamName
    this.members = []
  }

  // Метод для добавления сотрудника в команду
  void addMember(Person member) {
    members.add(member)
  }

  // Метод для отображения информации о команде и ее членах
  void displayTeamInfo() {
    println("Команда: $teamName")
    println("Члены команды:")
    members.each { it.displayInfo() }
  }
}

// Создание команды
def team1 = new Team("Development Team")

// Добавление сотрудников в команду
team1.addMember(new Person("Алексей", 28))
team1.addMember(new Person("Елена", 24))

// Отображение информации о команде и ее членах
team1.displayTeamInfo()
class Project {
  String projectName
  Team developmentTeam
  Date deadline

  Project(String projectName, Team developmentTeam, Date deadline) {
    this.projectName = projectName
    this.developmentTeam = developmentTeam
    this.deadline = deadline
  }

  // Метод для вычисления времени до завершения проекта
  String getTimeToCompletion() {
    def currentDate = new Date()
    def timeRemainingMillis = deadline.time - currentDate.time
    def daysRemaining = timeRemainingMillis / (24 * 60 * 60 * 1000)
    "${daysRemaining.round()} дней"
  }

  // Метод для отображения информации о проекте
  void displayProjectInfo() {
    println("Проект: $projectName")
    println("Команда разработчиков:")
    developmentTeam.displayTeamInfo()
    println("Срок завершения: ${deadline.format('yyyy-MM-dd')}")
    println("Времени до завершения: ${getTimeToCompletion()}")
  }
}
// Добавим методы для проверки и обработки ошибок
class ErrorHandlingDemo {

  // Метод для создания объекта Person с проверкой возраста
  static Person createPerson(String name, int age) {
    if (age < 0) {
      throw new IllegalArgumentException("Возраст не может быть отрицательным.")
    }
    return new Person(name, age)
  }

  // Метод для создания объекта Address с проверкой наличия данных
  static Address createAddress(String city, String street) {
    if (city.isEmpty() || street.isEmpty()) {
      throw new IllegalArgumentException("Город и улица не могут быть пустыми.")
    }
    return new Address(city, street)
  }
}

// Пример использования
try {
  def personWithNegativeAge = ErrorHandlingDemo.createPerson("John", -5)
} catch (IllegalArgumentException e) {
  println("Ошибка: ${e.message}")
}

try {
  def emptyAddress = ErrorHandlingDemo.createAddress("", "Main Street")
} catch (IllegalArgumentException e) {
  println("Ошибка: ${e.message}")
}
// Использование функции для вывода объединенных имен
println("Объединенные имена: ${concatenateNames(extendedPeople)}")

// Пример цикла for
for (i in 1..5) {
  println("Iteration $i")
}

// Пример цикла while
def count = 0
while (count < 5) {
  println("Count is $count")
  count++
}
// Пример цикла do-while
def number = 1
do {
  println("Number is $number")
  number++
} while (number <= 5)

// Пример конструкции switch
def dayOfWeek = "Wednesday"

switch (dayOfWeek) {
  case "Monday":
    println("It's the beginning of the week!")
    break
  case "Tuesday":
    println("It's another workday.")
    break
  case "Wednesday":
    println("It's the middle of the week.")
    break
  case "Thursday":
    println("The weekend is almost here.")
    break
  case "Friday":
    println("It's Friday! The weekend is here!")
    break
  case "Saturday":
  case "Sunday":
    println("It's the weekend!")
    break
  default:
    println("Not a valid day of the week.")
}
def calculate(s)
{
  def result = (5-2)/(s-3)
  return result
}
def s = 10
def a = calculate(s)