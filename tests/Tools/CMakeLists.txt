file(GLOB SUBDIRS *.cmake)
foreach(sub ${SUBDIRS})
    include(${sub})
endforeach()

