package(default_visibility = ["//visibility:public"])

cc_library(
    name = "screen_shotter",
    srcs = ["screen_shotter.cpp"],
    hdrs = ["screen_shotter.hpp"],
    deps = [
    ],
    includes = ["."],
    linkopts = ["-SUBSYSTEM:WINDOWS",
                "\gdi32.lib user32.lib",
    ],
)