#ifndef MyRun_h
#define MyRun_h 1

#include "G4Run.hh"
class MyRun : public G4Run
{
 public:
  MyRun();
  virtual ~MyRun();
  virtual void RecordEvent(const G4Event* evt);
  virtual void Merge(const G4Run*);

 private:
  G4int collID;
  // G4double fEDep;
};
#endif
