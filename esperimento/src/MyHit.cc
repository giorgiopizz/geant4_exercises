#include "MyHit.hh"
#include "G4ProcessType.hh"




G4ThreadLocal G4Allocator<MyHit>* HitAllocator = 0;
MyHit::MyHit()
 : G4VHit(),
   layerNumber(0),
   eDep(0),
   pt(fDecay),
   time(0)
{}
void MyHit::PrintHit(){
    G4cout << "Hit: " << layerNumber << " " << eDep << " " << time <<G4endl;
}

MyHit::~MyHit(){

}
