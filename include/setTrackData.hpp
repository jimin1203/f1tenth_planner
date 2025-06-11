#pragma once
#include "makeCSV.hpp"

void computeOffsetXY(const string& alpha,
                    int sign,
                    const string& out_x_name, 
                    const string& out_y_name);
void setTrackData(Document& csv);
