flags = Split('-Wall -Wextra -pedantic -std=c99 -O')
lib_path =  Split('/usr/local/lib')
cpp_path = Split('/usr/local/include') 


src_files = Split('main.c gpu_data_utils.c')
libs = Split('GLEW glfw GL X11 pthread rt')


Program('jumpy', src_files, LIBS=libs, CCFLAGS=flags, CPPPATH = cpp_path,
    LIBPATH = lib_path)
