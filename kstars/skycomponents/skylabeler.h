/***************************************************************************
						 skylabeler.h  -  K Desktop Planetarium
							 -------------------
	begin				: 2007-07-10
	copyright			: (C) 2007 by James B. Bowlin
	email				: bowlin@mindspring.com
 ***************************************************************************/

/***************************************************************************
 *																		 *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or	 *
 *   (at your option) any later version.								   *
 *																		 *
 ***************************************************************************/

#ifndef SKYLABELER_H
#define SKYLABELER_H

#include <QFontMetricsF>
#include <QList>
#include <QVector>

#include <QFont>

#include "skylabel.h"

class QString;
class QPointF;
class KStars;
class SkyMap;
class QPainter;
struct LabelRun;

typedef QList<LabelRun*>	LabelRow;
typedef QVector<LabelRow*>  ScreenRows;

enum label_t {
			STAR_LABEL,
		ASTEROID_LABEL,
		   COMET_LABEL,
		  PLANET_LABEL,
	JUPITER_MOON_LABEL,
		DEEP_SKY_LABEL,
	CONSTEL_NAME_LABEL,
	   NUM_LABEL_TYPES
};


/*@class SkyLabeler
 * The purpose of this class is to prevent labels from overlapping.  We do this
 * by creating a virtual (lower Y-resolution) screen. Each "pixel" of this
 * screen essentially contains a boolean value telling us whether or not there
 * is an existing label covering at least part of that pixel.  Before you draw
 * a label, call mark( QPointF, QString ) of that label.  We will check to see
 * if it would overlap any existing label.  If there is overlap we return false.
 * If there is no overlap then we mark all the pixels that cover the new label
 * and return true.
 *
 * Since we need to check for overlap for every label every time it is
 * potentially drawn on the screen, efficiency is essential.  So instead of
 * having a 2-dimensional array of boolean values we use Run Length Encoding
 * and store the virtual array in a QVector of QLists.  Each element of the
 * vector, a LabelRow, corresponds to a horizontal strip of pixels on the actual
 * screen.  How many vertical pixels are in each strip is controlled by
 * m_yDensity.  The higher the density, the fewer vertical pixels per strip and
 * hence a larger number of strips are needed to cover the screen.  As
 * m_yDensity increases so does the density of the strips.
 *
 * The information in the X-dimension is completed run length encoded. A
 * consecutive run of pixels in one strip that are covered by one or more labels
 * is stored in a LabelRun object that merely stores the start pixel and the end
 * pixel.  A LabelRow is a list of LabelRun's stored in ascending order.  This
 * saves a lot of space over an explicit array and it also makes checking for
 * overlaps faster and even makes inserting new overlaps faster on average.
 *
 * Synopsis:
 *
 *   1) Create a new SkyLabeler
 *
 *   2) every time you want to draw a new screen, reset the labeler.
 *
 *   3) Either:
 *
 *	 A) Call drawLabel() or drawOffsetLabel(), or
 *
 *	 B) Call addLabel() or addOffsetLabel()
 *
 *  4) Call draw() if addLabel() or addOffsetLabel() were used.
 *
 *
 *
 * SkyLabeler works totally on a first come, first served basis which is almost
 * the direct opposite of a z-buffer where the objects drawn last are most
 * visible.  This is why the addLabel() and draw() routines were created.
 * They allow us to time-shift the drawing of labels and thus gives us control
 * over their priority.  The drawLabel() routines are still available but are
 * not being used.  The addLabel() routines adds a label to a specfic buffer.
 * Each type of label has its own buffer which lets us control the font and
 * color as well as the priority.  The priority is now manually set in the
 * draw() routine by adjusting the order in which the various buffers get
 * drawn.
 *
 * Finally, even though this code was written to be very efficient, we might
 * want to take some care in how many labels we throw at it.  Sending it
 * a large number of overlapping labels can be wasteful. Also, if one type
 * of object floods it with labels early on then there may not be any room
 * left for other types of labels.  Therefore for some types of objects (stars)
 * we may want to have a zoom dependent label threshold magnitude just like
 * we have for drawing the stars themselves.  This would throw few labels
 * at the labeler when we are zoomed at and they would mostly overlap anyway
 * and it would give us more labels when the user is zoomed in and there
 * is more room for them.  The "b" key currently causes the labeler statistics
 * to be printed.  This may be useful in figuring out the best settings for
 * the magnitude limits.  It may even be possible to have KStars do some of
 * this throttling automatically but I haven't really thought about that
 * problem yet.
 *
 * -- James B. Bowlin  2007-08-02
 */


