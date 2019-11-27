cc_binary (
    name = "code",
    deps = [":main"],
)

cc_library(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        ":target_finder"
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "target_finder",
    srcs = ["target_finder.cpp"],
    hdrs = ["target_finder.hpp"],
    deps = [
        "//code/pixel_parser",
        "//code/screen_shotter",
        "//code/system_info",
    ],
)