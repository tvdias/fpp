/*
 *   Playlist Entry Image Class for Falcon Player (FPP)
 *
 *   Copyright (C) 2013-2018 the Falcon Player Developers
 *      Initial development by:
 *      - David Pitts (dpitts)
 *      - Tony Mace (MyKroFt)
 *      - Mathew Mrosko (Materdaddy)
 *      - Chris Pinkham (CaptainMurdoch)
 *      For additional credits and developers, see credits.php.
 *
 *   The Falcon Player (FPP) is free software; you can redistribute it
 *   and/or modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation; either version 2 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLAYLISTENTRYIMAGE_H
#define _PLAYLISTENTRYIMAGE_H

#include <mutex>
#include <thread>
#include <list>
#include <atomic>
#include <condition_variable>
#include <string>

#ifdef USE_X11VSFB
#   include <X11/Xlib.h>
#endif

#include <Magick++.h>

#ifndef USE_X11VSFB
#   include "FrameBuffer.h"
#endif

#include "PlaylistEntryBase.h"

using namespace Magick;

#ifdef USE_X11VSFB
class PlaylistEntryImage : public PlaylistEntryBase {
#else
class PlaylistEntryImage : public PlaylistEntryBase, public FrameBuffer {
#endif
  public:
	PlaylistEntryImage(PlaylistEntryBase *parent = NULL);
	~PlaylistEntryImage();

	int  Init(Json::Value &config);

	int  StartPlaying(void);
	int  Process(void);
	int  Stop(void);

	void Dump(void);

	Json::Value GetConfig(void);

	void PrepLoop(void);

  private:
	void SetFileList(void);

	const std::string GetNextFile(void);
	void              PrepImage(void);

	void Draw(void);

	std::string GetCacheFileName(std::string fileName);
	bool GetImageFromCache(std::string fileName, Image &image);
	void CacheImage(std::string fileName, Image &image);
	void CleanupCache(void);

  	std::string m_imagePath;
	std::string m_lastFileName;

	std::string m_cacheDir;
	int         m_cacheEntries; // # of items
	int         m_cacheSize;    // MB used by cached files
	int         m_freeSpace;    // MB free on filesystem

    std::vector<std::string> m_files;

	int m_width;
	int m_height;

	unsigned char *m_buffer;
	int m_bufferSize;

#ifdef USE_X11VSFB
	std::string    m_device; // normally comes from FrameBuffer.h
	std::string    m_title;
	unsigned char *m_imageData;
	Display       *m_display;
	int            m_screen;
	Window         m_window;
	GC             m_gc;
	Pixmap         m_pixmap;
	XImage        *m_xImage;
#endif

	unsigned int  m_fileSeed;

	volatile bool m_runLoop;
	volatile bool m_imagePrepped;
	volatile bool m_imageDrawn;

	std::thread  *m_prepThread;
	std::mutex    m_prepLock;
	std::mutex    m_bufferLock;

	std::condition_variable m_prepSignal;
};

#endif