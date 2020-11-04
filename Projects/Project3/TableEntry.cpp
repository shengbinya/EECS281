// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D

// EECS 281 Project 3 SillyQL TableEntry class
// Copyright 2020, Regents of the University of Michigan

#include "TableEntry.h"

#include <functional>
#include <cassert>
#include <iostream>
#include <utility>
#include <exception>

using std::string;
using std::greater;
using std::less;
using std::equal_to;
using std::not_equal_to;
using std::move;
using std::ostream;
using std::terminate;

// elt constructors
// const char* method, because otherwise it matches the bool one
TableEntry::TableEntry(const char* val) : tag{EntryType::String}, data_string{val} {}
TableEntry::TableEntry(const string& val) : tag{EntryType::String}, data_string{val} {}
TableEntry::TableEntry(string&& val) : tag{EntryType::String}, data_string{move(val)} {}
TableEntry::TableEntry(double val) : tag{EntryType::Double}, data_double{val} {}
TableEntry::TableEntry(int val) : tag{EntryType::Int}, data_int{val} {}
TableEntry::TableEntry(bool val) : tag{EntryType::Bool}, data_bool{val} {}

// copy/move ctors
TableEntry::TableEntry(const TableEntry& other) : tag{other.tag} {
  construct_from(other);
}
TableEntry::TableEntry(TableEntry&& other) noexcept : tag{other.tag} {
  construct_from(move(other));
}

// dtor
TableEntry::~TableEntry() noexcept {
  if (tag == EntryType::String)
    data_string.~string();
}

// comparisons
bool TableEntry::operator<(const TableEntry& other) const noexcept {
  return compare<less>(other);
}
bool TableEntry::operator>(const TableEntry& other) const noexcept {
  return compare<greater>(other);
}
bool TableEntry::operator==(const TableEntry& other) const noexcept {
  return compare<equal_to>(other);
}
bool TableEntry::operator!=(const TableEntry& other) const noexcept {
  return compare<not_equal_to>(other);
}

// specializations on the as<> template for conversion
template <> const string& TableEntry::as<string>() const noexcept {
  assert(tag == EntryType::String &&
         "tried to use TableEntry as a string when it didn't contain a string");
  return data_string;
}
template <> double TableEntry::as<double>() const noexcept {
  assert(tag == EntryType::Double &&
         "tried to use TableEntry as a double when it didn't contain a double");
  return data_double;
}
template <> int TableEntry::as<int>() const noexcept {
  assert(tag == EntryType::Int &&
         "tried to use TableEntry as an int when it didn't contain an int");
  return data_int;
}
template <> bool TableEntry::as<bool>() const noexcept {
  assert(tag == EntryType::Bool &&
         "tried to use TableEntry as a bool when it didn't contain a bool");
  return data_bool;
}


namespace std {
// overload to std::hash
size_t hash<TableEntry>::operator()(const TableEntry& tt) const noexcept {
  switch (tt.tag) {
  case EntryType::String:
    return hash<string>{}(tt.data_string);
  case EntryType::Double:
    return hash<double>{}(tt.data_double);
  case EntryType::Int:
    return hash<int>{}(tt.data_int);
  case EntryType::Bool:
    return hash<bool>{}(tt.data_bool);
  }
  terminate();
}
}

ostream& operator<<(ostream& os, const TableEntry& tt) {
  switch (tt.tag) {
  case EntryType::String:
    return os << tt.data_string;
  case EntryType::Double:
    return os << tt.data_double;
  case EntryType::Int:
    return os << tt.data_int;
  case EntryType::Bool:
    return os << tt.data_bool;
  }
  terminate();
}
