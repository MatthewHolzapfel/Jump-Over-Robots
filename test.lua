file = io.open("test.lua", "w")
io.output(file)
io.write("This works!")
io.close(file)