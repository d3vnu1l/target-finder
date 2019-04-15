workspace(name = "target_finder")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "build_bazel_rules_nodejs",
    sha256 = "88e5e579fb9edfbd19791b8a3c6bfbe16ae3444dba4b428e5efd36856db7cf16",
    urls = ["https://github.com/bazelbuild/rules_nodejs/releases/download/0.27.8/rules_nodejs-0.27.8.tar.gz"],
)

http_archive(
    name = "com_github_bazelbuild_buildtools",
    sha256 = "7525deb4d74e3aa4cb2b960da7d1c400257a324be4e497f75d265f2f508c518f",
    strip_prefix = "buildtools-0.22.0",
    url = "https://github.com/bazelbuild/buildtools/archive/0.22.0.tar.gz",
)

http_archive(
    name = "io_bazel_rules_go",
    sha256 = "77dfd303492f2634de7a660445ee2d3de2960cbd52f97d8c0dffa9362d3ddef9",
    url = "https://github.com/bazelbuild/rules_go/releases/download/0.18.1/rules_go-0.18.1.tar.gz",
)

load("@build_bazel_rules_nodejs//:defs.bzl", "check_bazel_version")
load("@com_github_bazelbuild_buildtools//buildifier:deps.bzl", "buildifier_dependencies")
load("@io_bazel_rules_go//go:deps.bzl", "go_register_toolchains", "go_rules_dependencies")

check_bazel_version("0.24.1")

go_rules_dependencies()

go_register_toolchains()

buildifier_dependencies()