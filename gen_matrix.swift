#!/usr/bin/swift

import Cocoa
import Foundation

let cwd = FileManager.default.currentDirectoryPath
let in_file = CommandLine.arguments.count < 2 ? "00.txt" : CommandLine.arguments[1]
let out_file = in_file + ".out"
let size = 10;
let randomRange = -10 ..< 10

let left = (0..<size).map { _ in
    return (0..<size).map { _ in return Int.random(in: randomRange) }
}
let right = (0..<size).map { _ in
    return (0..<size).map { _ in return Int.random(in: randomRange) }
}
var result = (0..<size).map { _ in
    return (0..<size).map { _ in return 0 }
}

for i in 0..<size {
    for j in 0..<size {
        result[i][j] = 0
        for k in 0..<size {
            result[i][j] += left[i][k] * right[k][j]
        }
    }
}

// Prepare strings
let left_str: String = left
    .map { $0.map { String($0) } }
    .map { $0.joined(separator: " ") }
    .joined(separator:"\n")
let right_str: String = right
    .map { $0.map { String($0) } }
    .map { $0.joined(separator: " ") }
    .joined(separator:"\n")
let results_str: String = result
    .map { $0.map { String($0) } }
    .map { $0.joined(separator: " ") }
    .joined(separator:"\n")

let manager = FileManager.default
let in_file_data = (left_str + "\n\n" + right_str + "\n").data(using: .utf8)
manager.createFile(atPath: in_file, contents: in_file_data, attributes: nil)
let out_file_data = results_str.data(using: .utf8)
manager.createFile(atPath: out_file, contents: out_file_data, attributes: nil)

//print(FileManager.default.isWritableFile(atPath: in_file))
//print(FileManager.default.isWritableFile(atPath: out_file))
//print(left_str)
//print(right_str)
//print(results_str)

