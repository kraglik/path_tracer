target_sources(path_tracer
    PRIVATE
        tracer.c
        camera.c
        material.c
)
add_subdirectory(math)
add_subdirectory(object)