const std = @import("std");
const Io = std.Io;

const hip = @import("hip");

pub fn main(_: std.process.Init) !void {
    // Prints to stderr, unbuffered, ignoring potential errors.
    std.debug.print("Cpp returned: {any}.\n", .{hip.add(4, 6)});

    var hipStream: hip.HipStream = undefined;
    if (hip.createHipStream(@ptrCast(&hipStream)) != hip.OK) return error.CreateHipStreamFailed;
    defer hip.destroyHipStream(@ptrCast(&hipStream));
}
