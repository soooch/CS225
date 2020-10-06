#include "StickerSheet.h"

Sticker::Sticker() {
  picture = NULL;
  x = y = 0;
}

Sticker::Sticker(Image * picture, unsigned x, unsigned y) {
  this->picture = picture;
  this->x = x;
  this->y = y;
}

Sticker::Sticker(Image picture, unsigned x, unsigned y) {
  this->picture = new Image(picture);
  this->x = x;
  this->y = y;
}

Sticker::~Sticker() {
  delete picture;
}



StickerSheet::StickerSheet(const Image &picture, unsigned max) {
  max_ = max + 1;
  stickers_ = new Sticker[max_] {Sticker()};
  stickers_[0].picture = new Image(picture);
}

StickerSheet::~StickerSheet() {
  delete[] stickers_;
}

StickerSheet::StickerSheet(const StickerSheet &other) {
  stickers_ = NULL;
  max_ = 0;
  copy_(other);
}

const StickerSheet &StickerSheet::operator=(const StickerSheet &other) {
  copy_(other);
  return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
  Sticker *newStickers = new Sticker[++max] {Sticker()};
  for (unsigned i = 0; i < max_ && i < max; i++) {
    newStickers[i] = stickers_[i];
  }
  // TODO: delete stickers left over when new size is smaller than old
  max_ = max;
  //delete stickers_;
  stickers_ = newStickers;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
  for (unsigned i = 1; i < max_; i++) {
    if (stickers_[i].picture == NULL) {
      stickers_[i] = Sticker(sticker, x, y);
      return --i;
    }
  }
  return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if (stickers_[++index].picture == NULL) return false;
  stickers_[index].x = x;
  stickers_[index].y = y;
  return true;
}

void StickerSheet::removeSticker(unsigned index) {
  //delete stickers_[++index].picture;
  stickers_[++index].picture = NULL;
}

Image *StickerSheet::getSticker(unsigned index) {
  return stickers_[++index].picture;
}

Image StickerSheet::render() const {
  unsigned maxWidth = 0, maxHeight = 0;
  unsigned numStickers = 0;
  Sticker ** validStickers = new Sticker*[max_];
  for (unsigned i = 0; i < max_; i++) {
    if (stickers_[i].picture != NULL) {
      validStickers[numStickers++] = &stickers_[i];
      maxWidth = std::max(maxWidth, stickers_[i].picture->width() + stickers_[i].x);
      maxHeight = std::max(maxHeight, stickers_[i].picture->height() + stickers_[i].y);
    }
  }
  Image output(maxWidth, maxHeight);
  for (unsigned i = 0; i < numStickers; i++) {
    for (unsigned canvasX = validStickers[i]->x, stickerX = 0; stickerX < validStickers[i]->picture->width(); canvasX++, stickerX++) {
      for (unsigned canvasY = validStickers[i]->y, stickerY = 0; stickerY < validStickers[i]->picture->height(); canvasY++, stickerY++) {
        if (validStickers[i]->picture->getPixel(stickerX, stickerY).a != 0.0) {
          output.getPixel(canvasX, canvasY) = validStickers[i]->picture->getPixel(stickerX, stickerY);
        }
      }
    }
  }
  delete[] validStickers;
  return output;
}

void StickerSheet::copy_(const StickerSheet &other) {
  //delete this; TODO: fix this
  max_ = other.max_;
  stickers_ = new Sticker[max_] {Sticker()};
  for (unsigned i = 0; i < max_; i++) {
    if (other.stickers_[i].picture != NULL) {
      stickers_[i] = Sticker(*other.stickers_[i].picture, other.stickers_[i].x ,other.stickers_[i].y);
    }
    else {
      stickers_[i] = Sticker();
    }
  }
}