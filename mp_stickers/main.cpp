#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);

  /**
   * For testing deep copy of base image
   * The {...} are used for a block statement
   * and are intentional
   */

  sheet.addSticker(i, 800, 200);
  sheet.addSticker(i, 50, 500);

  sheet.changeMaxStickers(7);
  sheet.removeSticker(1);
  sheet.changeMaxStickers(4);

  const Image &renderXBound = sheet.render();



  sheet.removeSticker(0);


  sheet.addSticker(i, 20, 500);
  sheet.changeMaxStickers(1);

  const Image &renderYBound = sheet.render();



  sheet.removeSticker(0);
  sheet.changeMaxStickers(2);


  sheet.addSticker(i, 800, 200);
  sheet.addSticker(i, 20, 500);

  const Image &renderXYBound = sheet.render();


  sheet.changeMaxStickers(0);

  return 0;
}
