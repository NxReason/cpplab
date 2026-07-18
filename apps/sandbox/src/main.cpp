#include <iostream>
#include <string>

class Vector {
public:
  Vector()
    : x{}, y{}, z{} {}

  int x;
  int y;
  int z;

  void print() const {
    std::cout << x << ", " << y << ", " << z << '\n';
  }
};

class Employee {
private:
  std::string m_name { "???" };
  int m_id { 0 };

public:
  Employee(std::string_view name)
    : Employee { name, 0 } {}
  Employee(std::string_view name, int id)
    : m_name{ name }, m_id { id } {
    std::cout << "Employee " << m_name << " created\n";
  }
  ~Employee() {
    std::cout << "Employee " << m_name << " destroyed\n";
  }

  void print() {
    std::cout << "Employee " << m_name << ", id " << m_id << '\n';
  }
};

int main() {
  Employee e1 { "James" };
  Employee e2 { "Dave", 42 };
  auto e3 = Employee("John");
  Employee e4("Jane");
  return 0;
}