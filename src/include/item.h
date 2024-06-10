#ifndef __ITEM_H__
#define __ITEM_H__

#include "common.h"

typedef enum icon_e
{
  ICON_DIR,
  ICON_FILE,
  ICON_BASH,
  ICON_MAKEFILE,
  ICON_MD,
  ICON_CONFIG,
  ICON_GITIGNORE,
  ICON_GIT_DIR,
  ICON_DOCKERFILE,
  ICON_ESLINT,
  ICON_PRETTIER,
  ICON_TAILWIND,
  ICON_C,
  ICON_CPP,
  ICON_H,
  ICON_RS,
  ICON_CS,
  ICON_JAVA,
  ICON_SWIFT,
  ICON_PY,
  ICON_TS,
  ICON_JS,
  ICON_REACT,
  ICON_JSON,
  ICON_HTML,
  ICON_CSS,
  ICON_SVG,
  ICON_LENGTH
} icon_e;

char icon_list[ICON_LENGTH][10] = {
  "\U000F024B", // ICON_DIR
  "\U000F0214", // ICON_FILE
  "\uE795",     // ICON_BASH
  "\uE779",     // ICON_MAKEFILE
  "\uE28B",     // ICON_MD
  "\uE615",     // ICON_CONFIG
  "\U000F02A2", // ICON_GITIGNORE
  "\uE5FB",     // ICON_GIT_DIR
  "\U000F0868", // ICON_DOCKERFILE
  "\U000F0C7A", // ICON_ESLINT
  "\uE6B4",     // ICON_PRETTIER
  "\U000F13FF", // ICON_TAILWIND
  "\uE649",     // ICON_C
  "\uE646",     // ICON_CPP
  "\U000F0829", // ICON_H
  "\U000F1617", // ICON_RS
  "\uE648",     // ICON_CS
  "\uEDAF",     // ICON_JAVA
  "\uE699",     // ICON_SWIFT
  "\uE606",     // ICON_PY
  "\U000F06E6", // ICON_TS
  "\U000F031E", // ICON_JS
  "\U000F0708", // ICON_REACT
  "\uE60B",     // ICON_JSON
  "\uE736",     // ICON_HTML
  "\uE74A",     // ICON_CSS
  "\U000F0721"  // ICON_SVG
};

char color_list[ICON_LENGTH][22] = {
  "\x1B[38;2;100;170;210m",  // ICON_DIR (Lightblue)
  "\x1B[38;2;181;181;181m",  // ICON_FILE (Lightgray)
  "\x1B[38;2;193;167;64m",   // ICON_BASH (Yellow)
  "\x1B[38;2;210;210;210m",  // ICON_MAKEFILE (White)
  "\x1B[38;2;154;120;82m",   // ICON_MD (Brown)
  "\x1B[38;2;128;128;128m",  // ICON_CONFIG (Gray)
  "\x1B[38;2;205;86;63m",    // ICON_GITIGNORE (OrangeRed)
  "\x1B[38;2;205;86;63m",    // ICON_GIT_DIR (OrangeRed)
  "\x1B[38;2;69;154;195m",   // ICON_DOCKERFILE (Lightblue)
  "\x1B[38;2;128;128;235m",  // ICON_ESLINT (Lightpurple)
  "\x1B[38;2;164;134;77m",   // ICON_PRETTIER (Lightbrown)
  "\x1B[38;2;96;166;177m",   // ICON_TAILWIND (Lightblue)
  "\x1B[38;2;0;191;255m",    // ICON_C (DeepSkyBlue)
  "\x1B[38;2;65;105;225m",   // ICON_CPP (RoyalBlue)
  "\x1B[38;2;39;93;141m",    // ICON_H (SteelBlue)
  "\x1B[38;2;198;120;60m",   // ICON_RS (DarkGoldenRod)
  "\x1B[38;2;74;118;68m",    // ICON_CS (Green)
  "\x1B[38;2;89;118;145m",   // ICON_JAVA (LightSeaGreen)
  "\x1B[38;2;233;105;62m",   // ICON_SWIFT (Lightorange)
  "\x1B[38;2;88;166;255m",   // ICON_PY (Lightblue)
  "\x1B[38;2;0;191;255m",    // ICON_TS (DeepSkyBlue)
  "\x1B[38;2;255;223;0m",    // ICON_JS (Yellow)
  "\x1B[38;2;97;218;251m",   // ICON_REACT (SkyBlue)
  "\x1B[38;2;219;204;80m",   // ICON_JSON (Yellow)
  "\x1B[38;2;221;105;58m",   // ICON_HTML (Orange)
  "\x1B[38;2;84;161;211m",   // ICON_CSS (Lightblue)
  "\x1B[38;2;244;180;84m"    // ICON_SVG (Yellow)
};

typedef enum type_e
{
  TYPE_DIR,
  TYPE_FILE,
  TYPE_LENGTH
} type_e;

typedef struct item_t
{
  type_e type;
  icon_e icon;
  char name[FILENAME_MAX];
  char extension[FILENAME_MAX];
  int hidden;
} item_t;

typedef struct hash_entry_t
{
  char *key;
  icon_e value;
  struct hash_entry_t *next;
} hash_entry_t;

typedef struct hash_map_t
{
  hash_entry_t **buckets;
  size_t size;
} hash_map_t;

void print_item(item_t);
item_t init_item(struct dirent *);
icon_e get_icon_for_extension(item_t item);

#endif
