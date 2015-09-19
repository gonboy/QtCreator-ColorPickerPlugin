import qbs 1.0

QtcPlugin {
    name: "ColorPicker"

    Depends { name: "Qt"; submodules: ["widgets"] }
    Depends { name: "Core" }
    Depends { name: "TextEditor" }

    files: [
        "colorpickerplugin.cpp",
        "colorpickerplugin.h",
        "colorwatcher.cpp",
        "colorwatcher.h",
    ]
}
