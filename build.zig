const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const hip_translated_c = b.addTranslateC(.{
        .root_source_file = b.path("libs/hip/hip.h"),
        .optimize = optimize,
        .target = target,
        .link_libc = true,
    });

    const hip_library = b.addLibrary(.{
        .name = "hip",
        .root_module = init: {
            const hip_module = b.createModule(.{
                .optimize = optimize,
                .target = target,
                .link_libcpp = true,
            });

            hip_module.addObjectFile(b.path("libs/hip/hip.o"));

            break :init hip_module;
        },
        .linkage = .static,
    });

    b.installArtifact(hip_library);

    const exe = b.addExecutable(.{
        .name = "ZigWithHip",
        .root_module = init: {
            const exe_module = b.createModule(.{
                .root_source_file = b.path("src/main.zig"),
                .target = target,
                .optimize = optimize,
                .imports = &.{
                    .{ .name = "hip", .module = hip_translated_c.createModule() },
                },
            });

            exe_module.linkLibrary(hip_library);
            exe_module.linkSystemLibrary("amdhip64", .{});

            break :init exe_module;
        },
    });

    b.installArtifact(exe);

    const run_step = b.step("run", "Run the app");

    const run_cmd = b.addRunArtifact(exe);
    run_step.dependOn(&run_cmd.step);

    run_cmd.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const exe_tests = b.addTest(.{
        .root_module = exe.root_module,
    });

    const run_exe_tests = b.addRunArtifact(exe_tests);

    const test_step = b.step("test", "Run tests");
    test_step.dependOn(&run_exe_tests.step);
}
