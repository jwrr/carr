cmake_minimum_required(VERSION 2.8)

project(carr_prj)

add_library(carr STATIC carr_arg.c carr.c carr_readline.c carr_readline_lua.c lua_hacked.c)

INSTALL(TARGETS carr DESTINATION lib)
INSTALL(FILES carr_readline.h carr_esc.h carr_readline_lua.h carr.h carr_arg.h carr_cis.h DESTINATION include)


