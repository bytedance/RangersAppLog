#!/usr/bin/python
# -*- coding: UTF-8 -*-

import sys
import os
import io
import json

def util_dump(json_resp, file):
    with open(file, 'w') as json_file:
        json.dump(json_resp, json_file, indent=2, sort_keys=True, ensure_ascii=False)
        pass
    pass

def util_load(file):
    data = None
    with open(file) as f:
        data = json.load(f)
        pass

    return data

def check_base_link_map_file(base_link_map_file):
  if not os.path.exists(base_link_map_file):
    print("The File " + base_link_map_file + " not exist.")
    return False

  with open(base_link_map_file, errors='ignore') as link_map_file:
    content = link_map_file.read()
    obj_file_tag_index = content.find("# Object files:")
    sub_obj_file_symbol_str = content[obj_file_tag_index + 15:]
    symbols_index = sub_obj_file_symbol_str.find("# Symbols:")
    if obj_file_tag_index == -1 or symbols_index == -1:
      print("The Content of File " + base_link_map_file + " is Invalid.")
      return False

  return True

def read_key_symbol(line):
  key = 0
  symbol = {}
  index = line.find("]")
  if index != -1:
    file = line[index + 2:-1]
    o_file_name = file.split("/")[-1]
    # a_file_name = o_file_name.split("(")[0]
    symbol = {"file": o_file_name}
    key = int(line[1: index])
    pass

  return key, symbol


def read_key_size(line):
  key = 0
  size = 0
  symbols_array = line.split("\t")
  if len(symbols_array) == 3:
    file_key_and_name = symbols_array[2]
    size = int(symbols_array[1], 16)
    index = file_key_and_name.find("]")
    if index != -1:
      key = file_key_and_name[1:index]
      key = int(key)

  return key, size


def read_base_link_map_file(base_link_map_file, lib_names = []):
  if not check_base_link_map_file(base_link_map_file):
    print("check_base_link_map_file fail")
    return

  reach_files = 0
  reach_sections = 0
  reach_symbols = 0
  size_map = {}
  with open(base_link_map_file, errors='ignore') as link_map_file:
    for line in link_map_file:
      if line.startswith("#"):
        if line.startswith("# Object files:"):
          reach_files = 1
          continue
        if line.startswith("# Sections"):
          reach_sections = 1
          continue
        if line.startswith("# Symbols"):
          reach_symbols = 1
          continue
        continue
      else:
        if reach_files == 1 and reach_sections == 0 and reach_symbols == 0:
          key, symbol = read_key_symbol(line)
          size_map[key] = symbol
          continue
        elif reach_files == 1 and reach_sections == 1 and reach_symbols == 0:
          continue
        elif reach_files == 1 and reach_sections == 1 and reach_symbols == 1:
          key, size = read_key_size(line)
          if key < 1:
            continue
          symbol = size_map[key]
          if "size" in symbol:
            symbol["size"] += size
            pass
          else:
            symbol["size"] = size
            pass
          continue
        else:
          print("Invalid line")
          print(line)
          pass
        pass
      pass
    pass

  total_size = 0
  a_file_map = {}
  o_file_name_list = {}
  for key in size_map:
    symbol = size_map[key]
    if "size" in symbol:
      total_size += symbol["size"]
      o_file_name = symbol["file"]
      file_names = o_file_name.split("(")
      a_file_name = file_names[0]

      if a_file_name in a_file_map:
        a_file_map[a_file_name] += symbol["size"]
      else:
        a_file_map[a_file_name] = symbol["size"]
        pass

      if len(file_names) < 2:
        continue

      o_file_name_str = o_file_name.split("(")[1].rstrip(")")
      if a_file_name in o_file_name_list:
        o_file_name_list[a_file_name][o_file_name_str] = symbol["size"]
      else:
        o_file_name_list[a_file_name] = {o_file_name_str:symbol["size"]}
        pass
    else:
      print("WARN : some error occurred for key ",key)
      pass
    pass

  # a_file_sorted_list = sorted(a_file_map.items(), key=lambda x: x[1], reverse=True)
  # print("总共大小 %.0f B \t%.2f KB \t%.2f MB" % (total_size, total_size/1024.0, total_size/1024.0/1024.0))
  # for lib_name in a_file_map:
    # size = a_file_map[lib_name]
    # print("%s%.0f B \t%.2f KB" % (lib_name.ljust(50), size, size/1024.0))

  dump_json = {}
  print("\n\n")
  lib_total_size = 0
  all_libs = a_file_map.keys()
  for lib_name in all_libs:
    if "libRangers" in lib_name or "libE" in lib_name or "libBD" in lib_name or "libRSK" in lib_name:
    # if "libRangersKit" in lib_name or "libRSK" in lib_name:
      lib_names.append(lib_name)
    pass


  for lib_name in lib_names:#a_file_map.keys():#
    dump_info = {}
    file_size_info = {}
    if lib_name not in a_file_map:
      continue

    size = a_file_map[lib_name]
    lib_total_size += size
    print("%s%.0f B \t%.2f KB" % (lib_name.ljust(50), size, size/1024.0))
    dump_info["size"] = "%.2f KB" % (size/1024.0)
    dump_info["files"] = file_size_info

    if lib_name in o_file_name_list:
      o_file_names = o_file_name_list[lib_name]
      for o_file_name, size in o_file_names.items():
        # print("\t%s%.0f B \t%.2f KB" % (o_file_name.ljust(42), size, size/1024.0))
        file_size_info[o_file_name] = "%.2f KB" % (size/1024.0)
        pass

    dump_json[lib_name] = dump_info

  dump_json["total_size"] = "%.2f KB" % (lib_total_size/1024.0)
  util_dump(dump_json, "sdk_size_info.json")
  print("sdk 总大小 %.0f B \t%.2f KB" % (lib_total_size, lib_total_size/1024.0))


def print_help():
  print("%s%s\n" % ("".ljust(10), "- Usage : python LinkMapParser.py LinkMapFile".ljust(80)))
  pass


if __name__ == "__main__":
  if len(sys.argv) < 2:
    print_help()
    exit(1)

  base_map_link_file = sys.argv[1]
  read_base_link_map_file(base_map_link_file)



