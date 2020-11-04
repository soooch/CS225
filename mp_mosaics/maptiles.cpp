/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    auto canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    
    vector<Point<3>> tileColors(theTiles.size());
    transform(theTiles.begin(), theTiles.end(), tileColors.begin(), 
                [](TileImage tile){return convertToXYZ(tile.getAverageColor());});
    KDTree<3> tileKD(tileColors);

    for (int i = 0; i < theSource.getRows(); i++) {
        for (int j = 0; j < theSource.getColumns(); j++) {
            canvas->setTile(i, j, 
                &theTiles[
                    find(tileColors.begin(), tileColors.end(), 
                        tileKD.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(i, j)))
                    ) - tileColors.begin()
                ]
            );
        }
    }

    return canvas;
}

