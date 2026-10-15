#include "CliArgs.h"

#include <iostream>
#include <stdexcept>


namespace nxcli {

CliArgs::CliArgs(int argc, char** argv, const std::vector<Arg>& reqs, bool lazy)
: count { argc }, args_raw { argv }, reqs { reqs } {
  if (lazy) return;
  process();
}

void CliArgs::process() {
  if (count > 1) {
    auto first = std::string(args_raw[1]);
    state = first.starts_with("-") ? NEXT_ARG : INPUTS;
  }

  for (int i = 1; i < count; ++i) {
    auto current = std::string(args_raw[i]);

    switch (state) {
      case INPUTS: {
        if (!current.starts_with("-")) {
          inputs.emplace_back(current);
        }
        else {
          state = NEXT_ARG;
          --i;
        }
        break;
      }

      case NEXT_ARG: {
        if (current.starts_with("-")) {
          current_arg = strip_prefix(current);
          auto arg = find_arg(current_arg);
          if (!arg) {
            unknown_arg_err(current_arg);
            state = NEXT_ARG;
            break;
          }
          else {
            state = arg->t == typeid(bool) ? ARG_FLAG_INPUT : ARG_INPUT;
          }
          args[current_arg] = nullptr;
        }
        else {
          state = INPUTS;
          --i;
        }
        break;
      }

      case ARG_INPUT: {
        if (current.starts_with("-")) {
          missing_val_err(current_arg);
        }
        else {
          set_arg(current_arg, current);
        }
        state = NEXT_ARG;
        break;
      }

      case ARG_FLAG_INPUT: {
        if (current.starts_with("-")) {
          args[current_arg] = true;
          --i;
        }
        else {
          bool was_consumed = set_flag(current_arg, current);
          if (!was_consumed) --i;
        }
        state = NEXT_ARG;
        break;
      }
    }
  }
  // handle last argument being a flag
  if (state == ARG_FLAG_INPUT) {
    args[current_arg] = true;
  }

  set_defaults();
  validate();
}

std::vector<std::string> CliArgs::get_inputs() const {
  return inputs;
}

std::unordered_map<std::string, std::any> CliArgs::get_args() const {
  return args;
}


std::unordered_map<std::string, std::string> CliArgs::get_errors() const {
  return errors;
}

bool CliArgs::is_valid() const {
  return errors.empty();
}

void CliArgs::summary() const {
  std::cout << "Inputs:" << '\n';
  for (const auto& input : inputs) {
    std::cout << '\t' << input << '\n';
  }

  std::cout << "Args:" << '\n';
  for (const auto& pair : args) {
    std::cout << '\t' << pair.first << '\n';
  }

  std::cout << "Errors:" << '\n';
  for (const auto& err : errors) {
    std::cout << err.first << "-" << err.second << '\n';
  }
}

std::string CliArgs::strip_prefix(const std::string& arg_name) const {
  size_t i = 0;
  while (i < arg_name.length()) {
    if (arg_name[i] != '-') break;
    ++i;
  }
  return arg_name.substr(i, arg_name.length() - i);
}

std::string CliArgs::to_lower(const std::string& in) const {
  std::string builder;
  builder.reserve(in.length());

  for (const char c : in) {
    builder += std::tolower(c);
  }

  return builder;
}

bool CliArgs::in_reqs(const std::string& arg_name) const {
  for (const auto& req : reqs) {
    if (arg_name == req.name) return true;
  }
  return false;
}

std::optional<Arg> CliArgs::find_arg(const std::string& arg_name) const {
  for (auto req : reqs) {
    if (arg_name == req.name) return req;
  }
  return std::nullopt;
}

void CliArgs::set_arg(const std::string& name, const std::string& value) {
  auto arg = find_arg(name);
  if (!arg) return;

  auto t = arg->t;
  if (t.name() == typeid(std::string).name()) {
    args[name] = value;
  }

  // numeric values
  try {
    if (t.name() == typeid(int).name()) {
      args[name] = std::stoi(value);
    }
    if (t.name() == typeid(unsigned int).name()) {
      args[name] = static_cast<unsigned int>(std::stoul(value));
    }
    if (t.name() == typeid(long).name()) {
      args[name] = std::stol(value);
    }
    if (t.name() == typeid(unsigned long).name()) {
      args[name] = std::stoul(value);
    }
    if (t.name() == typeid(long long).name()) {
      args[name] = std::stoll(value);
    }
    if (t.name() == typeid(unsigned long long).name()) {
      args[name] = std::stoull(value);
    }

    if (t.name() == typeid(float).name()) {
      args[name] = std::stof(value);
    }
    if (t.name() == typeid(double).name()) {
      args[name] = std::stod(value);
    }
  }
  catch (std::invalid_argument&) {
    conversion_err(name, value);
    args.erase(name);
  }
}

// return true if the value was consumed
bool CliArgs::set_flag(const std::string& name, const std::string& value) {
  auto value_lc = to_lower(value);
  bool is_true = std::find(truthy.begin(), truthy.end(), value_lc) != truthy.end();
  bool is_false = std::find(falsy.begin(), falsy.end(), value_lc) != falsy.end();

  // decide value
  if (is_false) {
    args[name] = false;
  }
  else {
    args[name] = true;
  }

  // decide if was consumed
  if (is_true || is_false) return true;
  return false;
}

void CliArgs::set_defaults() {
  for (const auto& req : reqs) {
    try {
      // skip no default
      if (req.def.type() == typeid(std::nullptr_t)) continue;

      if (args.contains(req.name)) {
        // skip if value was set
        auto val = args.at(req.name);
        if (val.type() != typeid(std::nullptr_t)) continue;
      }

      // set default
      args[req.name] = req.def;
    }
    catch (std::exception& e) {
      std::cout << e.what() << '\n';
      continue;
    }
  }
}

void CliArgs::validate() {
  for (const auto& req : reqs) {
    if (req.required && !args.contains(req.name)) {
      missing_arg_err(req.name);
    }
  }
}

void CliArgs::unknown_arg_err(const std::string& name) {
  errors[name] = "Unknown argument";
}

void CliArgs::missing_arg_err(const std::string& name) {
  errors[name] = "Missing argument";
}

void CliArgs::missing_val_err(const std::string& name) {
  errors[name] = "Missing value";
}

void CliArgs::invalid_val_err(const std::string& name, const std::string& value) {
  errors[name] = "Invalid value (" + value + ")";
}

void CliArgs::conversion_err(const std::string& name, const std::string& value) {
  errors[name] = "Failed to convert " + value + " to requested type";
}

}
