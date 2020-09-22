#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
  max_ = max;
  stickers_ = new Image*[max_];
  basePicture_ = picture;
}

StickerSheet::~StickerSheet() {
  for (unsigned i = 0; i < max_; i++) {
    delete stickers_[i];
  }
  delete[] stickers_;
}

StickerSheet::StickerSheet(const StickerSheet &other) {
  copy_(other);
}

const StickerSheet &StickerSheet::operator=(const StickerSheet &other) {
  copy_(other);
  return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
  StickerSheet newSheet(basePicture_, max);
  for (unsigned i = 0; i < max_; i++) {
    newSheet.stickers_[i] = new Image(*stickers_[i]);
  }
  delete this;
  *this = newSheet;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
  for (unsigned i = 0; i < max_; i++) {
    if (stickers_[i] != NULL) {
      stickers_[i] = new Image(sticker);
      translate(i, x, y);
      return i;
    }
  }
  return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if (stickers_[index] == NULL) return false;
  Image *translated = new Image(stickers_[index]->width() + x, stickers_[index]->height() + y);
  for (unsigned xTrans = x, xOrig = 0; xTrans < translated->width(); xTrans++, xOrig++) {
    for (unsigned yTrans = y, yOrig = 0; yTrans < translated->height(); yTrans++, yOrig++) {
      translated->getPixel(xTrans, yTrans) = stickers_[index]->getPixel(xOrig, yOrig);
    }
  }
  delete stickers_[index];
  stickers_[index] = translated;
  return true;
}

void StickerSheet::removeSticker(unsigned index) {
  delete stickers_[index];
  stickers_[index] = NULL;
}

Image *StickerSheet::getSticker(unsigned index) {
  return stickers_[index];
}

Image StickerSheet::render() const {
  unsigned maxWidth = 0, maxHeight = 0;
  unsigned numStickers = 0;
  Image ** validStickers = new Image*[max_];  // TODO: delete this allocation
  for (unsigned i = 0; i < max_; i++) {
    if (stickers_[i] != NULL) {
      validStickers[numStickers++] = stickers_[i];
      maxWidth = std::max(maxWidth, stickers_[i]->width());
      maxHeight = std::max(maxHeight, stickers_[i]->height());
    }
  }
  Image output(maxWidth, maxHeight);
  for (unsigned i = 0; i < numStickers; i++) {
    for (unsigned x = 0; x < validStickers[i]->width(); x++) {
      for (unsigned y = 0; y < validStickers[i]->height(); y++) {
        if (validStickers[i]->getPixel(x, y).a != 0.0) {
          output.getPixel(x, y) = validStickers[i]->getPixel(x, y);
        }
      }
    }
  }
  delete[] validStickers;
  return output;
}

void StickerSheet::copy_(const StickerSheet &other) {
  delete this;
  StickerSheet(other.basePicture_, other.max_);
  for (unsigned i = 0; i < max_; i++) {
    stickers_[i] = new Image(*other.stickers_[i]);
  }
}