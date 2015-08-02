#include "Command.h"

/**
 *   Gets a new command over serial. returns true if a new command was received,
 *     false if no new command was available
 */
boolean CommandHandler::readNewCommand(){
  if(Serial.available()){
    switch((char)Serial.read()){
      case 'S': this->setCurrentCommand(STOP);
                break;
      case 'G': this->setCurrentCommand(RUN);
                break;
      case 'C': this->setCurrentCommand(CONFIGURE);
                break;
      case 'R': this->setCurrentCommand(RESET);
                break; 
                
      default : return false;     
    }
    
    return this->getCurrentCommand();
  }
  
  return false;
}

void CommandHandler::setCurrentCommand(Command c){
  this->currentCommand = c;
}

Command CommandHandler::getCurrentCommand(){
  return this->currentCommand;
}
