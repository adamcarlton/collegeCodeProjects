#include <source.h>
#include <stdio.h>

Image*
Source::GetOutput(){
    return &(this->img);
}

void
Source::Update(){
  char msg[128];
  sprintf(msg, "%s: about to execute", SourceName());
  Logger::LogEvent(msg);
  Execute();
  sprintf(msg, "%s: done executing", SourceName());
  Logger::LogEvent(msg);
}
