#ifndef  __PLOTSTYLE_H
#define __PLOTSTYLE_H

#include "TStyle.h"
#include "TLatex.h"

void SetPlotStyle();

TStyle* PlotStyle();

void CMSLABEL();

void LABEL(std::string lab);

#endif
