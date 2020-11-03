cmake_minimum_required(VERSION "3.18.2")

project("kernel.elf")

set(LINKER_SCRIPT "linker.ld")

aux_source_directory(src/ CFILES)

add_executable("${PROJECT_NAME}" CFILES)