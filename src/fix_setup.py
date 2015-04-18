from distutils.core import setup, Extension

module1 = Extension('FixTest',
    sources = ['py3fmath.cc',
              'py3fmathmod.cc'
              ],
              #include_dirs= ["C:/Boost/include/boost-1_57"],
              #      define_macros = [("WIN32",None),
              #      			("WPCAP",None),
              #      			("HAVE_REMOTE",None)],
              #library_dirs = ["F:/Develop/WpdPack4.1.2/Lib/x64"],
              #libraries = ["wpcap","ws2_32","iphlpapi"],
              extra_compile_args = ["/EHsc"]
)              

setup (name = 'Fixed16MathTest:Push the limits',
       version = '1.0',
       description = "You may be gone, but you're never over",
       author = 'Eminem',
       author_email = 'hai.bai.cn@gmail.com',
       ext_modules = [module1])
