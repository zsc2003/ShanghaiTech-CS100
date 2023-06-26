#include <memory>

#include "GameManager.hpp"
#include "GameWorld.hpp"

#include  <direct.h>  
#include  <stdio.h> 
 

int main(int argc, char** argv) {
  std::shared_ptr<WorldBase> world = std::make_shared<GameWorld>();


  char   buffer[MAX_PATH];   
  getcwd(buffer, MAX_PATH);
  std::cerr<<"---------------------------------\n";
  std::cerr << "pwd: " << buffer << std::endl;
  std::cerr<<"---------------------------------\n";

  GameManager::Instance().Play(argc, argv, world);
}