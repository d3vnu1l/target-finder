package(default_visibility = ["//visibility:public"])

cc_binary (
    name = "code_exe",
    deps = [":code"],
)

cc_library(
    name = "code",
    srcs = ["main.cpp"],
    deps = [
        "//code/pixel_parser",
        "//code/screen_shotter",
        "//code/system_info",
    ],
)