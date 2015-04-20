-- http://industriousone.com/topic/newplatform
function newplatform(plf)
    local name = plf.name
    local description = plf.description
 
    -- Register new platform
    premake.platforms[name] = {
        cfgsuffix = "_"..name,
        iscrosscompiler = true
    }
 
    -- Allow use of new platform in --platfroms
    table.insert(premake.option.list["platform"].allowed, { name, description })
    table.insert(premake.fields.platforms.allowed, name)
 
    -- Add compiler support
    -- gcc
    premake.gcc.platforms[name] = plf.gcc
    --other compilers (?)
end
 
function newgcctoolchain(toolchain)
    newplatform {
        name = toolchain.name,
        description = toolchain.description,
        gcc = {
            cc = toolchain.prefix .. "gcc",
            cxx = toolchain.prefix .. "g++",
            ar = toolchain.prefix .. "ar",
            cppflags = "-MMD " .. toolchain.cppflags
        }
    }
end

newplatform {
    name = "mingw",
    description = "Mingw Windows cross-compiler",
    gcc = {
        cc = "/usr/bin/i486-mingw32-gcc",
        cxx = "/usr/bin/i486-mingw32-g++",
        cppflags = "-DMINGW32"
    }
}
 


solution "ld32warmup"
   configurations { "Debug", "Release" }
   platforms { "native", "mingw" }
   language "C++"
   targetdir "bin"

   configuration { "native", "linux" }
      defines { "OSLINUX" }
      includedirs { "/usr/local/include", "/usr/include/bullet" }
	  libdirs { "/usr/local/lib" }
      links { "m", "GL", "GLU", "pthread", "sndfile", "openal", "GLEW", "sfml-audio", "sfml-graphics", "sfml-window", "sfml-system", "Xrandr", "IL", "ILU", "X11", "dl", "BulletSoftBody", "BulletDynamics", "BulletCollision", "LinearMath", "boost_locale" }
      -- Add the current directory the .so search path
      linkoptions { "-Wl,-R." }
      linkoptions { "-Wl,-R./bin" }
      buildoptions { "-std=c++11" }
      -- needed, as by default on arch the default elf interpreter is /lib/ld-linux-x86-64.so.2
      -- instead of /lib64/ld-linux-x86-64.so.2 that seems to be used on others distro (at least
      -- ubuntu, but is also available on arch)
      -- To see the interpreter used: readelf -l executable_name
      -- eg: readelf -l ./bin/pong3d
      linkoptions { "-Wl,-dynamic-linker,/lib64/ld-linux-x86-64.so.2" }
 
   configuration "windows"
      defines { "OSWINDOWS" }
      includedirs { "external/vstudio2k13/glew-1.12.0/include", "external/vstudio2k13/SFML-2.2/include", "external/vstudio2k13/devil-1.7.8/include", "external/vstudio2k13/bullet3/include", "$(BOOST_PATH)" }
      libdirs { "external/vstudio2k13/glew-1.12.0/lib", "external/vstudio2k13/SFML-2.2/lib", "external/vstudio2k13/devil-1.7.8/lib", "external/vstudio2k13/bullet3/lib", "$(BOOST_PATH)/lib", "$(BOOST_PATH)/stage/lib" }
      links { "opengl32", "glu32", "glew32", "DevIL", "ILU", "ILUT" }
      configuration { "windows", "Debug" }
	  links { "BulletSoftBody_debug", "BulletDynamics_debug", "BulletCollision_debug", "LinearMath_debug", "sfml-graphics-d", "sfml-main-d", "sfml-system-d", "sfml-window-d", "sfml-audio-d" }
      configuration { "windows", "Release" }
	  links { "BulletSoftBody", "BulletDynamics", "BulletCollision", "LinearMath", "sfml-graphics", "sfml-main", "sfml-system", "sfml-window", "sfml-audio" }

      configuration "mingw"
      -- Does not work at the moment
      links { "m", "GL", "GLU", "pthread", "sndfile", "openal", "GLEW", "sfml-audio", "sfml-graphics", "sfml-window", "sfml-system", "Xrandr", "IL", "ILU", "X11", "dl" }
      includedirs { "external/mingw/glew/include", "external/mingw/sfml2/include" }
      libdirs { "external/mingw/glew/lib", "external/mingw/sfml2/lib" }

   project "pong3d"
      kind "ConsoleApp"
      files { "*.h", "*.cpp" }
      location ("build/" .. iif(_ACTION ~= nil, _ACTION, ""))
      links { "tak" }
      includedirs { "tak" }
      uuid "3DDD58D6-F7FD-1B4E-5AF8-DE509FA64237"
 
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }

   project "tak"
      kind "StaticLib"
      files { "tak/*.h", "tak/*.cpp" }
      location ("build/" .. iif(_ACTION ~= nil, _ACTION, ""))
      uuid "F03ACDFC-7268-D161-9C7C-9B2C2EAFDFAF"
 
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }
