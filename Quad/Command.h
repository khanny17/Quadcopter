#ifndef Command_h
#define Command_h

#include "Arduino.h"

enum Command { RUN, STOP, CONFIGURE, RESET };

class CommandHandler
{
  public:
    boolean readNewCommand();
    Command getCurrentCommand();
    void setCurrentCommand(Command c);
  private:
    Command currentCommand;
};

#endif
