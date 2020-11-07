/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include <unordered_map>
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

namespace std
{
    template<int Dim> struct hash<Point<Dim>>
    {
        std::size_t operator()(Point<Dim> const& p) const noexcept
        {
            std::size_t h = std::hash<double>{}(p[0]);
            for (int i = 1; i < Dim; i++) {
                h ^= std::hash<double>{}(p[i]);
            }
            return h; // or use boost::hash_combine
        }
    };
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
    std::unordered_map<Point<3>, TileImage*> tileMap;
    for (unsigned long i = 0; i < tileColors.size(); i++) {
        tileMap[tileColors[i]] = &theTiles[i];
    }


    for (int i = 0; i < theSource.getRows(); i++) {
        for (int j = 0; j < theSource.getColumns(); j++) {
            canvas->setTile(i, j, 
                tileMap[
                    tileKD.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(i, j)))
                ]
            );
        }
    }
    return canvas;
}

