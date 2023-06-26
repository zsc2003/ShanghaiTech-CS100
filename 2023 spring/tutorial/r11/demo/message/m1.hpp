#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <set>
#include <string>
#include <utility>
#include <iostream>

class Folder;

class Message {
  std::string m_contents;
  std::set<Folder *> m_folders;

public:
  explicit Message(std::string contents = "") : m_contents{std::move(contents)} {}
  void AddFolder(Folder &folder) {
    m_folders.insert(&folder);
    // std::cout << "AddFolder: " << folder.m_message << std::endl;
  }
};

class Folder {
  std::set<Message *> m_messages;

};

#endif // MESSAGE_HPP