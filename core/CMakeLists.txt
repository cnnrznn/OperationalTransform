# libraries
add_library(ops ops.c)
add_library(queue queue.c)
add_library(ot-client ot-client.c)
add_library(ot-server ot-server.c)

# link (only have to link exec's against ot-client/ot-server)
target_link_libraries(ot-client ops queue)
target_link_libraries(ot-server ops queue)