class SkyLabeler
{
	protected:
		SkyLabeler();
		SkyLabeler( SkyLabeler& skyLabler );

	public:

		//----- Static Methods ----------------------------------------------//

		static SkyLabeler* Instance();

		/* @short adjusts the font in psky to be smaller if we are zoomed out.
		 * This static function allows us to prevent code duplication since it
		 * can be used without a SkyLabeler instance.  This is used in SkyObject
		 * and StarObject in addition to be used in this class.
		 */
		static void SetZoomFont( QPainter& psky );

		/* @short returns the zoom dependent label offset.  This is used in this
		 * class and in SkyObject.  It is important that the offsets be the same
		 * so highlighted labels are always drawn exactly on top of the normally
		 * drawn labels.
		 */
		static double ZoomOffset( double scale );

		/* @short static version of addOffsetLabel() below.
		 */
		inline static void AddOffsetLabel( const QPointF& p, const QString& text, label_t type )
		{
			pinstance->addOffsetLabel( p, text, type );
		}

		/* @short static version of addLabel() below.
		 */
		inline static void AddLabel( const QPointF& p, const QString& text, label_t type )
		{
			pinstance->addLabel( p, text, type );
		}


		//--------------------------------------------------------------------//
		~SkyLabeler();

		/* @short clears the virtual screen (if needed) and resizes the virtual
		 * screen (if needed) to match skyMap.  A font must be specified which
		 * is taken to be the average or normal font that will be used.  The
		 * size of the horizontal strips will be (slightly) optimized for this
		 * font.  We also adjust the font size in psky to smaller fonts if the
		 * screen is zoomed out.  You can mimic this setting with the static
		 * method SkyLabeler::setZoomFont( psky ).
		 */
		void reset( SkyMap* skyMap, QPainter& psky, double scale );


		//----- Font Setting -----//

		/* @short tells the labeler the font you will be using so it can figure
		 * out the height and width of the labels.  Also sets this font in the
		 * psky since this is almost always what is wanted.
		 */
		void setFont( QPainter& psky, const QFont& font );

		/* @short decreases the size of the font in psky and in the SkyLabeler
		 * by the delta points.  Negative deltas will increase the font size.
		 */
		void shrinkFont( QPainter& psky, int delta );

		/* @short sets the font in SkyLabeler and in psky to the font psky
		 * had originally when reset() was called.  Used by ConstellationNames.
		 */
		void useStdFont(QPainter& psky);

		/* @short sets the font in SkyLabeler and in psky back to the zoom
		 * dependent value that was set in reset().  Also used in
		 * ConstellationLines.
		 */
		void resetFont(QPainter& psky);

		/* @short returns the fontMetricsF we have already created.
		 */
		QFontMetricsF& fontMetrics() { return m_fontMetrics; }


		//----- Drawing/Adding Labels -----//

		/* @short sets four margins for help in keeping labels entirely on the
		 * screen.
		 */
		void getMargins( QPainter& psky, const QString& text, float *left,
				         float *right, float *top, float *bot );

		/* @short a convenience routine that draws the label specified
		 * in the SkyLabel.
		 */
		void drawLabel( QPainter& psky, const SkyLabel& skyLabel ) {
			 drawLabel( psky, skyLabel.o , skyLabel.text );
		}

