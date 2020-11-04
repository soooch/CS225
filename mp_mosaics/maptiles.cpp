/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include <chrono>
#include <unordered_map>
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

namespace std
{
    template<> struct hash<Point<3>>
    {
        std::size_t operator()(Point<3> const& p) const noexcept
        {
            std::size_t h1 = std::hash<double>{}(p[0]);
            std::size_t h2 = std::hash<double>{}(p[1]);
            std::size_t h3 = std::hash<double>{}(p[0]);
            return h1 ^ (h2 << 1) ^ (h3 >> 1); // or use boost::hash_combine
        }
    };
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    auto start = std::chrono::high_resolution_clock::now();
    auto canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    
    vector<Point<3>> tileColors(theTiles.size());
    transform(theTiles.begin(), theTiles.end(), tileColors.begin(), 
                [](TileImage tile){return convertToXYZ(tile.getAverageColor());});
    KDTree<3> tileKD(tileColors);
    std::unordered_map<Point<3>, int> tileMap;
    for (unsigned long i = 0; i < tileColors.size(); i++) {
        tileMap[tileColors[i]] = i;
    }


    for (int i = 0; i < theSource.getRows(); i++) {
        for (int j = 0; j < theSource.getColumns(); j++) {
            canvas->setTile(i, j, 
                &theTiles[tileMap[
                    tileKD.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(i, j)))
                ]]
            );
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << std::endl << "mosaic creation: " << duration.count() << std::endl;
    start = stop;

    return canvas;
}

