local filename = "bin/SparkAmpOS.bin"

-- Open The File In Binary Mode
local file = io.open(filename, "rb")

-- ANSI Escape Sequences
local blue = "\27[34m"
local red = "\27[31m"
local reset = "\27[0m"

local ksize_sectors

-- Show Info
if file then
	file:seek("end")
	local size = file:seek()

	ksize_sectors = math.ceil(size / 512) + 1

	file:close()
	io.write(blue .. "File Size: " .. size .. " bytes" .. reset .. "\n")
	io.write(blue .. "Sectors to read: " .. ksize_sectors .. reset .. "\n")
else
	io.write(red .. "Failed to open the file" .. reset .. "\n")
end

-- Write New Kernel Size To Bootloader Source Code
local boot_filepath = "boot/sys_init/kernel_size.inc"

local boot_file = io.open(boot_filepath, "r")
local content = boot_file:read("*all")
boot_file:close()

local macro_pattern = "KERNEL_SIZE%s+equ%s+(%d+)"
local curr_val = content:match(macro_pattern)
if curr_val then
	local new_val = tostring(ksize_sectors)
	local new_content = content:gsub(macro_pattern, "KERNEL_SIZE equ " .. new_val)

	local new_boot_file = io.open(boot_filepath, "w")
	new_boot_file:write(new_content)
	new_boot_file:close()
	print("Kernel size updated successfully.")
else
	print("KERNEL_SIZE macro not found.")
end
