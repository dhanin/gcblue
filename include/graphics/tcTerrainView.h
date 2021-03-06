/**  
**  @file tcTerrainView.h
*/
/*
**  Copyright (c) 2014, GCBLUE PROJECT
**  All rights reserved.
**
**  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
**
**  1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
**
**  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the 
**     documentation and/or other materials provided with the distribution.
**
**  3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from 
**     this software without specific prior written permission.
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT 
**  NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
**  COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
**  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
**  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
**  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef _TERRAINVIEW_H_
#define _TERRAINVIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 
#ifdef WIN32
#include "wx/msw/private.h" //for MS Windows specific definitions
#endif
#include "simmath.h"
#include "tcMapData.h"
#include "tc3DWindow2.h"
#include <boost/shared_ptr.hpp>

class tcTexture2D;
class tcOptions;


struct tsTerrainViewParameters 
{
	int mnSurfaceWidth;
	int mnSurfaceHeight;
	tcGeoRect mrectGeo;
	tcRect mrectDisplay;
};

/**
* Modified to use OSG. This constructs a textured image using map data and
* uses it to draw a textured quad showing a color elevation map for the view
* area.
*/
class tcTerrainView : public tc3DWindow2
{
public:
	tcGeoRect mrectCurrentView;

	void Draw();
	void GetViewParameters(tsTerrainViewParameters& vp);
	void AttachMapData(tcMapData *apMapData) {mpMapData = apMapData;}
	int LoadHighResSurface();
	int LoadLowResSurface();
	void Maximize();
	void Minimize();
	int RefreshSurfaces(); ///< reloads terrain data to map view
	int CreateSurfaces();
	void SetActive(bool abActive);
	void SetDisplayRegion(tcRect& r);
	void SetView(tcGeoRect r); 

	tcTerrainView(wxWindow *parent, 
		const wxPoint& pos, const wxSize& size, 
		bool isHighRes,
		const wxString& name = "TerrainView");
	~tcTerrainView();
private:
	const bool highRes;
	tcMapData* mpMapData;
	tcOptions* mpOptions;   
	tcGeoRect mrectMap;  ///< current borders of loaded map   
	tcRect displayRegion; ///< normalized coords [0, 1] to display on textured quad
	tcRect displayRegionWrapped; ///< wrapped section for wrapped view
	float wrapWidth; ///< 0-1.0 fraction of view for wrapped portion of map
	bool isWrapped; ///< true if wrapped
    boost::shared_ptr<tcTexture2D> mapImage;
	bool redraw; ///< true to redraw
};



#endif 
