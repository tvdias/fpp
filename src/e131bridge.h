/*
 *   E131 bridge for Falcon Pi Player (FPP)
 *
 *   Copyright (C) 2013 the Falcon Pi Player Developers
 *      Initial development by:
 *      - David Pitts (dpitts)
 *      - Tony Mace (MyKroFt)
 *      - Mathew Mrosko (Materdaddy)
 *      - Chris Pinkham (CaptainMurdoch)
 *      For additional credits and developers, see credits.php.
 *
 *   The Falcon Pi Player (FPP) is free software; you can redistribute it
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

#ifndef _E131_BRIDGE_H
#define _E131_BRIDGE_H

#define  BRIDGE_INVALID_UNIVERSE_INDEX								0xFF

#define MAX_TIME_BETWEEN_RECEIVE                              5000
#define MIN_DELAY_BETWEEN_SENDING_PIXELNET            47000
      
void Bridge_Initialize();
void Bridge_InitializeSockets();
void Bridge_Process();
void Bridge_StoreData(int universe);
int Bridge_GetIndexFromUniverseNumber(int universe);

#endif
