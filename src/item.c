#include "include/item.h"

void print_item(item_t item)
{
  char *weight = item.type == TYPE_DIR ? "\033[1m" : "\033[0m";
  char *color = item.hidden ? "\x1B[38;2;100;115;115m" : "\x1b[38;2;211;211;211m";

  char name[FILENAME_MAX + 29] = {0};
  char icon[32] = {0};

  sprintf(name, "%s%s%s", weight, color, item.name);
  sprintf(icon, "%s%s", color_list[item.icon], icon_list[item.icon]);

  printf("  %s %s%s%s%s\n", icon, weight, color, item.name, PRINT_RESET);
}

item_t init_item(struct dirent *dir)
{
  char *extension = strrchr(dir->d_name, '.');
  item_t item = {0};
  item.hidden = dir->d_name[0] == '.';
  item.type = dir->d_type == DT_DIR ? TYPE_DIR : TYPE_FILE;
  strcpy(item.name, dir->d_name);
  strcpy(item.extension, extension != NULL ? extension + 1 : "\0");
  item.icon = get_icon_for_extension(item);
  return item;
}

hash_map_t* init_hash_map(size_t size) {
  hash_map_t *map = malloc(sizeof(hash_map_t));
  if (map == NULL) return NULL;
  map->size = size;
  map->buckets = calloc(size, sizeof(hash_entry_t*));
  if (map->buckets == NULL)
  {
    free(map);
    return NULL;
  }
  return map;
}

size_t hash_alg(const char *key)
{
  size_t hash = 0;
  while (*key)
  {
    hash = hash * 31 + *key++;
  }
  return hash;
}

void hash_map_insert(hash_map_t *map, const char *key, icon_e value)
{
  size_t index = hash_alg(key) % map->size;
  hash_entry_t *new_entry = malloc(sizeof(hash_entry_t));
  new_entry->key = strdup(key);
  new_entry->value = value;
  new_entry->next = map->buckets[index];
  map->buckets[index] = new_entry;
}

icon_e* hash_map_lookup(hash_map_t *map, const char *key)
{
  size_t index = hash_alg(key) % map->size;
  hash_entry_t *entry = map->buckets[index];

  while (entry)
  {
    if (strcmp(entry->key, key) == 0)
    {
      return &entry->value;
    }
    entry = entry->next;
  }

  return NULL;
}

void free_hash_map(hash_map_t *map)
{
  for (int i = 0; i < map->size; i++)
  {
    hash_entry_t *entry = map->buckets[i];
    while (entry)
    {
      hash_entry_t *tmp = entry;
      entry = entry->next;
      free(tmp->key);
      free(tmp);
    }
  }
  free(map->buckets);
  free(map);
}

hash_map_t* init_icon_map()
{
  hash_map_t *map = init_hash_map(ICON_LENGTH);

  hash_map_insert(map, "sh", ICON_BASH);
  hash_map_insert(map, "md", ICON_MD);
  hash_map_insert(map, "env", ICON_CONFIG);
  hash_map_insert(map, "gitignore", ICON_GITIGNORE);
  hash_map_insert(map, "git", ICON_GIT_DIR);
  hash_map_insert(map, "prettierrc", ICON_PRETTIER);
  hash_map_insert(map, "prettierignore", ICON_PRETTIER);
  hash_map_insert(map, "c", ICON_C);
  hash_map_insert(map, "cpp", ICON_CPP);
  hash_map_insert(map, "h", ICON_H);
  hash_map_insert(map, "rs", ICON_RS);
  hash_map_insert(map, "cs", ICON_CS);
  hash_map_insert(map, "java", ICON_JAVA);
  hash_map_insert(map, "swift", ICON_SWIFT);
  hash_map_insert(map, "py", ICON_PY);
  hash_map_insert(map, "ts", ICON_TS);
  hash_map_insert(map, "js", ICON_JS);
  hash_map_insert(map, "tsx", ICON_REACT);
  hash_map_insert(map, "jsx", ICON_REACT);
  hash_map_insert(map, "json", ICON_JSON);
  hash_map_insert(map, "html", ICON_HTML);
  hash_map_insert(map, "css", ICON_CSS);
  hash_map_insert(map, "svg", ICON_SVG);

  return map;
}

icon_e get_icon_for_extension(item_t item)
{
  char *extension = item.extension;

  static hash_map_t *icon_map = NULL;
  if (icon_map == NULL)
  {
    icon_map = init_icon_map();
  }

  if (extension == NULL || strlen(extension) == 0)
  {
    if (item.type == TYPE_FILE)
    {
      if (strcmp(item.name, "Makefile") == 0) return ICON_MAKEFILE;
      if (strcmp(item.name, "Dockerfile") == 0) return ICON_DOCKERFILE;
    }
    return item.type == TYPE_DIR ? ICON_DIR : ICON_FILE;
  }

  if (strcmp(extension, "js") == 0)
  {
    if (strcmp(item.name, ".eslintrc.js") == 0) return ICON_ESLINT;
    if (strcmp(item.name, "prettier.config.js") == 0) return ICON_PRETTIER;
    if (strcmp(item.name, "tailwind.config.js") == 0) return ICON_TAILWIND;
  }
  if (strcmp(extension, "cjs") == 0)
  {
    if (strcmp(item.name, ".eslintrc.cjs") == 0) return ICON_ESLINT;
  }

  icon_e *icon_ptr = hash_map_lookup(icon_map, item.extension);
  if (icon_ptr != NULL)
  {
    return *icon_ptr;
  }

  return item.type == TYPE_DIR ? ICON_DIR : ICON_FILE;
}
