// $Id: HadCaloHit.hh 100 2010-01-26 16:12:59Z adotti $
#ifndef MyHit_h
#define MyHit_h 1

/**
 * @file
 * @brief Define user class HadCaloHit.
 *
 * We define "our" hit content : the layer number and the energy deposited in the layer
 */

#include "G4VHit.hh"
#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4ProcessType.hh"
#include "G4Types.hh"
#include "tls.hh"
#include "globals.hh"
/*!
 * \brief This class stores information of a hit.
 *
 * It contains
 *  - Hadronic calorimeter layer number
 *  - Deposited energy in layer
 */



class MyHit : public G4VHit {
public:
  /// Constructor
  MyHit();
  /// Destructor
  ~MyHit();
  //! Print on screen a Hit
  // void Print();

public:
  //! \name The new and delete operators are overloaded for performances reasons:
  /*! -- Tricky business here... :-(, but provided for you below */
  //@{
  inline void *operator    new(size_t);
  inline void  operator delete(void *aHit);
  //@}
private:
  G4int   layerNumber;
  G4double      eDep;
  G4int pt;
  G4double      time;
  G4int direction;

public:
  //! \name  simple set and get methods
  //@{
  void          SetLayer(const G4int e){ layerNumber = e; }
  void          SetEdep(const G4double e){ eDep = e; }
  void          SetProcess(const G4int e){ pt = e; }
  void          SetTime(const G4double e){ time = e; }
  void          SetDirection(const G4int e){ direction = e; }

  G4int         GetLayer() const { return layerNumber; }
  G4double      GetEdep()        const { return eDep;}
  G4int      GetProcess()        const { return pt;}
  G4double      GetTime()        const { return time; }
  G4int         GetDirection()  const {return direction;}
  //@}

  void PrintHit();




};

// Define the "hit collection" using the template class G4THitsCollection:
typedef G4THitsCollection<MyHit> HitCollection;


// -- new and delete overloaded operators:
extern G4ThreadLocal G4Allocator<MyHit>* HitAllocator;

inline void* MyHit::operator new(size_t)
{
  if (!HitAllocator) HitAllocator = new G4Allocator<MyHit>;
  return (void* ) HitAllocator->MallocSingle();

  // void *aHit;
  // aHit = (void *) HitAllocator->MallocSingle();
  // return aHit;
}
inline void MyHit::operator delete(void *hit)
{
  HitAllocator->FreeSingle((MyHit*) hit);
}

#endif
