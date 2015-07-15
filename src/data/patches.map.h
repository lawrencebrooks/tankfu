#ifndef PATCHES_MAP_H
#define PATCHES_MAP_H

#define PATCH_NAVIGATE 0
#define PCM_CHANNEL 4

const struct PatchStruct my_patches[] PROGMEM = {
  {2,ad_navigate,0,sizeof(ad_navigate)-2,sizeof(ad_navigate)-1}
};

#endif