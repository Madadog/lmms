/*
 * sample_track.h - class sampleTrack, a track which provides arrangement of
 *                  samples
 *
 * Copyright (c) 2005-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
 * 
 * This file is part of Linux MultiMedia Studio - http://lmms.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */


#ifndef _SAMPLE_TRACK_H
#define _SAMPLE_TRACK_H

#include <QtGui/QDialog>

#include "audio_port.h"
#include "track.h"

class QLabel;
class effectLabel;
class sampleBuffer;
class knob;

//class sampleTCOSettingsDialog;


class sampleTCO : public trackContentObject
{
	Q_OBJECT
public:
	sampleTCO( track * _track );
	virtual ~sampleTCO();

	virtual void changeLength( const midiTime & _length );
	const QString & sampleFile( void ) const;

	virtual void saveSettings( QDomDocument & _doc,
							QDomElement & _parent );
	virtual void loadSettings( const QDomElement & _this );
	inline virtual QString nodeName( void ) const
	{
		return( "sampletco" );
	}

	sampleBuffer * getSampleBuffer( void )
	{
		return( m_sampleBuffer );
	}


public slots:
	void setSampleFile( const QString & _sf );
	void updateLength( bpm_t = 0 );

protected:
	virtual void dragEnterEvent( QDragEnterEvent * _dee );
	virtual void dropEvent( QDropEvent * _de );
	virtual void mouseDoubleClickEvent( QMouseEvent * );
	virtual void paintEvent( QPaintEvent * );

	midiTime getSampleLength( void ) const;


private:
	sampleBuffer * m_sampleBuffer;


	//friend class sampleTCOSettingsDialog;

} ;



/*
class sampleTCOSettingsDialog : public QDialog
{
	Q_OBJECT
public:
	sampleTCOSettingsDialog( sampleTCO * _stco );
	~sampleTCOSettingsDialog();


protected slots:
	void openSampleFile( void );
	void setSampleFile( const QString & _f );


private:
	sampleTCO * m_sampleTCO;
	QLabel * m_fileLbl;

} ;
*/



class sampleTrack : public track
{
	Q_OBJECT
public:
	sampleTrack( trackContainer * _tc );
	virtual ~sampleTrack();

	virtual bool play( const midiTime & _start, const fpp_t _frames,
						const f_cnt_t _frame_base,
							Sint16 _tco_num = -1 );
	virtual trackView * createView( trackContainerView * _tcv );
	virtual trackContentObject * createTCO( const midiTime & _pos );


	virtual void saveTrackSpecificSettings( QDomDocument & _doc,
							QDomElement & _parent );
	virtual void loadTrackSpecificSettings( const QDomElement & _this );

	inline audioPort * getAudioPort( void )
	{
		return( &m_audioPort );
	}

	virtual QString nodeName( void ) const
	{
		return( "sampletrack" );
	}


private:
	audioPort m_audioPort;
	floatModel m_volumeModel;


	friend class sampleTrackView;

} ;



class sampleTrackView : public track
{
public:
	sampleTrackView( sampleTrack * _track, trackContainerView * _tcv );
	virtual ~sampleTrackView();


private:
	effectLabel * m_trackLabel;

	knob * m_volumeKnob;

} ;



#endif
