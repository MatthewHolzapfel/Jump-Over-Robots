print("Hi.")
io.write("???")
filename = "test.txt"
file = io.open(filename, "r+")
io.input(file)
io.write("This works!")
file:write("Or this?")
io.close(file)
file2 = io.open("test.lua", "a+")
file2:write("...please?")
file2:close()