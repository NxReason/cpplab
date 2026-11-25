#include <iostream>
#include <string>
#include <utility>

void print(const std::string& prefix, int&) {
  std::cout << prefix << " is lvalue" << '\n';
}
void print(const std::string& prefix, const int&) {
  std::cout << prefix << " is const lvalue" << '\n';
}
void print(const std::string& prefix, int&&) {
  std::cout << prefix << " is rvalue" << '\n';
}

void value_categories() {
  int val = 42;
  const int c_val = 42;
  int&& rval = 10;
  decltype(40 + 2) sum;
  print("int variable", val);
  print("decltype(int) variable", sum);
  print("const int variable", c_val);
  print("int&& variable", rval);
  print("literal", 42);
  print("arithmetic expr", 40 + 2);
  print("std::move(42)", std::move(42));
  print("std::move(int)", std::move(val));
  print("std::move(const int)", std::move(c_val));
}

// ----------------------------
class StringBuffer {
public:
  StringBuffer(size_t size) 
    : m_data { new char[size + 1] }
    , m_count { 0 }
    , m_size { size }
  {
    std::cout << "Allocating memory constructor" << '\n';
    m_data[0] = '\0';
  }

  // copy
  StringBuffer(const StringBuffer& other) {
    std::cout << "Copying buffer" << '\n';

    m_size = other.m_size;
    m_count = other.m_count;
    m_data = new char[m_size];
    for (size_t i = 0; i < m_count; ++i) {
      m_data[i] = other.m_data[i];
    }
    m_data[m_count] = '\0';
  }

  StringBuffer& operator=(const StringBuffer& other) {
    std::cout << "Copy assignment" << '\n';

    if (this == &other) return *this;

    delete[] m_data;

    m_size = other.m_size;
    m_count = other.m_count;
    m_data = new char[m_size];
    for (size_t i = 0; i < m_count; ++i) {
      m_data[i] = other.m_data[i];
    }
    m_data[m_count] = '\0';

    return *this;
  }

  // move
  StringBuffer(StringBuffer&& other) noexcept {
    std::cout << "Moving buffer" << '\n';
    m_size = other.m_size;
    m_count = other.m_count;
    m_data = other.m_data;

    other.m_count = 0;
    other.m_size = 0;
    other.m_data = nullptr;
  }

  StringBuffer& operator=(StringBuffer&& other) noexcept {
    std::cout << "Move assignment" << '\n';

    if (this == &other) return *this;

    delete[] m_data;

    m_size = other.m_size;
    m_count = other.m_count;
    m_data = other.m_data;

    other.m_count = 0;
    other.m_size = 0;
    other.m_data = nullptr;

    return *this;
  }

  // dctor
  ~StringBuffer() {
    std::cout << "Destructor" << '\n';
    delete[] m_data;
  }

  void put(const char* str) {
    if (str == nullptr) return;

    size_t index = 0;
    while (index < m_size && str[index] != '\0') {
      m_data[index] = str[index];
      index++;
    }
    m_data[index] = '\0';
    m_count = index;
  }

  void print() {
    std::cout << "Size: " << m_size << '\n';
    std::cout << "Count: " << m_count << '\n';
    std::cout << "Data: " << (m_data == nullptr ? "" : m_data) << '\n';
  }

  size_t count() const { return m_count; }
  const char* data() const { return m_data; }
private:
  char* m_data { nullptr };
  size_t m_count { 0 };
  size_t m_size { 0 };
};

void copy_vs_move() {
  StringBuffer sb { 10 };  
  sb.put("hello");
  sb.print();

  StringBuffer sb_copy { sb };
  sb_copy.put("bye");
  sb.print();
  sb_copy.print();

  StringBuffer sb_move { std::move(sb) };
  sb.print();
  sb_move.print();
}

void rule_of_5() {
  StringBuffer sb { 10 };
  sb.put("hello");

  StringBuffer sb_copy { 20 };
  sb_copy = sb;
  sb_copy.put("salute");
  sb.print();
  sb_copy.print();

  StringBuffer sb_move { 2 };
  sb_move = std::move(sb);
  sb.print();
  sb_move.print();
}

// --------------------------
#include <vector>

class GameEntity {
public:
  GameEntity() {
    std::cout << "No args constructor" << '\n';
  }
  GameEntity(const std::string& name, const std::vector<int> inventory, const std::vector<float> stats)
    : name { name }
    , inventory { inventory }
    , stats { stats }
  {
    std::cout << "All args constructor" << '\n';
  }

  GameEntity(const GameEntity& other) {
    std::cout << "GameEntity copy ctor" << '\n';
    name = other.name;
    inventory = other.inventory;
    stats = other.stats;
  }

  GameEntity(GameEntity&& other) noexcept {
    std::cout << "GameEntity move ctor" << '\n';
    name = std::move(other.name);
    inventory = std::move(other.inventory);
    stats = std::move(other.stats);
  }

  ~GameEntity() {
    std::cout << "Destructor" << '\n';
  }

  void print() const {
    std::cout << "Name: " << name << '\n';
    std::cout << "Inventory: " << '\n';
    for (const auto& item : inventory) {
      std::cout << '\t' << item << '\n';
    }
    std::cout << "Stats: " << '\n';
    for (const auto& stat : stats) {
      std::cout << '\t' << stat << '\n';
    }
  }

  std::string name;
  std::vector<int> inventory;
  std::vector<float> stats;
};

GameEntity createGameEntity() {
  return GameEntity { "Player", { 4, 8, 15, 16 }, { 4.2, 13.37} };
}

void move_stl() {
  auto ge = createGameEntity();
  auto copy { ge };
  ge.print();
  copy.print();
  std::cout << "----------------" << '\n';

  auto moved = std::move(ge);
  ge.print();
  moved.print();
  std::cout << "----------------" << '\n';

  std::vector<GameEntity> entities{};
  entities.reserve(10);
  auto entity = createGameEntity();
  std::cout << "vector<GameEntity>" << '\n';
  entities.push_back(createGameEntity());
  std::cout << "----------------" << '\n';
  entities.emplace_back(createGameEntity());
  std::cout << "----------------" << '\n';
  entities.emplace_back("Enemy", std::vector<int>{ 1, 2, 3 }, std::vector<float>{ 4.5 });
  std::cout << "----------------" << '\n';
  entities.push_back(entity);
  std::cout << "----------------" << '\n';
  entities.push_back(std::move(entity));
  std::cout << "----------------" << '\n';
}

int main() {
  move_stl();
  return 0;
}