#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ical" for configuration ""
set_property(TARGET ical APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ical PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libical.so.3.0.95"
  IMPORTED_SONAME_NOCONFIG "libical.so.3"
  )

list(APPEND _cmake_import_check_targets ical )
list(APPEND _cmake_import_check_files_for_ical "${_IMPORT_PREFIX}/lib/libical.so.3.0.95" )

# Import target "ical-static" for configuration ""
set_property(TARGET ical-static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ical-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libical.a"
  )

list(APPEND _cmake_import_check_targets ical-static )
list(APPEND _cmake_import_check_files_for_ical-static "${_IMPORT_PREFIX}/lib/libical.a" )

# Import target "ical_cxx" for configuration ""
set_property(TARGET ical_cxx APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ical_cxx PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libical_cxx.so.3.0.95"
  IMPORTED_SONAME_NOCONFIG "libical_cxx.so.3"
  )

list(APPEND _cmake_import_check_targets ical_cxx )
list(APPEND _cmake_import_check_files_for_ical_cxx "${_IMPORT_PREFIX}/lib/libical_cxx.so.3.0.95" )

# Import target "ical_cxx-static" for configuration ""
set_property(TARGET ical_cxx-static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ical_cxx-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libical_cxx.a"
  )

list(APPEND _cmake_import_check_targets ical_cxx-static )
list(APPEND _cmake_import_check_files_for_ical_cxx-static "${_IMPORT_PREFIX}/lib/libical_cxx.a" )

# Import target "icalss" for configuration ""
set_property(TARGET icalss APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(icalss PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libicalss.so.3.0.95"
  IMPORTED_SONAME_NOCONFIG "libicalss.so.3"
  )

list(APPEND _cmake_import_check_targets icalss )
list(APPEND _cmake_import_check_files_for_icalss "${_IMPORT_PREFIX}/lib/libicalss.so.3.0.95" )

# Import target "icalss-static" for configuration ""
set_property(TARGET icalss-static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(icalss-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libicalss.a"
  )

list(APPEND _cmake_import_check_targets icalss-static )
list(APPEND _cmake_import_check_files_for_icalss-static "${_IMPORT_PREFIX}/lib/libicalss.a" )

# Import target "icalss_cxx" for configuration ""
set_property(TARGET icalss_cxx APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(icalss_cxx PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libicalss_cxx.so.3.0.95"
  IMPORTED_SONAME_NOCONFIG "libicalss_cxx.so.3"
  )

list(APPEND _cmake_import_check_targets icalss_cxx )
list(APPEND _cmake_import_check_files_for_icalss_cxx "${_IMPORT_PREFIX}/lib/libicalss_cxx.so.3.0.95" )

# Import target "icalss_cxx-static" for configuration ""
set_property(TARGET icalss_cxx-static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(icalss_cxx-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libicalss_cxx.a"
  )

list(APPEND _cmake_import_check_targets icalss_cxx-static )
list(APPEND _cmake_import_check_files_for_icalss_cxx-static "${_IMPORT_PREFIX}/lib/libicalss_cxx.a" )

# Import target "icalvcal" for configuration ""
set_property(TARGET icalvcal APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(icalvcal PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libicalvcal.so.3.0.95"
  IMPORTED_SONAME_NOCONFIG "libicalvcal.so.3"
  )

list(APPEND _cmake_import_check_targets icalvcal )
list(APPEND _cmake_import_check_files_for_icalvcal "${_IMPORT_PREFIX}/lib/libicalvcal.so.3.0.95" )

# Import target "icalvcal-static" for configuration ""
set_property(TARGET icalvcal-static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(icalvcal-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libicalvcal.a"
  )

list(APPEND _cmake_import_check_targets icalvcal-static )
list(APPEND _cmake_import_check_files_for_icalvcal-static "${_IMPORT_PREFIX}/lib/libicalvcal.a" )

# Import target "ical-glib" for configuration ""
set_property(TARGET ical-glib APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ical-glib PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_NOCONFIG "ical"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libical-glib.so.3.0.95"
  IMPORTED_SONAME_NOCONFIG "libical-glib.so.3"
  )

list(APPEND _cmake_import_check_targets ical-glib )
list(APPEND _cmake_import_check_files_for_ical-glib "${_IMPORT_PREFIX}/lib/libical-glib.so.3.0.95" )

# Import target "ical-glib-static" for configuration ""
set_property(TARGET ical-glib-static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ical-glib-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libical-glib.a"
  )

list(APPEND _cmake_import_check_targets ical-glib-static )
list(APPEND _cmake_import_check_files_for_ical-glib-static "${_IMPORT_PREFIX}/lib/libical-glib.a" )

# Import target "icalvcard" for configuration ""
set_property(TARGET icalvcard APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(icalvcard PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libicalvcard.so.3.0.95"
  IMPORTED_SONAME_NOCONFIG "libicalvcard.so.3"
  )

list(APPEND _cmake_import_check_targets icalvcard )
list(APPEND _cmake_import_check_files_for_icalvcard "${_IMPORT_PREFIX}/lib/libicalvcard.so.3.0.95" )

# Import target "icalvcard-static" for configuration ""
set_property(TARGET icalvcard-static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(icalvcard-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libicalvcard.a"
  )

list(APPEND _cmake_import_check_targets icalvcard-static )
list(APPEND _cmake_import_check_files_for_icalvcard-static "${_IMPORT_PREFIX}/lib/libicalvcard.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
