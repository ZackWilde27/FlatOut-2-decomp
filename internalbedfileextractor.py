print("== FlatOut 2 Internal BED Extractor ==")
print("This only works on the DRM-free copies of FlatOut 2 (GOG or Epic Games). It does not work with the Steam version")
fo2_path = input("Path to FlatOut 2 exe: ")
directory = fo2_path[:-12]

with open(fo2_path, 'rb') as file:

    file.seek(0x2649a0)
    with open(directory + "sandbox.bed", 'wb') as sandbox:
        sandbox.write(file.read1(0xD8B))

    file.seek(0x265a08)
    with open(directory + "windowfunctions.bed", 'wb') as wfunc:
        wfunc.write(file.read1(0x1F0B))

    file.seek(0x26ac58)
    with open(directory + "fonts.bed", 'wb') as fonts:
        fonts.write(file.read1(0xDB))

print("Done!")
