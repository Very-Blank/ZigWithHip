const std = @import("std");
const Io = std.Io;

const hip = @import("hip");

const HipError = enum(u32) {
    ok = 0,
    _,

    pub inline fn from(value: u32) HipError {
        return @enumFromInt(value);
    }
};

pub fn main(_: std.process.Init) !void {
    std.debug.print("Cpp returned: {any}.\n", .{hip.add(4, 6)});

    var hipStream: hip.HipStream = undefined;
    if (HipError.from(hip.createHipStream(&hipStream)) != .ok) return error.CreateHipStreamFailed;
    defer hip.destroyHipStream(hipStream);
}
