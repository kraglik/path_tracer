target_sources(path_tracer
    PRIVATE
        tracer.c
        camera.c
)
add_subdirectory(math)
add_subdirectory(object)