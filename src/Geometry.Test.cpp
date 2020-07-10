/* Geometry.Test.cpp
 *
 */

#if defined DEBUG

#include <cstdio>
#include "Geometry.h"
#include "Logger.h"

int Geometry::Test() {
	Geometry* g = new Geometry();
	g->SetPosition({100.0, 100.0});
	g->SetSize({36.0, 48.0});
	g->SetCenter({-12.0, -24.0});
	char msg[128] = {};
	double xl = g->GetXLeft();
	double xr = g->GetXRight();
	double yt = g->GetYTop();
	double yb = g->GetYBottom();
	Logger("Geometry::Test:  position set to (100,100), size set to (36,48), center offset set to (-12,-24)");
	sprintf(msg, "Geometry::Test:  XLeft=%.1f, XRight=%.1f, YTop=%.1f, YBottom=%.1f", xl, xr, yt, yb);
	Logger(msg);
	coords pair = g->GetTopLeft();
	sprintf(msg, "Geometry::Test:      Top Left corner X=%5.1f, Y=%5.1f", pair.x, pair.y);
	Logger(msg);
	pair = g->GetTopRight();
	sprintf(msg, "Geometry::Test:     Top Right corner X=%5.1f, Y=%5.1f", pair.x, pair.y);
	Logger(msg);
	pair = g->GetBottomLeft();
	sprintf(msg, "Geometry::Test:   Bottom Left corner X=%5.1f, Y=%5.1f", pair.x, pair.y);
	Logger(msg);
	pair = g->GetBottomRight();
	sprintf(msg, "Geometry::Test:  Bottom Right corner X=%5.1f, Y=%5.1f", pair.x, pair.y);
	Logger(msg);
	return 0;
}

#endif //DEBUG
