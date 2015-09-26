import qbs 1.0
import qbs.FileInfo

QtcPlugin {
    name: "ColorPicker"

    Depends { name: "Qt"; submodules: ["widgets"] }
    Depends { name: "Core" }
    Depends { name: "TextEditor" }

    cpp.cxxFlags: "-std=c++11"
    cpp.cxxLanguageVersion: "c++11"

    files: [
        "colormodifier.cpp",
        "colormodifier.h",
        "colorpicker_global.h",
        "colorpickerconstants.h",
        "colorpickerplugin.cpp",
        "colorpickerplugin.h",
        "colorwatcher.cpp",
        "colorwatcher.h",
    ]

    Group {
        name: "Tests"
        condition: project.testsEnabled

        files: [
            "replacecolor_test.cpp"
        ]

        cpp.defines: outer.concat(['SRCDIR="' + FileInfo.path(filePath) + '"'])
    }
}
