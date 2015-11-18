// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <wctype.h>

#include "wctype_impl.h"

int iswpunct(wint_t wc) {
  static const uint32_t extents[] = {
      0x0001080e, 0x0001d006, 0x0002d805, 0x0003d803, 0x00050009, 0x00055806,
      0x0005a000, 0x0005b002, 0x0005d800, 0x0005f800, 0x0006b800, 0x0007b800,
      0x00161003, 0x0016900d, 0x00172806, 0x00176800, 0x00177855, 0x001a3029,
      0x001ba800, 0x001bf000, 0x001c2001, 0x001c3800, 0x001fb000, 0x00241007,
      0x002ad005, 0x002c4801, 0x002c6802, 0x002c8836, 0x002f9801, 0x0030001c,
      0x0030f001, 0x00325814, 0x00335003, 0x00338000, 0x0036a000, 0x0036b00e,
      0x00373806, 0x0037e801, 0x0038000d, 0x00387800, 0x00388800, 0x0039801a,
      0x003d300a, 0x003f5808, 0x003fb003, 0x0040b003, 0x0040d808, 0x00412802,
      0x00414804, 0x0041800e, 0x0042c802, 0x0042f000, 0x0047201f, 0x0049d002,
      0x0049f011, 0x004a8806, 0x004b1003, 0x004b8000, 0x004c0802, 0x004de000,
      0x004df006, 0x004e3801, 0x004e5802, 0x004eb800, 0x004f1001, 0x004f9001,
      0x004fd001, 0x00500802, 0x0051e000, 0x0051f004, 0x00523801, 0x00525802,
      0x00528800, 0x00538001, 0x0053a800, 0x00540802, 0x0055e000, 0x0055f007,
      0x00563802, 0x00565802, 0x00571001, 0x00578001, 0x00580802, 0x0059e000,
      0x0059f006, 0x005a3801, 0x005a5802, 0x005ab001, 0x005b1001, 0x005b8000,
      0x005c1000, 0x005df004, 0x005e3002, 0x005e5003, 0x005eb800, 0x005f9807,
      0x00600003, 0x0061f006, 0x00623002, 0x00625003, 0x0062a801, 0x00631001,
      0x0063f800, 0x00640802, 0x0065e000, 0x0065f006, 0x00663002, 0x00665003,
      0x0066a801, 0x00671001, 0x00680802, 0x0069f006, 0x006a3002, 0x006a5003,
      0x006ab800, 0x006b1001, 0x006bc800, 0x006c1001, 0x006e5000, 0x006e7805,
      0x006eb000, 0x006ec007, 0x006f9002, 0x00718800, 0x0071a006, 0x0071f800,
      0x00723808, 0x0072d001, 0x00758800, 0x0075a005, 0x0075d801, 0x00764005,
      0x0078081e, 0x0079a00b, 0x007b8816, 0x007c680a, 0x007cc823, 0x007df00e,
      0x007e700c, 0x00815813, 0x00825005, 0x0082b003, 0x0082f002, 0x00831002,
      0x00833806, 0x00838803, 0x0084100b, 0x00847800, 0x0084d005, 0x0087d800,
      0x009ae80b, 0x009c8009, 0x00a00000, 0x00b36801, 0x00b4d801, 0x00b75802,
      0x00b89002, 0x00b99004, 0x00ba9001, 0x00bb9001, 0x00bda022, 0x00bec003,
      0x00bee800, 0x00c0000e, 0x00c54800, 0x00c9000b, 0x00c9800b, 0x00ca0000,
      0x00ca2001, 0x00cd8010, 0x00ce4001, 0x00cef021, 0x00d0b804, 0x00d0f001,
      0x00d2a809, 0x00d3001c, 0x00d3f800, 0x00d50006, 0x00d54005, 0x00d5800e,
      0x00d80004, 0x00d9a010, 0x00dad022, 0x00dc0002, 0x00dd080c, 0x00df300d,
      0x00dfe003, 0x00e12013, 0x00e1d804, 0x00e3f001, 0x00e60007, 0x00e68018,
      0x00e76800, 0x00e79002, 0x00e7c001, 0x00ee0035, 0x00efe003, 0x00fde800,
      0x00fdf802, 0x00fe6802, 0x00fee802, 0x00ff6802, 0x00ffe801, 0x01003800,
      0x0100581c, 0x01015034, 0x01030004, 0x01033009, 0x0103d004, 0x01045004,
      0x0105001d, 0x01068020, 0x01080001, 0x01081803, 0x01084001, 0x0108a000,
      0x0108b002, 0x0108f005, 0x01092800, 0x01093800, 0x01097000, 0x0109d001,
      0x010a0004, 0x010a5003, 0x010a7800, 0x010c826a, 0x01200026, 0x0122000a,
      0x01280275, 0x013ca3df, 0x015bb01f, 0x015cc021, 0x015de80b, 0x015e5007,
      0x01672805, 0x01677802, 0x0167c803, 0x0167f001, 0x016b8000, 0x016bf800,
      0x016f004e, 0x01718012, 0x01740019, 0x0174d858, 0x017800d5, 0x017f800b,
      0x01800803, 0x01804018, 0x01815006, 0x0181b001, 0x0181e802, 0x0184c803,
      0x01850000, 0x0187d800, 0x018c8001, 0x018cb009, 0x018e0023, 0x0190001e,
      0x0191501d, 0x01928000, 0x0193001f, 0x01945026, 0x0196003e, 0x019800ff,
      0x026e003f, 0x05248036, 0x0527f001, 0x05306802, 0x0533780f, 0x0534f800,
      0x05378007, 0x05380016, 0x05390001, 0x053c4801, 0x05401000, 0x05403000,
      0x05405800, 0x05411808, 0x0541b003, 0x0543a003, 0x05440001, 0x0545a010,
      0x05467001, 0x05470011, 0x0547c002, 0x05493009, 0x054a380c, 0x054af800,
      0x054c0003, 0x054d981a, 0x054ef001, 0x054f2800, 0x0551480d, 0x05521800,
      0x05526001, 0x0552e003, 0x0553b802, 0x0553d802, 0x05558000, 0x05559002,
      0x0555b801, 0x0555f001, 0x05560800, 0x0556f001, 0x05575806, 0x0557a801,
      0x055ad800, 0x055f180a, 0x06c00000, 0x06dbf801, 0x06dff801, 0x06fff801,
      0x07c7f800, 0x07d8f000, 0x07d94800, 0x07dd900f, 0x07e9f001, 0x07efe001,
      0x07f00019, 0x07f1000d, 0x07f18022, 0x07f2a012, 0x07f34003, 0x07f7f800,
      0x07f8080e, 0x07f8d006, 0x07f9d805, 0x07fad80a, 0x07ff0006, 0x07ff4006,
      0x07ffc804, 0x08080002, 0x0809b808, 0x080bc810, 0x080c6000, 0x080c800b,
      0x080d0000, 0x080e802d, 0x08170000, 0x081bb004, 0x081cf800, 0x081e8000,
      0x082b7800, 0x0842b800, 0x0843b801, 0x0848f800, 0x0849f800, 0x08500802,
      0x08502801, 0x08506003, 0x0851c002, 0x0851f800, 0x08528008, 0x0853f800,
      0x08564000, 0x08572801, 0x08578006, 0x0859c806, 0x085cc803, 0x08800002,
      0x0881c015, 0x0883f803, 0x08858011, 0x08880002, 0x0889380d, 0x088a0003,
      0x088b9802, 0x088c0002, 0x088d980d, 0x088e2803, 0x088e6800, 0x08916011,
      0x0896f80b, 0x08980802, 0x0899e000, 0x0899f006, 0x089a3801, 0x089a5802,
      0x089ab800, 0x089b1001, 0x089b3006, 0x089b8004, 0x08a58013, 0x08a63000,
      0x08ad7806, 0x08adc011, 0x08b18013, 0x08b5580c, 0x09238004, 0x0b537001,
      0x0b578005, 0x0b59800f, 0x0b5a2001, 0x0b7a882d, 0x0b7c7803, 0x0de4e007,
      0x0e8000f5, 0x0e880026, 0x0e8948b4, 0x0e900045, 0x0e980056, 0x0eb60800,
      0x0eb6d800, 0x0eb7d800, 0x0eb8a800, 0x0eb9a800, 0x0eba7800, 0x0ebb7800,
      0x0ebc4800, 0x0ebd4800, 0x0ebe1800, 0x0f468006, 0x0f778001, 0x0f80002b,
      0x0f818063, 0x0f85000e, 0x0f85880e, 0x0f86080e, 0x0f868824, 0x0f896801,
      0x0f8a5005, 0x0f8b5001, 0x0f8c580f, 0x0f900002, 0x0f90802a, 0x0f920008,
      0x0f928001, 0x0f98002c, 0x0f99804d, 0x0f9c004e, 0x0f9ea023, 0x0fa000fe,
      0x0fa8004a, 0x0faa8029, 0x0fabd828, 0x0fad289d, 0x0fb2288a, 0x0fb7000c,
      0x0fb78003, 0x0fb80073, 0x0fbc0054, 0x0fc0000b, 0x0fc08037, 0x0fc28009,
      0x0fc30027, 0x0fc4801d, 0x70000800, 0x7001005f, 0x700800ef, 0x78000000,
      0x7fffe800, 0x80000000, 0x87ffe800,
  };
  return iswctype_extents(wc, extents, __arraycount(extents));
}
