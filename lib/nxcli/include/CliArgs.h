#pragma once

#include <any>
#include <optional>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace nxcli {

struct Arg {
  std::string name;
  std::type_index t = typeid(std::string);
  bool required = true;
  std::any def = nullptr;
  std::optional<std::string> alias = std::nullopt;
};

class CliArgs {
public:
  CliArgs(int argc, char** argv, const std::vector<Arg>& reqs = {}, bool lazy = false);

  void process();

  std::vector<std::string> get_inputs() const;

  std::unordered_map<std::string, std::any> get_args() const;

  template<typename T>
  std::optional<T> try_get_value(const std::string& name) const {
    if (!args.contains(name)) return std::nullopt;
    return std::any_cast<T>(args.at(name));
  }

  template<typename T>
  T get_value(const std::string& name) const {
    return std::any_cast<T>(args.at(name));
  }

  std::unordered_map<std::string, std::string> get_errors() const;

  bool is_valid() const;

  void summary() const;

private:
  enum State {
    INPUTS,
    NEXT_ARG,
    ARG_INPUT,
    ARG_FLAG_INPUT,
  } state;

  int count;
  char** args_raw;
  std::vector<Arg> reqs;

  std::vector<std::string> inputs;
  std::unordered_map<std::string, std::any> args;
  std::unordered_map<std::string, std::string> errors;

  std::string current_arg;

  std::string strip_prefix(const std::string& arg_name) const;

  std::string to_lower(const std::string& in) const;

  bool in_reqs(const std::string& arg_name) const;

  std::optional<Arg> find_arg(const std::string& arg_name) const;

  void set_arg(const std::string& name, const std::string& value);

  const std::vector<std::string> truthy { "true", "t", "1", "on", "yes", "+" };
  const std::vector<std::string> falsy { "false", "f", "0", "off", "no", "-" };
  // return true if the value was consumed
  bool set_flag(const std::string& name, const std::string& value);

  void set_defaults();

  void validate();

  void unknown_arg_err(const std::string& name);

  void missing_arg_err(const std::string& name);

  void missing_val_err(const std::string& name);

  void invalid_val_err(const std::string& name, const std::string& value);

  void conversion_err(const std::string& name, const std::string& value);
};

}