		/* @short attempts to draw the label at the given position but will
		 * not draw it if it would overlap an existing label.
		 */
		void drawLabel( QPainter& psky, const QPointF& p, const QString& text );

		/* @short like drawLabel() but offsets the location by a zoom dependent
		 * offset.
		 */
		void drawOffsetLabel( QPainter& psky, const QPointF& p, const QString& text );


		/* @short Tries to draw the text at the position and angle specfied. If
		 * the label would overlap an existing label it is not drawn and we
		 * return false, otherwise the label is drawn, its position is marked
		 * and we return true.
		 */
		bool drawLabel( QPainter& psky, QPointF& o, const QString& text, double angle );

		/* @short queues the label in the "type" buffer for later drawing.
		 */
		void addLabel( const QPointF& p, const QString& text, label_t type );

		/* @short queues the label in the "type" buffer for later drawing.  A
		 * zoom dependent offset is automatically added to the coordinates.
		 */
		void addOffsetLabel( const QPointF& p, const QString& text, label_t type );

		/*@short draws the labels stored in all the buffers.  You can change the
		 * priority by editing the .cpp file and changing the order in which
		 * buffers are drawn.  You can also change the fonts and colors there
		 * too.
		 */
		void draw( KStars* kstars, QPainter& psky );

		/* @short a convenience routine that draws all the labels from a single
		 * buffer.  Currently this is only called from within draw() above.
		 */
		void drawLabels( QPainter& psky, label_t type );


		//----- Marking Regions -----//

		/* @short tells the labeler the location and text of a label you want
		 * to draw.  Returns true if there is room for the label and returns
		 * false otherwise.  If it returns true, the location of the label is
		 * marked on the virtual screen so future labels won't overlap it.
		 *
		 * It is usually easier to use drawLabel() or drawLabelOffest() instead
		 * which both call mark() internally.
		 */
		bool markText( const QPointF& p, const QString& text);

		/* @short Works just like markText() above but for an arbitrary
		 * rectangular region bounded by top, bot, left, and right.
		 */
		bool markRegion( qreal left, qreal right, qreal top, qreal bot );

		bool markRect( qreal x, qreal y, qreal width, qreal height, QPainter& psky );


		//----- Diagnostics and Information -----//

		/* @short diagnostic. the *percentage* of pixels that have been filled.
		 * Expect return values between 0.0 and 100.0.  A fillRatio above 20
		 * is pretty busy and crowded.  I think a fillRatio of about 10 looks
		 * good.  The fillRatio will be lowered of the screen is zoomed out
		 * so are big blank spaces around the celestial sphere.
		 */
		float fillRatio();

		/* @short diagnostic, the number of times mark() returned true divided by
		 * the total number of times mark was called multiplied by 100.  Expect
		 * return values between 0.0 an 100.  A hit ratio of 100 means no labels
		 * would have overlapped.  A ratio of zero means no labels got drawn
		 * (which should never happen).  A hitRatio around 50 might be a good
		 * target to shoot for.  Expect it to be lower when fully zoomed out and
		 * higher when zoomed in.
		 */
		float hitRatio();

		/* @short diagnostic, prints some brief statistics to the console.
		 * Currently this is connected to the "b" key in SkyMapEvents.
		 */
		void printInfo();

		/* @short these two routines are tied to the "F" and "G" keys in
		 * skymapactions.cpp to allow users/devs to fiddle with the label
		 * density.
		 */
		void incDensity();
		void decDensity();

		int hits()  { return m_hits; };
		int marks() { return m_marks; }

	private:
		ScreenRows screenRows;

		int m_maxX;
		int m_maxY;
		int m_size;
		int m_minDeltaX;

		int m_marks;
		int m_hits;
		int m_misses;
		int m_elements;
		int m_errors;

		qreal  m_yDensity;
		qreal  m_yScale;
		double m_offset;

		QFont		 m_stdFont, m_skyFont;
		QFontMetricsF m_fontMetrics;

		QVector<LabelList>   labelList;

		static SkyLabeler* pinstance;
};

#endif