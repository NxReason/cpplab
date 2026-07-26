#include "Bar.h"

#include <iostream>

Bar::Bar()
  : Bar("...") {}

Bar::Bar(const std::string& name)
  : m_name(name) {}

void Bar::Update(int value) {
  std::cout << m_name << ": " << value << '\n';
}

void Bar::OnPlayerDamageTaken(EventDetails<Player*, int> details) {
  std::cout << details.sender->GetName() << '\n';
  std::cout << m_name << ": " << details.data << '\n';
}