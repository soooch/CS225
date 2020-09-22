/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"

class Sticker {
  public:
  Image * picture;
  unsigned x, y;

  Sticker();
  Sticker(Image * picture, unsigned x, unsigned y);
  Sticker(Image picture, unsigned x, unsigned y);
  ~Sticker();
};

class StickerSheet {
  unsigned max_;
  Sticker * stickers_;
  public:
  StickerSheet(const Image &picture, unsigned max);
  ~StickerSheet();
  StickerSheet(const StickerSheet &other);
  const StickerSheet &operator=(const StickerSheet &other);
  void changeMaxStickers(unsigned max);
  int addSticker(Image &sticker, unsigned x, unsigned y);
  bool translate(unsigned index, unsigned x, unsigned y);
  void removeSticker(unsigned index);
  Image *getSticker(unsigned index);
  Image render() const;
  private:
  void copy_(const StickerSheet &other);
};