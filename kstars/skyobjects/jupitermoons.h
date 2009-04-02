/***************************************************************************
                          jupitermoons.h  -  description
                             -------------------
    begin                : Fri Oct 18 2002
    copyright            : (C) 2002 by Jason Harris
    email                : kstars@30doradus.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef JUPITERMOONS_H_
#define JUPITERMOONS_H_

#include <QString>
#include <QVector>

class KSNumbers;
class KSPlanet;
class KSSun;
class TrailObject;
class dms;

/**
  *@class JupiterMoons
  *Implements the four largest moons of Jupiter.
  *See Chapter 43 of "Astronomical Algorithms"by Jean Meeus for details
  *
  *TODO: make the moons SkyObjects, rather than just points.
  *
  *@author Jason Harris
  *@version 1.0
  */
class JupiterMoons {
public:
    /**
      *Constructor.  Assign the name of each moon,
      *and initialize their XYZ positions to zero.
      */
    JupiterMoons();

    /**
      *Destructor.  Delete moon objects.
      */
    ~JupiterMoons();

    /**
      *@short Find the positions of each Moon, relative to Jupiter.
      *We use an XYZ coordinate system, centered on Jupiter, 
      *where the X-axis corresponds to Jupiter's Equator, 
      *the Y-Axis is parallel to Jupiter's Poles, and the 
      *Z-axis points along the line joining the Earth and 
      *Jupiter.  Once the XYZ positions are known, this 
      *function also computes the RA,Dec positions of each 
      *Moon, and sets the inFront bool variable to indicate 
      *whether the Moon is nearer to us than Jupiter or not
      *(this information is used to determine whether the 
      *Moon should be drawn on top of Jupiter, or vice versa).
      *
      *See "Astronomical Algorithms" bu Jean Meeus, Chapter 43.
      *
      *@param num pointer to the KSNumbers object describing 
      *the date/time at which to find the positions.
      *@param jup pointer to the jupiter object
      *@param sunptr pointer to the Sun object
      */
    void findPosition( const KSNumbers *num, const KSPlanet *jup, const KSSun *sunptr );

    /**
      *@return pointer to a moon given the ID number.
      *@param id which moon?  0=Io, 1=Europa, 2=Ganymede, 3=Callisto
      */
    inline TrailObject* moon( int id ) { return Moon[id]; }

    /**
      *@return pointer to a moon, given its name:
      *@param name the name of the moon (Io, Europa, Ganymede, Callisto)
      */
    TrailObject* moonNamed( const QString &name ) const;

    /**
      *@return true if the Moon is nearer to Earth than Jupiter.
      *@param id which moon?  0=Io, 1=Europa, 2=Ganymede, 3=Callisto
      */
    inline bool inFront( int id ) const { return InFront[id]; }

    /**
      *@return the name of a moon.
      *@param id which moon?  0=Io, 1=Europa, 2=Ganymede, 3=Callisto
      */
    QString name( int id ) const;

    /**
      *Convert the RA,Dec coordinates of each moon to Az,Alt
      *@param LSTh pointer to the current local sidereal time
      *@param lat pointer to the geographic latitude
      */
    void EquatorialToHorizontal( const dms *LSTh, const dms *lat );

    /**
      *@return the X-coordinate in the Jupiter-centered coord. system.
      *@param i which moon? 0=Io, 1=Europa, 2=Ganymede, 3=Callisto.  
      */
    double x( int i ) const { return XJ[i]; }

    /**
      *@return the Y-coordinate in the Jupiter-centered coord. system.
      *@param i which moon? 0=Io, 1=Europa, 2=Ganymede, 3=Callisto.  
      */
    double y( int i ) const { return YJ[i]; }

    /**
      *@return the Z-coordinate in the Jupiter-centered coord. system.
      *@param i which moon? 0=Io, 1=Europa, 2=Ganymede, 3=Callisto.  
      */
    double z( int i ) const { return ZJ[i]; }

private:
    QVector<TrailObject*> Moon;
    bool InFront[4];
    //the rectangular position, relative to Jupiter.  X-axis is equator of Jupiter; usints are Jup. Radius
    double XJ[4], YJ[4], ZJ[4];
};

#endif
